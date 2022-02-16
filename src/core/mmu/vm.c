#include <vm.h>

#include <config.h>
#include <mem.h>

void vm_mem_prot_init(struct vm* vm, const struct vm_config* config) {
    as_init(&vm->as, AS_VM, vm->id, NULL, config->colors);
}
