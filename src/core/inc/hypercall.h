/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef HYPERCALL_H
#define HYPERCALL_H

#include <bao.h>
#include <arch/hypercall.h>

enum {
    HC_INVAL = 0,
    HC_IPC = 1
};

enum {
    HC_E_SUCCESS = 0,
    HC_E_FAILURE = 1,
    HC_E_INVAL_ID = 2,
    HC_E_INVAL_ARGS = 3
};

typedef unsigned long (*hypercall_handler)( unsigned long arg0, 
                                            unsigned long arg1, 
                                            unsigned long arg2);

long int hypercall(unsigned long id);

#endif /* HYPERCALL_H */
