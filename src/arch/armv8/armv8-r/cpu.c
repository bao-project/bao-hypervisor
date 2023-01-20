/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <arch/gic.h>

void cpu_arch_profile_init(cpuid_t cpuid, paddr_t load_addr) {

}

void cpu_arch_profile_idle() {
    asm volatile("wfi");
}
