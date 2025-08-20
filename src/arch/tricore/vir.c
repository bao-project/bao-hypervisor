/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/vir.h>
#include <arch/ir.h>
#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>
#include <arch/vm.h>
#include <platform.h>
#include <config.h>

extern volatile const size_t VIR_IPI_ID;
extern volatile bitmap_granule_t* valid;

static void vir_emul_src_access(struct emul_access* acc, struct vcpu* vcpu, unsigned long irqid)
{
    if (acc->write) {
        uint32_t orig = (unsigned long)ir_src_get_node(irqid);
        uint32_t val = vcpu_readreg(vcpu, acc->reg);
        uint32_t tos = IR_SRC_GET_TOS(val);
        uint32_t orig_tos = IR_SRC_GET_TOS(orig);
        uint32_t vm = IR_SRC_GET_VM(orig);

        /* TODO: Validate is the tos belongs to the VM or the DMA belongs to BM */
        if (tos > PLAT_CPU_NUM) {
            WARNING("Other TOS receiving the interrupt is currently not supported!");
            return;
        }

        if (orig_tos != 0xF && orig_tos != cpu()->id) {
            WARNING("TOS is already set up (%d)!", orig_tos);
            return;
        }

        uint32_t out = ((val & (unsigned long)~(0x7 << 8)) | vm << 8);

        ir_src_set_node(irqid, out);
    } else {
        uint32_t val = ir_src->SRC[irqid];

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static bool ir_src_emul_handler(struct emul_access* acc)
{
    uint32_t addr = acc->addr;

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
    if (DEFINED(MMIO_SLAVE_SIDE_PROT)) {
        // Make sure the SRC is unmapped from the MMIO regions
        mem_unmap(&vm->as, (vaddr_t)platform.arch.ir.src_addr, NUM_PAGES(sizeof(struct ir_src_hw)),
            false);
    } else {
        // Map access to the GPSR nodes in INT.
        mem_alloc_map_dev(&vm->as, SEC_VM_ANY,
            (vaddr_t)(platform.arch.ir.GPSR_offset + platform.arch.ir.int_addr),
            (vaddr_t)(platform.arch.ir.GPSR_offset + platform.arch.ir.int_addr),
            NUM_PAGES(platform.arch.ir.GPSR_size));
    }

    // Install emul handler for accesses to the SRC
    vm->arch.vir_src_emul = (struct emul_mem){ .va_base = (vaddr_t)platform.arch.ir.src_addr,
        .size = ALIGN(sizeof(struct ir_src_hw), PAGE_SIZE),
        .handler = ir_src_emul_handler };
    vm_emul_add_mem(vm, &vm->arch.vir_src_emul);
}

void vir_vcpu_init(struct vcpu* vcpu)
{
    ir_assign_icu_to_vm(cpu()->id, vcpu->vm);
}
