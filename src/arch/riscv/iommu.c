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

#include <iommu.h>

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
