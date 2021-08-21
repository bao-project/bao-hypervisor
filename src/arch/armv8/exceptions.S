/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
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
    sub sp, sp, #(VCPU_REGS_SIZE)

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

    ldr x0, =cpu
    ldr x0, [x0, #CPU_VCPU_OFF]
    mov x1, sp
    str x1, [x0, #VCPU_REGS_OFF]

.endm

.global vcpu_arch_entry
vcpu_arch_entry:
    ldr x0, =cpu
    ldr x0, [x0, #CPU_VCPU_OFF]
    ldr x0, [x0, #VCPU_REGS_OFF]
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

    add sp, sp, #(VCPU_REGS_SIZE)
    
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
