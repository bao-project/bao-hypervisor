/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vmm.h>
#include <arch/csrs.h>

void vmm_arch_init()
{
    /**
     * At this point, we should make sure misa's H bit is set (at least by
     * reading it). However, current SBI does not allow us to even read it.
     * So we assume it is set - if not, the first acess to an hypervisor
     * register will set an illegal inst fault.
     */

    /**
     * Delegate all interrupts and exceptions not meant to be dealt by
     * the hypervisor
     */

    CSRW(CSR_HIDELEG, HIDELEG_VSSI | HIDELEG_VSTI | HIDELEG_VSEI);
    CSRW(CSR_HEDELEG, HEDELEG_ECU | HEDELEG_IPF | HEDELEG_LPF | HEDELEG_SPF);

    /**
     * TODO: consider delegating other exceptions e.g. breakpoint or ins
     * misaligned
     */
}
