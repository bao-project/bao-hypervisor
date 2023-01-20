/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/sysregs.h>

#define ENTRY_SIZE   (0x4)

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
    SAVE_SP
    push {r0-r12}
    SAVE_ELR_SPSR

.endm


.macro SAVE_SP

    mrs r14, SPSR_hyp
    and r14, r14, #0x1F
    
    cmp r14, #SPSR_USR
    beq 1f
    cmp r14, #SPSR_IRQ
    beq 2f
    cmp r14, #SPSR_SVC
    beq 3f
    cmp r14, #SPSR_ABT
    beq 4f
    cmp r14, #SPSR_UND
    beq 5f
    
    1:  //read_usr:
        mrs r14,  sp_usr
        push {r14}
        b 6f
    2:  //read_irq:
        mrs r14,  sp_irq
        push {r14}
        b 6f
    3:  //read_hvc:
        mrs r14,  sp_svc
        push {r14}
        b 6f
    4:  //read_abt:
        mrs r14,  sp_abt
        push {r14}
        b 6f
    5:  //read_und:
        mrs r14,  sp_und
        push {r14}
    6:

.endm

.macro LOAD_SP

    mrs r14, SPSR_hyp
    and r14, r14, #0x1F
    
    cmp r14, #SPSR_USR
    beq 1f
    cmp r14, #SPSR_IRQ
    beq 2f
    cmp r14, #SPSR_SVC
    beq 3f
    cmp r14, #SPSR_ABT
    beq 4f
    cmp r14, #SPSR_UND
    beq 5f
    
    1:  
        pop {r14}
        msr sp_usr, r14
        b 6f
    2:
        pop {r14}
        msr sp_irq, r14
        b 6f
    3:
        pop {r14}
        msr sp_svc, r14
        b 6f
    4:
        pop {r14}
        msr sp_abt, r14
        b 6f
    5:
        pop {r14}
        msr sp_und, r14
    6:

.endm

.macro VM_ENTRY

    mrc p15, 4, r0, c13, c0, 2  // Read HTPIDR (CPU base address)
    ldr r0, [r0, #CPU_VCPU_OFF]
    add r0, r0, #VCPU_REGS_OFF
    mov sp, r0

    LOAD_ELR_SPSR
    pop {r0-r12}
    LOAD_SP
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
