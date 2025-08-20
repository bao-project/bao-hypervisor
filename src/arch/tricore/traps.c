/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <vm.h>
#include <emul.h>
#include <config.h>
#include <arch/traps.h>
#include <arch/csfrs.h>
#include <arch/fences.h>
#include <hypercall.h>
#include <arch/decode.h>

void sys_bus_errors_handler(void)
{
    /* this trap suppresses errors to the first address in a device region.
    This address is often the CLC register that is used to enable the peripheral.
    Since the access to this register is managed by the PROT mechanism, when
    the slave side mmio protection is enable, a guest trying to enable the device
    will always trap and we suppress the error.
    This is trade-off that covers a majority of devices in TC4 and allows for
    most BSPs to execute correctly. */
    unsigned long vmid = cpu()->vcpu->vm->id;

    unsigned long addr = csfr_deadd_read();

    unsigned long ret = 0;

    if (vmid >= config.vmlist_size) {
        ERROR("Trying to access config.vmlist out-of-bounds")
    }

    for (unsigned long i = 0; i < config.vmlist[vmid].platform.dev_num; i++) {
        unsigned long dev_addr = config.vmlist[vmid].platform.devs[i].pa;

        if (dev_addr == addr) {
            ret = 1;
            break;
        }
    }

    if (!ret) {
        ERROR("vm accesing a device it doesn't own or trying to acccess a PROT/APU/CLC register");
    }
}

void l2_dmem_prot_trap_handler(unsigned long* instr_addr, unsigned long is_write)
{
    struct emul_access emul;
    unsigned long addr = csfr_deadd_read();
    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);

    if (handler != NULL) {
        /* Give bao the same read permissions on the mpu */
        /* We save the bao prs bitmap, and we OR it with the guest prs */
        volatile unsigned long hyp_d_r_entries = csfr_dpre_0_read();
        unsigned long vmid = cpu()->vcpu->vm->id;
        volatile unsigned long vm_d_r_entries = get_dpre(VMID_TO_HWVM(vmid));
        volatile unsigned long perms = hyp_d_r_entries | vm_d_r_entries;

        /* We are changing the active entries in the PRS we are using. A fence
        is needed to ensure the upcoming accesses see the correct permissions. */
        set_dpre(HYP_VMID, perms);
        fence_sync();

        unsigned long ins = *(unsigned long*)instr_addr;
        unsigned long opcode = bit32_extract(ins, 0, 8);
        volatile bool reg = 0;

        if (opcode % 2 == 0) {
            reg = decode_16b_access(ins, &emul);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 2);
        } else {
            reg = decode_32b_access(ins, &emul);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 4);
        }

        set_dpre(HYP_VMID, hyp_d_r_entries);
        fence_sync();

        if (reg != false) {
            emul.addr = addr;
            emul.width = emul.reg_width;
            emul.write = !!is_write;
            emul.sign_ext = false;
            if (!handler(&emul)) {
                ERROR("register access emulation failed (0x%x)", addr);
            }
        }
    } else {
        ERROR("No emulation handler for access to 0x%x, at 0x%x", addr, vcpu_readpc(cpu()->vcpu));
    }
}

void hvcall_handler(unsigned long function_id)
{
    hypercall(function_id);
}

static bool csfr_pcon0_emul_handler(struct emul_access* acc)
{
    if (acc->write) {
        uint32_t val = vcpu_readreg(cpu()->vcpu, acc->reg);
        csfr_pcon0_write(val);
        fence_sync();
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, csfr_pcon0_read());
    }
    return true;
}

static bool csfr_dcon0_emul_handler(struct emul_access* acc)
{
    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, csfr_dcon0_read());
    } else {
        /* We don't allow guests to enable data cache as it would prevent
        coherency for the hypervisor. */
    }
    return true;
}

static bool csfr_emul_handler(struct emul_access* emul, unsigned long csfr)
{
    bool ret = false;
    switch (csfr) {
        case CSFR_PCON0:
            ret = csfr_pcon0_emul_handler(emul);
            break;
        case CSFR_DCON0:
            ret = csfr_dcon0_emul_handler(emul);
            break;
        default:
            WARNING("Emulation of csfr 0x%x is not yet implemented", csfr);
            break;
    }
    return ret;
}

void hyp_csfr_access_handler(unsigned long* instr_addr, unsigned long hvtin)
{
    UNUSED_ARG(hvtin);
    struct emul_access emul;
    unsigned long vmid = cpu()->vcpu->vm->id;

    /* Give bao the same read permissions on the mpu */
    /* We save the bao prs bitmap, and we OR it with the guest prs */
    volatile unsigned long hyp_d_r_entries = csfr_dpre_0_read();
    volatile unsigned long vm_d_r_entries = get_dpre(VMID_TO_HWVM(vmid));
    volatile unsigned long perms = hyp_d_r_entries | vm_d_r_entries;

    set_dpre(HYP_VMID, perms);
    fence_sync();

    unsigned long csfr = decode_cfr_access(*instr_addr, &emul);

    set_dpre(HYP_VMID, hyp_d_r_entries);
    fence_sync();

    if (!csfr_emul_handler(&emul, csfr)) {
        ERROR("CSFR emulation failed at 0x%x", instr_addr);
    }
    vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 4);
}
