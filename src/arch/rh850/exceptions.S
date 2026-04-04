/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <asm_defs.h>
#include <arch/vmm.h>

.text

.macro VM_EXIT

    ldsr r31, 28, 0 /* use EIWR as scratchpad */

    /* save program registers in vcpu struct */
    stsr 29, r31, 0                /* get cpu* from FEWR */
    ld.w CPU_VCPU_OFF[r31], r31    /* get vcpu* */
    add VCPU_REGS_OFF, r31
    st.w  r1,  4[r31]
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

    /**
     * Save PC from EIPC or FEPC depending on the exception type
     * r30: vcpu register struct base address
     * uses r20
     */
    stsr 5, r20, 0
    andi 0x80, r20, r20
    cmp r0, r20
    be 1f
    stsr 2, r20, 0    /* FEPC */
    br 2f
1:
    stsr 0, r20, 0    /* EIPC */
2:
    st.w r20, 128[r30]

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
    ld.w CPU_VCPU_OFF[r30], r30
    add VCPU_REGS_OFF, r30

    /**
     * Restore PC to EIPC or FEPC depending on the exception type
     * r30: vcpu register struct base address
     * uses r20 and r21
     */
    ld.w 128[r30], r20
    stsr 5, r21, 0
    andi 0x80, r21, r21
    cmp r0, r21
    be 1f
    ldsr r20, 2, 0     /* set FEPC */
    br 2f
1:
    ldsr r20, 2, 0     /* set EIPC */
2:
    mov r30, r31

    ld.w  4[r31], r1
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
    ld.w 120[r31], r30

    /* uses EIWR as scratchpad register */
    ld.w 124[r31], r31
    ldsr r31, 28, 0

    /**
     * read PSW and execute eiret or feret depending on the exception type
     * and restores r31 from EIWR
     */
    stsr 5, r31, 0
    andi 0x80, r31, r31
    cmp r0, r31
    be 1f
    stsr 28, r31, 0
    feret
1:
    stsr 28, r31, 0
    eiret
.endm


.balign 0x200
.global _hyp_vector_table
_hyp_vector_table:
    br    .                   /* RESET */

    .balign 0x10
    br    _guest_exception    /* SYSERR */

    .balign 0x10
    br    _guest_exception,   /* HVTRAP */

    .balign 0x10
    br    _guest_exception    /* FETRAP */

    .balign 0x10
    br    _guest_exception    /* TRAP0 */

    .balign 0x10
    br    _guest_exception    /* TRAP1 */

    .balign 0x10
    br    _host_exception     /* RIE */

    .balign 0x10
    br    _host_exception     /* FPE/FXE */

    .balign 0x10
    br    _host_exception     /* UCPOP */

    .balign 0x10
    br    _guest_exception    /* MIP/MDP */

    .balign 0x10
    br    _host_exception     /* PIE */

    .balign 0x10
    br    _host_exception     /* R.F.U. */

    .balign 0x10
    br    _host_exception     /* MAE */

    .balign 0x10
    br    _host_exception     /* BGFEINT/BGEIINT */

    .balign 0x10
    br    _host_exception,    /* FENMI */

    .balign 0x10
    br    _host_exception     /* FEINT/GMFEINT */

    /* only used with direct vector method */
    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority0) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority1) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority2) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority3) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority4) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority5) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority6) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority7) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority8) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority9) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority10) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority11) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority12) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority13) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority14) */

    .balign 0x10
    br    _Interrupt_EI       /* INTn(priority15) */


_guest_exception:
    VM_EXIT
    jarl abort, lp
    VM_ENTRY

_host_exception:
    jarl internal_abort, lp

_Interrupt_EI:
    VM_EXIT

    /* copy int_id to r6 */
    stsr 13, r6, 0    /* EIIC (TODO: FEIC) */
    mov 0x7FF, r20
    and r20, r6

    jarl interrupts_handle, lp

.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
