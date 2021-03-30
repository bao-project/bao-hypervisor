/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __PLIC_H__
#define __PLIC_H__

#include <bao.h>
#include <plat/plic.h>

#define PLIC_MAX_INTERRUPTS (1024)
#define PLIC_NUM_PRIO_REGS (PLIC_MAX_INTERRUPTS)
#define PLIC_NUM_PEND_REGS (PLIC_MAX_INTERRUPTS)
#define PLIC_NUM_ENBL_REGS (PLIC_MAX_INTERRUPTS / 32)

#define PLIC_ENBL_OFF (0x002000)
#define PLIC_CLAIMCMPLT_OFF (0x200000)

typedef struct {
    uint32_t prio[PLIC_NUM_PRIO_REGS];
    uint32_t pend[PLIC_NUM_PEND_REGS];
    uint32_t enbl[PLIC_PLAT_CNTXT_NUM][PLIC_NUM_ENBL_REGS];
} __attribute__((__packed__, aligned(PAGE_SIZE))) plic_global_t;

typedef struct {
    uint32_t threshold;
    union {
        uint32_t claim;
        uint32_t complete;
    };
    uint8_t res[0x1000 - 0x0008];
} __attribute__((__packed__, aligned(PAGE_SIZE))) plic_hart_t;

extern volatile plic_global_t plic_global;
extern volatile plic_hart_t plic_hart[PLIC_PLAT_CNTXT_NUM];
extern int PLIC_IMPL_INTERRUPTS;

void plic_init();
void plic_cpu_init();
void plic_handle();
void plic_set_enbl(unsigned cntxt, unsigned int_id, bool en);
bool plic_get_enbl(unsigned cntxt, unsigned int_id);
void plic_set_prio(unsigned int_id, uint32_t prio);
uint32_t plic_get_prio(unsigned int_id);
void plic_set_threshold(unsigned cntxt, uint32_t threshold);
uint32_t plic_get_threshold(unsigned int_id);
bool plic_get_pend(unsigned int_id);

typedef struct {
    int hart_id;
    enum { PRIV_M = 3, PRIV_S = 2, PRIV_U = 0 } mode;
} plic_cntxt_t;

int plic_plat_cntxt_to_id(plic_cntxt_t cntxt);
plic_cntxt_t plic_plat_id_to_cntxt(int id);

#endif /* __PLIC_H__ */
