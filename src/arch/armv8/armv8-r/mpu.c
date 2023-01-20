/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

static inline const size_t mpu_num_entries()
{
    return (size_t) MPUIR_REGION(sysreg_mpuir_el2_read());
}

static void mpu_entry_get_region(mpid_t mpid, struct mp_region *mpe)
{
    sysreg_prselr_el2_write(mpid);
    ISB();
    unsigned long prbar = sysreg_prbar_el2_read ();
    unsigned long prlar = sysreg_prlar_el2_read();
    mpe->mem_flags.prbar = PRBAR_FLAGS(prbar);
    mpe->mem_flags.prlar = PRLAR_FLAGS(prlar);
    mpe->base = PRBAR_BASE(prbar);
    mpe->size = (PRLAR_LIMIT(prlar) + 1) - mpe->base;
    mpe->as_sec = SEC_UNKNOWN;
}

static int mpu_node_cmp(node_t* _n1, node_t* _n2) {
    struct mpu_node *n1 = (struct mpu_node*) _n1;
    struct mpu_node *n2 = (struct mpu_node*) _n2;
    struct mp_region r1;
    struct mp_region r2;
    mpu_entry_get_region(n1->mpid, &r1);
    mpu_entry_get_region(n2->mpid, &r2);
    if (r1.base > r2.base) {
        return 1;
    } else if (r1.base < r2.base) {
        return -1;
    } else {
        return 0;
    }
}

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr) {
    unsigned long lim = mpr->base + mpr->size - 1;
    
    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prbar_el2_write((mpr->base & PRBAR_BASE_MSK) | 
                            mpr->mem_flags.prbar);
    sysreg_prlar_el2_write((lim & PRLAR_LIMIT_MSK) | mpr->mem_flags.prlar);

    list_insert_ordered(&cpu()->arch.profile.mpu.order.list, 
        (node_t*)&cpu()->arch.profile.mpu.order.node[mpid],
        mpu_node_cmp);
}

static void mpu_entry_modify(mpid_t mpid, struct mp_region* mpr) {

    list_rm(&cpu()->arch.profile.mpu.order.list, 
        (node_t*)&cpu()->arch.profile.mpu.order.node[mpid]);

    mpu_entry_set(mpid, mpr);
}

static bool mpu_entry_clear(mpid_t mpid)
{
    list_rm(&cpu()->arch.profile.mpu.order.list, 
        (node_t*)&cpu()->arch.profile.mpu.order.node[mpid]);

    sysreg_prselr_el2_write(mpid);
    ISB();
    sysreg_prlar_el2_write(0);
    sysreg_prbar_el2_write(0);
    return true;
}

static inline void mpu_entry_free(mpid_t mpid)
{
    mpu_entry_clear(mpid);
    bitmap_clear(cpu()->arch.profile.mpu.bitmap, mpid);
}

static inline bool mpu_entry_valid(mpid_t mpid) {
    sysreg_prselr_el2_write(mpid);
    ISB();
    return !!(sysreg_prlar_el2_read() & PRLAR_EN);
}

static inline bool mpu_entry_locked(mpid_t mpid) {
    return !!bitmap_get(cpu()->arch.profile.mpu.locked, mpid);
}

static bool mpu_entry_has_priv(mpid_t mpid, priv_t priv) {
    if (priv == PRIV_VM) {
        return cpu()->arch.profile.mpu.perms[mpid].el1 != PERM_NONE;
    } else {
        return cpu()->arch.profile.mpu.perms[mpid].el2 != PERM_NONE;
    }
}

static inline perms_t mem_vmpu_entry_perms(struct mp_region *mpr) {
    perms_t perms = PERM_R;
    perms |= !(mpr->mem_flags.prbar & PRBAR_XN) ? PERM_X : 0;
    perms |= !(mpr->mem_flags.prbar & PRBAR_NWR_BIT) ? PERM_W : 0;
    return perms;
}

static inline void mpu_entry_set_perms(struct mp_region *mpr,
    struct mpu_perms mpu_perms)
{
    // TODO: should we check this is following the allowed permission
    // combinations?

    bool el1_priv = mpu_perms.el1 != PERM_NONE;
    perms_t perms = mpu_perms.el1 | mpu_perms.el2;

    mpr->mem_flags.prbar &= ~(PRBAR_PERMS_FLAGS_MSK);
    if (perms & PERM_W) {
        mpr->mem_flags.prbar |= PRBAR_AP_RW_EL2;
    } else {
        mpr->mem_flags.prbar |= PRBAR_AP_RO_EL2;
    }

    if (!(perms & PERM_X)) {
        mpr->mem_flags.prbar |= PRBAR_XN;
    }

    if (el1_priv) {
        mpr->mem_flags.prbar |= PRBAR_EL1_BIT;
    }
}

static void mpu_entry_update_priv_perms(priv_t priv, mpid_t mpid, perms_t perms) 
{
    if (priv == PRIV_VM) {
        cpu()->arch.profile.mpu.perms[mpid].el1 = perms;
    } else {
        cpu()->arch.profile.mpu.perms[mpid].el2 = perms;
    }
}

static inline bool mpu_perms_equivalent(struct mpu_perms *p1, struct mpu_perms *p2)
{
    return (p1->el1 == p2->el1) && (p1->el2 == p2->el2);
}

static inline mem_attrs_t mpu_entry_attrs(struct mp_region *mpr) {
    mem_flags_t flags = mpr->mem_flags;
    flags.prbar &= PRBAR_MEM_ATTR_FLAGS_MSK;
    flags.prbar &= PRLAR_MEM_ATTR_FLAGS_MSK;
    return (mem_attrs_t) flags.raw;
}

static mpid_t mpu_entry_allocate()
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < mpu_num_entries(); i++) {
        if (bitmap_get(cpu()->arch.profile.mpu.bitmap, i) == 0) {
            bitmap_set(cpu()->arch.profile.mpu.bitmap, i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

bool mem_region_get_overlap(struct mp_region *reg1,  struct mp_region *reg2,
    struct mp_region *overlap)
{
    bool regions_overlap = mem_regions_overlap(reg1, reg2);

    if (regions_overlap) {
        vaddr_t reg1_lim = (reg1->base + reg1->size);
        vaddr_t reg2_lim = (reg2->base + reg2->size);
        vaddr_t base = reg2->base > reg1->base ? reg2->base : reg1->base;
        vaddr_t lim = reg2_lim > reg1_lim ? reg1_lim : reg2_lim;

        overlap->base = base;
        overlap->size = lim - base;
    }

    return regions_overlap;
}


bool mpu_map(priv_t priv, struct mp_region* mpr)
{
    size_t size_left = mpr->size;
    bool failed = false;
    struct mp_region reg1 = *mpr;
    struct mp_region reg2 = *mpr;
    bool reg1_valid = true;
    bool reg2_valid = false;
    mpid_t prev = INVALID_MPID;
    mpid_t next = INVALID_MPID;
    mpid_t bottom_mpid = INVALID_MPID;
    mpid_t top_mpid = INVALID_MPID;

    while (size_left > 0 && !failed) {

        /**
         * Since we'll be checking for overlapping regions in order, there
         * will be at most two regions to map in a given iteration. This
         * happens when the previous iteration found an overlapping region
         * that is fully contained by the new region.
         */

        struct mp_region *new_reg;
        if (reg1_valid) {
            new_reg = &reg1;
        } else if (reg2_valid) {
            new_reg = &reg2;
        } else {
            break;
        }

        // As Armv8-R does not allow overlapping regions, we must first check
        // if usch regions already exist. Specifically, for the case where the
        // regions has hypervisor permissions only, and this is a map
        // targetting a guest mpu, we just need to flip the guest permission
        // bit. This will allow us to share regions between guest and hypevisor
        // to, for example, (i) share the use of a peripheral (mainly uart for
        // debugging purposes), or (ii) share a RW page between hypervisor and
        // guest. Although having a RO page for guest while RW for the
        // hypervisor is highly useful, this MPU does not allow it. That said,
        // in the case we need it in the future, we'll have to implement a
        // mechanism for that based on traps.

        bool overlaped = false;
        perms_t new_perms = mem_vmpu_entry_perms(new_reg);

        prev = INVALID_MPID;
        next = INVALID_MPID;
        bottom_mpid = INVALID_MPID;
        top_mpid = INVALID_MPID;

        struct list *mpu_order_list = &cpu()->arch.profile.mpu.order.list;
        list_foreach((*mpu_order_list), struct mpu_node, entry) {

            mpid_t mpid = entry->mpid;
            struct mp_region overlapped_reg;

            mpu_entry_get_region(mpid, &overlapped_reg);

            if ((new_reg->base + new_reg->size) <= overlapped_reg.base) {
                next = mpid;
                break; 
            }

            if (!mem_regions_overlap(new_reg, &overlapped_reg)) {
                // If we are not overlapping, continue to search for overlapped
                // regions until we check all entries. This should be the most
                // frequent case, so the overhead for the checks on overllap
                // will rarely execute.
                prev = mpid;
                continue;
            }
            overlaped = true;

            if (mpu_entry_has_priv(mpid, priv)) {
                // We don't allow overlapping regions of the same privilege.
                // This is something that should be checked at the vmpu level,
                // but we re-check it here anyway.
                failed = true;
                break;
            }

            // We only allow to bump up permissions if the overlapped region
            // is a RO hypervisor region. Otherwise permissions have to be
            // RW in both regions. We don't allow to overlap executable regions.
            struct mpu_perms overlapped_perms = cpu()->arch.profile.mpu.perms[mpid];
            struct mpu_perms overlap_perms = overlapped_perms;
            priv_t overlapped_priv;
            perms_t overlapped_perms2;
            if (priv == PRIV_VM) {
                overlap_perms.el1 = new_perms;
                overlapped_priv = PRIV_HYP;
                overlapped_perms2 = overlapped_perms.el2;
            } else {
                overlap_perms.el2 = new_perms;
                overlapped_priv = PRIV_VM;
                overlapped_perms2 = overlapped_perms.el1;
            }

            if (((overlap_perms.el1 & PERM_RW) == PERM_R) &&
                ((overlap_perms.el2 & PERM_W) != PERM_NONE))
            {
                // We allow promoting read/write privielges of the hypervisor 
                // region to match the guest's. However, this combination 
                // promotes the guest privielges, which we don't allow.
                failed = true;
                break;
            }

            if ((overlap_perms.el1 & PERM_X) != (overlap_perms.el2 & PERM_X))
            {
                // Unless explicitly mapped, we don't promote execution privileges.
                failed = true;
                break;
            }  

            // The Armv8-R MPU does not allow us to have different permissions
            // for hypervisor and guest. So we must fail if asked to add an
            // overlapping mapping with different permissions or attributes
            if (mpu_entry_attrs(new_reg) != mpu_entry_attrs(&overlapped_reg)) {
                failed = true;
                break;
            }

            vaddr_t new_reg_limit = new_reg->base + new_reg->size;
            vaddr_t overlapped_reg_limit = 
                overlapped_reg.base + overlapped_reg.size;
            size_t top_size = new_reg_limit >= overlapped_reg_limit ? 0 : 
                overlapped_reg_limit - new_reg_limit;
            size_t bottom_size = new_reg->base <= overlapped_reg.base ? 
                0 : new_reg->base - overlapped_reg.base;
            size_t top_left = new_reg_limit <= overlapped_reg_limit ? 0 : 
                new_reg_limit - overlapped_reg_limit;
            size_t bottom_left = new_reg->base >= overlapped_reg.base ?
                0 : overlapped_reg.base - new_reg->base;
            bool subset = (new_reg->base >= overlapped_reg.base) && 
                (new_reg_limit <= overlapped_reg_limit);
            bool superset = (bottom_left > 0) || (top_left > 0);

            struct mp_region middle;
            middle.size = overlapped_reg.size - (top_size + bottom_size);
            middle.base = overlapped_reg.base + bottom_size;
            middle.mem_flags = overlapped_reg.mem_flags; // copy attributes
            mpu_entry_set_perms(&middle, overlap_perms);

            if (bottom_size > 0) {
                bottom_mpid = mpu_entry_allocate();
                if(bottom_mpid == INVALID_MPID) {
                    failed = true;
                    break;
                }
            }
            
            if (top_size > 0) {
                top_mpid = mpu_entry_allocate();
                if(top_mpid == INVALID_MPID) {
                    failed = true;
                    break;
                }
            }

            mpu_entry_update_priv_perms(priv, mpid, new_perms);
            mpu_entry_modify(mpid, &middle);
            
            if (bottom_size > 0) {
                struct mp_region bottom;
                bottom.base = overlapped_reg.base;
                bottom.size = bottom_size;
                bottom.mem_flags = overlapped_reg.mem_flags; // copy attrs
                mpu_entry_set_perms(&bottom, overlapped_perms);
                mpu_entry_update_priv_perms(overlapped_priv, bottom_mpid, overlapped_perms2);
                mpu_entry_set(bottom_mpid, &bottom);
            }

            if (top_size > 0) {
                struct mp_region top;
                top.base = new_reg_limit;
                top.size = top_size;
                top.mem_flags = overlapped_reg.mem_flags; // copy attrs
                mpu_entry_set_perms(&top, overlapped_perms);
                mpu_entry_update_priv_perms(overlapped_priv, top_mpid, overlapped_perms2);
                mpu_entry_set(top_mpid, &top);
            }

            if (bottom_left > 0) {
                reg1_valid = true;
                reg1.base = new_reg->base;
                reg1.size = bottom_left;
            } else {
                reg1_valid = false;
            }

            if (top_left > 0) {
                reg2_valid = true;
                reg2.base = overlapped_reg_limit;
                reg2.size = top_left;
            } else {
                reg2_valid = true;
            }

            if (superset) {
                size_left = (top_left + bottom_left);
            } else if (subset) {
                size_left = 0;
            } else  {
                size_left -= middle.size;
            }

            break;
        }

        if (!overlaped && !failed) {

            mpid_t merge_mpid = INVALID_MPID;
            size_t mem_size = new_reg->size;
            struct mpu_perms *prev_perms = &cpu()->arch.profile.mpu.perms[prev];
            struct mpu_perms *next_perms = &cpu()->arch.profile.mpu.perms[next];
            struct mpu_perms new_reg_perms;
            if (priv == PRIV_VM) {
                new_reg_perms.el1 = new_perms;
                new_reg_perms.el2 = PERM_NONE;
            } else {
                new_reg_perms.el1 = PERM_NONE;
                new_reg_perms.el2 = new_perms;
            }

            /**
             * Check if we can merge the current region with the region
             * right before and/or right after. This can only be done if
             * they are adjacent and have the same exect flags (i.e. 
             * permissions and memory attribtues).
             */

            if ((prev != INVALID_MPID) && !mpu_entry_locked(prev)) {
                struct mp_region r;
                mpu_entry_get_region(prev, &r);
                if (((r.base + r.size) == new_reg->base) &&
                    (mpu_entry_attrs(&r) == mpu_entry_attrs(new_reg)) &&
                    (mpu_perms_equivalent(prev_perms, &new_reg_perms)))
                {
                    merge_mpid = prev;
                    new_reg->base = r.base;
                    new_reg->size += r.size;
                }
            }

            if ((next != INVALID_MPID) && !mpu_entry_locked(next)) {
                struct mp_region r;
                mpu_entry_get_region(next, &r);
                if ((new_reg->base + new_reg->size) == r.base &&
                    (mpu_entry_attrs(&r) == mpu_entry_attrs(new_reg)) &&
                    (mpu_perms_equivalent(next_perms, &new_reg_perms)))
                {
                    if (merge_mpid == INVALID_MPID) {
                        merge_mpid = next;
                    } else {
                        mpu_entry_free(next);
                    }
                    new_reg->size += r.size;
                }
            }

            /**
             * If we can merge the region do it. Otherwise, allocate a new
             * entry and set it.
             */
            if (merge_mpid != INVALID_MPID) {
                mpu_entry_update_priv_perms(priv, merge_mpid, new_perms);
                mpu_entry_modify(merge_mpid, new_reg);
            } else {
                mpid_t mpid = mpu_entry_allocate();
                if (mpid == INVALID_MPID) {
                    ERROR("failed to allocate mpu entry");
                }
                mpu_entry_update_priv_perms(priv, mpid, new_perms);
                mpu_entry_set(mpid, new_reg);
            }
            size_left -= mem_size;
        }
    }

    if (failed) {
        if (bottom_mpid != INVALID_MPID) {
            mpu_entry_free(bottom_mpid);
        }

        if (top_mpid != INVALID_MPID) {
            mpu_entry_free(top_mpid);
        }
    }

    return !failed;
}

bool mpu_unmap(priv_t priv, struct mp_region* mpr)
{   
    size_t size_left = mpr->size;

    while(size_left > 0) {

        mpid_t mpid = INVALID_MPID;
        struct mp_region reg;

        struct list *mpu_order_list = &cpu()->arch.profile.mpu.order.list;
        list_foreach((*mpu_order_list), struct mpu_node, entry) {
            mpu_entry_get_region(entry->mpid, &reg);

            if ((mpr->base + mpr->size) < reg.base) {
                break;
            }

            if (!mpu_entry_has_priv(entry->mpid, priv)) {
                continue;
            }

            if (mem_regions_overlap(&reg, mpr)) {
                mpid = entry->mpid;
                break;
            }
        }

        if (mpid == INVALID_MPID) {
            break;
        }

        vaddr_t mpr_limit = mpr->base + mpr->size;
        vaddr_t reg_limit = reg.base + reg.size;
        size_t top_size = mpr_limit >= reg_limit ? 0 : reg_limit - mpr_limit;
        size_t bottom_size = mpr->base <= reg.base ? 0 : mpr->base -reg.base;
        struct mpu_perms orig_perms = cpu()->arch.profile.mpu.perms[mpid];

        mpu_entry_update_priv_perms(priv, mpid, PERM_NONE);
        bool update_perms = 
            !((cpu()->arch.profile.mpu.perms[mpid].el1 == PERM_NONE) &&
            (cpu()->arch.profile.mpu.perms[mpid].el2 == PERM_NONE));

        if (update_perms) {
            struct mp_region update_reg = reg;
            update_reg.base = bottom_size > 0 ? mpr->base : reg.base;
            update_reg.size = reg.size - top_size - bottom_size;
            mpu_entry_set_perms(&update_reg, cpu()->arch.profile.mpu.perms[mpid]);
            mpu_entry_modify(mpid, &update_reg);
        } else {
            mpu_entry_free(mpid);
        }

        if (top_size > 0) {
            struct mp_region top = reg;
            top.base = mpr_limit;
            top.size = top_size;
            mpid_t top_mpid = mpu_entry_allocate();
            cpu()->arch.profile.mpu.perms[top_mpid] = orig_perms;
            mpu_entry_set(top_mpid, &top);
        }

        if (bottom_size > 0) {
            struct mp_region bottom = reg;
            bottom.size = bottom_size;
            mpid_t bottom_mpid = mpu_entry_allocate();
            cpu()->arch.profile.mpu.perms[bottom_mpid] = orig_perms;
            mpu_entry_set(bottom_mpid, &bottom);
        }

        size_t overlap_size = reg.size - top_size - bottom_size;
        size_left -= overlap_size;

    }

    // TODO: check if we can merge new regions after unmapping a given
    // privilege from a shared region

    return size_left == 0;
}

void mpu_init() {

    bitmap_clear_consecutive(cpu()->arch.profile.mpu.bitmap, 0, mpu_num_entries());
    list_init(&cpu()->arch.profile.mpu.order.list);

    for (mpid_t mpid = 0; mpid < mpu_num_entries(); mpid++) {

        cpu()->arch.profile.mpu.order.node[mpid].mpid = mpid;
        
        if (mpu_entry_valid(mpid)) {

            bitmap_set(cpu()->arch.profile.mpu.bitmap, mpid);
            bitmap_set(cpu()->arch.profile.mpu.locked, mpid);

            /**
             * We are assuming all initial regions have all hyp perms.
             * This might change in the future.
             */
            cpu()->arch.profile.mpu.perms[mpid].el1 = PERM_NONE;
            cpu()->arch.profile.mpu.perms[mpid].el2 = PERM_RWX;

            list_insert_ordered(&cpu()->arch.profile.mpu.order.list, 
                (node_t*)&cpu()->arch.profile.mpu.order.node[mpid],
                mpu_node_cmp);
        }

    }
}
