/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
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

.globl root_l3_pt
.balign PAGE_SIZE, 0
root_l3_pt:
    .skip PAGE_SIZE

.globl root_l1_flat_pt
.balign PAGE_SIZE, 0
root_l1_flat_pt:
    .skip PAGE_SIZE

