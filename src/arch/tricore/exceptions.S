/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/csfrs.h>
#include <arch/csa.h>

#define ENTRY_SIZE   (0x20)

.macro get_label_addr rd, label
    movh \rd, hi:\label
    addi  \rd, \rd, lo:\label
.endm

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

.macro GET_VCPU_REGS_PTR
    mov.d   %d8, %a8    
    mov     %d10, CPU_VCPU_OFF
    add     %d8, %d8, %d10
    mov.a   %a12, %d8
    ld.w    %d8, [%a12]
    mov     %d11, VCPU_REGS_OFF
    add     %d8, %d8, %d11
    mov.a   %a10, %d8
.endm

.macro GET_VM_ID
    mov.d   %d8, %a8    
    mov     %d10, CPU_VCPU_OFF
    add     %d8, %d8, %d10
    mov.a   %a12, %d8
    ld.w    %d8, [%a12]
    mov     %d11, VCPU_VM_OFF
    add     %d8, %d8, %d11
    mov.a   %a10, %d8
    ld.a    %a10, [%a10]
    ld.w    %d8, [%a10] 
    addi     %d8, %d8, 1
.endm

.macro GET_VCPU_LOWER_CTX_PTR
    mov.d   %d8, %a8    
    mov     %d10, CPU_VCPU_OFF
    add     %d8, %d8, %d10
    mov.a   %a12, %d8
    ld.w    %d8, [%a12]
    mov     %d11, VCPU_REGS_LOWER_CTX_OFF
    add     %d8, %d8, %d11
    mov.a   %a10, %d8
.endm

.macro VM_EXIT
    /*Upper context was saved by hardware*/

    /*Save lower context*/
    svlcx 

    /* Save a0, a1, a8, a9 */
    GET_VCPU_REGS_PTR

    mfcr %d0, 0xFF81
    st.w [%a10] REGS_A0_OFF, %d0    

    mfcr %d0, 0xFF85
    st.w [%a10] REGS_A1_OFF, %d0 

    mfcr %d0, 0xFFA1
    st.w [%a10] REGS_A8_OFF, %d0 

    mfcr %d0, 0xFFA5
    st.w [%a10] REGS_A8_OFF, %d0 

    
.endm

.macro VM_ENTRY
    /* d8 and A10 contains the pointer to vcpu->regs (same as lower_ctx) */
    GET_VCPU_REGS_PTR
    
    /*restore a0, a1, a8, a9*/
    ld.w %d0, [%a10] REGS_A0_OFF
    mtcr csfr_hvhra_a0, %d0

    ld.w %d0, [%a10] REGS_A1_OFF
    mtcr csfr_hvhra_a1, %d0

    ld.w %d0, [%a10] REGS_A8_OFF
    mtcr csfr_hvhra_a8, %d0

    ld.w %d0, [%a10] REGS_A9_OFF
    mtcr csfr_hvhra_a9, %d0

    isync
    /* Restore lower context */
    rslcx

    /* Return from hypervisor (Restore upper context) */ 
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
    call	sys_bus_errors_handler
    jz.t %d15, 31, 1f
    rfh
1:
    rfe

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
        j _irq_handler
    .endr



.balign 0x100
.global _hyp_vector_table
_hyp_vector_table:

.balign ENTRY_SIZE
hyp_call:
    j hyp_call_handler

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
    j mmu_trap_handler

.global internal_protection_trap_handler
internal_protection_trap_handler:
    j internal_protection_trap_handler

.global instruction_error_handler
instruction_error_handler:
    j instruction_error_handler

.global ctx_mgnt_handler
ctx_mgnt_handler:
    j ctx_mgnt_handler

.global assertion_trap_handler
assertion_trap_handler:
    j assertion_trap_handler

.global system_call_handler
system_call_handler:
    j system_call_handler

.global non_mskbl_interrupt_handler
non_mskbl_interrupt_handler:
    j non_mskbl_interrupt_handler

.global _irq_handler
_irq_handler:
    VM_EXIT
    call ir_handle
    VM_ENTRY


/* Virtualization Related */
.global hyp_call_handler
hyp_call_handler:
    VM_EXIT
    call hvcall_handler
    VM_ENTRY

.global hyp_interrupt_trap_handler
hyp_interrupt_trap_handler:
    VM_EXIT
    j .
    VM_ENTRY

.global l2_data_mem_prot_trap_handler
l2_data_mem_prot_trap_handler:
    VM_EXIT
    mov.aa %a4, %a11
    mov %d4,%d15
    call l2_dmem_prot_trap_handler
    VM_ENTRY

.global l2_code_mem_prot_trap_handler
l2_code_mem_prot_trap_handler:
    VM_EXIT
    j .
    VM_ENTRY

.global hyp_csfr_access_supp_handler
hyp_csfr_access_supp_handler:
    VM_EXIT
    mov.aa %a4, %a11
    mov %d4,%d15
    call hyp_csfr_access_handler
    VM_ENTRY

.global vcpu_arch_entry
vcpu_arch_entry:
/*
    The last in the CSA array is the 1st context used. 
    We are sure of this, because this code only executes in the boot sequence.
    We need to re-establish the CSA list. To do it, we have to point the FCX
    to the current PCXI, and point the 1st context to the current FCX.
*/
    mfcr    %d3,$core_id
    and     %d3,%d3,7

    mfcr %d0, $pcxi
    mfcr %d1, $fcx 
    mtcr $fcx, %d0
    movh %d0, hi:csa_array   
    addi %d0, %d0, lo:csa_array 
    mov %d2, CSA_ARRAY_SIZE 
    madd %d0, %d0, %d3, %d2
    add %d0, %d0, 16*4 
    mov.a %a2, %d0
    st.w [%a2], %d1

    /* Invalidate the PCXI register */
    GET_VCPU_REGS_PTR
    /* convert the vcpu->regs to pcx format */    
    extr.u %d1, %d8, 28, 4
    extr.u %d2, %d8, 6, 16
    sh %d1, %d1, 16
    or %d2, %d2, %d1
    /* point pcxi to the vcpu->regs->lower_ctx*/
    mtcr $pcxi, %d2

    /* Clear CDC before jumping to guest */
    mfcr %d0, $psw
    movh %d1, hi:0xFFFFF80
    addi %d1, %d1, lo:0xFFFFF80
    and %d0, %d0, %d1
    mtcr $psw, %d0

    /* Enable VCON2 l2_prs & VMn */
    GET_VM_ID
    
    movh %d0, lo:0
    or %d0, %d0, %d8
    sh %d8, %d8, 8
    or %d0, %d0, %d8
    mtcr 0xB008, %d0

    isync

    VM_ENTRY
