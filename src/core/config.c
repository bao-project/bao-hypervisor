/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
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
