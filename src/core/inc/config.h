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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <bao.h>
#include <platform.h>

#define VM_IMAGE(img_name, img_path)                                         \
    extern uint8_t _##img_name##_vm_size;                                    \
    extern uint8_t _##img_name##_vm_beg;                                     \
    asm(".pushsection .vm_image_" XSTR(img_name) ", \"a\"\n\t"               \
        ".global _" XSTR(img_name) "_vm_beg\n\t"                             \
        "_" XSTR(img_name) "_vm_beg:\n\t"                                    \
        ".incbin " XSTR(img_path) "\n\t"                                     \
        "_" XSTR(img_name) "_vm_end:\n\t"                                    \
        ".global _" XSTR(img_name) "_vm_size\n\t"                            \
        ".set _" XSTR(img_name) "_vm_size,  (_" XSTR(img_name) "_vm_end - _" \
        #img_name "_vm_beg)\n\t"                                             \
        ".popsection");

#define VM_IMAGE_OFFSET(img_name) ((paddr_t)&_##img_name##_vm_beg)
#define VM_IMAGE_SIZE(img_name) ((size_t)&_##img_name##_vm_size)

#define VM_IMAGE_BUILTIN(img_name, image_base_addr) \
    {\
        .base_addr = image_base_addr,\
        .load_addr = VM_IMAGE_OFFSET(img_name),\
        .size = VM_IMAGE_SIZE(img_name),\
        .separately_loaded = false,\
    }

#define VM_IMAGE_LOADED(image_base_addr, image_load_addr, image_size) \
    {\
        .base_addr = image_base_addr,\
        .load_addr = image_load_addr,\
        .size = image_size,\
        .separately_loaded = true,\
    }

/* CONFIG_HEADER is just defined for compatibility with older configs */
#define CONFIG_HEADER

struct vm_config {
    /**
     * To setup the image field either the VM_IMAGE_BUILTIN or VM_IMAGE_LOADED
     * macros should be used.
     */
    struct {
        /* Image load address in VM's address space */
        vaddr_t base_addr;
        /* Image load address in hyp address space */
        paddr_t load_addr;
        /* Image size */
        size_t size;
        /**
         * Informs the hypervisor if the VM image is to be loaded
         * separately by a bootloader.
         */
        bool separately_loaded;
        /* Dont copy the image */
        bool inplace;
    } image;

    /* Entry point address in VM's address space */
    vaddr_t entry;
    /**
     * A bitmap signaling the preferred physical cpus assigned to the VM.
     * If this value is each mutual exclusive for all the VMs, this field
     * allows to direcly assign specific physical cpus to the VM.
     */
    cpumap_t cpu_affinity;

    /**
     * A bitmap for the assigned colors of the VM. This value is truncated
     * depending on the number of available colors calculated at runtime
     */
    colormap_t colors;

    /**
     * A description of the virtual platform available to the guest, i.e.,
     * the virtual machine itself.
     */

    struct platform_desc platform;

};

extern struct config {
    /* Hypervisor colors */
    colormap_t hyp_colors;

    /* Definition of shared memory regions to be used by VMs */
    size_t shmemlist_size;
    struct shmem *shmemlist;

    /* The number of VMs specified by this configuration */
    size_t vmlist_size;

    /* Array list with VM configuration */
    struct vm_config vmlist[];

} config;

void config_adjust_vm_image_addr(paddr_t load_addr);

#endif /* __CONFIG_H__ */
