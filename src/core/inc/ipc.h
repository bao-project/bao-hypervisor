/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
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
void ipc_init();
struct shmem* ipc_get_shmem(size_t shmem_id);

#endif /* IPC_H */
