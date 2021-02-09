/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef IPC_H
#define IPC_H

#include <bao.h>
#include <mem.h>

typedef struct ipc {
    uint64_t base;
    size_t size;
    uint64_t shmem_id;
    size_t interrupt_num;
    uint64_t *interrupts;
} ipc_t;

typedef struct vm_config vm_config_t;

int64_t ipc_hypercall(uint64_t arg0, uint64_t arg1, uint64_t arg2);
void ipc_init(const vm_config_t* vm_config, bool vm_master);
shmem_t* ipc_get_shmem(uint64_t shmem_id);

#endif /* IPC_H */
