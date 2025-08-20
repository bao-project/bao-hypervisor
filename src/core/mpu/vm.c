/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>

#ifndef VM_TO_AS_ID
#define VM_TO_AS_ID(x) (x)
#endif

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config)
{
    UNUSED_ARG(config);

    as_init(&vm->as, AS_VM, VM_TO_AS_ID(vm->id), vm->cpus, 0);
}
