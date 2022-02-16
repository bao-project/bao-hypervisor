/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2021-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
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

bool io_vm_add_device(struct vm *vm, streamid_t dev_id)
{
    return true;
}
