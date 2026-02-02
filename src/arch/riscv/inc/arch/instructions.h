/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ARCH_INSTRUCTIONS_H
#define ARCH_INSTRUCTIONS_H

static inline uint64_t hlvxhu(uintptr_t addr)
{
    uint64_t value;
    __asm__ volatile(".insn r 0x73, 0x4, 0x32, %0, %1, x3\n\t" : "=r"(value) : "r"(addr)
                     : "memory");
    return value;
}

/**
 * TODO: The following implementation of fence instructions assume global
 * invalidation of memory translation/protection structures, without an
 * explicit address or asid/vmid. If per-address or per-asid/vmid invalidation
 * is required in the features, new versions of these instructions shall be
 * defined. For example, `sfence_vma_vaddr`/`sfence_vma_asid`/`sfence_vma_vaddr_asid`.
 */

static inline void sfence_vma(void) {
    __asm__ volatile("sfence.vma");
}

static inline void hfence_vvma(void) {
    __asm__ volatile("hfence.vvma");
}

static inline void hfence_gvma(void) {
    __asm__ volatile("hfence.gvma");
}

#endif /* ARCH_INSTRUCTIONS_H */
