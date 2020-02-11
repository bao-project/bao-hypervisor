/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <arch/page_table.h>
#include <asm_defs.h>

/**
 * Copy memory:
 *
 *      x2: data
 *      x3: data
 *      x4: count
 *      x5: size
 *      x0: destination address
 *      x7: source address
 */
memcpy:
        mov x4, #0
1:
        /* Copy two words */
        ldp x2, x3, [x7]
        stp x2, x3, [x0]

        /* Increment addressess and count accordingly */
        add x7, x7, 8
        add x0, x0, 8
        add x4, x4, 8

        /* If count is less then size, repeat */
        cmp x4, x5
        b.le 1b

        /* Restore original addresses */
        sub x7, x7, x4
        sub x0, x0, x4

        ret

/**
 * Switch to a new address:
 *
 *      x0: virtual address of new cpu space
 *      x1: physical address of new cpu space
 */
.globl switch_space
switch_space:
        
    /**
    * update flat maping page table entry  to feature new physical address space 
    * entry page
    */
    adr x3, _image_start
    PTE_INDEX_ASM x4, x3, 1
    adr x5, root_l1_flat_pt
    add x3, x3, #(PTE_HYP_FLAGS | PTE_TABLE)
    str x3, [x5, x4]

    /**
     * Copy the stack
     */

    /* Get current CPU space stack start */
    ldr x7, =cpu
    add x7, x7, #(CPU_STACK_OFF + CPU_STACK_SIZE)

    /* Calculate stack size */
    mov x8, sp
    sub x5, x7, x8

    /* Get current CPU space current sp */
    mov x7, sp

    /* Get new CPU space current sp */
    add x0, x0, #(CPU_STACK_OFF + CPU_STACK_SIZE)
    sub x0, x0, x5

    /* Copy */
    mov x8, x30
    bl      memcpy
    mov x30, x8

    /**
     * Invalidate TLB
     */
    dsb ishst
    tlbi alle2
    dsb ish
    isb

    /**
     * Update TTBR
     */

    /* Update value of TTBR0_EL2 */
	msr TTBR0_EL2, x1
    dsb ish
    isb

    tlbi alle2
    dsb ish
    isb

    ret
