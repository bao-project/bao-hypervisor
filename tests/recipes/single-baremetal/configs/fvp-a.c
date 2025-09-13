#include <config.h>

VM_IMAGE(baremetal_image, XSTR(BAO_WRKDIR_IMGS/baremetal.bin))

struct config config = {

    .vmlist_size = 1,
    .vmlist = (struct vm_config[]) {
        { 
            .image = {
                .base_addr = 0x90000000,
                .load_addr = VM_IMAGE_OFFSET(baremetal_image),
                .size = VM_IMAGE_SIZE(baremetal_image)
            },

            .entry = 0x90000000,

            .platform = {
                .cpu_num = 4,
                
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x90000000,
                        .size = 0x4000000
                    }
                },

                .dev_num = 2,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* UART2, PL011 */
                        .pa = 0x1c090000,
                        .va = 0x1c090000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {37} 
                    },
                    {   
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {27} 
                    }
                },

                .arch = {
                    .gic = {
                        .gicr_addr = (paddr_t) 0x2F100000,
                        .gicd_addr = (paddr_t) 0x2F000000
                    }
                }
            },
        },
    },
};