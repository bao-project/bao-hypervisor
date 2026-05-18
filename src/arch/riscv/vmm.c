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
     * Start from a clean slate for the entire HENVCFG CSR
     * to avoid unintended side effects from any non-zero default bits
     */
    csrs_henvcfg_write(0);

    /**
     * Enable and sanity check presence of Sstc extension if the hypervisor was
     * configured to use it (via the CPU_EXT_SSTC macro). Otherwise, make sure
     * it is disabled.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_SSTC)) {
        csrs_henvcfg_set(HENVCFG_STCE);
        bool sstc_present = (csrs_henvcfg_read() & HENVCFG_STCE) != 0;
        if (cpu_is_master() && !sstc_present) {
            ERROR("Platform configured to use Sstc extension, but extension not present.\n");
        }
        // Set stimecmp to infinity in case we enable the stimer interrupt somewhere else
        // and fail to set the timer to a point in the future.
        csrs_stimecmp_write(~0U);
    }

    /**
     * Enable and sanity check the Zicboz extension if the hypervisor was
     * configured to use it (via the CPU_EXT_ZICBOZ macro). Otherwise, leave
     * the corresponding henvcfg bit cleared.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_ZICBOZ)) {
        csrs_henvcfg_set(HENVCFG_CBZE);
        bool zicboz_present = (csrs_henvcfg_read() & HENVCFG_CBZE) != 0;
        if (cpu_is_master() && !zicboz_present) {
            ERROR("Platform configured to use Zicboz extensions, but extension not present.\r\n");
        }
    }

    /**
     * Enable and sanity check the Zicbom extension if the hypervisor was
     * configured to use it (via the CPU_EXT_ZICBOM macro). Otherwise, leave
     * the corresponding henvcfg bits cleared.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_ZICBOM)) {
        csrs_henvcfg_set(HENVCFG_CBCFE | HENVCFG_CBIE_FLUSH);
        bool zicbom_present = (csrs_henvcfg_read() & (HENVCFG_CBCFE | HENVCFG_CBIE_FLUSH)) != 0;
        if (cpu_is_master() && !zicbom_present) {
            ERROR("Platform configured to use ZICBOM extensions, but extension not present.\r\n");
        }
    }

#if CPU_HAS_EXTENSION(CPU_EXT_SSNPM)
#if defined(RV32)
#error "Ssnpm extension is not available for RV32. Please disable CPU_EXT_SSNPM."
#elif !defined(CPU_EXT_SSNPM_PMM_MODE)
#error "Ssnpm extension PMM mode is not defined. Please define CPU_EXT_SSNPM_PMM_MODE."
#else
    /**
     * Program the guest-visible Ssnpm PMM mode if the hypervisor was
     * configured to use it (via the CPU_EXT_SSNPM_PMM_MODE macro).
     * Otherwise, henvcfg keeps the reset value written above.
     */
    switch (CPU_EXT_SSNPM_PMM_MODE) {
        case HENVCFG_PMM_DISABLED:
            /* Use the disable encoding to keep PMM effectively off. */
            if (cpu_is_master()) {
                WARNING("Ssnpm extension is enabled but PMM mode is set to disabled.\r\n");
            }
            csrs_henvcfg_set(HENVCFG_PMM_DISABLED << HENVCFG_PMM_OFF);
            break;
        case HENVCFG_PMM_PMLEN_7:
            csrs_henvcfg_set(HENVCFG_PMM_PMLEN_7 << HENVCFG_PMM_OFF);
            break;
        case HENVCFG_PMM_PMLEN_16:
            csrs_henvcfg_set(HENVCFG_PMM_PMLEN_16 << HENVCFG_PMM_OFF);
            break;
        default:
            if (cpu_is_master()) {
                ERROR("Unsupported PMM mode for Ssnpm extension.\r\n");
            }
    }
#endif
#endif
    /**
     * TODO: consider delegating other exceptions e.g. breakpoint or ins misaligned
     */
}
