/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>

void config_adjust_vm_image_addr(paddr_t load_addr)
{
    for (size_t i = 0; i < config.vmlist_size; i++) {
        struct vm_config *vm_config = &config.vmlist[i];
        if (!vm_config->image.separately_loaded) {
            vm_config->image.load_addr =
                (vm_config->image.load_addr - BAO_VAS_BASE) + load_addr;
        }
    }
}

__attribute__((weak)) void config_mem_prot_init(paddr_t load_addr) {}

void config_init(paddr_t load_addr) {
    config_adjust_vm_image_addr(load_addr);
    config_mem_prot_init(load_addr);
}
