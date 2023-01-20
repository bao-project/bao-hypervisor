/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/page_table.h>

.section .glb_page_tables, "aw"

.globl root_l1_pt
.balign PAGE_SIZE, 0
root_l1_pt:
    .skip PAGE_SIZE

.globl root_l2_pt
.balign PAGE_SIZE, 0
root_l2_pt:
    .skip PAGE_SIZE

.globl root_l1_flat_pt
.balign PAGE_SIZE, 0
root_l1_flat_pt:
    .skip PAGE_SIZE

