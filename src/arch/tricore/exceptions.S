/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/csfrs.h>
#include <arch/csa.h>

#define ENTRY_SIZE   (0x20)

.text

.macro load_32bit_val_d rd, label
    movh   \rd, hi:\label
    addi   \rd, \rd, lo:\label
.endm

.macro GET_VCPU_REGS_PTR
    ld.w    %d8, [%a8]CPU_VCPU_OFF /* get cpu()->vcpu */
    add     %d8, %d8, VCPU_REGS_OFF
    mov.a   %a10, %d8
.endm

.macro GET_HWVM_ID
    ld.a    %a12, [%a8]CPU_VCPU_OFF /* a12: cpu()->vcpu */
    ld.a    %a12, [%a12]VCPU_VM_OFF /* get vcpu->vm */
    ld.w    %d8,  [%a12]VM_ID_OFF /* get vm->vmid */
    addi    %d8,   %d8, 1
    /* The VMID used in HW is bao's internal vm.id + 1 because VM0 is
    reserved for the hypervisor. */
.endm

.macro VM_EXIT
    /*Upper context was saved by hardware*/

    /*Save lower context*/
    svlcx

    /* Save a0, a1, a8, a9 */
    GET_VCPU_REGS_PTR

    mfcr %d0, CSFR_HVHRA_A0
    st.w [%a10] REGS_A0_OFF, %d0

    mfcr %d0, CSFR_HVHRA_A1
    st.w [%a10] REGS_A1_OFF, %d0

    mfcr %d0, CSFR_HVHRA_A8
    st.w [%a10] REGS_A8_OFF, %d0

    mfcr %d0, CSFR_HVHRA_A9
    st.w [%a10] REGS_A8_OFF, %d0
.endm

.macro VM_ENTRY
    /* d8 and A10 contains the pointer to vcpu->regs (same as lower_ctx) */
    GET_VCPU_REGS_PTR

    /*restore a0, a1, a8, a9*/
    ld.w %d0, [%a10] REGS_A0_OFF
    mtcr CSFR_HVHRA_A0, %d0

    ld.w %d0, [%a10] REGS_A1_OFF
    mtcr CSFR_HVHRA_A1, %d0

    ld.w %d0, [%a10] REGS_A8_OFF
    mtcr CSFR_HVHRA_A8, %d0

    ld.w %d0, [%a10] REGS_A9_OFF
    mtcr CSFR_HVHRA_A9, %d0

    dsync
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
    j _sys_bus_errors_handler

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
    .rept   256
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

.global sys_bus_errors_handler
_sys_bus_errors_handler:
    /* Check whether we came from the guest or hv */
    jz.t %d15, 31, hyp_sys_bus_errors_handler
    VM_EXIT
    call	sys_bus_errors_handler
    VM_ENTRY
hyp_sys_bus_errors_handler:
    j hyp_sys_bus_errors_handler
    rfe

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
    Since this a point of no return, the used CSA list and the stack need to
    reset.
    To do so, we just need to correctly manage the CSA pointers. The FCX
    (next free context) now points to the PCXI (previous used context). Finally
    the last entry in the CSA list, now points to the old FCX.
*/
    mfcr    %d3,$core_id
    and     %d3,%d3,COREID_CORE_MASK

    /* RESET CSA */
    mfcr %d0, $pcxi
    mfcr %d1, $fcx
    mtcr $fcx, %d0
    load_32bit_val_d %d0, csa_array
    mov %d2, CSA_ARRAY_SIZE
    madd %d0, %d0, %d3, %d2
    add %d0, %d0, CSA_SIZE_BYTES
    mov.a %a2, %d0
    st.w [%a2], %d1

    /* RESET STACK */
    mov.d   %d4, %a8
    load_32bit_val_d %d5, (CPU_STACK_OFF + CPU_STACK_SIZE)
    add     %d4, %d4, %d5
    mov.a   %sp, %d4

    /* Invalidate the PCXI register */
    GET_VCPU_REGS_PTR
    /* convert the vcpu->regs to pcx format */
    extr.u %d1, %d8, ADDR_PCXS_OFF, ADDR_PCXS_LEN
    extr.u %d2, %d8, ADDR_PCXO_OFF, ADDR_PCXO_LEN
    sh %d1, %d1, PCXI_PCXS_OFF
    or %d2, %d2, %d1
    /* point pcxi to the vcpu->regs->lower_ctx*/
    mtcr $pcxi, %d2

    /* Clear CDC before jumping to guest */
    mfcr %d0, $psw
    movh %d1, hi:0xFFFFFF80 /* ~PSW_CDC_MASK */
    addi %d1, %d1, lo:0xFFFFFF80 /* ~PSW_CDC_MASK */
    and %d0, %d0, %d1
    mtcr $psw, %d0

    /* Enable VCON2 l2_prs & VMn */
    GET_HWVM_ID
    /* PRS is the same as the VMID */
    mov %d0, %d8    /* vcon2.vmn=vmid */
    sh %d8, %d8, 8  /* vcon2.l2_prs=vmid */
    or %d0, %d0, %d8
    mtcr CSFR_VCON2, %d0

    isync

    VM_ENTRY
