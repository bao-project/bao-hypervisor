/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#define ENTRY_SIZE   (0x20)

.text 

.macro SAVE_HYP_GPRS

//    push {r0-r12}
//    add r0, sp, #(13*4)  // adjust and save the sp (cp is r13)
//    push {r0, r14}

.endm


.macro SAVE_ELR_SPSR

//    mrs r0, ELR_hyp
//    mrs r1, SPSR_hyp
//    push {r0, r1}

.endm

.macro LOAD_ELR_SPSR

 //   pop {r0, r1}
 //   msr ELR_hyp, r0
 //   msr SPSR_hyp, r1

.endm

.macro SET_SP

//    mrc p15, 4, r0, c13, c0, 2  // Read HTPIDR (CPU base address)
//    add r0, r0, #CPU_STACK_OFF
//    add r0, r0, #CPU_STACK_SIZE
//    mov sp, r0
    
.endm


.macro VM_EXIT
    svlcx

    /* TODO move lcx and ucx in the CSA to vcpu registers */
//    push {r14}
//    SAVE_SP
//    push {r0-r12}
//    SAVE_ELR_SPSR

.endm


.macro SAVE_SP

//    mrs r14, SPSR_hyp
//    and r14, r14, #0x1F
//    
//    cmp r14, #SPSR_USR
//    beq 1f
//    cmp r14, #SPSR_IRQ
//    beq 2f
//    cmp r14, #SPSR_SVC
//    beq 3f
//    cmp r14, #SPSR_ABT
//    beq 4f
//    cmp r14, #SPSR_UND
//    beq 5f
//    
//    1:  //read_usr:
//        mrs r14,  sp_usr
//        push {r14}
//        b 6f
//    2:  //read_irq:
//        mrs r14,  sp_irq
//        push {r14}
//        b 6f
//    3:  //read_hvc:
//        mrs r14,  sp_svc
//        push {r14}
//        b 6f
//    4:  //read_abt:
//        mrs r14,  sp_abt
//        push {r14}
//        b 6f
//    5:  //read_und:
//        mrs r14,  sp_und
//        push {r14}
//    6:

.endm

.macro LOAD_SP

//    mrs r14, SPSR_hyp
//    and r14, r14, #0x1F
//    
//    cmp r14, #SPSR_USR
//    beq 1f
//    cmp r14, #SPSR_IRQ
//    beq 2f
//    cmp r14, #SPSR_SVC
//    beq 3f
//    cmp r14, #SPSR_ABT
//    beq 4f
//    cmp r14, #SPSR_UND
//    beq 5f
//    
//    1:  
//        pop {r14}
//        msr sp_usr, r14
//        b 6f
//    2:
//        pop {r14}
//        msr sp_irq, r14
//        b 6f
//    3:
//        pop {r14}
//        msr sp_svc, r14
//        b 6f
//    4:
//        pop {r14}
//        msr sp_abt, r14
//        b 6f
//    5:
//        pop {r14}
//        msr sp_und, r14
//    6:

.endm

.macro VM_ENTRY

    movh    %d9,hi:_dmem_phys_beg
    addi    %d9,%d9,lo:_dmem_phys_beg

    mfcr    %d8,$core_id
    and     %d8,%d8,7
    /* CPU_X physical base address */
    mov     %d10, CPU_SIZE
    madd    %d8, %d9, %d8, %d10
    mov.a   %a10, %d0

    ld.a    %a10, [%a10]#CPU_VCPU_OFF
    add     %a10, %a10, #VCPU_REGS_OFF

    /* TODO move vcpu registers to lcx and ucx in the CSA */

    // LOAD_ELR_SPSR TODO what is this?
    pop {r0-r12}
    LOAD_SP
    pop {r14}
    
    rslcx
    rfh

oops:
    j   oops
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

balign ENTRY_SIZE
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

balign ENTRY_SIZE
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
_irq_handler
    VM_EXIT
    /* TODO identify interrupt */
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
