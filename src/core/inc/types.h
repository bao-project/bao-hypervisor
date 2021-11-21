/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2021-
 *
 * Authors:
 *      Aras Ashraf Gandomi <aras.ashrafgandomi2@unibo.it>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 * 
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef signed long ssize_t;

typedef unsigned long asid_t;

typedef unsigned long vmid_t;

typedef uintptr_t paddr_t;
typedef uintptr_t vaddr_t;
#define NULL_VA ((vaddr_t)NULL)
#define MAX_VA  ((vaddr_t)-1)

typedef unsigned long cpuid_t;
typedef unsigned long vcpuid_t;
typedef unsigned long cpumap_t;
#define INVALID_CPUID   ((cpuid_t)-1)

typedef unsigned irqid_t;

typedef unsigned streamid_t;

#endif
