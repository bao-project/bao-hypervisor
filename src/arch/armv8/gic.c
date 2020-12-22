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
#include <interrupts.h>
#include <cpu.h>
#include <spinlock.h>
#include <platform.h>

volatile gicd_t gicd __attribute__((section(".devices"), aligned(PAGE_SIZE)));
spinlock_t gicd_lock;

void gicd_init()
{
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
    for (int i = GIC_NUM_PRIO_REGS(GIC_CPU_PRIV);
         i < GIC_NUM_PRIO_REGS(int_num); i++) {
        gicd.IPRIORITYR[i] = -1;
    }

    if (GIC_VERSION == GICV2) {
        /* No CPU targets for any interrupt by default */
        for (int i = GIC_NUM_TARGET_REGS(GIC_CPU_PRIV);
             i < GIC_NUM_TARGET_REGS(int_num); i++) {
            gicd.ITARGETSR[i] = 0;
        }

        /* Enable distributor */
        gicd.CTLR |= GICD_CTLR_EN_BIT;

    } else {
        for (int i = GIC_CPU_PRIV; i < GIC_MAX_INTERUPTS; i++) {
            gicd.IROUTER[i] = GICD_IROUTER_INV;
        }

        /* Enable distributor and affinity routing */
        gicd.CTLR |= GICD_CTLR_ARE_NS_BIT | GICD_CTLR_ENA_BIT;
    }

    /* ICFGR are platform dependent, lets leave them as is */

    /* No need to setup gicd.NSACR as all interrupts are  setup to group 1 */

    interrupts_reserve(platform.arch.gic.maintenance_id,
                       gic_maintenance_handler);
}

void gic_map_mmio();

void gic_init()
{
    if (cpu.id == CPU_MASTER) {
        gic_map_mmio();
        gicd_init();
        NUM_LRS = gich_num_lrs();
    }

    cpu_sync_barrier(&cpu_glb_sync);

    gic_cpu_init();
}

void gic_handle()
{
    uint64_t ack = gicc_iar();
    uint64_t id = bit_extract(ack, GICC_IAR_ID_OFF, GICC_IAR_ID_LEN);

    if (id < GIC_FIRST_SPECIAL_INTID) {
        enum irq_res res = interrupts_handle(id);
        gicc_eoir(ack);
        if (res == HANDLED_BY_HYP) gicc_dir(ack);
    }
}

uint64_t gicd_get_prio(uint64_t int_id)
{
    uint64_t reg_ind = GIC_PRIO_REG(int_id);
    uint64_t off = GIC_PRIO_OFF(int_id);

    uint64_t prio =
        gicd.IPRIORITYR[reg_ind] >> off & BIT_MASK(off, GIC_PRIO_BITS);

    return prio;
}

void gicd_set_icfgr(uint64_t int_id, uint8_t cfg)
{
    uint64_t reg_ind = (int_id * GIC_CONFIG_BITS) / (sizeof(uint32_t) * 8);
    uint64_t off = (int_id * GIC_CONFIG_BITS) % (sizeof(uint32_t) * 8);
    uint64_t mask = ((1U << GIC_CONFIG_BITS) - 1) << off;

    spin_lock(&gicd_lock);

    gicd.ICFGR[reg_ind] = (gicd.ICFGR[reg_ind] & ~mask) | ((cfg << off) & mask);

    spin_unlock(&gicd_lock);
}

void gicd_set_prio(uint64_t int_id, uint8_t prio)
{
    uint64_t reg_ind = GIC_PRIO_REG(int_id);
    uint64_t off = GIC_PRIO_OFF(int_id);
    uint64_t mask = BIT_MASK(off, GIC_PRIO_BITS);

    spin_lock(&gicd_lock);

    gicd.IPRIORITYR[reg_ind] =
        (gicd.IPRIORITYR[reg_ind] & ~mask) | ((prio << off) & mask);

    spin_unlock(&gicd_lock);
}

void gicd_set_pend(uint64_t int_id, bool pend)
{
    uint64_t reg_ind = GIC_INT_REG(int_id);
    if (pend) {
        gicd.ISPENDR[reg_ind] = GIC_INT_MASK(int_id);
    } else {
        gicd.ICPENDR[reg_ind] = GIC_INT_MASK(int_id);
    }
}

bool gicd_get_pend(uint64_t int_id)
{
    return (gicd.ISPENDR[GIC_INT_REG(int_id)] & GIC_INT_MASK(int_id)) != 0;
}

void gicd_set_act(uint64_t int_id, bool act)
{
    uint64_t reg_ind = GIC_INT_REG(int_id);

    if (act) {
        gicd.ISACTIVER[reg_ind] = GIC_INT_MASK(int_id);
    } else {
        gicd.ICACTIVER[reg_ind] = GIC_INT_MASK(int_id);
    }
}

bool gicd_get_act(uint64_t int_id)
{
    return (gicd.ISACTIVER[GIC_INT_REG(int_id)] & GIC_INT_MASK(int_id)) != 0;
}

void gicd_set_enable(uint64_t int_id, bool en)
{
    uint64_t reg_ind = GIC_INT_REG(int_id);
    uint64_t bit = GIC_INT_MASK(int_id);

    if (en) {
        gicd.ISENABLER[reg_ind] = bit;
    } else {
        gicd.ICENABLER[reg_ind] = bit;
    }
}
