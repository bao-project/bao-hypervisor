/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __IOMMU_ARCH_H__
#define __IOMMU_ARCH_H__

#include <bao.h>
#include <arch/smmuv2.h>

struct iommu_vm_arch {
    streamid_t global_mask;
    size_t ctx_id;
};

#endif
