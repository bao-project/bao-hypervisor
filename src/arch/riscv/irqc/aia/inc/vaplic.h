/**
 * @file vaplic.h
 * @author Jose Martins <jose.martins@bao-project.org>
 * @author Francisco Marques (fmarques_00@protonmail.com)
 * @brief This module gives a set of function to virtualize the RISC-V APLIC.
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) Bao Project (www.bao-project.org), 2019-
 * 
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 */

#ifndef __VAPLIC_H__
#define __VAPLIC_H__

#include <bao.h>
#include <aplic.h>
#include <arch/spinlock.h>
#include <bitmap.h>
#include <emul.h>

/**
 * @brief   Data structure to the virtual interrupt controller when a APLIC 
 *          is the platform interrupt controller.
 * 
 */
struct virqc {
    spinlock_t lock;
    size_t idc_num;
    BITMAP_ALLOC(hw, APLIC_MAX_INTERRUPTS);
    uint32_t domaincfg;
    uint32_t srccfg[APLIC_MAX_INTERRUPTS-1];
    uint32_t setip[APLIC_MAX_INTERRUPTS/32];
    uint32_t in_clrip[APLIC_MAX_INTERRUPTS/32];
    uint32_t setie[APLIC_MAX_INTERRUPTS/32];
    uint32_t target[APLIC_MAX_INTERRUPTS-1];
    BITMAP_ALLOC(idelivery, APLIC_PLAT_IDC_NUM);
    BITMAP_ALLOC(iforce, APLIC_PLAT_IDC_NUM);
    uint32_t ithreshold[APLIC_PLAT_IDC_NUM];
    uint32_t topi_claimi[APLIC_PLAT_IDC_NUM];
    struct emul_mem aplic_domain_emul;
    struct emul_mem aplic_idc_emul;
};

struct vm;
struct vcpu;

/**
 * @brief Initialize the virtual APLIC for a given virtual machine.
 * 
 * @param vm Virtual machine associated to the virtual APLIC
 * @param vaplic_base address base of the physical APLIC
 * 
 */
void vaplic_init(struct vm *vm, vaddr_t vplic_base);

/**
 * @brief Inject an interrupt into a vm.
 * 
 * @param vcpu Virtual CPU that will inject the interrupt
 * @param id interrupt identification
 * 
 * The virtual CPU passed by arg. may not be the CPU to which the interrupt 
 * is associated. In that case the vcpu will send a msg to the target cpu. 
 */
void vaplic_inject(struct vcpu *vcpu, irqid_t id);

/**
 * @brief For a given virtual machine and a interrupt, associate this interrupt
 *        with the physical one. Thus, interrupt id is mapped to the physical
 *        id source.
 * 
 * @param vm Virtual machine to associate the 1-1 virt/phys interrupt
 * @param id interrupt identification to associate.
 */
void vaplic_set_hw(struct vm *vm, irqid_t id);

typedef struct vcpu vcpu_t;
static inline void vcpu_arch_inject_hw_irq_vxplic(vcpu_t *vcpu, uint64_t id)
{
    vaplic_inject(vcpu, id);
}

static inline void vcpu_arch_inject_irq_vxplic(vcpu_t *vcpu, uint64_t id)
{
    vaplic_inject(vcpu, id);
}

#endif /* __VAPLIC_H__ */