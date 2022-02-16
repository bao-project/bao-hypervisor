#include <stdio.h>
#include <platform.h>

void arch_platform_defs() {
    printf("#define GICD_BASE (0x%lxUL)\n", platform.arch.gic.gicd_addr);
    printf("#define GICC_BASE (0x%lxUL)\n", platform.arch.gic.gicd_addr);
    printf("#define GICR_BASE (0x%lxUL)\n", platform.arch.gic.gicr_addr);
    printf("#define GICH_BASE (0x%lxUL)\n", platform.arch.gic.gich_addr);
    printf("#define GICV_BASE (0x%lxUL)\n", platform.arch.gic.gicv_addr);
}
