/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/sysregs.h>
/*
 * TODO:ARMV8M
 * In Armv8-M the vector table is naturally aligned to a power of two, with an alignment value that
 * is, e.g., 128 bytes for CM33, 256 bytes for CM23. As such, this needs to be cpu-specific.
 *
 * The number of interrupts is also cpu-specific, e.g., 480 for CM33, 240 for CM23.
 */
#define VECTTBL_ALIGN   (0x80)
#define MAX_INTERRUPTS  (480)

.macro define_handler name
    .thumb
    .thumb_func
    .global \name
    \name:
.endm

.syntax unified
.text

.macro VM_EXIT
    /* Read CPU pointer (psp) to r0 */
    mrs r1, psp
    ldr r0, [r1, #CPU_VCPU_OFF]

    //TODO:ARMV8M - This should be done only if we are scheduling another VM
    /* Save all special registers */

    /* Save all registers */
    add r0, (VCPU_REGS_OFF+VCPU_GP_REGS_SIZE)      /* Point to R14 */
    stmdb r0!, {r1-r12, lr}                     /* R1-R12, R14 */
    add r0, #-4
    str r0, [r0]                                /* R0 */
.endm

.macro VM_ENTRY
    /* Read CPU pointer (psp) to r0 */
    mrs r1, psp
    ldr r0, [r1, #CPU_VCPU_OFF]

    //TODO:ARMV8M - This should be done only if we are scheduling another VM
    @ ldr r0, [r0,#CPU_VCPU_OFF]
    @ add r0, #(VCPU_SPREGS_OFF+VCPU_SPREGS_SIZE)
    @ /* Restore sp_regs */
    @ ldmdb r0!, {r1-r8}

    @ msr msp_ns,       r1  /* r1 (MSP)         */
    @ msr psp_ns,       r2  /* r2 (PSP)         */
    @ msr msplim_ns,    r3  /* r3 (MSPLIM)      */
    @ msr psplim_ns,    r4  /* r4 (PSPLIM)      */
    @ msr basepri_ns,   r5  /* r5 (BASEPRI)     */
    @ msr primask_ns,   r6  /* r6 (PRIMASK)     */
    @ msr faultmask_ns, r7  /* r7 (FAULTMASK)   */
    @ msr control_ns,   r8  /* r8 (CONTROL)     */
    @ //msr xpsr,         r9  /* r9 (xPSR)        */

1:
    /* Restore all registers */
    add r0, (VCPU_REGS_OFF+VCPU_GP_REGS_SIZE)      /* Point to R14 */
    ldmdb r0!, {r1-r12, lr}                     /* R1-R12, R14 */
    add r0, #-4
    ldr r0, [r0]                                /* R0 */

    //TODO:ARMV8-M - Still missing some procedures (Security Extensions on Dev Tools)

    /* Jump to VM */
    bxns lr
    b   .
.endm


.balign VECTTBL_ALIGN
.global _hyp_vector_table
_hyp_vector_table:
    /* Exceptions */
    /*
     * In Armv8-M, the processor fetches the first two words of the vector table at each power-on/
     * reset sequence. The first is initial value of the MSP (stack pointer) and the second is the
     * reset vector. The reset vector is the address of the reset handler.
     */
    .word 0                     //TODO:ARMV8M should this be initialized with the real MSP value?
    .word _reset_handler
    .word _nmi_handler
    .word _hard_fault_handler
    .word _mem_manage_handler
    .word _bus_fault_handler
    .word _usage_fault_handler
    .word _secure_fault_handler
    .word 0
    .word 0
    .word 0
    .word _svc_handler
    .word _debug_mon_handler
    .word 0
    .word _pendsv_handler
    .word _systick_handler
    /* Interrupts */
    .rept MAX_INTERRUPTS
    .word _irq_handler
    .endr


/* Handlers */
define_handler _nmi_handler
_nmi_handler:
    b   .

define_handler _hard_fault_handler
_hard_fault_handler:
    b   .

define_handler _mem_manage_handler
_mem_manage_handler:
    b   .

define_handler _bus_fault_handler
_bus_fault_handler:
    b   .

define_handler _usage_fault_handler
_usage_fault_handler:
    b   .

define_handler _secure_fault_handler
_secure_fault_handler:
    b   .

define_handler _svc_handler
_svc_handler:
    b   .

define_handler _debug_mon_handler
_debug_mon_handler:
    b   .

define_handler _pendsv_handler
_pendsv_handler:
    b   .

define_handler _systick_handler
_systick_handler:
    b   .

define_handler _irq_handler
_irq_handler:
    b   .

.global _hyp_trap_vector
_hyp_trap_vector:
    VM_EXIT

.global vcpu_arch_entry
vcpu_arch_entry:
    VM_ENTRY
