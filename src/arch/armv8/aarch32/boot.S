/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro@bao-project.org>
 *      Afonso Santos <afomms@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

.macro get_phys_addr rd, ra, label
    adr \rd, _el2_entry
    ldr \ra, =_el2_entry
    sub \rd, \ra, \rd
    ldr \ra, =\label
    sub \rd, \ra, \rd
.endm

.data 
.align 3
/**
 * barrier is used to minimal synchronization in boot - other cores wait for
 * bsp to set it.
 */
_barrier: .8byte 0			

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

    get_phys_addr r1, r3, _image_start

    /* 
     * Install vector table physical address early, in case exception occurs
     * during this initialization.
     */
    get_phys_addr r3, r4, _hyp_vector_table
    mcr p15, 4, r3, c12, c0, 0 // write HVBAR

.pushsection .data
_master_set:
    .8byte 0
.popsection


/**
 * For setting the master CPU, we assume only one CPU is initially activated 
 * which later will turn on all the others. Therefore, there is no concurrency 
 * when setting CPU_MASTER and no atomic operations are needed.
 * As a result r9 should be set to !is_cpu_master
 */
_set_master_cpu:
    get_phys_addr r3, r4, _master_set
    ldr r9, [r3]
    cmp r9, #0
    bne 7f
    mov	r9, #1
    str r9, [r3]
    mov r9, #0
    get_phys_addr r3, r4, CPU_MASTER
    str r0, [r3]
7:

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

    /* If this is bsp (cpu 0) clear bss */
    cmp r9, #0
    bne 1f
    ldr r11, =_bss_start	
    ldr r12, =_bss_end	
    bl boot_clear	

    ldr r5, =_barrier
    mov r7, #2
    str r7, [r5]	

1:
    /* wait for bsp to finish clearing bss */
    ldr r7, =_barrier
    ldr r8, [r7]
    cmp r8, #2
    blt 1b

    isb

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

