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

    /**
     * TODO: make sure this is a valid instruction address
     */

    CSRS(sstatus, SSTATUS_MXR);
    vm_readmem(cpu.vcpu->vm, &ins, ins_addr, 2);
    if ((ins & 0x3) == 3) {
        vm_readmem(cpu.vcpu->vm, &ins, ins_addr, 4);
    }
    CSRC(sstatus, SSTATUS_MXR);

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
    uintptr_t addr = CSRR(CSR_HTVAL) << 2;

    emul_handler_t handler = vm_get_emul(cpu.vcpu->vm, addr);
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
            ERROR("emulation handler failed");
        }
    } else {
        ERROR("no emulation handler for abort(0x%x at 0x%x)", addr, CSRR(sepc));
    }
}

size_t illegal_ins_handler()
{
    // assuming the instruction is placed in stval
    uintptr_t ins = CSRR(stval);

    if ((ins & MASK_WFI) == MATCH_WFI) {
        asm volatile("wfi" ::: "memory");
    } else {
        ERROR("unkown illegal instruction\n");
    }

    return INS_SIZE(ins);
}

sync_handler_t sync_handler_table[] = {
    [SCAUSE_CODE_ECV] = sbi_vs_handler,
    [SCAUSE_CODE_LGPF] = guest_page_fault_handler,
    [SCAUSE_CODE_SGPF] = guest_page_fault_handler,
    [SCAUSE_CODE_ILI] = illegal_ins_handler,
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
