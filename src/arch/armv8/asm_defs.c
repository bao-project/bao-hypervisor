/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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

#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <platform.h>

void cpu_defines() __attribute__((used));
void cpu_defines()
{
    DEFINE_SIZE(CPU_SIZE, struct cpu);

    DEFINE_OFFSET(CPU_ROOT_PT_OFF, struct cpu, root_pt);

    DEFINE_OFFSET(CPU_STACK_OFF, struct cpu, stack);
    DEFINE_SIZE(CPU_STACK_SIZE, ((struct cpu*)NULL)->stack);

    DEFINE_OFFSET(CPU_IF_OFF, struct cpu, interface);
    DEFINE_SIZE(CPU_IF_SIZE, ((struct cpu*)NULL)->interface);

    DEFINE_OFFSET(CPU_VCPU_OFF, struct cpu, vcpu);

    DEFINE_OFFSET(CPU_ARCH_OFF, struct cpu, arch);
    DEFINE_OFFSET(CPU_ARCH_OFFSTATE_OFF, struct cpu_arch, psci_off_state);
}

void vcpu_defines() __attribute__((used));
void vcpu_defines()
{
    DEFINE_SIZE(VCPU_ARCH_SIZE, vcpu_arch_t);
    DEFINE_OFFSET(VCPU_REGS_OFF, struct vcpu, regs);
    DEFINE_SIZE(VCPU_REGS_SIZE, struct arch_regs);
}

void platform_defines() __attribute__((used));
void platform_defines()
{
    DEFINE_OFFSET(PLAT_CPUNUM_OFF, struct platform_desc, cpu_num);
    DEFINE_OFFSET(PLAT_ARCH_OFF, struct platform_desc, arch);
    DEFINE_OFFSET(PLAT_ARCH_CLUSTERS_OFF, struct arch_platform, clusters);
    DEFINE_OFFSET(PLAT_CLUSTERS_CORES_NUM_OFF, struct clusters, core_num);
}
