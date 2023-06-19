/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <io.h>
#include <vm.h>

void io_init()
{
    return;
}

bool io_vm_init(struct vm *vm, const struct vm_config *config)
{
    return true;
}

bool io_vm_add_device(struct vm *vm, deviceid_t dev_id)
{
    return true;
}
