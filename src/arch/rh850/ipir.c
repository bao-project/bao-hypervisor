/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <interrupts.h>
#include <vm.h>
#include <ipir.h>

#define IPIR_REGS_PAT_MASK (0x9FUL)

#define IPInENS_PAT        (0x000UL)
#define IPInFLGS_PAT       (0x004UL)
#define IPInFCLRS_PAT      (0x008UL)
#define IPInREQS_PAT       (0x010UL)
#define IPInRCLRS_PAT      (0x014UL)

#define IPInENm_PAT        (0x800UL)
#define IPInFLGm_PAT       (0x804UL)
#define IPInFCLRm_PAT      (0x808UL)
#define IPInREQm_PAT       (0x810UL)
#define IPInRCLRm_PAT      (0x814UL)

typedef enum { IPInEN, IPInFLG, IPInFCLR, IPInREQ, IPInRCLR } ipir_reg_t;

static const unsigned long ipir_reg_self_pat[] = { IPInENS_PAT, IPInFLGS_PAT, IPInFCLRS_PAT,
    IPInREQS_PAT, IPInRCLRS_PAT };

static const unsigned long ipir_reg_pem_pat[] = { IPInENm_PAT, IPInFLGm_PAT, IPInFCLRm_PAT,
    IPInREQm_PAT, IPInRCLRm_PAT };

volatile struct ipir_hw* ipir;
static bool ipir_ready = false;

extern irqid_t interrupts_ipi_id;

static bool decode_ipir_chann(size_t* chann, size_t reg_idx, size_t offset, bool self)
{
    bool ret = false;

    if (self) {
        size_t delta = offset - ipir_reg_self_pat[reg_idx];
        if (delta % 0x20 == 0) {
            *chann = delta / 0x20;
            ret = true;
        }
    } else {
        size_t delta = offset - ipir_reg_pem_pat[reg_idx];
        size_t rem = delta % 0x100;
        if (rem % 0x20 == 0) {
            *chann = rem / 0x20;
            ret = true;
        }
    }
    return ret;
}

void ipir_handle(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    /* Clear IPI */
    uint8_t src_cpu_idx = ipir->self[IPI_HYP_IRQ_ID].IPInFLG;
    ipir->self[IPI_HYP_IRQ_ID].IPInFCLR = src_cpu_idx;

    cpu_msg_handler();
}

void ipir_send_ipi(cpuid_t cpu_target)
{
    if (ipir_ready) {
        ipir->self[IPI_HYP_IRQ_ID].IPInREQ = (uint8_t)(1U << cpu_target);
    }
}

void ipir_init(void)
{
    if (cpu_is_master()) {
        vaddr_t ipir_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.arch.ipir_addr, NUM_PAGES(sizeof(struct ipir_hw)));
        if (ipir_ptr == INVALID_VA) {
            ERROR("Mapping IPIR failed");
        }
        ipir = (struct ipir_hw*)ipir_ptr;

        interrupts_ipi_id = interrupts_reserve(IPI_HYP_IRQ_ID, ipir_handle);
        if (interrupts_ipi_id == INVALID_IRQID) {
            ERROR("Failed to reserve IPIR interrupt");
        }

        ipir_ready = true;
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    ipir->self[IPI_HYP_IRQ_ID].IPInEN = ((1 << PLAT_CPU_NUM) - 1);
}

bool vipir_emul_handler(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;

    size_t acc_offset = acc->addr - platform.arch.ipir_addr;
    uint8_t bitop_mask = 0;
    cpuid_t pe_idx = 0;
    size_t chann_idx = 0;
    volatile uint8_t* tgt_reg = NULL;
    bool self = false;
    bool ignore = false;

    size_t ipir_self_bot = offsetof(struct ipir_hw, self);
    size_t ipir_self_top = sizeof(((struct ipir_hw*)NULL)->self) + ipir_self_bot;
    size_t ipir_pe_bot = offsetof(struct ipir_hw, pe);
    size_t ipir_pe_top = sizeof(((struct ipir_hw*)NULL)->pe) + ipir_pe_bot;

    /* Determine whether the access was made to the self region or to a PEm region */
    if (acc_offset >= ipir_self_bot && acc_offset < ipir_self_top) {
        /* If the access was made to a self register, redirect
            the access to the corresponding PEm register of the CPU */
        pe_idx = vcpu->phys_id;
        self = true;
    } else if (acc_offset >= ipir_pe_bot && acc_offset < ipir_pe_top) {
        /* If the access was made to a PEm register, check whether the CPU
            corresponding to the target register belongs to the VM */
        pe_idx = (acc_offset - ipir_pe_bot) >> 8;
        if (!(vm->cpus & (1UL << pe_idx))) {
            ignore = true;
        }
    } else {
        ignore = true;
    }

    /* Determine target IPIR register */
    switch (acc->addr & IPIR_REGS_PAT_MASK) {
        case IPInENS_PAT:
            ignore = !decode_ipir_chann(&chann_idx, IPInEN, acc_offset, self);
            tgt_reg = &(ipir->pe[pe_idx].chann[chann_idx].IPInEN);
            break;
        case IPInFLGS_PAT:
            ignore = !decode_ipir_chann(&chann_idx, IPInFLG, acc_offset, self);
            tgt_reg = &(ipir->pe[pe_idx].chann[chann_idx].IPInFLG);
            break;
        case IPInFCLRS_PAT:
            ignore = !decode_ipir_chann(&chann_idx, IPInFCLR, acc_offset, self);
            tgt_reg = &(ipir->pe[pe_idx].chann[chann_idx].IPInFCLR);
            break;
        case IPInREQS_PAT:
            ignore = !decode_ipir_chann(&chann_idx, IPInREQ, acc_offset, self);
            tgt_reg = &(ipir->pe[pe_idx].chann[chann_idx].IPInREQ);
            break;
        case IPInRCLRS_PAT:
            ignore = !decode_ipir_chann(&chann_idx, IPInRCLR, acc_offset, self);
            tgt_reg = &(ipir->pe[pe_idx].chann[chann_idx].IPInRCLR);
            break;
        default:
            ignore = true;
            break;
    }

    if (chann_idx == IPI_HYP_IRQ_ID) {
        ignore = true;
    }

    /* Ignore access */
    if (ignore) {
        if (!acc->write && acc->arch.op == NO_OP) {
            vcpu_writereg(vcpu, acc->reg, 0);
        }
        return true;
    }

    /* Translate access */
    if (acc->arch.op != NO_OP) {
        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            if ((1U << i) & acc->arch.byte_mask) {
                size_t phys_id = vm->vcpus[i].phys_id;
                bitop_mask = (uint8_t)(1U << phys_id);
                break;
            }
        }

        unsigned long psw = get_gmpsw();
        if (*tgt_reg & bitop_mask) {
            set_gmpsw(psw & ~PSW_Z);
        } else {
            set_gmpsw(psw | PSW_Z);
        }

        switch (acc->arch.op) {
            case SET1:
                *tgt_reg |= bitop_mask;
                break;
            case NOT1:
                *tgt_reg = (uint8_t)((*tgt_reg & bitop_mask) ? (*tgt_reg & ~bitop_mask) :
                                                               (*tgt_reg | bitop_mask));
                break;
            case CLR1:
                *tgt_reg &= (uint8_t)(~bitop_mask);
                break;
            /* TST1 only modifies the PSW.Z flag */
            default:
                break;
        }
    } else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        unsigned long write_val = 0;
        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            size_t virt_id = vm->vcpus[i].id;
            size_t phys_id = vm->vcpus[i].phys_id;
            if (phys_id >= virt_id) {
                write_val |= ((val & (1UL << virt_id)) << (phys_id - virt_id));
            } else {
                write_val |= ((val & (1UL << virt_id)) >> (virt_id - phys_id));
            }
        }
        *tgt_reg = (uint8_t)((*tgt_reg & ~vm->cpus) | (write_val & vm->cpus));
    } else {
        unsigned long val = *tgt_reg;
        unsigned long read_val = 0;
        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            size_t virt_id = vm->vcpus[i].id;
            size_t phys_id = vm->vcpus[i].phys_id;
            if (phys_id >= virt_id) {
                read_val |= (val & (1UL << phys_id)) >> (phys_id - virt_id);
            } else {
                read_val |= (val & (1UL << phys_id)) << (virt_id - phys_id);
            }
        }
        vcpu_writereg(vcpu, acc->reg, read_val);
    }
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

        // TODO: Add spinlock for IPIR emulation?
    }

    /* Reserve IPIR channels not used by the hypervisor */
    for (size_t i = 0; i < IPIR_NUM_CHANNELS; i++) {
        if (i != IPI_HYP_IRQ_ID) {
            if (!interrupts_vm_assign(vm, i)) {
                ERROR("Failed to reserve VM IPIR channel interrupt");
            }
        }
    }
}
