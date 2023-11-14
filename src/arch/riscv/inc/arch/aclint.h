/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef ACLINT_H
#define ACLINT_H

#include <bao.h>
#include <platform.h>

#define ACLINT_SSWI_MAX_HARTS   (4095)
#define ACLINT_SSWI_SET_SETSSIP (0x1)

struct aclint_sswi_hw {
    uint32_t setssip[ACLINT_SSWI_MAX_HARTS];
    uint32_t res;
} __attribute__((__packed__, aligned(PAGE_SIZE)));

extern volatile struct aclint_sswi_hw* aclint_sswi;

void aclint_init();
void aclint_send_ipi(cpuid_t hart);

cpuid_t aclint_plat_sswi_index_to_hart_id(cpuid_t sswi_index);
cpuid_t aclint_plat_hart_id_to_sswi_index(cpuid_t hard_id);

#endif /* ACLINT_H */
