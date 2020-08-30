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

static int vplic_vcntxt_to_pcntxt(vm_t *vm, int vcntxt_id)
{
    plic_cntxt_t vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    plic_cntxt_t pcntxt;

    int pcntxt_id = -1;
    pcntxt.mode = vcntxt.mode;
    pcntxt.hart_id = vm_translate_to_pcpuid(cpu.vcpu->vm, vcntxt.hart_id);
    if (pcntxt.hart_id >= 0) {
        pcntxt_id = plic_plat_cntxt_to_id(pcntxt);
    }

    return pcntxt_id;
}

static void vplic_set_pend(vplic_t *vplic, int id, bool set)
{
    spin_lock(&vplic->lock);
    if (id <= PLIC_IMPL_INTERRUPTS) {
        if (set)
            bitmap_set(vplic->pend, id);
        else
            bitmap_clear(vplic->pend, id);
    }
    spin_unlock(&vplic->lock);
}

static bool vplic_get_pend(vplic_t *vplic, int id)
{
    bool ret = false;
    spin_lock(&vplic->lock);
    if (id <= PLIC_IMPL_INTERRUPTS) ret = bitmap_get(vplic->pend, id);
    spin_unlock(&vplic->lock);
    return ret;
}

static int vplic_next_pending(vplic_t *vplic)
{
    uint32_t max_prio = 0;
    uint32_t int_id = 0;
    for (int i = 0; i <= PLIC_IMPL_INTERRUPTS; i++) {
        if (vplic_get_pend(vplic, i)) {
            uint32_t prio = plic_get_prio(i);
            if (prio > max_prio) {
                max_prio = prio;
                int_id = i;
            }
        }
    }

    if (max_prio > plic_hart[cpu.arch.plic_cntxt].threshold)
        return int_id;
    else
        return 0;
}

static int vplic_claim(vplic_t *vplic)
{
    int int_id = vplic_next_pending(vplic);
    vplic_set_pend(vplic, int_id, false);
    return int_id;
}

static void vplic_complete(vplic_t *vplic, int int_id)
{
    plic_hart[cpu.arch.plic_cntxt].complete = int_id;
    if (vplic_next_pending(vplic) == 0) {
        CSRC(CSR_HVIP, HIP_VSEIP);
    }
}

void vplic_inject(vplic_t *vplic, int id)
{
    if (id > 0 && id < PLIC_MAX_INTERRUPTS) {
        vplic_set_pend(vplic, id, true);
        CSRS(CSR_HVIP, HIP_VSEIP);
    }
}

static void vplic_emul_prio_access(emul_access_t *acc)
{
    int int_id = (acc->addr & 0xfff) / 4;

    if (vm_has_interrupt(cpu.vcpu->vm, int_id)) {
        if (acc->write) {
            plic_set_prio(int_id, vcpu_readreg(cpu.vcpu, acc->reg));
        } else {
            vcpu_writereg(cpu.vcpu, acc->reg, plic_get_prio(int_id));
        }
    }
}

static void vplic_emul_pend_access(emul_access_t *acc)
{
    // pend registers are read only
    if (acc->write) return;

    int first_int = ((acc->addr & 0xfff) / 4) * 32;

    uint32_t val = 0;
    for (int i = 0; i < 32; i++) {
        if (vm_has_interrupt(cpu.vcpu->vm, first_int + i) &&
            vplic_get_pend(&cpu.vcpu->vm->arch.vplic, first_int + i)) {
            val |= (1ULL << i);
        }
    }

    vcpu_writereg(cpu.vcpu, acc->reg, val);
}

static void vplic_emul_enbl_access(emul_access_t *acc)
{
    int vcntxt_id =
        (((acc->addr - 0x2000) & 0x1fffff) / 4) / PLIC_NUM_ENBL_REGS;
    plic_cntxt_t vcntxt = plic_plat_id_to_cntxt(vcntxt_id);
    plic_cntxt_t pcntxt;

    int pcntxt_id = -1;
    pcntxt.mode = vcntxt.mode;
    pcntxt.hart_id = vm_translate_to_pcpuid(cpu.vcpu->vm, vcntxt.hart_id);
    if (pcntxt.hart_id >= 0) {
        pcntxt_id = plic_plat_cntxt_to_id(pcntxt);
    }

    if (pcntxt_id >= 0) {
        int first_int = ((acc->addr & 0x7f) / 4) * 32;
        unsigned long val = acc->write ? vcpu_readreg(cpu.vcpu, acc->reg) : 0;
        for (int i = 0; i < 32; i++) {
            if (vm_has_interrupt(cpu.vcpu->vm, first_int + i)) {
                if (acc->write) {
                    plic_set_enbl(pcntxt_id, first_int + i, val & (1U << i));
                } else {
                    val |= (plic_get_enbl(pcntxt_id, first_int + i) ? (1U << i)
                                                                    : 0);
                }
            }
        }

        if (!acc->write) {
            vcpu_writereg(cpu.vcpu, acc->reg, val);
        }
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
    int pcntxt = vplic_vcntxt_to_pcntxt(cpu.vcpu->vm, vcntxt);

    if (pcntxt < 0) return false;

    plic_cntxt_t cntxt = plic_plat_id_to_cntxt(pcntxt);
    if (cntxt.mode < PRIV_S) return false;

    switch (acc->addr & 0xf) {
        case offsetof(plic_hart_t, threshold):
            if (acc->write) {
                plic_hart[pcntxt].threshold = vcpu_readreg(cpu.vcpu, acc->reg);
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg, plic_hart[pcntxt].threshold);
            }
            break;
        case offsetof(plic_hart_t, claim):
            if (acc->write) {
                vplic_complete(&cpu.vcpu->vm->arch.vplic,
                               vcpu_readreg(cpu.vcpu, acc->reg));
            } else {
                vcpu_writereg(cpu.vcpu, acc->reg,
                              vplic_claim(&cpu.vcpu->vm->arch.vplic));
            }
            break;
    }

    return true;
}

void vplic_init(vm_t *vm, uintptr_t vplic_base)
{
    if (cpu.id == vm->master) {
        emul_region_t plic_global_emu = {.va_base = vplic_base,
                                         .pa_base = (uint64_t)&plic_global,
                                         .size = sizeof(plic_global),
                                         .handler = vplic_global_emul_handler};

        vm_add_emul(vm, &plic_global_emu);

        emul_region_t plic_claimcomplte_emu = {
            .va_base = vplic_base + PLIC_CLAIMCMPLT_OFF,
            .pa_base = (uint64_t)plic_hart,
            .size = sizeof(plic_hart),
            .handler = vplic_hart_emul_handler};

        vm_add_emul(vm, &plic_claimcomplte_emu);
    }
}
