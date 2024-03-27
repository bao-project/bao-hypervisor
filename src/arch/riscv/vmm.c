/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <arch/csrs.h>

void vmm_arch_init()
{
    /**
     * At this point, we should make sure misa's H bit is set (at least by reading it). However,
     * current SBI does not allow us to even read it. So we assume it is set - if not, the first
     * acess to an hypervisor register will set an illegal inst fault.
     */

    /**
     * Delegate all interrupts and exceptions not meant to be dealt by the hypervisor
     */

    csrs_hideleg_write(HIDELEG_VSSI | HIDELEG_VSTI | HIDELEG_VSEI);
    csrs_hedeleg_write(HEDELEG_ECU | HEDELEG_IPF | HEDELEG_LPF | HEDELEG_SPF);

    /**
     * Enable and sanity check presence of Sstc extension if the hypervisor was
     * configured to use it (via the CPU_EXT_SSTC macro). Otherwise, make sure
     * it is disabled.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_SSTC)) {
        csrs_henvcfg_set(HENVCFG_STCE);
        bool sstc_present = (csrs_henvcfg_read() & HENVCFG_STCE) != 0;
        if (cpu_is_master() && !sstc_present) {
            ERROR("Platform configured to use Sstc extension, but extension not present.");
        }
        // Set stimecmp to infinity in case we enable the stimer interrupt somewhere else
        // and fail to set the timer to a point in the future.
        csrs_stimecmp_write(~0U);
    } else {
        csrs_henvcfg_clear(HENVCFG_STCE);
    }

    /**
     * TODO: consider delegating other exceptions e.g. breakpoint or ins misaligned
     */
}
