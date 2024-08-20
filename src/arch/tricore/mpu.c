/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include "types.h"
#include <mem.h>
#include <cpu.h>
#include <arch/sysregs.h>
#include <arch/fences.h>

#define VM_PSR (1)
#define HYP_PSR (0)

static inline size_t mpu_num_entries()
{
    /* TODO separate data and code region */
    /* TODO for now we will consider code and data as one */
    return (size_t)16;
}

/* Protection Range Registers */

#define CSR_GEN_PRx(x)                                                             \
    static inline unsigned long csr_get_dpr##x##_l(void)                           \
    {                                                                              \
        unsigned long val;                                                         \
        asm inline("mfcsr %d[reg], HRVH_DPR"STR(x)"_L\n\t" [reg] "=d" (val) : : );      \
        return val;                                                                \
    }                                                                              \
    static inline unsigned long csr_get_dpr##x##_u(void)                           \
    {                                                                              \
        unsigned long val;                                                         \
        asm inline("mfcsr %d[reg], HRVH_DPR"STR(x)"_U\n\t" [reg] "=d" (val) : : );      \
        return val;                                                                \
    }                                                                              \
    static inline unsigned long csr_get_cpr##x##_l(void)                           \
    {                                                                              \
        unsigned long val;                                                         \
        asm inline("mfcsr %d[reg], HRVH_CPR"STR(x)"_L\n\t" [reg] "=d" (val) : : );      \
        return val;                                                                \
    }                                                                              \
    static inline unsigned long csr_get_cpr##x##_u(void)                           \
    {                                                                              \
        unsigned long val;                                                         \
        asm inline("mfcsr %d[reg], HRVH_CPR"STR(x)"_U\n\t" [reg] "=d" (val) : : );      \
        return val;                                                                \
    }                                                                              \
    static inline unsigned long csr_set_dpr##x##_l(unsigned long val)              \
    {                                                                              \
        asm inline("mtcsr HRVH_DPR"STR(x)"_L, %d[reg]\n\t" [reg] : "d" (val) : );  \
    }                                                                              \
    static inline unsigned long csr_set_dpr##x##_u(unsigned long val)              \
    {                                                                              \
        asm inline("mtcsr HRVH_DPR"STR(x)"_U, %d[reg]\n\t" [reg] : "d" (val) : );  \
    }                                                                              \
    static inline unsigned long csr_set_cpr##x##_l(unsigned long val)              \
    {                                                                              \
        asm inline("mtcsr HRVH_CPR"STR(x)"_L, %d[reg]\n\t" [reg] : "d" (val) : );  \
    }                                                                              \
    static inline unsigned long csr_set_cpr##x##_u(unsigned long val)              \
    {                                                                              \
        asm inline("mtcsr HRVH_CPR"STR(x)"_U, %d[reg]\n\t" [reg] : "d" (val) : );  \
    }


CSR_GEN_PRx(0)
CSR_GEN_PRx(1)
CSR_GEN_PRx(2)
CSR_GEN_PRx(3)
CSR_GEN_PRx(4)
CSR_GEN_PRx(5)
CSR_GEN_PRx(6)
CSR_GEN_PRx(7)
CSR_GEN_PRx(8)
CSR_GEN_PRx(9)
CSR_GEN_PRx(10)
CSR_GEN_PRx(11)
CSR_GEN_PRx(12)
CSR_GEN_PRx(13)
CSR_GEN_PRx(14)
CSR_GEN_PRx(15)
CSR_GEN_PRx(16)
CSR_GEN_PRx(17)
CSR_GEN_PRx(18)
CSR_GEN_PRx(19)
CSR_GEN_PRx(20)
CSR_GEN_PRx(21)
CSR_GEN_PRx(22)
CSR_GEN_PRx(23)
CSR_GEN_PRx(24)
CSR_GEN_PRx(25)
CSR_GEN_PRx(26)
CSR_GEN_PRx(27)
CSR_GEN_PRx(28)
CSR_GEN_PRx(29)
CSR_GEN_PRx(30)
CSR_GEN_PRx(31)


#define CSR_GEN_PR_ACCESSOR(m, r)                                                    \
    static inline unsigned long csr_get_##m##pr_##r##(mpid_t id)                     \
    {                                                                                \
        switch(id){                                                                  \
            case 0: return csr_get_##m##pr0_##r##();                                 \
            case 1: return csr_get_##m##pr1_##r##();                                 \
            case 2: return csr_get_##m##pr2_##r##();                                 \
            case 3: return csr_get_##m##pr3_##r##();                                 \
            case 4: return csr_get_##m##pr4_##r##();                                 \
            case 5: return csr_get_##m##pr5_##r##();                                 \
            case 6: return csr_get_##m##pr6_##r##();                                 \
            case 7: return csr_get_##m##pr7_##r##();                                 \
            case 8: return csr_get_##m##pr8_##r##();                                 \
            case 9: return csr_get_##m##pr9_##r##();                                 \
            case 10: return csr_get_##m##pr10_##r##();                               \
            case 11: return csr_get_##m##pr11_##r##();                               \
            case 12: return csr_get_##m##pr12_##r##();                               \
            case 13: return csr_get_##m##pr13_##r##();                               \
            case 14: return csr_get_##m##pr14_##r##();                               \
            case 15: return csr_get_##m##pr15_##r##();                               \
            case 16: return csr_get_##m##pr16_##r##();                               \
            case 17: return csr_get_##m##pr17_##r##();                               \
            case 18: return csr_get_##m##pr18_##r##();                               \
            case 19: return csr_get_##m##pr19_##r##();                               \
            case 20: return csr_get_##m##pr20_##r##();                               \
            case 21: return csr_get_##m##pr21_##r##();                               \
            case 22: return csr_get_##m##pr22_##r##();                               \
            case 23: return csr_get_##m##pr23_##r##();                               \
            case 24: return csr_get_##m##pr24_##r##();                               \
            case 25: return csr_get_##m##pr25_##r##();                               \
            case 26: return csr_get_##m##pr26_##r##();                               \
            case 27: return csr_get_##m##pr27_##r##();                               \
            case 28: return csr_get_##m##pr28_##r##();                               \
            case 29: return csr_get_##m##pr29_##r##();                               \
            case 30: return csr_get_##m##pr30_##r##();                               \
            case 31: return csr_get_##m##pr31_##r##();                               \
        }                                                                            \
    }                                                                                \
    static inline unsigned long csr_set_##m##pr_##r##(mpid_t id, unsigned long val)  \
    {                                                                                \
        switch(id){                                                                  \
            case 0: return csr_set_##m##pr0_##r##(val);                              \
            case 1: return csr_set_##m##pr1_##r##(val);                              \
            case 2: return csr_set_##m##pr2_##r##(val);                              \
            case 3: return csr_set_##m##pr3_##r##(val);                              \
            case 4: return csr_set_##m##pr4_##r##(val);                              \
            case 5: return csr_set_##m##pr5_##r##(val);                              \
            case 6: return csr_set_##m##pr6_##r##(val);                              \
            case 7: return csr_set_##m##pr7_##r##(val);                              \
            case 8: return csr_set_##m##pr8_##r##(val);                              \
            case 9: return csr_set_##m##pr9_##r##(val);                              \
            case 10: return csr_set_##m##pr10_##r##(val);                            \
            case 11: return csr_set_##m##pr11_##r##(val);                            \
            case 12: return csr_set_##m##pr12_##r##(val);                            \
            case 13: return csr_set_##m##pr13_##r##(val);                            \
            case 14: return csr_set_##m##pr14_##r##(val);                            \
            case 15: return csr_set_##m##pr15_##r##(val);                            \
            case 16: return csr_set_##m##pr16_##r##(val);                            \
            case 17: return csr_set_##m##pr17_##r##(val);                            \
            case 18: return csr_set_##m##pr18_##r##(val);                            \
            case 19: return csr_set_##m##pr19_##r##(val);                            \
            case 20: return csr_set_##m##pr20_##r##(val);                            \
            case 21: return csr_set_##m##pr21_##r##(val);                            \
            case 22: return csr_set_##m##pr22_##r##(val);                            \
            case 23: return csr_set_##m##pr23_##r##(val);                            \
            case 24: return csr_set_##m##pr24_##r##(val);                            \
            case 25: return csr_set_##m##pr25_##r##(val);                            \
            case 26: return csr_set_##m##pr26_##r##(val);                            \
            case 27: return csr_set_##m##pr27_##r##(val);                            \
            case 28: return csr_set_##m##pr28_##r##(val);                            \
            case 29: return csr_set_##m##pr29_##r##(val);                            \
            case 30: return csr_set_##m##pr30_##r##(val);                            \
            case 31: return csr_set_##m##pr31_##r##(val);                            \
        }                                                                            \
    }

/* data */
#define CSR_GEN_PR_ACCESSOR(d, u)
#define CSR_GEN_PR_ACCESSOR(d, l)
/* code */
#define CSR_GEN_PR_ACCESSOR(c, u)
#define CSR_GEN_PR_ACCESSOR(c, l)

void get_pr_l(mpid_t mpid)
{
    /* cpr and dpr refer to the same region */
    csr_get_cpr_l(mpid);
}

void get_pr_u(mpid_t mpid)
{
    /* cpr and dpr refer to the same region */
    csr_get_cpr_u(mpid);
}

void set_pr_l(mpid_t mpid, unsigned long addr)
{
    /* make cpr and dpr refer to the same region */
    csr_set_cpr_l(mpid, addr);
    csr_set_dpr_l(mpid, addr);
}

void set_pr_u(mpid_t mpid, unsigned long addr)
{
    /* make cpr and dpr refer to the same region */
    csr_set_cpr_u(mpid, addr);
    csr_set_dpr_u(mpid, addr);
}

/* Protection Read/Write/Execute Enable Registers */

#define CSR_GEN_Px(x)                                                            \
    static inline unsigned long csr_get_dpre##x##(mpid_t id)                     \
    {                                                                            \
        unsigned long val;                                                       \
        asm inline("mfcsr %d[reg], DPRE_"STR(x)"\n\t" [reg] "=d" (val) : : );    \
        return val & (1 << id);                                                  \
    }                                                                            \
    static inline unsigned long csr_get_dpwe##x##(mpid_t id)                     \
    {                                                                            \
        unsigned long val;                                                       \
        asm inline("mfcsr %d[reg], DPWE_"STR(x)"\n\t" [reg] "=d" (val) : : );    \
        return val & (1 << id);                                                  \
    }                                                                            \
    static inline unsigned long csr_get_cpxe##x##(mpid_t id)                     \
    {                                                                            \
        unsigned long val;                                                       \
        asm inline("mfcsr %d[reg], CPXE_"STR(x)"\n\t" [reg] "=d" (val) : : );    \
        return val & (1 << id);                                                  \
    }                                                                            \
    static inline unsigned long csr_set_dpre##x##(mpid_t id, unsigned long val)  \
    {                                                                            \
        asm inline("mtcsr DPRE_"STR(x)", %d[reg]\n\t" [reg] : "d" (val) : );     \
    }                                                                            \
    static inline unsigned long csr_set_dpwe##x##(mpid_t id, unsigned long val)  \
    {                                                                            \
        asm inline("mtcsr DPRE_"STR(x)", %d[reg]\n\t" [reg] : "d" (val) : );     \
    }                                                                            \
    static inline unsigned long csr_set_cpxe##x##(mpid_t id, unsigned long val)  \
    {                                                                            \
        asm inline("mtcsr DPRE_"STR(x)", %d[reg]\n\t" [reg] : "d" (val) : );     \
    }

CSR_GEN_Px(0)
CSR_GEN_Px(1)
CSR_GEN_Px(2)
CSR_GEN_Px(3)
CSR_GEN_Px(4)
CSR_GEN_Px(5)
CSR_GEN_Px(6)
CSR_GEN_Px(7)

#define GEN_P_ACCESSOR(m)                                                      \
    static inline bool get_##m##(psid_t psid, mpid_t mpid)                     \
    {                                                                          \
        unsigned long val = 0;                                                 \
        switch(psid){                                                          \
            case 0: val = csr_get_##m##0(mpid);                                \
                break;                                                         \
            case 1: val = csr_get_##m##1(mpid);                                \
                break;                                                         \
            case 2: val = csr_get_##m##2(mpid);                                \
                break;                                                         \
            case 3: val = csr_get_##m##3(mpid);                                \
                break;                                                         \
            case 4: val = csr_get_##m##4(mpid);                                \
                break;                                                         \
            case 5: val = csr_get_##m##5(mpid);                                \
                break;                                                         \
            case 6: val = csr_get_##m##6(mpid);                                \
                break;                                                         \
            case 7: val = csr_get_##m##7(mpid);                                \
                break;                                                         \
        }                                                                      \
        return !!(val & (1 << mpid));                                          \
    }                                                                          \
    static inline void set_##m##(psid_t psid, mpid_t mpid, bool val)  \
    {                                                                          \
        switch(psid){                                                          \
            case 0:                                                            \
                unsigned long tmp = csr_get_##m##0(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##0(mpid, val);                              \
            case 1:                                                            \
                unsigned long tmp = csr_get_##m##1(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##1(mpid, val);                              \
            case 2:                                                            \
                unsigned long tmp = csr_get_##m##2(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##2(mpid, val);                              \
            case 3:                                                            \
                unsigned long tmp = csr_get_##m##3(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##3(mpid, val);                              \
            case 4:                                                            \
                unsigned long tmp = csr_get_##m##4(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##4(mpid, val);                              \
            case 5:                                                            \
                unsigned long tmp = csr_get_##m##5(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##5(mpid, val);                              \
            case 6:                                                            \
                unsigned long tmp = csr_get_##m##6(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##6(mpid, val);                              \
            case 7:                                                            \
                unsigned long tmp = csr_get_##m##7(mpid);                      \
                if(val)                                                        \
                    tmp |= 1 << mpid;                                          \
                else                                                           \
                    tmp &= ~(1 << mpid);                                       \
                return csr_set_##m##7(mpid, val);                              \
        }                                                                      \
    }

GEN_P_ACCESSOR(dpre)
GEN_P_ACCESSOR(dpwe)
GEN_P_ACCESSOR(cpxe)

static void mpu_entry_get_region(mpid_t mpid, struct mp_region* mpe)
{
    unsigned long l = get_pr_l(mpid);
    unsigned long u = get_pr_u(mpid);

    /* TODO good enough? */
    unsigned long ps = VM_PSR;
    bool exec  = get_cpxe(ps, mpid);
    bool read  = get_dpre(ps, mpid);
    bool write = get_dpwe(ps, mpid);
    if(exec || read || write)
        mpe.mem_flags.el1 = true;

    mpe->mem_flags.exec = exec;
    mpe->mem_flags.read = read;
    mpe->mem_flags.write = write;

    ps = HYP_PSR;
    exec  = get_cpxe(ps, mpid);
    read  = get_dpre(ps, mpid);
    write = get_dpwe(ps, mpid);
    if(exec || read || write)
        mpe.mem_flags.el2 = true;

    mpe->mem_flags.exec ||= exec;
    mpe->mem_flags.read ||= read;
    mpe->mem_flags.write ||= write;

    mpe->base = l;
    mpe->size = u - l;
    mpe->as_sec = SEC_UNKNOWN;
}

static int mpu_node_cmp(node_t* _n1, node_t* _n2)
{
    struct mpu_node* n1 = (struct mpu_node*)_n1;
    struct mpu_node* n2 = (struct mpu_node*)_n2;
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

static void mpu_entry_set(mpid_t mpid, struct mp_region* mpr)
{
    /* TODO */
    unsigned long lim = mpr->base + mpr->size - 1;

    set_pr_l(mpid, mpr->base);
    set_pr_u(mpid, lim);

    unsigned long ps = VM_PSR;
    if(mpr->mem_flags.vm){
        ps = VM_PSR;
        set_cpxe(ps, pmid, mpr->mem_flags.exec);
        set_dpre(ps, pmid, mpr->mem_flags.read);
        set_dpwe(ps, pmid, mpr->mem_flags.write);
    }

    /* TODO this is duplicate code */
    if(mpr->mem_flags.hyp){
        ps = HYP_PSR;
        set_cpxe(ps, pmid, mpr->mem_flags.exec);
        set_dpre(ps, pmid, mpr->mem_flags.read);
        set_dpwe(ps, pmid, mpr->mem_flags.write);
    }

    list_insert_ordered(&cpu()->arch.mpu.order.list,
        (node_t*)&cpu()->arch.mpu.order.node[mpid], mpu_node_cmp);
}

static void mpu_entry_modify(mpid_t mpid, struct mp_region* mpr)
{
    list_rm(&cpu()->arch.mpu.order.list, (node_t*)&cpu()->arch.mpu.order.node[mpid]);

    mpu_entry_set(mpid, mpr);
}

static bool mpu_entry_clear(mpid_t mpid)
{
    list_rm(&cpu()->arch.mpu.order.list, (node_t*)&cpu()->arch.mpu.order.node[mpid]);

    /* TODO */
    /* TODO function that takes ps as input */
    unsigned long ps = VM_PSR;
    set_dpre(ps, mpid, 0);
    set_dpwe(ps, mpid, 0);
    set_cpxe(ps, mpid, 0);

    ps = HYP_PSR;
    set_dpre(ps, mpid, 0);
    set_dpwe(ps, mpid, 0);
    set_cpxe(ps, mpid, 0);

    set_pr_l(mpid, 0);
    set_pr_u(mpid, 0);

    return true;
}

static inline void mpu_entry_free(mpid_t mpid)
{
    mpu_entry_clear(mpid);
    bitmap_clear(cpu()->arch.mpu.bitmap, mpid);
}

static inline bool mpu_entry_valid(mpid_t mpid)
{
    /* TODO there is no valid bit, so we assume if mp size is 0 region is invalid */
    unsigned long l = get_pr_l(mpid);
    unsigned long u = get_pr_u(mpid);
    return l != u;
}

static inline bool mpu_entry_locked(mpid_t mpid)
{
    return !!bitmap_get(cpu()->arch.mpu.locked, mpid);
}

static bool mpu_entry_has_priv(mpid_t mpid, priv_t priv)
{
    if (priv == PRIV_VM) {
        return cpu()->arch.mpu.perms[mpid].el1 != PERM_NONE;
    } else {
        return cpu()->arch.mpu.perms[mpid].el2 != PERM_NONE;
    }
}

static inline perms_t mem_vmpu_entry_perms(struct mp_region* mpr)
{
    /* TODO we need to know the address space */
    unsigned long ps = VM_PSR;
    unsigned long dre = get_dpre(ps, mpid);
    unsigned long dwe = get_dpwe(ps, mpid);
    unsigned long cxe = get_cpxe(ps, mpid);

    ps = HYP_PSR;
    dre |= get_dpre(ps, mpid);
    dwe |= get_dpwe(ps, mpid);
    cxe |= get_cpxe(ps, mpid);

    perms_t perms = cxe ? PERM_X : 0;
    perms | = dre ? PERM_R : 0;
    perms | = dwe ? PERM_W : 0;

    return perms;
}

static inline void mpu_entry_set_perms(struct mp_region* mpr, struct mpu_perms mpu_perms)
{
    bool el1_priv = mpu_perms.el1 != PERM_NONE;
    bool el2_priv = mpu_perms.el2 != PERM_NONE;

    if(el1_priv && el2_priv){
        if(mpu_perms.el1 != mpu_perms.el2)
            ERROR("Permissions for EL1 and EL2 differ for EL1 and EL2 region");
    }
    perms_t perms = mpu_perms.el1 != PERM_NONE ? mpu_perms.el1 : mpu_perms.el2;

    mpr->mem_flags.write = !!(perms & PERM_W);
    mpr->mem_flags.read = !!(perms & PERM_R);
    mpr->mem_flags.exec = !!(perms & PERM_X);

    mpr->mem_flags.vm = el1_priv;
    mpr->mem_flags.hyp = el2_priv;
}

static void mpu_entry_update_priv_perms(priv_t priv, mpid_t mpid, perms_t perms)
{
    if (priv == PRIV_VM) {
        cpu()->arch.mpu.perms[mpid].el1 = perms;
    } else {
        cpu()->arch.mpu.perms[mpid].el2 = perms;
    }
}

static inline bool mpu_perms_equivalent(struct mpu_perms* p1, struct mpu_perms* p2)
{
    return (p1->el1 == p2->el1) && (p1->el2 == p2->el2);
}

static inline bool mpu_entry_attrs_equivalent(struct mp_region* mpr1, struct mp_region* mpr2)
{
    /* TODO make sure it is correct */
    return mpr1->mem_flags == mpr2->mem_flags;
}

static mpid_t mpu_entry_allocate()
{
    mpid_t reg_num = INVALID_MPID;
    for (mpid_t i = 0; i < (mpid_t)mpu_num_entries(); i++) {
        if (bitmap_get(cpu()->arch.mpu.bitmap, i) == 0) {
            bitmap_set(cpu()->arch.mpu.bitmap, i);
            reg_num = i;
            break;
        }
    }
    return reg_num;
}

bool mpu_map(priv_t priv, struct mp_region* mpr)
{
    if(!mpr)
        ERROR("invalid argument in %s", __func__);

    /* TODO detect whether map code or map data and whether is hyp or VM rgn */

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
         * Since we'll be checking for overlapping regions in order, there will be at most two
         * regions to map in a given iteration. This happens when the previous iteration found an
         * overlapping region that is fully contained by the new region.
         */

        struct mp_region* new_reg;
        if (reg1_valid) {
            new_reg = &reg1;
        } else if (reg2_valid) {
            new_reg = &reg2;
        } else {
            break;
        }

        // TODO we are reusing cortex-r mpu algorithm, however this mpu does
        // not feature the same limitiations. for example we can have the same
        // memory region with different permissions for hyp and guest, we just
        // need to make use of additional DPRE,DPWE and CXE registers.

        bool overlaped = false;
        perms_t new_perms = mem_vmpu_entry_perms(new_reg);

        prev = INVALID_MPID;
        next = INVALID_MPID;
        bottom_mpid = INVALID_MPID;
        top_mpid = INVALID_MPID;

        struct list* mpu_order_list = &cpu()->arch.mpu.order.list;
        list_foreach ((*mpu_order_list), struct mpu_node, entry) {
            mpid_t mpid = entry->mpid;
            struct mp_region overlapped_reg;

            mpu_entry_get_region(mpid, &overlapped_reg);

            if ((new_reg->base + new_reg->size) <= overlapped_reg.base) {
                next = mpid;
                break;
            }

            if (!mem_regions_overlap(new_reg, &overlapped_reg)) {
                // If we are not overlapping, continue to search for overlapped regions until we
                // check all entries. This should be the most frequent case, so the overhead for
                // the checks on overllap will rarely execute.
                prev = mpid;
                continue;
            }
            overlaped = true;

            if (mpu_entry_has_priv(mpid, priv)) {
                // We don't allow overlapping regions of the same privilege. This is something that
                // should be checked at the vmpu level, but we re-check it here anyway.
                failed = true;
                break;
            }

            // We only allow to bump up permissions if the overlapped region is a RO hypervisor
            // region. Otherwise permissions have to be RW in both regions. We don't allow to
            // overlap executable regions.
            struct mpu_perms overlapped_perms = cpu()->arch.mpu.perms[mpid];
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
                ((overlap_perms.el2 & PERM_W) != PERM_NONE)) {
                // We allow promoting read/write privielges of the hypervisor region to match the
                // guest's. However, this combination promotes the guest privielges, which we don't
                // allow.
                failed = true;
                break;
            }

            if ((overlap_perms.el1 & PERM_X) != (overlap_perms.el2 & PERM_X)) {
                // Unless explicitly mapped, we don't promote execution privileges.
                failed = true;
                break;
            }

            // TODO we choose to imlement the cortex-r restriction of not to
            // have different permissions for hypervisor and guest. So we must
            // fail if asked to add an overlapping mapping with different
            // permissions or attributes
            if (!mpu_entry_attrs_equivalent(new_reg, &overlapped_reg)) {
                failed = true;
                break;
            }

            vaddr_t new_reg_limit = new_reg->base + new_reg->size;
            vaddr_t overlapped_reg_limit = overlapped_reg.base + overlapped_reg.size;
            size_t top_size =
                new_reg_limit >= overlapped_reg_limit ? 0 : overlapped_reg_limit - new_reg_limit;
            size_t bottom_size =
                new_reg->base <= overlapped_reg.base ? 0 : new_reg->base - overlapped_reg.base;
            size_t top_left =
                new_reg_limit <= overlapped_reg_limit ? 0 : new_reg_limit - overlapped_reg_limit;
            size_t bottom_left =
                new_reg->base >= overlapped_reg.base ? 0 : overlapped_reg.base - new_reg->base;
            bool subset =
                (new_reg->base >= overlapped_reg.base) && (new_reg_limit <= overlapped_reg_limit);
            bool superset = (bottom_left > 0) || (top_left > 0);

            struct mp_region middle;
            middle.size = overlapped_reg.size - (top_size + bottom_size);
            middle.base = overlapped_reg.base + bottom_size;
            middle.mem_flags = overlapped_reg.mem_flags; // copy attributes
            mpu_entry_set_perms(&middle, overlap_perms);

            if (bottom_size > 0) {
                bottom_mpid = mpu_entry_allocate();
                if (bottom_mpid == INVALID_MPID) {
                    failed = true;
                    break;
                }
            }

            if (top_size > 0) {
                top_mpid = mpu_entry_allocate();
                if (top_mpid == INVALID_MPID) {
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
            } else {
                size_left -= middle.size;
            }

            break;
        }

        if (!overlaped && !failed) {
            mpid_t merge_mpid = INVALID_MPID;
            size_t mem_size = new_reg->size;
            struct mpu_perms* prev_perms = &cpu()->arch.mpu.perms[prev];
            struct mpu_perms* next_perms = &cpu()->arch.mpu.perms[next];
            struct mpu_perms new_reg_perms;
            if (priv == PRIV_VM) {
                new_reg_perms.el1 = new_perms;
                new_reg_perms.el2 = PERM_NONE;
            } else {
                new_reg_perms.el1 = PERM_NONE;
                new_reg_perms.el2 = new_perms;
            }

            /**
             * Check if we can merge the current region with the region right before and/or right
             * after. This can only be done if they are adjacent and have the same exect flags
             * (i.e. permissions and memory attribtues).
             */

            if ((prev != INVALID_MPID) && !mpu_entry_locked(prev)) {
                struct mp_region r;
                mpu_entry_get_region(prev, &r);
                if (((r.base + r.size) == new_reg->base) &&
                    (mpu_entry_attrs_equivalent(&r, new_reg)) &&
                    (mpu_perms_equivalent(prev_perms, &new_reg_perms))) {
                    merge_mpid = prev;
                    new_reg->base = r.base;
                    new_reg->size += r.size;
                }
            }

            if ((next != INVALID_MPID) && !mpu_entry_locked(next)) {
                struct mp_region r;
                mpu_entry_get_region(next, &r);
                if ((new_reg->base + new_reg->size) == r.base &&
                    (mpu_entry_attrs_equivalent(&r, new_reg)) &&
                    (mpu_perms_equivalent(next_perms, &new_reg_perms))) {
                    if (merge_mpid == INVALID_MPID) {
                        merge_mpid = next;
                    } else {
                        mpu_entry_free(next);
                    }
                    new_reg->size += r.size;
                }
            }

            /**
             * If we can merge the region do it. Otherwise, allocate a new entry and set it.
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

    while (size_left > 0) {
        mpid_t mpid = INVALID_MPID;
        struct mp_region reg;

        struct list* mpu_order_list = &cpu()->arch.mpu.order.list;
        list_foreach ((*mpu_order_list), struct mpu_node, entry) {
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
        size_t bottom_size = mpr->base <= reg.base ? 0 : mpr->base - reg.base;
        struct mpu_perms orig_perms = cpu()->arch.mpu.perms[mpid];

        mpu_entry_update_priv_perms(priv, mpid, PERM_NONE);
        bool update_perms = !((cpu()->arch.mpu.perms[mpid].el1 == PERM_NONE) &&
            (cpu()->arch.mpu.perms[mpid].el2 == PERM_NONE));

        if (update_perms) {
            struct mp_region update_reg = reg;
            update_reg.base = bottom_size > 0 ? mpr->base : reg.base;
            update_reg.size = reg.size - top_size - bottom_size;
            mpu_entry_set_perms(&update_reg, cpu()->arch.mpu.perms[mpid]);
            mpu_entry_modify(mpid, &update_reg);
        } else {
            mpu_entry_free(mpid);
        }

        if (top_size > 0) {
            struct mp_region top = reg;
            top.base = mpr_limit;
            top.size = top_size;
            mpid_t top_mpid = mpu_entry_allocate();
            cpu()->arch.mpu.perms[top_mpid] = orig_perms;
            mpu_entry_set(top_mpid, &top);
        }

        if (bottom_size > 0) {
            struct mp_region bottom = reg;
            bottom.size = bottom_size;
            mpid_t bottom_mpid = mpu_entry_allocate();
            cpu()->arch.mpu.perms[bottom_mpid] = orig_perms;
            mpu_entry_set(bottom_mpid, &bottom);
        }

        size_t overlap_size = reg.size - top_size - bottom_size;
        size_left -= overlap_size;
    }

    // TODO: check if we can merge new regions after unmapping a given privilege from a shared
    // region

    return size_left == 0;
}

void mpu_init(void)
{
    bitmap_clear_consecutive(cpu()->arch.mpu.bitmap, 0, mpu_num_entries());
    list_init(&cpu()->arch.mpu.order.list);

    for (mpid_t mpid = 0; mpid < (mpid_t)mpu_num_entries(); mpid++) {
        cpu()->arch.mpu.order.node[mpid].mpid = mpid;

        if (mpu_entry_valid(mpid)) {
            bitmap_set(cpu()->arch.mpu.bitmap, mpid);
            bitmap_set(cpu()->arch.mpu.locked, mpid);

            /**
             * We are assuming all initial regions have all hyp perms. This might change in the
             * future.
             */
            cpu()->arch.mpu.perms[mpid].el1 = PERM_NONE;
            cpu()->arch.mpu.perms[mpid].el2 = PERM_RWX;

            list_insert_ordered(&cpu()->arch.mpu.order.list,
                (node_t*)&cpu()->arch.mpu.order.node[mpid], mpu_node_cmp);
        }
    }
}
