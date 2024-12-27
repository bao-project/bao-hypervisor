/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>
#include <config_defs.h>
#include <platform_defs.h>

.syntax unified

/**
 *  The following code MUST be at the base of the image, as this is bao's entry point. Therefore
 * .boot section must also be the first in the linker script. DO NOT implement any code before the
 * _reset_handler in this section.
 */
 .section ".boot", "ax"
.thumb
.thumb_func
.globl _reset_handler
_reset_handler:

    /**
     * Not following any ABI for registers in this boot code.
     * The following registers are however reserved to be passed to main
     * as arguments:
     *     r0 -> contains cpu id
     *     r1 -> contains image base load address
     *     r2 -> contains config binary load address (passed in r0)
     *     r10-> fixed in the compiler to be used as the CPU struct pointer
     * Register r9 is reserved to indicate if the current CPU is master (negated)
	 */

    /* Disable interrupts */
    cpsid i

    /* TODO:ARMV8M
     * In Armv8-M, there is no core id register. We need to use platform specific code to get
     * the core id.
     * e.g., in LPC55S69 CPU1 has no MPU, therefore MPU->TYPE reg should be read-as-zero. That's
     * how we can distinguish between CPU0 and CPU1. For now just use #0 for CPU0
     */
    mov r0, #0

    /**
     * Get base image load address.
     */
    adr r1, _reset_handler

    /*
     * Install vector table physical address early, in case exception occurs during this
     * initialization.
     */
    ldr r3, =SCB_BASE
    add r4, r3, SCB_VTOR_OFF
    ldr r3, =_sec_vector_table
    str r3, [r4]

    /*
     * TODO:ARMV8M
     * What should we do here?
     */
    /* Setting r9 should if set !is_cpu_master */

    /*
     * TODO:ARMV8M
     * Bring the system to a well known state. This includes disabling the MPU, all caches, BP and
     * others, and invalidating them.
     */
    /* Disable SAU */
    ldr r3, =SAU_BASE
    mov r4, #SAU_CTRL_ENABLE
    ldr r5, [r3]
    bic r5, r5, r4
    str r5, [r3]

    /* Disable MPU */
    ldr r3, =MPU_BASE
    mov r4, #MPU_CTRL_ENABLE
    ldr r5, [r3]
    bic r5, r5, r4
    str r5, [r3]

    /*
     * TODO:ARMV8M
     * In Armv8-M, the stack pointer is initialized by the processor at reset. Therefore, we don't
     * need to clear it.
     */

    /* Call boot subarch specific */
    //bl boot_arch_profile_init

    /* CPU physical based address */
    ldr r10, =_dmem_beg

    /* CPU_X physical base address
     * In Armv8-M there is not scratch register, so we use r10 as the scratch register by setting
     * -ffixed-r10 in the compiler.
     */
    mov r7, #CPU_SIZE
    mla r10, r0, r7, r10      //TODO:ARMV8M - We are running in single-core, so this is not needed?!

    /* Clear the CPU struct */
    mov r11, r10
    add r12, r10, r7
    mov r3, lr
    bl boot_clear
    mov lr, r3

    /* r4 contains the id of the MPU entry being used */
    mov r4, #(-1)
    /* r5 contains the secure MPU based address */
    ldr r5, =MPU_BASE

    /* Configure MPU MAIR */
    ldr r6, =MAIR_SEC_PLVL_DFLT
    str r6, [r5, #MPU_MAIR0_OFF]

    /* Region 0 - Map LMA sections */
    add r4, r4, #1
    str r4, [r5, #MPU_RNR_OFF]
    ldr r6, =_image_start
    and r6, r6, #MPU_RBAR_BASE_MSK      /* TODO:ARMV8M - I suppose it should be Non shareable? */
    orr r6, r6, #MPU_RBAR_AP_RW_PLVL
    str r6, [r5, #MPU_RBAR_OFF]
    ldr r6, =_image_load_end
    sub r6, r6, #1
    and r6, r6, #MPU_RLAR_LIMIT_MSK
    orr r6, r6, #(MPU_RLAR_ATTR(0) | MPU_RLAR_EN)               /* TODO:ARMV8M - What should be done here */
    str r6, [r5, #MPU_RLAR_OFF]

    /* Region 1 - Map VMA sections */
    add r4, r4, #1
    str r4, [r5, #MPU_RNR_OFF]
    ldr r6, =_data_vma_start
    and r6, r6, #MPU_RBAR_BASE_MSK      /* TODO:ARMV8M - I suppose it should be Non shareable? */
    orr r6, r6, #MPU_RBAR_AP_RW_PLVL
    str r6, [r5, #MPU_RBAR_OFF]
    ldr r6, =_image_end
    sub r6, r6, #1
    and r6, r6, #MPU_RLAR_LIMIT_MSK
    orr r6, r6, #(MPU_RLAR_ATTR(0) | MPU_RLAR_EN)               /* TODO:ARMV8M - What should be done here */
    str r6, [r5, #MPU_RLAR_OFF]

    /* Region 2 - CPU */
    add r4, r4, #1
    str r4, [r5, #MPU_RNR_OFF]
    ldr r6, =_dmem_beg
    and r6, r10, #MPU_RBAR_BASE_MSK      /* TODO:ARMV8M - I suppose it should be Non shareable? */
    orr r6, r6, #MPU_RBAR_AP_RW_PLVL
    str r6, [r5, #MPU_RBAR_OFF]
    add r6, r10, #CPU_SIZE
    sub r6, r6, #1
    and r6, r6, #MPU_RLAR_LIMIT_MSK
    orr r6, r6, #(MPU_RLAR_ATTR(0) | MPU_RLAR_EN | MPU_RLAR_PXN)               /* TODO:ARMV8M - What should be done here */
    str r6, [r5, #MPU_RLAR_OFF]

    /* Clear remaining regions */
    bl clear_mpu

    /* Read MPU regions */
    mov r4, #0
1:
    str r4, [r5, #MPU_RNR_OFF]
    ldr r6, [r5, #MPU_RBAR_OFF]
    ldr r7, [r5, #MPU_RLAR_OFF]
    add r4, r4, #1
    cmp r4, #8
    bne 1b

    dsb
    isb

    /* Enable Fault Handlers */
    ldr r3, =SCB_BASE
    ldr r4, [r3, #SCB_SHCSR_OFF]
    orr r4, r4, #(SCB_ENABLE_ALL_FAULTS)
    str r4, [r3, #SCB_SHCSR_OFF]

    /* Enable MPU */
    mov r4, #(MPU_CTRL_ENABLE)
    ldr r6, [r5, #MPU_CTRL_OFF]
    orr r4, r4, r6
    str r4, [r5, #MPU_CTRL_OFF]

    dsb
    isb

    /* Copy data from RX to RWX */
    ldr r7, =_data_lma_start        // LMA start
    ldr r11, =_data_vma_start       // VMA start
    ldr r12, =_image_noload_start   // VMA end
    bl copy_data

    /* Clear bss */
    ldr r11, =_bss_start
    ldr r12, =_bss_end
    bl boot_clear

    isb

    /* Initialize stack pointer and stack limit */
    mov r4, #CPU_STACK_OFF
    add r5, r10, r4
    msr msplim, r5
    add r4, r4, #CPU_STACK_SIZE
    add r5, r10, r4
    msr msp, r5

    /* Enable interrupts */
    cpsie i

    b init

    /* This point should never be reached */
    b .

/*****  Helper functions for boot code. ******/

.global boot_clear
boot_clear:
2:
    mov r8, #0
	cmp r11, r12
	bge 1f
	str r8, [r11]
	add r11, r11, #4
	b 2b
1:
	bx lr

/* Copies data from r7 to r11 up to the r12 limit */
.global copy_data
copy_data:
1:
    ldr r8, [r7], #4
    str r8, [r11], #4
    cmp r11, r12
    bne 1b
    bx lr

/* Clear all remaining MPU regions (r5 contains MPU_BASE, r4 the region number) */
.global clear_mpu
clear_mpu:
    mov r6, #0
1:
    add r4, r4, #1
    str r4, [r5, #MPU_RNR_OFF]
    str r6, [r5, #MPU_RBAR_OFF]
    str r6, [r5, #MPU_RLAR_OFF]
    cmp r4, #7  //TODO:ARMV8M - This is implementation-def, should be changed
    bne 1b
    bx lr
