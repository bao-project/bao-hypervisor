#include <config.h>

VM_IMAGE(baremetal_image, XSTR(BAO_WRKDIR_IMGS/baremetal.bin))

struct config config = {

.vmlist_size = 1,
        //.hyp.base_addr = 0xA0000000,

        .vmlist = (struct vm_config[]){
            {
                .image = {
                    .base_addr = 0x90100000, //TODO
                    .load_addr = VM_IMAGE_OFFSET(baremetal_image),
                    .size = VM_IMAGE_SIZE(baremetal_image),
                },

                .entry = 0x90100000, //TODO
                .platform = {
                    .cpu_num = 6,
                    .region_num = 1,
                    .regions = (struct vm_mem_region[]){
                        {
                            .base = 0x90100000, //TODO
                            .size = 0x100000 //TODO
                        },
                        /*{
                            .base = 0x90000000, //TODO
                            .size = 0x100000 //TODO
                        }*/
                    },
                    .dev_num = 4,
                    .devs = (struct vm_dev_region[]){
                        { //TIMER
                            .pa = 0xF8800000,
                            .va = 0xF8800000,
                            .size = 0x1000,
                            .interrupt_num = 1,
                            .interrupts = (irqid_t[]) {10},
                        },
                        {   //Ports 13 and 14 base is 13, 0x400 for each port
                            .pa = 0xF003D400,
                            .va = 0xF003D400,
                            .size = 0x400,
                        },
                        {   //Ports 13 and 14 base is 13, 0x400 for each port
                            .pa = 0xF003D800,
                            .va = 0xF003D800,
                            .size = 0x400,
                        },
                        { //UART
                            .pa = 0xF46C0000,
                            .va = 0xF46C0000,
                            .size = 0x200,
                            .interrupt_num = 1,
                            .interrupts = (irqid_t[]) {173},
                        },
                       /* {   //watchdog
                            .pa = 0xF0000000,
                            .va = 0xF0000000,
                            .size = 0x800,
                        },
                        {   //SMM+ccu+tri
                            .pa = 0xF0060000,
                            .va = 0xF0060000,
                            .size = 0x8100,
                        },
                        {   //DMTUs
                            .pa = 0xF0400000,
                            .va = 0xF0400000,
                            .size = 0x100000,
                        },
                        {   //NVM-DMU
                            .pa = 0xF8040000,
                            .va = 0xF8040000,
                            .size =  0x90000,
                        },

                        {   //SCU+SMU
                            .pa = 0xF0024000,
                            .va = 0xF0024000,
                            .size =  0x6000,
                        },
                        {   //SFRs shouldn't be needed
                            .pa = 0xF8800000,
                            .va = 0xF8800000,
                            .size = 0x180000,
                        },*/
                    },
                    .arch = {
                        .gspr_num = 1,
                        .gspr_groups = (unsigned long int[]){1},
                    }
                }
            },
        },
};