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
    console_printk("stval:\t\t0x%0lx\n", csrs_stval_read());
    console_printk("sepc:\t\t0x%0lx\n", csrs_sepc_read());
    ERROR("cpu%d internal hypervisor abort - PANIC\n", cpu()->id);
}

static uint32_t read_ins(uintptr_t ins_addr)
{
    uint32_t ins = 0;

    if (ins_addr & 0x1) {
        ERROR("trying to read guest unaligned instruction\n");
    }

    /**
     * Read 16 bits at a time to make sure the access is aligned. If the instruction is not
     * compressed, read the following 16-bits.
     */
    ins = (uint32_t)hlvxhu(ins_addr);
    if ((ins & 0x3) == 3) {
        ins |= ((uint32_t)hlvxhu(ins_addr + 2)) << 16;
    }

    return ins;
}

typedef bool (*sync_handler_t)(size_t* inst_size);

extern bool sbi_vs_handler(size_t* inst_size);

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

static bool guest_page_fault_handler(size_t* inst_size)
{
    bool fault_handled = false;
    vaddr_t addr = (csrs_htval_read() << 2) | (csrs_stval_read() & 0x3);

    emul_handler_t handler = vm_emul_get_mem(cpu()->vcpu->vm, addr);
    if (handler != NULL) {
        unsigned long ins = csrs_htinst_read();
        if (ins == 0) {
            /**
             * If htinst does not provide information about the trap, we must read the instruction
             * from the guest's memory manually.
             */
            vaddr_t ins_addr = csrs_sepc_read();
            ins = read_ins(ins_addr);
            *inst_size = INS_SIZE(ins);
        } else if (!is_pseudo_ins((uint32_t)ins)) {
            /**
             * If htinst is valid and is not a pseudo isntruction make sure the opcode is valid
             * even if it was a compressed instruction, but before save the real instruction size.
             */
            *inst_size = TINST_INS_SIZE(ins);
            ins = ins | 0x2;
        }

        struct emul_access emul;
        if (ins_ldst_decode(ins, &emul)) {
            /**
             * TODO: check if the access is aligned. If not, inject an exception in the vm.
             */
            emul.addr = addr;
            fault_handled = handler(&emul);
        }
    }

    return fault_handled;
}

static bool vcpu_redirect_exception(void)
{
    /**
     * This functions assumes we redirect the exception to the currently active vcpu.
     * It also assumes we are always handling exceptions, not interrupts.
     */

    bool exception_redirected = false;

    unsigned long vsepc = csrs_sepc_read();
    unsigned long vstval = csrs_stval_read();
    unsigned long exception_pc = csrs_vstvec_read() & ~STVEC_MODE_MSK;

    unsigned long vsstatus = csrs_vsstatus_read();

    vsstatus &= ~SSTATUS_SPP_BIT;
    bool vcpu_in_vs = (cpu()->vcpu->regs.sstatus & SSTATUS_SPP_BIT) != 0;
    if (vcpu_in_vs) {
        vsstatus |= SSTATUS_SPP_BIT;
    }
    vsstatus &= ~SSTATUS_SPIE_BIT;
    bool vcpu_interrupts_enabled = (vsstatus & SSTATUS_SIE_BIT) != 0;
    if (vcpu_interrupts_enabled) {
        vsstatus |= SSTATUS_SPIE_BIT;
    }
    vsstatus &= ~SSTATUS_SIE_BIT;

    unsigned long vscause = 0;
    bool cause_can_be_redirected = true;
    unsigned long scause = csrs_scause_read();
    switch (scause) {
        case SCAUSE_CODE_IGPF:
            vscause = SCAUSE_CODE_IAF;
            break;
        case SCAUSE_CODE_LGPF:
            vscause = SCAUSE_CODE_LAF;
            break;
        case SCAUSE_CODE_SGPF:
            vscause = SCAUSE_CODE_SAF;
            break;
        case SCAUSE_CODE_VRTI:
            vscause = SCAUSE_CODE_ILI;
            break;
        case SCAUSE_CODE_IAM:
        case SCAUSE_CODE_IAF:
        case SCAUSE_CODE_ILI:
        case SCAUSE_CODE_LAM:
        case SCAUSE_CODE_LAF:
        case SCAUSE_CODE_SAM:
        case SCAUSE_CODE_SAF:
            vscause = scause;
            break;
        default:
            cause_can_be_redirected = false;
            break;
    }

    if (cause_can_be_redirected) {
        csrs_vsstatus_write(vsstatus);
        csrs_vscause_write(vscause);
        csrs_vsepc_write(vsepc);
        csrs_vstval_write(vstval);
        vcpu_writepc(cpu()->vcpu, exception_pc);
        cpu()->vcpu->regs.sstatus |= SSTATUS_SPP_BIT;
        exception_redirected = true;
    }

    return exception_redirected;
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
    bool exception_handled = false;
    unsigned long _scause = csrs_scause_read();

    if (!(csrs_hstatus_read() & HSTATUS_SPV)) {
        internal_exception_handler(&cpu()->vcpu->regs.x[0]);
    } else {
        // TODO: Do we need to check call comes from VS-mode and not VU-mode or U-mode ?

        if (_scause < sync_handler_table_size && sync_handler_table[_scause]) {
            exception_handled = sync_handler_table[_scause](&pc_step);
        }

        if (exception_handled) {
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + pc_step);
        } else {
            if (_scause == SCAUSE_CODE_ILI){
                vcpu_redirect_exception();
            } else {
                ERROR("unknown synchronous exception (%d) at 0x%x\n", _scause, vcpu_readpc(cpu()->vcpu));
                //vcpu_redirect_exception();
            }
        }
    }
}
