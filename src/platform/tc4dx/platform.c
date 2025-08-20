/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

#include <arch/csfrs.h>
#include <arch/prot.h>
#include <cpu.h>
#include <fences.h>

#define PORT14_BASE              0xF003D800UL
#define PORT_DRVCFG_OFFSET       0x304UL
#define PORT_PIN_ADDR(addr, pin) (unsigned long*)((addr) + PORT_DRVCFG_OFFSET + ((pin) * 0x10))
#define PORT_DRVCFG_MODE_ALT02PU 0x2UL
#define PORT_DRVCFG_MODE_OFFSET  0x4UL
#define PORT_DRVCFG_DIR_IN       0x1UL
#define PORT_DRVCFG_DIR_OUT      0UL

void platform_default_init(void)
{
    if (cpu_is_master()) {
        unsigned long* P14_0_DRVCFG = PORT_PIN_ADDR(PORT14_BASE, 0);
        unsigned long* P14_1_DRVCFG = PORT_PIN_ADDR(PORT14_BASE, 1);

        // UART PINS P14.1 Rx and P14.0 Tx
        *P14_0_DRVCFG = PORT_DRVCFG_MODE_ALT02PU << PORT_DRVCFG_MODE_OFFSET | PORT_DRVCFG_DIR_IN;
        *P14_1_DRVCFG = PORT_DRVCFG_DIR_OUT;
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
        csfr_cpu_bootcon_write(coreid, BOOTCON_BHALT_START);
        fence_sync();
    }
}
