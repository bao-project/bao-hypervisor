/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <interrupts.h>
#include <arch/ir.h>
#include <arch/vir.h>
#include <string.h>
#include <config.h>
#include <platform.h>
#include <arch/csa.h>

#define NOT_IN_CSA (-1)

/* We assume that D regs are (16+reg_num) */
static const long int a_lut[CSA_SIZE] = { NOT_IN_CSA, NOT_IN_CSA, 2, 3, 8, 9, 10, 11, NOT_IN_CSA,
    NOT_IN_CSA, 2, 3, 8, 9, 10, 11 };
static const long int d_lut[CSA_SIZE] = { 4, 5, 6, 7, 12, 13, 14, 15, 4, 5, 6, 7, 12, 13, 14, 15 };

static void vm_ipi_init(struct vm* vm, const struct vm_config* vm_config)
{
    // Return if there are no groups to be assigned
    if (vm_config->platform.arch.gpsr_num == 0) {
        return;
    }

    for (unsigned long int i = 0; i < vm_config->platform.arch.gpsr_num; i++) {
        unsigned long group = (unsigned long)vm_config->platform.arch.gpsr_groups[i];
        if (group == 0) {
            ERROR("GPSR group 0 is reserved for Bao internal use.");
        }
        // We need to clear the group 1st because it allows access to everyone by default
        ir_clear_gpsr_group(group);
        ir_init_gpsr_group(group, vm);

        unsigned long gpsr_src_node = GPSR_SRC_BASE + (GPSR_MAX_NODES * (group));
        for (unsigned long int node = gpsr_src_node; node < gpsr_src_node + GPSR_MAX_NODES;
             node++) { // interrupt assign all src nodes from each group
            interrupts_vm_assign(vm, (irqid_t)node);
        }
    }
}

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    if (vm->master == cpu()->id) {
        vir_init(vm);
        vm_ipi_init(vm, vm_config);
    }
    cpu_sync_and_clear_msgs(&vm->sync);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    unsigned long pcxo =
        bit32_extract((uint32_t) & (vcpu->regs.upper_ctx), ADDR_PCXO_OFF, ADDR_PCXO_LEN);
    unsigned long pcxs =
        bit32_extract((uint32_t) & (vcpu->regs.upper_ctx), ADDR_PCXS_OFF, ADDR_PCXS_LEN);

    vcpu->regs.lower_ctx.pcxi =
        (1 << PCXI_PIE_OFF) | (1 << PCXI_UL_OFF) | (pcxs << PCXI_PCXS_OFF) | pcxo;
    vcpu->regs.lower_ctx.a11 = vm->config->entry;

    vcpu->regs.upper_ctx.csa_psw = PSW_IO_SUPERVISOR << PSW_IO_OFF;

    vir_vcpu_init(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    vcpu->regs.lower_ctx.a11 = entry;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    bool a_reg = (reg < 15) ? true : false;
    unsigned long reg_num = a_reg ? reg : reg - CSA_SIZE;

    if (reg > 32 || reg_num > CSA_SIZE) {
        ERROR("Trying to access out-of-bound registers.");
    }

    unsigned long ret = 0;

    if (a_reg && a_lut[reg_num] == NOT_IN_CSA) {
        switch (reg_num) {
            case 0:
                ret = vcpu->regs.a0;
                break;

            case 1:
                ret = vcpu->regs.a1;
                break;

            case 8:
                ret = vcpu->regs.a8;
                break;

            case 9:
                ret = vcpu->regs.a9;
                break;
            default:
                break;
        }
    } else {
        if (reg_num < 8) {
            ret = (a_reg) ? vcpu->regs.lower_array[a_lut[reg_num]] :
                            vcpu->regs.lower_array[d_lut[reg_num]];
        } else {
            ret = (a_reg) ? vcpu->regs.upper_array[a_lut[reg_num]] :
                            vcpu->regs.upper_array[d_lut[reg_num]];
        }
    }

    return ret;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    bool a_reg = (reg < 15) ? true : false;
    unsigned long reg_num = a_reg ? reg : reg - CSA_SIZE;

    if (reg > 32 || reg_num > CSA_SIZE) {
        ERROR("Trying to access out-of-bound registers.");
    }

    if (a_reg && a_lut[reg_num] == NOT_IN_CSA) {
        switch (reg_num) {
            case 0:
                vcpu->regs.a0 = val;
                break;

            case 1:
                vcpu->regs.a1 = val;
                break;

            case 8:
                vcpu->regs.a8 = val;
                break;

            case 9:
                vcpu->regs.a9 = val;
                break;
            default:
                break;
        }
    } else {
        if (reg_num < 8) {
            if (a_reg) {
                vcpu->regs.lower_array[a_lut[reg_num]] = val;
            } else {
                vcpu->regs.lower_array[d_lut[reg_num]] = val;
            }
        } else {
            if (a_reg) {
                vcpu->regs.upper_array[a_lut[reg_num]] = val;
            } else {
                vcpu->regs.upper_array[d_lut[reg_num]] = val;
            }
        }
    }
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.lower_ctx.a11;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.lower_ctx.a11 = pc;
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    return true;
}

static const struct plat_device* vm_find_platform_device(struct vm_dev_region* dev)
{
    const struct plat_device* ret = NULL;

    for (unsigned long i = 0; i < platform.arch.device_num; i++) {
        const struct plat_device* pdev = &platform.arch.devices[i];
        if (dev->pa == pdev->dev_base) {
            ret = pdev;
            break;
        }
    }
    return ret;
}

void vm_arch_allow_mmio_access(struct vm* vm, struct vm_dev_region* dev)
{
    const struct plat_device* pdev = vm_find_platform_device(dev);

    if (pdev == NULL) {
        ERROR("Device 0x%x not found", dev->pa);
    }

    for (unsigned long apu = 0; apu < pdev->apu_num; apu++) {
        apu_enable_access_vm((struct PROT_ACCESSEN*)(pdev->dev_base + pdev->apu_offset[apu]),
            vm->as.id);
        for (unsigned long cpu = 0; cpu < platform.cpu_num; cpu++) {
            if (vm->cpus & (1UL << cpu)) {
                apu_enable_access_cpu((struct PROT_ACCESSEN*)(pdev->dev_base +
                                          pdev->apu_offset[apu]),
                    cpu);
            }
        }
    }
    for (unsigned long j = 0; j < pdev->prot_num; j++) {
        prot_write((volatile prottos_t*)(pdev->dev_base + pdev->prot_offset[j]), vm->master,
            VMID_TO_HWVM(vm->id), PROT_STATE_RUN);
    }
}
