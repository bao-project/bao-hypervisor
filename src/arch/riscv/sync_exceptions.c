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

static unsigned long read_ins(uintptr_t ins_addr)
{
    unsigned long ins = 0;

    bool succ = vm_readmem(cpu.vcpu->vm, &ins, ins_addr, 2, true);
    if (succ && ((ins & 0x3) == 3)) {
        succ = vm_readmem(cpu.vcpu->vm, &ins, ins_addr, 4, true);
    }

    if(!succ){
        ERROR("failed to read guest instruction");
        /**
         * TODO: maybe the best is to inject the instuction fault in the
         * guest instead of stopping altogether
         */
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

size_t guest_page_fault_handler()
{   
    /**
     * If this was caused by an hypervisor access using hlv instructions, 
     * just mark it as such, and return.
     * TODO: should we proceed with emulation even if this is a hypervisor
     * access? 
     */
    if(!(CSRR(CSR_HSTATUS) & HSTATUS_SPV)){
        cpu.arch.hlv_except = true;
        return 4;
    }

    uintptr_t addr = CSRR(CSR_HTVAL) << 2;

    emul_handler_t handler = vm_emul_get_mem(cpu.vcpu->vm, addr);
    if (handler != NULL) {
        uintptr_t ins_addr = CSRR(sepc);
        unsigned long ins = read_ins(ins_addr);

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
            return INS_SIZE(ins);
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

    // TODO: Do we need to check call comes from VS-mode and not VU-mode
    // or U-mode ?

    if (_scause < sync_handler_table_size && sync_handler_table[_scause]) {
        pc_step = sync_handler_table[_scause]();
    } else {
        ERROR("unkown synchronous exception (%d)", _scause);
    }

    cpu.vcpu->regs->sepc += pc_step;
}
