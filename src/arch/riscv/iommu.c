/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <io.h>

/**
 * TODO: No IOMMU available in riscv
 */

bool iommu_arch_init()
{   
    return true;
}

inline bool iommu_arch_vm_add_device(struct vm *vm, streamid_t id)
{
    return true;
}

bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config)
{
    return true;
}
