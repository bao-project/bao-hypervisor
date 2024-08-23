/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/csfrs.h>

#define ENTRY_SIZE   (0x20)

.text 

.macro SAVE_HYP_GPRS
    st.w [%a10]0x0, %d0
    st.w [%a10]0x4, %d1
    st.w [%a10]0x8, %d2
    st.w [%a10]0xc, %d3
    st.w [%a10]0x10, %d4
    st.w [%a10]0x14, %d5
    st.w [%a10]0x18, %d6
    st.w [%a10]0x1c, %d7
    st.w [%a10]0x20, %d8
    st.w [%a10]0x24, %d9
    st.w [%a10]0x28, %d10
    st.w [%a10]0x2c, %d11
    st.w [%a10]0x30, %d12
    st.w [%a10]0x34, %d13
    st.w [%a10]0x38, %d14
    st.w [%a10]0x3c, %d15

    st.a [%a10]0x40, %a0
    st.a [%a10]0x44, %a1
    st.a [%a10]0x48, %a2
    st.a [%a10]0x4c, %a3
    st.a [%a10]0x50, %a4
    st.a [%a10]0x54, %a5
    st.a [%a10]0x58, %a6
    st.a [%a10]0x5c, %a7
    st.a [%a10]0x60, %a8
    st.a [%a10]0x64, %a9
    mov.d %d0, %a10
    mov.a %a9, %d0
    st.a [%a10]0x68, %a9
    st.a [%a10]0x6c, %a11
    st.a [%a10]0x70, %a12
    st.a [%a10]0x74, %a13
    st.a [%a10]0x78, %a14
    st.a [%a10]0x7c, %a15
.endm

.macro GET_CPU_PTR
    movh    %d9,hi:_dmem_phys_beg
    addi    %d9,%d9,lo:_dmem_phys_beg

    mfcr    %d8,$core_id
    and     %d8,%d8,7
    /* CPU_X physical base address */
    mov     %d10, CPU_SIZE
    madd    %d8, %d9, %d8, %d10
    mov.a   %a10, %d0
.endm

.macro GET_VCPU_REG_PTR
    GET_CPU_PTR

    ld.a    %a10, [%a10] CPU_VCPU_OFF
    mov.a   %a11, VCPU_REGS_OFF
    add.a   %a10, %a11
.endm

.macro SET_SP
    GET_CPU_PTR

    ld.a    %a10, [%a10] CPU_STACK_OFF
    mov     %d9, CPU_STACK_SIZE
    mov.a   %a11, %d9
    add.a   %a10, %a11
.endm

.macro VM_EXIT
    GET_VCPU_REG_PTR

    /* save unsave regs */
    st.w [%a10]0x0, %d0
    st.w [%a10]0x4, %d1
    st.w [%a10]0x8, %d2
    st.w [%a10]0xc, %d3
    st.w [%a10]0x10, %d4
    st.w [%a10]0x14, %d5
    st.w [%a10]0x18, %d6
    st.w [%a10]0x1c, %d7

    st.a [%a10]0x40, %a0 // not saved
    st.a [%a10]0x44, %a1 // not saved
    st.a [%a10]0x48, %a2 // Lower Ctx
    st.a [%a10]0x4c, %a3 // Lower Ctx
    st.a [%a10]0x50, %a4 // Lower Ctx
    st.a [%a10]0x54, %a5 // Lower Ctx
    st.a [%a10]0x58, %a6 // Lower Ctx
    st.a [%a10]0x5c, %a7 // Lower Ctx
    st.a [%a10]0x60, %a8 // not saved
    st.a [%a10]0x64, %a9 // not saved


    /* TODO how to handle first exit? a CSA needs to be allocated ? */
    /* Save remaining regs from upper context CSA */
    mfcr %d0, csfr_pcx
    mov.a %a12, %d0

    ld.a  %a13, [%a12]0x8
    st.a [%a10]0x68, %a13 /* Guest a10 */

    ld.a  %a13, [%a12]0xc
    st.a [%a10]0x6c, %a13 /* Guest a11 */

    ld.a  %a13, [%a12]0x10
    st.a [%a10]0x20, %a13 /* Guest d8 */

    ld.a  %a13, [%a12]0x14
    st.a [%a10]0x24, %a13 /* Guest d9 */

    ld.a  %a13, [%a12]0x18
    st.a [%a10]0x28, %a13 /* Guest d10 */

    ld.a  %a13, [%a12]0x1c
    st.a [%a10]0x2c, %a13 /* Guest d11 */

    ld.a  %a13, [%a12]0x20
    st.a [%a10]0x70, %a13 /* Guest a12 */

    ld.a  %a13, [%a12]0x24
    st.a [%a10]0x74, %a13 /* Guest a13 */

    ld.a  %a13, [%a12]0x28
    st.a [%a10]0x78, %a13 /* Guest a14 */

    ld.a  %a13, [%a12]0x2c
    st.a [%a10]0x7c, %a13 /* Guest a15 */

    ld.a  %a13, [%a12]0x30
    st.a [%a10]0x80, %a13 /* Guest a16 */

    ld.a  %a13, [%a12]0x34
    st.a [%a10]0x30, %a13 /* Guest d12 */

    ld.a  %a13, [%a12]0x38
    st.a [%a10]0x34, %a13 /* Guest d13 */

    ld.a  %a13, [%a12]0x3c
    st.a [%a10]0x38, %a13 /* Guest d14 */

    ld.a  %a13, [%a12]0x40
    st.a [%a10]0x3c, %a13 /* Guest d15 */

    SET_SP
.endm

.macro VM_ENTRY

    GET_VCPU_REG_PTR

    /* restore unsave regs */
    ld.w %d0, [%a10]0x0
    ld.w %d1, [%a10]0x4
    ld.w %d2, [%a10]0x8
    ld.w %d3, [%a10]0xc
    ld.w %d4, [%a10]0x10
    ld.w %d5, [%a10]0x14
    ld.w %d6, [%a10]0x18
    ld.w %d7, [%a10]0x1c

    ld.a %a0, [%a10]0x40
    ld.a %a1, [%a10]0x44
    ld.a %a2, [%a10]0x48
    ld.a %a3, [%a10]0x4c
    ld.a %a4, [%a10]0x50
    ld.a %a5, [%a10]0x54
    ld.a %a6, [%a10]0x58
    ld.a %a7, [%a10]0x5c
    ld.a %a8, [%a10]0x60
    ld.a %a9, [%a10]0x64


    /* restore remaining regs to upper context CSA */
    mfcr %d9, csfr_pcx
    mov.a %a12, %d9

    ld.a  %a13, [%a10]0x68 /* Guest a10 */
    st.a  [%a12]0x8, %a13

    ld.a %a13, [%a10]0x6c /* Guest a11 */
    st.a  [%a12]0xc, %a13

    ld.a %a13, [%a10]0x20 /* Guest d8 */
    st.a  [%a12]0x10, %a13

    ld.a %a13, [%a10]0x24 /* Guest d9 */
    st.a  [%a12]0x14, %a13

    ld.a %a13, [%a10]0x28 /* Guest d10 */
    st.a  [%a12]0x18, %a13

    ld.a %a13, [%a10]0x2c /* Guest d11 */
    st.a  [%a12]0x1c, %a13

    ld.a %a13, [%a10]0x70 /* Guest a12 */
    st.a  [%a12]0x20, %a13

    ld.a %a13, [%a10]0x74 /* Guest a13 */
    st.a  [%a12]0x24, %a13

    ld.a %a13, [%a10]0x78 /* Guest a14 */
    st.a  [%a12]0x28, %a13

    ld.a %a13, [%a10]0x7c /* Guest a15 */
    st.a  [%a12]0x2c, %a13

    ld.a %a13, [%a10]0x30 /* Guest d12 */
    st.a  [%a12]0x30, %a13

    ld.a %a13, [%a10]0x34 /* Guest d13 */
    st.a  [%a12]0x34, %a13

    ld.a %a13, [%a10]0x38 /* Guest d14 */
    st.a  [%a12]0x38, %a13

    ld.a %a13, [%a10]0x3c /* Guest d15 */
    st.a  [%a12]0x3c, %a13

    ld.a %a11, [%a10]0x80 /* address to return to */

    rfh

1:
    j   1b
.endm


.balign 0x100
.global _trap_vector_table
_trap_vector_table:

.balign ENTRY_SIZE
mmu_trap:
    j	mmu_trap_handler

.balign ENTRY_SIZE
internal_protection_trap:
    j   internal_protection_trap_handler

.balign ENTRY_SIZE
instruction_error:
    j	instruction_error_handler

.balign ENTRY_SIZE
ctx_mgnt:
    j	ctx_mgnt_handler

.balign ENTRY_SIZE
sys_bus_errors:
    j	sys_bus_errors_handler

.balign ENTRY_SIZE
assertion_trap:
    j	assertion_trap_handler

.balign ENTRY_SIZE
system_call:
    j	system_call_handler

.balign ENTRY_SIZE
non_mskbl_interrupt:
    j	non_mskbl_interrupt_handler



.balign 0x100
.global _irq_vector
_irq_vector:
    .rept   255
        .balign ENTRY_SIZE
        1:
            /* TODO */
            j 1b
    .endr



.balign 0x100
.global _hyp_vector_table
_hyp_vector_table:

.balign ENTRY_SIZE
hyp_call:
    j   hyp_call_handler

.balign ENTRY_SIZE
hyp_interrupt_trap:
    j   hyp_interrupt_trap_handler

.balign ENTRY_SIZE
l2_data_mem_prot_trap:
    j	l2_data_mem_prot_trap_handler

.balign ENTRY_SIZE
l2_code_mem_prot_trap:
    j	l2_code_mem_prot_trap_handler

.balign ENTRY_SIZE
hyp_csfr_access_supp:
    j	hyp_csfr_access_supp_handler




/* Internal */
.global mmu_trap_handler
mmu_trap_handler:
    SAVE_HYP_GPRS
    j mmu_trap_handler

.global internal_protection_trap_handler
internal_protection_trap_handler:
    SAVE_HYP_GPRS
    j internal_protection_trap_handler

.global instruction_error_handler
instruction_error_handler:
    SAVE_HYP_GPRS
    j instruction_error_handler

.global ctx_mgnt_handler
ctx_mgnt_handler:
    SAVE_HYP_GPRS
    j ctx_mgnt_handler

.global sys_bus_errors_handler
sys_bus_errors_handler:
    SAVE_HYP_GPRS
    j sys_bus_errors_handler

.global assertion_trap_handler
assertion_trap_handler:
    SAVE_HYP_GPRS
    j assertion_trap_handler

.global system_call_handler
system_call_handler:
    SAVE_HYP_GPRS
    j system_call_handler

.global non_mskbl_interrupt_handler
non_mskbl_interrupt_handler:
    SAVE_HYP_GPRS
    j non_mskbl_interrupt_handler

.global _irq_handler
_irq_handler:
    VM_EXIT
    j ir_handle
    VM_ENTRY


/* Virtualization Related */
.global hyp_call_handler
hyp_call_handler:
    VM_EXIT
    j hyp_call_handler
    VM_ENTRY

.global hyp_interrupt_trap_handler
hyp_interrupt_trap_handler:
    VM_EXIT
    j hyp_interrupt_trap_handler
    VM_ENTRY

.global l2_data_mem_prot_trap_handler
l2_data_mem_prot_trap_handler:
    VM_EXIT
    j l2_data_mem_prot_trap_handler
    VM_ENTRY

.global l2_code_mem_prot_trap_handler
l2_code_mem_prot_trap_handler:
    VM_EXIT
    j l2_code_mem_prot_trap_handler
    VM_ENTRY

.global hyp_csfr_access_supp_handler
hyp_csfr_access_supp_handler:
    VM_EXIT
    j hyp_csfr_access_supp_handler
    VM_ENTRY

.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
