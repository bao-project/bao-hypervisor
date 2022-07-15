/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

typedef signed long ssize_t;

typedef unsigned long asid_t;

typedef unsigned long vmid_t;

typedef uintptr_t paddr_t;
typedef uintptr_t regaddr_t;
typedef uintptr_t vaddr_t;
#define NULL_VA ((vaddr_t)NULL)
#define MAX_VA  ((vaddr_t)-1)

typedef unsigned long colormap_t;

typedef unsigned long cpuid_t;
typedef unsigned long vcpuid_t;
typedef unsigned long cpumap_t;
#define INVALID_CPUID   ((cpuid_t)-1)

typedef unsigned irqid_t;

typedef unsigned streamid_t;

#endif
