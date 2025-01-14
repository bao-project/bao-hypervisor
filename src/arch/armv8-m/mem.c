/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <list.h>
#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <arch/mpu.h>
#include <arch/sau.h>

void as_arch_init(struct addr_space* as)
{
    UNUSED_ARG(as);
}

bool mpu_map(struct addr_space* as, struct mp_region* mpr)
{
    bool failed = true;

    if (as == &cpu()->as) {
        /* Add region to MPU */
        if (!mpu_add_region(mpr)) {
            ERROR("failed to register mpu entry");
        } else {
            failed = false;
        }
    } else {
        if (as == &cpu()->vcpu->vm->as) {
            /* Add region to SAU  */
            if (!sau_add_region(mpr)) {
                ERROR("failed to register sau entry");
            } else {
                failed = false;
            }
        }
    }

    return !failed;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mpr)
{
    bool failed = true;

    if (as == &cpu()->as) {
        /* Remove region */
        if (!mpu_remove_region(mpr)) {
            ERROR("failed to register mpu entry");
        } else {
            failed = false;
        }
    } else {
        if (as == &cpu()->vcpu->vm->as) {
            /* Remove region */
            if (!sau_remove_region(mpr)) {
                ERROR("failed to register sau entry");
            } else {
                failed = false;
            }
        }
    }

    return !failed;
}

void mpu_init(void)
{
    mpu_arch_init();
}
