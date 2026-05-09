/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file vm.c
 * @brief   This file implements the initialization of the VMs' address space
 *          access control for MPU-based systems.
 */

#include <vm.h>

/**
 * @brief Initialize memory protection mechanism for a VM.
 *
 * Initialize the MPU according to the VM address space configuration.
 *
 * @note The initialization of the MMIO regions is performed only once by the master
 *       CPU to prevent race conditions.
 *
 * @param[in,out] vm VM instance whose memory protection will be initialized.
 * @param[in] vm_config VM configuration (unused).
 * @see as_init, vm, vm_config, mem_mmio_init_regions, MMIO_SLAVE_SIDE_PROT,
 *      cpuid_t, cpu, cpu(), addr_space, AS_TYPE.
 */
void vm_mem_prot_init(struct vm* vm, const struct vm_config* vm_config)
{
    UNUSED_ARG(vm_config);

    as_init(&vm->as, AS_VM, 0);

    if (DEFINED(MMIO_SLAVE_SIDE_PROT) && (vm->master == cpu()->id)) {
        mem_mmio_init_regions(&vm->as);
    }
}
