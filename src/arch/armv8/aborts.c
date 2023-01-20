/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aborts.h>
#include <arch/sysregs.h>
#include <arch/smcc.h>
#include <cpu.h>
#include <vm.h>
#include <emul.h>
#include <config.h>
#include <hypercall.h>

typedef void (*abort_handler_t)(unsigned long, unsigned long, unsigned long, unsigned long);

void aborts_data_lower(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    if (!(iss & ESR_ISS_DA_ISV_BIT) || (iss & ESR_ISS_DA_FnV_BIT)) {
        ERROR("no information to handle data abort (0x%x)", far);
    }

    unsigned long DSFC =
        bit64_extract(iss, ESR_ISS_DA_DSFC_OFF, ESR_ISS_DA_DSFC_LEN) & (0xf << 2);

    if (DSFC != ESR_ISS_DA_DSFC_TRNSLT && DSFC != ESR_ISS_DA_DSFC_PERMIS) {
        ERROR("data abort is not translation fault - cant deal with it");
    }

    vaddr_t addr = far;
    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        struct emul_access emul;
        emul.addr = addr;
        emul.width =
            (1 << bit64_extract(iss, ESR_ISS_DA_SAS_OFF, ESR_ISS_DA_SAS_LEN));
        emul.write = iss & ESR_ISS_DA_WnR_BIT ? true : false;
        emul.reg = bit64_extract(iss, ESR_ISS_DA_SRT_OFF, ESR_ISS_DA_SRT_LEN);
        emul.reg_width =
            4 + (4 * bit64_extract(iss, ESR_ISS_DA_SF_OFF, ESR_ISS_DA_SF_LEN));
        emul.sign_ext =
            bit64_extract(iss, ESR_ISS_DA_SSE_OFF, ESR_ISS_DA_SSE_LEN);

        // TODO: check if the access is aligned. If not, inject an exception in
        // the vm

        if (handler(&emul)) {
            unsigned long pc_step = 2 + (2 * il);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("data abort emulation failed (0x%x)", far);
        }
    } else {
        ERROR("no emulation handler for abort(0x%x at 0x%x)", far,
              vcpu_readpc(cpu()->vcpu));
    }
}

long int standard_service_call(unsigned long _fn_num) {

    int64_t ret = -1;

    unsigned long smc_fid = vcpu_readreg(cpu()->vcpu, 0);
    unsigned long x1 = vcpu_readreg(cpu()->vcpu, 1);
    unsigned long x2 = vcpu_readreg(cpu()->vcpu, 2);
    unsigned long x3 = vcpu_readreg(cpu()->vcpu, 3);

    if (is_psci_fid(smc_fid)) {
        ret = psci_smc_handler(smc_fid, x1, x2, x3);
    } else {
        INFO("unknown smc_fid 0x%lx", smc_fid);
    }

    return ret;
}

static inline void syscall_handler(unsigned long iss, unsigned long far,
    unsigned long il, unsigned long ec)
{
    unsigned long fid = vcpu_readreg(cpu()->vcpu, 0);

    long ret = SMCC_E_NOT_SUPPORTED;
    switch(fid & ~SMCC_FID_FN_NUM_MSK) {
        case SMCC32_FID_STD_SRVC:
        case SMCC64_FID_STD_SRVC:
            ret = standard_service_call(fid);
            break;
        case SMCC32_FID_VND_HYP_SRVC:
        case SMCC64_FID_VND_HYP_SRVC:
            ret = hypercall(fid & SMCC_FID_FN_NUM_MSK);
            break;
        default:
            WARNING("Unknown system call fid 0x%x", fid);
    }

    vcpu_writereg(cpu()->vcpu, 0, ret);
}

void hvc_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    syscall_handler(iss, far, il, ec);
}

void smc_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    syscall_handler(iss, far, il, ec);

    /**
     * Since SMCs are trapped due to setting hcr_el2.tsc, the "preferred
     * exception return address" is the address of the actual smc instruction.
     * Thus, we need to adjust it to the next instruction.
     */
    vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 4);
}

static regaddr_t reg_addr_translate(unsigned long iss)
{
    iss &= ESR_ISS_SYSREG_ADDR_64;
    if (iss == ICC_SGI1R_CASE) {
        return (regaddr_t) ICC_SGI1R_ADDR;
    } else {
        return (regaddr_t) UNDEFINED_REG_ADDR;
    }
}

void sysreg_handler(unsigned long iss, unsigned long far, unsigned long il, unsigned long ec)
{
    regaddr_t reg_addr = UNDEFINED_REG_ADDR;
    if (ec == ESR_EC_RG_64) {
        reg_addr = reg_addr_translate(iss);
    } else {
        reg_addr = (iss & ESR_ISS_SYSREG_ADDR_32) | OP0_MRS_CP15;
    }

    emul_handler_t handler = vm_emul_get_reg(cpu()->vcpu->vm, reg_addr);
    if(handler != NULL){
        struct emul_access emul;
        emul.addr = reg_addr;
        emul.width = 8;
        emul.write = iss & ESR_ISS_SYSREG_DIR ? false : true;
        emul.reg = bit64_extract(iss, ESR_ISS_SYSREG_REG_OFF, ESR_ISS_SYSREG_REG_LEN);
        emul.reg_high = bit64_extract(iss, ESR_ISS_SYSREG_REG2_OFF, ESR_ISS_SYSREG_REG2_LEN);
        emul.reg_width = 8;
        emul.multi_reg = (ec == ESR_EC_RG_64)? true : false;
        emul.sign_ext = false;

        if (handler(&emul)) {
            unsigned long pc_step = 2 + (2 * il);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("register access emulation failed (0x%x)", reg_addr);
        }
    } else {
        ERROR("no emulation handler for register access (0x%x at 0x%x)", reg_addr,
              vcpu_readpc(cpu()->vcpu));
    }
}

abort_handler_t abort_handlers[64] = {[ESR_EC_DALEL] = aborts_data_lower,
                                      [ESR_EC_SMC32] = smc_handler,
                                      [ESR_EC_SMC64] = smc_handler,
                                      [ESR_EC_SYSRG] = sysreg_handler,
                                      [ESR_EC_RG_32] = sysreg_handler,
                                      [ESR_EC_RG_64] = sysreg_handler,
                                      [ESR_EC_HVC32] = hvc_handler,
                                      [ESR_EC_HVC64] = hvc_handler,};

void aborts_sync_handler()
{
    unsigned long esr = sysreg_esr_el2_read();
    unsigned long far = sysreg_far_el2_read();
    unsigned long hpfar = sysreg_hpfar_el2_read();
    unsigned long ipa_fault_addr = 0;

    if (DEFINED(MEM_PROT_MMU) || cpu()->vcpu->vm->config->platform.mmu) {
        ipa_fault_addr = (far & 0xFFF) | (hpfar << 8);
    } else {
        ipa_fault_addr = far;
    }

    unsigned long ec = bit64_extract(esr, ESR_EC_OFF, ESR_EC_LEN);
    unsigned long il = bit64_extract(esr, ESR_IL_OFF, ESR_IL_LEN);
    unsigned long iss = bit64_extract(esr, ESR_ISS_OFF, ESR_ISS_LEN);

    abort_handler_t handler = abort_handlers[ec];
    if (handler)
        handler(iss, ipa_fault_addr, il, ec);
    else
        ERROR("no handler for abort ec = 0x%x", ec);  // unknown guest exception
}
