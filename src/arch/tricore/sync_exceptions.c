/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <arch/encoding.h>
#include <arch/csfrs.h>
#include <arch/instructions.h>

/* static void internal_exception_handler(unsigned long gprs[]) */
/* { */
/*     for (int i = 0; i < 31; i++) { */
/*         console_printk("x%d:\t\t0x%0lx\n", i, gprs[i]); */
/*     } */

/*     ERROR("cpu%d internal hypervisor abort - PANIC\n", cpu()->id); */
/* } */

/* static uint32_t read_ins(uintptr_t ins_addr) */
/* { */
/*     uint32_t ins = 0; */


/*     return ins; */
/* } */

/* typedef size_t (*sync_handler_t)(); */

/* extern size_t sbi_vs_handler(); */

/* static inline bool ins_ldst_decode(vaddr_t ins, struct emul_access* emul) */
/* { */
/*     (void) ins; */
/*     (void) emul; */
/*      return true; */
/* } */

/* static inline bool is_pseudo_ins(uint32_t ins) */
/* { */
/*     (void) ins; */
/*     return false; */
/* } */


/* sync_handler_t sync_handler_table[] = { */
/*     [SCAUSE_CODE_ECV] = sbi_vs_handler, */
/*     [SCAUSE_CODE_LGPF] = guest_page_fault_handler, */
/*     [SCAUSE_CODE_SGPF] = guest_page_fault_handler, */
/* }; */

/* static const size_t sync_handler_table_size = sizeof(sync_handler_table) / sizeof(sync_handler_t); */

void sync_exception_handler(void);
void sync_exception_handler(void)
{
}
