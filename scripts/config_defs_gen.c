/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <config.h>

static size_t remio_dev_num(void)
{
    size_t dev_num = 0;
    for (size_t vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
            struct remio_dev* dev = &vm_config->platform.remio_devs[i];
            if (dev->type == REMIO_DEV_BACKEND) {
                dev_num++;
            }
        }
    }
    return dev_num;
}

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

    if(config.hyp.data_relocate) {
        printf("#define CONFIG_HYP_DATA_ADDR (0x%lx)\n", config.hyp.data_addr);
    } else {
        printf("#define CONFIG_HYP_DATA_ADDR PLAT_DATA_ADDR\n");
    }

    printf("#define CONFIG_REMIO_DEV_NUM %ld\n", remio_dev_num());

    return 0;
 }
