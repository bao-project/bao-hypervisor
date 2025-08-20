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
    if (cpu_is_master()) {
        if (!DEFINED(MMIO_SLAVE_SIDE_PROT)) {
            mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, 0xF003D400, 0x800);
        }
        unsigned long* P14_0_DRVCFG = (unsigned long*)(PORT14 + 0x304);
        unsigned long* P14_1_DRVCFG = (unsigned long*)(PORT14 + 0x304 + 0x10);

        // UART PINS P14.1 Rx and P14.0 Tx
        *P14_0_DRVCFG = 0x21;
        *P14_1_DRVCFG = 0;

        if (!DEFINED(MMIO_SLAVE_SIDE_PROT)) {
            mem_unmap(&cpu()->as, 0xF003D400, 0x800, 0);
        }
    }
}

void platform_cpu_init(cpuid_t cpuid, paddr_t load_addr)
{
    for (size_t coreid = 0; coreid < platform.cpu_num; coreid++) {
        if (coreid == cpuid) {
            continue;
        }

        /* Enable access to system timer for all VMs */
        for (unsigned int i = 0; i < 8; i++) {
            uintptr_t cpu_base = 0xF8800000UL + (coreid * 0x40000UL);
            uintptr_t cpu_stm_sel_reg = cpu_base + CPUx_PROTSTMSE_OFFSET;
            uintptr_t cpu_stm_apu = cpu_base + CPUx_ACCENSTMCFG_OFFSET;

            *(unsigned long*)cpu_stm_sel_reg = (i << PROTSTMSE_SEL_OFFSET);

            apu_enable_access_all_cpus((struct PROT_ACCESSEN*)cpu_stm_apu);
        }

        csfr_cpu_pc_write(coreid, load_addr);
        csfr_cpu_bootcon_write(coreid, 0);
    }
}
