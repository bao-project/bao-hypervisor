/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>
#include <bao.h>

__attribute__((weak)) void arch_platform_defs(void){
    return;
}

int main() {

    size_t bitmap_array_size = 0;

    printf("#define PLAT_CPU_NUM (%ld)\n", platform.cpu_num);
    printf("#define PLAT_BASE_ADDR (0x%lx)\n", platform.regions[0].base);

    for(size_t i = 0; i < platform.region_num; i++)
    {
        size_t reg_size;

        reg_size = platform.regions[i].size;

        bitmap_array_size += BITMAP_SIZE_IN_BYTES(NUM_PAGES(reg_size));
    }

    printf("#define PLAT_BITMAP_POOL_SIZE (0x%lx)\n", bitmap_array_size);

    if (platform.cpu_master_fixed) {
        printf("#define CPU_MASTER_FIXED (%ld)\n", platform.cpu_master);
    }
    // Call arch specific platform defines generator
    arch_platform_defs();
    return 0;
}
