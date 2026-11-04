/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <platform.h>
#include <arch/csfrs.h>
#include <arch/prot.h>
#include <arch/csa.h>
#include <fences.h>

cpuid_t CPU_MASTER __attribute__((section(".data")));

/* Link word (PCXI/FCX format: segment and offset) of a CSA */
#define CSA_LINK(csa)                                                                              \
    (((((unsigned long)(csa)) >> ADDR_PCXS_OFF) & ((1UL << ADDR_PCXS_LEN) - 1)) << PCXI_PCXS_OFF | \
        ((((unsigned long)(csa)) >> ADDR_PCXO_OFF) & ((1UL << ADDR_PCXO_LEN) - 1)))

/*
 * Rebuild this CPU's free CSA list as _init_csa does at boot (entries 1 to CSA_ENTRIES - 1; entry
 * 0 stays unused), for paths that discard the whole call chain. No context in csa_array is live
 * then: a paused vCPU's contexts are in vcpu->regs, outside csa_array, and VM entry links them
 * back. Must be inlined and must not call functions, since a call would save a context into the
 * list being rebuilt.
 */
static inline __attribute__((always_inline)) void cpu_reset_csa(void)
{
    unsigned long core_id = csfr_coreid_read() & COREID_CORE_MASK;
    union csa* csas = csa_array[core_id];

    for (size_t i = 1; i < (CSA_ENTRIES - 1); i++) {
        csas[i].lower.pcxi = CSA_LINK(&csas[i + 1]);
    }
    csas[CSA_ENTRIES - 1].lower.pcxi = 0;

    csfr_pcxi_write(0);
    csfr_fcx_write(CSA_LINK(&csas[1]));
    fence_sync();
}

static inline __attribute__((always_inline)) void cpu_reset_stack(void)
{
    unsigned long stack_top = (unsigned long)&(cpu()->stack[STACK_SIZE]);

    __asm__ volatile("mov.a %%sp, %0" : : "d"(stack_top) : "memory");
}

/* Perform architecture dependent cpu cores initializations */
void cpu_arch_init(cpuid_t cpuid, paddr_t load_addr)
{
    if (cpu_is_master()) {
        platform_cpu_init(cpuid, load_addr);
    }
}

void cpu_arch_powerdown(void)
{
    __asm__ volatile("wait \n\r" ::: "memory");

    cpu_reset_csa();
    cpu_reset_stack();

    __asm__ volatile("j cpu_powerdown_wakeup");

    ERROR("returned from powerdown wake up\n");
}

void cpu_arch_standby(void)
{
    __asm__ volatile("wait \n\r" ::: "memory");

    cpu_reset_csa();
    cpu_reset_stack();

    __asm__ volatile("j cpu_standby_wakeup");

    ERROR("returned from standby wake up\n");
}

/* The current GCC injects calls to abort() in some places, which
   results in undefined references.
   For this reason we define our own abort() for this architecture. */
void abort(void)
{
    ERROR("abort() reached!\n");
}
