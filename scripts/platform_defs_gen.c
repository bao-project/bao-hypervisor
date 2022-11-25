/**
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>

extern void arch_platform_defs();

int main() {

    printf("#define PLAT_CPU_NUM (%ld)\n", platform.cpu_num);
    printf("#define PLAT_BASE_ADDR (0x%lx)\n", platform.regions[0].base);

    return 0;
}
