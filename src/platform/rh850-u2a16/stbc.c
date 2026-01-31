/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

volatile struct stbc_hw* stbc;

void stbc_init(void)
{
    /* Enable temporary access to STBC registers */
    vaddr_t stbc_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
        (paddr_t)(PLAT_STBC_BASE), NUM_PAGES(sizeof(struct stbc_hw)));
    if (stbc_ptr == INVALID_VA) {
        ERROR("Maping STBC MMIO failed");
    }
    stbc = (struct stbc_hw*)stbc_ptr;

    /* Supply clocks for required peripherals */
    // TODO: Are OSTM, TAUD, and RSCFD required?
    stbc->MSRKCPROT = MSRKCPROT_ENABLE_WR;
    stbc->MSR_RSCFD = 0;
    stbc->MSR_RLIN3 = 0;
    stbc->MSR_TAUD = 0;
    stbc->MSR_OSTM = 0;
    stbc->MSRKCPROT = MSRKCPROT_DISABLE_WR;

    mem_unmap(&cpu()->as, (vaddr_t)(PLAT_STBC_BASE), NUM_PAGES(sizeof(struct stbc_hw)), true);
}
