/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VIMSIC_H
#define VIMSIC_H

#include <bao.h>

/**
 * @brief Maps the guest IMSIC addresses into the physical IMSIC adresses
 *
 *        Guest's VCPUs assume no indexation order, e.g., VCPU 0 can map to CPU 2. This mapping
 *        occurs at run-time (during bao initialization), therefore, also the IMSIC mapping needs to
 *        be done at initialization time.
 *        The vimsic_init function needs to be executed by every VM's virtual CPU. Then, it will
 *        calculate the physical IMSIC address based on the physical CPU into which the VCPU is
 *        mapped. Finally, it adds a new entry in the MMU.
 *
 * @param vm Virtual Machine
 * @param vm_irqc_dscrp Virtual Machine Description
 */
void vimsic_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp);

#endif // VIMSIC_H
