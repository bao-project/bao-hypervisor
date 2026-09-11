/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <timer.h>
#include <spinlock.h>
#include "kao.h"

#define CPU_BOOT_WAIT_TIME TIME_MS(1000)

static volatile bool cpu_boot_status[NUM_CPUS] = { false };
static spinlock_t boot_status_lock = SPINLOCK_INITVAL;

static void vm_boot(void)
{
    if (cpu_is_master()) {
        KAO_PASS("System booted successfully!\n");
    }
}
KAO_TEST(00_00_00_00, vm_boot, TAGS(integration, boot, smoke), ENVS(baremetal),
    "Check that baremetal guest boots successfully");

static void cpu_boot(void)
{
    int cpu_id = get_cpuid();
    spin_lock(&boot_status_lock);
    cpu_boot_status[cpu_id] = true;
    spin_unlock(&boot_status_lock);

    if (cpu_is_master()) {
        timer_wait(CPU_BOOT_WAIT_TIME);
        for (int i = 0; i < NUM_CPUS; i++) {
            if (!cpu_boot_status[i]) {
                KAO_FAIL("CPUs did not boot successfully!\n");
                return;
            }
        }
        KAO_PASS("All CPUs booted successfully!\n");
    }
}
KAO_TEST(00_00_00_01, cpu_boot, TAGS(integration, boot, smp), ENVS(baremetal),
    "Check that all CPUs on the baremetal boot successfully");
