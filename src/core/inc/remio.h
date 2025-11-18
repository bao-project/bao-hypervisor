/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/**
 * @file remio.h
 * @brief This header file contains the Remote I/O device interface
 */

#ifndef REMIO_H
#define REMIO_H

#include <bao.h>
#include <emul.h>
#include <list.h>
#include <vm.h>

/**
 * @struct remio_shmem
 * @brief This structure represents a shared memory region used by a Remote I/O device
 */
struct remio_shmem {
    paddr_t base;    /**< Shared memory base address */
    size_t size;     /**< Shared memory size */
    size_t shmem_id; /**< Shared memory ID */
};

/**
 * @enum REMIO_DEV_TYPE
 * @brief This enum represents the Remote I/O device type
 */
enum REMIO_DEV_TYPE {
    REMIO_DEV_FRONTEND = 0, /**< Remote I/O frontend device */
    REMIO_DEV_BACKEND       /**< Remote I/O backend device */
};

/**
 * @struct remio_dev
 * @brief This structure represents a Remote I/O device
 * @note The device can be either a frontend (driver) or a backend (device)
 */
struct remio_dev {
    vaddr_t va;                /**< Frontend MMIO base virtual address */
    size_t size;               /**< Frontend MMIO size */
    irqid_t interrupt;         /**< Frontend/backend interrupt number */
    remio_bind_key_t bind_key; /**< Remote I/O bind key */
    enum REMIO_DEV_TYPE type;  /**< Type of the Remote I/O device */
    struct remio_shmem shmem;  /**< Shared memory region */
    struct emul_mem emul;      /**< Frontend MMIO emulation memory */
};

/**
 * @brief Remote I/O device initialization routine
 * @note Executed only once by the master CPU
 */
void remio_init(void);

/**
 * @brief Remote I/O device VM CPU assignment routine
 * @note Executed by each VM that holds a Remote I/O device, it is responsible for
 *       assigning the frontend or backend CPU ID for the respective Remote I/O device
 *       If the VM was alloacted with more than one CPU the assigned CPU will be the
 *       one with the lowest ID, since only one CPU is required to inject VM interrupts
 * @param vm Pointer to the VM structure
 */
void remio_assign_vm_cpus(struct vm* vm);

/**
 * @brief Remote I/O hypercall callback
 * @note Used to exchange information between the Remote I/O system and the backend VM
 * @return Returns the number of pending I/O requests
 */
long int remio_hypercall(void);

/**
 * @brief Remote I/O MMIO emulation handler
 * @note Executed by the frontend VM when a MMIO access is performed
 * @param emul_access Holds the information about the MMIO access
 * @return Returns true if handled successfully, false otherwise
 */
bool remio_mmio_emul_handler(struct vcpu* vcpu, struct emul_access* emul_access);

#endif /* __REMIO_H__ */
