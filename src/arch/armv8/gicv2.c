/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
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

extern volatile gicd_t gicd;
extern spinlock_t gicd_lock;

volatile gicc_t gicc __attribute__((section(".devices"), aligned(PAGE_SIZE)));
volatile gich_t gich __attribute__((section(".devices"), aligned(PAGE_SIZE)));

static uint64_t gic_cpu_map[GIC_MAX_TARGETS];

uint64_t NUM_LRS;

uint64_t gich_num_lrs()
{
    return ((gich.VTR & GICH_VTR_MSK) >> GICH_VTR_OFF) + 1;
}

inline uint64_t gich_read_lr(size_t i)
{
    if (i < NUM_LRS) {
        return gich.LR[i];
    } else {
        ERROR("gic: trying to read inexistent list register");
    }
}

inline void gich_write_lr(size_t i, uint64_t val)
{
    if (i < NUM_LRS) {
        gich.LR[i] = val;
    } else {
        ERROR("gic: trying to write inexistent list register");
    }
}

uint32_t gich_get_hcr()
{
    return gich.HCR;
}

void gich_set_hcr(uint32_t hcr)
{
    gich.HCR = hcr;
}

uint32_t gich_get_misr()
{
    return gich.MISR;
}

uint64_t gich_get_eisr()
{
    uint64_t eisr = gich.EISR[0];
    if (NUM_LRS > 32) eisr |= (((uint64_t)gich.EISR[1] << 32));
    return eisr;
}

uint64_t gich_get_elrsr()
{
    uint64_t elsr = gich.ELSR[0];
    if (NUM_LRS > 32) elsr |= (((uint64_t)gich.ELSR[1] << 32));
    return elsr;
}

static inline void gicc_init()
{
    for (int i = 0; i < gich_num_lrs(); i++) {
        gich.LR[i] = 0;
    }

    gicc.PMR = GIC_LOWEST_PRIO;
    gicc.CTLR |= GICC_CTLR_EN_BIT | GICC_CTLR_EOImodeNS_BIT;

    gich.HCR |= GICH_HCR_LRENPIE_BIT;
    
    uint64_t sgi_targets = gicd.ITARGETSR[0] & BIT_MASK(0, GIC_TARGET_BITS);
    int64_t gic_cpu_id = 
        bitmap_find_nth((bitmap_t)&sgi_targets, GIC_TARGET_BITS, 1, 0, true);
    if(gic_cpu_id < 0) {
        ERROR("cant find gic cpu id");
    }

    gic_cpu_map[cpu.id] = gic_cpu_id;
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

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicd.IPRIORITYR[i] = -1;
    }

    gicc_init();
}

void gic_map_mmio()
{
    mem_map_dev(&cpu.as, (void *)&gicc, platform.arch.gic.gicc_addr,
                NUM_PAGES(sizeof(gicc)));
    mem_map_dev(&cpu.as, (void *)&gich, platform.arch.gic.gich_addr,
                NUM_PAGES(sizeof(gich)));
    mem_map_dev(&cpu.as, (void *)&gicd, platform.arch.gic.gicd_addr,
                NUM_PAGES(sizeof(gicd)));
}

uint32_t gicc_iar() {
    return gicc.IAR;
}

void gicc_eoir(uint32_t eoir) {
     gicc.EOIR = eoir;
}

void gicc_dir(uint32_t dir) {
     gicc.DIR = dir;
}

void gic_send_sgi(uint64_t cpu_target, uint64_t sgi_num)
{
    if (sgi_num < GIC_MAX_SGIS && cpu_target < GIC_MAX_TARGETS) {
        gicd.SGIR = 
            (1UL << (GICD_SGIR_CPUTRGLST_OFF + gic_cpu_map[cpu_target])) |
            (sgi_num & GICD_SGIR_SGIINTID_MSK);
    }
}

static inline uint8_t gic_translate_cpu_to_trgt(uint8_t cpu_targets) {
    uint8_t gic_targets = 0;
    for(int i = 0; i < GIC_MAX_TARGETS; i++) {
        if((1 << i) & cpu_targets) {
            gic_targets |= (1 << gic_cpu_map[i]);
        }
    }
    return gic_targets;
}

void gicd_set_trgt(uint64_t int_id, uint8_t cpu_targets)
{
    uint64_t reg_ind = GIC_TARGET_REG(int_id);
    uint64_t off = GIC_TARGET_OFF(int_id);
    uint32_t mask = BIT_MASK(off, GIC_TARGET_BITS);

    spin_lock(&gicd_lock);

    gicd.ITARGETSR[reg_ind] = (gicd.ITARGETSR[reg_ind] & ~mask) | 
        ((gic_translate_cpu_to_trgt(cpu_targets) << off) & mask);

    spin_unlock(&gicd_lock);
}

void gic_set_prio(uint64_t int_id, uint8_t prio)
{
    gicd_set_prio(int_id, prio);
}

uint64_t gic_get_prio(uint64_t int_id)
{
    return gicd_get_prio(int_id);
}

void gic_set_icfgr(uint64_t int_id, uint8_t cfg)
{
    gicd_set_icfgr(int_id, cfg);
}

bool gic_get_pend(uint64_t int_id)
{
    return gicd_get_pend(int_id);
}

void gic_set_act(uint64_t int_id, bool act)
{
    gicd_set_act(int_id, act);
}

bool gic_get_act(uint64_t int_id)
{
    return gicd_get_act(int_id);
}

void gic_set_enable(uint64_t int_id, bool en)
{
    gicd_set_enable(int_id, en);
}

void gic_set_pend(uint64_t int_id, bool pend)
{
    if (gic_is_sgi(int_id)) {
        uint64_t reg_ind = GICD_SGI_REG(int_id);
        uint64_t off = GICD_SGI_OFF(int_id);

        if (pend) {
            gicd.SPENDSGIR[reg_ind] = (1U) << (off + cpu.id);
        } else {
            gicd.CPENDSGIR[reg_ind] = BIT_MASK(off, 8);
        }
    } else {
        gicd_set_pend(int_id, pend);
    }
}
