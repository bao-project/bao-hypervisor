/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <earlycon.h>
#include <arch/sbi.h>
#include <cpu.h>

static bool dbcn_available;

void earlycon_init(cpuid_t cpu_id)
{
    if (cpu_id != CPU_MASTER) {
        return;
    }

    bool available = false;
    struct sbiret ret = sbi_get_spec_version();
    /* SBI v0.1 has no BASE probing. Leave early output disabled if BASE
     * is unavailable; Bao requires SBI v0.2 or later. */
    if (ret.error == SBI_SUCCESS && ret.value >= 2) {
        ret = sbi_probe_extension(SBI_EXTID_DBCN);
        if (ret.error == SBI_SUCCESS && ret.value != 0) {
            available = true;
        }
    }

    /* Only this scalar is shared: secondary CPUs and fault handlers never wait. */
    __atomic_store_n(&dbcn_available, available, __ATOMIC_RELAXED);
}

/* Firmware output is independent of the platform's normal UART driver. */
void earlycon_putchar(char c)
{
    if (__atomic_load_n(&dbcn_available, __ATOMIC_RELAXED)) {
        /* Blocking firmware call. Drop errors without retries or logging. */
        (void)sbi_debug_console_write_byte((uint8_t)c);
    }
}
