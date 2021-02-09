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

#include <arch/vplic.h>
#include <cpu.h>
#include <emul.h>
#include <mem.h>
#include <vm.h>
#include <interrupts.h>
#include <arch/csrs.h>

static int vplic_vcntxt_to_pcntxt(vcpu_t *vcpu, int vcntxt_id)
{
    plic_cntxt_t vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    plic_cntxt_t pcntxt;

    int pcntxt_id = -1;
    pcntxt.mode = vcntxt.mode;
    pcntxt.hart_id = vm_translate_to_pcpuid(vcpu->vm, vcntxt.hart_id);
    if (pcntxt.hart_id >= 0) {
        pcntxt_id = plic_plat_cntxt_to_id(pcntxt);
    }

    return pcntxt_id;
}

static bool vplic_vcntxt_valid(vcpu_t *vcpu, int vcntxt_id) {
    plic_cntxt_t vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    return vcntxt_id < vcpu->vm->arch.vplic.cntxt_num && vcntxt.mode <= PRIV_S ;
}

static bool vplic_get_pend(vcpu_t* vcpu, int id)
{
    bool ret = false;
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    if (id <= PLIC_IMPL_INTERRUPTS) ret = bitmap_get(vplic->pend, id);
    return ret;
}

static bool vplic_get_act(vcpu_t* vcpu, int id)
{
    bool ret = false;
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    if (id <= PLIC_IMPL_INTERRUPTS) ret = bitmap_get(vplic->act, id);
    return ret;
}

static bool vplic_get_enbl(vcpu_t* vcpu, int vcntxt, int id)
{
    bool ret = false;
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    if (id <= PLIC_IMPL_INTERRUPTS) ret = !!bitmap_get(vplic->enbl[vcntxt], id);
    return ret;
}


static uint32_t vplic_get_prio(vcpu_t *vcpu, int id)
{
    uint32_t ret = 0;
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    if (id <= PLIC_IMPL_INTERRUPTS) ret = vplic->prio[id];
    return ret;
}


void vplic_set_hw(vm_t *vm, int id)
{
    if (id <= PLIC_IMPL_INTERRUPTS) {
        bitmap_set(vm->arch.vplic.hw,id);
    }
}

static bool vplic_get_hw(vcpu_t* vcpu, int id)
{
    bool ret = false;
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    if (id <= PLIC_IMPL_INTERRUPTS) ret = bitmap_get(vplic->hw, id);
    return ret;
}

static uint32_t vplic_get_theshold(vcpu_t* vcpu, int vcntxt) 
{
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    return vplic->threshold[vcntxt];
}

static int vplic_next_pending(vcpu_t *vcpu, int vcntxt)
{
    uint32_t max_prio = 0;
    uint32_t int_id = 0;

    for (int i = 0; i <= PLIC_IMPL_INTERRUPTS; i++) {
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

void vplic_update_hart_line(vcpu_t* vcpu, int vcntxt) 
{
    int pcntxt_id = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
    plic_cntxt_t pcntxt = plic_plat_id_to_cntxt(pcntxt_id);
    if(pcntxt.hart_id == cpu.id) {
        int id = vplic_next_pending(vcpu, vcntxt);
        if(id != 0){
            CSRS(CSR_HVIP, HIP_VSEIP);
        } else  {
            CSRC(CSR_HVIP, HIP_VSEIP);
        }
    } else {
        cpu_msg_t msg = {VPLIC_IPI_ID, UPDATE_HART_LINE, vcntxt};
        cpu_send_msg(pcntxt.hart_id, &msg);       
    }
}

static void vplic_ipi_handler(uint32_t event, uint64_t data) 
{
    switch(event) {
        case UPDATE_HART_LINE:
            vplic_update_hart_line(cpu.vcpu, data);
            break;
    }
}

static void vplic_set_threshold(vcpu_t* vcpu, int vcntxt, uint32_t threshold) 
{
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    spin_lock(&vplic->lock);
    vplic->threshold[vcntxt] = threshold;
    int pcntxt = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
    plic_set_threshold(pcntxt, threshold);
    spin_unlock(&vplic->lock);

    vplic_update_hart_line(vcpu, vcntxt);
}

static void vplic_set_enbl(vcpu_t* vcpu, int vcntxt, int id, bool set)
{
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    spin_lock(&vplic->lock);
    if (id <= PLIC_IMPL_INTERRUPTS && vplic_get_enbl(vcpu, vcntxt, id) != set) {
        if(set){
            bitmap_set(vplic->enbl[vcntxt],id);
        } else {
            bitmap_clear(vplic->enbl[vcntxt],id);
        }

        if(vplic_get_hw(vcpu, id)){
            int pcntxt_id = vplic_vcntxt_to_pcntxt(vcpu, vcntxt);
            plic_set_enbl(pcntxt_id, id, set);
        } else {
            vplic_update_hart_line(vcpu, vcntxt);
        }
    }
    spin_unlock(&vplic->lock);
}

static void vplic_set_prio(vcpu_t *vcpu, int id, uint32_t prio)
{
    vplic_t *vplic = &vcpu->vm->arch.vplic;
    spin_lock(&vplic->lock);
    if (id <= PLIC_IMPL_INTERRUPTS && vplic_get_prio(vcpu, id) != prio) {
        vplic->prio[id] = prio;
        if(vplic_get_hw(vcpu,id)){
            plic_set_prio(id, prio);
        } else {
            for(int i = 0; i < vplic->cntxt_num; i++) {
                if(plic_plat_id_to_cntxt(i).mode != PRIV_S) continue;
                if(vplic_get_enbl(vcpu, i, id)) {
                    vplic_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vplic->lock);
}

static int vplic_claim(vcpu_t *vcpu, int vcntxt)
{
    spin_lock(&vcpu->vm->arch.vplic.lock);
    int int_id = vplic_next_pending(vcpu, vcntxt);
    bitmap_clear(vcpu->vm->arch.vplic.pend, int_id);
    bitmap_set(vcpu->vm->arch.vplic.act, int_id);
    spin_unlock(&vcpu->vm->arch.vplic.lock);

    vplic_update_hart_line(vcpu, vcntxt);
    return int_id;
}

static void vplic_complete(vcpu_t *vcpu, int vcntxt, int int_id)
{
    if(vplic_get_hw(vcpu ,int_id)){
        plic_hart[cpu.arch.plic_cntxt].complete = int_id;
    }

    spin_lock(&vcpu->vm->arch.vplic.lock);
    bitmap_clear(vcpu->vm->arch.vplic.act, int_id);
    spin_unlock(&vcpu->vm->arch.vplic.lock);

    vplic_update_hart_line(vcpu, vcntxt);
}

void vplic_inject(vcpu_t *vcpu, int id)
{
    vplic_t * vplic = &vcpu->vm->arch.vplic;
    spin_lock(&vplic->lock);
    if (id > 0 && id <= PLIC_IMPL_INTERRUPTS && !vplic_get_pend(vcpu, id)) {
        
        bitmap_set(vplic->pend, id);

        if(vplic_get_hw(vcpu, id)) {
            plic_cntxt_t vcntxt = {vcpu->id, PRIV_S};
            int vcntxt_id = plic_plat_cntxt_to_id(vcntxt);
            vplic_update_hart_line(vcpu, vcntxt_id);
        } else {
            for(int i = 0; i < vplic->cntxt_num; i++) {
                if(plic_plat_id_to_cntxt(i).mode != PRIV_S) continue;
                if(vplic_get_enbl(vcpu, i, id) && 
                vplic_get_prio(vcpu, id) > vplic_get_theshold(vcpu, i)) {
                    vplic_update_hart_line(vcpu, i);
                }
            }
        }
    }
    spin_unlock(&vplic->lock);
}

static void vplic_emul_prio_access(emul_access_t *acc)
{
    int int_id = (acc->addr & 0xfff) / 4;
    if (acc->write) {
        vplic_set_prio(cpu.vcpu,int_id, vcpu_readreg(cpu.vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu.vcpu, acc->reg, vplic_get_prio(cpu.vcpu,int_id));
    }
}

static void vplic_emul_pend_access(emul_access_t *acc)
{
    // pend registers are read only
    if (acc->write) return;

    int first_int = ((acc->addr & 0xfff) / 4) * 32;

    uint32_t val = 0;
    for (int i = 0; i < 32; i++) {
        if (vplic_get_pend(cpu.vcpu, first_int + i)) {
            val |= (1ULL << i);
        }
    }

    vcpu_writereg(cpu.vcpu, acc->reg, val);
}

static void vplic_emul_enbl_access(emul_access_t *acc)
{
    int vcntxt_id =
        (((acc->addr - 0x2000) & 0x1fffff) / 4) / PLIC_NUM_ENBL_REGS;

    int first_int = ((acc->addr & 0x7f) / 4) * 32;
    unsigned long val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
    if(vplic_vcntxt_valid(cpu.vcpu, vcntxt_id)) {
        for (int i = 0; i < 32; i++) {
            if (acc->write) {
                vplic_set_enbl(cpu.vcpu, vcntxt_id, first_int + i, val & (1U << i));
            } else {
                val |= (vplic_get_enbl(cpu.vcpu, vcntxt_id, first_int + i) ? (1U << i)
                                                                : 0);
            }
        }
    }

    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, val);
    }
}

static bool vplic_global_emul_handler(emul_access_t *acc)
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

static bool vplic_hart_emul_handler(emul_access_t *acc)
{
    // only allow aligned word accesses
    if (acc->width > 4 || acc->addr & 0x3) return false;

    int vcntxt = ((acc->addr - PLIC_CLAIMCMPLT_OFF) >> 12) & 0x3ff;
    if(!vplic_vcntxt_valid(cpu.vcpu, vcntxt)) {
        if(!acc->write) {
            vcpu_writereg(cpu.vcpu, acc->reg, 0);
        }
        return true;
    }

    switch (acc->addr & 0xf) {
        case offsetof(plic_hart_t, threshold):
            if (acc->write) {
                vplic_set_threshold(cpu.vcpu, vcntxt, vcpu_readreg(cpu.vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg, vplic_get_theshold(cpu.vcpu, vcntxt));
            }
            break;
        case offsetof(plic_hart_t, claim):
            if (acc->write) {
                vplic_complete(cpu.vcpu, vcntxt, vcpu_readreg(cpu.vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg, vplic_claim(cpu.vcpu, vcntxt));
            }
            break;
    }

    return true;
}

void vplic_init(vm_t *vm, uintptr_t vplic_base)
{
    if (cpu.id == vm->master) {
        emul_mem_t plic_global_emu = {.va_base = vplic_base,
                                         .pa_base = (uint64_t)&plic_global,
                                         .size = sizeof(plic_global),
                                         .handler = vplic_global_emul_handler};

        vm_emul_add_mem(vm, &plic_global_emu);

        emul_mem_t plic_claimcomplte_emu = {
            .va_base = vplic_base + PLIC_CLAIMCMPLT_OFF,
            .pa_base = (uint64_t)plic_hart,
            .size = sizeof(plic_hart),
            .handler = vplic_hart_emul_handler};

        vm_emul_add_mem(vm, &plic_claimcomplte_emu);

        /* assumes 2 contexts per hart */
        vm->arch.vplic.cntxt_num = vm->cpu_num * 2; 
    }
}
