/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cpu.h>
#include <emul.h>
#include <arch/decode.h>

/* We assume that D regs are (16+reg_num)*/
bool decode_16b_access(unsigned long ins, struct emul_access* emul)
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

bool decode_32b_access(unsigned long ins, struct emul_access* emul)
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
            WARNING("ST.T (store bit) emulation is not yet supported");
            break;

        default:
            break;
    }

    return ret;
}

unsigned long decode_cfr_access(unsigned long ins, struct emul_access* emul)
{
    unsigned long opcode = bit32_extract(ins, 0, 8);
    unsigned long csfr = bit32_extract(ins, 12, 16);

    emul->reg = bit32_extract(ins, 8, 4) + 16;

    switch (opcode) {
        case 0x4D:
            /* MFCR */
            emul->write = false;
            emul->reg_width = 4;
            break;

        case 0x4F:
            /* MFDCR*/
            emul->write = false;
            emul->reg_width = 8;
            break;

        case 0xCD:
            /* MTCR */
            emul->write = true;
            emul->reg_width = 4;
            break;

        case 0xCF:
            /* MTDCR*/
            emul->write = true;
            emul->reg_width = 8;
            break;

        default:
            break;
    }
    return csfr;
}
