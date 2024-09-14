/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef HYPERCALL_H
#define HYPERCALL_H

#include <bao.h>
#include <arch/hypercall.h>
#include <vm.h>

enum { HC_INVAL = 0, HC_IPC = 1, HC_REMIO = 2 };

enum { HC_E_SUCCESS = 0, HC_E_FAILURE = 1, HC_E_INVAL_ID = 2, HC_E_INVAL_ARGS = 3 };

typedef unsigned long (*hypercall_handler)(void);

long int hypercall(unsigned long id);

static inline unsigned long hypercall_get_arg(struct vcpu* vcpu, size_t arg_index)
{
    return vcpu_readreg(vcpu, HYPCALL_IN_ARG_REG(arg_index));
}

static inline void hypercall_set_ret(struct vcpu* vcpu, size_t arg_index, unsigned long arg_val)
{
    vcpu_writereg(vcpu, HYPCALL_OUT_ARG_REG(arg_index), arg_val);
}

#endif /* HYPERCALL_H */
