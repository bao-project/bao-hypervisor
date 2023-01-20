/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <vmm.h>
#include <arch/sysregs.h>
#include <page_table.h>

void vmm_arch_init_tcr() {

    if (cpu()->id == CPU_MASTER) {

        /* Despite LPAE, we only support 32-bit guest physical address spaces. */
        parange = PAR_32BIT;

    }

    cpu_sync_barrier(&cpu_glb_sync);

    uint64_t vtcr = VTCR_RES1 | VTCR_ORGN0_WB_RA_WA | VTCR_IRGN0_WB_RA_WA |
                    VTCR_T0SZ(0) | VTCR_SH0_IS | VTCR_SL0_12;

    sysreg_vtcr_el2_write(vtcr);

}
