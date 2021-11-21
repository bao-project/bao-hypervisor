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

struct ipc {
    paddr_t base;
    size_t size;
    size_t shmem_id;
    size_t interrupt_num;
    irqid_t *interrupts;
};

struct vm_config;

unsigned long ipc_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2);
void ipc_init(const struct vm_config* vm_config, bool vm_master);
struct shmem* ipc_get_shmem(size_t shmem_id);

#endif /* IPC_H */
