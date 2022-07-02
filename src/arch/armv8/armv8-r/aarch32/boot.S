/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

.section ".boot", "ax"
.global boot_arch_profile_init
boot_arch_profile_init:

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
    mcr p15, 4, r4, c10, c2, 0

    // TODO - Set MPU hypervisor regions

    dsb
    isb

    /* Enable caches */
    mrc p15, 4, r3, c1, c0, 0 // HSCTLR
    ldr r4, =(SCTLR_C | SCTLR_I)
    orr r3, r3, r4
    mcr p15, 4, r3, c1, c0, 0 // HSCTLR

    // TODO - Enable MPU

    dsb
    isb

/* In Armv8-R there is no virtual address space (VAS). Notwithstanding,  
 * we define VAS as an identity map of the PAS with MPU rules enforced 
 * using an equivalent "page size" of (at least) 64 bytes (minimal MPU 
 * granularity). 
 */
_enter_vas:

    /* CPU physical based address */
    ldr r3, =_dmem_phys_beg 
    
    /* CPU_X physical base address */
    mov r7, #CPU_SIZE
    mla r3, r0, r7, r3

    /* Save CPU_X phys base address on Hyp Soft Thread ID */
    mcr p15, 4, r3, c13, c0, 2 // write HTPIDR

    /* Initialize stack pointer */
    mov r4, #(CPU_STACK_OFF + CPU_STACK_SIZE)
    add r3, r3, r4
    mov sp, r3

    bx lr

