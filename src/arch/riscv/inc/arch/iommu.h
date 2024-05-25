/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __IOMMU_ARCH_H__
#define __IOMMU_ARCH_H__

#include <bao.h>

// VM-specific IOMMU data
struct iommu_vm_arch {
    EMPTY_STRUCT_FIELDS
};

struct vm;
void rv_iommu_fq_irq_handler(irqid_t irq_id);
void alloc_2lvl_vptrs(void);
void up_1lvl_to_2lvl(void);
void alloc_3lvl_vptrs(void);
void up_2lvl_to_3lvl(void);
void ddt_init(void);
void rv_iommu_init(void);
bool rv_iommu_alloc_did(deviceid_t dev_id);
void rv_iommu_write_ddt(deviceid_t dev_id, struct vm* vm, paddr_t root_pt);

#endif /* __IOMMU_ARCH_H__ */
