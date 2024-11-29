/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>

__attribute__((weak)) void arch_platform_defs(void){
    return;
}

int main() {

    printf("#define PLAT_CPU_NUM (%ld)\n", platform.cpu_num);
    printf("#define PLAT_BASE_ADDR (0x%lx)\n", platform.regions[0].base);

    for(size_t i = 1; i < platform.region_num; i++)
    {
        if(platform.regions[i].perms == RWX)
        {
            printf("#define PLAT_MEM_RWX_ADDR (0x%lx)\n", platform.regions[i].base);
            break;
        }
    }
    if (platform.cpu_master_fixed) {
        printf("#define CPU_MASTER_FIXED (%ld)\n", platform.cpu_master);
    }
    // Call arch specific platform defines generator
    arch_platform_defs();
    return 0;
}
