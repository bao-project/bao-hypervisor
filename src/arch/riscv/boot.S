/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/csrs.h>
#include <arch/page_table.h>
#include <asm_defs.h>
#include <platform_defs.h>

#define PT_SIZE PAGE_SIZE
#define PT_LVLS 3
#define PTE_INDEX_SHIFT(LEVEL) ((9 * (PT_LVLS - 1 - (LEVEL))) + 12)

/**
 *  Calculates the index or offset of a page table entry for given virtual 
 * address(addr) at a given level of page table.
 */
.macro PTE_INDEX_ASM	index, addr, level
	srl \index, \addr, PTE_INDEX_SHIFT(\level) 
    li  s0, ((PAGE_SIZE/8)-1)
	and \index, \index, s0
	sll \index, \index, 3
.endm

/**
 * Calculates the pointer to a pte given the page table pointer(pt),
 * the page table level (levle) and the target virtual address (va)
 */
.macro PTE_PTR  pte, pt, level, va
    PTE_INDEX_ASM	s1, \va, \level
    add     \pte, s1, \pt
.endm

/**
 * Creates a page table entry (pte) for a given physical address (pa) 
 * and set of flags.
 */
.macro PTE_FILL    pte, pa, flags
    srl     \pte, \pa, 2
    or      \pte, \pte, \flags
.endm

.macro LD_SYM       rd, sym
    la      \rd, \sym
    LOAD      \rd, 0(\rd)
.endm

.section ".rodata", "a"
/* Symbol values */
_image_start_sym: .8byte _image_start
_image_load_end_sym: .8byte _image_load_end
_image_noload_start_sym: .8byte _image_noload_start
_image_end_sym: .8byte _image_end
_dmem_beg_sym: .8byte _dmem_beg
_enter_vas_sym: .8byte _enter_vas
_bss_start_sym: .8byte _bss_start
_bss_end_sym: .8byte _bss_end

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

_reset_handler:

    /**
    *  The previous boot stage should pass the following arguments:
    *      a0 -> hart id
    *      a1 -> config binary load addr
    * The following registers are reserved to be passed to init function
    * as arguments:
    *      a0 -> hart id
    *      a1 -> contains image base load address
    *      a2 -> config binary load address (originally passed in a1)
    *
    * The remaining code must use t0-t6 as scratchpad registers in the main
    * flow and s0-s5 in auxiliary routines. s6-s11 are used to hold constants
    * a3-a7 are used as arguments and return values (can be also corrputed in
    * auxiliary routines).
    */

    mv      a2, a1
    la      a1, _image_start
    la      s6, extra_allocated_phys_mem

    /**
     *  Setup stvec early. In case of we cause an exception in this boot code
     * we end up at a known place.
     */
    la      t0, _hyp_trap_vector
    and     t0, t0, ~STVEC_MODE_MSK
    or      t0, t0, STVEC_MODE_DIRECT
    csrw    stvec, t0

    /**
     *  Bring processor to known supervisor state: make sure interrupts
     * and memory translation are disabled.
     */

    csrw   sstatus, zero
    csrw   sie, zero
    csrw   sip, zero
    csrw   satp, zero 


#if defined(CPU_MASTER_FIXED)
/**
 * All cpus set the CPU_MASTER with the same value to avoid synchronization.    
 */
    la      t0, CPU_MASTER
    li      t1, CPU_MASTER_FIXED
    sd      t1, 0(t0)
#else
/**
 * The first hart to grab the lock is CPU_MASTER.
 */
.pushsection .data
_boot_lock:
    .4byte 0
.popsection
    la      t0, _boot_lock
    li      t1, 1
1:
    lr.w    t2, (t0)
    bnez    t2, 2f
    sc.w    t2, t1, (t0)   
    bnez    t2, 1b 
    la      t0, CPU_MASTER
    sd      a0, 0(t0)
2:
#endif

    /* Setup bootstrap page tables. Assuming sv39 support. */ 

 	/* Skip initialy global page tables setup if not hart */
    LD_SYM  t0, CPU_MASTER
	bne     a0, t0, wait_for_bsp   

 	la	    a3, _page_tables_start	
	la	    a4, _page_tables_end	
    add     a3, a3, s6
    add     a4, a4, s6
	call	clear		 

    la          t0, root_l1_pt
    add         t0, t0, s6
    la          t1, root_l2_pt
    add         t1, t1, s6
    PTE_FILL    t1, t1, PTE_TABLE
    li          t2, BAO_VAS_BASE
    PTE_PTR     t2, t0, 1, t2
    STORE       t1, 0(t2)


    la          t0, root_l2_pt
    add         t0, t0, s6
    LD_SYM      t1, _image_start_sym
    PTE_PTR     t1, t0, 2, t1
    LD_SYM      t2, _image_load_end_sym
    PTE_PTR     t2, t0, 2, t2

    la          t0, _image_start
    PTE_FILL    t0, t0, PTE_HYP_FLAGS | PTE_PAGE
1:
    bge     t1, t2, 2f
    STORE   t0, 0(t1)
    add     t1, t1, 8
    add     t0, t0, 0x400
    j       1b
2:
    la          t0, root_l2_pt
    add         t0, t0, s6
    LD_SYM      t2, _image_end_sym
    PTE_PTR     t2, t0, 2, t2
    bge         t1, t2, 3f
    la          t0, _image_noload_start
    PTE_FILL    t0, t0, PTE_HYP_FLAGS | PTE_PAGE
    j 1b
3:
    fence   w, w
    la      t0, _barrier
    li      t1, 1
    STORE   t1, 0(t0)
    j       map_cpu

wait_for_bsp:
    la      t0, _barrier
    li      t1, 1
1:
    LOAD      t2, 0(t0)
    blt     t2, t1, 1b

map_cpu:
    /* Calculate base phys address of CPU struct -> t0 */
    la      t0, _dmem_phys_beg
    li      t1, (CPU_SIZE + (PT_SIZE*PT_LVLS))
    mul     t2, t1, a0
    add     t0, t0, t2
    mv      a3, t0
    add     a4, a3, t1
    call    clear

    /* Calculate phys address page table -> t1 */
    li      t2, CPU_SIZE
    add     t1, t0, t2

    /* Flat mapping to switch to VAS. */
    PTE_PTR     t2, t1, 0, a1
    li          t3, ~((1 << 30) -1)
    and         t3, a1, t3          //align a1 to 1GB (levle 0 superpage)  
    PTE_FILL    t3, t3, PTE_HYP_FLAGS | PTE_PAGE | PTE_SUPERPAGE
    STORE       t3, 0(t2)

    /* Add root l1 page table pointer to root page table */
    la          t2, root_l1_pt
    add         t2, t2, s6
    PTE_FILL    t2, t2, PTE_TABLE
    li          t3, BAO_VAS_BASE
    PTE_PTR     t3, t1, 0, t3
    STORE       t2, 0(t3)

    li      t4, PAGE_SIZE

    add         t2, t1, t4
    PTE_FILL    t2, t2, PTE_TABLE
    li          t3, BAO_CPU_BASE
    PTE_PTR     t3, t1, 0, t3
    STORE       t2, 0(t3)

    add         t1, t1, t4
    add         t2, t1, t4
    PTE_FILL    t2, t2, PTE_TABLE
    li          t3, BAO_CPU_BASE
    PTE_PTR     t3, t1, 1, t3
    STORE       t2, 0(t3)


    add         t1, t1, t4
    li          t2, BAO_CPU_BASE
    PTE_PTR     t1, t1, 2, t2
    PTE_FILL    t2, t0, PTE_HYP_FLAGS | PTE_PAGE
    li          t3, CPU_SIZE+PT_SIZE
1:
    blez    t3, setup_cpu
    STORE   t2, 0(t1)
    add     t1, t1, 8
    add     t2, t2, 0x400
    sub     t3, t3, t4
    j       1b
    
setup_cpu:
    la      t0, _dmem_phys_beg
    li      t1, (CPU_SIZE + (PT_SIZE*PT_LVLS))
    mul     t1, t1, a0
    add     t0, t0, t1   
    li      t1, CPU_SIZE
    add     t0, t0, t1
    srl     t0, t0, PAGE_SHIFT
    li      t2, SATP_MODE_DFLT
    or      t0, t0, t2

    la      t2, _enter_vas_sym
    LOAD    t2, 0(t2)

    sfence.vma
    csrw   satp, t0

    jr      t2

_enter_vas:
	/* Remove temporary mapping - the L1 page holding it leaks */
	/* TODO: clear TLB entries for this mapping */

    /* now set stvec in virtual address space */
    la      t0, _hyp_trap_vector
    and     t0, t0, ~STVEC_MODE_MSK
    or      t0, t0, STVEC_MODE_DIRECT
    csrw   stvec, t0

    /* Init stack pointer and global pointer */
    /* TODO: what about tp? */
    li      t0, BAO_CPU_BASE
    li      sp, CPU_STACK_OFF + CPU_STACK_SIZE
    add     sp, t0, sp

    .option push
    .option norelax
    la  gp, __global_pointer$
    .option pop

    /* clear bss if hart 0 */
    LD_SYM  t0, CPU_MASTER
    bne     a0, t0, wait_for_bsp_2
    la      a3, _bss_start_sym
    LOAD    a3, 0(a3)
    la      a4, _bss_end_sym
    LOAD    a4, 0(a4)
    call    clear

    fence   w, w
    la  t0, _barrier
    li  t1, 2
    STORE  t1, 0(t0)

wait_for_bsp_2:
    /* wait for hart 0 to finish clearing bss */
    la  t0, _barrier
    li  t1, 2
1:
    LOAD  t2, 0(t0)
    blt t2, t1, 1b

    j   init

	/* This point should never be reached */
	j	.	

clear:
    sb  zero, 0(a3)
    add a3, a3, 1
    blt a3, a4, clear
    ret
