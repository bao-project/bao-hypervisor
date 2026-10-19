/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <asm_defs.h>

#define ENTRY_SIZE   (0x80)

.text 

.macro SAVE_HYP_GPRS

    sub sp, sp, 32*8

    stp x0, x1,   [sp, #(8*0)]
    stp x2, x3,   [sp, #(8*2)]
    stp x4, x5,   [sp, #(8*4)]
    stp x6, x7,   [sp, #(8*6)]
    stp x8, x9,   [sp, #(8*8)]
    stp x10, x11, [sp, #(8*10)]
    stp x12, x13, [sp, #(8*12)]
    stp x14, x15, [sp, #(8*14)]
    stp x16, x17, [sp, #(8*16)]
    stp x18, x19, [sp, #(8*18)]
    stp x20, x21, [sp, #(8*20)]
    stp x22, x23, [sp, #(8*22)]
    stp x24, x25, [sp, #(8*24)]
    stp x26, x27, [sp, #(8*26)]
    stp x28, x29, [sp, #(8*28)]
    mov x29, sp 
    add x29, x29, 32*8
    stp x30, x29, [sp, #(8*30)]

.endm

.macro VM_EXIT

    stp x0, x1,   [sp, #(8*0)]
    stp x2, x3,   [sp, #(8*2)]
    stp x4, x5,   [sp, #(8*4)]
    stp x6, x7,   [sp, #(8*6)]
    stp x8, x9,   [sp, #(8*8)]
    stp x10, x11, [sp, #(8*10)]
    stp x12, x13, [sp, #(8*12)]
    stp x14, x15, [sp, #(8*14)]
    stp x16, x17, [sp, #(8*16)]
    stp x18, x19, [sp, #(8*18)]
    stp x20, x21, [sp, #(8*20)]
    stp x22, x23, [sp, #(8*22)]
    stp x24, x25, [sp, #(8*24)]
    stp x26, x27, [sp, #(8*26)]
    stp x28, x29, [sp, #(8*28)]
    str x30,      [sp, #(8*30)]

    mrs x0, ELR_EL2
    mrs x1, SPSR_EL2
    stp x0, x1,   [sp, #(8*31)]

    mrs x0, tpidr_el2
    ldr x1, =(CPU_STACK_OFF + CPU_STACK_SIZE)
    add x0, x0, x1
    mov sp, x0

    #ifdef MEM_PROT_MPU
    mrs x0, tpidr_el2
    ldr x0, [x0, #CPU_ARCH_PROFILE_MPU_MASK_OFF]
    msr prenr_el2, x0
    #endif /* MEM_PROT_MPU */

.endm

.global vcpu_arch_entry
vcpu_arch_entry:
    mrs x0, tpidr_el2

    #ifdef MEM_PROT_MPU
    ldr x1, [x0, #CPU_VCPU_OFF]
    ldr x1, [x1, #VCPU_ARCH_MASK_OFF]

    mov x2, #CPU_ARCH_PROFILE_MPU_LOCKED_OFF
    add x2, x2, x0
    ldr x2, [x2]

    orr x1, x1, x2
    
    msr prenr_el2, x1
    #endif /* MEM_PROT_MPU */

    ldr x0, [x0, #CPU_VCPU_OFF]
    add x0, x0, #VCPU_REGS_OFF
    mov sp, x0

    ldp x0, x1, [sp, #(8*31)]
    msr ELR_EL2, x0
    msr SPSR_EL2, x1

    ldp x0, x1,   [sp, #(8*0)]
    ldp x2, x3,   [sp, #(8*2)]
    ldp x4, x5,   [sp, #(8*4)]
    ldp x6, x7,   [sp, #(8*6)]
    ldp x8, x9,   [sp, #(8*8)]
    ldp x10, x11, [sp, #(8*10)]
    ldp x12, x13, [sp, #(8*12)]
    ldp x14, x15, [sp, #(8*14)]
    ldp x16, x17, [sp, #(8*16)]
    ldp x18, x19, [sp, #(8*18)]
    ldp x20, x21, [sp, #(8*20)]
    ldp x22, x23, [sp, #(8*22)]
    ldp x24, x25, [sp, #(8*24)]
    ldp x26, x27, [sp, #(8*26)]
    ldp x28, x29, [sp, #(8*28)]
    ldr x30,      [sp, #(8*30)]
    
    eret
    b   .

.balign 0x800
.global _hyp_vector_table	
_hyp_vector_table:

/* 
 * EL2 with SP0
 */  
.balign ENTRY_SIZE
curr_el_sp0_sync:        
    b	.
.balign ENTRY_SIZE
curr_el_sp0_irq:  
    b   .
.balign ENTRY_SIZE
curr_el_sp0_fiq:         
    b	.
.balign ENTRY_SIZE
curr_el_sp0_serror:      
    b	.
          

/* 
 * EL2 with SPx
 */  
.balign ENTRY_SIZE  
curr_el_spx_sync:
    SAVE_HYP_GPRS
    mov x0, sp
    bl	internal_abort_handler        
    b	.
.balign ENTRY_SIZE
curr_el_spx_irq:         
    b	.
.balign ENTRY_SIZE
curr_el_spx_fiq:         
    b	.
.balign ENTRY_SIZE
curr_el_spx_serror:
    SAVE_HYP_GPRS
    mov x0, sp
    bl	internal_abort_handler       
    b	.         

/* 
 * Lower EL using AArch64
 */  

.balign ENTRY_SIZE
lower_el_aarch64_sync:
    VM_EXIT
    bl	aborts_sync_handler
    b   vcpu_arch_entry
.balign ENTRY_SIZE
lower_el_aarch64_irq:    
    VM_EXIT
    bl  gic_handle
    b   vcpu_arch_entry
.balign ENTRY_SIZE
lower_el_aarch64_fiq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch64_serror: 
    b	.          

/* 
 * Lower EL using AArch32
 */  
.balign ENTRY_SIZE   
lower_el_aarch32_sync:   
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_irq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_fiq:    
    b	.
.balign ENTRY_SIZE
lower_el_aarch32_serror: 
    b	.

.balign ENTRY_SIZE          

/* Before a C runtime is available, traps must not touch the stack. */
.balign 0x800
.global _hyp_trap_halt_vector
_hyp_trap_halt_vector:
    .rept 16
    b _hyp_early_halt
    .balign 0x80
    .endr

.balign 0x800
.global _hyp_early_trap_vector
_hyp_early_trap_vector:
    b _hyp_early_trap_0
    .balign 0x80
    b _hyp_early_trap_1
    .balign 0x80
    b _hyp_early_trap_2
    .balign 0x80
    b _hyp_early_trap_3
    .balign 0x80
    b _hyp_early_trap_4
    .balign 0x80
    b _hyp_early_trap_5
    .balign 0x80
    b _hyp_early_trap_6
    .balign 0x80
    b _hyp_early_trap_7
    .balign 0x80
    b _hyp_early_trap_8
    .balign 0x80
    b _hyp_early_trap_9
    .balign 0x80
    b _hyp_early_trap_10
    .balign 0x80
    b _hyp_early_trap_11
    .balign 0x80
    b _hyp_early_trap_12
    .balign 0x80
    b _hyp_early_trap_13
    .balign 0x80
    b _hyp_early_trap_14
    .balign 0x80
    b _hyp_early_trap_15
    .balign 0x80
_hyp_early_trap_0:
    mov x0, #0
    b _hyp_early_report
_hyp_early_trap_1:
    mov x0, #1
    b _hyp_early_report
_hyp_early_trap_2:
    mov x0, #2
    b _hyp_early_report
_hyp_early_trap_3:
    mov x0, #3
    b _hyp_early_report
_hyp_early_trap_4:
    mov x0, #4
    b _hyp_early_report
_hyp_early_trap_5:
    mov x0, #5
    b _hyp_early_report
_hyp_early_trap_6:
    mov x0, #6
    b _hyp_early_report
_hyp_early_trap_7:
    mov x0, #7
    b _hyp_early_report
_hyp_early_trap_8:
    mov x0, #8
    b _hyp_early_report
_hyp_early_trap_9:
    mov x0, #9
    b _hyp_early_report
_hyp_early_trap_10:
    mov x0, #10
    b _hyp_early_report
_hyp_early_trap_11:
    mov x0, #11
    b _hyp_early_report
_hyp_early_trap_12:
    mov x0, #12
    b _hyp_early_report
_hyp_early_trap_13:
    mov x0, #13
    b _hyp_early_report
_hyp_early_trap_14:
    mov x0, #14
    b _hyp_early_report
_hyp_early_trap_15:
    mov x0, #15
    b _hyp_early_report

_hyp_early_report:
    ldr x1, =_hyp_trap_halt_vector
    msr vbar_el2, x1
    isb
    bl early_internal_exception_handler
_hyp_early_halt:
    wfi
    b _hyp_early_halt
