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
            ERROR("Platform configured to use Sstc extension, but extension not present.\n");
        }
        // Set stimecmp to infinity in case we enable the stimer interrupt somewhere else
        // and fail to set the timer to a point in the future.
        csrs_stimecmp_write(~0U);
    } else {
        csrs_henvcfg_clear(HENVCFG_STCE);
    }

    /**
     * Configure the State Enable mechanism (Ssstateen).
     *
     * State enable CSRs control whether less-privileged software may access
     * selected architectural state and extension-specific CSRs.
     *
     * In Bao, this is used to define which optional privileged features are
     * visible to VS-mode guests, while keeping the default policy restrictive.
     *
     * Execution reaches this block only when the Ssstateen extension is
     * implemented by the platform.
     */
#if CPU_HAS_EXTENSION(CPU_EXT_SSSTATEEN)
    /**
     * Enable and sanity check the custom-state hstateen bit if the platform
     * implements the compressed extension. Otherwise, keep the bit cleared.
     *
     * The write is verified through readback because hstateen fields are
     * WARL: unsupported bits may read back as zero.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_C)) {
        csrs_hstateen0_set(HSTATEEN_C);
        bool custom_state_present = (csrs_hstateen0_read() & HSTATEEN_C) != 0;
        if (cpu_is_master() && !custom_state_present) {
            ERROR("Platform configured to allow access to custom state, but extension not "
                  "avaialble.\r\n");
        }
    }

    /**
     * Enable and sanity check the FCSR-related hstateen bit when floating-point
     * instructions operate on x registers. Otherwise, keep the bit cleared.
     */
    if (!CPU_HAS_EXTENSION(CPU_EXT_F)) {
        csrs_hstateen0_set(HSTATEEN_FCSR);
        bool fcsr_not_present = (csrs_hstateen0_read() & HSTATEEN_FCSR) != 0;
        if (cpu_is_master() && !fcsr_not_present) {
            ERROR("Platform configured so that floating-point instructions operate on integer "
                  "registers, but floating-point unit is implemented.\r\n");
        }
    }

    /**
     * Enable and sanity check the context-state hstateen bit when Sdtrig is
     * implemented. Otherwise, keep the bit cleared.
     *
     * This allows guests to access the scontext CSR if the
     * platform supports it.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_SDTRIG)) {
        csrs_hstateen0_set(HSTATEEN_CTX);
        bool sdtrig_state_enabled = (csrs_hstateen0_read() & HSTATEEN_CTX) != 0;
        if (cpu_is_master() && !sdtrig_state_enabled) {
            ERROR("Platform configured to use Sdtrig extension, but extension not available.\r\n");
        }
    }

    /**
     * Enable and sanity check the indirect-CSR hstateen bit when Sscsrind is
     * present. Otherwise, keep the bit cleared.
     *
     * Indirect CSR access is required by some optional privileged features,
     * so it is enabled independently and verified with a WARL readback.
     */
    if (CPU_HAS_EXTENSION(CPU_EXT_SSCSRIND)) {
        csrs_hstateen0_set(HSTATEEN_CSRIND);
        bool sscrind_ctxt_en = (csrs_hstateen0_read() & HSTATEEN_CSRIND) != 0;
        if (cpu_is_master() && !sscrind_ctxt_en) {
            ERROR("Platform configured to use Sscsrind extension, but extension not "
                  "available.\r\n");
        }
    }

    /**
     * Enable and sanity check the AIA and IMSIC hstateen bits when Bao is
     * built to use AIA. Otherwise, keep those bits cleared.
     *
     * AIA guest support depends on the relevant AIA state being exposed
     * through hstateen. Sscsrind is checked first because some IMSIC-related
     * state is accessed through the indirect CSR mechanism.
     */
    if (IRQC == AIA) {
        if (!CPU_HAS_EXTENSION(CPU_EXT_SSCSRIND)) {
            ERROR("AIA requires Sscsrind extension to be present.");
        }
        csrs_hstateen0_set(HSTATEEN_IMSIC | HSTATEEN_AIA | HSTATEEN_CSRIND);
        INFO("\nM\n")
        bool aia_ctxt_en =
            (csrs_hstateen0_read() & (HSTATEEN_IMSIC | HSTATEEN_AIA | HSTATEEN_CSRIND)) ==
            (HSTATEEN_IMSIC | HSTATEEN_AIA | HSTATEEN_CSRIND);
        if (cpu_is_master() && (!aia_ctxt_en)) {
            ERROR("Platform configured to use AIA and IMSIC extensions, but extensions not "
                  "available.\r\n");
        }
    }

    /**
     * Enable and sanity check the senvcfg hstateen bit so VS-mode can manage
     * delegated environment configuration state.
     */
    csrs_hstateen0_set(HSTATEEN_ENVCFG);
    bool senvcfg_ctxt_en = (csrs_hstateen0_read() & HSTATEEN_ENVCFG) != 0;
    if (cpu_is_master() && (!senvcfg_ctxt_en)) {
        ERROR("Platform configured to enable senvcfg access to VS-mode but this feature is not "
              "available.\r\n");
    }

    /**
     * Enable the SEO bits in hstateen0-3 so VS-mode can access the sstateen
     * CSRs.
     *
     * Because hstateen[1..3] are initialized to zero except for the SEO bits,
     * guests may probe or read these CSRs without obtaining access to any
     * additional architectural state.
     *
     * This helps compatibility and avoids unnecessary traps for guest
     * software that checks for the presence of state-enable CSRs.
     */
    csrs_hstateen0_write(HSTATEEN_SEO);
    csrs_hstateen1_write(HSTATEEN_SEO);
    csrs_hstateen2_write(HSTATEEN_SEO);
    csrs_hstateen3_write(HSTATEEN_SEO);
#endif
    /**
     * TODO: consider delegating other exceptions e.g. breakpoint or ins misaligned
     */
}
