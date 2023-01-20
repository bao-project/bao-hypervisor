/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/gic.h>
#include <arch/gicv3.h>

#include <cpu.h>
#include <mem.h>
#include <platform.h>
#include <interrupts.h>
#include <fences.h>

extern volatile struct gicd_hw *gicd;
volatile struct gicr_hw *gicr;

static spinlock_t gicd_lock = SPINLOCK_INITVAL;
static spinlock_t gicr_lock = SPINLOCK_INITVAL;

size_t NUM_LRS;

size_t gich_num_lrs()
{
    return ((sysreg_ich_vtr_el2_read() & ICH_VTR_MSK) >> ICH_VTR_OFF) + 1;
}

static inline void gicc_init()
{
    for (size_t i = 0; i < gich_num_lrs(); i++) {
        gich_write_lr(i, 0);
    }

    sysreg_icc_pmr_el1_write(GIC_LOWEST_PRIO);
    sysreg_icc_bpr1_el1_write(0x0);
    sysreg_icc_ctlr_el1_write(ICC_CTLR_EOIMode_BIT);
    sysreg_ich_hcr_el2_write(sysreg_ich_hcr_el2_read() | ICH_HCR_LRENPIE_BIT);
    sysreg_icc_igrpen1_el1_write(ICC_IGRPEN_EL1_ENB_BIT);
}

static inline void gicr_init()
{
    gicr[cpu()->id].WAKER &= ~GICR_WAKER_ProcessorSleep_BIT;
    while(gicr[cpu()->id].WAKER & GICR_WAKER_ChildrenASleep_BIT);

    gicr[cpu()->id].IGROUPR0 = -1;
    gicr[cpu()->id].ICENABLER0 = -1;
    gicr[cpu()->id].ICPENDR0 = -1;
    gicr[cpu()->id].ICACTIVER0 = -1;

    for (size_t i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicr[cpu()->id].IPRIORITYR[i] = -1;
    }
}

void gicc_save_state(struct gicc_state *state)
{
    state->PMR = sysreg_icc_pmr_el1_read();
    state->BPR = sysreg_icc_bpr1_el1_read();
    state->priv_ISENABLER = gicr[cpu()->id].ISENABLER0;

    for (size_t i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        state->priv_IPRIORITYR[i] = gicr[cpu()->id].IPRIORITYR[i];
    }

    state->HCR = sysreg_ich_hcr_el2_read();
    for (size_t i = 0; i < gich_num_lrs(); i++) {
        state->LR[i] = gich_read_lr(i);
    }
}

void gicc_restore_state(struct gicc_state *state)
{
    sysreg_icc_sre_el2_write(ICC_SRE_SRE_BIT);
    sysreg_icc_ctlr_el1_write(ICC_CTLR_EOIMode_BIT);
    sysreg_icc_igrpen1_el1_write(ICC_IGRPEN_EL1_ENB_BIT);
    sysreg_icc_pmr_el1_write(state->PMR);
    sysreg_icc_bpr1_el1_write(state->BPR);
    gicr[cpu()->id].ISENABLER0 = state->priv_ISENABLER;

    for (size_t i = 0; i < GIC_NUM_PRIO_REGS(GIC_CPU_PRIV); i++) {
        gicr[cpu()->id].IPRIORITYR[i] = state->priv_IPRIORITYR[i];
    }

    sysreg_ich_hcr_el2_write(state->HCR);
    for (size_t i = 0; i < gich_num_lrs(); i++) {
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
    gicd = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 
        platform.arch.gic.gicd_addr, NUM_PAGES(sizeof(struct gicd_hw)));
    gicr = (void*) mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 
       platform.arch.gic.gicr_addr, 
       NUM_PAGES(sizeof(struct gicr_hw) * PLAT_CPU_NUM));
}

void gicr_set_prio(irqid_t int_id, uint8_t prio, cpuid_t gicr_id)
{
    size_t reg_ind = GIC_PRIO_REG(int_id);
    size_t off = GIC_PRIO_OFF(int_id);
    uint32_t mask = BIT32_MASK(off, GIC_PRIO_BITS);

    spin_lock(&gicr_lock);

    gicr[gicr_id].IPRIORITYR[reg_ind] =
        (gicr[gicr_id].IPRIORITYR[reg_ind] & ~mask) | ((prio << off) & mask);

    spin_unlock(&gicr_lock);
}

uint8_t gicr_get_prio(irqid_t int_id, cpuid_t gicr_id)
{
    size_t reg_ind = GIC_PRIO_REG(int_id);
    size_t off = GIC_PRIO_OFF(int_id);

    spin_lock(&gicr_lock);

    uint8_t prio =
        gicr[gicr_id].IPRIORITYR[reg_ind] >> off & BIT32_MASK(off, GIC_PRIO_BITS);

    spin_unlock(&gicr_lock);

    return prio;
}

void gicr_set_icfgr(irqid_t int_id, uint8_t cfg, cpuid_t gicr_id)
{
    size_t reg_ind = (int_id * GIC_CONFIG_BITS) / (sizeof(uint32_t) * 8);
    size_t off = (int_id * GIC_CONFIG_BITS) % (sizeof(uint32_t) * 8);
    uint32_t mask = ((1U << GIC_CONFIG_BITS) - 1) << off;

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

void gicr_set_pend(irqid_t int_id, bool pend, cpuid_t gicr_id)
{
    spin_lock(&gicr_lock);
    if (pend) {
        gicr[gicr_id].ISPENDR0 = (1U) << (int_id);
    } else {
        gicr[gicr_id].ICPENDR0 = (1U) << (int_id);
    }
    spin_unlock(&gicr_lock);
}

bool gicr_get_pend(irqid_t int_id, cpuid_t gicr_id)
{
    if (gic_is_priv(int_id)) {
        return !!(gicr[gicr_id].ISPENDR0 & GIC_INT_MASK(int_id));
    } else {
        return false;
    }
}

void gicr_set_act(irqid_t int_id, bool act, cpuid_t gicr_id)
{
    spin_lock(&gicr_lock);

    if (act) {
        gicr[gicr_id].ISACTIVER0 = GIC_INT_MASK(int_id);
    } else {
        gicr[gicr_id].ICACTIVER0 = GIC_INT_MASK(int_id);
    }

    spin_unlock(&gicr_lock);
}

bool gicr_get_act(irqid_t int_id, cpuid_t gicr_id)
{
    if (gic_is_priv(int_id)) {
        return !!(gicr[gicr_id].ISACTIVER0 & GIC_INT_MASK(int_id));
    } else {
        return false;
    }
}

void gicr_set_enable(irqid_t int_id, bool en, cpuid_t gicr_id)
{
    uint32_t bit = GIC_INT_MASK(int_id);

    spin_lock(&gicr_lock);
    if (en)
        gicr[gicr_id].ISENABLER0 = bit;
    else
        gicr[gicr_id].ICENABLER0 = bit;
    spin_unlock(&gicr_lock);
}

void gicd_set_route(irqid_t int_id, unsigned long route)
{
    if (gic_is_priv(int_id)) return;

    spin_lock(&gicd_lock);

    gicd->IROUTER[int_id] = route & GICD_IROUTER_AFF_MSK;

    spin_unlock(&gicd_lock);
}

void gic_send_sgi(cpuid_t cpu_target, irqid_t sgi_num)
{
    if (sgi_num < GIC_MAX_SGIS) {
        unsigned long mpidr = cpu_id_to_mpidr(cpu_target) & MPIDR_AFF_MSK;
        /* We only support two affinity levels */
        uint64_t sgi = (MPIDR_AFF_LVL(mpidr, 1) << ICC_SGIR_AFF1_OFFSET) |
                       (1UL << MPIDR_AFF_LVL(mpidr, 0)) |
                       (sgi_num << ICC_SGIR_SGIINTID_OFF);             
        sysreg_icc_sgi1r_el1_write(sgi);
    }
}

void gic_set_prio(irqid_t int_id, uint8_t prio)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_prio(int_id, prio);
    } else {
        gicr_set_prio(int_id, prio, cpu()->id);
    }
}

uint8_t gic_get_prio(irqid_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_prio(int_id);
    } else {
        return gicr_get_prio(int_id, cpu()->id);
    }
}

void gic_set_icfgr(irqid_t int_id, uint8_t cfg)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_icfgr(int_id, cfg);
    } else {
        gicr_set_icfgr(int_id, cfg, cpu()->id);
    }
}

void gic_set_pend(irqid_t int_id, bool pend)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_pend(int_id, pend);
    } else {
        gicr_set_pend(int_id, pend, cpu()->id);
    }
}

bool gic_get_pend(irqid_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_pend(int_id);
    } else {
        return gicr_get_pend(int_id, cpu()->id);
    }
}

void gic_set_act(irqid_t int_id, bool act)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_act(int_id, act);
    } else {
        gicr_set_act(int_id, act, cpu()->id);
    }
}

bool gic_get_act(irqid_t int_id)
{
    if (!gic_is_priv(int_id)) {
        return gicd_get_act(int_id);
    } else {
        return gicr_get_act(int_id, cpu()->id);
    }
}

void gic_set_enable(irqid_t int_id, bool en)
{
    if (!gic_is_priv(int_id)) {
        gicd_set_enable(int_id, en);
    } else {
        gicr_set_enable(int_id, en, cpu()->id);
    }
}
