/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <hypercall.h>

long int hypercall(unsigned long id)
{
    long int ret = -HC_E_INVAL_ID;

    switch (id) {
        case HC_IPC:
            ret = ipc_hypercall();
            break;
        case HC_REMIO:
            ret = remio_hypercall();
            break;
        default:
            WARNING("Unknown hypercall id %d", id);
    }

    return ret;
}
