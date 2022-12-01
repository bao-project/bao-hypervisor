/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <hypercall.h>
#include <cpu.h>
#include <vm.h>
#include <ipc.h>

long int hypercall(unsigned long id) {
    long int ret = -HC_E_INVAL_ID;

    unsigned long arg1 = vcpu_readreg(cpu()->vcpu, 1);
    unsigned long arg2 = vcpu_readreg(cpu()->vcpu, 2);
    unsigned long arg3 = vcpu_readreg(cpu()->vcpu, 3);

    switch(id){
        case HC_IPC:
            ret = ipc_hypercall(arg1, arg2, arg3);
        break;
        default:
            WARNING("Unknown hypercall id %d", id);
    }

    return ret;
}
