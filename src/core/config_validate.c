/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/**
 * Boot-time validation of the static configuration, for debug builds only. init() calls
 * config_validate() on the master CPU once the console is up and before any VM is set up. Every
 * violated rule ends in a panic that names the VM and the field. Release builds do not contain
 * this file and keep their behaviour: the same mistakes surface later as an ERROR, or not at all.
 */

#include <bao.h>
#include <config.h>
#include <platform.h>
#include <cache.h>
#include <interrupts.h>

#define CONFIG_CHECK(cond, ...)                \
    do {                                       \
        if (!(cond)) {                         \
            panic("BAO CONFIG: " __VA_ARGS__); \
        }                                      \
    } while (0)

static bool page_aligned(unsigned long value)
{
    return IS_ALIGNED(value, PAGE_SIZE);
}

static bool colors_valid(colormap_t colors)
{
    return (COLOR_NUM >= (sizeof(colormap_t) * 8)) || ((colors >> COLOR_NUM) == 0);
}

static bool in_platform_memory(paddr_t base, size_t size)
{
    for (size_t i = 0; i < platform.region_num; i++) {
        if (range_in_range(base, size, platform.regions[i].base, platform.regions[i].size)) {
            return true;
        }
    }
    return false;
}

static bool in_vm_memory(const struct vm_platform* plat, vaddr_t base, size_t size)
{
    for (size_t i = 0; i < plat->region_num; i++) {
        if (range_in_range(base, size, plat->regions[i].base, plat->regions[i].size)) {
            return true;
        }
    }
    return false;
}

static bool in_vm_device(const struct vm_platform* plat, vaddr_t addr)
{
    for (size_t i = 0; i < plat->dev_num; i++) {
        struct vm_dev_region* dev = &plat->devs[i];
        if (dev->size > 0 && dev->va != INVALID_VA && range_in_range(addr, 1, dev->va, dev->size)) {
            return true;
        }
    }
    return false;
}

static void config_validate_platform(void)
{
    CONFIG_CHECK(platform.cpu_num > 0 && platform.cpu_num <= (size_t)PLAT_CPU_NUM,
        "platform: cpu_num %zu is not within 1 and PLAT_CPU_NUM (%zu)\n", platform.cpu_num,
        (size_t)PLAT_CPU_NUM);
    CONFIG_CHECK(!platform.cpu_master_fixed || platform.cpu_master < platform.cpu_num,
        "platform: fixed master cpu %lu does not exist\n", platform.cpu_master);
    CONFIG_CHECK(platform.region_num > 0 && platform.regions != NULL,
        "platform: no memory regions\n");
    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region* reg = &platform.regions[i];
        CONFIG_CHECK(reg->size > 0 && page_aligned(reg->base) && page_aligned(reg->size),
            "platform: region %zu (0x%lx, 0x%lx) is empty or not page aligned\n", i,
            (unsigned long)reg->base, (unsigned long)reg->size);
        for (size_t j = 0; j < i; j++) {
            CONFIG_CHECK(!range_overlap_range(reg->base, reg->size, platform.regions[j].base,
                             platform.regions[j].size),
                "platform: regions %zu and %zu overlap\n", i, j);
        }
    }
}

static void config_validate_shmem(size_t id, const struct shmem* shmem)
{
    CONFIG_CHECK(shmem->size > 0 && page_aligned(shmem->size),
        "shmem %zu: size 0x%lx is empty or not page aligned\n", id, (unsigned long)shmem->size);
    CONFIG_CHECK(colors_valid(shmem->colors), "shmem %zu: colors 0x%lx exceed the %zu colors\n", id,
        shmem->colors, COLOR_NUM);
    if (shmem->place_phys) {
        CONFIG_CHECK(page_aligned(shmem->phys) && in_platform_memory(shmem->phys, shmem->size),
            "shmem %zu: placement (0x%lx, 0x%lx) is not page aligned or outside memory\n", id,
            (unsigned long)shmem->phys, (unsigned long)shmem->size);
    }
}

static void config_validate_regions(size_t id, const struct vm_platform* plat)
{
    CONFIG_CHECK(plat->region_num == 0 || plat->regions != NULL,
        "vm %zu: region_num %zu without regions\n", id, plat->region_num);
    for (size_t i = 0; i < plat->region_num; i++) {
        struct vm_mem_region* reg = &plat->regions[i];
        CONFIG_CHECK(reg->size > 0 && page_aligned(reg->base) && page_aligned(reg->size) &&
                (reg->base + reg->size) > reg->base,
            "vm %zu: region %zu (0x%lx, 0x%lx) is empty, not page aligned or wraps around\n", id, i,
            (unsigned long)reg->base, (unsigned long)reg->size);
        CONFIG_CHECK(colors_valid(reg->colors),
            "vm %zu: region %zu colors 0x%lx exceed the %zu colors\n", id, i, reg->colors,
            COLOR_NUM);
        if (reg->place_phys) {
            CONFIG_CHECK(page_aligned(reg->phys) && in_platform_memory(reg->phys, reg->size),
                "vm %zu: region %zu placement (0x%lx, 0x%lx) is not page aligned or outside "
                "memory\n",
                id, i, (unsigned long)reg->phys, (unsigned long)reg->size);
        }
        for (size_t j = 0; j < i; j++) {
            CONFIG_CHECK(!range_overlap_range(reg->base, reg->size, plat->regions[j].base,
                             plat->regions[j].size),
                "vm %zu: regions %zu and %zu overlap\n", id, i, j);
        }
    }
}

static void config_validate_image(size_t id, const struct vm_config* vm)
{
    const struct vm_platform* plat = &vm->platform;

    if (vm->image.size > 0) {
        CONFIG_CHECK(in_vm_memory(plat, vm->image.base_addr, vm->image.size),
            "vm %zu: image (0x%lx, 0x%lx) is not inside a memory region\n", id,
            (unsigned long)vm->image.base_addr, (unsigned long)vm->image.size);
        if (vm->image.inplace) {
            CONFIG_CHECK(page_aligned(vm->image.base_addr) && page_aligned(vm->image.load_addr),
                "vm %zu: an in-place image must be page aligned (base 0x%lx, load 0x%lx)\n", id,
                (unsigned long)vm->image.base_addr, (unsigned long)vm->image.load_addr);
        }
    }
    CONFIG_CHECK(plat->region_num == 0 || in_vm_memory(plat, vm->entry, 1) ||
            in_vm_device(plat, vm->entry),
        "vm %zu: entry 0x%lx is not inside a memory region or a device\n", id,
        (unsigned long)vm->entry);
}

static void config_validate_ipcs(size_t id, const struct vm_platform* plat)
{
    CONFIG_CHECK(plat->ipc_num == 0 || plat->ipcs != NULL, "vm %zu: ipc_num %zu without ipcs\n", id,
        plat->ipc_num);
    for (size_t i = 0; i < plat->ipc_num; i++) {
        struct ipc* ipc = &plat->ipcs[i];
        CONFIG_CHECK(ipc->shmem_id < config.shmemlist_size,
            "vm %zu: ipc %zu names shmem %zu, but there are only %zu\n", id, i, ipc->shmem_id,
            config.shmemlist_size);
        CONFIG_CHECK(ipc->size > 0 && page_aligned(ipc->base),
            "vm %zu: ipc %zu (0x%lx, 0x%lx) is empty or not page aligned\n", id, i,
            (unsigned long)ipc->base, (unsigned long)ipc->size);
        CONFIG_CHECK(ipc->interrupt_num == 0 || ipc->interrupts != NULL,
            "vm %zu: ipc %zu has %zu interrupts but no array\n", id, i, ipc->interrupt_num);
        for (size_t j = 0; j < ipc->interrupt_num; j++) {
            CONFIG_CHECK(ipc->interrupts[j] < (unsigned)MAX_GUEST_INTERRUPTS,
                "vm %zu: ipc %zu interrupt %u is not below MAX_GUEST_INTERRUPTS (%u)\n", id, i,
                ipc->interrupts[j], (unsigned)MAX_GUEST_INTERRUPTS);
        }
    }
}

static void config_validate_devs(size_t id, const struct vm_platform* plat)
{
    CONFIG_CHECK(plat->dev_num == 0 || plat->devs != NULL, "vm %zu: dev_num %zu without devs\n", id,
        plat->dev_num);
    for (size_t i = 0; i < plat->dev_num; i++) {
        struct vm_dev_region* dev = &plat->devs[i];
        /* A device without MMIO (size 0) only carries interrupts and a bus master id. */
        if (!DEFINED(MMIO_SLAVE_SIDE_PROT) && dev->size > 0 && dev->va != INVALID_VA) {
            CONFIG_CHECK(page_aligned(dev->va) && page_aligned(dev->pa),
                "vm %zu: device %zu (va 0x%lx, pa 0x%lx, size 0x%lx) is not page aligned\n", id, i,
                (unsigned long)dev->va, (unsigned long)dev->pa, (unsigned long)dev->size);
            CONFIG_CHECK(!DEFINED(MEM_PROT_MPU) || dev->va == dev->pa,
                "vm %zu: device %zu must be identity mapped on an MPU platform\n", id, i);
            for (size_t j = 0; j < plat->region_num; j++) {
                CONFIG_CHECK(!range_overlap_range(dev->va, dev->size, plat->regions[j].base,
                                 plat->regions[j].size),
                    "vm %zu: device %zu overlaps memory region %zu\n", id, i, j);
            }
        }
        CONFIG_CHECK(dev->interrupt_num == 0 || dev->interrupts != NULL,
            "vm %zu: device %zu has %zu interrupts but no array\n", id, i, dev->interrupt_num);
        for (size_t j = 0; j < dev->interrupt_num; j++) {
            CONFIG_CHECK(dev->interrupts[j] < (unsigned)MAX_GUEST_INTERRUPTS &&
                    dev->interrupts[j] < (unsigned)MAX_INTERRUPT_LINES,
                "vm %zu: device %zu interrupt %u is not below MAX_GUEST_INTERRUPTS (%u)\n", id, i,
                dev->interrupts[j], (unsigned)MAX_GUEST_INTERRUPTS);
        }
    }
}

static void config_validate_remio(size_t id, const struct vm_platform* plat)
{
    CONFIG_CHECK(plat->remio_dev_num == 0 || plat->remio_devs != NULL,
        "vm %zu: remio_dev_num %zu without remio_devs\n", id, plat->remio_dev_num);
    for (size_t i = 0; i < plat->remio_dev_num; i++) {
        struct remio_dev* dev = &plat->remio_devs[i];
        CONFIG_CHECK(dev->type == REMIO_DEV_FRONTEND || dev->type == REMIO_DEV_BACKEND,
            "vm %zu: remote I/O device %zu has an unknown type\n", id, i);
        CONFIG_CHECK(dev->shmem.shmem_id < config.shmemlist_size,
            "vm %zu: remote I/O device %zu names shmem %zu, but there are only %zu\n", id, i,
            dev->shmem.shmem_id, config.shmemlist_size);
        CONFIG_CHECK(dev->bind_key <= UINT8_MAX,
            "vm %zu: remote I/O device %zu bind key %zu does not fit the 8-bit message field\n", id,
            i, dev->bind_key);
        CONFIG_CHECK(dev->interrupt < (unsigned)MAX_GUEST_INTERRUPTS,
            "vm %zu: remote I/O device %zu interrupt %u is not below MAX_GUEST_INTERRUPTS (%u)\n",
            id, i, dev->interrupt, (unsigned)MAX_GUEST_INTERRUPTS);
        if (dev->type == REMIO_DEV_FRONTEND) {
            CONFIG_CHECK(dev->size > 0 && page_aligned(dev->va),
                "vm %zu: remote I/O frontend %zu (0x%lx, 0x%lx) is empty or not page aligned\n", id,
                i, (unsigned long)dev->va, (unsigned long)dev->size);
        }
    }
}

static void config_validate_vm(size_t id, const struct vm_config* vm)
{
    const struct vm_platform* plat = &vm->platform;

    CONFIG_CHECK(plat->cpu_num >= 1 && plat->cpu_num <= platform.cpu_num,
        "vm %zu: cpu_num %zu is not within 1 and the platform's %zu cpus\n", id, plat->cpu_num,
        platform.cpu_num);
    CONFIG_CHECK(platform.cpu_num >= (sizeof(cpumap_t) * 8) ||
            (vm->cpu_affinity >> platform.cpu_num) == 0,
        "vm %zu: cpu_affinity 0x%lx names cpus the platform does not have\n", id, vm->cpu_affinity);
    CONFIG_CHECK(colors_valid(vm->colors), "vm %zu: colors 0x%lx exceed the %zu colors\n", id,
        vm->colors, COLOR_NUM);
    config_validate_regions(id, plat);
    config_validate_image(id, vm);
    config_validate_ipcs(id, plat);
    config_validate_devs(id, plat);
    config_validate_remio(id, plat);
}

void config_validate(void)
{
    size_t cpus_needed = 0;

    config_validate_platform();
    CONFIG_CHECK(colors_valid(config.hyp.colors), "hypervisor colors 0x%lx exceed the %zu colors\n",
        config.hyp.colors, COLOR_NUM);
    CONFIG_CHECK(config.shmemlist_size == 0 || config.shmemlist != NULL,
        "shmemlist_size %zu without a shmemlist\n", config.shmemlist_size);
    for (size_t i = 0; i < config.shmemlist_size; i++) {
        config_validate_shmem(i, &config.shmemlist[i]);
    }
    CONFIG_CHECK(config.vmlist_size == 0 || config.vmlist != NULL,
        "vmlist_size %zu without a vmlist\n", config.vmlist_size);
    for (size_t i = 0; i < config.vmlist_size; i++) {
        config_validate_vm(i, &config.vmlist[i]);
        cpus_needed += config.vmlist[i].platform.cpu_num;
    }
    CONFIG_CHECK(cpus_needed <= platform.cpu_num,
        "the VMs need %zu cpus but the platform has %zu\n", cpus_needed, platform.cpu_num);

    INFO("configuration validated\n");
}
