/**
 * baohu separation kernel
 *
 * Copyright (c) Jose Martins, Sandro Pinto, David Cerdeira
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * baohu is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __IOMMU_ARCH_H__
#define __IOMMU_ARCH_H__

#include <bao.h>

typedef struct {
    uint32_t global_mask;
    int32_t ctx_id;
} iommu_vm_arch_t;

#endif
