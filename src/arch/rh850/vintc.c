/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <interrupts.h>
#include <platform.h>
#include <vm.h>
#include <arch/fences.h>
#include <intc.h>
#include <ipir.h>
#include <srs.h>

extern volatile struct intc1* intc1_hw;
extern volatile struct intc2* intc2_hw;
extern volatile struct intif* intif_hw;
extern volatile struct eint* eint_hw;
extern volatile struct fenc* fenc_hw;
extern volatile struct feinc* feinc_hw[PLAT_CPU_NUM];

#define INTC2_EIC_OFFSET    0x0000
#define INTC2_IMR_OFFSET    0x1000
#define INTC2_EIBD_OFFSET   0x2000
#define INTC2_EEIC_OFFSET   0x4000
#define INTC2_OFFSET_MASK   0x7000

#define INTC_EIBD_PEID_MASK (0x7UL)
#define INTC_EIBD_HYP_MASK  (~INTC_EIBD_PEID_MASK)

void vintc_inject(struct vcpu* vcpu, irqid_t int_id)
{
    if (!vm_has_interrupt(vcpu->vm, int_id)) {
        ERROR("Trying to inject unassigned interrupt in VM");
    }
    intc_set_pend(int_id, true);
}

static void emulate_intc_eic_access(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    if (acc->width > 2) {
        /* ignore access */
        return;
    }

    size_t acc_intc2_offset = acc->addr - (unsigned long)intc2_hw;
    unsigned long bot = offsetof(struct intc2, EIC);
    size_t reg_idx = (ALIGN(acc_intc2_offset - bot, 2)) / 2;

    unsigned long mask = BIT_MASK(0, acc->width * 8);
    size_t addr_off = acc->addr & 0x1UL;
    volatile uint16_t* tgt_reg = &(intc2_hw->EIC[reg_idx]);
    irqid_t int_id = reg_idx + 32;

    if (vm_has_interrupt(vm, int_id)) {
        if (emul_arch_is_bwop(&acc->arch)) {
            volatile uint8_t* byte_addr = ((volatile uint8_t*)tgt_reg) + addr_off;
            *byte_addr = emul_arch_bwop_emul_acc(&acc->arch, *byte_addr);
        } else if (acc->write) {
            unsigned long val = vcpu_readreg(vcpu, acc->reg);
            *tgt_reg = (uint16_t)(((val & mask) << (addr_off * 8)) |
                (*tgt_reg & ~(mask << (addr_off * 8))));
        } else {
            unsigned long val = *tgt_reg;

            val = (val >> (addr_off * 8)) & mask;
            if (acc->sign_ext && (1UL << (acc->width * 8 - 1) & val)) {
                val |= ~mask;
            }

            vcpu_writereg(vcpu, acc->reg, val);
        }
    } else if (!acc->write) {
        vcpu_writereg(vcpu, acc->reg, 0);
    }
}

static void emulate_intc_imr_access(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t acc_intc2_offset = acc->addr - (unsigned long)intc2_hw;
    unsigned long bot = offsetof(struct intc2, IMR);
    size_t reg_idx = (ALIGN(acc_intc2_offset - bot, 4)) / 4;

    unsigned long mask = BIT_MASK(0, acc->width * 8);
    size_t addr_off = acc->addr & 0x3UL;
    irqid_t first_imr_int = 0;
    volatile uint32_t* tgt_reg = &(intc2_hw->IMR[reg_idx]);

    first_imr_int = reg_idx * 32;
    first_imr_int += 32;

    if (emul_arch_is_bwop(&acc->arch)) {
        volatile uint8_t* byte_addr = ((volatile uint8_t*)tgt_reg) + addr_off;
        *byte_addr = emul_arch_bwop_emul_acc(&acc->arch, *byte_addr);
    } else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        unsigned long write_val = *tgt_reg;

        for (unsigned int i = 0; i < 32; i++) {
            if (!vm_has_interrupt(vm, i + first_imr_int)) {
                continue;
            }
            if ((1UL << i) & val) {
                write_val |= (1UL << i);
            } else {
                write_val &= ~(1UL << i);
            }
        }
        *tgt_reg = ((write_val & mask) << (addr_off * 8)) | (*tgt_reg & ~(mask << (addr_off * 8)));
    } else {
        unsigned long val = 0;

        for (unsigned int i = 0; i < 32; i++) {
            if (!vm_has_interrupt(vm, i + first_imr_int)) {
                continue;
            }
            unsigned int imr_val = *tgt_reg;
            if ((1UL << i) & imr_val) {
                val |= (1UL << i);
            }
        }

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << (acc->width * 8 - 1) & val)) {
            val |= ~mask;
        }
        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc_eibd_access(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t acc_intc2_offset = acc->addr - (unsigned long)intc2_hw;
    unsigned long bot = offsetof(struct intc2, EIBD);
    size_t reg_idx = (ALIGN(acc_intc2_offset - bot, 4)) / 4;

    unsigned long mask = BIT_MASK(0, acc->width * 8);
    size_t addr_off = acc->addr & 0x3UL;
    irqid_t int_id = 0;
    volatile uint32_t* tgt_reg = &(intc2_hw->EIBD[reg_idx]);
    int_id = reg_idx + 32;

    if (vm_has_interrupt(vm, int_id)) {
        if (emul_arch_is_bwop(&acc->arch)) {
            volatile uint8_t* byte_addr = ((volatile uint8_t*)tgt_reg) + addr_off;
            *byte_addr = emul_arch_bwop_emul_acc(&acc->arch, *byte_addr);
        } else if (acc->write) {
            unsigned long val = vcpu_readreg(vcpu, acc->reg);
            unsigned long virt_peid = val & 0x7UL;
            unsigned long phys_peid = vm_translate_to_pcpuid(vm, virt_peid);
            if (phys_peid == INVALID_CPUID) {
                /* in case the vcpu_id is invalid sanitize the write by using the first vcpu */
                phys_peid = vm_translate_to_pcpuid(vm, 0);
            }
            val = (*tgt_reg & INTC_EIBD_HYP_MASK) | (phys_peid & INTC_EIBD_PEID_MASK);
            *tgt_reg = ((val & mask) << (addr_off * 8)) | (*tgt_reg & ~(mask << (addr_off * 8)));
        } else {
            unsigned long val = *tgt_reg;
            unsigned long phys_peid = val & 0x7UL;
            unsigned long virt_peid = vm_translate_to_vcpuid(vm, phys_peid);
            if (virt_peid == INVALID_CPUID) {
                ERROR("Inconsistent state in intc2\n");
            } else {
                val = (virt_peid & INTC_EIBD_PEID_MASK);
            }

            val = (val >> (addr_off * 8)) & mask;
            if (acc->sign_ext && (1UL << (acc->width * 8 - 1) & val)) {
                val |= ~mask;
            }

            vcpu_writereg(vcpu, acc->reg, val);
        }
    } else if (!acc->write) {
        vcpu_writereg(vcpu, acc->reg, 0);
    }
}

static void emulate_intc_eeic_access(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t acc_intc2_offset = acc->addr - (unsigned long)intc2_hw;
    unsigned long bot = offsetof(struct intc2, EEIC);
    size_t reg_idx = (ALIGN(acc_intc2_offset - bot, 4)) / 4;

    unsigned long mask = BIT_MASK(0, acc->width * 8);
    size_t addr_off = acc->addr & 0x3UL;
    volatile uint32_t* tgt_reg = &(intc2_hw->EEIC[reg_idx]);
    irqid_t int_id = reg_idx + 32;

    if (vm_has_interrupt(vm, int_id)) {
        if (emul_arch_is_bwop(&acc->arch)) {
            volatile uint8_t* byte_addr = ((volatile uint8_t*)tgt_reg) + addr_off;
            *byte_addr = emul_arch_bwop_emul_acc(&acc->arch, *byte_addr);
        } else if (acc->write) {
            unsigned long val = vcpu_readreg(vcpu, acc->reg);
            *tgt_reg = ((val & mask) << (addr_off * 8)) | (*tgt_reg & ~(mask << (addr_off * 8)));
        } else {
            unsigned long val = *tgt_reg;

            val = (val >> (addr_off * 8)) & mask;
            if (acc->sign_ext && (1UL << (acc->width * 8 - 1) & val)) {
                val |= ~mask;
            }

            vcpu_writereg(vcpu, acc->reg, val);
        }
    } else if (!acc->write) {
        vcpu_writereg(vcpu, acc->reg, 0);
    }
}

static bool vintc2_emul_handler(struct emul_access* acc)
{
    if (IS_ALIGNED(acc->addr, acc->width) && acc->width <= 4) {
        unsigned long offset = (acc->addr - (unsigned long)intc2_hw);
        unsigned long base_reg_id = (offset) & (INTC2_OFFSET_MASK);
        switch (base_reg_id) {
            case INTC2_EIC_OFFSET:
                emulate_intc_eic_access(acc);
                break;
            case INTC2_IMR_OFFSET:
                emulate_intc_imr_access(acc);
                break;
            case INTC2_EIBD_OFFSET:
                emulate_intc_eibd_access(acc);
                break;
            case INTC2_EEIC_OFFSET:
                emulate_intc_eeic_access(acc);
                break;
            default:
                return false;
        }
    } else {
        if (!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
    }

    return true;
}

static bool vintif_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
    return false;
}

static bool veint_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
    return false;
}

static bool vfenc_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
    return false;
}

static bool vfeinc_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
    return false;
}

void vintc_init(struct vm* vm)
{
    if (cpu()->id == vm->master) {
        vm->arch.intc2_emul = (struct emul_mem){
            .va_base = platform.arch.intc.intc2_addr,
            .size = ALIGN(sizeof(struct intc2), PAGE_SIZE),
            .handler = vintc2_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.intc2_emul);

        /* of the following which can we bypass? */
        vm->arch.intif_emul = (struct emul_mem){
            .va_base = platform.arch.intc.intif_addr,
            .size = ALIGN(sizeof(struct intif), PAGE_SIZE),
            .handler = vintif_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.intif_emul);

        vm->arch.eint_emul = (struct emul_mem){
            .va_base = platform.arch.intc.eint_addr,
            .size = ALIGN(sizeof(struct eint), PAGE_SIZE),
            .handler = veint_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.eint_emul);

        vm->arch.fenc_emul = (struct emul_mem){
            .va_base = platform.arch.intc.fenc_addr,
            .size = ALIGN(sizeof(struct fenc), PAGE_SIZE),
            .handler = vfenc_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.fenc_emul);

        vm->arch.feinc_emul = (struct emul_mem){
            .va_base = platform.arch.intc.feinc_addr[cpu()->id],
            .size = ALIGN(sizeof(struct feinc), PAGE_SIZE),
            .handler = vfeinc_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.feinc_emul);
    }
}

void vintc_vcpu_reset(struct vcpu* vcpu)
{
    for (size_t i = 0; i < INTC_PRIVATE_IRQS_NUM; i++) {
        if (vm_has_interrupt(vcpu->vm, i)) {
            intc_set_trgt(i, vcpu->phys_id);
            intc_set_enable(i, false);
            intc_set_prio(i, INTC_MAX_PRIO);
            intc_set_pend(i, false);
        }
    }
}

void vintc_vm_reset(struct vm* vm)
{
    if (vm->master == cpu()->id) {
        for (size_t i = INTC_PRIVATE_IRQS_NUM; i < PLAT_MAX_INTERRUPTS; i++) {
            if (vm_has_interrupt(vm, i)) {
                intc_set_trgt(i, cpu()->id);
                intc_set_enable(i, false);
                intc_set_prio(i, INTC_MAX_PRIO);
                intc_set_pend(i, false);
            }
        }
    }
}
