/*
 * Copyright (c) Bao Project and Contributors. All rights reserved
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <plat.h>

MEMORY {
    RAM (rwx)    : ORIGIN = PLAT_MEM_BASE, LENGTH = PLAT_MEM_SIZE    
}

ENTRY(_start)

SECTIONS {

    .start : {
        *(.start)
    } 

    .text :  {
        *(.text*)
    } 

    .rodata :  {
        *(.rodata*)
    }

    .data : {
        *(.data .data.*)
        PROVIDE(__global_pointer$ = . + 0x800);
        *(.sdata .sdata.* .sdata2.*)
    }

    .testframework : {
        testframework_start = . ;
        *(.testframework.PRIO* .testframework.prio*)
        *(.testframework.*)
        testframework_end = . ;        
    }
    
    .bss (NOLOAD) :  {	
        __bss_start = .;
        *(.bss* .sbss*) 
        *(COMMON)	
        __bss_end = .;
    }

    . = ALIGN(16);
    PROVIDE(_stack_base = .);
    . = . + 2M; /* 2M of total stack size */
    PROVIDE(_heap_base = .);
}
