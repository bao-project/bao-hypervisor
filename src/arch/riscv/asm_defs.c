#include <bao.h>
#include <cpu.h>
#include <vm.h>
#include <platform.h>
#include <arch/plic.h>

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
}

void vcpu_defines() __attribute__((used));
void vcpu_defines()
{
    DEFINE_SIZE(VCPU_ARCH_SIZE, vcpu_arch_t);
    DEFINE_OFFSET(VCPU_REGS_OFF, struct vcpu, regs);
    DEFINE_SIZE(VCPU_REGS_SIZE, struct arch_regs);
}
