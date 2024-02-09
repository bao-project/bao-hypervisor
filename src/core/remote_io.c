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
#include <spinlock.h>

// TODO: Get this value from the config
#define IO_INSTANCES_NUM_MAX      16
#define IO_INSTANCE_UNINITIALIZED -1
#define IO_CPU_NUM                PLAT_CPU_NUM
#define IO_VCPU_NUM               PLAT_CPU_NUM
#define ID_SHIFT                  0
#define CPU_ID_SHIFT              16
#define VCPU_ID_SHIFT             32
#define ID_MASK                   (long long)((long long)0x000000000000FFFF << ID_SHIFT)
#define CPU_ID_MASK               (long long)((long long)0x000000000000FFFF << CPU_ID_SHIFT)
#define VCPU_ID_MASK              (long long)((long long)0x000000000000FFFF << VCPU_ID_SHIFT)

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
    IO_WRITE_NOTIFY,              // Write notification
    IO_READ_NOTIFY,               // Read notification
    IO_INJECT_INTERRUPT_FRONTEND, // Interrupt injection operation on the frontend
    IO_INJECT_INTERRUPT_BACKEND,  // Interrupt injection operation on the backend
    IO_NOTIFY_BACKEND_POOL,       // Pooling notification
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
    unsigned int device_type;    // Identifies the actual physical device type
};

/*!
 * @enum
 * @brief   I/O request states
 */
enum IO_STATE {
    IO_STATE_FREE, // The I/O request slot is not used or the client has completed it and a new I/O
                   // requests can be delivered
    IO_STATE_PENDING,    // The I/O request slot is occupied with an I/O request pending to be
                         // processed by Backend VM
    IO_STATE_PROCESSING, // The I/O request has been dispatched to a client but the client has not
                         // finished handling it yet
    IO_STATE_COMPLETE,   // The client has completed the I/O request but the hypervisor has not
                         // updated the register value yet
};

/*!
 * @struct  io_access
 * @brief   Contains the specific parameters of a I/O device access
 */
struct io_access {
    unsigned long reg_off;      // Offset of the accessed MMIO Register
    vaddr_t addr;               // Address of the accessed MMIO Register
    unsigned long access_width; // Access width
    unsigned long op;           // Operation
    unsigned long value;        // Value to write or read
    unsigned long reg;          // CPU register for storing the MMIO register valu
    enum IO_STATE state;        // I/O request state
};

/*!
 * @struct  io_access_event
 * @brief   Contains the specific parameters of a I/O device access event
 *
 * @note    This is used to only advertise the backend that a new I/O request is available
 *          and the backend can ask for it, avoiding the need to iterate over all the
 *          CPUs and vCPUs slots to find the next I/O request to be processed
 */
struct io_access_event {
    node_t node;
    cpuid_t cpu_id;   // Frontend CPU ID of the I/O request
    vcpuid_t vcpu_id; // Frontend vCPU ID of the I/O request
};

/*!
 * @struct  io_requests
 * @brief   Contains the I/O requests for a specific CPU
 *
 * @note    Each remote_io frontend can run on multiple vCPUs
 */
struct io_requests {
    struct io_access io_access[IO_VCPU_NUM]; // I/O requests for each vCPU
};

/*!
 * @struct  remote_io
 * @brief   Comprises all the information about the Remote I/O infrastructure for each Remote I/O
 * instance
 */
struct remote_io {
    node_t node;
    uint64_t id;
    struct io_instance instance;
    struct list requests;
    spinlock_t lock;
};

struct list remote_io_list;
struct io_requests remote_io_requests[IO_CPU_NUM];

static void remote_io_handler(uint32_t, uint64_t);
CPU_MSG_HANDLER(remote_io_handler, REMOTE_IO_CPUMSG_ID);

OBJPOOL_ALLOC(remote_io_pool, struct remote_io, sizeof(struct remote_io));
OBJPOOL_ALLOC(remote_io_access_event_pool, struct io_access_event, sizeof(struct io_access_event));

void remote_io_init()
{
    int i, vm_id, frontend_id = 0, backend_id = 0;
    int backend_devices[IO_INSTANCES_NUM_MAX];

    if (!cpu_is_master()) {
        return;
    }

    objpool_init(&remote_io_pool);
    objpool_init(&remote_io_access_event_pool);
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
                node->id = dev->remote_io_id;
                node->lock = SPINLOCK_INITVAL;
                list_init(&node->requests);
                list_push(&remote_io_list, (node_t*)node);

                if (backend_devices[dev->remote_io_id] != IO_INSTANCE_UNINITIALIZED) {
                    ERROR("Failed to link backend to the frontend, more than one back-end was "
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
            list_foreach (remote_io_list, struct remote_io, io_device) {
                if (dev->remote_io_id == io_device->id) {
                    if (dev->is_back_end) {
                        io_device->instance.backend_vm_id = dev->backend_vm_id;
                        io_device->instance.device_type = dev->device_type;
                        io_device->instance.remote_io_interrupt =
                            vm_config->platform.remote_io_interrupt;
                    } else {
                        io_device->instance.frontend_vm_id = dev->frontend_vm_id;
                        io_device->instance.device_interrupt = dev->device_interrupt;
                    }
                }
            }
        }
    }

    for (int cpu_idx = 0; cpu_idx < IO_CPU_NUM; cpu_idx++) {
        for (int vcpu_idx = 0; vcpu_idx < IO_VCPU_NUM; vcpu_idx++) {
            remote_io_requests[cpu_idx].io_access[vcpu_idx].state = IO_STATE_FREE;
        }
    }
}

void remote_io_assign_cpus(struct vm* vm)
{
    for (int i = 0; i < vm->remote_io_dev_num; i++) {
        list_foreach (remote_io_list, struct remote_io, io_device) {
            if (vm->remote_io_devs[i].remote_io_id == io_device->id) {
                if (vm->remote_io_devs[i].backend_vm_id == cpu()->vcpu->vm->id) {
                    io_device->instance.backend_cpu_id = cpu()->id;
                } else if (vm->remote_io_devs[i].frontend_vm_id == cpu()->vcpu->vm->id) {
                    io_device->instance.frontend_cpu_id = cpu()->id;
                }
            }
        }
    }
}

/*!
 * @fn                  remote_io_w_r_operation
 * @brief               Performs the write or read operation by updating the value
 * @param remote_io_id     Contains the Remote I/O
 * @param reg_off       Contains the MMIO register offset
 * @param value         Contains the register value
 * @param cpu_id        Contains the frontend CPU ID of the I/O request
 * @param vcpu_id       Contains the frontend vCPU ID of the I/O request
 * @return              true if the operation was successful, false otherwise
 */
static bool remote_io_w_r_operation(unsigned long remote_io_id, unsigned long reg_off,
    unsigned long value, unsigned long cpu_id, unsigned long vcpu_id)
{
    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == remote_io_id) {
            spin_lock(&io_device->lock);
            struct io_access* node = &remote_io_requests[cpu_id].io_access[vcpu_id];
            spin_unlock(&io_device->lock);

            if (node->reg_off != reg_off || node->state != IO_STATE_PROCESSING) {
                break;
            }

            spin_lock(&io_device->lock);
            node->value = value;
            node->state = IO_STATE_COMPLETE;
            spin_unlock(&io_device->lock);
            return true;
        }
    }
    return false;
}

/*!
 * @fn              remote_io_cpu_msg_handler
 * @brief           Handles the cpu_msg comming from the backend
 * @param event     Contains the message event
 * @param data      Contains the Remote I/O
 * @return          void
 */
static void remote_io_cpu_msg_handler(uint32_t event, uint64_t data)
{
    uint16_t id = (data & ID_MASK) >> ID_SHIFT;
    uint16_t cpu_id = (data & CPU_ID_MASK) >> CPU_ID_SHIFT;
    uint16_t vcpu_id = (data & VCPU_ID_MASK) >> VCPU_ID_SHIFT;

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == id) {
            spin_lock(&io_device->lock);
            struct io_access* node = &remote_io_requests[cpu_id].io_access[vcpu_id];
            spin_unlock(&io_device->lock);

            switch (event) {
                case IO_READ_NOTIFY:
                    vcpu_writereg(cpu()->vcpu, node->reg, node->value);
                    break;
            }

            spin_lock(&io_device->lock);
            node->state = IO_STATE_FREE;
            spin_unlock(&io_device->lock);

            cpu()->vcpu->active = true;
            break;
        }
    }
}

/*!
 * @fn                  remote_io_cpu_send_msg
 * @brief               Dispatches a message from the backend CPU to the frontend CPU
 * @param remote_io_id     Contains the Remote I/O
 * @param op            Contains the operation type
 * @param cpu_id        Contains the frontend CPU ID of the I/O request
 * @param vcpu_id       Contains the frontend vCPU ID of the I/O request
 * @return              void
 */
static void remote_io_cpu_send_msg(unsigned long remote_io_id, unsigned long op,
    unsigned long cpu_id, unsigned long long vcpu_id)
{
    struct cpu_msg msg = { REMOTE_IO_CPUMSG_ID, IO_WRITE_NOTIFY, 0 };
    cpuid_t target_cpu = 0;

    if (op == IO_READ_OP) {
        msg.event = IO_READ_NOTIFY;
    } else if (op == IO_NOTIFY_OP) {
        msg.event = IO_INJECT_INTERRUPT_FRONTEND;
    }

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == remote_io_id) {
            if (op == IO_READ_OP || op == IO_WRITE_OP) {
                target_cpu = cpu_id;
            } else {
                target_cpu = io_device->instance.frontend_cpu_id;
            }

            msg.data = remote_io_id | (target_cpu << CPU_ID_SHIFT) | (vcpu_id << VCPU_ID_SHIFT);

            cpu_send_msg(target_cpu, &msg);
            break;
        }
    }
}

/*!
 * @fn              remote_io_inject_interrupt
 * @brief           Injects an interrupt into the vCPU running the frontend or backend VM
 * @param data      Contains the Remote I/O ID
 * @return          void
 */
static void remote_io_inject_interrupt(uint64_t data, enum IO_DIRECTION dir)
{
    irqid_t irq_id = 0;
    uint16_t id = (data & ID_MASK) >> ID_SHIFT;

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == id) {
            if (dir == IO_FRONTEND_TO_BACKEND) {
                irq_id = io_device->instance.remote_io_interrupt;
            } else {
                irq_id = io_device->instance.device_interrupt;
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
    unsigned long ret = -HC_E_SUCCESS;
    unsigned long virt_remote_io_id = cpu()->vcpu->regs.x[2];
    unsigned long reg_off = cpu()->vcpu->regs.x[3];
    // unsigned long addr = cpu()->vcpu->regs.x[4];
    unsigned long op = cpu()->vcpu->regs.x[5];
    unsigned long value = cpu()->vcpu->regs.x[6];
    unsigned long cpu_id = cpu()->vcpu->regs.x[7];
    unsigned long vcpu_id = cpu()->vcpu->regs.x[8];

    unsigned long abs_remote_io_id = 0;
    bool match = false;

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (cpu()->vcpu->vm->id == io_device->instance.backend_vm_id) {
            if (abs_remote_io_id == virt_remote_io_id) {
                match = true;
                break;
            } else {
                abs_remote_io_id++;
            }
        }
    }

    if (!match) {
        WARNING("No matching for Remote I/O ID (%d) within VM (%d)", virt_remote_io_id,
            cpu()->vcpu->vm->id);
        return -HC_E_FAILURE;
    }

    switch (op) {
        case IO_WRITE_OP:
        case IO_READ_OP:
            if (!remote_io_w_r_operation(abs_remote_io_id, reg_off, value, cpu_id, vcpu_id)) {
                ret = -HC_E_FAILURE;
            } else {
                remote_io_cpu_send_msg(abs_remote_io_id, op, cpu_id, vcpu_id);
            }
            break;
        case IO_ASK_OP:
            ret = -HC_E_FAILURE;
            if (reg_off != 0 || value != 0) {
                break;
            }
            list_foreach (remote_io_list, struct remote_io, io_device) {
                if (cpu()->vcpu->vm->id == io_device->instance.backend_vm_id &&
                    io_device->id == abs_remote_io_id) {
                    struct io_access_event* node =
                        (struct io_access_event*)list_pop(&io_device->requests);

                    if (!node) {
                        ret = -HC_E_FAILURE;
                        break;
                    }

                    spin_lock(&io_device->lock);
                    struct io_access* request =
                        &remote_io_requests[node->cpu_id].io_access[node->vcpu_id];
                    request->state = IO_STATE_PROCESSING;
                    spin_unlock(&io_device->lock);

                    vcpu_writereg(cpu()->vcpu, 1, virt_remote_io_id);
                    vcpu_writereg(cpu()->vcpu, 2, request->reg_off);
                    vcpu_writereg(cpu()->vcpu, 3, request->addr);
                    vcpu_writereg(cpu()->vcpu, 4, request->op);
                    vcpu_writereg(cpu()->vcpu, 5, request->value);
                    vcpu_writereg(cpu()->vcpu, 6, request->access_width);
                    vcpu_writereg(cpu()->vcpu, 7, node->cpu_id);
                    vcpu_writereg(cpu()->vcpu, 8, node->vcpu_id);

                    objpool_free(&remote_io_access_event_pool, node);

                    return HC_E_SUCCESS;
                }
            }
            break;
        case IO_NOTIFY_OP:
            remote_io_cpu_send_msg(abs_remote_io_id, op, cpu_id, vcpu_id);
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

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == dev.remote_io_id) {
            struct io_access_event* node = objpool_alloc(&remote_io_access_event_pool);
            struct io_access request;
            struct cpu_msg msg = { REMOTE_IO_CPUMSG_ID, IO_INJECT_INTERRUPT_BACKEND,
                dev.remote_io_id };
            request.reg_off = acc->addr - dev.va;
            request.addr = acc->addr;
            request.reg = acc->reg;
            request.access_width = acc->width;
            request.state = IO_STATE_PENDING;
            node->cpu_id = cpu()->id;
            node->vcpu_id = cpu()->vcpu->id;

            if (acc->write) {
                int value = vcpu_readreg(cpu()->vcpu, acc->reg);
                request.op = IO_WRITE_OP;
                request.value = value;
            } else {
                request.op = IO_READ_OP;
                request.value = 0;
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
 * @param data      Contains the Remote I/O ID
 * @return          void
 */
static void remote_io_handler(uint32_t event, uint64_t data)
{
    switch (event) {
        case IO_WRITE_NOTIFY:
        case IO_READ_NOTIFY:
            remote_io_cpu_msg_handler(event, data);
            break;
        case IO_INJECT_INTERRUPT_FRONTEND:
        case IO_INJECT_INTERRUPT_BACKEND:
            remote_io_inject_interrupt(data,
                (event == IO_INJECT_INTERRUPT_FRONTEND) ? IO_BACKEND_TO_FRONTEND :
                                                          IO_FRONTEND_TO_BACKEND);
            break;
    }
}
