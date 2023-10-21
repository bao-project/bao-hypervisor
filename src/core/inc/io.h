/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef IO_H
#define IO_H

#include <bao.h>
#include <mem_prot/io.h>
#include <list.h>

struct vm_config;
struct vm;

struct vm_io {
    struct io_prot prot;
};

/* Mainly for HW initialization. */
void io_init();

/* iommu api for vms. */
bool io_vm_init(struct vm* vm, const struct vm_config* config);
bool io_vm_add_device(struct vm* vm, deviceid_t dev_id);

#endif /* IO_H_ */
