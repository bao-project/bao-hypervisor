/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/vgic.h>
#include <arch/vgicv2.h>

#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>
#include <platform.h>

bool vgic_int_has_other_target(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool has_other_targets = (interrupt->targets & ~(1 << cpu()->id)) != 0;
    return !priv && has_other_targets;
}

uint8_t vgic_int_ptarget_mask(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    return interrupt->targets;
}

bool vgicd_set_trgt(struct vcpu *vcpu, struct vgic_int *interrupt, cpumap_t targets)
{
    if (gic_is_priv(interrupt->id)) {
        return false;
    }

    uint8_t prev_targets = interrupt->targets;
    targets = vm_translate_to_pcpu_mask(vcpu->vm, targets, GIC_TARGET_BITS);
    interrupt->targets = (uint8_t)targets;
    return prev_targets != targets;
}

void vgicd_set_trgt_hw(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    gicd_set_trgt(interrupt->id, interrupt->targets);
}

cpumap_t vgicd_get_trgt(struct vcpu *vcpu, struct vgic_int *interrupt)
{
    if (gic_is_priv(interrupt->id)) {
        return (((cpumap_t)1) << vcpu->id);
    } else {
        return vm_translate_to_vcpu_mask(vcpu->vm, interrupt->targets,
                                                  GIC_TARGET_BITS);
    }
}

void vgicd_emul_sgiregs_access(struct emul_access *acc,
                               struct vgic_reg_handler_info *handlers,
                               bool gicr_access, vcpuid_t vgicr_id)
{
    unsigned long val = acc->write ? vcpu_readreg(cpu()->vcpu, acc->reg) : 0;

    if ((acc->addr & 0xfff) == (((uintptr_t)&gicd->SGIR) & 0xfff)) {
        if (acc->write) {
            cpumap_t trgtlist = 0;
            irqid_t int_id = GICD_SGIR_SGIINTID(val);
            switch (GICD_SGIR_TRGLSTFLT(val)) {
                case 0:
                    trgtlist = vm_translate_to_pcpu_mask(
                        cpu()->vcpu->vm, GICD_SGIR_CPUTRGLST(val),
                        GIC_TARGET_BITS);
                    break;
                case 1:
                    trgtlist = cpu()->vcpu->vm->cpus & ~(1U << cpu()->vcpu->phys_id);
                    break;
                case 2:
                    trgtlist = (1U << cpu()->id);
                    break;
                case 3:
                    return;
            }

            vgic_send_sgi_msg(cpu()->vcpu, trgtlist, int_id);
        }

    } else {
        // TODO: CPENDSGIR and SPENDSGIR access
    }
}

struct vgic_reg_handler_info itargetr_info = {
    vgic_emul_generic_access,
    0b0101,
    VGIC_ITARGETSR_ID,
    offsetof(struct gicd_hw, ITARGETSR),
    8,
    vgicd_get_trgt,
    vgicd_set_trgt,
    vgicd_set_trgt_hw,
};

struct vgic_reg_handler_info sgir_info = {
    vgicd_emul_sgiregs_access,
    0b0100,
};

void vgic_inject_sgi(struct vcpu *vcpu, struct vgic_int *interrupt, vcpuid_t source)
{
    spin_lock(&interrupt->lock);

    vgic_remove_lr(vcpu, interrupt);

    uint8_t pendstate = interrupt->sgi.pend;
    uint8_t new_pendstate = pendstate | (1U << source);

    if (pendstate ^ new_pendstate) {
        interrupt->sgi.pend = new_pendstate;
        if (new_pendstate) {
            interrupt->state |= PEND;
        } else {
            interrupt->state &= ~PEND;
        }

        if (interrupt->state != INV) {
            vgic_add_lr(vcpu, interrupt);
        }
    }

    spin_unlock(&interrupt->lock);
}

void vgic_init(struct vm *vm, const struct vgic_dscrp *vgic_dscrp)
{
    vm->arch.vgicd.CTLR = 0;
    size_t vtyper_itln = vgic_get_itln(vgic_dscrp);
    vm->arch.vgicd.int_num = 32 * (vtyper_itln + 1);
    vm->arch.vgicd.TYPER =
        ((vtyper_itln << GICD_TYPER_ITLN_OFF) & GICD_TYPER_ITLN_MSK) |
        (((vm->cpu_num - 1) << GICD_TYPER_CPUNUM_OFF) & GICD_TYPER_CPUNUM_MSK);
    vm->arch.vgicd.IIDR = gicd->IIDR;

    size_t n = NUM_PAGES(sizeof(struct gicc_hw));
    mem_alloc_map_dev(&vm->as, SEC_VM_ANY,(vaddr_t)vgic_dscrp->gicc_addr, 
        (vaddr_t)platform.arch.gic.gicv_addr, n);

    size_t vgic_int_size = vm->arch.vgicd.int_num * sizeof(struct vgic_int);
    vm->arch.vgicd.interrupts =
        mem_alloc_page(NUM_PAGES(vgic_int_size), SEC_HYP_VM, false);
    if (vm->arch.vgicd.interrupts == NULL) {
        ERROR("failed to alloc vgic");
    }

    for (size_t i = 0; i < vm->arch.vgicd.int_num; i++) {
        vm->arch.vgicd.interrupts[i].owner = NULL;
        vm->arch.vgicd.interrupts[i].lock = SPINLOCK_INITVAL;
        vm->arch.vgicd.interrupts[i].id = i + GIC_CPU_PRIV;
        vm->arch.vgicd.interrupts[i].state = INV;
        vm->arch.vgicd.interrupts[i].prio = GIC_LOWEST_PRIO;
        vm->arch.vgicd.interrupts[i].cfg = 0;
        vm->arch.vgicd.interrupts[i].targets = 0;
        vm->arch.vgicd.interrupts[i].hw = false;
        vm->arch.vgicd.interrupts[i].in_lr = false;
        vm->arch.vgicd.interrupts[i].enabled = false;
    }

    vm->arch.vgicd_emul = (struct emul_mem) {
        .va_base = vgic_dscrp->gicd_addr,
        .size = ALIGN(sizeof(struct gicd_hw), PAGE_SIZE),
        .handler = vgicd_emul_handler
    };
    vm_emul_add_mem(vm, &vm->arch.vgicd_emul);

    list_init(&vm->arch.vgic_spilled);
    vm->arch.vgic_spilled_lock = SPINLOCK_INITVAL;
}

void vgic_cpu_init(struct vcpu *vcpu)
{
    for (size_t i = 0; i < GIC_CPU_PRIV; i++) {
        vcpu->arch.vgic_priv.interrupts[i].owner = vcpu;
        vcpu->arch.vgic_priv.interrupts[i].lock = SPINLOCK_INITVAL;
        vcpu->arch.vgic_priv.interrupts[i].id = i;
        vcpu->arch.vgic_priv.interrupts[i].state = INV;
        vcpu->arch.vgic_priv.interrupts[i].prio = GIC_LOWEST_PRIO;
        vcpu->arch.vgic_priv.interrupts[i].cfg = 0;
        vcpu->arch.vgic_priv.interrupts[i].sgi.act = 0;
        vcpu->arch.vgic_priv.interrupts[i].sgi.pend = 0;                              
        vcpu->arch.vgic_priv.interrupts[i].hw = false;
        vcpu->arch.vgic_priv.interrupts[i].in_lr = false;
        vcpu->arch.vgic_priv.interrupts[i].enabled = false;
    }

    for (size_t i = 0; i < GIC_MAX_SGIS; i++) {
        vcpu->arch.vgic_priv.interrupts[i].enabled = true;
    }

    list_init(&vcpu->arch.vgic_spilled);
}
