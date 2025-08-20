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

typedef void (*trap_handler_t)(unsigned long, unsigned long);

static void bpe_dae_handler(unsigned long datr, unsigned long deadd)
{
    UNUSED_ARG(deadd);
    if (!(datr & DATR_SBE_BIT)) {
        ERROR("Not a store.");
    }
}

static void bpe_pse_handler(unsigned long datr, unsigned long deadd)
{
    /* This is a synchronous trap, the inputs will be different */
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}
static void bpe_dse_handler(unsigned long datr, unsigned long deadd)
{
    /* This is a synchronous trap, the inputs will be different */
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}
static void bpe_cae_handler(unsigned long datr, unsigned long deadd)
{
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}
static void bpe_pie_handler(unsigned long datr, unsigned long deadd)
{
    /* This is a synchronous trap, the inputs will be different */
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}
static void bpe_die_handler(unsigned long datr, unsigned long deadd)
{
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}
static void bpe_tae_handler(unsigned long datr, unsigned long deadd)
{
    UNUSED_ARG(datr);
    UNUSED_ARG(deadd);
    return;
}

trap_handler_t bus_periph_error_handlers[8] = { [TIN_BPE_PSE] = bpe_pse_handler,
    [TIN_BPE_DSE] = bpe_dse_handler,
    [TIN_BPE_DAE] = bpe_dae_handler,
    [TIN_BPE_CAE] = bpe_cae_handler,
    [TIN_BPE_PIE] = bpe_pie_handler,
    [TIN_BPE_DIE] = bpe_die_handler,
    [TIN_BPE_TAE] = bpe_tae_handler };

void sys_bus_errors_handler(void)
{
    unsigned long vmid = cpu()->vcpu->vm->id;

    fence_sync();

    unsigned long access_addr = csfr_deadd_read();

    unsigned long ret = 0;

    for (unsigned long i = 0; i < config.vmlist[vmid].platform.dev_num; i++) {
        unsigned long dev_addr = config.vmlist[vmid].platform.devs[i].pa;

        if (dev_addr == access_addr) {
            ret = 1;
        }
    }

    if (!ret) {
        ERROR("vm accesing a device it doesn't own or trying to acccess a PROT/APU/CLC register");
    }
}

/* We assume that D regs are (16+reg_num)*/
static bool decode_16b_access(unsigned long ins, struct emul_access* emul)
{
    unsigned long opcode = bit32_extract(ins, 0, 8);
    bool ret = false;

    switch (opcode) {
        case 0xD8:
        case 0xCC:
        /* LD.A */
        case 0xF8:
        case 0xEC:
            /* ST.A */
            emul->reg = 15;
            emul->reg_width = 4;
            ret = true;
            break;

        case 0xC4:
        case 0xD4:
        case 0xC8:
        /* LD.A */
        case 0xE4:
        case 0xF4:
        case 0xE8:
            /* ST.A */
            emul->reg = bit32_extract(ins, 8, 4);
            emul->reg_width = 4;
            ret = true;
            break;

        case 0x0C:
        /* LD.BU */
        case 0x2C:
            /* ST.B */
            emul->reg = 15 + 16;
            emul->reg_width = 1;
            break;

        case 0x04:
        case 0x14:
        case 0x08:
        /* LD.BU */
        case 0x24:
        case 0x34:
        case 0x28:
            /* ST.B */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 1;
            ret = true;
            break;

        case 0x8C:
        /* LD.H */
        case 0xAC:
            /* ST.H */
            emul->reg_width = 2;
            ret = true;
            break;
        case 0x84:
        case 0x94:
        case 0x88:
        /* LD.H */
        case 0xA4:
        case 0xB4:
        case 0xA8:
            /* ST.H */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 2;
            ret = true;
            break;

        case 0x58:
        case 0x4C:
        /* LD.W */
        case 0x78:
        case 0x6C:
            /* ST.W */
            emul->reg = 15 + 16;
            emul->reg_width = 4;
            ret = true;
            break;

        case 0x44:
        case 0x54:
        case 0x48:
        /* LD.W */
        case 0x64:
        case 0x74:
        case 0x68:
            /* ST.W */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 4;
            ret = true;
            break;
        default:
            break;
    }
    return ret;
}

static bool decode_32b_access(unsigned long ins, struct emul_access* emul)
{
    bool ret = 0;
    unsigned long opcode = bit32_extract(ins, 0, 8);
    /* The first sub_opcode is 6 bits, but only the least significant 4
    are used to identify which instruction. The other two are used to identify
    the addressing mode. */
    unsigned long sub_opc = bit32_extract(ins, 22, 4);
    unsigned long sub_opc2 = bit32_extract(ins, 26, 2);

    switch (opcode) {
        case 0x85:
            /* LD.A / LD.W / LD.D / LD.DA */
        case 0xA5:
            /* ST.A / ST.W / ST.D / ST.DA */
            emul->reg = ((sub_opc2 > 1) ? bit32_extract(ins, 8, 4) : bit32_extract(ins, 8, 4) + 16);
            emul->reg_width = (sub_opc2 % 2 == 0 ? 4 : 8);
            ret = true;
            break;

        case 0x09:
        case 0x29:
        /*              LSB(sub_opc)
            LD.B    =       0x0      D 1
            LD.BU   =       0x1      D 1
            LD.H    =       0x2      D 2
            LD.HU   =       0x3      D 2
            LD.W    =       0x4      D 4
            LD.D    =       0x5      D 8
            LD.A    =       0x6      A 4
            LD.DA   =       0x7      A 8
            LD.Q    =       0x8      D 2
            LD.DD   =       0x9      D 16

        */
        case 0xA9:
        case 0x89:
            /*              LSB(sub_opc)
                ST.B    =       0x0      D 1
                ST.H    =       0x2      D 2
                ST.W    =       0x4      D 4
                ST.D    =       0x5      D 8
                ST.A    =       0x6      A 4
                ST.DA   =       0x7      A 8
                ST.Q    =       0x8      D 2
                ST.DD   =       0x9      D 16
            */
            emul->reg = ((sub_opc == 0x6 || sub_opc == 0x7) ? bit32_extract(ins, 8, 4) :
                                                              bit32_extract(ins, 8, 4) + 16);
            emul->reg_width = (sub_opc == 0x0)     ? 1 :
                (sub_opc == 0x9)                   ? 16 :
                (sub_opc == 0x2 || sub_opc == 0x8) ? 2 :
                (sub_opc == 0x4 || sub_opc == 0x6) ? 4 :
                                                     8;
            ret = true;
            break;
        case 0xB5:
            /* ST.A */
        case 0x99:
            /* LD.A */
            emul->reg = bit32_extract(ins, 8, 4);
            emul->reg_width = 4;
            ret = true;
            break;

        case 0x25:
            /* ST.B / ST.H */
        case 0x05:
            /* LD.B / LD.H / LD.BU / LD.HU */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = (sub_opc2 < 2) ? 1 : 2;
            ret = true;
            break;

        case 0xE9:
            /* ST.B */
        case 0x79:
        case 0x39:
            /* LD.B / LD.BU */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 1;
            ret = true;
            break;

        case 0xF9:
            /* ST.H */
        case 0xB9:
        case 0xC9:
            /* LD.H / LD.HU */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 2;
            ret = true;
            break;

        case 0x59:
            /* ST.W */
        case 0x19:
            /* LD.W */
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 4;
            ret = true;
            break;

        case 0x65:
            /* ST.Q */
        case 0x45:
            /* LD.Q */
            /* TODO: Verify*/
            emul->reg = bit32_extract(ins, 8, 4) + 16;
            emul->reg_width = 2;
            ret = true;
            break;

        case 0xD5:
            /* ST.T */
            /* Store bit, how to deal with it? */
            break;

        default:
            break;
    }

    return ret;
}

static bool decode_cfr_access(unsigned long ins, struct emul_access* emul)
{
    unsigned long opcode = bit32_extract(ins, 0, 8);
    bool ret = false;

    switch (opcode) {
        case 0x4D:
            /* MFCR */
            emul->write = false;
            emul->reg = bit32_extract(ins, 28, 31) + 16;
            emul->reg_width = 4;
            break;

        case 0x4F:
            /* MFDCR*/
            emul->write = false;
            emul->reg = bit32_extract(ins, 28, 31) + 16;
            emul->reg_width = 8;
            break;

        case 0xCD:
            /* MTCR */
            emul->write = true;
            emul->reg = bit32_extract(ins, 28, 31) + 16;
            emul->reg_width = 4;
            break;

        case 0xCF:
            /* MTDCR*/
            emul->write = true;
            emul->reg = bit32_extract(ins, 28, 31) + 16;
            emul->reg_width = 8;
            break;

        default:
            break;
    }
    return ret;
}

void l2_dmem_prot_trap_handler(unsigned long* addr, unsigned long access)
{
    struct emul_access emul;
    /* Give bao the same read permissions on the mpu */
    /* We save the bao prs bitmap, and we OR it with the guest prs */
    volatile unsigned long hyp_d_r_entries = csfr_dpre_0_read();
    unsigned long vmid = cpu()->vcpu->vm->id;

    volatile unsigned long vm_d_r_entries = get_dpre(vmid + 1);

    volatile unsigned long perms = hyp_d_r_entries | vm_d_r_entries;
    set_dpre(0, perms);

    fence_sync();

    unsigned long ins = *(unsigned long*)addr;

    unsigned long opcode = bit32_extract(ins, 0, 8);

    volatile bool reg = 0;

    unsigned long access_addr = csfr_deadd_read();

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, access_addr);

    if (handler != NULL) {
        // Only adjust the return addr if there is an emul_handler.
        if (opcode % 2 == 0) {
            reg = decode_16b_access(ins, &emul);
            cpu()->vcpu->regs.lower_ctx.a11 += 2;
        } else {
            reg = decode_32b_access(ins, &emul);
            cpu()->vcpu->regs.lower_ctx.a11 += 4;
        }

        if (reg == false) {
            return;
        }

        emul.addr = access_addr;
        emul.width = emul.reg_width;
        emul.write = (access) ? true : false;
        emul.sign_ext = false;

        handler(&emul);
    }

    set_dpre(0, hyp_d_r_entries);
}

void hvcall_handler(unsigned long function_id, unsigned long dev_id, unsigned long event_id)
{
    UNUSED_ARG(dev_id);
    UNUSED_ARG(event_id);

    if ((function_id & 0xFFFF0000) == 0xDEAD0000) {
        hypercall(function_id & 0x3);
    }
}

static void csfr_emul_handler(struct emul_access* emul, unsigned long csfr)
{
    UNUSED_ARG(emul);
    switch (csfr) {
        default:
            break;
    }
    return;
}

void hyp_csfr_access_handler(unsigned long* addr, unsigned long hvtin)
{
    struct emul_access emul;
    /* Give bao the same read permissions on the mpu */
    /* We save the bao prs bitmap, and we OR it with the guest prs */
    volatile unsigned long hyp_d_r_entries = csfr_dpre_0_read();
    unsigned long vmid = cpu()->vcpu->vm->id;

    volatile unsigned long vm_d_r_entries = get_dpre(vmid + 1);

    volatile unsigned long perms = hyp_d_r_entries | vm_d_r_entries;
    set_dpre(0, perms);

    fence_sync();

    unsigned long ins = *(unsigned long*)addr;

    decode_cfr_access(ins, &emul);

    csfr_emul_handler(&emul, (hvtin & 0xFFFF));

    cpu()->vcpu->regs.lower_ctx.a11 += 4;

    set_dpre(0, hyp_d_r_entries);
}
