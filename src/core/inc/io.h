/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

/**
 * baohu separation kernel
 *
 * Copyright (c) Jose Martins, Sandro Pinto, David Cerdeira
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *
 * baohu is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
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
bool io_vm_init(struct vm *vm, const struct vm_config *config);
bool io_vm_add_device(struct vm *vm, deviceid_t dev_id);

#endif /* IO_H_ */
