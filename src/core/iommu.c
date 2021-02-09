/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <iommu.h>
#include <vm.h>

struct iommu_device {
    uint32_t id;
};

struct iommu_dev_node {
    node_t node;
    struct iommu_device dev;
};

/* Mainly for HW initialization. */
void iommu_init()
{
    iommu_arch_init();
}

/* Configure architecture dependent stuff. */
int iommu_vm_init(vm_t *vm, const vm_config_t *config)
{
    objcache_init(&vm->iommu.dev_oc, sizeof(struct iommu_dev_node),
                  SEC_HYP_GLOBAL, false);

    return iommu_arch_vm_init(vm, config);
}

/* Allows vms to add devices to their address space. */
int iommu_vm_add_device(vm_t *vm, int dev_id)
{
    int res = -1;

    /*
     * If dev_id == 0 assume global mask includes
     * the relevant devices for this VM.
     *
     * Assume there's no device id = 0 */
    if (dev_id != 0) {

        /* Stream id is valid. Match this device with this VM specifically. */
        res = iommu_arch_vm_add_device(vm, dev_id);
    }

    if (res >= 0) {
        struct iommu_dev_node *ptr = objcache_alloc(&vm->iommu.dev_oc);
        if(ptr != NULL){
            ptr->dev.id = dev_id;
            list_push(&vm->iommu.dev_list, (void *)ptr);
        } else {
            res = -1;
        }
    }

    return res;
}
