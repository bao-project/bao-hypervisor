/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>

extern uint32_t plat_ints[];
extern uint32_t plat_int_num;

void arch_platform_defs() {
    unsigned int bitmap[64] = {0};
    unsigned int count = plat_int_num;

    for(int i = 0; i < count; i++){
        unsigned int irq = plat_ints[i];
        unsigned int index = irq / 32;
        unsigned int bit = irq % 32;

        if(index < 64 && bit < 32)
            bitmap[index] |= 1UL << bit;
    }

    printf ("#define INTERRUPTS_COUNT %d\n", count);
    printf("#define INTERRUPTS_BITMAP {\t");
    for(int i = 0; i < 64; i++)
    {
        if(i && i % 4 == 0)
            printf(" \\\n\t\t\t\t\t\t");
        if(i != 63)
            printf("0x%x, ", bitmap[i]);
        else printf("0x%x }\n", bitmap[i]);
    }

}
