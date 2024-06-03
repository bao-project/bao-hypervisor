#include <config.h>

VM_IMAGE(baremetal_image, XSTR(BAO_WRKDIR_IMGS/baremetal.bin))

struct config config = {
    
    CONFIG_HEADER
    
    .vmlist_size = 1,
    .vmlist = (struct vm_config[]) {
        { 
            .image = {
                .base_addr = 0x50000000,
                .load_addr = VM_IMAGE_OFFSET(baremetal_image),
                .size = VM_IMAGE_SIZE(baremetal_image)
            },

            .entry = 0x50000000,

            .platform = {
                .cpu_num = 4,
                
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x50000000,
                        .size = 0x4000000 
                    }
                },

                .dev_num = 2,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* PL011 */
                        .pa = 0x9000000,
                        .va = 0x9000000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {33}                        
                    },
                    {   
                        /* Arch timer interrupt */
                        .interrupt_num = 1,
                        .interrupts = 
                            (irqid_t[]) {27}                         
                    }
                },

                .arch = {
                    .gic = {
                        .gicd_addr = (paddr_t) 0x08000000,
                        .gicr_addr = (paddr_t) 0x080A0000,
                    }
                }
            },
        }
    },
};