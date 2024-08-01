/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <ir.h>
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>

size_t IR_IMPL_INTERRUPTS;

volatile struct ir_global_hw* ir_global;

volatile struct ir_hart_hw* ir_hart;

static size_t ir_scan_max_int()
{
    size_t res = 0;
    for (size_t i = 1; i < IR_MAX_INTERRUPTS; i++) {
        ir_global->prio[i] = ~0U;
        if (ir_global->prio[i] == 0) {
            res = i - 1;
            break;
        }
        ir_global->prio[i] = 0;
    }
    return res;
}

void ir_init(void)
{
    /** Maps IR device */
    ir_global = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.irqc.ir.base, NUM_PAGES(sizeof(struct ir_global_hw)));

    ir_hart = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.irqc.ir.base + HART_REG_OFF,
        NUM_PAGES(sizeof(struct ir_hart_hw) * IRQC_HART_INST));

    /** Ensure that instructions after fence have the IR fully mapped */
    fence_sync();

    IR_IMPL_INTERRUPTS = ir_scan_max_int();

    for (size_t i = 0; i <= IR_IMPL_INTERRUPTS; i++) {
        ir_global->prio[i] = 0;
    }

    for (size_t i = 0; i < IR_PLAT_CNTXT_NUM; i++) {
        for (size_t j = 0; j < IR_NUM_ENBL_REGS; j++) {
            ir_global->enbl[i][j] = 0;
        }
    }
}

void ir_cpu_init(void)
{
    cpu()->arch.ir_cntxt =
        (unsigned)ir_plat_cntxt_to_id((struct ir_cntxt){ cpu()->id, PRIV_S });
    ir_hart[cpu()->arch.ir_cntxt].threshold = 0;
}

static bool ir_cntxt_valid(size_t cntxt_id)
{
    struct ir_cntxt cntxt = ir_plat_id_to_cntxt(cntxt_id);
    return (cntxt_id < IR_PLAT_CNTXT_NUM) && (cntxt.mode <= PRIV_S);
}

void ir_set_enbl(size_t cntxt, irqid_t int_id, bool en)
{
    size_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint32_t mask = 1U << (int_id % (sizeof(uint32_t) * 8));

    if (int_id <= IR_IMPL_INTERRUPTS && ir_cntxt_valid(cntxt)) {
        if (en) {
            ir_global->enbl[cntxt][reg_ind] |= mask;
        } else {
            ir_global->enbl[cntxt][reg_ind] &= ~mask;
        }
    }
}

bool ir_get_enbl(size_t cntxt, irqid_t int_id)
{
    size_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint32_t mask = 1U << (int_id % (sizeof(uint32_t) * 8));

    if (int_id <= IR_IMPL_INTERRUPTS && ir_cntxt_valid(cntxt)) {
        return ir_global->enbl[cntxt][reg_ind] & mask;
    } else {
        return false;
    }
}

void ir_set_prio(irqid_t int_id, uint32_t prio)
{
    if (int_id <= IR_IMPL_INTERRUPTS) {
        ir_global->prio[int_id] = prio;
    }
}

uint32_t ir_get_prio(irqid_t int_id)
{
    if (int_id <= IR_IMPL_INTERRUPTS) {
        return ir_global->prio[int_id];
    } else {
        return 0;
    }
}

bool ir_get_pend(irqid_t int_id)
{
    size_t reg_ind = (size_t)(int_id / 32);
    uint32_t mask = (1U << (int_id % 32));

    if (int_id <= IR_IMPL_INTERRUPTS) {
        return ir_global->pend[reg_ind] & mask;
    } else {
        return false;
    }
}

void ir_set_threshold(size_t cntxt, uint32_t threshold)
{
    if (ir_cntxt_valid(cntxt)) {
        ir_hart[cntxt].threshold = threshold;
    }
}

uint32_t ir_get_threshold(unsigned cntxt)
{
    uint32_t threshold = 0;
    if (ir_cntxt_valid(cntxt)) {
        threshold = ir_hart[cntxt].threshold;
    }
    return threshold;
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

/**
 * Context organization is spec-out by the vendor, this is the default mapping found in sifive's
 * ir.
 */

__attribute__((weak)) ssize_t ir_plat_cntxt_to_id(struct ir_cntxt cntxt)
{
    if (cntxt.mode != PRIV_M && cntxt.mode != PRIV_S) {
        return -1;
    }
    return (ssize_t)((cntxt.hart_id * 2) + (cntxt.mode == PRIV_M ? 0 : 1));
}

__attribute__((weak)) struct ir_cntxt ir_plat_id_to_cntxt(size_t id)
{
    struct ir_cntxt cntxt;
    if (id < IR_PLAT_CNTXT_NUM) {
        cntxt.hart_id = id / 2;
        cntxt.mode = (id % 2) == 0 ? PRIV_M : PRIV_S;
    } else {
        return (struct ir_cntxt){ INVALID_CPUID, 0 };
    }
    return cntxt;
}
