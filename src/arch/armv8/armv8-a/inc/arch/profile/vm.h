#ifndef VM_ARCH_PROFILE
#define VM_ARCH_PROFILE

#include <arch/psci.h>

struct vcpu_arch_profile {
    struct psci_ctx psci_ctx;
};

#endif /* VM_ARCH_PROFILE */
