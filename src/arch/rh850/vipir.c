/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vipir.h>
#include <emul.h>
#include <vm.h>
#include <cpu.h>
#include <ipir.h>
#include <spinlock.h>
#include <types.h>

#define IPIR_GET_CHANN(o)       (((o) & 0xE0) >> 5)
#define IPIR_IS_SELF(o)         ((((o) & 0xF00) >> 11) == 0)
#define IPIR_GET_NON_SELF_PE(o) ((((o) & 0xF00) >> 8) - 8)

#define IPIR_REG_OFFSET_MASK    (0x1f)

extern volatile struct ipir_hw* ipir;

static spinlock_t ipir_lock[PLAT_CPU_NUM][IPIR_NUM_CHANNELS] = { SPINLOCK_INITVAL };

static bool vipir_emul_handler(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    if (acc->width != 1) {
        /* only 8bit aligment allowed */
        return false;
    }

    volatile uint8_t* tgt_reg = NULL;
    size_t acc_offset = acc->addr - (unsigned long)ipir;
    size_t chan_idx = IPIR_GET_CHANN(acc_offset);
    size_t pe_idx = 0;

    bool self = IPIR_IS_SELF(acc_offset);
    if (self) {
        pe_idx = vcpu->phys_id;
    } else {
        cpuid_t virt_peid = IPIR_GET_NON_SELF_PE(acc_offset);
        if (virt_peid == INVALID_CPUID) {
            ERROR("Access to unassigned PE IPIR\n");
        }
        pe_idx = vm_translate_to_pcpuid(vm, virt_peid);
    }

    spin_lock(&ipir_lock[pe_idx][chan_idx]);

    switch (acc_offset & IPIR_REG_OFFSET_MASK) {
        case offsetof(struct ipir_chann, IPInEN):
            tgt_reg = &(ipir->pe[pe_idx].chann[chan_idx].IPInEN);
            break;
        case offsetof(struct ipir_chann, IPInFLG):
            tgt_reg = &(ipir->pe[pe_idx].chann[chan_idx].IPInFLG);
            break;
        case offsetof(struct ipir_chann, IPInFCLR):
            tgt_reg = &(ipir->pe[pe_idx].chann[chan_idx].IPInFCLR);
            break;
        case offsetof(struct ipir_chann, IPInREQ):
            tgt_reg = &(ipir->pe[pe_idx].chann[chan_idx].IPInREQ);
            break;
        case offsetof(struct ipir_chann, IPInRCLR):
            tgt_reg = &(ipir->pe[pe_idx].chann[chan_idx].IPInRCLR);
            break;
        default:
            tgt_reg = NULL;
    }

    if ((chan_idx != IPI_HYP_IRQ_ID) && (tgt_reg != NULL)) {
        if (acc->write) {
            unsigned long val;
            if (emul_arch_is_bwop(&acc->arch)) {
                val = (uint8_t)emul_arch_bwop_emul_acc(&acc->arch, *tgt_reg);
            } else {
                val = (uint8_t)vcpu_readreg(vcpu, acc->reg);
            }
            val = (uint8_t)vm_translate_to_pcpu_mask(vm, val, vm->cpu_num);
            *tgt_reg = (uint8_t)((*tgt_reg & ~vm->cpus) | (val & vm->cpus));
        } else {
            uint8_t val = *tgt_reg;
            if (emul_arch_is_bwop(&acc->arch)) {
                /* translate vcpu_id bit to pcpu_id bit */
                acc->arch.bit =
                    (uint8_t)vm_translate_to_pcpu_mask(vm, val & acc->arch.bit, vm->cpu_num);
                /* invoke emul to update gmpsw.z */
                (void)emul_arch_bwop_emul_acc(&acc->arch, val);
            } else {
                val = (uint8_t)vm_translate_to_pcpu_mask(vm, val, vm->cpu_num);
                vcpu_writereg(vcpu, acc->reg, val);
            }
        }
    }

    spin_unlock(&ipir_lock[pe_idx][chan_idx]);

    return true;
}

void vipir_init(struct vm* vm)
{
    if (cpu()->id == vm->master) {
        vm->arch.ipir_emul = (struct emul_mem){
            .va_base = platform.arch.ipir_addr,
            .size = ALIGN(sizeof(struct ipir_hw), PAGE_SIZE),
            .handler = vipir_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.ipir_emul);

        /* Reserve IPIR channels not used by the hypervisor */
        for (irqid_t i = IPIR_CH0_IRQ_ID; i < (IPIR_CH0_IRQ_ID + IPIR_NUM_CHANNELS); i++) {
            if (i != IPI_HYP_IRQ_ID) {
                if (!interrupts_vm_assign(vm, i)) {
                    ERROR("Failed to reserve VM IPIR channel interrupt");
                }
            }
        }
    }
}
