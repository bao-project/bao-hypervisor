/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <platform.h>

__attribute__((used)) static void cpu_defines(void)
{
    DEFINE_SIZE(CPU_SIZE, struct cpu);

    DEFINE_OFFSET(CPU_STACK_OFF, struct cpu, stack);
    DEFINE_SIZE(CPU_STACK_SIZE, ((struct cpu*)NULL)->stack);

    DEFINE_OFFSET(CPU_VCPU_OFF, struct cpu, vcpu);
}

__attribute__((used)) static void vcpu_defines(void)
{
    DEFINE_OFFSET(VCPU_REGS_X_OFF, struct vcpu, regs.x);
    DEFINE_OFFSET(VCPU_REGS_HSTATUS_OFF, struct vcpu, regs.hstatus);
    DEFINE_OFFSET(VCPU_REGS_SSTATUS_OFF, struct vcpu, regs.sstatus);
    DEFINE_OFFSET(VCPU_REGS_SEPC_OFF, struct vcpu, regs.sepc);
}
