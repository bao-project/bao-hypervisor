/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/ir.h>
#include "arch/interrupts.h"
#include <arch/prot.h>
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>
#include <platform_defs.h>
#include <platform.h>

#include <vm.h>
#include <config.h>

volatile struct ir_int_hw* ir_int;
volatile struct ir_src_hw* ir_src;

bool ipi_initialized = false;

bitmap_t valid[IR_MAX_INTERRUPTS / 4] = INTERRUPTS_BITMAP;

spinlock_t src_lock = SPINLOCK_INITVAL;

void ir_init_ipi(void)
{
    for (unsigned int i = 0; i < PLAT_CPU_NUM; i++) {
        /* configure each GPSRG interrupt in this group for each CPU */
        /* We set the TOS of each Node in group 0 to the corresponding cpu*/

        IR_SRC_SET_TOS(ir_src->SRC[IPI_CPU_MSG + i], i);
        /* IPIs are the only interrupts for bao, we set them with the highest priority */
        IR_SRC_SET_SRPN(ir_src->SRC[IPI_CPU_MSG + i], 0xFF);

        prot_set_state(&ir_int->PROTTOS[i], PROT_STATE_CONFIG);
        ir_int->GPSRG[0].SWCACCEN[i] = (0UL << 31) | (1UL << 16) | (0x3UL << i);
        prot_set_state(&ir_int->PROTTOS[i], PROT_STATE_RUN);

        IR_SRC_SET_SRE(ir_src->SRC[IPI_CPU_MSG + i], 1UL);
        /* TODO after enabling we can broadcast interrupts (through SRB) for all cpus simultaneously
         * although care must be taken as the current cpu could also be interrupted.
         * we could temporarily remove this cpu from broadcast. use the gpsr
         * lock mechanism to do sync */
    }

    /* Bao (VM0) on any CPU can use the broadcast register */
    apu_enable_access_all_cpus(&ir_int->ACCENSRB[0]);
    apu_enable_access_vm(&ir_int->ACCENSRB[0], 0);

    /* Enable VM0 in the arbitration process on all CPUs*/
    for (size_t i = 0; i < platform.cpu_num; i++) {
        ir_int->ICU[i].VMEN |= 0x1;
    }

    fence_sync();
    ipi_initialized = true;
}

static void ir_assign_cpu_tos_access(void)
{
    /* In this function we only configure the TOS's related to each cpu */
    for (uint32_t tos = 0; tos < PLAT_CPU_NUM; tos++) {
        /* By default all TOSs (CPUs) can read and write on all field of SRC */
        /* but only the VM0 (hypervisor)*/
        apu_enable_access_cpu(&ir_int->TOS[tos].ACCENSCFG, tos);
        apu_enable_access_vm(&ir_int->TOS[tos].ACCENSCFG, 0);
        apu_enable_access_cpu(&ir_int->TOS[tos].ACCENSCTRL, tos);
        apu_enable_access_vm(&ir_int->TOS[tos].ACCENSCTRL, 0);

        /* We define VM0 on CPUx as the PROT owner of TOSx */
        /* Only bao on CPUx can reconfigure the acess to SRC for TOSx */
        prot_set_vm(&ir_int->PROTTOS[tos], 0, true); // set VM0 as the owner and enable VM as of the
                                                     // owner ID
        prot_enable(&ir_int->PROTTOS[tos]);          // enable protection
        prot_set_state(&ir_int->PROTTOS[tos], PROT_STATE_RUN);

        /* TODO: MS: Maybe sacrifice readability for optimizations, all the previous
            statements write on the same register */
    }
}

void ir_init(void)
{
    /* Map IR and SRC */
    if (!DEFINED(MMIO_SLAVE_SIDE_PROT)) {
        ir_int = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, platform.arch.ir.int_addr,
            platform.arch.ir.int_addr, NUM_PAGES(sizeof(struct ir_int_hw)));
        ir_src = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, platform.arch.ir.src_addr,
            platform.arch.ir.src_addr, NUM_PAGES(sizeof(ir_src->SRC[0]) * PLAT_IR_MAX_INTERRUPTS));
    } else {
        ir_int = (struct ir_int_hw*)platform.arch.ir.int_addr;
        ir_src = (struct ir_src_hw*)platform.arch.ir.src_addr;
    }
    /** Ensure that instructions after fence have the IR fully mapped */
    fence_sync();

    if (cpu_is_master()) {
        ir_assign_cpu_tos_access();
    }
}

void ir_cpu_init(void)
{
    /* Nothing to do */
}

void ir_set_enbl(irqid_t int_id, bool en)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_TOS(ir_src->SRC[int_id], cpu()->id); /* TODO assumes current cpu
                                                     is requesting interrupt
                                                     to be active */
    IR_SRC_SET_SRE(ir_src->SRC[int_id], (unsigned long)en);

    spin_unlock(&src_lock);
}

bool ir_get_enbl(irqid_t int_id)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool enabled = IR_SRC_GET_SRE(ir_src->SRC[int_id]);

    spin_unlock(&src_lock);

    return enabled;
}

void ir_set_prio(irqid_t int_id, uint32_t prio)
{
    spin_lock(&src_lock);

    if (prio > IR_MAX_PRIO || !bitmap_get(valid, int_id)) {
        ERROR("%s Invalid priority %u", __func__, prio);
    }

    IR_SRC_SET_SRPN(ir_src->SRC[int_id], prio);

    spin_unlock(&src_lock);
}

uint32_t ir_get_prio(irqid_t int_id)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    uint32_t prio = IR_SRC_GET_SRPN(ir_src->SRC[int_id]);

    spin_unlock(&src_lock);

    return prio;
}

bool ir_get_pend(irqid_t int_id)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool pending = IR_SRC_GET_SRR(ir_src->SRC[int_id]) != 0;

    spin_unlock(&src_lock);

    return pending;
}

bool ir_set_pend(irqid_t int_id)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
        spin_unlock(&src_lock);

        return false;
    } else {
        IR_SRC_SET_SETR(ir_src->SRC[int_id], true);
        spin_unlock(&src_lock);

        return true;
    }
}

bool ir_clr_pend(irqid_t int_id)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, int_id)) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_CLRR(ir_src->SRC[int_id], 1);

    spin_unlock(&src_lock);

    return true;
}

void ir_handle(void)
{
    uint32_t cpuid = cpu()->id;
    (void)cpuid;

    bool for_vm = true;

    unsigned long id = (ir_int->ICU[cpuid].VM[0] >> 16) & 0x7FF;

    if (for_vm) {
        /* TODO: Currently not supported? */
    }

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
        ir_int->SRB[0] = 0x1UL << target_cpu;
    }
}

void ir_assign_int_to_vm(struct vm* vm, irqid_t id)
{
    /* VM direct injection */
    uint32_t vmid = (vm->id) + 1;
    if (vmid > 7) {
        ERROR("Unsuported vm id %u > 7", vmid);
        return;
    }

    IR_SRC_SET_VM(ir_src->SRC[id], vmid);
}

void ir_assign_icu_to_vm(unsigned long id, struct vm* vm)
{
    UNUSED_ARG(id);
    /* VM direct injection */
    uint32_t vmid = (vm->id) + 1;
    if (vmid > 7) {
        ERROR("Unsuported vm id %u > 7", vmid);
        return;
    }

    ir_int->ICU[cpu()->id].VMEN |= 1UL << vmid;
}

bool ir_id_valid(unsigned long id)
{
    return bitmap_get(valid, id);
}

bool ir_src_config_irq(unsigned long id, unsigned long tos, unsigned long vm, unsigned long prio)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_SRPN(ir_src->SRC[id], prio);
    IR_SRC_SET_VM(ir_src->SRC[id], vm);
    IR_SRC_SET_TOS(ir_src->SRC[id], tos);

    spin_unlock(&src_lock);

    return true;
}

bool ir_src_config_tos(unsigned long id, unsigned long tos)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_TOS(ir_src->SRC[id], tos);

    spin_unlock(&src_lock);

    return true;
}

bool ir_src_config_vm(unsigned long id, unsigned long vm)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_VM(ir_src->SRC[id], vm);

    spin_unlock(&src_lock);

    return true;
}

bool ir_src_config_priority(unsigned long id, unsigned long prio)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_SRPN(ir_src->SRC[id], prio);

    spin_unlock(&src_lock);

    return true;
}

bool ir_src_enable(unsigned long id, bool en)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    IR_SRC_SET_SRE(ir_src->SRC[id], (unsigned long)en);

    spin_unlock(&src_lock);

    return true;
}

unsigned long ir_src_get_node(unsigned long id)
{
    unsigned long val = 0;
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return (unsigned long)-1;
    }

    val = ir_src->SRC[id];

    spin_unlock(&src_lock);

    return val;
}

bool ir_src_set_node(unsigned long id, unsigned long val)
{
    spin_lock(&src_lock);

    if (!bitmap_get(valid, id)) {
        ERROR("%s Invalid interrupt %u", __func__, id);
        return false;
    }

    ir_src->SRC[id] = val;

    spin_unlock(&src_lock);

    return true;
}

void ir_clear_gspr_group(unsigned long id)
{
    for (int node = 0; node < 8; node++) {
        ir_int->GPSRG[id].SWCACCEN[node] = 0;
    }
}

void ir_init_gspr_group(unsigned long id, struct vm* vm)
{
    for (unsigned long int i = 0; i < platform.cpu_num; i++) {
        if (vm->cpus & (1UL << i)) {
            apu_enable_access_cpu(&ir_int->ACCENSRB[id], i);

            for (int node = 0; node < 8; node++) {
                // ir_int->GPSRG[id].SWCACCEN[node] = 0;
                ir_int->GPSRG[id].SWCACCEN[node] |= (unsigned long)0x3 << (i * 2);
                ir_int->GPSRG[id].SWCACCEN[node] |= (unsigned long)0x1 << (vm->id + 16);
            }
        }
    }
}
