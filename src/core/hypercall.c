/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <hypercall.h>
#include <kconfig.h>

long int hypercall(unsigned long id)
{
    long int ret = -HC_E_INVAL_ID;

    switch (id) {
        case HC_IPC:
            ret = ipc_hypercall();
            break;
#if CONFIG_REMIO
        case HC_REMIO:
            ret = remio_hypercall();
            break;
#endif
        default:
            WARNING("Unknown hypercall id %d\n", id);
    }

    return ret;
}
