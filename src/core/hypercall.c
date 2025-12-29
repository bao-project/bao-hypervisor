/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 * 
 * @file hypercall.c
 * @brief This source file contains the definition of the hypervisor call.
 * 
 */

#include <hypercall.h>

/**
 * @brief Handle hypervisor calls from VMs
 *
 * Routes hypercalls to their specific handlers based on the call ID.
 * Currently supports IPC and remote I/O operations.
 *
 * @param id Hypercall identifier (HC_IPC, HC_REMIO, etc.)
 * @return long int 0 on success, negative error code on failure.
 *         -HC_E_INVAL_ID for unknown hypercall IDs
 * 
 * @see ipc_hypercall(), remio_hypercall(), WARNING(), HC_IPC, HC_REMIO, HC_E_INVAL_ID
 */
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
