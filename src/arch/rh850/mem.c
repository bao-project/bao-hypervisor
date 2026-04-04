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
    UNUSED_ARG(as);
    UNUSED_ARG(locked);

    return mpu_add_region(mem, false);
}

bool mpu_unmap(struct addr_space* as, struct mp_region* mem)
{
    return mpu_remove_region(as, mem);
}

bool mpu_update(struct addr_space* as, struct mp_region* mpr)
{
    UNUSED_ARG(as);
    UNUSED_ARG(mpr);

    return mpu_update_region(mpr);
}

bool mpu_perms_compatible(unsigned long perms1, unsigned long perms2)
{
    return perms1 == perms2;
}
