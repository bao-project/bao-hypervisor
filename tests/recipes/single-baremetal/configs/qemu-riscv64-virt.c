#include <config.h>

VM_IMAGE(baremetal_image, XSTR(BAO_WRKDIR_IMGS/baremetal.bin))

struct config config  = {
    
    CONFIG_HEADER

    .vmlist_size = 1,
    .vmlist = (struct vm_config[]) {
        { 
            .image = {
                .base_addr = 0x80200000,
                .load_addr = VM_IMAGE_OFFSET(baremetal_image),
                .size = VM_IMAGE_SIZE(baremetal_image)
            },

            .entry = 0x80200000,

            .platform = {
                .cpu_num = 4,
                
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x80200000,
                        .size = 0x4000000
                    }
                },

                .dev_num = 1,
                .devs =  (struct vm_dev_region[]) {
                    {
                        .pa = 0x10000000,   
                        .va = 0x10000000,  
                        .size = 0x1000, 
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {10}
                    },
                },

                .arch = {
                   .irqc = {
                        .plic = {
                            .base = 0xc000000,
                        },
                   },
                },
            },
        },
     }
};
