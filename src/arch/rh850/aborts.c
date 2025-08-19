/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <hypercall.h>
#include <vm.h>
#include <arch/aborts.h>
#include <arch/srs.h>

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

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        struct emul_access emul;
        emul.addr = addr;
        emul.width = len;
        emul.write = rw ? true : false;
        emul.reg = reg;
        emul.reg_width = ds;
        emul.sign_ext = ~u;

        if (handler(&emul)) {
            unsigned long pc_step = len;
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("data abort emulation failed (0x%x)", addr);
        }
    } else {
        ERROR("no emulation handler for abort(0x%x at 0x%x)", addr, vcpu_readpc(cpu()->vcpu));
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
            // WARNING("Exception: MDP - Memory protection exception due to operand access)\n");
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
            // WARNING("Exception: MDP - Guest memory protection exception due to operand "
            //     "access)\n");
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
