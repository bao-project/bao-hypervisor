/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

static inline size_t mpu_num_entries(void)
{
    return 0;
}

static void mpu_entry_get_region(mpid_t mpid, struct mp_region* mpe)
{
    UNUSED_ARG(mpid);
    UNUSED_ARG(mpe);
}

static int mpu_node_cmp(node_t* _n1, node_t* _n2)
{
    UNUSED_ARG(_n1);
    UNUSED_ARG(_n2);

    return 0;
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    UNUSED_ARG(mpid);
    UNUSED_ARG(mpr);
}

static void mpu_entry_modify(mpid_t mpid, struct mp_region* mpr)
{
    UNUSED_ARG(mpid);
    UNUSED_ARG(mpr);
}

static bool mpu_entry_clear(mpid_t mpid)
{
    UNUSED_ARG(mpid);
    return false;
}

static inline void mpu_entry_free(mpid_t mpid)
{
    UNUSED_ARG(mpid);
}

static inline bool mpu_entry_valid(mpid_t mpid)
{
    UNUSED_ARG(mpid);
    return false;
}

static inline bool mpu_entry_locked(mpid_t mpid)
{
    UNUSED_ARG(mpid);
    return false;
}

static bool mpu_entry_has_priv(mpid_t mpid, priv_t priv)
{
    UNUSED_ARG(mpid);
    UNUSED_ARG(priv);
    return false;
}

static inline perms_t mem_vmpu_entry_perms(struct mp_region* mpr)
{
    UNUSED_ARG(mpr);
    return PERM_NONE;
}

static inline void mpu_entry_set_perms(struct mp_region* mpr, struct mpu_perms mpu_perms)
{
    UNUSED_ARG(mpr);
    UNUSED_ARG(mpu_perms);
}

static void mpu_entry_update_priv_perms(priv_t priv, mpid_t mpid, perms_t perms)
{
    UNUSED_ARG(priv);
    UNUSED_ARG(mpid);
    UNUSED_ARG(perms);
}

static inline bool mpu_perms_equivalent(struct mpu_perms* p1, struct mpu_perms* p2)
{
    UNUSED_ARG(p1);
    UNUSED_ARG(p2);
    return false;
}

static inline mem_attrs_t mpu_entry_attrs(struct mp_region* mpr)
{
    UNUSED_ARG(mpr);
    return 0;
}

static mpid_t mpu_entry_allocate(void)
{
    return INVALID_MPID;
}

bool mpu_map(priv_t priv, struct mp_region* mpr)
{
    UNUSED_ARG(priv);
    UNUSED_ARG(mpr);
    return false;
}

bool mpu_unmap(priv_t priv, struct mp_region* mpr)
{
    UNUSED_ARG(priv);
    UNUSED_ARG(mpr);
    return false;
}

void mpu_init(void) { }
