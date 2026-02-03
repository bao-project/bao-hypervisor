/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file remio.c
 * @brief This source file contains the implmentation of IOMMU configuration procedure for the supported MPU-based systems.
 * 
 */

#include <io.h>
#include <vm.h>

struct iommu_device {
    deviceid_t id;
};

/**
 * @brief Perform the initial configuration of the mechanism for controlling the memory access of IO devices.
 *
 * Performs system-wide initialization of the IOMMU for MMU-based systems.
 * It entirely relies on the architecture-specific implementation of the IOMMU.
 *
 * @see iommu_arch_init()
 */
void io_init(void)
{
    iommu_arch_init();
}

/**
 * @brief Initializes the mechanism for controlling the memory access of IO devices to a VM-owned address space, as per its configuration.
 *
 * Performs the configuration of the IOMMU to grant an IO device access to
 * the specific VM's address space.
 *
 * @param vm Pointer to the VM structure.
 * @param config Pointer to the VM's configuration.
 * @return bool True if initialization successful, false otherwise.
 *
 * @see iommu_arch_vm_init(), vm, vm_config.
 */
bool io_vm_init(struct vm* vm, const struct vm_config* config)
{
    return iommu_arch_vm_init(vm, config);
}

/**
 * @brief Grant access to a VM address space to a specific device.
 *
 * Associates a device with a VM's address space through the IOMMU.
 *
 * @param vm Pointer to the VM structure.
 * @param dev_id Device identifier (0 for global mask).
 * @return bool True if device added successfully, false otherwise.
 *
 * @see iommu_arch_vm_add_device(), vm, deviceid_t
 * 
 */
bool io_vm_add_device(struct vm* vm, deviceid_t dev_id)
{
    bool res = false;

    /*
     * If dev_id == 0 assume global mask includes the relevant devices for this VM.
     *
     * Assume there's no device id = 0 */
    if (dev_id != 0) {
        /* Stream id is valid. Match this device with this VM specifically. */
        res = iommu_arch_vm_add_device(vm, dev_id);
    }

    return res;
}
