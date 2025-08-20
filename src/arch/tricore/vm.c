/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vm.h>
#include <arch/csfrs.h>
#include <interrupts.h>
#include <arch/ir.h>
#include <arch/vir.h>
#include <string.h>
#include <config.h>
#include <platform.h>

/* We assume that D regs are (16+reg_num) */
long int a_lut[16] = { -1, -1, 2, 3, 8, 9, 10, 11, -1, -1, 2, 3, 8, 9, 10, 11 };
long int d_lut[16] = { 4, 5, 6, 7, 12, 13, 14, 15, 4, 5, 6, 7, 12, 13, 14, 15 };

static void vm_ipi_init(struct vm* vm, const struct vm_config* vm_config)
{
    // Return if there are no groups to be assigned
    if (vm_config->platform.arch.gspr_num == 0) {
        return;
    }

    for (unsigned long int i = 0; i < vm_config->platform.arch.gspr_num; i++) {
        unsigned long group = (unsigned long)vm_config->platform.arch.gspr_groups[i];
        unsigned long gspr_src_node = GSPR_SRC_BASE + (8 * (group));
        if (group == 0) {
            ERROR("GSPR group 0 is reserved for Bao internal use.")
        }
        // We need to clear the group 1st because it allows access to everyone by default
        ir_clear_gspr_group(group);
        ir_init_gspr_group(group, vm);

        for (unsigned long int node = gspr_src_node; node < gspr_src_node + 8;
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
    unsigned long pcxo =
        bit32_extract((uint32_t) & (vcpu->regs.upper_ctx), ADDR_PCXO_OFF, ADDR_PCXO_LEN);
    unsigned long pcxs =
        bit32_extract((uint32_t) & (vcpu->regs.upper_ctx), ADDR_PCXS_OFF, ADDR_PCXS_LEN);

    vcpu->regs.lower_ctx.pcxi = (1 << 21) | (1 << PCXI_UL_OFF) | (pcxs << PCXI_PCXS_OFF) | pcxo;
    vcpu->regs.lower_ctx.a11 = vm->config->entry;
    vcpu->regs.lower_ctx.a2 = 0;
    vcpu->regs.lower_ctx.a3 = 0;
    vcpu->regs.lower_ctx.d0 = 0;
    vcpu->regs.lower_ctx.d1 = 0;
    vcpu->regs.lower_ctx.d2 = 0;
    vcpu->regs.lower_ctx.d3 = 0;
    vcpu->regs.lower_ctx.a4 = 0;
    vcpu->regs.lower_ctx.a5 = 0;
    vcpu->regs.lower_ctx.a6 = 0;
    vcpu->regs.lower_ctx.a7 = 0;
    vcpu->regs.lower_ctx.d4 = 0;
    vcpu->regs.lower_ctx.d5 = 0;
    vcpu->regs.lower_ctx.d6 = 0;
    vcpu->regs.lower_ctx.d7 = 0;

    vcpu->regs.upper_ctx.pcxi = 0;
    vcpu->regs.upper_ctx.csa_psw = 2 << 10;
    vcpu->regs.upper_ctx.a10 = 0;
    vcpu->regs.upper_ctx.a11 = 0;
    vcpu->regs.upper_ctx.d8 = 0;
    vcpu->regs.upper_ctx.d9 = 0;
    vcpu->regs.upper_ctx.d10 = 0;
    vcpu->regs.upper_ctx.d11 = 0;
    vcpu->regs.upper_ctx.a12 = 0;
    vcpu->regs.upper_ctx.a13 = 0;
    vcpu->regs.upper_ctx.a14 = 0;
    vcpu->regs.upper_ctx.a15 = 0;
    vcpu->regs.upper_ctx.d12 = 0;
    vcpu->regs.upper_ctx.d13 = 0;
    vcpu->regs.upper_ctx.d14 = 0;
    vcpu->regs.upper_ctx.d15 = 0;

    vcpu->regs.a0 = 0xFFFFFFFF;
    vcpu->regs.a8 = 0xFFFFFFFF;

    vir_vcpu_init(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    vcpu->regs.lower_ctx.a11 = entry;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    bool a_reg = (reg < 15) ? true : false;
    unsigned long reg_num = a_reg ? reg : reg - 16;
    if (reg_num < 8) {
        return (a_reg) ? vcpu->regs.lower_array[a_lut[reg_num]] :
                         vcpu->regs.lower_array[d_lut[reg_num]];
    } else {
        return (a_reg) ? vcpu->regs.upper_array[a_lut[reg_num]] :
                         vcpu->regs.upper_array[d_lut[reg_num]];
    }

    return 0;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    bool a_reg = (reg < 15) ? true : false;
    unsigned long reg_num = a_reg ? reg : reg - 16;
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

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.lower_ctx.a11;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{
    vcpu->regs.lower_ctx.a11 = pc;
}

void vcpu_arch_run(struct vcpu* vcpu)
{
    (void)vcpu;
    /* if (vcpu->arch.scr_ctx.state == STARTED) { */
    // TODO: All vms start running at "same" time?
    if (1) {
        vcpu_arch_entry();
    } /*else {
        cpu_idle();
    }*/
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    return true;
}

void vm_arch_allow_mmio_access(struct vm* vm, struct vm_dev_region* dev)
{
    for (unsigned long i = 0; i < platform.arch.device_num; i++) {
        struct plat_device pdev = platform.arch.devices[i];
        if (dev->pa == pdev.dev_base) {
            for (unsigned long apu = 0; apu < pdev.apu_num; apu++) {
                apu_enable_access_vm((struct PROT_ACCESSEN*)(pdev.apu_addr[apu] + pdev.dev_base),
                    vm->as.id);
                for (unsigned long cpu = 0; cpu < platform.cpu_num; cpu++) {
                    if (vm->cpus & (1UL << cpu)) {
                        apu_enable_access_cpu((struct PROT_ACCESSEN*)(pdev.apu_addr[apu] +
                                                  pdev.dev_base),
                            cpu);
                    }
                }
            }
            for (unsigned long j = 0; j < pdev.prot_num; j++) {
                prot_write((volatile prottos_t*)(pdev.prot_addr[j] + pdev.dev_base), vm->master,
                    vm->id, PROT_STATE_RUN);
            }
        }
    }
}
