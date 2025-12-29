/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file config.c
 * @brief This source file contains the implementation of VMs configuration's initialization.
 * 
 */

#include <config.h>

/**
 * @brief Adjust VM image load addresses based on actual hypervisor load address
 *
 * For VMs whose images are not separately loaded, adjusts their load addresses
 * relative to the actual hypervisor image address rather than the virtual
 * address space base.
 * 
 * @see config, vm_config, BAO_VAS_BASE, img_addr, paddr_t, vaddr_t
 */
static void config_adjust_vm_image_addr(void)
{
    for (size_t i = 0; i < config.vmlist_size; i++) {
        struct vm_config* vm_config = &config.vmlist[i];
        if (!vm_config->image.separately_loaded) {
            vm_config->image.load_addr = (vm_config->image.load_addr - BAO_VAS_BASE) + img_addr;
        }
    }
}

/**
 * @brief Weak implementation of memory protection initialization
 * 
 * This function will be left empty if the MPU is not available for the system.
 */
__attribute__((weak)) void config_mem_prot_init(void) { }

/**
 * @brief Initialize system configuration
 *
 * Performs necessary configuration adjustments including VM image
 * address updates and memory protection initialization.
 * 
 * @see config_adjust_vm_image_addr(), config_mem_prot_init().
 */
void config_init(void)
{
    config_adjust_vm_image_addr();
    config_mem_prot_init();
}
