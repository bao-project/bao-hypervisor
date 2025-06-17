/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

/**
 * In Armv8-R there is no virtual address space (VAS). Notwithstanding, we define VAS as an
 * identity map of the PAS with MPU rules enforced using an equivalent "page size" of (at least) 64
 * bytes (minimal MPU granularity).
 */
.section ".boot", "ax"
.global boot_arch_profile_init
boot_arch_profile_init:

    // Save LR in x20
    mov x20, lr

    /* CPU physical based address */
    ldr x3, =_dmem_phys_beg 
    
    /* CPU_X physical base address */
    mov x7, CPU_SIZE
    madd x3, x0, x7, x3

    /* Clear the CPU struct */
	mov	x16, x3	
	add	x17, x3, x7
	bl	boot_clear

    /* Save CPU_X phys base address on Hyp Soft Thread ID */
    msr tpidr_el2, x3

    /* Disable MPU and Caches */
    mrs x3, sctlr_el2
    mov x4, (SCTLR_I | SCTLR_C | SCTLR_M)
    bic x3, x3, x4
    msr sctlr_el2, x3
    isb

	/* set hypervisor default memory attributes */
	ldr x3, =MAIR_EL2_DFLT
	msr	MAIR_EL2, x3

    isb

    /* Enable caches and MPU */
    ldr x4, =(SCTLR_RES1 | SCTLR_C | SCTLR_I)
    msr sctlr_el2, x4

    dsb nsh
    isb

    br x20
