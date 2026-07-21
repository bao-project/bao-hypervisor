/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file io.c
 * @brief   This source file provide stubs for the access control mechanism of
 *          IO device (i.e. peripherals, non-CPU bus masters) as this mechanism
 *          is not supported for MPU-based systems.
 */

#include <io.h>
#include <vm.h>

/**
 * @brief Not implemented.
 */
void io_init()
{
    return;
}

/**
 * @brief Not implemented.
 * @param vm Unused.
 * @param config Unused.
 * @return bool Always returns true.
 */
bool io_vm_init(struct vm* vm, const struct vm_config* config)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(config);

    return true;
}

/**
 * @brief Not implemented.
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
