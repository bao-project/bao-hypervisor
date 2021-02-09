/**
 * Bao Hypervisor
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
#include <asm_defs.h>
#include <arch/csrs.h>

.text 

.macro VM_EXIT
    
    csrrw   x31, sscratch, x31 
    add     x31, x31, -VCPU_REGS_SIZE

    STORE   x1, 0*REGLEN(x31)
    STORE   x2, 1*REGLEN(x31)
    STORE   x3, 2*REGLEN(x31)
    STORE   x4, 3*REGLEN(x31)
    STORE   x5, 4*REGLEN(x31)
    STORE   x6, 5*REGLEN(x31)
    STORE   x7, 6*REGLEN(x31)
    STORE   x8, 7*REGLEN(x31)
    STORE   x9, 8*REGLEN(x31)
    STORE   x10, 9*REGLEN(x31)
    STORE   x11, 10*REGLEN(x31)
    STORE   x12, 11*REGLEN(x31)
    STORE   x13, 12*REGLEN(x31)
    STORE   x14, 13*REGLEN(x31)
    STORE   x15, 14*REGLEN(x31)
    STORE   x16, 15*REGLEN(x31)
    STORE   x17, 16*REGLEN(x31)
    STORE   x18, 17*REGLEN(x31)
    STORE   x19, 18*REGLEN(x31)
    STORE   x20, 19*REGLEN(x31)
    STORE   x21, 20*REGLEN(x31)
    STORE   x22, 21*REGLEN(x31)
    STORE   x23, 22*REGLEN(x31)
    STORE   x24, 23*REGLEN(x31)
    STORE   x25, 24*REGLEN(x31)
    STORE   x26, 25*REGLEN(x31)
    STORE   x27, 26*REGLEN(x31)
    STORE   x28, 27*REGLEN(x31)
    STORE   x29, 28*REGLEN(x31)
    STORE   x30, 29*REGLEN(x31)
    
    mv      sp, x31
    csrrw   x31, sscratch, x31
    STORE   x31, 30*REGLEN(sp)

    csrr    t0, CSR_HSTATUS
    STORE   t0, 31*REGLEN(sp)
    csrr    t0, sstatus
    STORE   t0, 32*REGLEN(sp)
    csrr    t0, sepc
    STORE   t0, 33*REGLEN(sp)

    .option push
    .option norelax
    la  gp, __global_pointer$
    .option pop   

.endm


.macro GET_VCPU_REGS_PTR reg 
    la      \reg, cpu
    LOAD    \reg, CPU_VCPU_OFF(\reg)
    LOAD    \reg, VCPU_REGS_OFF(\reg)
.endm

.macro VM_ENTRY
    GET_VCPU_REGS_PTR   x31
    add    t0, x31, VCPU_REGS_SIZE
    csrw   sscratch, t0

    LOAD   x1, 31*REGLEN(x31)
    csrw   CSR_HSTATUS, x1
    LOAD   x1, 32*REGLEN(x31)
    csrw   sstatus, x1
    LOAD   x1, 33*REGLEN(x31)
    csrw   sepc, x1

    LOAD   x1, 0*REGLEN(x31)
    LOAD   x2, 1*REGLEN(x31)
    LOAD   x3, 2*REGLEN(x31)
    LOAD   x4, 3*REGLEN(x31)
    LOAD   x5, 4*REGLEN(x31)
    LOAD   x6, 5*REGLEN(x31)
    LOAD   x7, 6*REGLEN(x31)
    LOAD   x8, 7*REGLEN(x31)
    LOAD   x9, 8*REGLEN(x31)
    LOAD   x10, 9*REGLEN(x31)
    LOAD   x11, 10*REGLEN(x31)
    LOAD   x12, 11*REGLEN(x31)
    LOAD   x13, 12*REGLEN(x31)
    LOAD   x14, 13*REGLEN(x31)
    LOAD   x15, 14*REGLEN(x31)
    LOAD   x16, 15*REGLEN(x31)
    LOAD   x17, 16*REGLEN(x31)
    LOAD   x18, 17*REGLEN(x31)
    LOAD   x19, 18*REGLEN(x31)
    LOAD   x20, 19*REGLEN(x31)
    LOAD   x21, 20*REGLEN(x31)
    LOAD   x22, 21*REGLEN(x31)
    LOAD   x23, 22*REGLEN(x31)
    LOAD   x24, 23*REGLEN(x31)
    LOAD   x25, 24*REGLEN(x31)
    LOAD   x26, 25*REGLEN(x31)
    LOAD   x27, 26*REGLEN(x31)
    LOAD   x28, 27*REGLEN(x31)
    LOAD   x29, 28*REGLEN(x31)
    LOAD   x30, 29*REGLEN(x31) 
    LOAD   x31, 30*REGLEN(x31)  

    sret
    j   .
.endm

.balign 0x4
.global _hyp_trap_vector	
_hyp_trap_vector:
    VM_EXIT
    csrr    t0, scause
    bltz    t0, 1f
    call    sync_exception_handler
    j       2f
1:
    call    interrupts_arch_handle
2:
.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
