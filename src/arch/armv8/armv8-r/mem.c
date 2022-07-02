/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>

void as_arch_init(struct addr_space* as)
{

}

bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    return false;
}
