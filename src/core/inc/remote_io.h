/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __REMOTE_IO_H__
#define __REMOTE_IO_H__

#include <bao.h>
#include <emul.h>
#include <list.h>
#include <vm.h>

/*!
 * @enum    remote_io_shmem
 * @brief   Contains all the information of a Remote I/O shared memory region
 */
struct remote_io_shmem {
    paddr_t base;
    size_t size;
    size_t shmem_id;
};

/*!
 * @struct  remote_io_dev
 * @brief   Contains all the information of a Remote I/O device
 */
struct remote_io_dev {
    vaddr_t va;        // Virtual address for device MMIO register access
    size_t size;       // MMIO region size
    irqid_t interrupt; // Interrupt
    uint64_t id;       // Unique Remote I/O ID linking each frontend driver to the backend
                       // device
    bool is_backend;   // True if the device is a backend device
    struct remote_io_shmem shmem; // Shared memory region
};

/*!
 * @fn              remote_io_init
 * @brief           Responsible for Remote I/O device initialization
 * @return          void
 */
void remote_io_init();

/*!
 * @fn              remote_io_assign_cpus
 * @brief           Assigns frontend and backend CPUs to VMs containing Remote I/O instances
 * @return          void
 */
void remote_io_assign_cpus(struct vm* vm);

/*!
 * @fn              remote_io_hypercall
 * @brief           Handle the Remote I/O hypercall
 * @note            The Remote I/O hypercall is used by the backend to request or send information
 * @param   arg0    First argument of the hypercall
 * @param   arg1    Second argument of the hypercall
 * @param   arg2    Third argument of the hypercall
 * @return          unsigned long
 */
unsigned long remote_io_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2);

/*!
 * @fn                      remote_io_mmio_emul_handler
 * @brief                   Manages all MMIO register accesses for a Remote I/O driver
 * @param   emul_access     Structure holding details for MMIO register access
 * @return                  bool
 */
bool remote_io_mmio_emul_handler(struct emul_access* emul_access);

#endif /* __REMOTE_IO_H__ */
