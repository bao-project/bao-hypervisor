/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/aclint.h>
#include <cpu.h>
#include <bao.h>
#include <platform.h>

volatile struct aclint_sswi_hw* aclint_sswi;

void aclint_init(void)
{
    aclint_sswi = (void*)mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
        platform.arch.aclint_sswi.base, NUM_PAGES(sizeof(struct aclint_sswi_hw)));
}

void aclint_send_ipi(cpuid_t target_hart)
{
    cpuid_t aclint_index = aclint_plat_hart_id_to_sswi_index(target_hart);
    if (target_hart < platform.cpu_num) {
        aclint_sswi->setssip[aclint_index] = ACLINT_SSWI_SET_SETSSIP;
    }
}

/**
 * By default aclint hart index is equal to the hart identifier
 * This may be overwritten on the platform defined code
 */

__attribute__((weak)) cpuid_t aclint_plat_sswi_index_to_hart_id(cpuid_t sswi_index)
{
    return sswi_index;
}

__attribute__((weak)) cpuid_t aclint_plat_hart_id_to_sswi_index(cpuid_t hart_id)
{
    return hart_id;
}
