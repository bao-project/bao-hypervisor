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

#include <arch/plic.h>
#include <interrupts.h>
#include <cpu.h>

int PLIC_IMPL_INTERRUPTS;

volatile plic_global_t plic_global
    __attribute__((section(".devices")));

volatile plic_hart_t plic_hart[PLIC_PLAT_CNTXT_NUM]
    __attribute__((section(".devices")));

static int plic_scan_max_int()
{
    int res = 0;
    for (int i = 1; i < PLIC_MAX_INTERRUPTS; i++) {
        plic_global.prio[i] = -1;
        if (plic_global.prio[i] == 0) {
            res = i - 1;
            break;
        }
        plic_global.prio[i] = 0;
    }
    return res;
}

void plic_init()
{
    PLIC_IMPL_INTERRUPTS = plic_scan_max_int();

    for (int i = 0; i <= PLIC_IMPL_INTERRUPTS; i++) {
        plic_global.prio[i] = 0;
    }

    for (int i = 0; i < PLIC_PLAT_CNTXT_NUM; i++) {
        for (int j = 0; j < PLIC_NUM_ENBL_REGS; j++) {
            plic_global.enbl[i][j] = 0;
        }
    }
}

void plic_cpu_init()
{
    cpu.arch.plic_cntxt = plic_plat_cntxt_to_id((plic_cntxt_t){cpu.id, PRIV_S});
    plic_hart[cpu.arch.plic_cntxt].threshold = 0;
}

bool plic_cntxt_valid(unsigned cntxt_id) {
    plic_cntxt_t cntxt = plic_plat_id_to_cntxt(cntxt_id);
    return (cntxt_id < PLIC_PLAT_CNTXT_NUM) && (cntxt.mode <= PRIV_S);
}

void plic_set_enbl(unsigned cntxt, unsigned int_id, bool en)
{
    int reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint32_t mask = 1U << (int_id % (sizeof(uint32_t) * 8));

    
    if (int_id <= PLIC_IMPL_INTERRUPTS && plic_cntxt_valid(cntxt)) { 
        if (en) {
            plic_global.enbl[cntxt][reg_ind] |= mask;
        } else {
            plic_global.enbl[cntxt][reg_ind] &= ~mask;
        }
    }
}

bool plic_get_enbl(unsigned cntxt, unsigned int_id)
{
    int reg_ind = int_id / (sizeof(uint32_t) * 8);
    uint32_t mask = 1U << (int_id % (sizeof(uint32_t) * 8));

    if (int_id <= PLIC_IMPL_INTERRUPTS && plic_cntxt_valid(cntxt))
        return plic_global.enbl[cntxt][reg_ind] & mask;
    else
        return false;
}

void plic_set_prio(unsigned int_id, uint32_t prio)
{
    if (int_id <= PLIC_IMPL_INTERRUPTS) {
        plic_global.prio[int_id] = prio;
    }
}

uint32_t plic_get_prio(unsigned int_id)
{
    if (int_id <= PLIC_IMPL_INTERRUPTS)
        return plic_global.prio[int_id];
    else
        return 0;
}

bool plic_get_pend(unsigned int_id)
{
    int reg_ind = int_id / 32;
    int mask = (1U << (int_id % 32));

    if (int_id <= PLIC_IMPL_INTERRUPTS)
        return plic_global.pend[reg_ind] & mask;
    else
        return false;
}

void plic_set_threshold(unsigned cntxt, uint32_t threshold)
{
    if(plic_cntxt_valid(cntxt)) {
        plic_hart[cntxt].threshold = threshold;
    }
}

uint32_t plic_get_thrshold(unsigned cntxt)
{
    uint32_t threshold = 0;
    if(plic_cntxt_valid(cntxt)) {
        threshold = plic_hart[cntxt].threshold;
    }
    return threshold;
}

void plic_handle()
{
    uint32_t id = plic_hart[cpu.arch.plic_cntxt].claim;

    if (id != 0) {
        enum irq_res res = interrupts_handle(id);
        if (res == HANDLED_BY_HYP) plic_hart[cpu.arch.plic_cntxt].complete = id;
    }
}

/**
 * Context organization is spec-out by the vendor, this is the default 
 * mapping found in sifive's plic.
 */

__attribute__((weak))
int plic_plat_cntxt_to_id(plic_cntxt_t cntxt){
    if(cntxt.mode != PRIV_M && cntxt.mode != PRIV_S) return -1;
    return (cntxt.hart_id*2) + (cntxt.mode == PRIV_M ? 0 : 1);
}

__attribute__((weak))
plic_cntxt_t plic_plat_id_to_cntxt(int id){
    plic_cntxt_t cntxt;
    if(id < PLIC_PLAT_CNTXT_NUM){
        cntxt.hart_id = id/2;
        cntxt.mode = (id%2) == 0 ? PRIV_M : PRIV_S; 
    } else {
        return (plic_cntxt_t){-1};
    }
    return cntxt;
}
