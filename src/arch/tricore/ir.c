/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/ir.h>
#include <arch/prot.h>
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>
#include <platform_defs.h>
#include <platform.h>
#include <vm.h>

volatile struct ir_int_hw* ir_int;
volatile struct ir_src_hw* ir_src;

/* We need a flag to represent whether or not the IPIs have been initialized.
This happens because during the mem_init stage of the boot, several broadcasts
are attempted. When a CPU tries to write to the SRB register to broadcast an IPI,
if the IPIs are not initialized the system traps. This flag circumvents that.*/
bool ipi_initialized = false;

bitmap_t valid[IR_MAX_INTERRUPTS / sizeof(bitmap_t)] = INTERRUPTS_BITMAP;

static inline bool ir_id_valid(irqid_t id)
{
    return bitmap_get(valid, id);
}

void ir_init_ipi(void)
{
    for (unsigned int i = 0; i < PLAT_CPU_NUM; i++) {
        /* configure each GPSRG interrupt in this group for each CPU */
        /* We set the TOS of each Node in group 0 to the corresponding cpu*/

        IR_SRC_SET_TOS(ir_src->SRC[IPI_CPU_MSG + i], i);
        /* IPIs are the only interrupts for bao, we set them with the highest priority */
        IR_SRC_SET_SRPN(ir_src->SRC[IPI_CPU_MSG + i], IR_MAX_PRIO);

        prot_set_state(&ir_int->PROTTOS[i], PROT_STATE_CONFIG);
        ir_int->GPSRG[HYP_GPSR_GROUP].SWCACCEN[i] =
            (IR_SWCACCEN_VM_CTRL_MASK << IR_SWCACCEN_VM_PRS_CTRL_OFFSET) |
            (IR_SWCACCEN_VM0_MASK << IR_SWCACCEN_VM_OFFSET) | (IR_SWCACCEN_CPUx_MASK << i);
        prot_set_state(&ir_int->PROTTOS[i], PROT_STATE_RUN);

        IR_SRC_SET_SRE(ir_src->SRC[IPI_CPU_MSG + i], 1UL);
        /* TODO after enabling we can broadcast interrupts (through SRB) for all cpus simultaneously
         * although care must be taken as the current cpu could also be interrupted.
         * we could temporarily remove this cpu from broadcast. use the gpsr
         * lock mechanism to do sync */
    }

    /* Bao (VM0) on any CPU can use the broadcast register */
    apu_enable_access_all_cpus(&ir_int->ACCENSRB[HYP_GPSR_GROUP]);
    apu_enable_access_vm(&ir_int->ACCENSRB[HYP_GPSR_GROUP], HYP_VMID);

    /* Enable VM0 in the arbitration process on all CPUs*/
    for (size_t i = 0; i < platform.cpu_num; i++) {
        ir_int->ICU[i].VMEN |= ICU_VMEN_VM0_MASK;
    }

    fence_sync();
    ipi_initialized = true;
}

void ir_init(void)
{
    /* Set IR and SRC */
    ir_int = (struct ir_int_hw*)platform.arch.ir.int_addr;
    ir_src = (struct ir_src_hw*)platform.arch.ir.src_addr;
    /* Ensure that instructions after fence have the IR fully mapped */
    fence_sync();
}

void ir_cpu_init(void)
{
    /* In this function we only configure the TOS's related to each cpu */
    for (uint32_t tos = 0; tos < PLAT_CPU_NUM; tos++) {
        /* By default all TOSs (CPUs) can read and write on all field of SRC */
        /* but only the VM0 (hypervisor)*/
        apu_enable_access_cpu(&ir_int->TOS[tos].ACCENSCFG, tos);
        apu_enable_access_vm(&ir_int->TOS[tos].ACCENSCFG, HYP_VMID);
        apu_enable_access_cpu(&ir_int->TOS[tos].ACCENSCTRL, tos);
        apu_enable_access_vm(&ir_int->TOS[tos].ACCENSCTRL, HYP_VMID);

        /* We define VM0 on CPUx as the PROT owner of TOSx */
        /* Only bao on CPUx can reconfigure the acess to SRC for TOSx */
        prot_set_vm(&ir_int->PROTTOS[tos], HYP_VMID, true); // set VM0 as the owner and enable VM as
                                                            // of the owner ID
        prot_enable(&ir_int->PROTTOS[tos]);                 // enable protection
        prot_set_state(&ir_int->PROTTOS[tos], PROT_STATE_RUN);
    }
}

bool ir_get_pend(irqid_t int_id)
{
    if (!ir_id_valid(int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool pending = IR_SRC_GET_SRR(ir_src->SRC[int_id]) != 0;

    return pending;
}

bool ir_set_pend(irqid_t int_id)
{
    if (!ir_id_valid(int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
        return false;
    }
    IR_SRC_SET_SETR(ir_src->SRC[int_id], true);

    return true;
}

bool ir_clr_pend(irqid_t int_id)
{
    if (!ir_id_valid(int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_CLRR(ir_src->SRC[int_id], 1);

    return true;
}

void ir_handle(void)
{
    uint32_t cpuid = cpu()->id;

    unsigned long id = (ir_int->ICU[cpuid].VM[HYP_VMID] >> ICU_VMx_ID_OFFSET) & ICU_VMx_ID_MASK;

    enum irq_res res = interrupts_handle(id);
    (void)res;
}

void ir_send_ipi(cpuid_t target_cpu)
{
    if (ipi_initialized) {
        if (target_cpu >= PLAT_CPU_NUM) {
            ERROR("%s invalid cpu number %u", target_cpu, __func__);
        }
        /* We previously configure interrupts for each CPU */
        ir_int->SRB[HYP_GPSR_GROUP] = 0x1UL << target_cpu;
    }
}

void ir_assign_int_to_vm(vmid_t vmid, irqid_t id)
{
    /* VM direct injection */
    IR_SRC_SET_VM(ir_src->SRC[id], vmid);
}

void ir_assign_icu_to_vm(cpuid_t cpuid, vmid_t vmid)
{
    ir_int->ICU[cpuid].VMEN |= 1UL << vmid;
}

bool ir_src_enable(irqid_t id, bool en)
{
    if (!ir_id_valid(id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_SRE(ir_src->SRC[id], (unsigned long)en);

    return true;
}

unsigned long ir_src_get_node(irqid_t id)
{
    unsigned long val = 0;

    if (!ir_id_valid(id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return IR_INVALID_NODE;
    }

    val = ir_src->SRC[id];

    return val;
}

bool ir_src_set_node(irqid_t id, unsigned long val)
{
    if (!ir_id_valid(id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    ir_src->SRC[id] = val;

    return true;
}

void ir_clear_gpsr_group(unsigned long id)
{
    for (int node = 0; node < GPSR_MAX_NODES; node++) {
        ir_int->GPSRG[id].SWCACCEN[node] = 0;
    }
}

void ir_init_gpsr_group(unsigned long id, struct vm* vm)
{
    for (unsigned long int i = 0; i < platform.cpu_num; i++) {
        if (vm->cpus & (1UL << i)) {
            apu_enable_access_cpu(&ir_int->ACCENSRB[id], i);

            for (int node = 0; node < GPSR_MAX_NODES; node++) {
                ir_int->GPSRG[id].SWCACCEN[node] |= ACCESSEN_CPU_MASK(i);
                ir_int->GPSRG[id].SWCACCEN[node] |= ACCESSEN_VM_MASK(VMID_TO_HWVM(vm->id))
                    << IR_SWCACCEN_VM_OFFSET;
            }
        }
    }
}
