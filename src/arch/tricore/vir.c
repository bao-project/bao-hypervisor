/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/vir.h>
#include <arch/ir.h>
#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <vm.h>
#include <arch/vm.h>
#include <platform.h>
#include <config.h>

extern volatile const size_t VIR_IPI_ID;
extern volatile bitmap_granule_t* valid;

#define GUEST_SRC_ACCESS (~IR_SRC_VM_MASK)

static void vir_emul_src_access(struct emul_access* acc, struct vcpu* vcpu, unsigned long irqid)
{
    size_t addr_off = acc->addr & 0x3UL;
    unsigned long mask = BIT_MASK(0, acc->width * 8);

    if (acc->write) {
        uint32_t orig = (uint32_t)ir_src_get_node(irqid);
        uint32_t val = vcpu_readreg(vcpu, acc->reg) & mask;

        uint32_t tos = IR_SRC_GET_TOS(val);
        uint32_t orig_tos = IR_SRC_GET_TOS(orig);

        if (tos > PLAT_CPU_NUM) {
            WARNING("TOS must belong to CPUs!");
            return;
        }

        if (orig_tos != SRC_TOS_UNASSIGNED && tos != cpu()->id) {
            WARNING("TOS is already set up (%d)!", orig_tos);
            return;
        }

        val = val << (addr_off * 8);
        /* reset hyp controlled fields */
        val = (val & GUEST_SRC_ACCESS) | (orig & ~GUEST_SRC_ACCESS);

        ir_src_set_node(irqid, val);
    } else {
        uint32_t val = ir_src->SRC[irqid] & GUEST_SRC_ACCESS;
        val = (val >> (addr_off * 8)) & mask;
        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static bool vir_src_emul_handler(struct emul_access* acc)
{
    if (!IS_ALIGNED(acc->addr, acc->width) || acc->width < 2) {
        if (!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
        return true;
    }

    uint32_t addr = acc->addr & ~0x3UL;

    uint32_t irqid = (addr - platform.arch.ir.src_addr) / sizeof(ir_src->SRC[0]);

    if (!vm_has_interrupt(cpu()->vcpu->vm, irqid)) {
        ERROR("Access to unsigned interrupt %u", irqid);
        return false;
    }

    vir_emul_src_access(acc, cpu()->vcpu, irqid);
    return true;
}

void vir_inject(struct vcpu* vcpu, irqid_t id)
{
    struct vm* vm = vcpu->vm;

    if (!vm_has_interrupt(vm, id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    ir_set_pend(id);
}

void vir_init(struct vm* vm)
{
    /* Make sure the SRC is unmapped from the MMIO regions.
        Guests should not be able to access the SRC since they could tamper
        with other guests interrupts
    */
    mem_unmap(&vm->as, (vaddr_t)platform.arch.ir.src_addr, NUM_PAGES(sizeof(struct ir_src_hw)),
        MEM_DONT_FREE_PAGES);

    // Install emul handler for accesses to the SRC
    vm->arch.vir_src_emul = (struct emul_mem){ .va_base = (vaddr_t)platform.arch.ir.src_addr,
        .size = ALIGN(sizeof(struct ir_src_hw), PAGE_SIZE),
        .handler = vir_src_emul_handler };
    vm_emul_add_mem(vm, &vm->arch.vir_src_emul);
}

void vir_vcpu_init(struct vcpu* vcpu)
{
    uint32_t vmid = VMID_TO_HWVM(vcpu->vm->id);
    if (vmid > VM_ARCH_MAX_NUM) {
        ERROR("Unsuported vm id %u > %u", vmid, VM_ARCH_MAX_NUM);
        return;
    }
    ir_assign_icu_to_vm(cpu()->id, vmid);
}
