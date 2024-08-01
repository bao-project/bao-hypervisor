/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __SCR_H__
#define __SCR_H__

#include <bao.h>
#include <spinlock.h>

/**
 * From https://github.com/riscv/riscv-scr-doc
 */

#define SCR_SUCCESS               (0)
#define SCR_ERR_FAILURE           (-1)
#define SCR_ERR_NOT_SUPPORTED     (-2)
#define SCR_ERR_INVALID_PARAM     (-3)
#define SCR_ERR_DENIED            (-4)
#define SCR_ERR_INVALID_ADDRESS   (-5)
#define SCR_ERR_ALREADY_AVAILABLE (-6)

struct scrret {
    long error;
    long value;
};

struct scr_ctx{
    enum { STARTED, STOPPED, START_PENDING, STOP_PENDING } state;
    spinlock_t lock;
    vaddr_t start_addr;
    unsigned int priv;
};

void scr_init(void);

struct scrret scr_core_start(unsigned long coreid, unsigned long start_addr, unsigned long priv);
struct scrret scr_core_stop(void);
struct scrret scr_core_status(unsigned long coreid);

#endif /* __SCR_H__ */
