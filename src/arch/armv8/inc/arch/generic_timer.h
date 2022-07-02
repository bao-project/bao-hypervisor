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

#ifndef GENERIC_TIMER_H
#define GENERIC_TIMER_H

#include <bao.h>

#define GENERIC_TIMER_CNTCTL_CNTCR_EN   (0x1)

struct generic_timer_cntctrl  {
    uint32_t CNTCR;
    uint32_t CNTSR;
    uint64_t CNTCV;
    uint8_t res0[0x20-0x10];
    uint32_t CNTDIF0;
    uint32_t CNTDIF[0];
    uint8_t res1[0xfd0-0x24];
    uint32_t CounterID[12];
} __attribute__((packed, aligned(PAGE_SIZE)));

#endif /* GENERIC_TIMER_H */
