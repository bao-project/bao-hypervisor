/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VM_H__
#define __VM_H__

#include <bao.h>
#include <arch/vm.h>

#include <mem.h>
#include <cpu.h>
#include <spinlock.h>
#include <emul.h>
#include <interrupts.h>
#include <bitmap.h>
#include <io.h>
#include <ipc.h>

struct vm_mem_region {
    paddr_t base;
    size_t size;
    colormap_t colors;
    bool place_phys;
    paddr_t phys;
};

struct vm_dev_region {
    paddr_t pa;
    vaddr_t va;
    size_t size;
    size_t interrupt_num;
    irqid_t *interrupts;
    deviceid_t id; /* bus master id for iommu effects */
};
    
struct vm_platform {
    size_t cpu_num;

    size_t region_num;
    struct vm_mem_region *regions;

    size_t ipc_num;
    struct ipc *ipcs;

    size_t dev_num;
    struct vm_dev_region *devs;

    // /**
    //  * In MPU-based platforms which might also support virtual memory 
    //  * (i.e. aarch64 cortex-r) the hypervisor sets up the VM using an MPU by
    //  * default. If the user wants this VM to use the MMU they must set the
    //  * config mmu parameter to true;
    //  */
    bool mmu;

    struct arch_vm_platform arch;
};

struct vm {
    vmid_t id;

    const struct vm_config* config;

    spinlock_t lock;
    struct cpu_synctoken sync;
    cpuid_t master;

    struct vcpu *vcpus;
    size_t cpu_num;
    cpumap_t cpus;

    struct addr_space as;

    struct vm_arch arch;

    struct list emul_mem_list;
    struct list emul_reg_list;

    struct vm_io io;

    BITMAP_ALLOC(interrupt_bitmap, MAX_INTERRUPTS);

    size_t ipc_num;
    struct ipc *ipcs;
};

struct vcpu {
    node_t node;

    struct arch_regs regs;
    struct vcpu_arch arch;

    vcpuid_t id;
    cpuid_t phys_id;
    bool active;

    struct vm* vm;
};

struct vm_allocation {
    vaddr_t base;
    size_t size;
    struct vm *vm;
    struct vcpu *vcpus;
};

extern struct vm vm;

struct vm* vm_init(struct vm_allocation* vm_alloc, const struct vm_config* config,
    bool master, vmid_t vm_id);
void vm_start(struct vm* vm, vaddr_t entry);
void vm_emul_add_mem(struct vm* vm, struct emul_mem* emu);
void vm_emul_add_reg(struct vm* vm, struct emul_reg* emu);
emul_handler_t vm_emul_get_mem(struct vm* vm, vaddr_t addr);
emul_handler_t vm_emul_get_reg(struct vm* vm, vaddr_t addr);
void vcpu_init(struct vcpu* vcpu, struct vm* vm, vaddr_t entry);
void vm_msg_broadcast(struct vm* vm, struct cpu_msg* msg);
cpumap_t vm_translate_to_pcpu_mask(struct vm* vm, cpumap_t mask, size_t len);
cpumap_t vm_translate_to_vcpu_mask(struct vm* vm, cpumap_t mask, size_t len);

static inline struct vcpu* vm_get_vcpu(struct vm* vm, vcpuid_t vcpuid) {
    if (vcpuid < vm->cpu_num) {
        return &vm->vcpus[vcpuid];
    }
    return NULL;
}

static inline cpuid_t vm_translate_to_pcpuid(struct vm* vm, vcpuid_t vcpuid)
{
    struct vcpu *vcpu = vm_get_vcpu(vm, vcpuid);

    if(vcpu == NULL) {
        return INVALID_CPUID;
    } else {
        return vcpu->phys_id;
    }
}

static inline vcpuid_t vm_translate_to_vcpuid(struct vm* vm, cpuid_t pcpuid)
{
    if (vm->cpus & (1UL << pcpuid)) {
        return (cpuid_t)bit_count(vm->cpus & BIT_MASK(0, pcpuid));
    } else {
        return INVALID_CPUID;
    }
}

static inline bool vm_has_interrupt(struct vm* vm, irqid_t int_id)
{
    return !!bitmap_get(vm->interrupt_bitmap, int_id);
}

static inline void vcpu_inject_hw_irq(struct vcpu *vcpu, irqid_t id)
{
    vcpu_arch_inject_hw_irq(vcpu, id);
}

static inline void vcpu_inject_irq(struct vcpu *vcpu, irqid_t id)
{
    vcpu_arch_inject_irq(vcpu, id);
}

/* ------------------------------------------------------------*/

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config);

/* ------------------------------------------------------------*/

void vm_arch_init(struct vm* vm, const struct vm_config* config);
void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm);
void vcpu_run(struct vcpu* vcpu);
unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg);
void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val);
unsigned long vcpu_readpc(struct vcpu* vcpu);
void vcpu_writepc(struct vcpu* vcpu, unsigned long pc);
void vcpu_arch_run(struct vcpu* vcpu);
void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry);

#endif /* __VM_H__ */
