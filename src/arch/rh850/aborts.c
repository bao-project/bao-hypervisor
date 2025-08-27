/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <hypercall.h>
#include <fences.h>
#include <vm.h>
#include <arch/aborts.h>
#include <arch/emul.h>
#include <arch/srs.h>

#define F8_OPCODE               (0x3EUL)
#define F9_OPCODE               (0x3FUL)
#define F9_SUBOPCODE            (0x1CUL)

#define OPCODE_SHIFT            (5)
#define OPCODE_MASK             (0x3FUL << OPCODE_SHIFT)

#define SUBOPCODE_SHIFT         (19)
#define SUBOPCODE_MASK          (0x1FFFUL << SUBOPCODE_SHIFT)

#define SUB8_SHIFT              (14)
#define SUB8_MASK               (0x3UL << SUB8_SHIFT)

#define SUB9_SHIFT              (17)
#define SUB9_MASK               (0x3UL << SUB9_SHIFT)

#define BITIDX_SHIFT            (11)
#define BITIDX_MASK             (0x7UL << BITIDX_SHIFT)

#define REGIDX_SHIFT            (11)
#define REGIDX_MASK             (0x1FUL << REGIDX_SHIFT)

// LEN (Bits 31-28)
#define MEI_LEN_MASK          (0xFUL << 28)
#define MEI_LEN_SHIFT         28
#define MEI_GET_LEN(val)      (((val) & MEI_LEN_MASK) >> MEI_LEN_SHIFT)

// REG (Bits 20-16)
#define MEI_REG_MASK          (0x1F << 16)
#define MEI_REG_SHIFT         16
#define MEI_GET_REG(val)      (((val) & MEI_REG_MASK) >> MEI_REG_SHIFT)

// DS (Bits 11-9)
#define MEI_DS_MASK           (0x7 << 9)
#define MEI_DS_SHIFT          9
#define MEI_GET_DS(val)       (((val) & MEI_DS_MASK) >> MEI_DS_SHIFT)

// U (Bit 8)
#define MEI_U_MASK            (1 << 8)
#define MEI_GET_U(val)        (((val) & MEI_U_MASK) >> 8)

// RW (Bit 0)
#define MEI_RW_MASK         (1 << 0)
#define MEI_GET_RW(val)     ((val) & MEI_RW_MASK)

static unsigned long read_instruction(unsigned long pc)
{
    unsigned long inst = 0;
    unsigned short* pc_ptr = (unsigned short*)(pc);

    if (pc & 0x1) {
        ERROR("Trying to read guest unaligned instruction");
    }

    /* Enable Hyp access to VM space */
    set_mpid7(HYP_SPID);
    fence_sync();

    inst = (unsigned long)(*pc_ptr | (*(pc_ptr+1) << 16));

    /* Disable Hyp access to VM space */
    set_mpid7(AUX_SPID);
    fence_sync();

    return inst;
}

static void data_abort(void)
{
    unsigned long mea = get_mea();
    unsigned long mei = get_mei();

    unsigned int len = MEI_GET_LEN(mei);
    unsigned int reg = MEI_GET_REG(mei);
    unsigned int ds = MEI_GET_DS(mei);
    unsigned int u = MEI_GET_U(mei);
    /* unsigned int itype = MEI_GET_ITYPE(mei); */
    unsigned int rw = MEI_GET_RW(mei);
    vaddr_t addr = mea;

    /* Decode possible bitwise instruction */
    unsigned long inst = read_instruction(vcpu_readpc(cpu()->vcpu));
    unsigned long opcode = ((inst & OPCODE_MASK) >> OPCODE_SHIFT);
    unsigned long subopcode = ((inst & SUBOPCODE_MASK) >> SUBOPCODE_SHIFT);
    unsigned long bit_op = 0;
    unsigned long mask = 0;
    
    if (opcode == F8_OPCODE) {
        mask = 1UL << ((inst & BITIDX_MASK) >> BITIDX_SHIFT);
        bit_op = ((inst & SUB8_MASK) >> SUB8_SHIFT) + 1;
    }
    else if (opcode == F9_OPCODE && subopcode == F9_SUBOPCODE) {
        unsigned long reg_idx = (inst & REGIDX_MASK) >> REGIDX_SHIFT;
        unsigned long bit_idx = vcpu_readreg(cpu()->vcpu, reg_idx);
        mask = 1UL << (bit_idx & 0x7UL);
        bit_op = ((inst & SUB9_MASK) >> SUB9_SHIFT) + 1;
    }

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        struct emul_access emul;
        emul.addr = addr;
        emul.width = len;
        emul.write = rw ? true : false;
        emul.reg = reg;
        emul.reg_width = ds;
        emul.sign_ext = ~u;

        emul.arch.op = (enum bitwise_op)bit_op;
        emul.arch.byte_mask = mask;

        if (handler(&emul)) {
            unsigned long pc_step = len;
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("Data abort emulation failed (0x%x)", addr);
        }
    } else {
        ERROR("No emulation handler for access to 0x%x, at 0x%x", addr, vcpu_readpc(cpu()->vcpu));
    }
}

static void hvtrap(void) {
    unsigned long r6 = vcpu_readreg(cpu()->vcpu , 6);
    unsigned long res = (unsigned long)hypercall(r6);
    vcpu_writereg(cpu()->vcpu, 6, res);
}

void abort(void)
{
    unsigned long psw = get_psw();
    unsigned long cause = (psw & (0x1UL << 7)) ? 
                            (get_feic() & 0xFFFFUL) :
                            (get_eiic() & 0xFFFFUL);

    switch (cause) {
        case 0x01:
            WARNING("Exception: RESET - Reset input\n");
            break;
            
        case 0x1C:
            WARNING("Exception: SYSERR - System error (context saving error)\n");
            break;

        case 0x1D:
            WARNING("Exception: SYSERR - System error (error prior to register bank "
                    "restoration)\n");
            break;

        case 0x60:
            WARNING("Exception: RIE - Reserved instruction exception\n");
            break;

        case 0x71:
            WARNING("Exception: FPE - FPU exception (precise)\n");
            break;

        case 0x75:
            WARNING("Exception: FXE - FXU exception (precise)\n");
            break;

        case 0x80:
        case 0x81:
        case 0x82:
            WARNING("Exception: UCPOP - Coprocessor unusable exception\n");
            break;

        case 0x90:
            WARNING("Exception: MIP - Memory protection exception due to instruction fetching\n");
            break;
        case 0x91:
            data_abort();
            break;
        case 0x95:
            WARNING("Exception: MDP - Memory protection exception (interrupt table reference "
                    "method)\n");
            break;
        case 0x98:
            WARNING("Exception: MIP - Guest memory protection exception due to instruction "
                "fetching\n");
            break;
        case 0x99:
            data_abort();
            break;
        case 0x9D:
            WARNING("Exception: MDP - Guest memory protection exception (interrupt table "
                    "reference method)\n");
            break;

        case 0xA0:
            WARNING("Exception: PIE - Privilege instruction exception\n");
            break;

        case 0xC0:
            WARNING("Exception: MAE - Misalignment exception\n");
            break;

        case 0xE0:
            WARNING("Exception: FENMI - FENMI interrupt\n");
            break;

        default:

            if (cause >= 0xF0 && cause <= 0xFF) {
                WARNING("FEINT - FEINT interrupt");
            } else if (cause >= 0x1000 && cause <= 0x17FF) {
                WARNING("EIINT - User interrupt");
            } else if (cause >= 0x10 && cause <= 0x1F) {
                WARNING("SYSERR - System error (instruction fetch error)");
            } else if (cause >= 0xf000 && cause <= 0xf01f) {
                hvtrap();
            }else if (cause >= 0x8000 && cause <= 0x80FF) {
                WARNING("SYSCALL - System call");
            } else if (cause >= 0x31 && cause <= 0x3F) {
                WARNING("FETRAP - FE level trap");
            } else if (cause >= 0x40 && cause <= 0x4F) {
                WARNING("TRAP0 - EI level trap 0");
            } else if (cause >= 0x50 && cause <= 0x5F) {
                WARNING("TRAP1 - EI level trap 1");
            } else {
                WARNING("Exception: Unknown exception code: 0x%X\n", cause);
            }
            break;
    }
}
