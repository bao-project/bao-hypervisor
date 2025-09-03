/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <interrupts.h>
#include <platform.h>
#include <vm.h>
#include <arch/fences.h>
#include <arch/intc.h>
#include <arch/ipir.h>
#include <arch/srs.h>

extern volatile struct intc1* intc1_hw;
extern volatile struct intc2* intc2_hw;
extern volatile struct intif* intif_hw;
extern volatile struct eint* eint_hw;
extern volatile struct fenc* fenc_hw;
extern volatile struct feinc* feinc_hw[PLAT_CPU_NUM];


void vintc_inject(struct vcpu* vcpu, irqid_t int_id)
{
    struct vm* vm = vcpu->vm;

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }
    intc_set_pend(int_id, true);
}

static void emulate_intc_eic_access(struct emul_access* acc, size_t reg_idx, unsigned long mask)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t addr_off = acc->addr & 0x1UL;
    uint16_t bitop_mask = (uint16_t)(acc->arch.byte_mask << (addr_off * 8));
    irqid_t int_id = 0;
    volatile uint16_t* tgt_reg = NULL;

    if (acc->addr < platform.arch.intc.intc1_addr) {    /* INTC2 */
        int_id = reg_idx + 32;
        tgt_reg = &(intc2_hw->EIC[reg_idx]);
    }
    else {  /* INTC1 */
        int_id = reg_idx;
        tgt_reg = &(intc1_hw->EIC[reg_idx]);
    }

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    /* bit manipulation instruction */
    if (acc->arch.op != NO_OP) {

        unsigned long psw = get_gmpsw();
        if (*tgt_reg & bitop_mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (acc->arch.op)
        {
            case SET1:
                *tgt_reg |= bitop_mask;
            break;
            case NOT1:                
                *tgt_reg = (uint16_t)((*tgt_reg & bitop_mask) ?
                                        (*tgt_reg & ~bitop_mask) :
                                        (*tgt_reg | bitop_mask));
            break;
            case CLR1:
                *tgt_reg &= (uint16_t)(~bitop_mask);
            break;
            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        *tgt_reg = (uint16_t)(((val & mask) << (addr_off * 8)) | 
                                    (*tgt_reg & ~(mask << (addr_off * 8))));
    }
    else {
        unsigned long val = *tgt_reg;

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc_imr_access(struct emul_access* acc, size_t reg_idx, uint32_t mask)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t addr_off = acc->addr & 0x3UL;
    uint32_t bitop_mask = acc->arch.byte_mask << (addr_off * 8);
    irqid_t int_id = 0;
    irqid_t first_imr_int = 0;
    volatile uint32_t* tgt_reg = NULL;

    if (acc->addr < platform.arch.intc.intc1_addr) {    /* INTC2 */
        first_imr_int = reg_idx * 32 + 32;
        tgt_reg = &(intc2_hw->IMR[reg_idx]);
    }
    else {  /* INTC1 */
        first_imr_int = 0;
        tgt_reg = &(intc1_hw->IMR);
    }

    /* bit manipulation instruction */
    if (acc->arch.op != NO_OP) {

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {
            if ((1UL << (i % 32)) & bitop_mask) {
                int_id = i;
                break;
            }
        }

        if (int_id == IPI_HYP_IRQ_ID)
            bitop_mask = 0;
        else if (!vm_has_interrupt(vm, int_id)) {
            ERROR("VM tried to access unassigned interrupt");
        }

        unsigned long psw = get_gmpsw();
        if (*tgt_reg & bitop_mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (acc->arch.op)
        {
            case SET1:
                *tgt_reg |= bitop_mask;
            break;
            case NOT1:                
                *tgt_reg = (*tgt_reg & bitop_mask) ?
                            (*tgt_reg & ~bitop_mask) :
                            (*tgt_reg | bitop_mask);
            break;
            case CLR1:
                *tgt_reg &= ~bitop_mask;
            break;
            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        unsigned long write_val = *tgt_reg;

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {

            if (!vm_has_interrupt(vm, i) || (int_id == IPI_HYP_IRQ_ID)) {
                continue;
            }

            unsigned int imr_bit = (i % 32);
            if ((1UL << imr_bit) & val)
                write_val |= (1UL << imr_bit);
            else
                write_val &= ~(1UL << imr_bit);
        }
        *tgt_reg = ((write_val & mask) << (addr_off * 8)) | 
                    (*tgt_reg & ~(mask << (addr_off * 8)));
    } else {
        unsigned long val = 0;

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {
            if (!vm_has_interrupt(vm, i) || (int_id == IPI_HYP_IRQ_ID)) {
                continue;
            }

            unsigned int imr_bit = (i % 32);
            unsigned int imr_val = *tgt_reg;
            if ((1UL << imr_bit) & imr_val) {
                val |= (1UL << imr_bit);
            }
        }

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }
        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc_eibd_access(struct emul_access* acc, size_t reg_idx, uint32_t mask)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t addr_off = acc->addr & 0x3UL;
    uint32_t bitop_mask = (acc->arch.byte_mask << (addr_off * 8)) & 0xFFFF0000;
    irqid_t int_id = 0;
    volatile uint32_t* tgt_reg = NULL;

    if (acc->addr < platform.arch.intc.intc1_addr) {    /* INTC2 */
        int_id = reg_idx + 32;
        tgt_reg = &(intc2_hw->EIBD[reg_idx]);
    }
    else {  /* INTC1 */
        int_id = reg_idx;
        tgt_reg = &(intc1_hw->EIBD[reg_idx]);
    }

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    /* we use 0xFFFF0000 to mask access to virtualization configuration */
    /* bit manipulation instruction */
    if (acc->arch.op != NO_OP) {

        unsigned long psw = get_gmpsw();
        if (*tgt_reg & bitop_mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (acc->arch.op)
        {
            case SET1:
                *tgt_reg |= bitop_mask;
            break;
            case NOT1:                
                *tgt_reg = (*tgt_reg & bitop_mask) ?
                            (*tgt_reg & ~bitop_mask) :
                            (*tgt_reg | bitop_mask);
            break;
            case CLR1:
                *tgt_reg &= ~bitop_mask;
            break;
            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        unsigned long virt_peid = val & 0x7UL;
        unsigned long phys_peid = vm_translate_to_pcpuid(vm, virt_peid);
        if (phys_peid != INVALID_CPUID)
            val = (val & 0xFFFF0000) | (*tgt_reg & 0xFFF8) | (phys_peid & 0x7UL);
        else
            val = (val & 0xFFFF0000) | (*tgt_reg & ~0xFFFF0000);
        *tgt_reg = ((val & mask) << (addr_off * 8)) | 
                                    (*tgt_reg & ~(mask << (addr_off * 8)));
    }
    else {
        unsigned long val = *tgt_reg;
        unsigned long phys_peid = val & 0x7UL;
        unsigned long virt_peid = INVALID_CPUID;
        for (size_t i = 0; i < vm->cpu_num; i++) {
            if (vm->vcpus[i].phys_id == phys_peid)
                virt_peid = vm->vcpus[i].id;
        }
        if (virt_peid != INVALID_CPUID)
            val = (val & 0xFFFF0000) | (virt_peid & 0x7UL);
        else
            val = (val & 0xFFFF0000);

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc_fibd_access(struct emul_access* acc, uint32_t mask)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t addr_off = acc->addr & 0x3UL;
    volatile uint32_t* tgt_reg = &(intc1_hw->FIBD);

    if (acc->arch.op != NO_OP || acc->write) {
        /* FIBD register can not be written/modified by any guest */
    }
    else {
        unsigned long val = 0;
        unsigned long phys_peid = *tgt_reg & 0x7UL;
        unsigned long virt_peid = INVALID_CPUID;
        for (size_t i = 0; i < vm->cpu_num; i++) {
            if (vm->vcpus[i].phys_id == phys_peid)
                virt_peid = vm->vcpus[i].id;
        }
        if (virt_peid != INVALID_CPUID)
            val = virt_peid & 0x7UL;

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc_eeic_access(struct emul_access* acc, size_t reg_idx, uint32_t mask)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t addr_off = acc->addr & 0x3UL;
    uint32_t bitop_mask = acc->arch.byte_mask << (addr_off * 8);
    irqid_t int_id = 0;
    volatile uint32_t* tgt_reg = NULL;

    if (acc->addr < platform.arch.intc.intc1_addr) {    /* INTC2 */
        int_id = reg_idx + 32;
        tgt_reg = &(intc2_hw->EEIC[reg_idx]);
    }
    else {  /* INTC1 */
        int_id = reg_idx;
        tgt_reg = &(intc1_hw->EEIC[reg_idx]);
    }

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    /* bit manipulation instruction */
    if (acc->arch.op != NO_OP) {

        unsigned long psw = get_gmpsw();
        if (*tgt_reg & bitop_mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (acc->arch.op)
        {
            case SET1:
                *tgt_reg |= bitop_mask;
            break;
            case NOT1:                
                *tgt_reg = (*tgt_reg & bitop_mask) ?
                                            (*tgt_reg & ~bitop_mask) :
                                            (*tgt_reg | bitop_mask);
            break;
            case CLR1:
                *tgt_reg &= ~bitop_mask;
            break;
            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        *tgt_reg = ((val & mask) << (addr_off * 8)) | 
                                    (*tgt_reg & ~(mask << (addr_off * 8)));
    }
    else {
        unsigned long val = *tgt_reg;

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

bool vintc1_emul_handler(struct emul_access* acc)
{
    size_t acc_offset = acc->addr - platform.arch.intc.intc1_addr;
    unsigned long mask = ((1U << (8 * (acc->reg_width + 1))) - 1) 
                            | ((acc->reg_width == 2) * 0xFF000000);

    size_t intc1_eic_bot = offsetof(struct intc1, EIC);
    size_t intc1_eic_top = sizeof(((struct intc1*)NULL)->EIC) + intc1_eic_bot;
    size_t intc1_eic_idx = (ALIGN(acc_offset - intc1_eic_bot, 2)) / 2;
    if (acc_offset >= intc1_eic_bot && acc_offset < intc1_eic_top && 
            intc1_eic_idx != IPI_HYP_IRQ_ID) {
        emulate_intc_eic_access(acc, intc1_eic_idx, mask);
        return true;
    }

    size_t intc1_imr_bot = offsetof(struct intc1, IMR);
    size_t intc1_imr_top = sizeof(((struct intc1*)NULL)->IMR) + intc1_imr_bot;
    size_t intc1_imr_idx = (ALIGN(acc_offset - intc1_imr_bot, 4)) / 4;
    if (acc_offset >= intc1_imr_bot && acc_offset < intc1_imr_top) {
        emulate_intc_imr_access(acc, intc1_imr_idx, mask);
        return true;
    }

    size_t intc1_eibd_bot = offsetof(struct intc1, EIBD);
    size_t intc1_eibd_top = sizeof(((struct intc1*)NULL)->EIBD) + intc1_eibd_bot;
    size_t intc1_eibd_idx = (ALIGN(acc_offset - intc1_eibd_bot, 4)) / 4;
    if (acc_offset >= intc1_eibd_bot && acc_offset < intc1_eibd_top &&
        intc1_eibd_idx != IPI_HYP_IRQ_ID) {
        emulate_intc_eibd_access(acc, intc1_eibd_idx, mask);
        return true;
    }
    
    size_t intc1_fibd_bot = offsetof(struct intc1, FIBD);
    size_t intc1_fibd_top = sizeof(((struct intc1*)NULL)->FIBD) + intc1_fibd_bot;
    if (acc_offset >= intc1_fibd_bot && acc_offset < intc1_fibd_top) {
        emulate_intc_fibd_access(acc, mask);
        return true;
    }

    size_t intc1_eeic_bot = offsetof(struct intc1, EEIC);
    size_t intc1_eeic_top = sizeof(((struct intc1*)NULL)->EEIC) + intc1_eeic_bot;
    size_t intc1_eeic_idx = (ALIGN(acc_offset - intc1_eeic_bot, 4)) / 4;
    if (acc_offset >= intc1_eeic_bot && acc_offset < intc1_eeic_top &&
            intc1_eeic_idx != IPI_HYP_IRQ_ID) {
        emulate_intc_eeic_access(acc, intc1_eeic_idx, mask);
        return true;
    }

    /* Ignore access */
    if (!acc->write && acc->arch.op == NO_OP)
        vcpu_writereg(cpu()->vcpu, acc->reg, 0);

    return true;
}

bool vintc2_emul_handler(struct emul_access* acc)
{
    size_t acc_offset = acc->addr - platform.arch.intc.intc2_addr;
    unsigned long mask = ((1U << (8 * (acc->reg_width + 1))) - 1) 
                            | ((acc->reg_width == 2) * 0xFF000000);

    size_t intc2_eic_bot = offsetof(struct intc2, EIC);
    size_t intc2_eic_top = sizeof(((struct intc2*)NULL)->EIC) + intc2_eic_bot;
    size_t intc2_eic_idx = (ALIGN(acc_offset - intc2_eic_bot, 2)) / 2;
    if (acc_offset >= intc2_eic_bot && acc_offset < intc2_eic_top) {
        emulate_intc_eic_access(acc, intc2_eic_idx, mask);
        return true;
    }

    size_t intc2_imr_bot = offsetof(struct intc2, IMR);
    size_t intc2_imr_top = sizeof(((struct intc2*)NULL)->IMR) + intc2_imr_bot;
    size_t intc2_imr_idx = (ALIGN(acc_offset - intc2_imr_bot, 4)) / 4;
    if (acc_offset >= intc2_imr_bot && acc_offset < intc2_imr_top) {
        emulate_intc_imr_access(acc, intc2_imr_idx, mask);
        return true;
    }

    size_t intc2_eibd_bot = offsetof(struct intc2, EIBD);
    size_t intc2_eibd_top = sizeof(((struct intc2*)NULL)->EIBD) + intc2_eibd_bot;
    size_t intc2_eibd_idx = (ALIGN(acc_offset - intc2_eibd_bot, 4)) / 4;
    if (acc_offset >= intc2_eibd_bot && acc_offset < intc2_eibd_top) {
        emulate_intc_eibd_access(acc, intc2_eibd_idx, mask);
        return true;
    }

    size_t intc2_eeic_bot = offsetof(struct intc2, EEIC);
    size_t intc2_eeic_top = sizeof(((struct intc2*)NULL)->EEIC) + intc2_eeic_bot;
    size_t intc2_eeic_idx = (ALIGN(acc_offset - intc2_eeic_bot, 4)) / 4;
    if (acc_offset >= intc2_eeic_bot && acc_offset < intc2_eeic_top) {
        emulate_intc_eeic_access(acc, intc2_eeic_idx, mask);
        return true;
    }

    /* Ignore access */
    if (!acc->write && acc->arch.op == NO_OP)
        vcpu_writereg(cpu()->vcpu, acc->reg, 0);

    return true;
}

bool vintif_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
}

bool veint_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
}

bool vfenc_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
}

bool vfeinc_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    ERROR("%s not implemented", __func__);
}

void vintc_init(struct vm* vm)
{
    if (cpu()->id == vm->master) {

        vm->arch.intc1_emul = (struct emul_mem){
            .va_base = platform.arch.intc.intc1_addr,
            .size = ALIGN(sizeof(struct intc1), PAGE_SIZE),
            .handler = vintc1_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.intc1_emul);

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
        
        // TODO: Add spinlock for INTC emulation
    }
}

void vintc_vcpu_reset(struct vcpu* vcpu) {
    for (size_t i = 0; i < PRIVATE_IRQS_NUM; i++) {
        if (vm_has_interrupt(vcpu->vm, i)) {
            intc_set_trgt(i, vcpu->phys_id);
            intc_set_enable(i, false);
            intc_set_prio(i, 0);
            // intc_set_act(i, false);
            intc_set_pend(i, false);
        }
    }
}

void vintc_vm_reset(struct vm* vm) {
    if (vm->master == cpu()->id) {
        for (size_t i = PRIVATE_IRQS_NUM; i < MAX_INTERRUPTS; i++) {
            if (vm_has_interrupt(vm, i)) {
                intc_set_trgt(i, cpu()->id);
                intc_set_enable(i, false);
                intc_set_prio(i, 0);
                // intc_set_act(i, false);
                intc_set_pend(i, false);
            }
        }
    }
}
