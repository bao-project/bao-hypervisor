/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <asm_defs.h>

.text

.macro VM_EXIT

	/* set SPID to HYP_SPID */
	ldsr r31, 28, 0 /* use EIWR as scratchpad */
	mov 0x0, r31	/* HYP_SPID (TODO: use macro) */
	ldsr r31, 0, 1

	/* save program registers in vcpu struct */
    stsr 29, r31, 0				/* get cpu* from FEWR */
    addi CPU_VCPU_OFF, r31, r31	/* CPU_VCPU_OFF */
    ld.w 0[r31], r31			/* get vcpu* */
    add VCPU_REGS_OFF, r31
    st.dw r0,  0[r31]
    st.dw r2,  8[r31]
    st.dw r4,  16[r31]
    st.dw r6,  24[r31]
    st.dw r8,  32[r31]
    st.dw r10, 40[r31]
    st.dw r12, 48[r31]
    st.dw r14, 56[r31]
    st.dw r16, 64[r31]
    st.dw r18, 72[r31]
    st.dw r20, 80[r31]
    st.dw r22, 88[r31]
    st.dw r24, 96[r31]
    st.dw r26, 104[r31]
    st.dw r28, 112[r31]
    st.w r30, 120[r31]

    mov r31, r30
    stsr 28, r31, 0
    st.w r31, 124[r30]

	/* save PC */
	jarl _save_pc, lp

	/* restore stack pointer */
	stsr 29, r20, 0
    mov CPU_STACK_OFF, r21
    add r21, r20
    mov CPU_STACK_SIZE, r21
    add r21, r20
    mov r20, sp
.endm

.macro VM_ENTRY
	/* load vcpu registers from memory */
    stsr 29, r30, 0
    addi CPU_VCPU_OFF, r30, r30
    ld.w 0[r30], r30
    add VCPU_REGS_OFF, r30

	/* restore PC */
	jarl _restore_pc, lp
	mov r30, r31

    ld.dw 0[r31], r0
    ld.dw 8[r31], r2
    ld.dw 16[r31], r4
    ld.dw 24[r31], r6
    ld.dw 32[r31], r8
    ld.dw 40[r31], r10
    ld.dw 48[r31], r12
    ld.dw 56[r31], r14
    ld.dw 64[r31], r16
    ld.dw 72[r31], r18
    ld.dw 80[r31], r20
    ld.dw 88[r31], r22
    ld.dw 96[r31], r24
    ld.dw 104[r31], r26
    ld.dw 112[r31], r28
    ld.dw 120[r31], r30

	/* set SPID to VM_SPID */
	ldsr r31, 28, 0
	mov 0x1, r31 	/* VM_SPID (TODO: use macro) */
	ldsr r31, 0, 1

	/* the instructions below should not trigger any MIP exception, 
	as all the hypervisor code belongs to an MPU entry with RG = 1 */

	/* select ret instruction */
	br _select_xxret
.endm

/**
 * Save PC from EIPC or FEPC depending on the exception type
 * r30: vcpu register struct base address
 * uses r20
 */
_save_pc:
	stsr 5, r20, 0
	andi 0x80, r20, r20
	cmp r0, r20
	be _save_ei
	stsr 2, r20, 0	/* FEPC */
	br _save_pc_exit
_save_ei:
	stsr 0, r20, 0	/* EIPC */
_save_pc_exit:
	st.w r20, 128[r30]
	jmp [lp]

/**
 * Restore PC to EIPC or FEPC depending on the exception type
 * r30: vcpu register struct base address
 * uses r20 and r21
 */
_restore_pc:
	ld.w 128[r30], r20
	stsr 5, r21, 0
	andi 0x80, r21, r21
	cmp r0, r21
	be _restore_ei
	ldsr r20, 2, 0 	/* set FEPC */
	br _restore_pc_exit
_restore_ei:
	ldsr r20, 2, 0 	/* set EIPC */
_restore_pc_exit:
	jmp [lp]

/**
 * Execute eiret or feret depending on the exception type
 * uses r31
 */
_select_xxret:
	stsr 5, r31, 0
	andi 0x80, r31, r31
	cmp r0, r31
	be _ei_ret
	stsr 28, r31, 0
    feret
_ei_ret:
	stsr 28, r31, 0
	eiret

.balign 0x200
.global _hyp_vector_table
_hyp_vector_table:
	br	.

	.balign 0x10
	syncp
	br	_guest_exception	/* SYSERR ; Guest */

	.balign 0x10
	br	_guest_exception,	/* HVTRAP; Guest */

	.balign 0x10
	br	_guest_exception	/* FETRAP ; Guest? */

	.balign 0x10
	br	_guest_exception	/* TRAP0 ; Guest? */

	.balign 0x10
	br	_guest_exception	/* TRAP1 ; Guest? */

	.balign 0x10
	br	_host_exception		/* RIE */

	.balign 0x10
	syncp
	br	_host_exception		/* FPP/FPI */

	.balign 0x10
	br	_host_exception		/* UCPOP */

	/* TODO: Dfferentiate between MIP/MDP guest and hyp exceptions */
	.balign 0x10
	br	_guest_exception	/* MIP/MDP ; Guest */

	.balign 0x10
	br	_host_exception		/* RIE */

	.balign 0x10
	br	_host_exception		/* PIE */

	.balign 0x10
	br	_host_exception		/* MAE */

	.balign 0x10
	br	_host_exception		/* UCPOP */

	.balign 0x10
	syncp
	br	_host_exception,	/* FENMI */

	.balign 0x10
	syncp
	br	_host_exception		/* FEINT */

	/* only used with direct vector method */
	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority0) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority1) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority2) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority3) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority4) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority5) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority6) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority7) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority8) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority9) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority10) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority11) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority12) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority13) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority14) */

	.balign 0x10
	syncp
	br	_Interrupt_EI		/* INTn(priority15) */

/* only used with table reference method */
.balign	0x200
.global _hyp_interrupt_table
_hyp_interrupt_table:
	.long	_Interrupt_EI 	/* INT0 */
	.long	_Interrupt_EI 	/* INT1 */
	.long	_Interrupt_EI 	/* INT2 */
	.rept	2048 - 3
	.long	_Interrupt_EI 	/* INTn */
	.endr

_guest_exception: 

    VM_EXIT
    jarl abort, lp
    VM_ENTRY

_host_exception:
	br	_host_exception

_Interrupt_EI:

    VM_EXIT
	
	/* copy int_id to r6 */
	stsr 13, r6, 0	/* EIIC (TODO: FEIC ?) */
	mov 0x7FF, r20
	and r20, r6

    jarl interrupts_handle, lp

.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
