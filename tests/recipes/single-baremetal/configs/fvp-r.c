#include <config.h>


struct config config = {

    .vmlist_size = 1,
    .vmlist = (struct vm_config[]) {
        {
            .image = VM_IMAGE_LOADED(0x10000000, 0x10000000, 100*1024),

            .entry = 0x10000000,

            .platform = {
                .cpu_num = 4,
                
                .region_num = 1,
                .regions =  (struct vm_mem_region[]) {
                    {
                        .base = 0x10000000,
                        .size = 0x4000000,
                    },
                },

                .dev_num = 2,
                .devs =  (struct vm_dev_region[]) {
                    {   
                        /* UART2, PL011 */
                        .pa = 0x9c0A0000,
                        .va = 0x9c0A0000,
                        .size = 0x10000,
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {38} 
                    },
                    {   
                        .interrupt_num = 1,
                        .interrupts = (irqid_t[]) {27} 
                    }
                },

                .arch = {
                    .gic = {
                        .gicd_addr = (paddr_t) 0xAF000000,
                        .gicr_addr = (paddr_t) 0xAF100000,
                    }
                }
            },
        }
    }
};