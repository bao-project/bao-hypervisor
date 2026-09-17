/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VM_TYPES_H__
#define __VM_TYPES_H__

/**
 * The vm description and its runtime state, kept apart from the vm API so that the cpu structure
 * (cpu.h) can embed a copy of the description.
 */

#include <bao.h>
#include <vcpu.h>
#include <arch/vm.h>
#include <cpu_sync.h>
#include <mem.h>
#include <list.h>
#include <bitmap.h>
#include <io.h>
#include <interrupts.h>
#include <platform_defs.h>

struct vm_config;
struct ipc;
struct remio_dev;

struct vm_mem_region {
    paddr_t base;
    size_t size;
    colormap_t colors;
    struct {
        bool place_phys;
        paddr_t phys;
        bool reserved;
    };
};

struct vm_dev_region {
    paddr_t pa;
    vaddr_t va;
    size_t size;
    size_t interrupt_num;
    irqid_t* interrupts;
    deviceid_t id; /* bus master id for iommu effects */
};

struct vm_platform {
    size_t cpu_num;

    size_t region_num;
    struct vm_mem_region* regions;

    size_t ipc_num;
    struct ipc* ipcs;

    size_t dev_num;
    struct vm_dev_region* devs;

    size_t remio_dev_num;
    struct remio_dev* remio_devs;

    // /**
    //  * In MPU-based platforms which might also support virtual memory
    //  * (i.e. aarch64 cortex-r) the hypervisor sets up the VM using an MPU by
    //  * default. If the user wants this VM to use the MMU they must set the
    //  * config mmu parameter to true;
    //  */
    bool mmu;

    struct arch_vm_platform arch;
};

/**
 * Mutable state of a vm: what is written after initialization or is inherently unique (locks,
 * synchronization, the guest address space), as opposed to the description, fixed once the vm is
 * initialized. It is kept apart from the description, exactly one instance per vm in a static
 * pool in globally accessible memory, bound to the vm by its master cpu in vm_init(), so that
 * cpus can hold local copies of the description.
 */
struct vm_mutable {
    spinlock_t lock;
    struct cpu_synctoken sync;
    struct addr_space as;
    struct vm_arch_mutable arch;
};

/**
 * Description of a vm. Every field of this structure is fixed once vm_init() completes: it is
 * written only during initialization, by the master cpu or by each cpu under the init barriers,
 * which is what lets a cpu run on a local copy of it (see CONFIG_CPU_LOCAL_COPIES).
 */
struct vm {
    vmid_t id;

    const struct vm_config* config;

    cpuid_t master;

    /* The vm's vcpus, indexed by vcpu id: the public part of each, valid on every cpu */
    struct vcpu_public* vcpus[PLAT_CPU_NUM];
    size_t cpu_num;
    cpumap_t cpus;

    struct vm_arch arch;

    struct list emul_mem_list;
    struct list emul_reg_list;

    struct vm_io io;

    BITMAP_ALLOC(interrupt_bitmap, MAX_GUEST_INTERRUPTS);

    size_t ipc_num;
    struct ipc* ipcs;

    size_t remio_dev_num;
    struct remio_dev* remio_devs;

    /* The vm's mutable state, in the pool of vm.c, bound by the master cpu in vm_init() */
    struct vm_mutable* mut;
};

#endif /* __VM_TYPES_H__ */
