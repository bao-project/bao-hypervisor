/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/sysregs.h>

.text 

.macro SAVE_HYP_GPRS

    push {r0-r12}
    add r0, sp, #(13*4)  // adjust and save the sp (cp is r13)
    push {r0, r14}

.endm


.macro SAVE_ELR_SPSR

    mrs r0, ELR_hyp
    mrs r1, SPSR_hyp
    push {r0, r1}

.endm

.macro LOAD_ELR_SPSR

    pop {r0, r1}
    msr ELR_hyp, r0
    msr SPSR_hyp, r1

.endm

.macro SET_SP

    mrc p15, 4, r0, c13, c0, 2  // Read HTPIDR (CPU base address)
    add r0, r0, #CPU_STACK_OFF
    add r0, r0, #CPU_STACK_SIZE
    mov sp, r0
    
.endm


.macro VM_EXIT

    push {r14}
    sub sp, sp, #4 // we skip sp as this is accessed/updated directly on the banked sp
    push {r0-r12}
    SAVE_ELR_SPSR

#ifdef MEM_PROT_MPU
    mrc p15, 4, r0, c13, c0, 2  // Read HTPIDR (CPU base address)
    add r0, r0, #CPU_AS_ARCH_MASK_OFF
    ldr r0, [r0]
    mcr p15, 4, r0, c6, c1, 1
#endif /* MEM_PROT_MPU */

.endm

.macro VM_ENTRY

    mrc p15, 4, r0, c13, c0, 2  // Read HTPIDR (CPU base address)

#ifdef MEM_PROT_MPU
    ldr r1, [r0, #CPU_VCPU_OFF]
    mov r2, #VCPU_VM_OFF
    add r1, r1, r2
    ldr r1, [r1]
    ldr r1, [r1, #VM_AS_ARCH_MASK_OFF]

    mov r2, #CPU_ARCH_PROFILE_MPU_LOCKED_OFF
    add r2, r2, r0
    ldr r2, [r2]

    orr r1, r1, r2
    mcr p15, 4, r1, c6, c1, 1
#endif /* MEM_PROT_MPU */

    ldr r0, [r0, #CPU_VCPU_OFF]
    add r0, r0, #VCPU_REGS_OFF
    mov sp, r0

    LOAD_ELR_SPSR
    pop {r0-r12}
    add sp, sp, #4 // we skip sp as this is accessed/updated directly on the banked sp
    pop {r14}
    
    eret
    b   .

.endm


.balign 0x20
.global _hyp_vector_table
_hyp_vector_table:
    b	.
    b	hyp_und_handler
    b	hyp_hvc_handler
    b	hyp_fetch_abt_handler
    b	hyp_data_abt_handler
    b	hyp_trap_handler
    b   hyp_irq_handler
    b   hyp_fiq_handler


.global hyp_und_handler
hyp_und_handler:
    b	.  


.global hyp_hvc_handler
hyp_hvc_handler:
    b	. 


.global hyp_fetch_abt_handler
hyp_fetch_abt_handler:
    SAVE_HYP_GPRS
    mov r0, sp
    bl internal_abort_handler
    b .


.global hyp_data_abt_handler
hyp_data_abt_handler:
    SAVE_HYP_GPRS
    mov r0, sp
    bl internal_abort_handler
    b .


.global hyp_trap_handler
hyp_trap_handler:
    VM_EXIT
    SET_SP
    bl	aborts_sync_handler
    VM_ENTRY


.global hyp_irq_handler
hyp_irq_handler:
    VM_EXIT
    SET_SP
    bl  gic_handle
    VM_ENTRY


.global hyp_fiq_handler
hyp_fiq_handler:
    b   .


.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
