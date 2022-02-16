#include <arch/aborts.h>
#include <cpu.h>
#include <vm.h>
#include <arch/psci.h>

void smc64_handler(uint64_t iss, uint64_t far, uint64_t il)
{
    uint64_t smc_fid = cpu()->vcpu->regs.x[0];
    uint64_t x1 = cpu()->vcpu->regs.x[1];
    uint64_t x2 = cpu()->vcpu->regs.x[2];
    uint64_t x3 = cpu()->vcpu->regs.x[3];

    int64_t ret = -1;

    if (is_psci_fid(smc_fid)) {
        ret = psci_smc_handler(smc_fid, x1, x2, x3);
    } else {
        INFO("unknown smc_fid 0x%lx", smc_fid);
    }

    vcpu_writereg(cpu()->vcpu, 0, ret);
    uint64_t pc_step = 2 + (2 * il);
    cpu()->vcpu->regs.elr_el2 += pc_step;
}
