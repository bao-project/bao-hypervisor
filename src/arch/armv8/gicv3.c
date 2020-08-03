/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <arch/gic.h>
#include <cpu.h>
#include <mem.h>
#include <platform.h>
#include <interrupts.h>
#include <fences.h>

extern volatile gicd_t gicd;
volatile gicr_t *gicr;

static spinlock_t gicd_lock;
static spinlock_t gicr_lock;

uint64_t NUM_LRS;

uint64_t gich_num_lrs()
{
    return ((MRS(ICH_VTR_EL2) & ICH_VTR_MSK) >> ICH_VTR_OFF) + 1;
}

inline uint64_t gich_read_lr(size_t i)
{
    if (i >= NUM_LRS) {
        ERROR("gic: trying to read inexistent list register");
    }

    switch (i) {
        case 0: return MRS(ICH_LR0_EL2);
        case 1: return MRS(ICH_LR1_EL2);
        case 2: return MRS(ICH_LR2_EL2);
        case 3: return MRS(ICH_LR3_EL2);
        case 4: return MRS(ICH_LR4_EL2);
        case 5: return MRS(ICH_LR5_EL2);
        case 6: return MRS(ICH_LR6_EL2);
        case 7: return MRS(ICH_LR7_EL2);
        case 8: return MRS(ICH_LR8_EL2);
        case 9: return MRS(ICH_LR9_EL2);
        case 10: return MRS(ICH_LR10_EL2);
        case 11: return MRS(ICH_LR11_EL2);
        case 12: return MRS(ICH_LR12_EL2);
        case 13: return MRS(ICH_LR13_EL2);
        case 14: return MRS(ICH_LR14_EL2);
        case 15: return MRS(ICH_LR15_EL2);
        default: return 0;
    }
}

inline void gich_write_lr(size_t i, uint64_t val)
{
    if (i >= NUM_LRS) {
        ERROR("gic: trying to write inexistent list register");
    }

    switch (i) {
        case 0: MSR(ICH_LR0_EL2, val);   break;        
        case 1: MSR(ICH_LR1_EL2, val);   break;         
        case 2: MSR(ICH_LR2_EL2, val);   break;         
        case 3: MSR(ICH_LR3_EL2, val);   break;         
        case 4: MSR(ICH_LR4_EL2, val);   break;         
        case 5: MSR(ICH_LR5_EL2, val);   break;         
        case 6: MSR(ICH_LR6_EL2, val);   break;         
        case 7: MSR(ICH_LR7_EL2, val);   break;         
        case 8: MSR(ICH_LR8_EL2, val);   break;         
        case 9: MSR(ICH_LR9_EL2, val);   break;         
        case 10: MSR(ICH_LR10_EL2, val); break;           
        case 11: MSR(ICH_LR11_EL2, val); break;           
        case 12: MSR(ICH_LR12_EL2, val); break;           
        case 13: MSR(ICH_LR13_EL2, val); break;           
        case 14: MSR(ICH_LR14_EL2, val); break;           
        case 15: MSR(ICH_LR15_EL2, val); break;
    }
}

uint32_t gich_get_hcr()
{
    return MRS(ICH_HCR_EL2);
}

void gich_set_hcr(uint32_t hcr)
{
    MSR(ICH_HCR_EL2, hcr);
}

uint32_t gich_get_misr()
{
    return MRS(ICH_MISR_EL2);
}

uint64_t gich_get_eisr()
{
    return MRS(ICH_EISR_EL2);
}

uint64_t gich_get_elrsr()
{
    return MRS(ICH_ELRSR_EL2);
}

static inline void gicc_init()
{
    /* Enable system register interface i*/
    MSR(ICC_SRE_EL2, ICC_SRE_SRE_BIT);
    ISB();

    for (int i = 0; i < gich_num_lrs(); i++) {
        gich_write_lr(i, 0);
    }

    MSR(ICC_PMR_EL1, GIC_LOWEST_PRIO);
    MSR(ICC_BPR1_EL1, 0x0);
    MSR(ICC_CTLR_EL1, ICC_CTLR_EOIMode_BIT);
    MSR(ICH_HCR_EL2, MRS(ICH_HCR_EL2) | ICH_HCR_LRENPIE_BIT);
    MSR(ICC_IGRPEN1_EL1, ICC_IGRPEN_EL1_ENB_BIT);
}

static inline void gicr_init()
{
    gicr[cpu.id].ICENABLER0 = -1;
    gicr[cpu.id].ICPENDR0 = -1;
    gicr[cpu.id].ICACTIVER0 = -1;

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicr[cpu.id].IPRIORITYR[i] = -1;
    }
}

void gicc_save_state(gicc_state_t *state)
{
    state->PMR = MRS(ICC_PMR_EL1);
    state->BPR = MRS(ICC_BPR1_EL1);
    state->priv_ISENABLER = gicr[cpu.id].ISENABLER0;

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        state->priv_IPRIORITYR[i] = gicr[cpu.id].IPRIORITYR[i];
    }

    state->HCR = MRS(ICH_HCR_EL2);
    for (int i = 0; i < gich_num_lrs(); i++) {
        state->LR[i] = gich_read_lr(i);
    }
}

void gicc_restore_state(gicc_state_t *state)
{
    MSR(ICC_SRE_EL2, ICC_SRE_SRE_BIT);
    MSR(ICC_CTLR_EL1, ICC_CTLR_EOIMode_BIT);
    MSR(ICC_IGRPEN1_EL1, ICC_IGRPEN_EL1_ENB_BIT);
    MSR(ICC_PMR_EL1, state->PMR);
    MSR(ICC_BPR1_EL1, state->BPR);
    gicr[cpu.id].ISENABLER0 = state->priv_ISENABLER;

    for (int i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicr[cpu.id].IPRIORITYR[i] = state->priv_IPRIORITYR[i];
    }

    MSR(ICH_HCR_EL2, state->HCR);
    for (int i = 0; i < gich_num_lrs(); i++) {
        gich_write_lr(i, state->LR[i]);
    }
}

void gic_cpu_init()
{
    gicr_init();
    gicc_init();
}

void gic_map_mmio()
{
    mem_map_dev(&cpu.as, (void *)&gicd, platform.arch.gic.gicd_addr,
                NUM_PAGES(sizeof(gicd)));
    size_t gicr_size = NUM_PAGES(sizeof(gicr_t)) * platform.cpu_num;
    gicr = (gicr_t *)mem_alloc_vpage(&cpu.as, SEC_HYP_GLOBAL, NULL, gicr_size);
    mem_map_dev(&cpu.as, (void *)gicr, platform.arch.gic.gicr_addr, gicr_size);
}

uint32_t gicc_iar() {
    return MRS(ICC_IAR1_EL1);
}

void gicc_eoir(uint32_t eoir) {
    MSR(ICC_EOIR1_EL1, eoir);
}

void gicc_dir(uint32_t dir) {
    MSR(ICC_DIR_EL1, dir);
}

void gicr_set_prio(uint64_t int_id, uint8_t prio, uint32_t gicr_id)
{
    uint64_t reg_ind = GIC_PRIO_REG(int_id);
    uint64_t off = GIC_PRIO_OFF(int_id);
    uint64_t mask = BIT_MASK(off, GIC_PRIO_BITS);

    spin_lock(&gicr_lock);

    gicr[gicr_id].IPRIORITYR[reg_ind] =
        (gicr[gicr_id].IPRIORITYR[reg_ind] & ~mask) | ((prio << off) & mask);

    spin_unlock(&gicr_lock);
}

uint64_t gicr_get_prio(uint64_t int_id, uint32_t gicr_id)
{
    uint64_t reg_ind = GIC_PRIO_REG(int_id);
    uint64_t off = GIC_PRIO_OFF(int_id);

    spin_lock(&gicr_lock);

    uint64_t prio =
        gicr[gicr_id].IPRIORITYR[reg_ind] >> off & BIT_MASK(off, GIC_PRIO_BITS);

    spin_unlock(&gicr_lock);

    return prio;
}

void gicr_set_icfgr(uint64_t int_id, uint8_t cfg, uint32_t gicr_id)
{
    uint64_t reg_ind = (int_id * GIC_CONFIG_BITS) / (sizeof(uint32_t) * 8);
    uint64_t off = (int_id * GIC_CONFIG_BITS) % (sizeof(uint32_t) * 8);
    uint64_t mask = ((1U << GIC_CONFIG_BITS) - 1) << off;

    spin_lock(&gicr_lock);

    if (reg_ind == 0) {
        gicr[gicr_id].ICFGR0 =
            (gicr[gicr_id].ICFGR0 & ~mask) | ((cfg << off) & mask);
    } else {
        gicr[gicr_id].ICFGR1 =
            (gicr[gicr_id].ICFGR1 & ~mask) | ((cfg << off) & mask);
    }

    spin_unlock(&gicr_lock);
}

void gicr_set_pend(uint64_t int_id, bool pend, uint32_t gicr_id)
{
    spin_lock(&gicr_lock);
    if (pend) {
        gicr[gicr_id].ISPENDR0 = (1U) << (int_id);
    } else {
        gicr[gicr_id].ICPENDR0 = (1U) << (int_id);
    }
    spin_unlock(&gicr_lock);
}

bool gicr_get_pend(uint64_t int_id, uint32_t gicr_id)
{
    if (gic_is_priv(int_id)) {
        return !!(gicr[gicr_id].ISPENDR0 & GIC_INT_MASK(int_id));
    } else {
        return false;
    }
}

void gicr_set_act(uint64_t int_id, bool act, uint32_t gicr_id)
{
    spin_lock(&gicr_lock);

    if (act) {
        gicr[gicr_id].ISACTIVER0 = GIC_INT_MASK(int_id);
    } else {
        gicr[gicr_id].ICACTIVER0 = GIC_INT_MASK(int_id);
    }

    spin_unlock(&gicr_lock);
}

bool gicr_get_act(uint64_t int_id, uint32_t gicr_id)
{
    if (gic_is_priv(int_id)) {
        return !!(gicr[gicr_id].ISACTIVER0 & GIC_INT_MASK(int_id));
    } else {
        return false;
    }
}

void gicr_set_enable(uint64_t int_id, bool en, uint32_t gicr_id)
{
    uint64_t bit = GIC_INT_MASK(int_id);

    spin_lock(&gicr_lock);
    if (en)
        gicr[gicr_id].ISENABLER0 = bit;
    else
        gicr[gicr_id].ICENABLER0 = bit;
    spin_unlock(&gicr_lock);
}

void gicd_set_route(uint64_t int_id, uint64_t route)
{
    if (gic_is_priv(int_id)) return;

    spin_lock(&gicd_lock);

    gicd.IROUTER[int_id] = route & GICD_IROUTER_AFF_MSK;

    spin_unlock(&gicd_lock);
}

void gic_send_sgi(uint64_t cpu_target, uint64_t sgi_num)
{
    if (sgi_num < GIC_MAX_SGIS) {
        uint64_t mpidr = cpu_id_to_mpidr(cpu_target) & MPIDR_AFF_MSK;
        /* We only support two affinity levels */
        uint64_t sgi = (MPIDR_AFF_LVL(mpidr, 1) << ICC_SGIR_AFF1_OFFSET) |
                       (1UL << MPIDR_AFF_LVL(mpidr, 0)) |
                       (sgi_num << ICC_SGIR_SGIINTID_OFF);             
        MSR(ICC_SGI1R_EL1, sgi);
    }
}

void gic_set_prio(uint64_t int_id, uint8_t prio)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_prio(int_id, prio);
    } else {
        gicr_set_prio(int_id, prio, cpu.id);
    }
}

uint64_t gic_get_prio(uint64_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_prio(int_id);
    } else {
        return gicr_get_prio(int_id, cpu.id);
    }
}

void gic_set_icfgr(uint64_t int_id, uint8_t cfg)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_icfgr(int_id, cfg);
    } else {
        gicr_set_icfgr(int_id, cfg, cpu.id);
    }
}

void gic_set_pend(uint64_t int_id, bool pend)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_pend(int_id, pend);
    } else {
        gicr_set_pend(int_id, pend, cpu.id);
    }
}

bool gic_get_pend(uint64_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_pend(int_id);
    } else {
        return gicr_get_pend(int_id, cpu.id);
    }
}

void gic_set_act(uint64_t int_id, bool act)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_act(int_id, act);
    } else {
        gicr_set_act(int_id, act, cpu.id);
    }
}

bool gic_get_act(uint64_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_act(int_id);
    } else {
        return gicr_get_act(int_id, cpu.id);
    }
}

void gic_set_enable(uint64_t int_id, bool en)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_enable(int_id, en);
    } else {
        gicr_set_enable(int_id, en, cpu.id);
    }
}
