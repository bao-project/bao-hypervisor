/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <arch/encoding.h>
#include <arch/csrs.h>
#include <arch/instructions.h>

void internal_exception_handler(unsigned long gprs[]) {

    for(int i = 0; i < 31; i++) {
        printk("x%d:\t\t0x%0lx\n", i, gprs[i]);
    }
    printk("sstatus:\t0x%0lx\n", CSRR(sstatus));
    printk("stval:\t\t0x%0lx\n", CSRR(stval));
    printk("sepc:\t\t0x%0lx\n", CSRR(sepc));
    ERROR("cpu%d internal hypervisor abort - PANIC\n", cpu.id);
}

static uint32_t read_ins(uintptr_t ins_addr)
{
    uint32_t ins = 0;

    if(ins_addr & 0b1) {
        ERROR("trying to read guest unaligned instruction");
    }

    /**
     * Read 16 bits at a time to make sure the access is aligned. If
     * the instruction is not compressed, read the following 16-bits.
     */
    ins = hlvxhu(ins_addr);
    if ((ins & 0b11) == 3) {
        ins |= ((uint32_t)hlvxhu(ins_addr + 2)) << 16;
    }

    return ins;
}

typedef size_t (*sync_handler_t)();

extern size_t sbi_vs_handler();

static inline int ins_ldst_decode(uintptr_t ins, emul_access_t *emul)
{
    if (INS_COMPRESSED(ins)) {
        if (INS_C_OPCODE(ins) != MATCH_C_LOAD &&
            INS_C_OPCODE(ins) != MATCH_C_STORE) {
            return -1;
        }

        emul->width = 4;
        emul->reg_width = REGLEN;
        emul->write = (INS_C_OPCODE(ins) == MATCH_C_STORE);
        emul->reg = INS_C_RD_RS2(ins) + 8;
        emul->sign_ext = true;
    } else {
        if (INS_OPCODE(ins) != MATCH_LOAD && INS_OPCODE(ins) != MATCH_STORE) {
            return -1;
        }

        int funct3 = INS_FUNCT3(ins);
        emul->width = (funct3 & 3) == 0
                          ? 1
                          : (funct3 & 3) == 1 ? 2 : (funct3 & 3) == 2 ? 4 : 8;
        emul->reg_width = REGLEN;
        emul->write = (INS_OPCODE(ins) == MATCH_STORE);
        emul->reg = emul->write ? INS_RS2(ins) : INS_RD(ins);
        emul->sign_ext = !(funct3 & 0x4);
    }

    return 0;
}

static inline bool is_pseudo_ins(uint32_t ins) {
    return ins == TINST_PSEUDO_STORE || ins == TINST_PSEUDO_LOAD;
}

size_t guest_page_fault_handler()
{
    uintptr_t addr = CSRR(CSR_HTVAL) << 2;

    emul_handler_t handler = vm_emul_get_mem(cpu.vcpu->vm, addr);
    if (handler != NULL) {

        uint64_t ins = CSRR(CSR_HTINST);
        uint64_t ins_size;
        if(ins == 0) {
            /**
             * If htinst does not provide information about the trap,
             * we must read the instruction from the guest's memory
             * manually.
             */
            uintptr_t ins_addr = CSRR(sepc);
            ins = read_ins(ins_addr);
            ins_size = INS_SIZE(ins);
        } else if (is_pseudo_ins(ins)) {
            //TODO: we should reinject this in the guest as a fault access
            ERROR("fault on 1st stage page table walk");
        } else {
            /**
             * If htinst is valid and is not a pseudo isntruction make sure
             * the opcode is valid even if it was a compressed instruction,
             * but before save the real instruction size.
             */
            ins_size = TINST_INS_SIZE(ins);
            ins = ins | 0b10;
        }

        emul_access_t emul;
        if (ins_ldst_decode(ins, &emul) < 0) {
            ERROR("cant decode ld/st instruction");
        }
        emul.addr = addr;

        /**
         * TODO: check if the access is aligned.
         * If not, inject an exception in the vm.
         */

        if (handler(&emul)) {
            return ins_size;
        } else {
            ERROR("emulation handler failed (0x%x at 0x%x)", addr, CSRR(sepc));
        }
    } else {
        ERROR("no emulation handler for abort(0x%x at 0x%x)", addr, CSRR(sepc));
    }
}

sync_handler_t sync_handler_table[] = {
    [SCAUSE_CODE_ECV] = sbi_vs_handler,
    [SCAUSE_CODE_LGPF] = guest_page_fault_handler,
    [SCAUSE_CODE_SGPF] = guest_page_fault_handler,
};

static const size_t sync_handler_table_size =
    sizeof(sync_handler_table) / sizeof(sync_handler_t);

void sync_exception_handler()
{
    size_t pc_step = 0;
    unsigned long _scause = CSRR(scause);

    if(!(CSRR(CSR_HSTATUS) & HSTATUS_SPV)) {
        internal_exception_handler(&cpu.vcpu->regs->x[0]);
    }

    // TODO: Do we need to check call comes from VS-mode and not VU-mode
    // or U-mode ?

    if (_scause < sync_handler_table_size && sync_handler_table[_scause]) {
        pc_step = sync_handler_table[_scause]();
    } else {
        ERROR("unkown synchronous exception (%d)", _scause);
    }

    cpu.vcpu->regs->sepc += pc_step;
}
