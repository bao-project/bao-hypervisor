/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <remote_io.h>
#include <cpu.h>
#include <vm.h>
#include <hypercall.h>
#include <objpool.h>
#include <config.h>

/* Remote I/O instances' maximum limit */
#define IO_INSTANCES_NUM_MAX      50

/* Default value assigned to Remote I/O instances */
#define IO_INSTANCE_UNINITIALIZED -1

/*!
 * @enum
 * @brief   Remote I/O hypercall events
 * @note    Used by the backend VM
 */
enum IO_HYP_EVENTS {
    IO_WRITE_OP,  // Write operation
    IO_READ_OP,   // Read operation
    IO_ASK_OP,    // Ask operation (used to retrieve the next request)
    IO_NOTIFY_OP, // Notification operation (used for buffer or configuration change)
};

/*!
 * @enum
 * @brief   Remote I/O cpu_msg events
 */
enum IO_CPU_MSG_EVENTS {
    IO_WRITE_NOTIFY,        // Write notification
    IO_READ_NOTIFY,         // Read notification
    IO_INJECT_INTERRUPT,    // Interrupt injection operation
    IO_NOTIFY_BACKEND_POOL, // Pooling notification
};

/*!
 * @enum
 * @brief   Remote I/O direction
 */
enum IO_DIRECTION {
    IO_FRONTEND_TO_BACKEND, // Frontend to backend direction
    IO_BACKEND_TO_FRONTEND, // Backend to frontend direction
};

/*!
 * @struct  io_instance
 * @brief   Holds the static information regarding a Remote I/O device and driver pair (Remote I/O
 * instance)
 */
struct io_instance {
    cpuid_t backend_cpu_id;      // CPU ID assigned to the Remote I/O backend
    vmid_t backend_vm_id;        // VM ID associated with the Remote I/O backend
    cpuid_t frontend_cpu_id;     // CPU ID assigned to the Remote I/O frontend
    vmid_t frontend_vm_id;       // VM ID associated with the Remote I/O frontend
    irqid_t remote_io_interrupt; // Backend VM interrupt
    irqid_t device_interrupt;    // Device interrupt
    unsigned int priority; // Driver priority for backend scheduling (Higher number indicates lower
                           // priority)
    unsigned int device_type; // Identifies the actual physical device type
    bool pooling;             // Define the backend execution mode: polling or interrupt-based
};

/*!
 * @struct  io_access
 * @brief   Contains the specific parameters of a Remote I/O device access
 */
struct io_access {
    node_t node;                // Node of the list
    unsigned long reg_off;      // Offset of the accessed MMIO Register
    vaddr_t addr;               // Address of the accessed MMIO Register
    unsigned long access_width; // Access width
    unsigned long op;           // Operation
    unsigned long value;        // Value to write or read
    unsigned long reg;          // CPU register for storing the MMIO register valu
    unsigned int priority; // Driver priority for backend scheduling (Higher number indicates lower
                           // priority)
    cpuid_t frontend_cpu_id; // CPU ID assigned to the Remote I/O frontend
    bool handled;            // Indicate whether the request was handled by the backend VM
};

/*!
 * @struct  remote_io
 * @brief   Comprises all the information about the Remote I/O infrastructure
 */
struct remote_io {
    node_t node;                 // Node of the list
    uint64_t remote_io_id;       // Unique Remote I/O ID linking each frontend driver to the backend
                                 // device
    enum IO_DIRECTION direction; // Direction of the request
    struct list frontend_access_list; // Frontend access list
    struct list backend_access_list;  // Backend access list
    struct io_instance instance;      // Static information about the Remote I/O instance
};

/*!
 * @struct  remote_io_list
 * @brief   Holds all Remote I/O information
 */
struct list remote_io_list;

OBJPOOL_ALLOC(remote_io_frontend_access_pool, struct io_access, sizeof(struct io_access));
OBJPOOL_ALLOC(remote_io_backend_access_pool, struct io_access, sizeof(struct io_access));
OBJPOOL_ALLOC(remote_io_pool, struct remote_io, sizeof(struct remote_io));

/* functions prototypes */
static void remote_io_handler(uint32_t, uint64_t);
static int remote_io_prio_node_cmp(node_t* _n1, node_t* _n2);

/* create the handler for the cpu_msg */
CPU_MSG_HANDLER(remote_io_handler, VIRTIO_CPUMSG_ID);

void remote_io_init()
{
    int i, vm_id, frontend_id = 0, backend_id = 0;
    int backend_devices[IO_INSTANCES_NUM_MAX];

    if (!cpu_is_master()) {
        return;
    }

    objpool_init(&remote_io_pool);
    objpool_init(&remote_io_frontend_access_pool);
    objpool_init(&remote_io_backend_access_pool);
    list_init(&remote_io_list);

    for (i = 0; i < IO_INSTANCES_NUM_MAX; i++) {
        backend_devices[i] = IO_INSTANCE_UNINITIALIZED;
    }

    for (vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (i = 0; i < vm_config->platform.remote_io_dev_num; i++) {
            struct remote_io_dev* dev = &vm_config->platform.remote_io_devs[i];
            if (dev->is_back_end) {
                struct remote_io* node = objpool_alloc(&remote_io_pool);
                node->remote_io_id = dev->remote_io_id;
                list_push(&remote_io_list, (node_t*)node);

                if (backend_devices[dev->remote_io_id] != IO_INSTANCE_UNINITIALIZED) {
                    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
                        objpool_free(&remote_io_pool, (struct remote_io*)list_pop(&remote_io_list));
                    }
                    ERROR("Failed to link backend to the device, more than one back-end was "
                          "atributed to the Remote I/O instance %d",
                        dev->remote_io_id);
                } else {
                    dev->backend_vm_id = vm_id;
                    backend_id++;
                    backend_devices[dev->remote_io_id] = vm_id;
                }
            } else {
                dev->frontend_vm_id = vm_id;
                frontend_id++;
            }
        }
    }

    if (backend_id != frontend_id) {
        ERROR("There is no 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend");
    }

    for (vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (i = 0; i < vm_config->platform.remote_io_dev_num; i++) {
            struct remote_io_dev* dev = &vm_config->platform.remote_io_devs[i];
            list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
                if (dev->remote_io_id == remote_io_dev->remote_io_id) {
                    if (dev->is_back_end) {
                        remote_io_dev->instance.backend_vm_id = dev->backend_vm_id;
                        remote_io_dev->instance.device_type = dev->device_type;
                        remote_io_dev->instance.remote_io_interrupt =
                            vm_config->platform.remote_io_interrupt;
                        remote_io_dev->instance.pooling = vm_config->platform.remote_io_pooling;
                    } else {
                        remote_io_dev->instance.frontend_vm_id = dev->frontend_vm_id;
                        remote_io_dev->instance.priority = dev->priority;
                        remote_io_dev->instance.device_interrupt = dev->device_interrupt;
                    }
                }
            }
        }
    }
}

void remote_io_assign_cpus(struct vm* vm)
{
    for (int i = 0; i < vm->remote_io_dev_num; i++) {
        list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
            if (vm->remote_io_devs[i].remote_io_id == remote_io_dev->remote_io_id) {
                if (vm->remote_io_devs[i].backend_vm_id == cpu()->vcpu->vm->id) {
                    remote_io_dev->instance.backend_cpu_id = cpu()->id;
                } else if (vm->remote_io_devs[i].frontend_vm_id == cpu()->vcpu->vm->id) {
                    remote_io_dev->instance.frontend_cpu_id = cpu()->id;
                }
            }
        }
    }
}

/*!
 * @fn                  remote_io_hypercall_w_r_operation
 * @brief               Performs the write or read operation by updating the value
 * @param remote_io_id     Contains the remote_io id
 * @param reg_off       Contains the MMIO register offset
 * @param value         Contains the register value
 * @return              true if the operation was successful, false otherwise
 */
static bool remote_io_hypercall_w_r_operation(unsigned long remote_io_id, unsigned long reg_off,
    unsigned long value)
{
    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
        if (remote_io_dev->remote_io_id == remote_io_id) {
            struct io_access* node =
                (struct io_access*)list_pop(&remote_io_dev->backend_access_list);

            if (node->reg_off != reg_off) {
                break;
            }

            node->value = value;

            struct io_access* frontend_node = objpool_alloc(&remote_io_frontend_access_pool);
            *frontend_node = *node;
            list_push(&remote_io_dev->frontend_access_list, (node_t*)frontend_node);
            objpool_free(&remote_io_backend_access_pool, node);
            return true;
        }
    }
    return false;
}

/*!
 * @fn              remote_io_cpu_msg_handler
 * @brief           Handles the cpu_msg comming from the backend
 * @param event     Contains the message event
 * @param data      Contains the remote_io id
 * @return          void
 */
static void remote_io_cpu_msg_handler(uint32_t event, uint64_t data)
{
    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
        if (remote_io_dev->remote_io_id == data) {
            struct io_access* node =
                (struct io_access*)list_pop(&remote_io_dev->frontend_access_list);

            switch (event) {
                case IO_READ_NOTIFY:
                    vcpu_writereg(cpu()->vcpu, node->reg, node->value);
                    break;
            }

            objpool_free(&remote_io_frontend_access_pool, node);
            cpu()->vcpu->active = true;
            break;
        }
    }
}

/*!
 * @fn                  remote_io_cpu_send_msg
 * @brief               Dispatches a message from the backend CPU to the frontend CPU
 * @param remote_io_id     Contains the remote_io id
 * @param op            Contains the operation type
 * @param cpu_id        Contains the frontend CPU ID of the I/O request
 * @param vcpu_id       Contains the frontend vCPU ID of the I/O request
 * @return              void
 */
static void remote_io_cpu_send_msg(unsigned long remote_io_id, unsigned long op,
    unsigned long cpu_id, unsigned long long vcpu_id)
{
    struct cpu_msg msg = { VIRTIO_CPUMSG_ID, IO_WRITE_NOTIFY, (uint64_t)remote_io_id };
    cpuid_t target_cpu = 0;

    if (op == IO_READ_OP) {
        msg.event = IO_READ_NOTIFY;
    } else if (op == IO_NOTIFY_OP) {
        msg.event = IO_INJECT_INTERRUPT;
    }

    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
        if (remote_io_dev->remote_io_id == remote_io_id) {
            remote_io_dev->direction = IO_BACKEND_TO_FRONTEND;

            if (op == IO_READ_OP || op == IO_WRITE_OP) {
                struct io_access* node =
                    (struct io_access*)list_peek(&remote_io_dev->frontend_access_list);
                if (node == NULL) {
                    ERROR("Failed to get the element from the list");
                }
                target_cpu = node->frontend_cpu_id;
            } else {
                target_cpu = remote_io_dev->instance.frontend_cpu_id;
            }

            cpu_send_msg(target_cpu, &msg);
            break;
        }
    }
}

/*!
 * @fn              remote_io_inject_interrupt
 * @brief           Injects an interrupt into the vCPU running the frontend or backend VM
 * @param data      Contains the remote_io id
 * @return          void
 */
static void remote_io_inject_interrupt(uint64_t data)
{
    irqid_t irq_id = 0;

    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
        if (remote_io_dev->remote_io_id == data) {
            if (remote_io_dev->direction == IO_FRONTEND_TO_BACKEND) {
                irq_id = remote_io_dev->instance.remote_io_interrupt;
            } else {
                irq_id = remote_io_dev->instance.device_interrupt;
            }
            break;
        }
    }

    if (irq_id) {
        vcpu_inject_irq(cpu()->vcpu, irq_id);
    } else {
        ERROR("Failed to inject interrupt");
    }
}

unsigned long remote_io_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
    unsigned long ret = -HC_E_SUCCESS;                   // return value
    unsigned long remote_io_id = cpu()->vcpu->regs.x[2]; // remote_io id
    unsigned long reg_off = cpu()->vcpu->regs.x[3];      // MMIO register offset
    // unsigned long addr = cpu()->vcpu->regs.x[4];            // MMIO register address
    unsigned long op = cpu()->vcpu->regs.x[5];    // operation
    unsigned long value = cpu()->vcpu->regs.x[6]; // register value

    switch (op) {
        case IO_WRITE_OP:
        case IO_READ_OP:
            if (!remote_io_hypercall_w_r_operation(remote_io_id, reg_off, value)) {
                ret = -HC_E_FAILURE;
            } else {
                remote_io_cpu_send_msg(remote_io_id, op);
            }
            break;
        case IO_ASK_OP:
            ret = -HC_E_FAILURE;
            if (reg_off != 0 || value != 0) {
                break;
            }
            list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
                if (remote_io_dev->remote_io_id == remote_io_id &&
                    cpu()->vcpu->vm->id == remote_io_dev->instance.backend_vm_id) {
                    list_foreach (remote_io_dev->backend_access_list, struct io_access, node) {
                        if (!node->handled) {
                            node->handled = true;
                            vcpu_writereg(cpu()->vcpu, 1, remote_io_id);
                            vcpu_writereg(cpu()->vcpu, 2, node->reg_off);
                            vcpu_writereg(cpu()->vcpu, 3, node->addr);
                            vcpu_writereg(cpu()->vcpu, 4, node->op);
                            vcpu_writereg(cpu()->vcpu, 5, node->value);
                            vcpu_writereg(cpu()->vcpu, 6, node->access_width);
                            return HC_E_SUCCESS;
                        }
                    }
                    ret = -HC_E_FAILURE;
                    break;
                }
            }
            break;
        case IO_NOTIFY_OP:
            remote_io_cpu_send_msg(remote_io_id, op);
            break;
        default:
            ret = -HC_E_INVAL_ARGS;
            break;
    }

    return ret;
}

bool remote_io_mmio_emul_handler(struct emul_access* acc)
{
    struct vm* vm = cpu()->vcpu->vm;
    struct remote_io_dev dev = { 0 };
    volatile int i, j;

    for (i = 0; i < vm->remote_io_dev_num; i++) {
        dev = vm->remote_io_devs[i];
        if (acc->addr >= dev.va && acc->addr <= dev.va + dev.size) {
            break;
        }
    }

    if (i == vm->remote_io_dev_num) {
        return false;
    }

    list_foreach (remote_io_list, struct remote_io, remote_io_dev) {
        if (remote_io_dev->remote_io_id == dev.remote_io_id) {
            struct io_access* node = objpool_alloc(&remote_io_backend_access_pool);
            struct cpu_msg msg = { VIRTIO_CPUMSG_ID, IO_INJECT_INTERRUPT, dev.remote_io_id };
            node->reg_off = acc->addr - dev.va;
            node->addr = acc->addr;
            node->reg = acc->reg;
            node->access_width = acc->width;
            node->priority = remote_io_dev->instance.priority;
            node->frontend_cpu_id = cpu()->id;
            node->handled = false;

            if (acc->write) {
                int value = vcpu_readreg(cpu()->vcpu, acc->reg);
                node->op = IO_WRITE_OP;
                node->value = value;
            } else {
                node->op = IO_READ_OP;
                node->value = 0;
            }
            for (j = 0; j < config.vmlist[dev.backend_vm_id].platform.remote_io_dev_num; j++) {
                if (config.vmlist[dev.backend_vm_id].platform.remote_io_devs[j].remote_io_id ==
                    dev.remote_io_id) {
                    if (config.vmlist[dev.backend_vm_id].platform.remote_io_devs[j].pooling) {
                        msg.event = IO_NOTIFY_BACKEND_POOL;
                    }
                    spin_lock(&io_device->lock);
                    remote_io_requests[node->cpu_id].io_access[node->vcpu_id] = request;
                    spin_unlock(&io_device->lock);
                    list_push(&io_device->requests, (node_t*)node);
                    cpu_send_msg(io_device->instance.backend_cpu_id, &msg);
                    vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 4);
                    cpu()->vcpu->active = false;
                    cpu_idle();
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

/*!
 * @fn              remote_io_handler
 * @brief           Manages incoming cpu_msg from the frontend or backend
 * @param event     Contains the message event
 * @param data      Contains the remote_io id
 * @return          void
 */
static void remote_io_handler(uint32_t event, uint64_t data)
{
    switch (event) {
        case IO_WRITE_NOTIFY:
        case IO_READ_NOTIFY:
            remote_io_cpu_msg_handler(event, data);
            break;
        case IO_INJECT_INTERRUPT:
            remote_io_inject_interrupt(data);
            break;
    }
}

/*!
 * @fn              remote_io_prio_node_cmp
 * @brief           Compares two elements by priority
 * @param _n1       Contains the first node
 * @param _n2       Contains the second node
 * @return          int
 */
static int remote_io_prio_node_cmp(node_t* _n1, node_t* _n2)
{
    struct io_access* n1 = (struct io_access*)_n1;
    struct io_access* n2 = (struct io_access*)_n2;

    if (n1->priority > n2->priority) {
        return 1;
    } else if (n1->priority < n2->priority) {
        return -1;
    } else {
        return 0;
    }
}
