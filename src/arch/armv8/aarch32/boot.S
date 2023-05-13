/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>
#include <config_defs.h>
#include <platform_defs.h>

.macro get_phys_addr rd, ra, label
    ldr \rd, =\label
    ldr \ra, =BAO_VAS_BASE
    sub \rd, \rd, \ra
    add \rd, \rd, r1
.endm

.data
.balign 4
/**
 * barrier is used to minimal synchronization in boot - other cores wait for
 * bsp to set it.
 */
_barrier: .4byte 0

/**
 * 	The following code MUST be at the base of the image, as this is bao's entry
 *	point. Therefore .boot section must also be the first in the linker script.
 *  DO NOT implement any code before the _reset_handler in this section.
 */
 .section ".boot", "ax"
.globl _reset_handler
.globl _el2_entry
_el2_entry:
_reset_handler:

    /**
     * Not following any ABI for registers in this boot code.
     * The following registers are however reserved to be passed to main
     * as arguments:
     *     r0 -> contains cpu id
     *     r1 -> contains image base load address
     *     r2 -> contains config binary load address (passed in r0)
     * Register r9 is reserved to indicate if the current CPU is master (negated)
	 */

    /* Read core ID (MPIDR) and set image load addr */
    mov r2, r0
    mrc p15, 0, r0, c0, c0, 5 // read MPIDR
    ldr r1, =MPIDR_AFF_MSK
    and r0, r0, r1

    /**
     * TODO: Linearize cpu id according to the number of clusters and
     * processors per cluster.
     */

    adr r1, _el2_entry

    /*
     * Install vector table physical address early, in case exception occurs
     * during this initialization.
     */
    get_phys_addr r3, r4, _hyp_vector_table
    mcr p15, 4, r3, c12, c0, 0 // write HVBAR

/* Setting r9 should if set !is_cpu_master */
#if defined(CPU_MASTER_FIXED)
   mov r3, #CPU_MASTER_FIXED
   cmp r0, r3
   movne r9, #1
   cmp r9, #0
   bne 1f
#else
/**
 * If the cpu master is not fixed, for setting it, we assume only one cpu is
 * initially activated which later will turn on all the others. Therefore, there
 * is no concurrency when setting CPU_MASTER and no atomic operations are needed.
 */
 .pushsection .data
_master_set:
    .4byte 0
.popsection
    mov	r5, #1
    get_phys_addr r3, r4, _master_set
_set_master_cpu:
    ldr r9, [r3]
    cmp r9, #0
    bne 1f
    str r5, [r3]
#endif
    get_phys_addr r3, r4, CPU_MASTER
    str r0, [r3]
1:

    /**
     * TODO: bring the system to a well known state. This includes disabling
     * the MPU, all caches, BP and others, and invalidating them.
     */

    /* Clear stack pointer to avoid unaligned SP exceptions during boot */
    mov r3, #0
    mov sp, r3


    /* Invalidate Caches */
    mov r10, r0 // save
    mov r11, r1
    mov r12, r2

    mov r0, #0 // invalidate DCache
    bl boot_cache_invalidate

    mov r0,	r10 // restore
    mov r1,	r11
    mov r2,	r12

    mcr p15, 0, r10, c7, c5, 0 // invalidate ICache

    /* Call boot subarch specific */
    bl boot_arch_profile_init

    /* If this is the cpu master, clear bss */
    cmp r9, #0
    bne 1f
    ldr r11, =_bss_start
    ldr r12, =_bss_end
    bl boot_clear

    ldr r5, =_barrier
    mov r7, #2
    stl r7, [r5]

1:
    /* wait for bsp to finish clearing bss */
    ldr r7, =_barrier
2:
    lda r8, [r7]
    cmp r8, #2
    blt 2b

    isb

    /* Initialize stack pointer */
    mrc p15, 4, r3, c13, c0, 2 // HTPIDR
    mov r4, #(CPU_STACK_OFF + CPU_STACK_SIZE)
    add r3, r3, r4
    mov sp, r3

    b init

    /* This point should never be reached */
    b .

/***** 	Helper functions for boot code. ******/

.global boot_clear
.func boot_clear
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
.endfunc

/*
 * Code adapted from "Application Note Bare-metal Boot Code for ARMv8-A
 * Processors - Version 1.0"
 *
 * r0 - cache level to be invalidated (0 - dl1$, 1 - il1$)
 */
.global boot_cache_invalidate
.func boot_cache_invalidate
boot_cache_invalidate:
    mcr p15, 2, r0, c0, c0, 0 // write CSSELR (cache size selection)
    mrc p15, 1, r4, c0, c0, 0 // read CCSIDR (cache size id)
    and r1, r4, #0x7
    add r1, r1, #0x4 // r1 = cache line size
    ldr r3, =0x7fff
    and r2, r3, r4, lsr #13 // r2 = cache set number - 1
    ldr r3, =0x3ff
    and r3, r3, r4, lsr #3 // r3 = cache associativity number - 1
    clz r4, r3 // r4 = way position in the cisw instruction
    mov r5, #0 // r5 = way counter way_loop
way_loop:
    mov r6, #0 // r6 = set counter set_loop
set_loop:
    lsl r7, r5, r4
    orr r7, r0, r7 // set way
    lsl r8, r6, r1
    orr r7, r7, r8 // set set
    mcr p15, 0, r7, c7, c14, 2 // clean and invalidate cache line
    add r6, r6, #1 // increment set counter
    cmp r6, r2 // last set reached yet?
    ble set_loop // if not, iterate set_loop
    add r5, r5, #1 // else, next way
    cmp r5, r3 // last way reached yet?
    ble way_loop // if not, iterate way_loop
    bx lr
.endfunc

