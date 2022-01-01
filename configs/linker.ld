/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

ASSERT(DEFINED(config), "Error: No config structure in configuration file");

SECTIONS
{   
    . = 0x0;

    .config : {
        KEEP(*(.config))
        KEEP(*(COMMON))
    }
    _config_end = ALIGN(CONSTANT(COMMONPAGESIZE));

    .vm_images : SUBALIGN(CONSTANT(COMMONPAGESIZE)) {
        KEEP(*(.vm_image*)) 
    }  
    _images_end = ALIGN(CONSTANT(COMMONPAGESIZE));

}
