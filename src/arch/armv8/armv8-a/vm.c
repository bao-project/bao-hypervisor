#include <vm.h>
#include <arch/sysregs.h>
#include <arch/fences.h>
#include <tlb.h>

void vcpu_arch_profile_init(struct vcpu* vcpu, struct vm* vm) {
    vcpu->arch.profile.psci_ctx.state = vcpu->id == 0 ? ON : OFF;

    paddr_t root_pt_pa;
    mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &root_pt_pa);
    sysreg_vttbr_el2_write(((vm->id << VTTBR_VMID_OFF) & VTTBR_VMID_MSK) |
                       (root_pt_pa & ~VTTBR_VMID_MSK));

    ISB();  // make sure vmid is commited befor tlbi
    tlb_vm_inv_all(vm->id);
}

void vcpu_arch_profile_reset(struct vcpu* vcpu) {
    vcpu->regs.spsr_el2 = SPSR_EL1h | SPSR_F | SPSR_I | SPSR_A | SPSR_D;
}


bool vcpu_arch_profile_on(struct vcpu* vcpu) {
    return vcpu->arch.profile.psci_ctx.state == ON;
}
