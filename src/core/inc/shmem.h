/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef SHMEM_H
#define SHMEM_H

#include <mem.h>

void shmem_init(void);
struct shmem* shmem_get(size_t shmem_id);

#endif /* SHMEM_H */
