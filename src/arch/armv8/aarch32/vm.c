#include <vm.h>
#include <arch/sysregs.h>

unsigned long vcpu_readreg(struct vcpu* vcpu, unsigned long reg)
{
    return 0;
}

void vcpu_writereg(struct vcpu* vcpu, unsigned long reg, unsigned long val)
{

}

unsigned long vcpu_readpc(struct vcpu* vcpu)
{
    return 0;
}

void vcpu_writepc(struct vcpu* vcpu, unsigned long pc)
{

}
