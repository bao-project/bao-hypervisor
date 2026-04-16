/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file io.c
 * @brief   This source file does not implement any IO access control mechanism
 *          as the supported MPU-based systems do not posseess a similar mechanism.
 */

#include <io.h>
#include <vm.h>

/**
 * @brief Not implemented. IOMMU/SMMU is not supported by MPU-based systems.
 */
void io_init()
{
    return;
}

/**
 * @brief Not implemented. IOMMU/SMMU is not supported by MPU-based systems.
 * @param vm Unused.
 * @param config Unused.
 * @return bool Always returns true
 */
bool io_vm_init(struct vm* vm, const struct vm_config* config)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(config);

    return true;
}

/**
 * @brief Not implemented. IOMMU/SMMU is not supported by MPU-based systems.
 * @param vm Unused.
 * @param dev_id Unused.
 * @return bool Always returns true.
 */
bool io_vm_add_device(struct vm* vm, deviceid_t dev_id)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(dev_id);

    return true;
}
