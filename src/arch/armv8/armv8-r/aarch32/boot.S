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
    /* CPU physical based address */
    ldr r3, =_dmem_phys_beg 
    
    /* CPU_X physical base address */
    mov r7, #CPU_SIZE
    mla r3, r0, r7, r3

    /* Clear the CPU struct */
    mov r11, r3
    add r12, r3, r7
    mov r10, lr
    bl boot_clear
    mov lr, r10

    /* Save CPU_X phys base address on Hyp Soft Thread ID */
    mcr p15, 4, r3, c13, c0, 2 // write HTPIDR

    /* Disable MPU and Caches */
    mrc p15, 4, r3, c1, c0, 0 // HSCTLR
    mov r4, #(SCTLR_I | SCTLR_C | SCTLR_M)
    bic r3, r3, r4
    dsb
    mcr p15, 4, r3, c1, c0, 0 // HSCTLR
    isb

    /* Reset Hyp Architectural Feature Trap */
    mov r4, #0
    mcr p15, 4, r4, c1, c1, 2 // HCPTR

    ldr r4, =MAIR_EL2_DFLT
    mcr p15, 4, r4, c10, c2, 0 // HMAIR

    /* r4 contains the id of the MPU entry being used */
    mov r4, #(-1)

    /**
     * Map loadable image (and possibly unloadable)
     * If the vm image section is used and has built-in vm images, we need
     * to map the loadble and non-loadble region of the image separately.
     * Otherwise we can map it as a single region.
     */
    add r4, r4, #1
    mcr p15, 4, r4, c6, c2, 1   // HPRSELR
    ldr r3, =_image_start
    and r3, r3, #PRBAR_BASE_MSK
    orr r3, r3, #PRBAR_SH_IS
    orr r3, r3, #PRBAR_AP_RW_EL2
    mcr p15, 4, r3, c6, c3, 0   // HPRBAR
    ldr r10, =_image_load_end
    ldr r11, =_image_noload_start
    cmp r10, r11
    ldreq r3, =_image_end
    ldrne r3, =_image_load_end
    sub r3, r3, #1
    and r3, r3, #PRLAR_LIMIT_MSK
    orr r3, r3, #(PRLAR_ATTR(1) | PRLAR_EN)
    mcr p15, 4, r3, c6, c3, 1   // HPRLAR

    /* Map Image Non-loadable if needed */
    ldr r10, =_image_load_end
    ldr r11, =_image_noload_start
    cmp r10, r11
    beq skip_non_loadable
    add r4, r4, #1
    mcr p15, 4, r4, c6, c2, 1   // HPRSELR
    ldr r3, =_image_noload_start
    and r3, r3, #PRBAR_BASE_MSK
    orr r3, r3, #PRBAR_SH_IS
    orr r3, r3, #PRBAR_AP_RW_EL2
    mcr p15, 4, r3, c6, c3, 0   // HPRBAR
    ldr r3, =_image_end
    sub r3, r3, #1
    and r3, r3, #PRLAR_LIMIT_MSK
    orr r3, r3, #(PRLAR_ATTR(1) | PRLAR_EN)
    mcr p15, 4, r3, c6, c3, 1   // HPRLAR

skip_non_loadable:

    /* Region 2 - CPU */
    add r4, r4, #1
    mcr p15, 4, r4, c6, c2, 1   // HPRSELR
    mrc p15, 4, r3, c13, c0, 2  // HTPIDR (read CPU base addr)
    and r3, r3, #PRBAR_BASE_MSK
    orr r3, r3, #PRBAR_SH_IS
    orr r3, r3, #PRBAR_AP_RW_EL2
    mcr p15, 4, r3, c6, c3, 0   // HPRBAR
    mrc p15, 4, r3, c13, c0, 2  // HTPIDR (read CPU base addr)
    add r3, r3, #CPU_SIZE
    sub r3, r3, #1
    and r3, r3, #PRLAR_LIMIT_MSK
    orr r3, #(PRLAR_ATTR(1) | PRLAR_EN)
    mcr p15, 4, r3, c6, c3, 1   // HPRLAR

    dsb
    isb

    /* Enable caches and MPU */
    ldr r4, =(SCTLR_RES1_AARCH32 | SCTLR_C | SCTLR_I | SCTLR_M)
    mcr p15, 4, r4, c1, c0, 0 // HSCTLR

    dsb
    isb
    bx lr
