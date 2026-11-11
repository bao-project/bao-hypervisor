/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <timer.h>
#include <spinlock.h>
#include "kao.h"

#define CPU_BOOT_WAIT_TIME TIME_MS(1000)

static volatile bool gen_boot_all_cpus_status[NUM_CPUS] = { false };
static spinlock_t boot_status_lock = SPINLOCK_INITVAL;

static void gen_boot_vm(void)
{
    if (cpu_is_master()) {
        KAO_PASS("System booted successfully!\n");
    }
}
KAO_TEST(00_00_00_00, gen_boot_vm, TAGS(integration, boot, smoke), ENVS(baremetal),
    "Check that baremetal guest boots successfully");

static void gen_boot_all_cpus(void)
{
    int cpu_id = get_cpuid();
    spin_lock(&boot_status_lock);
    gen_boot_all_cpus_status[cpu_id] = true;
    spin_unlock(&boot_status_lock);

    if (cpu_is_master()) {
        timer_wait(CPU_BOOT_WAIT_TIME);
        for (int i = 0; i < NUM_CPUS; i++) {
            if (!gen_boot_all_cpus_status[i]) {
                KAO_FAIL("CPUs did not boot successfully!\n");
                return;
            }
        }
        KAO_PASS("All CPUs booted successfully!\n");
    }
}
KAO_TEST(00_00_00_01, gen_boot_all_cpus, TAGS(integration, boot, smp), ENVS(baremetal),
    "Check that all CPUs on the baremetal boot successfully");
