/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <ir.h>
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>

size_t IR_IMPL_INTERRUPTS;

volatile struct ir_src_hw* ir_src;

volatile struct ir_icu_hw* ir_hart;

static size_t ir_scan_max_int()
{
    return 256;
}

void ir_init(void)
{
    /* Maps IR device */
    ir_src = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.irqc.ir.base, NUM_PAGES(sizeof(struct ir_src_hw)));

    ir_hart = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.irqc.ir.base + HART_REG_OFF,
        NUM_PAGES(sizeof(struct ir_icu_hw) * IRQC_HART_INST));

    /** Ensure that instructions after fence have the IR fully mapped */
    fence_sync();

    IR_IMPL_INTERRUPTS = ir_scan_max_int();

    for (size_t i = 0; i <= IR_IMPL_INTERRUPTS; i++) {
        ir_src->prio[i] = 0;
    }

    for (size_t i = 0; i < IR_PLAT_CNTXT_NUM; i++) {
        for (size_t j = 0; j < IR_NUM_ENBL_REGS; j++) {
            ir_src->enbl[i][j] = 0;
        }
    }
}

void ir_cpu_init(void)
{

}

static bool ir_cntxt_valid(size_t cntxt_id)
{

    return true;
}

void ir_set_enbl(size_t cntxt, irqid_t int_id, bool en)
{
    (void) cntxt;
    (void) int_id;
    (void) en;
}

bool ir_get_enbl(size_t cntxt, irqid_t int_id)
{
    (void) cntxt;
    (void) int_id;
    return false;
}

void ir_set_prio(irqid_t int_id, uint32_t prio)
{
    (void) int_id;
    (void) prio;
}

uint32_t ir_get_prio(irqid_t int_id)
{
    (void) int_id;
    (void) prio;
    return 0;
}

bool ir_get_pend(irqid_t int_id)
{
    (void) int_id;
    return false;
}

void ir_set_pend(irqid_t int_id)
{
    (void) int_id;
    return false;
}

void ir_clr_pend(irqid_t int_id)
{
    (void) int_id;
    return false;
}

void ir_handle(void)
{
    uint32_t id = ir_hart[cpu()->arch.ir_cntxt].claim;

    if (id != 0) {
        enum irq_res res = interrupts_handle(id);
        if (res == HANDLED_BY_HYP) {
            ir_hart[cpu()->arch.ir_cntxt].complete = id;
        }
    }
}

