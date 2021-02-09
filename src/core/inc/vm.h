/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __VM_H__
#define __VM_H__

#include <bao.h>
#include <arch/vm.h>

#include <platform.h>
#include <mem.h>
#include <cpu.h>
#include <spinlock.h>
#include <config.h>
#include <emul.h>
#include <objcache.h>
#include <interrupts.h>
#include <bitmap.h>
#include <iommu.h>
#include <ipc.h>

typedef struct vm {
    uint64_t id;

    const vm_config_t* config;

    spinlock_t lock;
    cpu_synctoken_t sync;
    uint64_t master;

    list_t vcpu_list;
    uint64_t cpu_num;
    uint64_t cpus;

    addr_space_t as;

    vm_arch_t arch;

    list_t emul_list;
    objcache_t emul_oc;

    iommu_vm_t iommu;

    BITMAP_ALLOC(interrupt_bitmap, MAX_INTERRUPTS);

    size_t ipc_num;
    ipc_t *ipcs;
} vm_t;

typedef struct vcpu {
    node_t node;

    struct arch_regs* regs;
    vcpu_arch_t arch;

    uint64_t id;
    uint32_t phys_id;
    bool active;

    vm_t* vm;

    uint8_t stack[STACK_SIZE] __attribute__((aligned(STACK_SIZE)));
} vcpu_t;

extern vm_t vm;
extern struct config* vm_config_ptr;

void vm_init(vm_t* vm, const vm_config_t* config, bool master, uint64_t vm_id);
void vm_start(vm_t* vm, uint64_t entry);
vcpu_t* vm_get_vcpu(vm_t* vm, uint64_t vcpuid);
void vm_emul_add_mem(vm_t* vm, emul_mem_t* emu);
void vm_emul_add_reg(vm_t* vm, emul_reg_t* emu);
emul_handler_t vm_emul_get_mem(vm_t* vm, uint64_t addr);
emul_handler_t vm_emul_get_reg(vm_t* vm, uint64_t addr);
void vcpu_init(vcpu_t* vcpu, vm_t* vm, uint64_t entry);
void vm_msg_broadcast(vm_t* vm, cpu_msg_t* msg);
uint64_t vm_translate_to_pcpu_mask(vm_t* vm, uint64_t mask, size_t len);
uint64_t vm_translate_to_vcpu_mask(vm_t* vm, uint64_t mask, size_t len);

static inline int64_t vm_translate_to_pcpuid(vm_t* vm, uint64_t vcpuid)
{
    return bitmap_find_nth((bitmap_t)&vm->cpus, sizeof(vm->cpus) * 8,
                           vcpuid + 1, 0, true);
}

static inline uint64_t vm_translate_to_vcpuid(vm_t* vm, uint64_t pcpuid)
{
    return bitmap_count((bitmap_t)&vm->cpus, 0, pcpuid, true);
}

static inline int vm_has_interrupt(vm_t* vm, int int_id)
{
    return bitmap_get(vm->interrupt_bitmap, int_id);
}

/* ------------------------------------------------------------*/

void vm_arch_init(vm_t* vm, const vm_config_t* config);
void vcpu_arch_init(vcpu_t* vcpu, vm_t* vm);
void vcpu_run(vcpu_t* vcpu);
uint64_t vcpu_readreg(vcpu_t* vcpu, uint64_t reg);
void vcpu_writereg(vcpu_t* vcpu, uint64_t reg, uint64_t val);
uint64_t vcpu_readpc(vcpu_t* vcpu);
void vcpu_writepc(vcpu_t* vcpu, uint64_t pc);
void vcpu_arch_run(vcpu_t* vcpu);
void vcpu_arch_reset(vcpu_t* vcpu, uint64_t entry);

#endif /* __VM_H__ */
