/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PROT_H__
#define __PROT_H__

#include <bao.h>
#include <platform.h>

typedef unsigned long prottos_t;

struct PROT_ACCESSEN {
    volatile uint32_t WRA; // write access enable register A
    volatile uint32_t WRB; // write access enable register B
    volatile uint32_t RDA; // read access enable register A
    volatile uint32_t RDB; // read access enable register B
    volatile uint32_t VM;  // VM access enable register
    volatile uint32_t PRS; // PRS access enable register
};

#define PROT_OWEN_POS   31
#define PROT_ODEF_POS   30
#define PROT_TAGID_POS  24
#define PROT_PRSEN_POS  23
#define PROT_PRS_POS    20
#define PROT_VMEN_POS   19
#define PROT_VM_POS     16
#define PROT_SWEN_POS   3
#define PROT_STATE_POS  0

#define PROT_OWEN_MASK  (0x1U << PROT_OWEN_POS)
#define PROT_ODEF_MASK  (0x1U << PROT_ODEF_POS)
#define PROT_TAGID_MASK (0x3F << PROT_TAGID_POS)
#define PROT_PRSEN_MASK (0x1U << PROT_PRSEN_POS)
#define PROT_PRS_MASK   (0x7U << PROT_PRS_POS)
#define PROT_VMEN_MASK  (0x1U << PROT_VMEN_POS)
#define PROT_VM_MASK    (0x7U << PROT_VM_POS)
#define PROT_SWEN_MASK  (0x1U << PROT_SWEN_POS)
#define PROT_STATE_MASK (0x7U << PROT_STATE_POS)

#define SET_PROT_ODEF(reg, val)                                                        \
    ((reg) = ((reg) & ~PROT_ODEF_MASK) | (((val) << PROT_ODEF_POS) & PROT_ODEF_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_TAGID(reg, val)                                                          \
    ((reg) = ((reg) & ~PROT_TAGID_MASK) | (((val) << PROT_TAGID_POS) & PROT_TAGID_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_PRSEN(reg, val)                                                          \
    ((reg) = ((reg) & ~PROT_PRSEN_MASK) | (((val) << PROT_PRSEN_POS) & PROT_PRSEN_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_PRS(reg, val)                                                      \
    ((reg) = ((reg) & ~PROT_PRS_MASK) | (((val) << PROT_PRS_POS) & PROT_PRS_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_VMEN(reg, val)                                                        \
    ((reg) = ((reg) & ~PROT_VMEN_MASK) | (((val) << PROT_VMEN_POS) & PROT_VMEN_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_VM(reg, val)                                                    \
    ((reg) = ((reg) & ~PROT_VM_MASK) | (((val) << PROT_VM_POS) & PROT_VM_MASK) | \
            (1UL << PROT_OWEN_POS))
#define SET_PROT_STATE(reg, val) \
    (reg) = ((((val) << PROT_STATE_POS) & PROT_STATE_MASK) | (1UL << PROT_SWEN_POS))

#define GET_PROT_ODEF(reg)      (((reg) & PROT_ODEF_MASK) >> PROT_ODEF_POS)
#define GET_PROT_TAGID(reg)     (((reg) & PROT_TAGID_MASK) >> PROT_TAGID_POS)
#define GET_PROT_PRSEN(reg)     (((reg) & PROT_PRSEN_MASK) >> PROT_PRSEN_POS)
#define GET_PROT_PRS(reg)       (((reg) & PROT_PRS_MASK) >> PROT_PRS_POS)
#define GET_PROT_VMEN(reg)      (((reg) & PROT_VMEN_MASK) >> PROT_VMEN_POS)
#define GET_PROT_VM(reg)        (((reg) & PROT_VM_MASK) >> PROT_VM_POS)

#define PROT_STATE_INIT         0
#define PROT_STATE_CONFIG       1
#define PROT_STATE_CONFIG_SEC   2
#define PROT_STATE_CHECK        3
#define PROT_STATE_RUN          4
#define PROT_STATE_RUN_SEC      5
#define PROT_STATE_RUN_LOCK     6
#define PROT_STATE_RUN_LOCK_SEC 7

inline void apu_enable_access_all_cpus(volatile struct PROT_ACCESSEN* accessen)
{
    accessen->WRA |= 0x7FFUL;
    accessen->RDA |= 0x7FFUL;
}

inline void apu_enable_access_cpu(volatile struct PROT_ACCESSEN* accessen, unsigned long cpuid)
{
    accessen->WRA |= 0x3UL << (cpuid * 2);
    accessen->RDA |= 0x3UL << (cpuid * 2);
}

inline void apu_enable_access_vm(volatile struct PROT_ACCESSEN* accessen, unsigned long vmid)
{
    accessen->VM |= 0x1UL << vmid;
}

inline void apu_clear_access_cpu(struct PROT_ACCESSEN* accessen, unsigned long cpuid)
{
    unsigned long val;
    val = accessen->WRA;
    val = val & ~(0x3UL << cpuid);
    accessen->WRA = val;

    val = accessen->RDA;
    val = val & ~(0x3UL << cpuid);
    accessen->RDA = val;
}

inline void prot_set_state(volatile prottos_t* prottos, unsigned long state)
{
    SET_PROT_STATE(*prottos, state);
}

inline void prot_set_vm(volatile prottos_t* prottos, unsigned long vmid, bool vmen)
{
    SET_PROT_VM(*prottos, vmid);
    SET_PROT_VMEN(*prottos, vmen ? 1UL : 0);
}

inline void prot_enable(volatile prottos_t* prottos)
{
    SET_PROT_ODEF(*prottos, 1);
}

inline void prot_disable(volatile prottos_t* prottos)
{
    SET_PROT_ODEF(*prottos, 0);
}

inline void prot_write(volatile prottos_t* prottos, unsigned long cpu, unsigned long vm,
    unsigned long state)
{
    unsigned long temp = PROT_ODEF_MASK | PROT_OWEN_MASK;
    temp |= (vm << PROT_VM_POS);
    temp |= (cpu * 2 << PROT_TAGID_POS);
    temp |= PROT_SWEN_MASK | (state << PROT_STATE_POS);

    *prottos = temp;
}

#endif //__PROT_H__
