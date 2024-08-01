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

static ssize_t vir_vcntxt_to_pcntxt(struct vcpu* vcpu, size_t vcntxt_id)
{
    struct ir_cntxt vcntxt = ir_plat_id_to_cntxt(vcntxt_id);
    struct ir_cntxt pcntxt;

    ssize_t pcntxt_id = -1;
    pcntxt.mode = vcntxt.mode;
    pcntxt.hart_id = vm_translate_to_pcpuid(vcpu->vm, vcntxt.hart_id);
    if (pcntxt.hart_id != INVALID_CPUID) {
        pcntxt_id = ir_plat_cntxt_to_id(pcntxt);
    }

    return pcntxt_id;
}

static bool vir_vcntxt_valid(struct vcpu* vcpu, size_t vcntxt_id)
{
    struct ir_cntxt vcntxt = ir_plat_id_to_cntxt(vcntxt_id);
    return (unsigned int)vcntxt_id < vcpu->vm->arch.vir.cntxt_num && vcntxt.mode <= PRIV_S;
}

static bool vir_get_pend(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct vir* vir = &vcpu->vm->arch.vir;
    if (id < IR_MAX_INTERRUPTS) {
        ret = bitmap_get(vir->pend, id);
    }
    return ret;
}

static bool vir_get_act(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct vir* vir = &vcpu->vm->arch.vir;
    if (id < IR_MAX_INTERRUPTS) {
        ret = bitmap_get(vir->act, id);
    }
    return ret;
}

static bool vir_get_enbl(struct vcpu* vcpu, size_t vcntxt, irqid_t id)
{
    bool ret = false;
    struct vir* vir = &vcpu->vm->arch.vir;
    if (id < IR_MAX_INTERRUPTS) {
        ret = !!bitmap_get(vir->enbl[vcntxt], id);
    }
    return ret;
}

static uint32_t vir_get_prio(struct vcpu* vcpu, irqid_t id)
{
    uint32_t ret = 0;
    struct vir* vir = &vcpu->vm->arch.vir;
    if (id < IR_MAX_INTERRUPTS) {
        ret = vir->prio[id];
    }
    return ret;
}

void vir_set_hw(struct vm* vm, irqid_t id)
{
    if (id < IR_MAX_INTERRUPTS) {
        bitmap_set(vm->arch.vir.hw, id);
    }
}

static bool vir_get_hw(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct vir* vir = &vcpu->vm->arch.vir;
    if (id < IR_MAX_INTERRUPTS) {
        ret = bitmap_get(vir->hw, id);
    }
    return ret;
}

static uint32_t vir_get_threshold(struct vcpu* vcpu, size_t vcntxt)
{
    struct vir* vir = &vcpu->vm->arch.vir;
    return vir->threshold[vcntxt];
}

static irqid_t vir_next_pending(struct vcpu* vcpu, size_t vcntxt)
{
    uint32_t max_prio = 0;
    irqid_t int_id = 0;

    for (irqid_t i = 0; i < IR_MAX_INTERRUPTS; i++) {
        if (vir_get_pend(vcpu, i) && !vir_get_act(vcpu, i) && vir_get_enbl(vcpu, vcntxt, i)) {
            uint32_t prio = vir_get_prio(vcpu, i);
            if (prio > max_prio) {
                max_prio = prio;
                int_id = i;
            }
        }
    }

    if (max_prio > vir_get_threshold(vcpu, vcntxt)) {
        return int_id;
    } else {
        return 0;
    }
}

enum { UPDATE_HART_LINE };
static void vir_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vir_ipi_handler, VIR_IPI_ID)

static void vir_update_hart_line(struct vcpu* vcpu, size_t vcntxt)
{
    ssize_t pcntxt_id = vir_vcntxt_to_pcntxt(vcpu, vcntxt);
    struct ir_cntxt pcntxt = ir_plat_id_to_cntxt((size_t)pcntxt_id);
    if (pcntxt.hart_id == cpu()->id) {
        irqid_t id = vir_next_pending(vcpu, vcntxt);
        if (id != 0) {
            csrs_hvip_set(HIP_VSEIP);
        } else {
            csrs_hvip_clear(HIP_VSEIP);
        }
    } else {
        struct cpu_msg msg = { (uint32_t)VIR_IPI_ID, UPDATE_HART_LINE, vcntxt };
        cpu_send_msg(pcntxt.hart_id, &msg);
    }
}

static void vir_ipi_handler(uint32_t event, uint64_t data)
{
    switch (event) {
        case UPDATE_HART_LINE:
            vir_update_hart_line(cpu()->vcpu, data);
            break;
        default:
            WARNING("Unknown VIR IPI event");
            break;
    }
}

static void vir_set_threshold(struct vcpu* vcpu, size_t vcntxt, uint32_t threshold)
{
    struct vir* vir = &vcpu->vm->arch.vir;
    spin_lock(&vir->lock);
    vir->threshold[vcntxt] = threshold;
    ssize_t pcntxt = vir_vcntxt_to_pcntxt(vcpu, vcntxt);
    ir_set_threshold((size_t)pcntxt, threshold);
    spin_unlock(&vir->lock);

    vir_update_hart_line(vcpu, vcntxt);
}

static void vir_set_enbl(struct vcpu* vcpu, size_t vcntxt, irqid_t id, bool set)
{
    struct vir* vir = &vcpu->vm->arch.vir;
    spin_lock(&vir->lock);
    if (id < IR_MAX_INTERRUPTS && vir_get_enbl(vcpu, vcntxt, id) != set) {
        if (set) {
            bitmap_set(vir->enbl[vcntxt], id);
        } else {
            bitmap_clear(vir->enbl[vcntxt], id);
        }

        if (vir_get_hw(vcpu, id)) {
            ssize_t pcntxt_id = vir_vcntxt_to_pcntxt(vcpu, vcntxt);
            ir_set_enbl((size_t)pcntxt_id, id, set);
        } else {
            vir_update_hart_line(vcpu, vcntxt);
        }
    }
    spin_unlock(&vir->lock);
}

static void vir_set_prio(struct vcpu* vcpu, irqid_t id, uint32_t prio)
{
    struct vir* vir = &vcpu->vm->arch.vir;
    spin_lock(&vir->lock);
    if (id < IR_MAX_INTERRUPTS && vir_get_prio(vcpu, id) != prio) {
        vir->prio[id] = prio;
        if (vir_get_hw(vcpu, id)) {
            ir_set_prio(id, prio);
        } else {
            for (size_t i = 0; i < vir->cntxt_num; i++) {
                if (ir_plat_id_to_cntxt(i).mode != PRIV_S) {
                    continue;
                }
                if (vir_get_enbl(vcpu, i, id)) {
                    vir_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vir->lock);
}

static irqid_t vir_claim(struct vcpu* vcpu, size_t vcntxt)
{
    spin_lock(&vcpu->vm->arch.vir.lock);
    irqid_t int_id = vir_next_pending(vcpu, vcntxt);
    bitmap_clear(vcpu->vm->arch.vir.pend, int_id);
    bitmap_set(vcpu->vm->arch.vir.act, int_id);
    spin_unlock(&vcpu->vm->arch.vir.lock);

    vir_update_hart_line(vcpu, vcntxt);
    return int_id;
}

static void vir_complete(struct vcpu* vcpu, size_t vcntxt, irqid_t int_id)
{
    if (vir_get_hw(vcpu, int_id)) {
        ir_hart[cpu()->arch.ir_cntxt].complete = int_id;
    }

    spin_lock(&vcpu->vm->arch.vir.lock);
    bitmap_clear(vcpu->vm->arch.vir.act, int_id);
    spin_unlock(&vcpu->vm->arch.vir.lock);

    vir_update_hart_line(vcpu, vcntxt);
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
    irqid_t int_id = (irqid_t)((acc->addr & 0xfff) / 4);
    if (acc->write) {
        vir_set_prio(cpu()->vcpu, int_id, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vir_get_prio(cpu()->vcpu, int_id));
    }
}

static void vir_emul_pend_access(struct emul_access* acc)
{
    // pend registers are read only
    if (acc->write) {
        return;
    }

    irqid_t first_int = (irqid_t)(((acc->addr & 0xfff) / 4) * 32);

    uint32_t val = 0;
    for (irqid_t i = 0; i < 32; i++) {
        if (vir_get_pend(cpu()->vcpu, first_int + i)) {
            val |= (1U << i);
        }
    }

    vcpu_writereg(cpu()->vcpu, acc->reg, val);
}

static void vir_emul_enbl_access(struct emul_access* acc)
{
    size_t vcntxt_id = (((acc->addr - 0x2000) & 0x1fffff) / 4) / IR_NUM_ENBL_REGS;

    irqid_t first_int = (irqid_t)(((acc->addr & 0x7f) / 4) * 32);
    unsigned long val = acc->write ? vcpu_readreg(cpu()->vcpu, acc->reg) : 0;
    if (vir_vcntxt_valid(cpu()->vcpu, vcntxt_id)) {
        for (irqid_t i = 0; i < 32; i++) {
            if (acc->write) {
                vir_set_enbl(cpu()->vcpu, vcntxt_id, first_int + i, val & (1U << i));
            } else {
                val |= (vir_get_enbl(cpu()->vcpu, vcntxt_id, first_int + i) ? (1U << i) : 0);
            }
        }
    }

    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, val);
    }
}

static bool vir_global_emul_handler(struct emul_access* acc)
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

    size_t vcntxt = ((acc->addr - IR_THRESHOLD_OFF) >> 12) & 0x3ff;
    if (!vir_vcntxt_valid(cpu()->vcpu, vcntxt)) {
        if (!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
        return true;
    }

    switch (acc->addr & 0xf) {
        case offsetof(struct ir_hart_hw, threshold):
            if (acc->write) {
                vir_set_threshold(cpu()->vcpu, vcntxt,
                    (irqid_t)vcpu_readreg(cpu()->vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu()->vcpu, acc->reg, vir_get_threshold(cpu()->vcpu, vcntxt));
            }
            break;
        case offsetof(struct ir_hart_hw, claim):
            if (acc->write) {
                vir_complete(cpu()->vcpu, vcntxt, (irqid_t)vcpu_readreg(cpu()->vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu()->vcpu, acc->reg, vir_claim(cpu()->vcpu, vcntxt));
            }
            break;
        default:
            if (!acc->write) {
                vcpu_writereg(cpu()->vcpu, acc->reg, 0);
            }
            break;
    }

    return true;
}

void vir_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    if (cpu()->id == vm->master) {
        vm->arch.vir.ir_global_emul = (struct emul_mem){ .va_base = vm_irqc_dscrp->ir.base,
            .size = sizeof(struct ir_global_hw),
            .handler = vir_global_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vir.ir_global_emul);

        vm->arch.vir.ir_threshold_emul =
            (struct emul_mem){ .va_base = vm_irqc_dscrp->ir.base + IR_THRESHOLD_OFF,
                .size = sizeof(struct ir_hart_hw) * vm->cpu_num * PLAT_IR_CNTXT_PER_HART,
                .handler = vir_hart_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vir.ir_threshold_emul);

        /* assumes 2 contexts per hart */
        vm->arch.vir.cntxt_num = vm->cpu_num * 2;
    }
}
