#include <vmm.h>
#include <io.h>

void vmm_io_init() {
    io_init();
}

struct vm_install_info vmm_get_vm_install_info(struct vm* vm) {
    struct vm_install_info info;
    info.vm_section_pte = *pt_get_pte(&cpu()->as.pt, 0, (vaddr_t)vm);
    return info;
}

void vmm_vm_install(struct vm* vm, struct vm_install_info *install_info) {
    pte_t* pte = pt_get_pte(&cpu()->as.pt, 0, (vaddr_t)vm);
    *pte = install_info->vm_section_pte;
}
