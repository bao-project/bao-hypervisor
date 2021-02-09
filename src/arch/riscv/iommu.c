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

int iommu_arch_init()
{   
    return 0;
}

inline int iommu_arch_vm_add_device(vm_t *vm, int id)
{
    return 0;
}

int iommu_arch_vm_init(vm_t *vm, const vm_config_t *config)
{
    return 0;
}
