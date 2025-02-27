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
    irqid_t* interrupts;
};

struct vm_config;

long int ipc_hypercall(void);
void ipc_init(void);

#endif /* IPC_H */
