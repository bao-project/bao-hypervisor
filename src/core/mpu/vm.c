/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config) {
    as_init(&vm->as, AS_VM, vm->id, 0);
}

