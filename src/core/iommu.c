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

    iommu_arch_vm_init(vm, config);
    return 0;
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

    struct iommu_dev_node *ptr = objcache_alloc(&vm->iommu.dev_oc);
    if (ptr != NULL && res == 0) {
        ptr->dev.id = dev_id;
        list_push(&vm->iommu.dev_list, (void *)ptr);
    }

    return res;
}
