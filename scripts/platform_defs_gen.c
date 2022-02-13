#include <stdio.h>
#include <platform.h>

extern void arch_platform_defs();

int main() {

    printf("#define PLAT_CPU_NUM (%ld)\n", platform.cpu_num);
    printf("#define CONSOLE_BASE (0x%lx)\n", platform.console.base);

    arch_platform_defs();

    return 0;
}
