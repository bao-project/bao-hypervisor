/**
 * SPDX-License-Identifier: GPL-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vplic.h>
#include <cpu.h>
#include <emul.h>
#include <mem.h>
#include <vm.h>
#include <interrupts.h>
#include <arch/csrs.h>

static int vplic_vcntxt_to_pcntxt(struct vcpu *vcpu, int vcntxt_id)
{
    struct plic_cntxt vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    struct plic_cntxt pcntxt;

    int pcntxt_id = -1;
    pcntxt.mode = vcntxt.mode;
    pcntxt.hart_id = vm_translate_to_pcpuid(vcpu->vm, vcntxt.hart_id);
    if (pcntxt.hart_id != INVALID_CPUID) {
        pcntxt_id = plic_plat_cntxt_to_id(pcntxt);
    }

    return pcntxt_id;
}

static bool vplic_vcntxt_valid(struct vcpu *vcpu, int vcntxt_id) {
    struct plic_cntxt vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    return vcntxt_id < vcpu->vm->arch.vxplic.cntxt_num && vcntxt.mode <= PRIV_S;
}

static bool vplic_get_pend(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (id <= PLIC_MAX_INTERRUPTS) ret = bitmap_get(vxplic->pend, id);
    return ret;
}

static bool vplic_get_act(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (id <= PLIC_MAX_INTERRUPTS) ret = bitmap_get(vxplic->act, id);
    return ret;
}

static bool vplic_get_enbl(struct vcpu* vcpu, int vcntxt, irqid_t id)
{
    bool ret = false;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (id <= PLIC_MAX_INTERRUPTS) ret = !!bitmap_get(vxplic->enbl[vcntxt], id);
    return ret;
}


static uint32_t vplic_get_prio(struct vcpu *vcpu, irqid_t id)
{
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (id <= PLIC_MAX_INTERRUPTS) ret = vxplic->prio[id];
    return ret;
}


void vplic_set_hw(struct vm *vm, irqid_t id)
{
    if (id <= PLIC_MAX_INTERRUPTS) {
        bitmap_set(vm->arch.vxplic.hw,id);
    }
}

static bool vplic_get_hw(struct vcpu* vcpu, irqid_t id)
{
    bool ret = false;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (id <= PLIC_MAX_INTERRUPTS) ret = bitmap_get(vxplic->hw, id);
    return ret;
}

static uint32_t vplic_get_theshold(struct vcpu* vcpu, int vcntxt) 
{
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    return vxplic->threshold[vcntxt];
}

static irqid_t vplic_next_pending(struct vcpu *vcpu, int vcntxt)
{
    uint32_t max_prio = 0;
    irqid_t int_id = 0;

    for (size_t i = 0; i <= PLIC_MAX_INTERRUPTS; i++) {
        if (vplic_get_pend(vcpu, i) && !vplic_get_act(vcpu, i) && 
            vplic_get_enbl(vcpu, vcntxt, i)) {

            uint32_t prio = vplic_get_prio(vcpu,i);
            if (prio > max_prio) {
                max_prio = prio;
                int_id = i;
            }
        }
    }

    if (max_prio > vplic_get_theshold(vcpu, vcntxt))
        return int_id;
    else
        return 0;
}

enum {UPDATE_HART_LINE};
static void vplic_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vplic_ipi_handler, VPLIC_IPI_ID);

void vplic_update_hart_line(struct vcpu* vcpu, int vcntxt) 
{
    int pcntxt_id = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
    struct plic_cntxt pcntxt = plic_plat_id_to_cntxt(pcntxt_id);
    if(pcntxt.hart_id == cpu()->id) {
        int id = vplic_next_pending(vcpu, vcntxt);
        if(id != 0){
            CSRS(CSR_HVIP, HIP_VSEIP);
        } else  {
            CSRC(CSR_HVIP, HIP_VSEIP);
        }
    } else {
        struct cpu_msg msg = {VPLIC_IPI_ID, UPDATE_HART_LINE, vcntxt};
        cpu_send_msg(pcntxt.hart_id, &msg);       
    }
}

static void vplic_ipi_handler(uint32_t event, uint64_t data) 
{
    switch(event) {
        case UPDATE_HART_LINE:
            vplic_update_hart_line(cpu()->vcpu, data);
            break;
    }
}

static void vplic_set_threshold(struct vcpu* vcpu, int vcntxt, uint32_t threshold) 
{
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    vxplic->threshold[vcntxt] = threshold;
    int pcntxt = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
    plic_set_threshold(pcntxt, threshold);
    spin_unlock(&vxplic->lock);

    vplic_update_hart_line(vcpu, vcntxt);
}

static void vplic_set_enbl(struct vcpu* vcpu, int vcntxt, irqid_t id, bool set)
{
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (id <= PLIC_MAX_INTERRUPTS && vplic_get_enbl(vcpu, vcntxt, id) != set) {
        if(set){
            bitmap_set(vxplic->enbl[vcntxt],id);
        } else {
            bitmap_clear(vxplic->enbl[vcntxt],id);
        }

        if(vplic_get_hw(vcpu, id)){
            int pcntxt_id = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
            plic_set_enbl(pcntxt_id, id, set);
        } else {
            vplic_update_hart_line(vcpu, vcntxt);
        }
    }
    spin_unlock(&vxplic->lock);
}

static void vplic_set_prio(struct vcpu *vcpu, irqid_t id, uint32_t prio)
{
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (id <= PLIC_MAX_INTERRUPTS && vplic_get_prio(vcpu, id) != prio) {
        vxplic->prio[id] = prio;
        if(vplic_get_hw(vcpu,id)){
            plic_set_prio(id, prio);
        } else {
            for(size_t i = 0; i < vxplic->cntxt_num; i++) {
                if(plic_plat_id_to_cntxt(i).mode != PRIV_S) continue;
                if(vplic_get_enbl(vcpu, i, id)) {
                    vplic_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vxplic->lock);
}

static irqid_t vplic_claim(struct vcpu *vcpu, int vcntxt)
{
    spin_lock(&vcpu->vm->arch.vxplic.lock);
    irqid_t int_id = vplic_next_pending(vcpu, vcntxt);
     bitmap_clear(vcpu->vm->arch.vxplic.pend, int_id);
    bitmap_set(vcpu->vm->arch.vxplic.act, int_id);
    spin_unlock(&vcpu->vm->arch.vxplic.lock);

    vplic_update_hart_line(vcpu, vcntxt);
    return int_id;
}

static void vplic_complete(struct vcpu *vcpu, int vcntxt, irqid_t int_id)
{
    if(vplic_get_hw(vcpu ,int_id)){
        plic_hart[cpu()->arch.plic_cntxt].complete = int_id;
    }

    spin_lock(&vcpu->vm->arch.vxplic.lock);
    bitmap_clear(vcpu->vm->arch.vxplic.act, int_id);
    spin_unlock(&vcpu->vm->arch.vxplic.lock);

    vplic_update_hart_line(vcpu, vcntxt);
}

void vplic_inject(struct vcpu *vcpu, irqid_t id)
{
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (id > 0 && id <= PLIC_MAX_INTERRUPTS && !vplic_get_pend(vcpu, id)) {
        
        bitmap_set(vxplic->pend, id);

        if(vplic_get_hw(vcpu, id)) {
            struct plic_cntxt vcntxt = {vcpu->id, PRIV_S};
            int vcntxt_id = plic_plat_cntxt_to_id(vcntxt);
            vplic_update_hart_line(vcpu, vcntxt_id);
        } else {
            for(size_t i = 0; i < vxplic->cntxt_num; i++) {
                if(plic_plat_id_to_cntxt(i).mode != PRIV_S) continue;
                if(vplic_get_enbl(vcpu, i, id) && 
                vplic_get_prio(vcpu, id) > vplic_get_theshold(vcpu, i)) {
                    vplic_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vxplic->lock);

}

static void vplic_emul_prio_access(struct emul_access *acc)
{
    irqid_t int_id = (acc->addr & 0xfff) / 4;
    if (acc->write) {
        vplic_set_prio(cpu()->vcpu,int_id, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vplic_get_prio(cpu()->vcpu,int_id));
    }
}

static void vplic_emul_pend_access(struct emul_access *acc)
{
    // pend registers are read only
    if (acc->write) return;

    irqid_t first_int = ((acc->addr & 0xfff) / 4) * 32;

    uint32_t val = 0;
    for (size_t i = 0; i < 32; i++) {
        if (vplic_get_pend(cpu()->vcpu, first_int + i)) {
            val |= (1ULL << i);
        }
    }

    vcpu_writereg(cpu()->vcpu, acc->reg, val);
}

static void vplic_emul_enbl_access(struct emul_access *acc)
{
    int vcntxt_id =
        (((acc->addr - 0x2000) & 0x1fffff) / 4) / PLIC_NUM_ENBL_REGS;

    irqid_t first_int = ((acc->addr & 0x7f) / 4) * 32;
    unsigned long val = acc->write ? vcpu_readreg(cpu()->vcpu, acc->reg) : 0;
    if(vplic_vcntxt_valid(cpu()->vcpu, vcntxt_id)) {
        for (size_t i = 0; i < 32; i++) {
            if (acc->write) {
                vplic_set_enbl(cpu()->vcpu, vcntxt_id, first_int + i, val & (1U << i));
            } else {
                val |= (vplic_get_enbl(cpu()->vcpu, vcntxt_id, first_int + i) ? (1U << i)
                                                                : 0);
            }
        }
    }

    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, val);
    }
}

static bool vplic_global_emul_handler(struct emul_access *acc)
{
    // only allow aligned word accesses
    if (acc->width != 4 || acc->addr & 0x3) return false;

    switch ((acc->addr >> 12) & 0x3) {
        case 0:
            vplic_emul_prio_access(acc);
            break;
        case 1:
            vplic_emul_pend_access(acc);
            break;
        default:
            vplic_emul_enbl_access(acc);
            break;
    }

    return true;
}

static bool vplic_hart_emul_handler(struct emul_access *acc)
{
    // only allow aligned word accesses
    if (acc->width > 4 || acc->addr & 0x3) return false;

    int vcntxt = ((acc->addr - PLIC_CLAIMCMPLT_OFF) >> 12) & 0x3ff;
    if(!vplic_vcntxt_valid(cpu()->vcpu, vcntxt)) {
        if(!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
        return true;
    }

    switch (acc->addr & 0xf) {
        case offsetof(struct plic_hart_hw, threshold):
            if (acc->write) {
                vplic_set_threshold(cpu()->vcpu, vcntxt, vcpu_readreg(cpu()->vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu()->vcpu, acc->reg, vplic_get_theshold(cpu()->vcpu, vcntxt));
            }
            break;
        case offsetof(struct plic_hart_hw, claim):
            if (acc->write) {
                vplic_complete(cpu()->vcpu, vcntxt, vcpu_readreg(cpu()->vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu()->vcpu, acc->reg, vplic_claim(cpu()->vcpu, vcntxt));
            }
            break;
    }

    return true;
}

void vplic_init(struct vm *vm, vaddr_t vplic_base)
{
    if (cpu()->id == vm->master) {
        vm->arch.vxplic.plic_global_emul = (struct emul_mem) {
            .va_base = vplic_base,
            .size = sizeof(struct plic_global_hw),
            .handler = vplic_global_emul_handler
        };

        vm_emul_add_mem(vm, &vm->arch.vxplic.plic_global_emul);

        vm->arch.vxplic.plic_claimcomplte_emul = (struct emul_mem) {
            .va_base = vplic_base + PLIC_CLAIMCMPLT_OFF,
            .size = sizeof(struct plic_hart_hw) * vm->cpu_num * PLAT_PLIC_CNTXT_PER_HART,
            .handler = vplic_hart_emul_handler
        };

        vm_emul_add_mem(vm, &vm->arch.vxplic.plic_claimcomplte_emul);

        /* assumes 2 contexts per hart */
        vm->arch.vxplic.cntxt_num = vm->cpu_num * 2; 
    }
}
