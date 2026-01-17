/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <arch/mpu.h>

void as_arch_init(struct addr_space* as)
{
    UNUSED_ARG(as);
}

void mpu_init(void)
{
    mpu_arch_init();
}

void mpu_enable(void)
{
    mpu_arch_enable();
}

bool mpu_map(struct addr_space* as, struct mp_region* mem, bool locked)
{
    bool failed = true;
    UNUSED_ARG(as);
    UNUSED_ARG(locked);

    /* Add region to MPU */
    if (!mpu_add_region(mem, false)) {
        ERROR("failed to register mpu entry");
    } else {
        failed = false;
    }
    return !failed;
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mem)
{
    bool failed = true;
    UNUSED_ARG(as);

    if (!mpu_remove_region(mem)) {
        ERROR("failed to register mpu entry");
    } else {
        failed = false;
    }

    return !failed;
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    bool failed = true;
    UNUSED_ARG(as);

    /* Remove region */
    if (!mpu_update_region(mpr)) {
        ERROR("failed to register mpu entry");
    } else {
        failed = false;
    }

    return !failed;
}

bool mpu_perms_compatible(uint32_t perms1, uint32_t perms2)
{
    return perms1 == perms2;
}
