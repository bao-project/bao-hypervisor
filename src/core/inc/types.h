/**
 * SPDX-License-Identifier: Apache-2.0
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
#define MAX_VA  ((vaddr_t)-1)
#define INVALID_VA MAX_VA

typedef ssize_t mpid_t;
#define INVALID_MPID    ((mpid_t)-1)

typedef unsigned long colormap_t;

typedef unsigned long cpuid_t;
typedef unsigned long vcpuid_t;
typedef unsigned long cpumap_t;
#define INVALID_CPUID   ((cpuid_t)-1)

typedef unsigned irqid_t;

typedef unsigned deviceid_t;

typedef enum AS_SEC {
    /*--- HYP AS SECTIONS -----*/
    SEC_HYP_GLOBAL = 0,
    SEC_HYP_IMAGE,
    SEC_HYP_PRIVATE,
    SEC_HYP_VM,
    SEC_HYP_ANY, /* must be last */
    /*--- VM AS SECTIONS -----*/
    SEC_VM_ANY = 0, /* must be last */
    /*---- INVALID AS_SECTION ----*/
    SEC_UNKNOWN = -1,
} as_sec_t;

typedef enum AS_TYPE { AS_HYP = 0, AS_VM, AS_HYP_CPY } as_type_t;

typedef enum { PRIV_NONE = 0, PRIV_HYP = 1, PRIV_VM = 2 } priv_t;

typedef enum { PERM_X = 1, PERM_R = 2, PERM_W = 4} perms_t;
#define PERM_NONE   ((perms_t)0)
#define PERM_RW     (PERM_R | PERM_W)
#define PERM_RX     (PERM_R | PERM_X)
#define PERM_RWX    (PERM_R | PERM_W | PERM_X)

typedef unsigned long mem_attrs_t;

#endif
