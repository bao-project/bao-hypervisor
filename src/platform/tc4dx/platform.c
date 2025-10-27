/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

#include <arch/csfrs.h>
#include <arch/prot.h>
#include <cpu.h>

#define PORT14 0xF003D800UL

void platform_default_init(void)
{
    mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 0xF003D400, 0x800);

    unsigned long* P14_0_DRVCFG = (unsigned long*)(PORT14 + 0x304);
    unsigned long* P14_1_DRVCFG = (unsigned long*)(PORT14 + 0x304 + 0x10);

    // UART PINS P14.1 Rx and P14.0 Tx
    *P14_0_DRVCFG = 0x21;
    *P14_1_DRVCFG = 0;

    struct PROT_ACCESSEN* gpio_accessen = (struct PROT_ACCESSEN*)(PORT14 + 0x90);

    for (unsigned long i = 0; i < platform.cpu_num; i++) {
        apu_enable_access_cpu(gpio_accessen, i);
    }

    mem_unmap(&cpu()->as, 0xF003D400, 0x800, 0);
}

void platform_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    for (size_t coreid = 0; coreid < platform.cpu_num; coreid++) {
        if (coreid == cpuid) {
            continue;
        }

        csfr_cpu_pc_write(coreid, load_addr);
        csfr_cpu_bootcon_write(coreid, 0);
    }
}
