#include <vm.h>
#include <arch/csrs.h>
#include <vplic.h>

void vm_arch_init(struct vm *vm, const struct vm_config *config)
{
    paddr_t root_pt_pa;
    mem_translate(&cpu()->as, (vaddr_t)vm->as.pt.root, &root_pt_pa);

    unsigned long hgatp = (root_pt_pa >> PAGE_SHIFT) | (HGATP_MODE_DFLT) |
                          ((vm->id << HGATP_VMID_OFF) & HGATP_VMID_MSK);

    CSRW(CSR_HGATP, hgatp);

    vplic_init(vm, platform.arch.plic_base);
}
