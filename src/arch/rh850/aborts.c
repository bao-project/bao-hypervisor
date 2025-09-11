/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <emul.h>
#include <hypercall.h>
#include <fences.h>
#include <vmm.h>
#include <arch/aborts.h>
#include <arch/emul.h>
#include <srs.h>

#define MDP_HOST          (0x91)
#define MDP_GUEST         (0x99)
#define HVTRAP_LOW        (0xf000)
#define HVTRAP_HIGH       (0xf01f)

#define PSW_NP_SHIFT      (7UL)
#define PSW_NP_MASK       (0x1UL << PSW_NP_SHIFT)
#define PSW_GET_NP(v)     (((v) & PSW_NP_MASK) >> PSW_NP_SHIFT)

#define EIIC_CAUSE_SHIFT  (0UL)
#define EIIC_CAUSE_MASK   (0xFFFFUL)
#define EIIC_GET_CAUSE(v) (((v) & EIIC_CAUSE_MASK) >> EIIC_CAUSE_SHIFT)

#define FEIC_CAUSE_SHIFT  (0UL)
#define FEIC_CAUSE_MASK   (0xFFFFUL)
#define FEIC_GET_CAUSE(v) (((v) & FEIC_CAUSE_MASK) >> FEIC_CAUSE_SHIFT)

#define F8_OPCODE         (0x3EUL)
#define F9_OPCODE         (0x3FUL)
#define F9_SUBOPCODE      (0x1CUL)

#define OPCODE_SHIFT      (5)
#define OPCODE_MASK       (0x3FUL << OPCODE_SHIFT)

#define SUBOPCODE_SHIFT   (19)
#define SUBOPCODE_MASK    (0x1FFFUL << SUBOPCODE_SHIFT)

#define SUB8_SHIFT        (14)
#define SUB8_MASK         (0x3UL << SUB8_SHIFT)

#define SUB9_SHIFT        (17)
#define SUB9_MASK         (0x3UL << SUB9_SHIFT)

#define BITIDX_SHIFT      (11)
#define BITIDX_MASK       (0x7UL << BITIDX_SHIFT)

#define REGIDX_SHIFT      (11)
#define REGIDX_MASK       (0x1FUL << REGIDX_SHIFT)

// LEN (Bits 31-28)
#define MEI_LEN_MASK      (0xFUL << 28)
#define MEI_LEN_SHIFT     28
#define MEI_GET_LEN(val)  (((val) & MEI_LEN_MASK) >> MEI_LEN_SHIFT)

// REG (Bits 20-16)
#define MEI_REG_MASK      (0x1F << 16)
#define MEI_REG_SHIFT     16
#define MEI_GET_REG(val)  (((val) & MEI_REG_MASK) >> MEI_REG_SHIFT)

// DS (Bits 11-9)
#define MEI_DS_MASK       (0x7 << 9)
#define MEI_DS_SHIFT      9
#define MEI_GET_DS(val)   (((val) & MEI_DS_MASK) >> MEI_DS_SHIFT)

// U (Bit 8)
#define MEI_U_MASK        (1 << 8)
#define MEI_GET_U(val)    (((val) & MEI_U_MASK) >> 8)

// RW (Bit 0)
#define MEI_RW_MASK       (1 << 0)
#define MEI_GET_RW(val)   ((val) & MEI_RW_MASK)

static unsigned long read_instruction(unsigned long pc)
{
    unsigned long inst = 0;
    uint16_t* pc_ptr = (uint16_t*)(pc);

    if (pc & 0x1) {
        ERROR("Trying to read guest unaligned instruction");
    }

    /* Enable Hyp access to VM space */
    srs_mpid6_write(HYP_SPID);
    fence_sync_write();

    inst = (unsigned long)(*pc_ptr | (*(pc_ptr + 1) << 16));

    /* Disable Hyp access to VM space */
    srs_mpid6_write(cpu()->vcpu->vm->id);
    fence_sync();

    return inst;
}

static unsigned long ds_to_width(unsigned long ds)
{
    /**
     * 0: Byte (1 byte)
     * 1: Halfword (2 bytes)
     * 2: Word (4 bytes)
     * 3: Double-word (8 bytes)
     * 4: Quad-word (16 bytes)
     */
    return (1UL << ds);
}

static void decode_access(struct emul_access* acc, unsigned long addr)
{
    unsigned long mei = srs_mei_read();

    unsigned int reg = MEI_GET_REG(mei);
    unsigned int ds = MEI_GET_DS(mei);
    unsigned int u = MEI_GET_U(mei);
    unsigned int rw = MEI_GET_RW(mei);

    /* Decode possible bitwise instruction */
    unsigned long inst = read_instruction(vcpu_readpc(cpu()->vcpu));
    unsigned long opcode = ((inst & OPCODE_MASK) >> OPCODE_SHIFT);
    unsigned long subopcode = ((inst & SUBOPCODE_MASK) >> SUBOPCODE_SHIFT);
    unsigned long bwop = EMUL_ARCH_BWOP_NO;
    uint8_t bit = 0;

    if (opcode == F8_OPCODE) {
        bit = (inst & BITIDX_MASK) >> BITIDX_SHIFT;
        bwop = ((inst & SUB8_MASK) >> SUB8_SHIFT) + 1;
        int16_t imm = (int16_t)(inst >> 16);
        if (imm < 0) {
            if ((unsigned long)(-imm) > addr) {
                ERROR("bitwise addr underflow")
            }
        } else {
            if (addr > UINT32_MAX - (unsigned long)imm) {
                ERROR("bitwise addr overflow")
            }
        }

        addr = (unsigned long)((signed long)addr + imm);
    } else if (opcode == F9_OPCODE && subopcode == F9_SUBOPCODE) {
        unsigned long reg_idx = (inst & REGIDX_MASK) >> REGIDX_SHIFT;
        /* only the three LSB of register val are used as bit index */
        bit = vcpu_readreg(cpu()->vcpu, reg_idx) & 0x7;
        bwop = ((inst & SUB9_MASK) >> SUB9_SHIFT) + 1;
    }

    acc->addr = addr;
    acc->width = ds_to_width(ds);
    acc->write = rw ? true : false;
    acc->reg = reg;
    acc->sign_ext = ~u;
    acc->arch.bwop = bwop;
    acc->arch.bit = bit;
}

static void data_abort(void)
{
    unsigned long mea = srs_mea_read();
    unsigned long mei = srs_mei_read();
    vaddr_t addr = mea;

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        struct emul_access emul;
        decode_access(&emul, addr);

        if (handler(&emul)) {
            unsigned long pc_step = MEI_GET_LEN(mei);
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            ERROR("Data abort emulation failed (0x%x)", addr);
        }
    } else {
        ERROR("No emulation handler for access to 0x%x, at 0x%x", addr, vcpu_readpc(cpu()->vcpu));
    }
}

static void hvtrap(void)
{
    unsigned long r6 = vcpu_readreg(cpu()->vcpu, 6);
    unsigned long res = (unsigned long)hypercall(r6);
    vcpu_writereg(cpu()->vcpu, 6, res);
}

static inline unsigned long get_exception_cause(void)
{
    unsigned long psw = srs_psw_read();
    unsigned long cause = 0;

    if (PSW_GET_NP(psw)) {
        cause = FEIC_GET_CAUSE(srs_feic_read());
    } else {
        cause = EIIC_GET_CAUSE(srs_eiic_read());
    }
    return cause;
}

void internal_abort(void)
{
    bool is_fe = !!(srs_psw_read() & 0x80);
    unsigned long fault_pc = is_fe ? srs_feic_read() : srs_eipc_read();
    ERROR("Internal abort at 0x%x\n", fault_pc);
}

void abort(void)
{
    unsigned long cause = get_exception_cause();
    switch (cause) {
        case MDP_GUEST:
            data_abort();
            break;
        case MDP_HOST:
            ERROR("Host data abort");
            break;
        default:
            if (cause >= HVTRAP_LOW && cause <= HVTRAP_HIGH) {
                hvtrap();
            } else {
                WARNING("Exception not handled. Cause: 0x%lx", cause);
            }
    }
}
