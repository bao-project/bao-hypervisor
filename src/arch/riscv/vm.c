/**
 * Bao Hypervisor
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

#include <vm.h>
#include <page_table.h>
#include <arch/csrs.h>
#include <arch/vplic.h>
#include <string.h>

void vm_arch_init(vm_t *vm, const vm_config_t *config)
{
    unsigned long root_pt_pa;
    mem_translate(&cpu.as, vm->as.pt.root, &root_pt_pa);

    unsigned long hgatp = (root_pt_pa >> PAGE_SHIFT) | (HGATP_MODE_DFLT) |
                          ((vm->id << HGATP_VMID_OFF) & HGATP_VMID_MSK);

    CSRW(CSR_HGATP, hgatp);

    vplic_init(vm, platform.arch.plic_base);
}

void vcpu_arch_init(vcpu_t *vcpu, vm_t *vm) {
    vcpu->arch.sbi_ctx.lock = SPINLOCK_INITVAL;
    vcpu->arch.sbi_ctx.state = vcpu->id == 0 ?  STARTED : STOPPED;
}

void vcpu_arch_reset(vcpu_t *vcpu, uint64_t entry)
{
    memset(vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu->regs->hstatus = HSTATUS_SPV | HSTATUS_VSXL_64;
    vcpu->regs->sstatus = SSTATUS_SPP_BIT | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY;
    vcpu->regs->sepc = entry;
    vcpu->regs->a0 = vcpu->arch.hart_id = vcpu->id;
    vcpu->regs->a1 = 0;  // according to sbi it should be the dtb load address

    CSRW(CSR_HCOUNTEREN, HCOUNTEREN_TM);
    CSRW(CSR_HTIMEDELTA, 0);
    CSRW(CSR_VSSTATUS, SSTATUS_SD | SSTATUS_FS_DIRTY | SSTATUS_XS_DIRTY);
    CSRW(CSR_HIE, 0);
    CSRW(CSR_VSTVEC, 0);
    CSRW(CSR_VSSCRATCH, 0);
    CSRW(CSR_VSEPC, 0);
    CSRW(CSR_VSCAUSE, 0);
    CSRW(CSR_VSTVAL, 0);
    CSRW(CSR_HVIP, 0);
    CSRW(CSR_VSATP, 0);
}

uint64_t vcpu_readreg(vcpu_t *vcpu, uint64_t reg)
{
    if ((reg <= 0) || (reg > 31)) return 0;
    return vcpu->regs->x[reg - 1];
}

void vcpu_writereg(vcpu_t *vcpu, uint64_t reg, uint64_t val)
{
    if ((reg <= 0) || (reg > 31)) return;
    vcpu->regs->x[reg - 1] = val;
}

uint64_t vcpu_readpc(vcpu_t *vcpu)
{
    return vcpu->regs->sepc;
}

void vcpu_writepc(vcpu_t *vcpu, uint64_t pc)
{
    vcpu->regs->sepc = pc;
}

static int find_max_alignment(uintptr_t addr)
{
    for (int i = 3; i > 0; i--) {
        uintptr_t mask = (1 << i) - 1;
        if ((addr & mask) == 0) {
            return (1 << i);
        }
    }

    return 1;
}

static inline uint64_t hlvb(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x30, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvbu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x30, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}


static inline uint64_t hlvh(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvhu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvxhu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x3\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

uint64_t hlvw(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvwu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

uint64_t hlvxwu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x3\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvd(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x36, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

#define VM_LOAD(width, d, s)                                                 \
    ({                                                                       \
        switch (width) {                                                     \
            case 1:                                                          \
                *((uint8_t *)d) = hlvbu(s);                                  \
                break;                                                       \
            case 2:                                                          \
                *((uint16_t *)d) = hlvhu(s);                                 \
                break;                                                       \
            case 4:                                                          \
                *((uint32_t *)d) = hlvwu(s);                                 \
                break;                                                       \
            case 8:                                                          \
                *((uint64_t *)d) = hlvd(s);                                  \
                break;                                                       \
                /*default: WARNING("trying to perform unsoported vm load")*/ \
        }                                                                    \
    })

#define VM_LOAD_EXEC(width, d, s)                                            \
    ({                                                                       \
        switch (width) {                                                     \
            case 2:                                                          \
                *((uint16_t *)d) = hlvxhu(s);                                \
                break;                                                       \
            case 4:                                                          \
                *((uint32_t *)d) = hlvxwu(s);                                \
                break;                                                       \
                /*default: WARNING("trying to perform unsoported vm load")*/ \
        }                                                                    \
    })


bool vm_readmem(vm_t *vm, void *dest, uintptr_t vmaddr, size_t n, bool exec)
{
    if(n == 0) return true;

    if (vm == cpu.vcpu->vm) {
        while (n > 0 && !cpu.arch.hlv_except) {
            int width = find_max_alignment(((uintptr_t)dest) | vmaddr);
            while(width > n) width = PPOT(width);
            /**
             * You can only load aligned halfword or word instructions.
             */
            if(exec && width == 8) width = 4;
            if(exec && width == 1) break;
            size_t count = n / width;
            for (int i = 0; i < count; i++) {
                if(exec) VM_LOAD_EXEC(width, dest, vmaddr);
                else VM_LOAD(width, dest, vmaddr);
                dest += width;
                vmaddr += width;
            }
            n -= (count * width);
        }
    } 

    bool hlv_except = cpu.arch.hlv_except;
    cpu.arch.hlv_except = false; 

    return n == 0 && !hlv_except;
}

void vcpu_arch_run(vcpu_t *vcpu){

    if(vcpu->arch.sbi_ctx.state == STARTED){
        vcpu_arch_entry();
    } else {
        cpu_idle();
    }    

}
