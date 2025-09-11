/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <interrupts.h>
#include <intc.h>
#include <vm.h>
#include <types.h>

/* EIC */
#define EIRFn_BIT          (1U << 12)
#define EIMKn_BIT          (1U << 7)

#define EIPn_MASK          (0xF)

#define EIC_SET_EIRFn(reg) ((reg) |= (uint16_t)EIRFn_BIT)
#define EIC_CLR_EIRFn(reg) ((reg) &= (uint16_t)(~EIRFn_BIT))
#define EIC_GET_EIRFn(reg) (((reg) & (uint16_t)EIRFn_BIT) >> 12)

#define EIC_SET_EIMKn(reg) ((reg) |= (uint16_t)EIMKn_BIT)
#define EIC_CLR_EIMKn(reg) ((reg) &= (uint16_t)(~EIMKn_BIT))

#define EIC_SET_EIPn(reg, value) \
    ((reg) = (uint16_t)(((reg) & (uint16_t)(~EIPn_MASK)) | ((value) & EIPn_MASK)))

/* EIBD */
#define EIBD_GM_BIT      (1U << 15)

#define EIBD_GPID_MASK   (0x7U << 8)
#define EIBD_GPID_SHIFT  8

#define EIBD_PEID_MASK   (0x7U)

#define EIBD_SET_GM(reg) ((reg) |= (unsigned long)EIBD_GM_BIT)
#define EIBD_CLR_GM(reg) ((reg) &= (unsigned long)(~EIBD_GM_BIT))

#define EIBD_SET_GPID(reg, value) \
    ((reg) = ((reg) & (unsigned long)(~EIBD_GPID_MASK)) | (((value) & 0x7) << EIBD_GPID_SHIFT))

#define EIBD_SET_PEID(reg, value) \
    ((reg) = ((reg) & (unsigned long)(~EIBD_PEID_MASK)) | ((value) & EIBD_PEID_MASK))

volatile struct intc1* intc1_hw;
volatile struct intc2* intc2_hw;
volatile struct intif* intif_hw;
volatile struct eint* eint_hw;
volatile struct fenc* fenc_hw;
volatile struct feinc* feinc_hw[PLAT_CPU_NUM];

void intc_set_pend(irqid_t int_id, bool en)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        if (en) {
            EIC_SET_EIRFn(intc1_hw->self.EIC[int_id]);
        } else {
            EIC_CLR_EIRFn(intc1_hw->self.EIC[int_id]);
        }
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        if (en) {
            EIC_SET_EIRFn(intc2_hw->EIC[intc2_irq_id]);
        } else {
            EIC_CLR_EIRFn(intc2_hw->EIC[intc2_irq_id]);
        }
    }
}

bool intc_get_pend(irqid_t int_id)
{
    unsigned int pend = 0;
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        pend = EIC_GET_EIRFn(intc1_hw->self.EIC[int_id]);

    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        pend = EIC_GET_EIRFn(intc2_hw->EIC[intc2_irq_id]);
    }

    return !!pend;
}

void intc_hyp_assign(irqid_t int_id)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        for (cpuid_t c = 0; c < PLAT_CPU_NUM; c++) {
            EIBD_CLR_GM(intc1_hw->pe[c].EIBD[int_id]);
        }
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        EIBD_CLR_GM(intc2_hw->EIBD[intc2_irq_id]);
    }
}

void intc_vm_assign(struct vm* vm, irqid_t int_id)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        /* assign private interrupt to all VM's vcpus */
        for (cpuid_t i = 0; i < vm->cpu_num; i++) {
            cpuid_t pcpu_id = vm_translate_to_pcpuid(vm, i);
            if (pcpu_id != INVALID_CPUID) {
                EIBD_SET_GM(intc1_hw->pe[pcpu_id].EIBD[int_id]);
                EIBD_SET_GPID(intc1_hw->pe[pcpu_id].EIBD[int_id], vm->id);
            }
        }
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        EIBD_SET_GM(intc2_hw->EIBD[intc2_irq_id]);
        EIBD_SET_GPID(intc2_hw->EIBD[intc2_irq_id], vm->id);
        /* default target for interrupts is VM's vcpu 0 */
        cpuid_t pcpu_id = vm_translate_to_pcpuid(vm, 0);
        if (pcpu_id != INVALID_CPUID) {
            EIBD_SET_PEID(intc2_hw->EIBD[intc2_irq_id], pcpu_id);
        }
    }
}

void intc_set_trgt(irqid_t int_id, cpuid_t cpu_id)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        if (cpu()->id != cpu_id) {
            ERROR("setting private interrupt on another core");
        }
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        EIBD_SET_PEID(intc2_hw->EIBD[intc2_irq_id], cpu_id);
    }
}

void intc_set_enable(irqid_t int_id, bool en)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        if (en) {
            EIC_CLR_EIMKn(intc1_hw->self.EIC[int_id]);
        } else {
            EIC_SET_EIMKn(intc1_hw->self.EIC[int_id]);
        }
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        if (en) {
            EIC_CLR_EIMKn(intc2_hw->EIC[intc2_irq_id]);
        } else {
            EIC_SET_EIMKn(intc2_hw->EIC[intc2_irq_id]);
        }
    }
}

void intc_set_prio(irqid_t int_id, unsigned long prio)
{
    if (int_id < INTC_PRIVATE_IRQS_NUM) {
        EIC_SET_EIPn(intc1_hw->self.EIC[int_id], prio);
    } else {
        irqid_t intc2_irq_id = int_id - INTC_PRIVATE_IRQS_NUM;
        EIC_SET_EIPn(intc2_hw->EIC[intc2_irq_id], prio);
    }
}

static void intc_map_global_mmio(void)
{
    vaddr_t intc1_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.intc.intc1_addr, NUM_PAGES(sizeof(struct intc1)));
    if (intc1_ptr == INVALID_VA) {
        ERROR("maping intc1 failed");
    }
    intc1_hw = (struct intc1*)intc1_ptr;

    vaddr_t global_start_addr = platform.arch.intc.intif_addr;
    vaddr_t global_end_addr = platform.arch.intc.intc2_addr + sizeof(struct intc2);
    size_t global_size = global_end_addr - global_start_addr;
    size_t global_npages = NUM_PAGES(global_size);

    vaddr_t global_ptr =
        mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA, global_start_addr, global_npages);
    if (global_ptr == INVALID_VA) {
        ERROR("maping global interrupt controller region failed");
    }

    intc2_hw = (struct intc2*)platform.arch.intc.intc2_addr;
    intif_hw = (struct intif*)platform.arch.intc.intif_addr;
    eint_hw = (struct eint*)platform.arch.intc.eint_addr;
    fenc_hw = (struct fenc*)platform.arch.intc.fenc_addr;
}

static void intc_local_init(void)
{
    feinc_hw[cpu()->id] = (struct feinc*)platform.arch.intc.feinc_addr[cpu()->id];
}

void intc_init()
{
    if (cpu_is_master()) {
        intc_map_global_mmio();
    }
    /* wait for global mappings */
    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    /* setup local pointers */
    intc_local_init();

    cpu_sync_and_clear_msgs(&cpu_glb_sync);
}
