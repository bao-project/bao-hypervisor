/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <io.h>
#include <arch/smmuv3.h>
#include <config.h>

/**
 * IOMMU HW Initialization.
 *
 * @returns true on success, false on error.
 */
// TODO: We need a mechanism to select between both SMMU versions
bool iommu_arch_init()
{
    // By checking platform.arch.iommu.base we verify if an IOMMU is present in the platform
    if (cpu()->id == CPU_MASTER && platform.arch.iommu.base) {
        smmuv3_init();
        return true;
    }

    return false;
}

/**
 * Initialize the STE indexed by the StreamID for the given VM
 * Configure corresponding STE with root PT base addr, VMID and device config
 *
 * @vm:     VM struct to which the device will be assigned.
 * @sid:    StreamID of the device to be added.
 *
 * @returns true on success, false on error.
 */
static bool iommu_vm_arch_add(struct vm* vm, streamid_t sid)
{
    if (sid > 0) {
        // Check if device was already added to a VM
        if (smmuv3_alloc_ste(sid)) {
            paddr_t rootpt;
            // Translate root PT base address
            mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &rootpt);
            // Set DDT entry with root PT base address, VMID and configuration
            smmuv3_write_ste(sid, vm, rootpt);
        } else {
            INFO("SMMUv3: Cannot add the same StreamID (%d) twice", sid);
            return false;
        }
    } else {
        INFO("SMMUv3: Invalid StreamID: %d", sid);
        return false;
    }

    return true;
}

/**
 * Add device to the VM specified.
 *
 * @vm:     VM struct to which the device will be assigned.
 * @sid:    StreamID of the device to be added.
 *
 * @returns true on success, false on error.
 */
inline bool iommu_arch_vm_add_device(struct vm* vm, streamid_t sid)
{
    return iommu_vm_arch_add(vm, sid);
}

/**
 * Initialize VM-specific, arch-specific IOMMU data.
 *
 * @vm:     VM under consideration.
 * @config: VM config.
 *
 * @returns true on success, false on error.
 */
bool iommu_arch_vm_init(struct vm* vm, const struct vm_config* config)
{
    // For now there is no data to initialize
    return true;
}
