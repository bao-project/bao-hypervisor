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

#ifndef __IOMMU_H__
#define __IOMMU_H__

#include <bao.h>
#include <arch/iommu.h>
#include <objcache.h>
#include <list.h>

typedef struct vm_config vm_config_t;
typedef struct vm vm_t;

typedef struct iommu_dev {
    list_t dev_list;
    objcache_t dev_oc;
    iommu_vm_arch_t arch;
} iommu_vm_t;

/* Mainly for HW initialization. */
void iommu_init();

/* iommu api for vms. */
int iommu_vm_init(vm_t *vm, const vm_config_t *config);
int iommu_vm_add_device(vm_t *vm, int dev_id);

/* Must be implemented by architecture. */
int iommu_arch_init();
int iommu_arch_vm_init(vm_t *vm, const vm_config_t *config);
int iommu_arch_vm_add_device(vm_t *vm, int id);

#endif
