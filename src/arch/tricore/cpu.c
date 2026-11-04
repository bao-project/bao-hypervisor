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
    cpu()->arch.standby = true;
    __asm__ volatile("enable\n\r"
                     "1: wait\n\r"
                     "j 1b\n\r" ::: "memory");
}

void cpu_arch_standby_irq(void)
{
    cpu()->arch.standby = false;

    /*
     * Taking the interrupt disabled interrupts and raised ICR.CCPN to its priority. This path
     * does not return with rfe, which would restore CCPN, so clear it here: with CCPN at the
     * IPI priority, the next standby could not take the IPI.
     */
    csfr_vm0_icr_write(csfr_vm0_icr_read() & ~ICR_CCPN_MASK);

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
