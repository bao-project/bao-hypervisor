/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __MMIO_H__
#define __MMIO_H__

#ifndef __ASSEMBLER__

#define MMIO_OPS_GEN(PRE, TYPE)                              \
    static inline void PRE##_write(uintptr_t addr, TYPE val) \
    {                                                        \
        (*(volatile TYPE*)(addr)) = val;                     \
    }                                                        \
    static inline TYPE PRE##_read(uintptr_t addr)            \
    {                                                        \
        return (*(volatile TYPE*)(addr));                    \
    }

MMIO_OPS_GEN(mmio32, uint32_t)
MMIO_OPS_GEN(mmio64, uint64_t)
MMIO_OPS_GEN(mmio, unsigned long)

#endif /* |__ASSEMBLER__ */

#endif /* __MMIO_H__ */
