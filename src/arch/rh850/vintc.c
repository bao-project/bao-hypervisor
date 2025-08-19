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
#include <arch/srs.h>


#define F8_OPCODE               (0x3EUL)
#define F9_OPCODE               (0x3FUL)
#define F9_SUBOPCODE            (0x1CUL)

#define OPCODE_SHIFT            (5)
#define OPCODE_MASK             (0x3FUL << OPCODE_SHIFT)

#define SUBOPCODE_SHIFT         (19)
#define SUBOPCODE_MASK          (0x1FFFUL << SUBOPCODE_SHIFT)

#define BITIDX_SHIFT            (11)
#define BITIDX_MASK             (0x7UL << BITIDX_SHIFT)

#define REGIDX_SHIFT            (11)
#define REGIDX_MASK             (0x1FUL << REGIDX_SHIFT)

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

/* static void emulate_intc1_eic_access(struct emul_access *acc, size_t offset) */
/* { */
/*     size_t int_id = ALIGN(offset, 16)/16; */

/*     struct vcpu* vcpu = cpu()->vcpu; */
/*     struct vm* vm = vcpu->vm; */

/*     if(!vm_has_interrupt(vm, int_id)){ */
/*         ERROR("VM tried to access unassigned interrupt"); */
/*     } */

/*     if(acc->write){ */
/*         unsigned long val = vcpu_readreg(vcpu, acc->reg); */
/*         intc1_hw->EIC[int_id] = val; */
/* #warning "Unimplemented need to virtualize intc1 emulation peid" */
/*     } else { */
/*         unsigned int val = intc1_hw->EIC[int_id]; */
/*         vcpu_writereg(vcpu, acc->reg, val); */
/* #warning "Unimplemented need to virtualize intc1 emulation peid" */
/*     } */
/* } */

/* static void emulate_intc1_imr_access(struct emul_access *acc, size_t offset) */
/* { */
/*     struct vcpu* vcpu = cpu()->vcpu; */
/*     struct vm* vm = vcpu->vm; */

/*     if(acc->write){ */
/*         unsigned long val = vcpu_readreg(vcpu, acc->reg); */

/*         for(unsigned int i = 0; i < 32; i++){ */
/*             if(!vm_has_interrupt(vm, i)){ */
/*                 continue; */
/*             } */
/*             unsigned int imr_bit = (i % 32); */
/*             if((1UL << imr_bit) & val){ */
/*                 intc1_hw->IMR |= 1UL << imr_bit; */
/*             } */
/*         } */
/*     } else { */
/*         unsigned long val = 0; */

/*         for(unsigned int i = 0; i < 32; i++){ */
/*             if(!vm_has_interrupt(vm, i)){ */
/*                 continue; */
/*             } */
/*             unsigned int imr_bit = (i % 32); */
/*             unsigned int imr_val = intc1_hw->IMR; */
/*             if((1UL << imr_bit) & imr_val){ */
/*                 val |= (1UL << imr_bit); */
/*             } */
/*         } */
/*         vcpu_writereg(vcpu, acc->reg, val); */
/*     } */
/* } */

/* static void emulate_intc1_eeic_access(struct emul_access *acc, size_t offset) */
/* { */
/*     size_t int_id = ALIGN(offset, 32)/32; */

/*     struct vcpu* vcpu = cpu()->vcpu; */
/*     struct vm* vm = vcpu->vm; */

/*     if(!vm_has_interrupt(vm, int_id)){ */
/*         ERROR("VM tried to access unassigned interrupt"); */
/*     } */

/*     if(acc->write){ */
/*         unsigned long val = vcpu_readreg(vcpu, acc->reg); */
/*         intc1_hw->EEIC[int_id] = val; */
/* #warning "Unimplemented need to virtualize intc1 emulation peid" */
/*     } else { */
/*         unsigned int val = intc1_hw->EEIC[int_id]; */
/*         vcpu_writereg(vcpu, acc->reg, val); */
/* #warning "Unimplemented need to virtualize intc1 emulation peid" */
/*     } */
/* } */

/* static void emulate_intc1_eibg_access(struct emul_access *acc, size_t offset) */
/* { */
/*     struct vcpu* vcpu = cpu()->vcpu; */

/*     /1* TODO  Check priority threshold ... *1/ */

/*     if(acc->write){ */
/*         unsigned long val = vcpu_readreg(vcpu, acc->reg); */
/*         intc1_hw->EIBG = val; */
/*     } else { */
/*         /1* TODO access imr *1/ */
/*         unsigned int val = intc1_hw->EIBG; */
/*         vcpu_writereg(vcpu, acc->reg, val); */
/*     } */
/* } */

/* static bool vintc1_emul_handler(struct emul_access* acc) */
/* { */
/*     size_t acc_offset = acc->addr - platform.arch.intc.intc1_addr; */

/*     size_t intc1_eic_bot = offsetof(struct intc1, EIC); */
/*     size_t intc1_eic_top = sizeof(((struct intc1*)NULL)->EIC); */
/*     if(acc_offset >= intc1_eic_bot && acc_offset < intc1_eic_top){ */
/*         emulate_intc1_eic_access(acc, acc_offset - intc1_eic_bot); */
/*     } */

/*     size_t intc1_imr_bot = offsetof(struct intc1, IMR); */
/*     size_t intc1_imr_top = sizeof(((struct intc1*)NULL)->IMR); */
/*     if(acc_offset >= intc1_imr_bot && acc_offset < intc1_imr_top){ */
/*         emulate_intc1_imr_access(acc, acc_offset - intc1_imr_bot); */
/*     } */

/*     size_t intc1_eeic_bot = offsetof(struct intc1, EEIC); */
/*     size_t intc1_eeic_top = sizeof(((struct intc1*)NULL)->EEIC); */
/*     if(acc_offset >= intc1_eeic_bot && acc_offset < intc1_eeic_top){ */
/*         emulate_intc1_eeic_access(acc, acc_offset - intc1_eeic_bot); */
/*     } */

/*     size_t intc1_eibg_bot = offsetof(struct intc1, EIBG); */
/*     size_t intc1_eibg_top = sizeof(((struct intc1*)NULL)->EIBG); */
/*     if(acc_offset >= intc1_eibg_bot && acc_offset < intc1_eibg_top){ */
/*         emulate_intc1_eibg_access(acc, acc_offset - intc1_eibg_bot); */
/*     } */

/*     ERROR("%s not implemented", __func__); */
/* } */

static void emulate_intc2_eic_access(struct emul_access* acc, size_t offset, uint32_t mask, unsigned long bit_op)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;
    
    size_t eic_idx = ALIGN(offset, 2) / 2;
    irqid_t int_id = eic_idx + 32;
    uint32_t addr_off = acc->addr & 0x1UL;

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    /* bit manipulation instruction */
    if (bit_op != 0) {

        unsigned long psw = get_gmpsw();
        if (intc2_hw->EIC[eic_idx] & mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (bit_op)
        {
            /* SET1 */
            case 1:
                intc2_hw->EIC[eic_idx] |= (uint16_t)(mask);
            break;

            /* NOT1 */
            case 2:                
                intc2_hw->EIC[eic_idx] = (intc2_hw->EIC[eic_idx] & (uint16_t)(mask)) ?
                                            (intc2_hw->EIC[eic_idx] & (uint16_t)(~mask)) :
                                            (intc2_hw->EIC[eic_idx] | (uint16_t)(mask)); 
            break;

            /* CLR1 */
            case 3:
                intc2_hw->EIC[eic_idx] &= (uint16_t)(~mask);
            break;

            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        intc2_hw->EIC[eic_idx] = (uint16_t)(((val & mask) << (addr_off * 8)) | 
                                    (intc2_hw->EIC[eic_idx] & ~(mask << (addr_off * 8))));
    }
    else {
        unsigned long val = intc2_hw->EIC[eic_idx];

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc2_imr_access(struct emul_access* acc, size_t offset, uint32_t mask, unsigned long bit_op)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t imr_idx = ALIGN(offset, 4) / 4;
    uint32_t addr_off = acc->addr & 0x3UL;
    irqid_t first_imr_int = imr_idx * 32 + 32;

    /* bit manipulation instruction */
    if (bit_op != 0) {

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {
            if (!vm_has_interrupt(vm, i)) {
                ERROR("VM tried to access unassigned interrupt");
            }
        }

        unsigned long psw = get_gmpsw();
        if (intc2_hw->IMR[imr_idx] & mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (bit_op)
        {
            /* SET1 */
            case 1:
                intc2_hw->IMR[imr_idx] |= mask;
            break;

            /* NOT1 */
            case 2:                
                intc2_hw->IMR[imr_idx] = (intc2_hw->IMR[imr_idx] & mask) ?
                                            (intc2_hw->IMR[imr_idx] & ~mask) :
                                            (intc2_hw->IMR[imr_idx] | mask); 
            break;

            /* CLR1 */
            case 3:
                intc2_hw->IMR[imr_idx] &= ~mask;
            break;

            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        unsigned long write_val = intc2_hw->IMR[imr_idx];

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {

            if (!vm_has_interrupt(vm, i)) {
                continue;
            }

            unsigned int imr_bit = (i % 32);
            if ((1UL << imr_bit) & val)
                write_val |= (1UL << imr_bit);
            else
                write_val &= ~(1UL << imr_bit);
        }
        intc2_hw->IMR[imr_idx] = ((write_val & mask) << (addr_off * 8)) | 
                                    (intc2_hw->IMR[imr_idx] & ~(mask << (addr_off * 8)));
    } else {
        unsigned long val = 0;

        for (unsigned int i = first_imr_int; i < first_imr_int + 32; i++) {
            if (!vm_has_interrupt(vm, i)) {
                continue;
            }

            unsigned int imr_bit = (i % 32);
            unsigned int imr_val = intc2_hw->IMR[imr_idx];
            if ((1UL << imr_bit) & imr_val) {
                val |= 1UL << imr_bit;
            }
        }

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }
        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc2_eibd_access(struct emul_access* acc, size_t offset, uint32_t mask, unsigned long bit_op)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;
    
    size_t eibd_idx = ALIGN(offset, 4) / 4;
    irqid_t int_id = eibd_idx + 32;
    uint32_t addr_off = acc->addr & 0x3UL;
    uint32_t aux_mask = mask & 0xFFFF0000;

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    // TODO: set EIBDn.GPID with VM ID
    // TODO: set EIBDn.PEID with physical CPU ID where the VM is running.

    /* we use 0xFFFF0000 to mask access to virtualization configuration */
    /* bit manipulation instruction */
    if (bit_op != 0) {

        unsigned long psw = get_gmpsw();
        if (intc2_hw->EIBD[eibd_idx] & aux_mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (bit_op)
        {
            /* SET1 */
            case 1:
                intc2_hw->EIBD[eibd_idx] |= aux_mask;
            break;

            /* NOT1 */
            case 2:                
                intc2_hw->EIBD[eibd_idx] = (intc2_hw->EIBD[eibd_idx] & aux_mask) ?
                                            (intc2_hw->EIBD[eibd_idx] & ~aux_mask) :
                                            (intc2_hw->EIBD[eibd_idx] | aux_mask); 
            break;

            /* CLR1 */
            case 3:
                intc2_hw->EIBD[eibd_idx] &= ~aux_mask;
            break;

            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = (vcpu_readreg(vcpu, acc->reg) & 0xFFFF0000) | 
                                (intc2_hw->EIBD[eibd_idx] & ~0xFFFF0000);
        intc2_hw->EIBD[eibd_idx] = ((val & mask) << (addr_off * 8)) | 
                                    (intc2_hw->EIBD[eibd_idx] & ~(mask << (addr_off * 8)));
    }
    else {
        unsigned long val = intc2_hw->EIBD[eibd_idx] & 0xFFFF0000;

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

static void emulate_intc2_eeic_access(struct emul_access* acc, size_t offset, uint32_t mask, unsigned long bit_op)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;
    
    size_t eeic_idx = ALIGN(offset, 4) / 4;
    size_t int_id = eeic_idx + 32;
    uint32_t addr_off = acc->addr & 0x3UL;

    if (!vm_has_interrupt(vm, int_id)) {
        ERROR("VM tried to access unassigned interrupt");
    }

    /* bit manipulation instruction */
    if (bit_op != 0) {

        unsigned long psw = get_gmpsw();
        if (intc2_hw->EEIC[eeic_idx] & mask)
            set_gmpsw(psw & ~0x1UL);
        else
            set_gmpsw(psw | 0x1UL);

        switch (bit_op)
        {
            /* SET1 */
            case 1:
                intc2_hw->EEIC[eeic_idx] |= mask;
            break;

            /* NOT1 */
            case 2:                
                intc2_hw->EEIC[eeic_idx] = (intc2_hw->EEIC[eeic_idx] & mask) ?
                                            (intc2_hw->EEIC[eeic_idx] & ~mask) :
                                            (intc2_hw->EEIC[eeic_idx] | mask); 
            break;

            /* CLR1 */
            case 3:
                intc2_hw->EEIC[eeic_idx] &= ~mask;
            break;

            /* TST1 only modifies the PSW.Z flag */
            default:
            break;
        }
    }
    else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        intc2_hw->EEIC[eeic_idx] = ((val & mask) << (addr_off * 8)) | 
                                    (intc2_hw->EEIC[eeic_idx] & ~(mask << (addr_off * 8)));
        /* TODO: Unimplemented need to virtualize intc2 emulation peid */
    }
    else {
        unsigned long val = intc2_hw->EEIC[eeic_idx];

        val = (val >> (addr_off * 8)) & mask;
        if (acc->sign_ext && (1UL << ((acc->reg_width * 8) + 7) & val)) {
            val |= ~mask;
        }

        vcpu_writereg(vcpu, acc->reg, val);
        /* TODO: Unimplemented need to virtualize intc2 emulation peid */
    }
}

bool vintc2_emul_handler(struct emul_access* acc)
{
    size_t acc_offset = acc->addr - platform.arch.intc.intc2_addr;
    uint32_t mask = ((1U << (8 * (acc->reg_width + 1))) - 1) 
                        | ((acc->reg_width == 2) * 0xFF000000);

    unsigned short* pc = (unsigned short*)(vcpu_readpc(cpu()->vcpu));
    set_mpid7(HYP_SPID);
    fence_sync();
    unsigned long inst = (unsigned long)(*pc | (*(pc+1) << 16));
    set_mpid7(AUX_SPID);
    fence_sync();
    unsigned long opcode = ((inst & OPCODE_MASK) >> OPCODE_SHIFT);
    unsigned long subopcode = ((inst & SUBOPCODE_MASK) >> SUBOPCODE_SHIFT);
    unsigned long bit_op = 0;

    /* bit manipulation instruction */    
    if (opcode == F8_OPCODE) {
        mask = 1UL << ((inst & BITIDX_MASK) >> BITIDX_SHIFT);
        bit_op = ((inst & 0xC000UL) >> 14) + 1;
    }
    else if (opcode == F9_OPCODE && subopcode == F9_SUBOPCODE) {
        unsigned long bit_idx = vcpu_readreg(cpu()->vcpu, (inst & REGIDX_MASK) >> REGIDX_SHIFT);
        mask = 1UL << (bit_idx & 0x7UL);
        bit_op = ((inst & 0x60000UL) >> 17) + 1;
    }

    size_t intc2_eic_bot = offsetof(struct intc2, EIC);
    size_t intc2_eic_top = sizeof(((struct intc2*)NULL)->EIC) + intc2_eic_bot - 2;
    if (acc_offset >= intc2_eic_bot && acc_offset < intc2_eic_top) {
        emulate_intc2_eic_access(acc, acc_offset - intc2_eic_bot, mask, bit_op);
        return true;
    }

    size_t intc2_imr_bot = offsetof(struct intc2, IMR);
    size_t intc2_imr_top = sizeof(((struct intc2*)NULL)->IMR) + intc2_imr_bot - 4;
    if (acc_offset >= intc2_imr_bot && acc_offset < intc2_imr_top) {
        emulate_intc2_imr_access(acc, acc_offset - intc2_imr_bot, mask, bit_op);
        return true;
    }

    size_t intc2_eibd_bot = offsetof(struct intc2, EIBD);
    size_t intc2_eibd_top = sizeof(((struct intc2*)NULL)->EIBD) + intc2_eibd_bot - 4;
    if (acc_offset >= intc2_eibd_bot && acc_offset < intc2_eibd_top) {
        emulate_intc2_eibd_access(acc, acc_offset - intc2_eibd_bot, mask, bit_op);
        return true;
    }

    size_t intc2_eeic_bot = offsetof(struct intc2, EEIC);
    size_t intc2_eeic_top = sizeof(((struct intc2*)NULL)->EEIC) + intc2_eeic_bot - 4;
    if (acc_offset >= intc2_eeic_bot && acc_offset < intc2_eeic_top) {
        emulate_intc2_eeic_access(acc, acc_offset - intc2_eeic_bot, mask, bit_op);
        return true;
    }

    ERROR("%s not implemented", __func__);
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

void vintc_init(struct vcpu* vcpu)
{
    struct vm* vm = vcpu->vm;

    /* vm->arch.intc1_emul = (struct emul_mem){ */
    /*     .va_base = platform.arch.intc.intc1_addr, */
    /*     .size = ALIGN(sizeof(struct intc1), PAGE_SIZE), */
    /*     .handler = vintc1_emul_handler, */
    /* }; */
    /* vm_emul_add_mem(vm, &vm->arch.intc1_emul); */

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

// TODO
bool vbootctrl_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;
    bool ret;

    if (vm->cpu_num > 1)
    {
        // Multi-core guest: check if the cores it is trying 
        //                   to start belongs to that VM
        ret = true;
    }
    else {
        // Single-core guest: ignore? signal error? 
        ret = true;
    }

    return ret;
}

void vbootctrl_init(struct vcpu* vcpu)
{
    struct vm* vm = vcpu->vm;

    vm->arch.bootctrl_emul = (struct emul_mem){
        .va_base = platform.arch.bootctrl_addr,
        .size = 0x10,
        .handler = vbootctrl_emul_handler,
    };
    vm_emul_add_mem(vm, &vm->arch.bootctrl_emul);
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
