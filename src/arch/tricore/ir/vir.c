/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vir.h>
#include <cpu.h>
#include <emul.h>
#include <mem.h>
#include <vm.h>
#include <interrupts.h>
#include <arch/csrs.h>

void vir_set_hw(struct vm* vm, irqid_t id)
{
    if (id < IR_MAX_INTERRUPTS) {
        bitmap_set(vm->arch.vir.hw, id);
    }
}


void vir_inject(struct vcpu* vcpu, irqid_t id)
{
    struct vir* vir = &vcpu->vm->arch.vir;
    spin_lock(&vir->lock);
    if (id > 0 && id < IR_MAX_INTERRUPTS && !vir_get_pend(vcpu, id)) {
        bitmap_set(vir->pend, id);

        if (vir_get_hw(vcpu, id)) {
            struct ir_cntxt vcntxt = { vcpu->id, PRIV_S };
            ssize_t vcntxt_id = ir_plat_cntxt_to_id(vcntxt);
            vir_update_hart_line(vcpu, (size_t)vcntxt_id);
        } else {
            for (size_t i = 0; i < vir->cntxt_num; i++) {
                if (ir_plat_id_to_cntxt(i).mode != PRIV_S) {
                    continue;
                }
                if (vir_get_enbl(vcpu, i, id) &&
                    vir_get_prio(vcpu, id) > vir_get_threshold(vcpu, i)) {
                    vir_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vir->lock);
}

static void vir_emul_prio_access(struct emul_access* acc)
{

}

static void vir_emul_pend_access(struct emul_access* acc)
{
    // pend registers are read only
    if (acc->write) {
        return;
    }

    vcpu_writereg(cpu()->vcpu, acc->reg, val);
}

static void vir_emul_enbl_access(struct emul_access* acc)
{
    unsigned long val = acc->write ? vcpu_readreg(cpu()->vcpu, acc->reg) : 0;


    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, val);
    }
}

static bool vir_src_emul_handler(struct emul_access* acc)
{
    // only allow aligned word accesses
    if (acc->width != 4 || acc->addr & 0x3) {
        return false;
    }

    switch ((acc->addr >> 12) & 0x3) {
        case 0:
            vir_emul_prio_access(acc);
            break;
        case 1:
            vir_emul_pend_access(acc);
            break;
        default:
            vir_emul_enbl_access(acc);
            break;
    }

    return true;
}

static bool vir_hart_emul_handler(struct emul_access* acc)
{
    // only allow aligned word accesses
    if (acc->width > 4 || acc->addr & 0x3) {
        return false;
    }

    switch (acc->addr & 0xf) {

    }

    return true;
}

void vir_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    if (cpu()->id == vm->master) {
        vm->arch.vir.ir_src_emul = (struct emul_mem){ .va_base = vm_irqc_dscrp->ir.base,
            .size = sizeof(struct ir_src_hw),
            .handler = vir_src_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vir.ir_src_emul);

        vm->arch.vir.ir_threshold_emul =
            (struct emul_mem){ .va_base = vm_irqc_dscrp->ir.base + IR_THRESHOLD_OFF,
                .size = sizeof(struct ir_icu_hw) * vm->cpu_num * PLAT_IR_CNTXT_PER_HART,
                .handler = vir_hart_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vir.ir_threshold_emul);

        /* assumes 2 contexts per hart */
        vm->arch.vir.cntxt_num = vm->cpu_num * 2;
    }
}
