/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file vm.c
 * @brief   This file implements the initialization of the VMs' address space
 *          access control for MMU-based systems.
 */

#include <vm.h>

#include <config.h>
#include <mem.h>

/**
 * @brief Initialize memory access control for a VM in MMU-based systems
 * Sets up the address space for a VM with caches color map.
 * @param vm Pointer to the VM structure
 * @param vm_config Pointer to the VM's configuration
 * @see as_init, vm, vm_config, colormap_t, AS_TYPE
 */
void vm_mem_prot_init(struct vm* vm, const struct vm_config* vm_config)
{
    as_init(&vm->as, AS_VM, NULL, vm_config->colors);
}
