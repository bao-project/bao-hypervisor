/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <arch/gic.h>
#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>

volatile gicd_t gicd __attribute__((section(".devices"), aligned(PAGE_SIZE)));
volatile gicc_t gicc __attribute__((section(".devices"), aligned(PAGE_SIZE)));
volatile gich_t gich __attribute__((section(".devices"), aligned(PAGE_SIZE)));
volatile gich_t gich_alias[8]
    __attribute__((section(".devices"), aligned(PAGE_SIZE)));

static spinlock_t gicd_lock;

uint64_t NUM_LRS;

void gicc_init()
{
    for (int i = 0; i < gich_num_lrs(); i++) {
        gich.LR[i] = 0;
    }

    gicc.PMR = -1;
    gicc.CTLR |= GICC_CTLR_EN_BIT | GICC_CTLR_EOImodeNS_BIT;

    gich.HCR |= GICH_HCR_LRENPIE_BIT;
}

void gicc_save_state(gicc_state_t *state)
{
    state->CTLR = gicc.CTLR;
    state->PMR = gicc.PMR;
    state->BPR = gicc.BPR;
    state->IAR = gicc.IAR;
    state->EOIR = gicc.EOIR;
    state->RPR = gicc.RPR;
    state->HPPIR = gicc.HPPIR;
    state->priv_ISENABLER = gicd.ISENABLER[0];

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        state->priv_IPRIORITYR[i] = gicd.IPRIORITYR[i];
    }

    state->HCR = gich.HCR;
    for (int i = 0; i < gich_num_lrs(); i++) {
        state->LR[i] = gich.LR[i];
    }
}

void gicc_restore_state(gicc_state_t *state)
{
    gicc.CTLR = state->CTLR;
    gicc.PMR = state->PMR;
    gicc.BPR = state->BPR;
    gicc.IAR = state->IAR;
    gicc.EOIR = state->EOIR;
    gicc.RPR = state->RPR;
    gicc.HPPIR = state->HPPIR;
    gicd.ISENABLER[0] = state->priv_ISENABLER;

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicd.IPRIORITYR[i] = state->priv_IPRIORITYR[i];
    }

    gich.HCR = state->HCR;
    for (int i = 0; i < gich_num_lrs(); i++) {
        gich.LR[i] = state->LR[i];
    }
}

void gic_cpu_init()
{
    for (int i = 0; i < GIC_NUM_INT_REGS(GIC_CPU_PRIV); i++) {
        /**
         * Make sure all private interrupts are not enabled, non pending,
         * non active.
         */
        gicd.ICENABLER[i] = -1;
        gicd.ICPENDR[i] = -1;
        gicd.ICACTIVER[i] = -1;
    }

    /* Clear any pending SGIs. */
    for (int i = 0; i < GIC_NUM_SGI_REGS; i++) {
        gicd.CPENDSGIR[i] = -1;
    }

    for (int i = 0; i < GIC_NUM_TARGET_REGS(GIC_CPU_PRIV); i++) {
        gicd.IPRIORITYR[i] = -1;
    }

    for (int i = 0; i < GIC_NUM_TARGET_REGS(GIC_CPU_PRIV); i++) {
        gicd.IPRIORITYR[i] = -1;
    }

    gicc_init();
}

void gic_maintenance_handler(uint64_t arg, uint64_t source);

void gic_init()
{
    NUM_LRS = gich_num_lrs();
    size_t int_num = gic_num_irqs();

    /* Bring distributor to known state */
    for (int i = GIC_NUM_PRIVINT_REGS; i < GIC_NUM_INT_REGS(int_num); i++) {
        /**
         * Make sure all interrupts are not enabled, non pending,
         * non active.
         */
        gicd.ICENABLER[i] = -1;
        gicd.ICPENDR[i] = -1;
        gicd.ICACTIVER[i] = -1;
    }

    /* All interrupts have lowest priority possible by default */
    for (int i = 0; i < GIC_NUM_PRIO_REGS(int_num); i++)
        gicd.IPRIORITYR[i] = -1;

    /* No CPU targets for any interrupt by default */
    for (int i = 0; i < GIC_NUM_TARGET_REGS(int_num); i++)
        gicd.ITARGETSR[i] = 0;

    /* ICFGR are platform dependent, lets leave them as is */

    /* No need to setup gicd.NSACR as all interrupts are  setup to group 1 */

    interrupts_reserve(platform.arch.gic.maintenance_id,
                       gic_maintenance_handler);

    /* Enable distributor */
    gicd.CTLR |= GICD_CTLR_EN_BIT;
}

void gic_handle()
{
    uint64_t ack = gicc.IAR;
    uint64_t id = bit_extract(ack, GICC_IAR_ID_OFF, GICC_IAR_ID_LEN);
    uint64_t src = bit_extract(ack, GICC_IAR_CPU_OFF, GICC_IAR_CPU_LEN);

    if (id >= 1022) return;

    enum irq_res res = interrupts_handle(id, src);

    gicc.EOIR = ack;

    if (res == HANDLED_BY_HYP) gicc.DIR = ack;
}

void gicd_send_sgi(uint64_t cpu_target, uint64_t sgi_num)
{
    gicd.SGIR = (1UL << (GICD_SGIR_CPUTRGLST_OFF + cpu_target)) |
                (sgi_num & GICD_SGIR_SGIINTID_MSK);
}

uint64_t gicd_get_prio(uint64_t int_id)
{
    spin_lock(&gicd_lock);

    uint64_t reg_ind = (int_id * GIC_PRIO_BITS) / (sizeof(uint32_t) * 8);
    uint64_t off = (int_id * GIC_PRIO_BITS) % (sizeof(uint32_t) * 8);

    uint64_t prio =
        gicd.IPRIORITYR[reg_ind] >> off & ((1 << GIC_PRIO_BITS) - 1);

    spin_unlock(&gicd_lock);

    return prio;
}

void gicd_set_prio(uint64_t int_id, uint8_t prio)
{
    spin_lock(&gicd_lock);

    uint64_t reg_ind = (int_id * GIC_PRIO_BITS) / (sizeof(uint32_t) * 8);
    uint64_t off = (int_id * GIC_PRIO_BITS) % (sizeof(uint32_t) * 8);
    uint64_t mask = ((1U << GIC_PRIO_BITS) - 1) << off;

    gicd.IPRIORITYR[reg_ind] =
        (gicd.IPRIORITYR[reg_ind] & ~mask) | ((prio << off) & mask);

    spin_unlock(&gicd_lock);
}

uint8_t gicd_get_state(uint64_t int_id)
{
    spin_lock(&gicd_lock);

    uint64_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint64_t mask = 1U << int_id % (sizeof(uint32_t) * 8);

    uint64_t pend = (gicd.ISPENDR[reg_ind] & mask) ? 1 : 0;
    uint64_t act = (gicd.ISACTIVER[reg_ind] & mask) ? 1 : 0;

    spin_unlock(&gicd_lock);

    return pend | (act << 1);
}

void gicd_set_pend(uint64_t int_id, bool pend)
{
    if (gic_is_sgi(int_id)) {
        uint64_t reg_ind = int_id / 4;
        uint64_t off = (int_id % 4) * 8;

        if (pend) {
            gicd.SPENDSGIR[reg_ind] = (1U) << (off + cpu.id);
        } else {
            gicd.CPENDSGIR[reg_ind] = BIT_MASK(off, 8);
        }

    } else {
        uint64_t reg_ind = int_id / (sizeof(uint32_t) * 8);
        uint64_t mask = 1U << int_id % (sizeof(uint32_t) * 8);

        if (pend) {
            gicd.ISPENDR[reg_ind] = mask;
        } else {
            gicd.ICPENDR[reg_ind] = mask;
        }
    }
}

void gicd_set_act(uint64_t int_id, bool act)
{
    uint64_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint64_t mask = 1U << int_id % (sizeof(uint32_t) * 8);

    if (act) {
        gicd.ISACTIVER[reg_ind] = mask;
    } else {
        gicd.ICACTIVER[reg_ind] = mask;
    }
}

void gicd_set_state(uint64_t int_id, uint8_t state)
{
    spin_lock(&gicd_lock);

    uint64_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint64_t mask = 1U << int_id % (sizeof(uint32_t) * 8);

    if (state & 0x2) {
        gicd.ISACTIVER[reg_ind] = mask;
    } else {
        gicd.ICACTIVER[reg_ind] = mask;
    }

    if (state & 0x1) {
        gicd.ISPENDR[reg_ind] = mask;
    } else {
        gicd.ICPENDR[reg_ind] = mask;
    }

    spin_unlock(&gicd_lock);
}

void gicd_set_trgt(uint64_t int_id, uint8_t trgt)
{
    spin_lock(&gicd_lock);

    uint64_t reg_ind = (int_id * GIC_TARGET_BITS) / (sizeof(uint32_t) * 8);
    uint64_t off = (int_id * GIC_TARGET_BITS) % (sizeof(uint32_t) * 8);
    uint32_t mask = ((1U << GIC_TARGET_BITS) - 1) << off;

    gicd.ITARGETSR[reg_ind] =
        (gicd.ITARGETSR[reg_ind] & ~mask) | ((trgt << off) & mask);

    spin_unlock(&gicd_lock);
}

void gicd_set_enable(uint64_t int_id, bool en)
{
    uint64_t reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint64_t bit = (1UL << int_id % (sizeof(uint32_t) * 8));

    spin_lock(&gicd_lock);

    if (en) {
        gicd.ISENABLER[reg_ind] = bit;
    } else {
        gicd.ICENABLER[reg_ind] = bit;
    }

    spin_unlock(&gicd_lock);
}
