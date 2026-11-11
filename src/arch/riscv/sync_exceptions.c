/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <arch/encoding.h>
#include <arch/csrs.h>
#include <arch/instructions.h>

static void internal_exception_handler(unsigned long gprs[])
{
    for (int i = 0; i < 31; i++) {
        console_printk("x%d:\t\t0x%0lx\n", i, gprs[i]);
    }
    console_printk("sstatus:\t0x%0lx\n", csrs_sstatus_read());
    console_printk("scause:\t\t0x%0lx\n", csrs_scause_read());
    console_printk("stval:\t\t0x%0lx\n", csrs_stval_read());
    console_printk("sepc:\t\t0x%0lx\n", csrs_sepc_read());
    ERROR("cpu%lu internal hypervisor abort - PANIC\n", cpu()->id);
}

static bool read_ins(uintptr_t ins_addr, unsigned long* ins)
{
    uint16_t lo;
    uint16_t hi = 0;

    /**
     * Read 16 bits at a time to make sure the access is aligned. If the instruction is not
     * compressed, read the following 16-bits.
     */
    if (!hlvxhu(ins_addr, &lo) || (!INS_COMPRESSED(lo) && !hlvxhu(ins_addr + 2, &hi))) {
        return false;
    }

    *ins = ((unsigned long)hi << 16) | lo;
    return true;
}

/* Returns whether the exception was handled, and stores the guest pc increment in pc_step. */
typedef bool (*sync_handler_t)(size_t* pc_step);

static inline bool ins_ldst_decode(vaddr_t ins, struct emul_access* emul)
{
    if (INS_COMPRESSED(ins)) {
        if (INS_C_OPCODE(ins) != MATCH_C_LOAD && INS_C_OPCODE(ins) != MATCH_C_STORE) {
            return false;
        }

        emul->width = 4;
        emul->reg_width = REGLEN;
        emul->write = (INS_C_OPCODE(ins) == MATCH_C_STORE);
        emul->reg = INS_C_RD_RS2(ins) + 8;
        emul->sign_ext = true;
    } else {
        if (INS_OPCODE(ins) != MATCH_LOAD && INS_OPCODE(ins) != MATCH_STORE) {
            return false;
        }

        unsigned funct3 = INS_FUNCT3(ins);
        emul->width = (funct3 & 3) == 0 ? 1 : (funct3 & 3) == 1 ? 2 : (funct3 & 3) == 2 ? 4 : 8;
        emul->reg_width = REGLEN;
        emul->write = (INS_OPCODE(ins) == MATCH_STORE);
        emul->reg = emul->write ? INS_RS2(ins) : INS_RD(ins);
        emul->sign_ext = !(funct3 & 0x4);
    }

    return true;
}

static inline bool is_pseudo_ins(uint32_t ins)
{
    return ins == TINST_PSEUDO_STORE || ins == TINST_PSEUDO_LOAD;
}

static bool guest_page_fault_handler(size_t* pc_step)
{
    vaddr_t addr = (csrs_htval_read() << 2) | (csrs_stval_read() & 0x3);

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        unsigned long ins = csrs_htinst_read();
        size_t ins_size;
        if (ins == 0) {
            /**
             * If htinst does not provide information about the trap, we must read the instruction
             * from the guest's memory manually.
             */
            vaddr_t ins_addr = vcpu_readpc(cpu()->vcpu);
            if (!read_ins(ins_addr, &ins)) {
                /* The read faulted, let the guest retry the access. */
                *pc_step = 0;
                return true;
            }
            ins_size = INS_SIZE(ins);
        } else if (is_pseudo_ins((uint32_t)ins)) {
            return false;
        } else {
            /**
             * If htinst is valid and is not a pseudo isntruction make sure the opcode is valid
             * even if it was a compressed instruction, but before save the real instruction size.
             */
            ins_size = TINST_INS_SIZE(ins);
            ins = ins | 0x2;
        }

        struct emul_access emul;
        if (!ins_ldst_decode(ins, &emul)) {
            return false;
        }
        emul.addr = addr;

        /**
         * TODO: check if the access is aligned. If not, inject an exception in the vm.
         */

        if (handler(&emul)) {
            *pc_step = ins_size;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

sync_handler_t sync_handler_table[] = {
    [SCAUSE_CODE_ECV] = sbi_vs_handler,
    [SCAUSE_CODE_LGPF] = guest_page_fault_handler,
    [SCAUSE_CODE_SGPF] = guest_page_fault_handler,
};

static const size_t sync_handler_table_size = sizeof(sync_handler_table) / sizeof(sync_handler_t);

void sync_exception_handler(void);
void sync_exception_handler(void)
{
    size_t pc_step = 0;
    bool handled = false;
    unsigned long _scause = csrs_scause_read();
    /* Handlers may clobber stval. */
    unsigned long _stval = csrs_stval_read();

    if (!(csrs_hstatus_read() & HSTATUS_SPV)) {
        internal_exception_handler(&cpu()->vcpu->regs.x[0]);
    }

    // TODO: Do we need to check call comes from VS-mode and not VU-mode or U-mode ?

    if (_scause < sync_handler_table_size && sync_handler_table[_scause]) {
        handled = sync_handler_table[_scause](&pc_step);
    }

    if (handled) {
        vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
    } else if (!vcpu_arch_inject_exception(cpu()->vcpu, _scause, _stval)) {
        ERROR("unknown synchronous exception (%lu)\n", _scause);
    }

    if (vcpu_arch_is_on(cpu()->vcpu) && !cpu()->vcpu->active) {
        cpu_standby();
    }
}
