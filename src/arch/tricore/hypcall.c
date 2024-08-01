/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/csrs.h>
#include <cpu.h>
#include <vm.h>
#include <bit.h>
#include <fences.h>
#include <hypercall.h>


void bao_msg_handler(uint32_t event, uint64_t data);



size_t tricore_hypercall_handler(void);

size_t tricore_hypercall_handler(void)
{

    /* switch (extid) { */

    /*     default: */
    /*         WARNING("guest issued unsupport sbi extension call (%d)", extid); */
    /*         ret.value = SBI_ERR_NOT_SUPPORTED; */
    /* } */

    return 4;
}
