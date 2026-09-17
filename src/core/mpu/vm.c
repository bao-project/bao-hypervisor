/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config)
{
    UNUSED_ARG(config);

    as_init(&vm->as, AS_VM, 0);

    if (DEFINED(MMIO_SLAVE_SIDE_PROT) && (vm->master == cpu()->id)) {
        mem_mmio_init_regions(&vm->as);
    }
}

void vm_mem_prot_cpu_init(struct vm* vm)
{
    /* Nothing to reach: the vm's state and the public vcpu state are in global memory */
    UNUSED_ARG(vm);
}
