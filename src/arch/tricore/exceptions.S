/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#define ENTRY_SIZE   (0x20)

.macro SAVE_REGS
    /* TODO */
.endm

.macro RESTORE_REGS
    /* TODO */
.endm

.balign 0x100
.global _exception_vector
_exception_vector:

.balign ENTRY_SIZE
mmu_trap:
    j	mmu_trap

.balign ENTRY_SIZE
internal_protection_trap:
    j   internal_protection_trap

.balign ENTRY_SIZE
instruction_error:
    j	instruction_error

.balign ENTRY_SIZE
sys_bus_errors:
    j	sys_bus_errors

.balign ENTRY_SIZE
assertion_trap:
    j	assertion_trap

.balign ENTRY_SIZE
system_call:
    j	system_call

.balign ENTRY_SIZE
non_mskbl_interrupt:
    j	non_mskbl_interrupt

.balign ENTRY_SIZE
.global _irq_vector
_irq_vector:
    call ir_handle
    .rept   2
        .balign ENTRY_SIZE
        1:
            /* TODO */
            j 1b
    .endr

.balign ENTRY_SIZE

