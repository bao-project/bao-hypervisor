/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <config.h>
#include <string.h>
#include <vm.h>
#include <ipir.h>
#include <vintc.h>

void vm_arch_init(struct vm* vm, const struct vm_config* vm_config)
{
    UNUSED_ARG(vm_config);

    /* All VMs use MPID5 for memory protection */
    set_mpid5(vm->id);

    vintc_init(vm);
    vipir_init(vm);
    vbootctrl_init(vm);
}

void vcpu_arch_init(struct vcpu* vcpu, struct vm* vm)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(vcpu);
}

void vcpu_arch_reset(struct vcpu* vcpu, vaddr_t entry)
{
    struct vm* vm = vcpu->vm;

    memset(&vcpu->regs, 0, sizeof(struct arch_regs));

    vcpu_writepc(vcpu, entry);
    set_eipc(entry);

    vcpu->arch.started = vcpu->id == 0 ? true : false;

    /* Bao fixes the VMID as SPID to isolate VM memory regions */
    vcpu->regs.spid = vm->id;
    set_gmspid(vm->id);
    set_gmspidlist(0x0);

    set_gmmpm(GMMPM_GMPE);

    unsigned long eipswh = get_eipswh() & ~EIPSWH_GPID_MASK;
    set_eipswh(eipswh | (vm->id << EIPSWH_GPID_OFF));

    unsigned long fepswh = get_fepswh() & ~FEPSWH_GPID_MASK;
    set_fepswh(fepswh | (vm->id << FEPSWH_GPID_OFF));

    set_gmpeid(vcpu->id);

    /* clear guest-context exception registers */
    set_gmeipc(0x0);
    set_gmfepc(0x0);
    set_gmmea(0x0);
    set_gmmei(0x0);
    set_gmeiic(0x0);
    set_gmfeic(0x0);

    vintc_vcpu_reset(vcpu);
}

bool vcpu_arch_is_on(struct vcpu* vcpu)
{
    return vcpu->arch.started;
}

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    if (reg > 32) {
        ERROR("reading register out of bounds");
    }

    return vcpu->regs.gp_regs.r[reg];
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{
    if (reg > 32) {
        ERROR("writing register out of bounds");
    }

    vcpu->regs.gp_regs.r[reg] = val;
}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return vcpu->regs.pc;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long val)
{
    vcpu->regs.pc = val;
}

void vcpu_restore_state(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    ERROR("%s not implemented", __func__);
}

void vcpu_save_state(struct vcpu* vcpu)
{
    UNUSED_ARG(vcpu);
    ERROR("%s not implemented", __func__);
}

bool vbootctrl_emul_handler(struct emul_access* acc)
{
    struct vcpu* vcpu = cpu()->vcpu;
    struct vm* vm = vcpu->vm;
    unsigned long notify = 0;

    /* Translate access */
    if (acc->arch.op != BWOP_NO) {
        /* this access is fairly unique, so it's not practical to put behind
         * arch emul */
        size_t virt_id = INVALID_CPUID;

        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            if ((1U << i) & acc->arch.byte_mask) {
                virt_id = vm->vcpus[i].id;
                if (!vm->vcpus[i].arch.started) {
                    notify |= (1UL << vm->vcpus[i].phys_id);
                }
                break;
            }
        }

        if (virt_id == INVALID_CPUID) {
            return true;
        }

        unsigned long psw = get_gmpsw();
        if (vm->vcpus[virt_id].arch.started) {
            set_gmpsw(psw & ~PSW_Z);
        } else {
            set_gmpsw(psw | PSW_Z);
        }

        switch (acc->arch.op) {
            case BWOP_SET1:
                vm->vcpus[virt_id].arch.started = true;
                break;
            case BWOP_NOT1:
                vm->vcpus[virt_id].arch.started = true;
                break;
            /* CLR1 accesses are ignored */
            /* TST1 only modifies the PSW.Z flag */
            default:
                break;
        }
    } else if (acc->write) {
        unsigned long val = vcpu_readreg(vcpu, acc->reg);
        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            if ((1U << i) & val) {
                if (!vm->vcpus[i].arch.started) {
                    notify |= 1UL << vm->vcpus[i].phys_id;
                }
                vm->vcpus[i].arch.started = true;
            }
        }
    } else {
        unsigned long val = 0;
        for (size_t i = 0; i < vcpu->vm->cpu_num; i++) {
            if (vm->vcpus[i].arch.started) {
                val |= 1UL << i;
            }
        }
        vcpu_writereg(vcpu, acc->reg, val);
    }

    /* Notify physical CPUs, if any */
    for (cpuid_t c = 0; c < platform.cpu_num; c++) {
        if (notify & (1UL << c)) {
            interrupts_cpu_sendipi(c);
        }
    }

    return true;
}

void vbootctrl_init(struct vm* vm)
{
    if (cpu()->id == vm->master) {
        vm->arch.bootctrl_emul = (struct emul_mem){
            .va_base = platform.arch.bootctrl_addr,
            .size = 0x10,
            .handler = vbootctrl_emul_handler,
        };
        vm_emul_add_mem(vm, &vm->arch.bootctrl_emul);
    }
}
