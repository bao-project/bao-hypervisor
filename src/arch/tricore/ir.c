/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/ir.h>
#include "arch/interrupts.h"
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>
#include <platform_defs.h>
#include <vm.h>


volatile struct ir_int_hw* ir_int;
volatile struct ir_src_hw* ir_src;

void ir_init_ipi(void)
{
    /* TODO should each CPU add itself to the broadcast group? */
    for(unsigned int i = 0; i < PLAT_CPU_NUM; i++){
        /* configure each GPSRG interrupt in this group for each CPU */
        IR_SRC_SET_TOS(ir_src->SRC[IPI_CPU_MSG + i], i);

        /* TODO after enabling we can broadcast interrupts (through SRB) for all cpus simultaneously
         * although care must be taken as the current cpu could also be interrupted.
         * we could  temporarily remove this cpu from broadcast. use the gpsr
         * lock mechanism to do sync */

        /* TODO limit access to SRB */
    }
}

void ir_init(void)
{
    /* Map IR and SRC */
    ir_int = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.arch.ir.int_addr, NUM_PAGES(sizeof(struct ir_int_hw)));
    ir_src = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.arch.ir.src_addr,
            NUM_PAGES(sizeof(ir_src->SRC[0]) * PLAT_IR_MAX_INTERRUPTS));

    /** Ensure that instructions after fence have the IR fully mapped */
    fence_sync();

    /* make sure all interrupts are set to a default state */
    /* TODO necessary? default states is all 0x0 except TOS which is set to 0xF */
    for (size_t i = 0; i < PLAT_IR_MAX_INTERRUPTS; i++) {
        /* TODO Inneficient, maybe write default value to SRC */
        IR_SRC_SET_SRPN(ir_src->SRC[i], 0);
        /* we need to set TOS to prevent VMs from accessing the interrupts */
        IR_SRC_SET_TOS(ir_src->SRC[i], 0);
        IR_SRC_SET_SRE(ir_src->SRC[i], false);
        IR_SRC_SET_VM(ir_src->SRC[i], 0);
    }
}

void ir_cpu_init(void)
{
    /* Nothing to do */
}

void ir_set_enbl(irqid_t int_id, bool en)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_TOS(ir_src->SRC[int_id], cpu()->id); /* TODO assumes current cpu
                                                     is requesting interrupt
                                                     to be active */
    /* TODO: we already filled the SCR.VM during setup so no need to update again */
    IR_SRC_SET_SRE(ir_src->SRC[int_id], en);
}

bool ir_get_enbl(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool enabled = IR_SRC_GET_SRE(ir_src->SRC[int_id]);
    return enabled;
}

void ir_set_prio(irqid_t int_id, uint32_t prio)
{
    if(prio > IR_MAX_PRIO || int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid priority %u", __func__, prio);
    }

    IR_SRC_SET_SRPN(ir_src->SRC[int_id], prio);
}

uint32_t ir_get_prio(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    uint32_t prio = IR_SRC_GET_SRPN(ir_src->SRC[int_id]);

    return prio;
}

bool ir_get_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool pending = IR_SRC_GET_SRR(ir_src->SRC[int_id]) != 0;
    return pending;
}

bool ir_set_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_SETR(ir_src->SRC[int_id], true);
    return true;
}

bool ir_clr_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_CLRR(ir_src->SRC[int_id], 1);
    return true;
}

void ir_handle(void)
{
    uint32_t cpuid = cpu()->id;
    (void)cpuid;

    bool for_vm = true;
    /* TODO read ICR.PIPN */
    unsigned long id = 0;

    if(for_vm){
        /* TODO */
        /* uint32_t sr = ir_int->ICU[cpuid].LASR; */

        /* int pn = GET_IR_SR_VALID(sr); */
        /* int valid = GET_IR_SR_VALID(sr); */
        /* int invalid = GET_IR_SR_INVALID(sr); */
        /* unsigned int intid = GET_IR_SR_ID(sr); */
        /* unsigned int cs = GET_IR_SR_CS(sr); */
        /* unsigned int stat = GET_IR_SR_STAT(sr); */
    }

    enum irq_res res = interrupts_handle(id);
    (void)res;

    ir_clr_pend(id);
    /* TODO */
}

void ir_send_ipi(cpuid_t target_cpu)
{
    if(target_cpu < PLAT_CPU_NUM){
        ERROR("%s invalid cpu number %u", target_cpu, __func__);
    }

    /* TODO we are using group 0 for hyp we should probably use the last one */
    /* TODO why not do this? SET_GPSR_SR_SETR(ir_int->GPSRG[0].SWC.CR[target_cpu], 1); */

    /* We previously configure interrupts for each CPU */
    ir_set_pend(IPI_CPU_MSG + target_cpu);
}

void ir_config_irq(irqid_t int_id, bool en)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS){
        ERROR("%s invalid interrupt %u", __func__, int_id);
    }

    uint32_t sr = 0;
    if(en) {
        IR_SRC_SET_SRPN(sr, 0xff); /* highest priority TODO only do this once*/
        IR_SRC_SET_VM(sr, 0); /* VM0 (ie., hyp) TODO only do this once */
        IR_SRC_SET_TOS(sr, cpu()->id); /* current cpu. TODO only one cpu can
                                             be attributed to a given interrupt */
        IR_SRC_SET_SRE(sr, 1); /* enable */
    } else {
        IR_SRC_SET_SRE(sr, 0); /* disable */
    }
    ir_src->SRC[int_id] = sr;
}

void ir_assign_int_to_vm(struct vm* vm, irqid_t id)
{
    /* TODO assumes interrupt is for this cpu, and that VM was assigned to this CPU */

    /* VM direct injection */
    uint32_t vmid = vm->id;
    if(vmid > 7)
        ERROR("Unsuported vm id %u > 7", vmid);

    IR_SRC_SET_VM(ir_src->SRC[id], vmid);

    /* set interrupt on cpu */
    IR_SRC_SET_TOS(ir_src->SRC[id], cpu()->id);
    IR_SRC_SET_VM(ir_src->SRC[id], vmid);
}

void ir_reset_cpu_int_ctrl_access(unsigned long icuid)
{
    ir_int->TOS[icuid].ACCENSCTRL.VM = 0;
    ir_int->TOS[icuid].ACCENSCTRL.PRS = 0;
}
void ir_reset_cpu_int_cfg_access(unsigned long icuid)
{
    ir_int->TOS[icuid].ACCENSCFG.VM = 0;
    ir_int->TOS[icuid].ACCENSCFG.PRS = 0;
}

void ir_enable_vm_int_ctrl_access(unsigned long icuid, unsigned long vmid)
{
    unsigned long perm = 0;
    perm = (1 << vmid); // read
    perm |= (1 << vmid << 16); // write

    unsigned long vm = ir_int->TOS[icuid].ACCENSCTRL.VM;
    vm |= perm;
    ir_int->TOS[cpu()->id].ACCENSCTRL.VM = vm; // read

    unsigned long prs = ir_int->TOS[icuid].ACCENSCTRL.PRS;
    prs |= perm;
    /* TODO confirm PRS is the same as VCON2.L2_PRS / PSW.PRS or maybe VM should control this */
    ir_int->TOS[cpu()->id].ACCENSCTRL.PRS = prs; // read
}

void ir_enable_vm_int_cfg_access(unsigned long icuid, unsigned long vmid)
{
    unsigned long perm = 0;
    perm = (1 << vmid); // read
    perm |= (1 << vmid << 16); // write

    unsigned long vm = ir_int->TOS[icuid].ACCENSCTRL.VM;
    vm |= perm;
    ir_int->TOS[cpu()->id].ACCENSCTRL.VM = vm; // read

    unsigned long prs = ir_int->TOS[icuid].ACCENSCTRL.PRS;
    prs |= perm;
    /* TODO confirm PRS is the same as VCON2.L2_PRS / PSW.PRS or maybe VM should control this */
    ir_int->TOS[cpu()->id].ACCENSCFG.PRS = prs; // read
}

void ir_assign_icu_to_vm(unsigned long id, struct vm* vm)
{
    /* VM direct injection */
    uint32_t vmid = vm->id;
    if(vmid)
        ERROR("Unsuported vm id %u > 7", vmid);

    ir_reset_cpu_int_ctrl_access(id);
    ir_enable_vm_int_ctrl_access(id, vmid);
    ir_enable_vm_int_ctrl_access(id, 0); /* TODO 0 is hyp */

    /* TODO should not be needed */
    ir_reset_cpu_int_cfg_access(id);
    ir_enable_vm_int_cfg_access(id, 0); /* TODO 0 is hyp */
}

