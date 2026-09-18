/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __VM_H__
#define __VM_H__

#include <bao.h>
#include <vm_types.h>

#include <mem.h>
#include <cpu.h>
#include <spinlock.h>
#include <emul.h>
#include <interrupts.h>
#include <bitmap.h>
#include <io.h>
#include <ipc.h>
#include <remio.h>
#include <platform_defs.h>

struct vm* vm_init(struct vm* vm, struct cpu_synctoken* vm_init_sync,
    const struct vm_config* config, bool master, vmid_t vm_id);
void vm_start(struct vm* vm, vaddr_t entry);
void vm_emul_add_mem(struct vm* vm, struct emul_mem* emu);
void vm_emul_add_reg(struct vm* vm, struct emul_reg* emu);
emul_handler_t vm_emul_get_mem(struct vm* vm, vaddr_t addr);
emul_handler_t vm_emul_get_reg(struct vm* vm, vaddr_t addr);
void vcpu_init(struct vcpu* vcpu, struct vm* vm, vaddr_t entry);
void vm_msg_broadcast(struct vm* vm, struct cpu_msg* msg);
cpumap_t vm_translate_to_pcpu_mask(struct vm* vm, cpumap_t mask, size_t len);
cpumap_t vm_translate_to_vcpu_mask(struct vm* vm, cpumap_t mask, size_t len);

/* The public part of one of the vm's vcpus; the private part belongs to the cpu running it */
static inline struct vcpu_public* vm_get_vcpu(struct vm* vm, vcpuid_t vcpuid)
{
    if (vcpuid < vm->cpu_num) {
        return vm->vcpus[vcpuid];
    }
    return NULL;
}

static inline cpuid_t vm_translate_to_pcpuid(struct vm* vm, vcpuid_t vcpuid)
{
    struct vcpu_public* vcpu = vm_get_vcpu(vm, vcpuid);

    if (vcpu == NULL) {
        return INVALID_CPUID;
    } else {
        return vcpu->phys_id;
    }
}

static inline vcpuid_t vm_translate_to_vcpuid(struct vm* vm, cpuid_t pcpuid)
{
    if (vm->cpus & (1UL << pcpuid)) {
        return (cpuid_t)bit_count(vm->cpus & ((1UL << pcpuid) - 1UL));
    } else {
        return INVALID_CPUID;
    }
}

static inline bool vm_has_interrupt(struct vm* vm, irqid_t int_id)
{
    return !!bitmap_get(vm->interrupt_bitmap, int_id);
}

static inline void vcpu_inject_hw_irq(struct vcpu* vcpu, irqid_t id)
{
    vcpu_arch_inject_hw_irq(vcpu, id);
}

static inline void vcpu_inject_irq(struct vcpu* vcpu, irqid_t id)
{
    vcpu_arch_inject_irq(vcpu, id);
}

/* ------------------------------------------------------------*/

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config);
/* Called by every cpu of the vm after vm_mem_prot_init, before the vm's address space is used */
void vm_mem_prot_cpu_init(struct vm* vm);

/* ------------------------------------------------------------*/

void vm_arch_init(struct vm* vm, const struct vm_config* config);
void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm);
void vcpu_run(struct vcpu* vcpu);
unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg);
void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val);
unsigned long vcpu_readpc(struct vcpu* vcpu);
void vcpu_writepc(struct vcpu* vcpu, unsigned long pc);
void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry);
bool vcpu_arch_is_on(struct vcpu* vcpu);
void vm_arch_allow_mmio_access(struct vm* vm, struct vm_dev_region* dev);

#endif /* __VM_H__ */
