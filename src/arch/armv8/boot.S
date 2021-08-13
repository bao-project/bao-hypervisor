/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Gero Schwaericke <gero.schwaericke@tum.de>
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
	 * TODO: before anything...
	 * perform sanity checks on ID registers to ensure support for
	 * VE and TZ, 4K granule and possibly other needed features. 
	 * Also, check current exception level. Act accordingly. 
	 * However, we expect to be running at EL2 at this point.
	 */

	/**
	 * Not following any ABI for registers in this boot code.
	 * The following registers are however reserved to be passed to main
	 * as arguments:
	 * 		x0 -> contains cpu id
	 *		x1 -> contains image base load address
	 *		x2 -> contains config binary load address (passed in x0) 
	 * Register x9 is reserved to indicate if the current cpu is master (negated)
	 */

	mov x2, x0
	mrs  x0, MPIDR_EL1
	adrp x1, _image_start

	/* 
	 * Install vector table physical address early, in case exception occurs
	 * during this initialization.
	 */
	adr	x3, _hyp_vector_table
	msr	VBAR_EL2, x3

	/**
	 * 	Linearize cpu id according to the number of clusters and processors per
	 * cluster. We are only considering two levels of affinity.
	 *  TODO: this should be done some other way. We shouln'd depend on the platform
	 * description this early in the initialization.
	 */

	mov x3, x0, lsr #8 
	and x3, x3, 0xff
	adr x4, platform
	ldr x4, [x4, PLAT_ARCH_OFF+PLAT_ARCH_CLUSTERS_OFF+PLAT_CLUSTERS_CORES_NUM_OFF]
	ldr x5, =BAO_VAS_BASE
	sub x4, x4, x5
	add x4, x4, x1
	mov x5, xzr
	mov x7, xzr
1:
	cmp x5, x3
	b.ge	2f
	ldrb w6, [x4]
	add x4, x4, #1
	add x5, x5, #1
	add x7, x7, x6
	b 	1b
2:
	and x0, x0, #0xff
	add x0, x0, x7

.pushsection .data
_master_set:
	.8byte 	0
.popsection
/**
 * For setting the master cpu, we assume only one cpu is initially activated 
 * which later will turn on all the others. Therefore, there is no concurrency 
 * when setting CPU_MASTER and no atomic operations are needed.
 * As a result x9 should be set to !is_cpu_master
 */
_set_master_cpu:
	adr	x3, _master_set
	ldr x9, [x3]
	cbnz x9, 7f
	mov	x9, #1
	str x9, [x3]
	mov x9, xzr
	adr x3, CPU_MASTER
	str x0, [x3]
7: 

	/** 
	 * TODO: bring the system to a well known state. This includes disabling 
	 * the MMU (done), all caches (missing i$), BP and others...
	 * and invalidating them.	
	 */
 
	/* Clear stack pointer to avoid unaligned SP exceptions during boot */
    mov x3, xzr
	mov sp, x3

	/* Disable caches and MMU */
	mrs x3, SCTLR_EL2 
	bic x3, x3, #0x7	
	msr SCTLR_EL2, x3 

	/* Invalidate caches */
	/* Should we also clean ? */
	mov x19, x0
	mov x20, x1
	mov x21, x2

	mov x0, #0
	bl	cache_invalidate
	cbnz x9, 1f
	mov x0, #2
	bl	cache_invalidate
1:
	mov x0,	x19
	mov x1,	x20
	mov x2,	x21

	ic iallu

	/* Skip initialy global page tables setup if not bsp (boot cpu) */
	cbnz	x9, wait_for_bsp

	adr	x16, _page_tables_start	
	adr	x17, _page_tables_end	
	bl	clear				

	/* Set temporary flat mapping to switch to VAS. */

	adr x4, root_l1_flat_pt
	PTE_INDEX_ASM x5, x1, 1 
	add x6, x1, #(PTE_HYP_FLAGS | PTE_SUPERPAGE)
	str x6, [x4, x5]
	
	/* Set global root mappings for hypervisor image */

	adr x4, root_l1_pt
	ldr x5, =(PTE_INDEX(1, BAO_VAS_BASE)*8)
	adr x6, root_l2_pt
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	adr x4, root_l2_pt
	ldr x5, =(PTE_INDEX(2, BAO_VAS_BASE)*8)
	adr x6, root_l3_pt
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	adr x4, root_l3_pt
	ldr x7, =_image_start
	ldr x8, =_image_end
	adr x6, _image_start
	add x6, x6, #(PTE_HYP_FLAGS | PTE_PAGE)
1:
	cmp	x7, x8
	b.ge 2f
	//lsr x5, x7, #(PTE_INDEX_SHIFT(3)-3)
	PTE_INDEX_ASM x5, x7, 3
	str x6, [x4, x5]
	add x6, x6, #PAGE_SIZE
	add x7, x7, #PAGE_SIZE
	b	1b
2:
	adr x5, _barrier
	mov x4, #1
	str x4, [x5]
	//	dsb // arguments?
	sev
	b 	map_cpu

wait_for_bsp:	
/* wait fot the bsp to finish up global mappings */
	wfe
	ldr x4, _barrier
	cmp x4, #1
	b.lt wait_for_bsp

map_cpu:
	/**
	 *    x3 -> cpu base phys
	 *    x4 -> current pt base phys
	 *    x5 -> pte index
	 *    x6 -> phys addr
	 *    x7 -> virt addr
	 *    x8 -> aux 
	 */

	/* get cpu root pt */
	mov x8, #(CPU_SIZE + (PT_SIZE*(PT_LVLS-1)))
	adrp x3, _dmem_phys_beg
	madd x3, x0, x8, x3
	
	mov	x16, x3	
	add	x17, x3, x8
	bl	clear	

	/* Get pointer to root page table */
	add x4, x3, #CPU_ROOT_PT_OFF

	/* map original bootstrap flat mappings */
	PTE_INDEX_ASM x5, x1, 0 
	adr x6, root_l1_flat_pt
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]
	
	ldr x5, =(PTE_INDEX(0, BAO_VAS_BASE)*8)
	adr x6, root_l1_pt
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	ldr x5, =(PTE_INDEX(0, BAO_CPU_BASE)*8)
	//add x6, x4, #PT_SIZE
    add x6, x3, #CPU_SIZE
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	//add x4, x4, #PT_SIZE
    add x4, x3, #CPU_SIZE
	ldr x5, =(PTE_INDEX(1, BAO_CPU_BASE)*8)
	add x6, x4, #PT_SIZE
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	add x4, x4, #PT_SIZE
	ldr x5, =(PTE_INDEX(2, BAO_CPU_BASE)*8)
	add x6, x4, #PT_SIZE
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x6, [x4, x5]

	add x4, x4, #PT_SIZE
	ldr x7, =BAO_CPU_BASE
	add x8, x7, #CPU_SIZE
	mov x6, x3
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)
1:
	cmp	x7, x8
	b.ge map_cpu_interface
	PTE_INDEX_ASM x5, x7, 3
	str x6, [x4, x5]
	add x6, x6, #PAGE_SIZE
	add x7, x7, #PAGE_SIZE
	b	1b

map_cpu_interface:

	adr x4, root_l3_pt

	add x6, x3, #CPU_IF_OFF
	add x6, x6, #(PTE_HYP_FLAGS | PTE_TABLE)

	mov x8, #CPU_IF_SIZE
	ldr x7, =_dmem_beg
	madd x7, x0, x8, x7
	add x8, x8, x7

1:
	cmp	x7, x8
	b.ge setup_cpu
	PTE_INDEX_ASM x5, x7, 3 
	str x6, [x4, x5]

	add x7, x7, #PAGE_SIZE
	add x6, x6, #PAGE_SIZE

	b 1b

setup_cpu:

	/**
	 * 	The operation is purposely commented out.
	 *  We are assuming monitor code already enabled smp coherency.
	 */ 
	/* Turn on smp coherence */
	//mrs	x3, CPUECTLR_EL1  	
	//orr	x3, x3, #(CPUECTLR_SPEN_BIT)
	//msr	CPUECTLR_EL1, x3 

	mov x3, xzr
	msr CPTR_EL2, x3

	/* setup translation configurations */
	ldr x3, =TCR_EL2_DFLT
	msr	TCR_EL2, x3

	/* set hypervisor default memory attributes */
	ldr x3, =MAIR_EL2_DFLT
	msr	MAIR_EL2, x3

	mov x8, #(CPU_SIZE + (PT_SIZE*(PT_LVLS-1)))
	adrp x3, _dmem_phys_beg
	madd x3, x0, x8, x3
	add x3, x3, #CPU_ROOT_PT_OFF
	msr TTBR0_EL2, x3

	/* set up cpu stack */
	mov x3, #(SPSel_SP)								
	msr SPSEL, x3	
	ldr x3, =cpu
	add x3, x3, #(CPU_STACK_OFF + CPU_STACK_SIZE)
	mov SP, x3

	/**	
	 * TODO: set implementation defined registers such as ACTLR or AMAIR.
	 * Maybe define a macro for this in a implementation oriented directory
	 * inside arch.
	 */

	/**
	 * TODO: invalidate caches, TLBs and branch prediction.
	 * Need for barriers?
	 */

	ldr x5, =_enter_vas

	/* Enable MMU and caches */
	ldr x4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	msr	SCTLR_EL2, x4
	
	tlbi	alle2
	dsb	nsh
	isb
	
	br  x5

_enter_vas:

	/* Install vector table virtual address*/
	ldr	x3, =_hyp_vector_table
	msr	VBAR_EL2, x3

	/* Remove temporary mapping - the L1 page holding it leaks */
	ldr x4, =cpu
	add x4, x4, #CPU_ROOT_PT_OFF
	PTE_INDEX_ASM x5, x1, 0 
	str xzr, [x4, x5]

    tlbi	alle2
	dsb	nsh
	isb

	/* If this is bsp (cpu 0) clear bss */
	cbnz x9, 1f
	ldr	x16, =_bss_start	
	ldr	x17, =_bss_end	
	bl	clear	

	adr x5, _barrier
	mov x4, #2
	str x4, [x5]	

1:
	/* wait for bsp to finish clearing bss */
	ldr x4, _barrier
	cmp x4, #2
	b.lt 1b

	isb

	b init

	/* This point should never be reached */
	b	.				

/***** 	Helper functions for boot code. ******/

 .func clear
clear:
2:
	cmp	x16, x17			
	b.ge 1f				
	str	xzr, [x16], #8	
	b	2b				
1:
	ret
.endfunc

/*
 * Code taken from "Application Note Bare-metal Boot Code for ARMv8-A
 * Processors - Version 1.0"
 *
 * x0 - cache level to be invalidated (0 - dl1$, 1 - il1$, 2 - l2$)
 */
.func cache_invalidate
cache_invalidate:
	msr csselr_el1, x0 
	mrs x4, ccsidr_el1 // read cache size id.
	and x1, x4, #0x7
	add x1, x1, #0x4 // x1 = cache line size.
	ldr x3, =0x7fff
	and x2, x3, x4, lsr #13 // x2 = cache set number – 1.
	ldr x3, =0x3ff
	and x3, x3, x4, lsr #3 // x3 = cache associativity number – 1.
	clz w4, w3 // x4 = way position in the cisw instruction.
	mov x5, #0 // x5 = way counter way_loop.
way_loop:
	mov x6, #0 // x6 = set counter set_loop.
set_loop:
	lsl x7, x5, x4
	orr x7, x0, x7 // set way.
	lsl x8, x6, x1
	orr x7, x7, x8 // set set.
	dc cisw, x7 // clean and invalidate cache line.
	add x6, x6, #1 // increment set counter.
	cmp x6, x2 // last set reached yet?
	ble set_loop // if not, iterate set_loop,
	add x5, x5, #1 // else, next way.
	cmp x5, x3 // last way reached yet?
	ble way_loop // if not, iterate way_loop
	ret
.endfunc


.global psci_boot_entry
.func psci_boot_entry
psci_boot_entry:
warm_boot:

	adr	x3, _hyp_vector_table
	msr	VBAR_EL2, x3

	/* save x0 which contains pointer to saved state psci context */
	mov x19, x0
    	/* invalidate l1$ */
	mov x0, #0
	bl	cache_invalidate

	/* restore all needed register state */
	ldp x5, x6, [x19, #0]
	msr TCR_EL2, x5
	msr TTBR0_EL2, x6
	ldp x5, x6, [x19, #16]
	msr MAIR_EL2, x5
	msr CPTR_EL2, x6
	ldp x5, x6, [x19, #32]
	msr HCR_EL2, x5
	msr VMPIDR_EL2, x6
	ldp x5, x6, [x19, #48]
	msr VTCR_EL2, x5
	msr VTTBR_EL2, x6
    ldp x0, x5, [x19, #64]   /* wake up reason is the arg of the later psci_wake call */

	/* map original bootstrap flat mappings */
	mrs x3, TTBR0_EL2
	adrp x1, _image_start
	PTE_INDEX_ASM x1, x1, 0 
	add x3, x3, x1
	dc civac, x3  //we invalidated l1$, but make sure the pte is not in l2$
	add x5, x5, #(PTE_HYP_FLAGS | PTE_TABLE)
	str x5, [x3]

	/* Install vector table virtual address*/
	ldr	x3, =_hyp_vector_table
	msr	VBAR_EL2, x3

    tlbi	alle2 
	dsb	nsh
	isb

	/* Enable MMU and caches */
	ldr x4, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
	msr	SCTLR_EL2, x4

	dsb	nsh
	isb
	
	ldr x5, =_enter_vas_warm
	br  x5		

_enter_vas_warm:
	/* Unmap bootstrat flat mappings */
	ldr x4, =cpu
	add x3, x4, #(CPU_STACK_OFF+CPU_STACK_SIZE)

	add x4, x4, #CPU_ROOT_PT_OFF
	PTE_INDEX_ASM x5, x1, 0 
	str xzr, [x4, x5]
    tlbi	alle2
	dsb	nsh
	isb

    /* Initialize stack pointer */
    mov sp, x3

	bl	psci_wake
	b 	.

.endfunc
