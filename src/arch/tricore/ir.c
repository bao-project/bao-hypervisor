/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include "inc/ir.h"
#include "arch/interrupts.h"
#include "inc/arch/ir.h"
#include <ir.h>
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>


volatile struct ir_int_hw* ir_int;
volatile struct ir_src_hw* ir_src;
volatile struct ir_gpsr_hw* ir_gpsr;

void ir_init(void)
{
    if (cpu_is_master()) {
        /* Map IR */
        ir_int = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
                platform.arch.ir.base_int, NUM_PAGES(sizeof(struct ir_int_hw)));
        ir_src = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
                platform.arch.ir.base_src,
                NUM_PAGES(sizeof(ir_src->SRC[0]) * PLAT_IR_MAX_INTERRUPTS));

        /* TODO add group broadcast support */
        ir_gpsr = (volatile struct ir_gpsr_hw*)&ir_src->SRC[IPI_CPU_MSG];

        /** Ensure that instructions after fence have the IR fully mapped */
        fence_sync();
    }
    cpu_sync_and_clear_msgs(&cpu_glb_sync);


    /* disable all interrupts */
    for (size_t i = 0; i < PLAT_IR_MAX_INTERRUPTS; i++) {
        /* TODO Inneficient, maybe write default value to SRC */
        IR_SRC_SET_SRPN(ir_src->SRC[i], 0);
        IR_SRC_SET_TOS(ir_src->SRC[i], 0xf);
        IR_SRC_SET_SRE(ir_src->SRC[i], false);
    }

    for(unsigned int i = 0; i < PLAT_CPU_NUM; i++){
        /* configure each GPSRG interrupt in this group for each CPU */
        IR_SRC_SET_TOS(ir_gpsr->SRC_GPSRG_SR[i], i);

        /* TODO after enabling we can broadcast interrupts (through SRB) for all cpus simultaneously 
         * although care must be taken as the current cpu could also be interrupted.
         * we could disable interrupts, and temporarily remove this cpu from
         * broadcast. use the gpsr lock mechanism to do sync */

        /* TODO add api for ipi management to bao */
    }
}

void ir_cpu_init(void)
{

}

void ir_set_enbl(irqid_t int_id, bool en)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_TOS(ir_src[int_id], cpu()->cpuid); /* TODO assumes current cpu
                                                     is requesting interrupt
                                                     to be active */
    /* TODO: we already filled the SCR.VM during setup so no need to update again */
    IR_SRC_SET_SRE(ir_src[int_id], en);
}

bool ir_get_enbl(size_t cntxt, irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool enabled = IR_SRC_GET_SRE(ir_src[int_id]);
    return enabled;
}

void ir_set_prio(irqid_t int_id, uint32_t prio)
{
    if(prio > IR_MAX_PRIO || int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid priority %u", __func__, prio);
    }

    IR_SRC_SET_SRPN(ir_src[i], prio);
}

uint32_t ir_get_prio(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    uint32_t prio = IR_SRC_GET_SRPN(ir_src[int_id]);

    return prio;
}

bool ir_get_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    bool pending = IR_SRC_GET_SRR(ir_src[int_id]);
    return pending;
}

void ir_set_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_SRR(ir_src[int_id], true);
}

void ir_clr_pend(irqid_t int_id)
{
    if(int_id > PLAT_IR_MAX_INTERRUPTS) {
        ERROR("%s Invalid interrupt %u", __func__, int_id);
    }
    IR_SRC_SET_CLRR(ir_src[int_id], true);
}

void ir_handle(void)
{
    uint32_t cpuid = cpu()->cpuid;
    uint32_t sr = ir_int_hw.ICU[cpuid];

    int pn = GET_IR_SR_VALID(sr);
    int valid = GET_IR_SR_VALID(sr);
    int invalid = GET_IR_SR_INVALID(sr);
    unsigned int intid = GET_IR_SR_ID(sr);
    unsigned int cs = GET_IR_SR_CS(sr);
    unsigned int stat = GET_IR_SR_STAT(sr);

    /* TODO */
}
void ir_send_ipi(cpuid_t target_cpu, irqid_t ipi_id)
{
    if(target_cpu < PLAT_NUM_CPUS){
        ERROR("%s invalid cpu number %u", target_cpu, __func__);
    }

    /* TODO we are using group 0 for hyp we should probably use the last one */
    /* TODO why not do this? SET_GPSR_SR_SETR(ir_int_hw.GPSRG[0].SWC.CR[target_cpu], 1); */

    /* We previously configure interrupts for each CPU */
    IR_SRC_SETR_POS(ir_gpsr.SRC_GPSRG_SR[target_cpu], 1);
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
        IR_SRC_SET_TOS(sr, cpu()->cpuid); /* current cpu. TODO only one cpu can
                                             be attributed to a given interrupt */
        IR_SRC_SET_SRE(sr, 1); /* enable */
    } else {
        IR_SRC_SET_SRE(sr, 0); /* disable */
    }
    ir_src_hw.SRC[int_id] = sr;
}

void ir_assign_int_to_vm(struct vm* vm, irqid_t id)
{
    /* VM direct injection */
    IR_SRC_SET_VM(ir_src_hw.SRC[id], vm->vm_id);
    ir_src_hw.ICU[cpu()->cpuid] = 1 << vm->vm_id;

    /* set interrupt on cpu */
    IRS_SRC_SET_VM(ir_int_hw.SRC[id], cpu()->cpuid);

}

void ir_assign_icu_to_vm(struct vm* vm)
{
    uint8_t vmid = vm->id;
    /* TODO: check this upon vmid generation */
    /* TODO: add this define */
    if(vmid > PLAT_TRICORE_VM_NUM)
        ERROR("Unsuported VM id %u", vmid);

    ir_int_hw->ICU[cpu()->id].VMEN = 1 << vmid;
}
