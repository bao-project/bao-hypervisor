/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <io.h>
#include <arch/riscv_iommu.h>
#include <config.h>

/**
 * IOMMU HW Initialization.
 * 
 * @returns true on success, false on error.
 */
bool iommu_arch_init()
{   

    // By checking platform.arch.iommu.base we verify if an IOMMU is present in the platform
    if(cpu()->id == CPU_MASTER && platform.arch.iommu.base){
        rv_iommu_init();
        return true;
    }

    return false;
}

/**
 * Initialize the DDT entry indexed by device_id for the given VM
 * Configure corresponding DDT entry with root PT base addr, VMID (GSCID) and device config
 * 
 * @vm:     VM struct to which the device will be assigned.
 * @dev_id: device_id of the device to be added.
 * 
 * @returns true on success, false on error.
 */
static bool iommu_vm_arch_add(struct vm *vm, deviceid_t dev_id)
{
    if (dev_id > 0)
    {
        // Check if device was already added to a VM
        if(rv_iommu_alloc_did(dev_id))
        {
            paddr_t rootpt;
            // Translate root PT base address
            mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &rootpt);
            // Set DDT entry with root PT base address, VMID and configuration
            rv_iommu_write_ddt(dev_id, vm, rootpt);
        }
        else
        {
            INFO("RV IOMMU: Cannot add one device ID (%d) twice", dev_id);
            return false;
        }
    }
    else
    {
        INFO("RV IOMMU: Invalid device ID: %d", dev_id);
        return false;
    }

    return true;
}

/**
 * Add device to the VM specified.
 * 
 * @vm:     VM struct to which the device will be assigned.
 * @dev_id: device_id of the device to be added.
 * 
 * @returns true on success, false on error.
 */
inline bool iommu_arch_vm_add_device(struct vm *vm, deviceid_t dev_id)
{
    return iommu_vm_arch_add(vm, dev_id);
}

/**
 * Initialize VM-specific, arch-specific IOMMU data.
 * 
 * @vm:     VM under consideration.
 * @config: VM config.
 * 
 * @returns true on success, false on error.
 */
bool iommu_arch_vm_init(struct vm *vm, const struct vm_config *config)
{
    // For now there is no data to initialize
    return true;
}
