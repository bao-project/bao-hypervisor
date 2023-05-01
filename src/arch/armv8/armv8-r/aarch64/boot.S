/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

/* In Armv8-R there is no virtual address space (VAS). Notwithstanding,  
 * we define VAS as an identity map of the PAS with MPU rules enforced 
 * using an equivalent "page size" of (at least) 64 bytes (minimal MPU 
 * granularity). 
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

    /* x4 contains the id of the MPU entry being used */
    mov x4, 0

    /**
     * Map loadable image (and possibly unloadable)
     * If the vm image section is used and has built-in vm images, we need
     * to map the loadble and non-loadble region of the image separately.
     * Otherwise we can map it as a single region.
     */
    msr prselr_el2, x4
    isb
    ldr x3, =_image_start
    and x3, x3, PRBAR_BASE_MSK
    orr x3, x3, (PRBAR_SH_IS | PRBAR_AP_RW_EL2)
    msr prbar_el2, x3
    ldr x10, =_image_load_end
    ldr x11, =_image_noload_start
    cmp x10, x11
    bne 1f
    ldr x3, =_image_end
    b 2f
1:
    ldr x3, =_image_load_end
2:
    sub x3, x3, 1
    and x3, x3, PRLAR_LIMIT_MSK
    orr x3, x3, (PRLAR_ATTR(1) | PRLAR_EN)
    msr prlar_el2, x3

    /* Map Image Non-loadable if needed */
    ldr x10, =_image_load_end
    ldr x11, =_image_noload_start
    cmp x10, x11
    beq skip_non_loadable

    add x4, x4, 1
    msr prselr_el2, x4
    ldr x3, =_image_noload_start
    and x3, x3, PRBAR_BASE_MSK
    orr x3, x3, PRBAR_SH_IS
    add x3, x3, PRBAR_AP_RW_EL2
    msr prbar_el2, x3
    isb
    ldr x3, =_image_end
    sub x3, x3, 1
    and x3, x3, PRLAR_LIMIT_MSK
    orr x3, x3, (PRLAR_ATTR(1) | PRLAR_EN)
    msr prlar_el2, x3

skip_non_loadable:

    /* Region 2 - CPU */
    add x4, x4, 1
    msr prselr_el2, x4
    isb
    mrs x3, tpidr_el2
    and x3, x3, PRBAR_BASE_MSK
    orr x3, x3, (PRBAR_SH_IS | PRBAR_AP_RW_EL2)
    msr prbar_el2, x3
    mrs x3, tpidr_el2
    ldr x5, =CPU_SIZE
    add x3, x3, x5
    sub x3, x3, 1
    and x3, x3, PRLAR_LIMIT_MSK
    orr x3, x3, (PRLAR_ATTR(1) | PRLAR_EN)
    msr prlar_el2, x3

    isb

    /* Enable caches and MPU */
    ldr x4, =(SCTLR_RES1 | SCTLR_C | SCTLR_I | SCTLR_M)
    msr sctlr_el2, x4

    dsb nsh
    isb

    br x20
