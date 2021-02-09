/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/bao.h>
#include <arch/csrs.h>
#include <arch/page_table.h>
#include <asm_defs.h>

/**
 * Switch to a new address:
 *
 *      a0: virtual address of new cpu space
 *      a1: physical address of new translation tables
 */
.globl switch_space
switch_space:

    /* Get current CPU space stack start */
    la a6, cpu
    li t0, CPU_STACK_OFF + CPU_STACK_SIZE
    add a6, a6, t0

    /* Calculate stack size */
    mv a7, sp
    sub a5, a6, a7

    /* Get current CPU space current sp */
    mv a6, sp

    /* Get new CPU space current sp */
    li t0, CPU_STACK_OFF + CPU_STACK_SIZE
    add a0, a0, t0
    sub a0, a0, a5

    /* Copy stack */
    li a4, 0
1:
    /* Copy two words */
    ld a2, (a6)
    sd a2, (a0)
    
    /* Increment addressess and count accordingly */
    add a6, a6, 8
    add a0, a0, 8
    add a4, a4, 8
    
    /* If count is less then size, repeat */
    blt a4, a5, 1b
    
    /* Restore original addresses */
    sub a6, a6, a4
    sub a0, a0, a4

    /* Update root page table pointer */
    srl a1, a1, PAGE_SHIFT
    li  t0, SATP_MODE_DFLT
    or  a1, a1, t0
    csrw satp, a1

    /**
     * Invalidate TLB: we can do this directly here without sbi support
     * because we don't really need any shootdown as all harts must go
     * through here.
     */
    sfence.vma

    ret
