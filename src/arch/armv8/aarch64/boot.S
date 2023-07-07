/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>
#include <config_defs.h>
#include <platform_defs.h>

.data
.align 3
/**
 * barrier is used to minimal synchronization in boot - other cores wait for
 * bsp to set it.
 */
 .global _boot_barrier
_boot_barrier: .8byte 0

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
	 * Register x9 is reserved to indicate if the current cpu is master (negated).
	 * Register x1 is reserved to contain the cpu root page table address.
	 */

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
	 *  TODO: this should be done some other way. We shouldn't depend on the platform
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
#if PLAT_CLUSTERS_CORES_NUM_SIZE != 8
#error "struct platform cluster core_num field type size is not 8"
#endif
	ldr w6, [x4]
	add x4, x4, #PLAT_CLUSTERS_CORES_NUM_SIZE
	add x5, x5, #1
	add x7, x7, x6
	b 	1b
2:
	and x0, x0, #0xff
	add x0, x0, x7

/* Setting x9 should if set !is_cpu_master */
#if defined(CPU_MASTER_FIXED)
   mov x3, CPU_MASTER_FIXED
   cmp x0, x3
   cset x9, ne
   cbnz x9, 1f
#else
/**
 * If the cpu master is not fixed, for setting it, we assume only one cpu is
 * initially activated which later will turn on all the others. Therefore, there
 * is no concurrency when setting CPU_MASTER and no atomic operations are needed.
 */
 .pushsection .data
_master_set:
	.8byte 	0
.popsection
	mov x5, #1
	adr	x3, _master_set
_set_master_cpu:
	ldr w9, [x3]
	cbnz w9, 1f
	str w5, [x3]
#endif
	adr x3, CPU_MASTER
	str x0, [x3]
1:

	/**
	 * TODO: bring the system to a well known state. This includes disabling
	 * the MMU (done), all caches (missing i$), BP and others...
	 * and invalidating them.
	 */

	/* boot_clear stack pointer to avoid unaligned SP exceptions during boot */
	mov x3, xzr
	mov sp, x3

	/* Invalidate caches */
	/* Should we also clean ? */
	mov x19, x0
	mov x20, x1

	mov x0, #0
	bl	boot_cache_invalidate
	cbnz x9, 1f
	mov x0, #2
	bl	boot_cache_invalidate
1:
	mov x0,	x19
	mov x1,	x20

	ic iallu

	bl boot_arch_profile_init

	mov x3, xzr
	msr CPTR_EL2, x3

	/* set up cpu stack */
	mov x3, SPSel_SP
	msr SPSEL, x3
	mrs x3, tpidr_el2
	ldr x4, =(CPU_STACK_OFF + CPU_STACK_SIZE)
	add x3, x3, x4
	mov SP, x3


	/* If this is bsp (cpu 0) boot_clear bss */
	cbnz x9, 1f
	ldr	x16, =_bss_start
	ldr	x17, =_bss_end
	bl	boot_clear

	adr x5, _boot_barrier
	mov x4, #2
	stlr x4, [x5]

1:
	/* wait for bsp to finish boot_clearing bss */
	ldr x4, =_boot_barrier
2:
	ldar x5, [x4]
	cmp x5, #2
	b.lt 2b

	isb

	b init

	/* This point should never be reached */
	b	.

/***** 	Helper functions for boot code. ******/

.global boot_clear
.func boot_clear
boot_clear:
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
.global boot_cache_invalidate
.func boot_cache_invalidate
boot_cache_invalidate:
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


