/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <io.h>
#include <vm.h>

struct iommu_device {
    deviceid_t id;
};

/* Mainly for HW initialization. */
void io_init()
{
    iommu_arch_init();
}

/* Configure architecture dependent stuff. */
bool io_vm_init(struct vm *vm, const struct vm_config *config)
{
    return iommu_arch_vm_init(vm, config);
}

/* Allows vms to add devices to their address space. */
bool io_vm_add_device(struct vm *vm, deviceid_t dev_id)
{
    bool res = false;

    /*
     * If dev_id == 0 assume global mask includes
     * the relevant devices for this VM.
     *
     * Assume there's no device id = 0 */
    if (dev_id != 0) {

        /* Stream id is valid. Match this device with this VM specifically. */
        res = iommu_arch_vm_add_device(vm, dev_id);
    }

    return res;
}
