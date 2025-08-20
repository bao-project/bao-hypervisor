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
    DEFINE_OFFSET(VCPU_REGS_OFF, struct vcpu, regs);
    DEFINE_OFFSET(VCPU_VM_OFF, struct vcpu, vm);
    DEFINE_OFFSET(VM_ID_OFF, struct vm, id);
    DEFINE_OFFSET(REGS_A0_OFF, struct arch_regs, a0);
    DEFINE_OFFSET(REGS_A1_OFF, struct arch_regs, a1);
    DEFINE_OFFSET(REGS_A8_OFF, struct arch_regs, a8);
    DEFINE_OFFSET(REGS_A9_OFF, struct arch_regs, a9);
}
