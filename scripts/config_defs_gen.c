/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <config.h>

int main() {
    size_t vcpu_num = 0;
    for (size_t i = 0; i < config.vmlist_size; i++) {
        vcpu_num += config.vmlist[i].platform.cpu_num;
    }

    printf("#define CONFIG_VM_NUM %ld\n", config.vmlist_size);
    printf("#define CONFIG_VCPU_NUM %ld\n", vcpu_num);

    if(config.hyp.relocate) {
        printf("#define CONFIG_HYP_BASE_ADDR (0x%lx)\n", config.hyp.base_addr);
    } else {
        printf("#define CONFIG_HYP_BASE_ADDR PLAT_BASE_ADDR\n");
    }

    return 0;
 }
