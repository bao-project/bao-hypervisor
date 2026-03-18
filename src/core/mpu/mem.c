/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 *
 * @file    mem.c
 * @brief   This file implements the configuration for the address space access
 *          control for MPU-based systems.
 *
 * The term "Virtual MPU" (vMPU) is a Bao-specific terminology.
 * Consider familiarizing with the concept in the paper "Let’s Get Physical:
 * Rethinking the Static Partitioning Hypervisor Architecture for an MMU-less
 * Memory Model"
 */

#include <mem.h>
#include <cpu.h>
#include <vm.h>
#include <bao.h>
#include <fences.h>
#include <platform_defs.h>
#include <objpool.h>
#include <config.h>

#define MEM_BROADCAST      (true)
#define MEM_DONT_BROADCAST (false)

#define MEM_LOCKED         (true)
#define MEM_NOT_LOCKED     (false)

struct shared_region {
    enum AS_TYPE as_type;
    asid_t asid;
    struct mp_region region;
    cpumap_t sharing_cpus;
    bool lock;
};

void mem_handle_broadcast_region(uint32_t event, uint64_t data);
bool mem_unmap_range(struct addr_space* as, vaddr_t vaddr, size_t size, bool broadcast);

enum { MEM_INSERT_REGION, MEM_REMOVE_REGION, MEM_UPDATE_REGION };

#define SHARED_REGION_POOL_SIZE_DEFAULT (128)
#ifndef SHARED_REGION_POOL_SIZE
#define SHARED_REGION_POOL_SIZE SHARED_REGION_POOL_SIZE_DEFAULT
#endif
OBJPOOL_ALLOC(shared_region_pool, struct shared_region, SHARED_REGION_POOL_SIZE);

/**
 * @brief Retrieve a virtual MPU entry from an address space
 * Gets the MPU entry associated with a given MPU entry ID from the MPU mapping of
 * the address space.
 * @param as Pointer to the address space
 * @param mpid MPU entry identifier
 * @return struct mpe* Pointer to the MPU entry, or NULL if invalid mpid
 * @see addr_space, mpid_t, mpe, VMPU_NUM_ENTRIES
 */
static inline struct mpe* mem_vmpu_get_entry(struct addr_space* as, mpid_t mpid)
{
    if (mpid < VMPU_NUM_ENTRIES) {
        return &as->vmpu.node[mpid];
    }
    return NULL;
}

/**
 * @brief Compare two MPU entries by base address
 * Used for ordering MPU entries of the virtual MPU list based on their
 * base addresses.
 * @param _n1 Pointer to first node
 * @param _n2 Pointer to second node
 * @return int 1 if n1 > n2, -1 if n1 < n2, 0 if equal
 * @see mpe, node_t, vaddr_t, mp_region
 */
static int vmpu_node_cmp(node_t* _n1, node_t* _n2)
{
    struct mpe* n1 = (struct mpe*)_n1;
    struct mpe* n2 = (struct mpe*)_n2;

    if (n1->region.base > n2->region.base) {
        return 1;
    } else if (n1->region.base < n2->region.base) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * @brief Set up an MPU entry of the virtual MPU
 * Configures an MPU entry with the given memory region parameters and adds it
 * to the ordered list of MPU entries in the address space configuration.
 * @param as Pointer to the address space
 * @param mpid MPU entry identifier
 * @param mpr Pointer to the memory protection region configuration
 * @param locked Whether the entry should be locked
 * @see mem_vmpu_get_entry(), list_insert_ordered(), mpe, addr_space, mpid_t,
 *      mp_region, node_t, vmpu_node_cmp(), MPE_S_VALID.
 */
static void mem_vmpu_set_entry(struct addr_space* as, mpid_t mpid, struct mp_region* mpr,
    bool locked)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = mpr->base;
    mpe->region.size = mpr->size;
    mpe->region.mem_flags = mpr->mem_flags;
    mpe->region.as_sec = mpr->as_sec;
    mpe->state = MPE_S_VALID;
    mpe->mpid = mpid;
    mpe->lock = locked;

    list_insert_ordered(&as->vmpu.ordered_list, (node_t*)&as->vmpu.node[mpid], vmpu_node_cmp);
}

/**
 * @brief Clear an MPU entry in the virtual MPU
 * Invalidates the data in a MPU entry, effectively clearing it for
 * @param as Pointer to the address space configuration
 * @param mpid MPU entry identifier
 * @see mem_vmpu_get_entry(), as_sec_t, mpe, addr_space, mpid_t, PTE_INVALID,
 *      MPE_S_INVALID
 */
static void mem_vmpu_clear_entry(struct addr_space* as, mpid_t mpid)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = 0;
    mpe->region.size = 0;
    mpe->region.mem_flags = PTE_INVALID;
    mpe->region.as_sec = SEC_UNKNOWN;
    mpe->state = MPE_S_INVALID;
    mpe->lock = false;
}

/**
 * @brief Free an MPU entry from the address space configuration.
 * Clears the entry's contents and marks it as free for reuse. Also removes
 * the entry from the ordered list of MPU entries.
 * @param as Pointer to the address space
 * @param mpid MPU entry identifier
 * @see mem_vmpu_clear_entry(), mem_vmpu_get_entry(), list_rm(), MPE_S_FREE, node_t,
 *      addr_space, mpid_t, mpe
 */
static void mem_vmpu_free_entry(struct addr_space* as, mpid_t mpid)
{
    mem_vmpu_clear_entry(as, mpid);
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
    mpe->state = MPE_S_FREE;

    list_rm(&as->vmpu.ordered_list, (node_t*)&as->vmpu.node[mpid]);
}

/**
 * @brief Allocate a new MPU entry of the virtual MPU
 * Search for a free MPU entry in the address space configuration and return its ID.
 * @param as Pointer to the address space
 * @return mpid_t ID of the allocated entry, or INVALID_MPID if no MPU entries are available.
 * @see mem_vmpu_get_entry, addr_space, mpid_t, INVALID_MPID, VMPU_NUM_ENTRIES,
 *      MPE_S_INVALID, MPE_S_FREE
 */
static mpid_t mem_vmpu_allocate_entry(struct addr_space* as)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        struct mpe* mpe = mem_vmpu_get_entry(as, i);
        if (mpe->state == MPE_S_FREE) {
            mpid = i;
            mpe->state = MPE_S_INVALID;
            break;
        }
    }

    return mpid;
}

/**
 * @brief Deallocate an MPU entry of the virtual MPU
 * Resets all fields of the specified MPU entry and marks it as free,
 * making it available for future allocations.
 * @param as Pointer to the address space
 * @param mpid MPU entry identifier
 * @see mem_vmpu_get_entry(), addr_space, mpid_t, mpe, vaddr_t, SEC_UNKNOWN,
 *      AS_SEC, MPE_S_FREE, PTE_INVALID
 */
static void mem_vmpu_deallocate_entry(struct addr_space* as, mpid_t mpid)
{
    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    mpe->region.base = 0;
    mpe->region.size = 0;
    mpe->region.mem_flags = PTE_INVALID;
    mpe->region.as_sec = SEC_UNKNOWN;
    mpe->state = MPE_S_FREE;
    mpe->lock = false;
}

/**
 * @brief Find an MPU entry containing a given address
 * Searches through all MPU entries in the address space to find one that
 * contains the specified virtual address.
 * @param as Pointer to the address space configuration
 * @param addr Virtual address to look for in the virtual MPU entries
 * @return mpid_t ID of the matching entry, or INVALID_MPID if not found
 * @see mem_vmpu_get_entry, INVALID_MPID, VMPU_NUM_ENTRIES, mpe, vaddr_t, addr_space,
 *      VMPU_NUM_ENTRIES, mpid_t, MPE_S_VALID.
 */
static mpid_t mem_vmpu_get_entry_by_addr(struct addr_space* as, vaddr_t addr)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        struct mpe* mpe = mem_vmpu_get_entry(as, i);

        if (mpe->state != MPE_S_VALID) {
            continue;
        }

        vaddr_t limit_addr = mpe->region.base + mpe->region.size;
        if ((addr >= mpe->region.base) && (addr < limit_addr)) {
            mpid = i;
            break;
        }
    }

    return mpid;
}

/**
 * @brief   Configure the virtual MPU layer with hypervisor-owned regions that
 *          are already configured in the MPU during system boot.
 * @note It supports MEM_NON_UNIFIED architectures.
 * @see vaddr_t, _image_start, _image_load_end, _image_noload_start, _image_end,
 *      mem_map(), cpu(), PTE_HYP_FLAGS_CODE, PTE_HYP_FLAGS,
 */
static void mem_init_boot_regions(void)
{
    /**
     * Add hypervisor mpu entries set up during boot to the vmpu:
     *  - hypervisor image (loadable and non-loadable)
     *  - private cpu region
     */

    extern uint8_t _image_start, _image_load_end, _image_noload_start, _image_end;
    vaddr_t image_start = (vaddr_t)&_image_start;
    vaddr_t image_load_end = (vaddr_t)&_image_load_end;
    vaddr_t image_noload_start = (vaddr_t)&_image_noload_start;
    vaddr_t image_end = (vaddr_t)&_image_end;

#ifdef MEM_NON_UNIFIED
    extern uint8_t _data_vma_start;
    vaddr_t data_vma_start = (vaddr_t)&_data_vma_start;
#endif

    struct mp_region mpr;

    bool separate_noload_region = image_load_end != image_noload_start;
    vaddr_t first_region_end = separate_noload_region ? image_load_end : image_end;

    mpr = (struct mp_region){
        .base = image_start,
        .size = (size_t)(first_region_end - image_start),
#ifdef MEM_NON_UNIFIED
        .mem_flags = PTE_HYP_FLAGS_CODE,
#else
        .mem_flags = PTE_HYP_FLAGS,
#endif
        .as_sec = SEC_HYP_IMAGE,
    };
    mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);

    if (separate_noload_region) {
        mpr = (struct mp_region){
#ifdef MEM_NON_UNIFIED
            .base = data_vma_start,
            .size = (size_t)(image_end - data_vma_start),
#else
            .base = image_noload_start,
            .size = (size_t)image_end - image_noload_start,
#endif
            .mem_flags = PTE_HYP_FLAGS,
            .as_sec = SEC_HYP_IMAGE,
        };
        mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);
    }

    mpr = (struct mp_region){
        .base = (vaddr_t)cpu(),
        .size = ALIGN(sizeof(struct cpu), PAGE_SIZE),
        .mem_flags = PTE_HYP_FLAGS,
        .as_sec = SEC_HYP_PRIVATE,
    };
    mem_map(&cpu()->as, &mpr, MEM_DONT_BROADCAST, MEM_LOCKED);
}

/**
 * @brief   Initialize the memory access control mechanism according to the
 *          current CPU's address space configuration.
 * Set up the MPU hardware, initialize the hypervisor address space,
 * and configure boot-time memory regions.
 * @see mpu_init(), as_init(), mem_init_boot_regions(), mpu_enable(), cpu(),
 *      AS_TYPE, cpu_is_master(), addr_space, AS_TYPE, mem_mmio_init_regions(),
 *      MMIO_SLAVE_SIDE_PROT
 */
void mem_prot_init()
{
    mpu_init();
    as_init(&cpu()->as, AS_HYP, 0);
    mem_init_boot_regions();
    if (DEFINED(MMIO_SLAVE_SIDE_PROT) && cpu_is_master()) {
        mem_mmio_init_regions(&cpu()->as);
    }
    mpu_enable();
}

/**
 * @brief   Calculate the memory size needed to fit the CPU private data structure
 *          during Bao's startup.
 * Returns the page-aligned size required for the CPU structure allocation
 * during boot time.
 * @return size_t Size in bytes to fit a CPU private data structure.
 */
size_t mem_cpu_boot_alloc_size()
{
    size_t size = ALIGN(sizeof(struct cpu), PAGE_SIZE);
    return size;
}

/**
 * @brief Initialize configured memory regions in which devices are mapped.
 * @param as Address space configuration, containing the list of configured MMIO devices' regions.
 * @see mem_alloc_map_dev, NUM_PAGES(), mem_region, vaddr_t, AS_TYPE
 */
void mem_mmio_init_regions(struct addr_space* as)
{
    for (unsigned long i = 0; i < platform.mmio_region_num; i++) {
        mem_alloc_map_dev(as, as->type == AS_VM ? SEC_VM_ANY : SEC_HYP_GLOBAL,
            platform.mmio_regions[i].base, platform.mmio_regions[i].base,
            NUM_PAGES(platform.mmio_regions[i].size));
    }
}

/**
 * @brief Provide unique incremental VM address space ID at runtime.
 * @param as    Address space for which the ID shall be allocated.
 * @return unsigned long Unique ID. Always greater than 0.
 * @see spin_lock(), spin_unlock(), spinlock_t, asid_t, AS_TYPE
 */
static unsigned long as_id_alloc(struct addr_space* as)
{
    static spinlock_t as_id_alloc_lock = SPINLOCK_INITVAL;
    static asid_t asid_counter = 1;
    unsigned long ret = 0;

    spin_lock(&as_id_alloc_lock);
    if (as->type != AS_HYP) {
        ret = asid_counter;
        asid_counter++;
    }
    spin_unlock(&as_id_alloc_lock);

    return ret;
}

/**
 * @brief Initialize an address space structure in a MPU-based system.
 * Set up a new address space with the given type and ID.
 * @note Cache coloring is not a feature of MPU-based systems and @param color will not be used.
 * @param as Pointer to address space configuration.
 * @param type Type of address space (AS_HYP, AS_VM)
 * @param colors Memory region color (unused in MPU-based systems)
 * @see as_arch_init, mem_vmpu_free_entry, as_id_alloc, addr_space, AS_TYPE
 *      colormap_t, spinlock_t, VMPU_NUM_ENTRIES, SPINLOCK_INITVAL, list, vmpu.
 */
void as_init(struct addr_space* as, enum AS_TYPE type, colormap_t colors)
{
    UNUSED_ARG(colors);

    as->type = type;
    as->colors = 0;
    as->id = as_id_alloc(as);
    as->lock = SPINLOCK_INITVAL;
    as_arch_init(as);

    list_init(&(as->vmpu.ordered_list));

    for (size_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        mem_vmpu_free_entry(as, i);
    }
}

/**
 * @brief Frees physical pages back to their pool
 * Iterates through page pools to find the one containing the pages to be freed,
 * then clears the corresponding bits in the pool's bitmap.
 * @param ppages Pointer to physical pages structure to free
 * @see page_pool_list, bitmap_clear_consecutive, spin_lock(), spin_unlock(), page_pool,
 *      PAGE_SIZE, in_rage, range_in_range, ppages.
 */
static void mem_free_ppages(struct ppages* ppages)
{
    list_foreach (page_pool_list, struct page_pool, pool) {
        spin_lock(&pool->lock);
        if (in_range(ppages->base, pool->base, pool->num_pages * PAGE_SIZE)) {
            size_t index = (ppages->base - pool->base) / PAGE_SIZE;
            bitmap_clear_consecutive(pool->bitmap, index, ppages->num_pages);
        }
        spin_unlock(&pool->lock);
    }
}

/**
 * @brief Handles memory protection synchronization messages
 * Message handler for memory protection related IPI messages between CPUs.
 * @param event Event type for the message
 * @param data Message data containing region information
 * @see mem_handle_broadcast_region, CPU_MSG_HANDLER
 */
static void mem_msg_handler(uint32_t event, uint64_t data)
{
    mem_handle_broadcast_region(event, data);
}
CPU_MSG_HANDLER(mem_msg_handler, MEM_PROT_SYNC)

/**
 * @brief Determines which CPUs share an address space.
 * Calculates the CPU mask for a given address space and section type.
 * Handles both hypervisor and VMs' address spaces.
 * @param as Addres space configuration to check.
 * @param section Section type to check.
 * @return cpumap_t CPU map of the CPUs that share the address space configuration.
 * @see addr_space, as_sec_t, BIT_MASK(), cpumap_t, cpu(), vcpu, vm,
 */
static cpumap_t mem_section_shared_cpus(struct addr_space* as, as_sec_t section)
{
    cpumap_t cpus = 0;
    if (as->type == AS_HYP) {
        if ((section == SEC_HYP_GLOBAL) || (section == SEC_HYP_IMAGE)) {
            cpus = BIT_MASK(0, PLAT_CPU_NUM);
        } else if (section == SEC_HYP_VM) {
            /**
             * If we don't have a valid vcpu at this point, it means we are creating this region
             * before even having a vm. Therefore, the sharing of the region must be guaranteed by
             * other means (e.g. vmm_vm_install)
             */
            if (cpu()->vcpu != NULL) {
                cpus = cpu()->vcpu->vm->cpus;
            }
        }
    } else {
        cpus = cpu()->vcpu->vm->cpus;
    }

    return cpus;
}

/**
 * @brief Broadcasts memory region changes to other CPUs
 * Notifies other CPUs about changes to memory regions that are shared
 * across multiple cores.
 * @param as Pointer to address space being modified
 * @param mpr Pointer to memory protection region being changed
 * @param op Operation being performed (insert/remove/update)
 * @param locked Whether the region should be locked
 * @see mem_section_shared_cpus, shared_region_pool, addr_space, mp_region, cpumap_t,
 *      mp_region, as_sec_t, shared_region, cpuid_t, PLAT_CPU_NUM, bit_get, cpu(),
 *      cpuid_t, objpool_alloc, cpu_send_msg, cpu_msg, ERROR()
 */
static void mem_region_broadcast(struct addr_space* as, struct mp_region* mpr, uint32_t op,
    bool locked)
{
    cpumap_t shared_cpus = mem_section_shared_cpus(as, mpr->as_sec);

    if (shared_cpus == 0) {
        return;
    }

    struct shared_region shared_region = {
        .as_type = as->type,
        .asid = as->id,
        .region = *mpr,
        .lock = locked,
    };

    for (cpuid_t cpuid = 0; cpuid < PLAT_CPU_NUM; cpuid++) {
        if ((cpu()->id != cpuid) && bit_get(shared_cpus, cpuid)) {
            struct shared_region* node = objpool_alloc(&shared_region_pool);
            if (node == NULL) {
                ERROR("Failed allocating shared region node");
            }
            *node = shared_region;
            struct cpu_msg msg = { (uint32_t)MEM_PROT_SYNC, op, (uintptr_t)node };
            cpu_send_msg(cpuid, &msg);
        }
    }
}

/**
 * @brief Quert whether a change in the address space configuration shall be broadcasted or not by design.
 * @param as Address space affected by the change.
 * @param mpr Memory region affected by the change.
 * @param broadcast Expected value of the broadcast query.
 * @return false if the region or address space are strictly owned by the hypervisor, broadcast otherwise.
 * @see as_sec_t, AS_TYPE, addr_space, mp_region
 */
static bool mem_broadcast(struct addr_space* as, struct mp_region* mpr, bool broadcast)
{
    if (as->type == AS_HYP && mpr->as_sec == SEC_HYP_PRIVATE) {
        return false;
    }

    return broadcast;
}

/**
 * @brief Verify whether a memory region is locked by design (owned by the hypervisor) or not.
 * @param mpr memory region of which lock to verify.
 * @param locked the value returned if the region is locked by design.
 * @return true if the region belong to the hypervisor, else equal to locked.
 * @see mp_region, as_sec_t.
 */
static bool mem_check_forced_locked(struct mp_region* mpr, bool locked)
{
    if (mpr->as_sec == SEC_HYP_PRIVATE || mpr->as_sec == SEC_HYP_VM ||
        mpr->as_sec == SEC_HYP_IMAGE) {
        return true;
    }

    return locked;
}

/**
 * @brief Maps and inserts a memory region into vMPU entries. Optionally it broadcast the vMPU addition.
 * @param as Address space configuration from which the region is mapped.
 * @param mpid Identifier of the vMPU entry.
 * @param mpr Pointer to the memory protection region configuration.
 * @param broadcast Option to broadcast the change via IPI to other CPUs.
 * @param locked Option to lock the vMPU entry's memory region.
 * @return true if the vMPU entry has been successfully inserted in the address space configuration, false otherwise.
 * @see addr_space, mpid_t, mp_region, mem_check_forced_locked, mpu_map(), mem_vmpu_set_entry(),
 *      mem_broadcast(), mem_region_broadcast(), MEM_INSERT_REGION
 */
static bool mem_vmpu_insert_region(struct addr_space* as, mpid_t mpid, struct mp_region* mpr,
    bool broadcast, bool locked)
{
    bool lock = mem_check_forced_locked(mpr, locked);
    if (mpid == INVALID_MPID) {
        return false;
    }

    if (mpu_map(as, mpr, lock)) {
        mem_vmpu_set_entry(as, mpid, mpr, lock);
        if (mem_broadcast(as, mpr, broadcast)) {
            mem_region_broadcast(as, mpr, MEM_INSERT_REGION, lock);
        }
        return true;
    }

    return false;
}

/**
 * @brief Update a vMPU entry with a different memory region.
 * @param as Address space configuration to be updated.
 * @param mpid vMPU entry ID to be updated
 * @param merge_reg Merged region to be assign to the vMPU entry
 * @param broadcast Option to broadcast the vMPU entry update to other CPUs.
 * @param locked Option to lock the vMPU entry configuration.
 * @return true if the vMPU entry was updated successfully, false otherwise.
 * @see mpu_update(), addr_space, mpid_t, mp_region, mem_vmpu_get_entry(), mem_broadcast(),
 *      mem_region_broadcast(), MEM_UPDATE_REGION.
 */
static bool mem_vmpu_update_region(struct addr_space* as, mpid_t mpid, struct mp_region merge_reg,
    bool broadcast, bool locked)
{
    bool merged = false;

    if (mpu_update(as, &merge_reg)) {
        struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
        mpe->region = merge_reg;
        if (mem_broadcast(as, &mpe->region, broadcast)) {
            mem_region_broadcast(as, &mpe->region, MEM_UPDATE_REGION, locked);
        }
        merged = true;
    }
    return merged;
}

/**
 * @brief Remove vMPU entry from address space configuration.
 * @param as Address space configuration to be altered.
 * @param mpid vMPU entry ID to remove.
 * @param broadcast Option to broadcast the removal to other CPUs
 * @return true if the vMPU entry has been removed successfully, false otherwise.
 * @see addr_space, mpid_t, mpe, mem_vmpu_get_entry(), mem_broadcast(), mem_region_broadcast()
 *      MEM_REMOVE_REGION, mpu_unmap(), mem_vmpu_free_entry()
 */
static bool mem_vmpu_remove_region(struct addr_space* as, mpid_t mpid, bool broadcast)
{
    bool removed = false;

    struct mpe* mpe = mem_vmpu_get_entry(as, mpid);

    if ((mpe != NULL) && (mpe->state == MPE_S_VALID)) {
        bool lock = mpe->lock;
        if (mem_broadcast(as, &mpe->region, broadcast)) {
            mem_region_broadcast(as, &mpe->region, MEM_REMOVE_REGION, lock);
        }
        mpu_unmap(as, &mpe->region);
        mem_vmpu_free_entry(as, mpid);
        removed = true;
    }

    return removed;
}

/**
 * @brief Handle broadcasted events in which a new vMPU entry is inserted (mapped).
 * @param as Address space in which the vMPU entry is inserted.
 * @param mpr Memory region that has been inserted.
 * @param locked Option to lock the vMPU configuration of the memory region.
 * @see addr_space, mp_region, AS_TYPE, mem_map(), cpu()
 */
static void mem_handle_broadcast_insert(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    if (as->type == AS_HYP) {
        mem_map(&cpu()->as, mpr, MEM_DONT_BROADCAST, locked);
    } else {
        mpu_map(as, mpr, locked);
    }
}

/**
 * @brief Handle vMPU entry removal event by unmapping the broadcasted memory region from its CPU-bound MPU configuration.
 * @note    It does not call mpu_unmap() if the address space belongs to the hypevisor.
 *          This is to avoid broadcasting the configuration to all CPUs.
 * @param as Address space configuration to alter.
 * @param mpr Memory protected region to remove.
 * @see addr_space, mp_region, mem_unmap_range(), AS_TYPE, cpu(), mpu_unmap()
 */
static void mem_handle_broadcast_remove(struct addr_space* as, struct mp_region* mpr)
{
    if (as->type == AS_HYP) {
        /*
            We don't use mpu_unmap because that API forces a broadcast.
            During the handle of a broadcast we don't want that, to avoid
            a chain of broadcasts
        */
        mem_unmap_range(&cpu()->as, mpr->base, mpr->size, MEM_DONT_BROADCAST);
    } else {
        mpu_unmap(as, mpr);
    }
}

/**
 * @brief Updates memory region
 * The memory protected region is searched in the address space configuration and,
 * if found, the region boundaries are update.
 * Optionally, the update is propagated via broadcast message to all CPUs.
 * @param as Address space configuration
 * @param mpr Memory region to update
 * @param broadcast Option to broadcast the update to other CPUs.
 * @param locked Option to lock the updated vMPU entry.
 * @return true if the memory region is updated successfuly as requested.
 * @return false if the memory region cannot be updated
 * @see addr_space, mp_region, mpid_t, INVALID_MPID, mpe, list_foreach(), mem_vmpu_update_region()
 */
static bool mem_update(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked)
{
    mpid_t update_mpid = INVALID_MPID;
    list_foreach (as->vmpu.ordered_list, struct mpe, cur) {
        if (cur->region.base == mpr->base && cur->region.size != mpr->size) {
            update_mpid = cur->mpid;
            break;
        }
    }
    if (update_mpid != INVALID_MPID) {
        return mem_vmpu_update_region(as, update_mpid, *mpr, broadcast, locked);
    }
    return false;
}

/**
 * @brief   Perform vMPU configuration update upon reception of a memory
 *          protection synchronization's broadcasted message.
 * @param as Address space configuration to update.
 * @param mpr Memory region to update
 * @param locked Option to lock the updated vMPU region for the receiving CPU.
 * @see addr_space, mp_region, AS_TYPE, mem_update, cpu(),
 */
static void mem_handle_broadcast_update(struct addr_space* as, struct mp_region* mpr, bool locked)
{
    if (as->type == AS_HYP) {
        mem_update(&cpu()->as, mpr, MEM_DONT_BROADCAST, locked);
    } else {
        mpu_update(as, mpr);
    }
}

/**
 * @brief Handle broadcasted message on MPU regions' configuration changes
 * @param event The event associated with the broadcasted message.
 * @param data The data in the broadcasted message.
 * @see MEM_INSERT_REGION, MEM_REMOVE_REGION, MEM_UPDATE_REGION, ERROR(),
 *      mem_handle_broadcast_insert(), mem_handle_broadcast_remove(),
 *      mem_handle_broadcast_update(), objpool_free(), AS_TYPE, shared_region,
 *      cpu(), addr_space
 */
void mem_handle_broadcast_region(uint32_t event, uint64_t data)
{
    struct shared_region* sh_reg = (struct shared_region*)(uintptr_t)data;

    if (sh_reg != NULL) {
        struct addr_space* as;
        if (sh_reg->as_type == AS_HYP) {
            as = &cpu()->as;
        } else {
            struct addr_space* vm_as = &cpu()->vcpu->vm->as;
            if (vm_as->id != sh_reg->asid) {
                ERROR("Received shared region for unknown vm address space.");
            }
            as = vm_as;
        }

        switch (event) {
            case MEM_INSERT_REGION:
                mem_handle_broadcast_insert(as, &sh_reg->region, sh_reg->lock);
                break;
            case MEM_REMOVE_REGION:
                mem_handle_broadcast_remove(as, &sh_reg->region);
                break;
            case MEM_UPDATE_REGION:
                mem_handle_broadcast_update(as, &sh_reg->region, sh_reg->lock);
                break;
            default:
                ERROR("unknown mem broadcast msg");
        }

        objpool_free(&shared_region_pool, sh_reg);
    }
}

/**
 * @brief Find whether a memory region overlaps with the memory region of a mapped vMPU entry.
 * @param as Address space configuration
 * @param region Region to check for overlapping vMPU entries
 * @return mpid_t The ID of the first vMPU entry that overlaps in the region.
 * @see mpid_t, addr_space, mp_region, INVALID_MPID, VMPU_NUM_ENTRIES, mpe,
 *      mem_vmpu_get_entry(), mem_regions_overlap()
 */
static mpid_t mem_vmpu_find_overlapping_region(struct addr_space* as, struct mp_region* region)
{
    mpid_t mpid = INVALID_MPID;

    for (mpid_t i = 0; i < VMPU_NUM_ENTRIES; i++) {
        struct mpe* mpe = mem_vmpu_get_entry(as, i);

        if (mpe->state != MPE_S_VALID) {
            continue;
        }

        if (mem_regions_overlap(region, &mpe->region)) {
            mpid = i;
            break;
        }
    }

    return mpid;
}

/**
 * @brief Merge vMPU entries mapped to adiacent memory regions into one.
 * @param as Address space configuration in which the memory regions are allocated.
 * @param broadcast Option to broadcast the change of vMPU entries to other CPUs.
 * @see addr_space, mpid_t, mpe, list_foreach_tail(), mem_vmpu_get_entry,
 *      mpu_perms_compatible(), mem_vmpu_update_region(), mem_vmpu_remove_region(),
 *      mp_region.
 */
static void mem_vmpu_coalesce_contiguous(struct addr_space* as, bool broadcast)
{
    while (true) {
        bool merge = false;
        mpid_t cur_mpid = INVALID_MPID;
        mpid_t prev_mpid = INVALID_MPID;
        struct mpe* prev_reg;
        struct mpe* cur_reg;
        list_foreach_tail(as->vmpu.ordered_list, struct mpe, cur, prev)
        {
            if (prev == NULL) {
                continue;
            }
            cur_reg = mem_vmpu_get_entry(as, cur->mpid);
            prev_reg = mem_vmpu_get_entry(as, prev->mpid);

            bool contiguous = prev_reg->region.base + prev_reg->region.size == cur_reg->region.base;
            bool perms_compatible =
                mpu_perms_compatible(prev_reg->region.mem_flags.raw, cur_reg->region.mem_flags.raw);
            bool lock_compatible = !prev_reg->lock && !cur_reg->lock;
            if (contiguous && perms_compatible && lock_compatible) {
                cur_mpid = cur->mpid;
                prev_mpid = prev->mpid;
                merge = true;
                break;
            }
        }

        if (merge) {
            struct mp_region merged_reg = {
                .base = prev_reg->region.base,
                .size = prev_reg->region.size + cur_reg->region.size,
                .mem_flags = cur_reg->region.mem_flags,
            };
            if (mem_vmpu_update_region(as, prev_mpid, merged_reg, broadcast, prev_reg->lock)) {
                mem_vmpu_remove_region(as, cur_mpid, broadcast);
            }
        } else {
            break;
        }
    }
}

/**
 * @brief Map a memory region in the virtual MPU.
 * @param as Address space configuration in which the vMPU entry is mapped.
 * @param mpr Memory region to map in a vMPU entry.
 * @param broadcast Option to perform the broadcast message to synchronize the MPU configuration.
 * @param locked Option to lock the memory protection region's configuration.
 * @return true if successfully mapped, false otherwise.
 * @see addr_space, mp_region, mpid_t, INVALID_MPID, mpu_granularity(), spin_lock(),
 *      mem_vmpu_find_overlapping_region(), mem_vmpu_allocate_entry(), mem_vmpu_insert_region(),
 *      mem_vmpu_deallocate_entry(), mem_vmpu_coalesce_contiguous(), spin_unlock().
 */
bool mem_map(struct addr_space* as, struct mp_region* mpr, bool broadcast, bool locked)
{
    bool mapped = false;
    mpid_t mpid = INVALID_MPID;

    if (mpr->size == 0) {
        return true;
    }

    if ((mpr->size % mpu_granularity()) != 0) {
        ERROR("trying to set mpu region which is not a multiple of "
              "granularity");
    }

    spin_lock(&as->lock);

    if (mem_vmpu_find_overlapping_region(as, mpr) == INVALID_MPID) {
        mpid = mem_vmpu_allocate_entry(as);
        if (mpid != INVALID_MPID) {
            mapped = mem_vmpu_insert_region(as, mpid, mpr, broadcast, locked);
        } else {
            mem_vmpu_deallocate_entry(as, mpid);
        }
    }

    if (mapped && !locked) {
        mem_vmpu_coalesce_contiguous(as, broadcast);
    }

    spin_unlock(&as->lock);

    return mapped;
}

/**
 * @brief Unmap all vMPU entries in a memory range from the address space configuration.
 * @param as Address space configuration
 * @param vaddr Base address of the range to unmap
 * @param size Size of the range to unmap
 * @param broadcast Option to broadcast the vMPU change to other CPUs.
 * @return true if the whole range is unmapped. false otherwise.
 * @note This function can affect (resize) the configuration of vMPU entries overlapping in the memory range.
 * @see addr_space, vaddr_t, spin_lock(), mp_region, mpid_t, mem_vmpu_find_overlapping_region(),
 *      INVALID_MPID, mem_vmpu_get_entry(), mem_vmpu_remove_region(), mem_vmpu_allocate_entry(),
 *      mem_vmpu_insert_region(), spin_unlock().
 */
bool mem_unmap_range(struct addr_space* as, vaddr_t vaddr, size_t size, bool broadcast)
{
    spin_lock(&as->lock);

    size_t size_left = size;

    while (size_left > 0) {
        struct mp_region reg;
        reg.base = vaddr;
        reg.size = size;

        mpid_t mpid = mem_vmpu_find_overlapping_region(as, &reg);
        if (mpid == INVALID_MPID) {
            /**
             * FIXME: right now we are ignoring the fact that the range  or parts of it might not
             * be mapped. This is in line to what the MMU mem_unmap function does. We should change
             * this to only go ahead with the unpamming if the full range is indeed mapped.
             */
            break;
        }
        struct mpe* mpe = mem_vmpu_get_entry(as, mpid);
        reg = mpe->region;

        bool locked = mpe->lock;

        vaddr_t limit = vaddr + size;
        vaddr_t r_limit = reg.base + reg.size;
        vaddr_t r_base = reg.base;

        size_t top_size = limit >= r_limit ? 0 : r_limit - limit;
        size_t bottom_size = vaddr <= r_base ? 0 : vaddr - r_base;

        mem_vmpu_remove_region(as, mpid, broadcast);

        if (top_size > 0) {
            struct mp_region top = reg;
            top.base = limit;
            top.size = top_size;
            mpid_t top_mpid = mem_vmpu_allocate_entry(as);
            if (!mem_vmpu_insert_region(as, top_mpid, &top, broadcast, locked)) {
                return false;
            }
        }

        if (bottom_size > 0) {
            struct mp_region bottom = reg;
            bottom.size = bottom_size;
            mpid_t bottom_mpid = mem_vmpu_allocate_entry(as);
            if (!mem_vmpu_insert_region(as, bottom_mpid, &bottom, broadcast, locked)) {
                return false;
            }
        }

        size_t overlap_size = reg.size - top_size - bottom_size;
        size_left -= overlap_size;
    }

    spin_unlock(&as->lock);

    return size_left == 0;
}

/**
 * @brief Unmap a memory range. Optionally the pages are freed.
 * @note Freed pages can be re-allocated.
 * @param as Address space configuration of the memory range
 * @param at Base address of the memory range
 * @param num_pages number of page blocks in the rage.
 * @param free_ppages Option to free the memory range for re-allocation.
 * @see addr_space, vaddr_t, mem_unmap_range(), PAGE_SIZE, MEM_BROADCAST, ppages,
 *      mem_ppages_get(), mem_free_ppages().
 */
void mem_unmap(struct addr_space* as, vaddr_t at, size_t num_pages, bool free_ppages)
{
    if (mem_unmap_range(as, at, num_pages * PAGE_SIZE, MEM_BROADCAST) && free_ppages) {
        struct ppages ppages = mem_ppages_get(at, num_pages);
        mem_free_ppages(&ppages);
    }
}

/**
 * @brief   Map in the vMPU two memory region defined in different address space configurations
 *          and copy the contents into the other's region.
 * @param ass Source address space configuration
 * @param asd Destination address space configuration
 * @param asd_section Destionation address space's section type.
 * @param vas Source "virtual address" of the source area.
 * @param vad Source "virtual address" of the destination area
 * @param num_pages Number of pages to map and copy at source and destination.
 * @return vaddr_t Address of the destination.
 * @see addr_space, as_sec_t, vaddr_t, mpe, mp_region, INVALID_VA, spin_lock(),
 *      spin_unlock(), mpid_t, mem_vmpu_get_entry_by_addr(), mem_vmpu_get_entry(),
 *      PAGE_SIZE, mem_broadcast(), MEM_BROADCAST, mem_map(), MEM_NOT_LOCKED, INFO().
 */
vaddr_t mem_map_cpy(struct addr_space* ass, struct addr_space* asd, as_sec_t asd_section,
    vaddr_t vas, vaddr_t vad, size_t num_pages)
{
    UNUSED_ARG(num_pages);

    struct mpe* mpe;
    struct mp_region mpr;
    vaddr_t va_res = INVALID_VA;

    if ((ass != asd) && (vad == INVALID_VA || vad == vas)) {
        // In mpu-based systems, we can only copy mappings between address spaces, as copying a
        // mapping in a single address space would overlap the orignal mapping. Also because only
        // identify mappings are supported, the source va must equal the destination va, or be an
        // invalid va. This still covers the most useful uses cases.

        spin_lock(&ass->lock);
        mpid_t reg_num_src = mem_vmpu_get_entry_by_addr(ass, vas);
        mpe = mem_vmpu_get_entry(ass, reg_num_src);
        mpr = mpe->region;
        mpr.as_sec = asd_section;
        spin_unlock(&ass->lock);

        if (num_pages * PAGE_SIZE > mpr.size) {
            va_res = INVALID_VA;
        } else {
            mpr.size = num_pages * PAGE_SIZE;
            bool broadcast = mem_broadcast(asd, &mpr, MEM_BROADCAST);
            if (mem_map(asd, &mpr, broadcast, MEM_NOT_LOCKED)) {
                va_res = vas;
            } else {
                INFO("failed mem map on mem map cpy");
            }
        }
    } else {
        INFO("failed mem map cpy");
    }

    return va_res;
}

/**
 * @brief Translates the VA into PA.
 * @param as Address space in which the VA may be correctly mapped.
 * @param va Virtual address to check whether it is part of a valid vMPU entry.
 * @param pa Physical address in which the VA is copied if the vMPU entry is valid.
 * @return true if the vMPU entry associated to the VA has a valid. false otherwise.
 * @see     mem_vmpu_get_entry_by_addr, addr_space, vaddr_t, paddr_t, INVALID_MPID
 * @note    In MPU-based systems, physical address and virtual address are identically mapped.
 *          As such, this function is equivalent to mem_vmpu_get_entry_by_addr on the VA.
 */
bool mem_translate(struct addr_space* as, vaddr_t va, paddr_t* pa)
{
    if (mem_vmpu_get_entry_by_addr(as, va) != INVALID_MPID) {
        *pa = va;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Allocate and map an MPU region in the address space
 * @param as Address space configuration in which the region shall be mapped.
 * @param section The type of memory section to be mapped.
 * @param ppages Description of the physically-addressed memory pages to be mapped.
 * @param at if ppages is not specified, this VA is used instead as region's base address.
 * @param num_pages Number of pages to map.
 * @param flags
 * @return vaddr_t Virtual address to the mapped region.
 * @note In MPU-based systems, physical address and virtual address are identically mapped.
 * @see vaddr_t, addr_space, as_sec_t, ppages, mem_flags_t, ERROR(), mem_ppages_get(),
 *      mp_region, PAGE_SIZE, mem_map().
 */
vaddr_t mem_alloc_map(struct addr_space* as, as_sec_t section, struct ppages* ppages, vaddr_t at,
    size_t num_pages, mem_flags_t flags)
{
    // TODO: Check if page->base, page->size and vaddr_t at are page_size align?

    struct ppages temp_ppages;

    if (at == INVALID_VA && ppages == NULL) {
        ERROR("Can't map an MPU region because neither the virtual"
              "or phsyical address was specified.");
    }

    if (at != INVALID_VA && ppages != NULL && at != ppages->base) {
        ERROR("Trying to map non identity");
    }

    if (at == INVALID_VA) {
        at = ppages->base;
    } else if (ppages == NULL) {
        temp_ppages = mem_ppages_get(at, num_pages);
        ppages = &temp_ppages;
    }

    struct mp_region mpr = (struct mp_region){
        .base = ppages->base,
        .size = (num_pages * PAGE_SIZE),
        .as_sec = section,
        .mem_flags = flags,
    };

    mem_map(as, &mpr, MEM_BROADCAST, MEM_NOT_LOCKED);

    return at;
}

/**
 * @brief Allocate and map pages in which device are mapped.
 * @param as Address space configuration
 * @param section Type of section to be mapped
 * @param at Virtual base address of the device.
 * @param pa Physical base address of the device
 * @param num_pages Number of pages to map.
 * @return vaddr_t Virtual address at which the memory-mapped device is not mapped.
 * @see addr_space, as_sec_t, vaddr_t, paddr_t, ppages, mem_ppages_get(), mem_alloc_map(),
 *      PTE_HYP_DEV_FLAGS, PTE_VM_DEV_FLAGS
 */
vaddr_t mem_alloc_map_dev(struct addr_space* as, as_sec_t section, vaddr_t at, paddr_t pa,
    size_t num_pages)
{
    struct ppages temp_page = mem_ppages_get(pa, num_pages);
    return mem_alloc_map(as, section, &temp_page, at, num_pages,
        as->type == AS_HYP ? PTE_HYP_DEV_FLAGS : PTE_VM_DEV_FLAGS);
}
