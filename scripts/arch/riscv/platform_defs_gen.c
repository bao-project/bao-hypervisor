#include <stdio.h>
#include <platform.h>

void arch_platform_defs() {
     printf("#define PLIC_BASE (0x%lx)\n", platform.arch.plic_base);
}

