/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/nvic.h>
#include "arch/interrupts.h"
#include <interrupts.h>
#include <cpu.h>
#include <fences.h>
#include <platform_defs.h>
#include <platform.h>

#include <vm.h>

volatile struct nvic_int_hw* nvic_int;
volatile struct nvic_src_hw* nvic_src;

BITMAP_ALLOC(valid, NVIC_MAX_INTERRUPTS);

void nvic_init_ipi(void) { }

void nvic_init(void) { }

void nvic_cpu_init(void)
{
    /* Nothing to do */
}

void nvic_set_enbl(irqid_t int_id, bool en)
{
    UNUSED_ARG(int_id);
    UNUSED_ARG(en);
}

bool nvic_get_enbl(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return false;
}

void nvic_set_prio(irqid_t int_id, uint32_t prio)
{
    UNUSED_ARG(int_id);
    UNUSED_ARG(prio);
}

uint32_t nvic_get_prio(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return 0;
}

bool nvic_get_pend(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return false;
}

bool nvic_set_pend(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return false;
}

bool nvic_clr_pend(irqid_t int_id)
{
    UNUSED_ARG(int_id);
    return false;
}

void nvic_handle(void) { }

void nvic_send_ipi(cpuid_t target_cpu)
{
    UNUSED_ARG(target_cpu);
}

void nvic_config_irq(irqid_t int_id, bool en)
{
    UNUSED_ARG(int_id);
    UNUSED_ARG(en);
}

void nvic_assign_int_to_vm(struct vm* vm, irqid_t id)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(id);
}

void nvic_reset_cpu_int_ctrl_access(unsigned long icuid)
{
    UNUSED_ARG(icuid);
}
void nvic_reset_cpu_int_cfg_access(unsigned long icuid)
{
    UNUSED_ARG(icuid);
}

void nvic_enable_vm_int_ctrl_access(unsigned long icuid, unsigned long vmid)
{
    UNUSED_ARG(icuid);
    UNUSED_ARG(vmid);
}

void nvic_enable_vm_int_cfg_access(unsigned long icuid, unsigned long vmid)
{
    UNUSED_ARG(icuid);
    UNUSED_ARG(vmid);
}

void nvic_assign_icu_to_vm(unsigned long id, struct vm* vm)
{
    UNUSED_ARG(id);
    UNUSED_ARG(vm);
}

bool nvic_id_valid(unsigned long id)
{
    UNUSED_ARG(id);
    return false;
}
