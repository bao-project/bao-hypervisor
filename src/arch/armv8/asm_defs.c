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
    DEFINE_SIZE(VCPU_ARCH_SIZE, struct vcpu_arch);
    DEFINE_OFFSET(VCPU_REGS_OFF, struct vcpu, regs);
    DEFINE_SIZE(VCPU_REGS_SIZE, struct arch_regs);
}

__attribute__((used)) static void platform_defines(void)
{
    DEFINE_OFFSET(PLAT_CPUNUM_OFF, struct platform, cpu_num);
    DEFINE_OFFSET(PLAT_ARCH_OFF, struct platform, arch);
    DEFINE_OFFSET(PLAT_ARCH_CLUSTERS_OFF, struct arch_platform, clusters);
    DEFINE_OFFSET(PLAT_CLUSTERS_CORES_NUM_OFF, struct clusters, core_num);
    DEFINE_SIZE(PLAT_CLUSTERS_CORES_NUM_SIZE, ((struct clusters*)NULL)->core_num[0]);
}
