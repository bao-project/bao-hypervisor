/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <platform.h>
#include <arch/sysregs.h>

__attribute__((used)) static void sysregs_defines(void)
{
    DEFINE_OFFSET(SCB_VTOR_OFF, struct scb, vtor);

    DEFINE_OFFSET(MPU_CTRL_OFF, struct mpu, ctrl);
    DEFINE_OFFSET(MPU_RNR_OFF, struct mpu, rnr);
    DEFINE_OFFSET(MPU_RBAR_OFF, struct mpu, rbar);
    DEFINE_OFFSET(MPU_RLAR_OFF, struct mpu, rlar);
    DEFINE_OFFSET(MPU_MAIR0_OFF, struct mpu, mair0);

    DEFINE_OFFSET(SAU_CTRL_OFF, struct sau, ctrl);
    DEFINE_OFFSET(SAU_RNR_OFF, struct sau, rnr);
    DEFINE_OFFSET(SAU_RBAR_OFF, struct sau, rbar);
    DEFINE_OFFSET(SAU_RLAR_OFF, struct sau, rlar);

    DEFINE_OFFSET(SCB_SHCSR_OFF, struct scb, shcsr);
}

__attribute__((used)) static void cpu_defines(void)
{
    DEFINE_SIZE(CPU_SIZE, struct cpu);

    DEFINE_OFFSET(CPU_STACK_OFF, struct cpu, stack);
    DEFINE_SIZE(CPU_STACK_SIZE, ((struct cpu*)NULL)->stack);
    DEFINE_OFFSET(CPU_VCPU_OFF, struct cpu, vcpu);
}

__attribute__((used)) static void vcpu_defines(void)
{
    DEFINE_SIZE(VCPU_ARCH_SIZE, struct vcpu_arch);
    DEFINE_OFFSET(VCPU_REGS_OFF, struct vcpu, regs);
    DEFINE_SIZE(VCPU_REGS_SIZE, struct arch_regs);
    DEFINE_OFFSET(VCPU_SPREGS_OFF, struct arch_regs, sp_regs);
    DEFINE_SIZE(VCPU_GP_REGS_SIZE, ((struct arch_regs*)NULL)->gp_regs);
    DEFINE_SIZE(VCPU_SPREGS_SIZE, struct special_regs);
}

__attribute__((used)) static void platform_defines(void) { }
