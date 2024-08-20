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
.global _trap_vector_table
_trap_vector_table:

.balign ENTRY_SIZE
mmu_trap:
    j	mmu_trap

.balign ENTRY_SIZE
internal_protection_trap:
    j   internal_protection_trap

.balign ENTRY_SIZE
instruction_error:
    j	instruction_error

balign ENTRY_SIZE
ctx_mgnt:
    j	ctx_mgnt:

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
    j   hyp_call

.balign ENTRY_SIZE
hyp_interrupt_trap:
    j   hyp_interrupt_trap

.balign ENTRY_SIZE
l2_data_mem_prot_trap:
    j	l2_data_mem_prot_trap

balign ENTRY_SIZE
l2_code_mem_prot_trap:
    j	l2_code_mem_prot_trap

.balign ENTRY_SIZE
hyp_csfr_access_supp:
    j	hyp_csfr_access_supp

