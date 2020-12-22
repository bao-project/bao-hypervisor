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

#ifndef HYPERCALL_H
#define HYPERCALL_H

enum {
    HC_INVAL = 0,
    HC_IPC = 1
};

enum {
    HC_E_SUCCESS = 0,
    HC_E_FAILURE = 1,
    HC_E_INVAL_ID = 2,
    HC_E_INVAL_ARGS = 3
};

typedef int64_t (*hypercall_handler)(uint64_t arg0, uint64_t arg1, uint64_t arg2);

#endif /* HYPERCALL_H */