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
    /**
     * The vcpus of the vm's other cpus live in those cpus' structures, which are private to them.
     * Map each vcpu, and nothing else of its cpu, so this cpu reaches it: this cpu only, the
     * others do the same for themselves.
     */
    for (vcpuid_t id = 0; id < vm->cpu_num; id++) {
        struct vcpu* vcpu = vm_get_vcpu(vm, id);
        if (vcpu == &cpu()->vcpu) {
            continue;
        }
        struct mp_region mpr = {
            .base = (vaddr_t)vcpu,
            .size = ALIGN(sizeof(struct vcpu), PAGE_SIZE),
            .mem_flags = PTE_HYP_FLAGS,
            .as_sec = SEC_HYP_VM,
        };
        if (!mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED)) {
            ERROR("Can't map vcpu %d of vm %d\n", id, vm->id);
        }
    }
}

struct vcpu* vm_mem_prot_share_vcpu(struct vcpu* vcpu)
{
    /* Reached where it is, once the vm's cpus map it in vm_mem_prot_cpu_init */
    return vcpu;
}
