/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef MEM_PROT_IO_H
#define MEM_PROT_IO_H

#include <bao.h>
#include <arch/iommu.h>

struct vm_config;
struct vm;

struct io_prot {
    struct iommu_vm_arch mmu;
};

/* Must be implemented by architecture. */
bool iommu_arch_init();
bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config);
bool iommu_arch_vm_add_device(struct vm *vm, deviceid_t id);

#endif /* MEM_PROT_IO_H */
