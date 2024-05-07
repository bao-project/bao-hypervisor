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
#define REMOTE_IO_MAX_INSTANCES          16
#define REMOTE_IO_INSTANCE_UNINITIALIZED -1
#define REMOTE_IO_CPU_NUM                PLAT_CPU_NUM
#define REMOTE_IO_VCPU_NUM               PLAT_CPU_NUM

/*!
 * @enum
 * @brief   Remote I/O hypercall events
 * @note    Used by the backend VM
 */
enum REMOTE_IO_HYP_EVENT {
    REMOTE_IO_HYP_WRITE,  // Write operation
    REMOTE_IO_HYP_READ,   // Read operation
    REMOTE_IO_HYP_ASK,    // Ask operation (used to retrieve the next request)
    REMOTE_IO_HYP_NOTIFY, // Notification operation (used for buffer or configuration change)
};

/*!
 * @enum
 * @brief   Remote I/O cpu_msg events
 */
enum REMOTE_IO_CPU_MSG_EVENT {
    REMOTE_IO_CPU_MSG_WRITE,  // Write notification
    REMOTE_IO_CPU_MSG_READ,   // Read notification
    REMOTE_IO_CPU_MSG_NOTIFY, // Notification event (used to inject an interrupt into the frontend
                              // or backend)
};

/*!
 * @enum
 * @brief   I/O request states
 */
enum REMOTE_IO_STATE {
    REMOTE_IO_STATE_FREE, // The I/O request slot is not used or the client has completed it and a
                          // new I/O requests can be delivered
    REMOTE_IO_STATE_PENDING, // The I/O request slot is occupied with an I/O request pending to be
                             // processed by Backend VM
    REMOTE_IO_STATE_PROCESSING, // The I/O request has been dispatched to a client but the client
                                // has not finished handling it yet
    REMOTE_IO_STATE_COMPLETE, // The client has completed the I/O request but the hypervisor has not
                              // updated the register value yet
};

/*!
 * @enum
 * @brief   Remote I/O CPU message data structure
 */
union remote_io_cpu_msg_data {
    struct {
        uint8_t id;
        uint8_t cpu_id;
        uint8_t vcpu_id;
        uint8_t interrupt;
    };
    uint64_t raw;
};

/*!
 * @struct  remote_io_instance
 * @brief   Holds the static information regarding a Remote I/O device and driver pair (Remote I/O
 * instance)
 */
struct remote_io_instance {
    cpuid_t backend_cpu_id;     // CPU ID assigned to the Remote I/O backend
    vmid_t backend_vm_id;       // VM ID associated with the Remote I/O backend
    irqid_t backend_interrupt;  // Backend interrupt
    cpuid_t frontend_cpu_id;    // CPU ID assigned to the Remote I/O frontend
    vmid_t frontend_vm_id;      // VM ID associated with the Remote I/O frontend
    irqid_t frontend_interrupt; // Frontend interrupt
};

/*!
 * @struct  remote_io_access
 * @brief   Contains the specific parameters of a I/O device access
 */
struct remote_io_access {
    vaddr_t addr;               // Address of the accessed MMIO Register
    unsigned long access_width; // Access width
    unsigned long op;           // Operation
    unsigned long value;        // Value to write or read
    unsigned long reg;          // CPU register for storing the MMIO register valu
    enum REMOTE_IO_STATE state; // I/O request state
};

/*!
 * @struct  remote_io_access_event
 * @brief   Contains the specific parameters of a I/O device access event
 *
 * @note    This is used to only advertise the backend that a new I/O request is available
 *          and the backend can ask for it, avoiding the need to iterate over all the
 *          CPUs and vCPUs slots to find the next I/O request to be processed
 */
struct remote_io_access_event {
    node_t node;
    cpuid_t cpu_id;   // Frontend CPU ID of the I/O request
    vcpuid_t vcpu_id; // Frontend vCPU ID of the I/O request
};

/*!
 * @struct  remote_io
 * @brief   Comprises all the information about the Remote I/O infrastructure for each Remote I/O
 * instance
 */
struct remote_io {
    node_t node;
    uint64_t id;
    struct remote_io_instance instance;
    struct list requests;
    spinlock_t lock;
};

struct list remote_io_list;
struct remote_io_access remote_io_requests[REMOTE_IO_CPU_NUM][REMOTE_IO_VCPU_NUM];

static void remote_io_cpu_handler(uint32_t, uint64_t);
CPU_MSG_HANDLER(remote_io_cpu_handler, REMOTE_IO_CPUMSG_ID);

OBJPOOL_ALLOC(remote_io_pool, struct remote_io, sizeof(struct remote_io));
OBJPOOL_ALLOC(remote_io_access_event_pool, struct remote_io_access_event,
    sizeof(struct remote_io_access_event));

void remote_io_init()
{
    int i, vm_id, frontend_cnt = 0, backend_cnt = 0;
    int instances[REMOTE_IO_MAX_INSTANCES][2];

    if (!cpu_is_master()) {
        return;
    }

    objpool_init(&remote_io_pool);
    objpool_init(&remote_io_access_event_pool);
    list_init(&remote_io_list);

    for (i = 0; i < REMOTE_IO_MAX_INSTANCES; i++) {
        instances[i][0] = REMOTE_IO_INSTANCE_UNINITIALIZED;
        instances[i][1] = REMOTE_IO_INSTANCE_UNINITIALIZED;
    }

    for (vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (i = 0; i < vm_config->platform.remote_io_dev_num; i++) {
            struct remote_io_dev* dev = &vm_config->platform.remote_io_devs[i];
            if (instances[dev->id][0] != REMOTE_IO_INSTANCE_UNINITIALIZED && dev->is_backend) {
                ERROR("Failed to link backend to the frontend, more than one backend was "
                      "atributed to the Remote I/O instance %d",
                    dev->id);
            }
            if (instances[dev->id][1] != REMOTE_IO_INSTANCE_UNINITIALIZED && !dev->is_backend) {
                ERROR("Failed to link backend to the frontend, more than one frontend was "
                      "atributed to the Remote I/O instance %d",
                    dev->id);
            }
            if (dev->is_backend) {
                struct remote_io* node = objpool_alloc(&remote_io_pool);
                node->id = dev->id;
                node->lock = SPINLOCK_INITVAL;
                list_init(&node->requests);
                list_push(&remote_io_list, (node_t*)node);
                backend_cnt++;
                instances[dev->id][0] = vm_id;
            } else {
                frontend_cnt++;
                instances[dev->id][1] = vm_id;
            }
        }
    }

    if (backend_cnt != frontend_cnt) {
        ERROR("There is no 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend");
    }

    for (vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (i = 0; i < vm_config->platform.remote_io_dev_num; i++) {
            struct remote_io_dev* dev = &vm_config->platform.remote_io_devs[i];
            list_foreach (remote_io_list, struct remote_io, io_device) {
                if (dev->id == io_device->id) {
                    if (dev->is_backend) {
                        io_device->instance.backend_vm_id = vm_id;
                        io_device->instance.backend_interrupt = dev->interrupt;
                    } else {
                        io_device->instance.frontend_vm_id = vm_id;
                        io_device->instance.frontend_interrupt = dev->interrupt;
                    }
                }
            }
        }
    }

    for (int cpu_idx = 0; cpu_idx < REMOTE_IO_CPU_NUM; cpu_idx++) {
        for (int vcpu_idx = 0; vcpu_idx < REMOTE_IO_VCPU_NUM; vcpu_idx++) {
            remote_io_requests[cpu_idx][vcpu_idx].state = REMOTE_IO_STATE_FREE;
        }
    }
}

void remote_io_assign_cpus(struct vm* vm)
{
    for (int i = 0; i < vm->remote_io_dev_num; i++) {
        list_foreach (remote_io_list, struct remote_io, io_device) {
            if (vm->id == io_device->instance.backend_vm_id) {
                io_device->instance.backend_cpu_id = cpu()->id;
            } else if (vm->id == io_device->instance.frontend_vm_id) {
                io_device->instance.frontend_cpu_id = cpu()->id;
            }
        }
    }
}

/*!
 * @fn                  remote_io_w_r_operation
 * @brief               Performs the write or read operation by updating the value
 * @param id     Contains the Remote I/O
 * @param addr       Contains the MMIO register address
 * @param value         Contains the register value
 * @param cpu_id        Contains the frontend CPU ID of the I/O request
 * @param vcpu_id       Contains the frontend vCPU ID of the I/O request
 * @return              true if the operation was successful, false otherwise
 */
static bool remote_io_w_r_operation(unsigned long id, unsigned long addr, unsigned long value,
    unsigned long cpu_id, unsigned long vcpu_id)
{
    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == id) {
            spin_lock(&io_device->lock);
            struct remote_io_access* node = &remote_io_requests[cpu_id][vcpu_id];
            spin_unlock(&io_device->lock);

            if (node->addr != addr || node->state != REMOTE_IO_STATE_PROCESSING) {
                break;
            }

            spin_lock(&io_device->lock);
            node->value = value;
            node->state = REMOTE_IO_STATE_COMPLETE;
            spin_unlock(&io_device->lock);
            return true;
        }
    }
    return false;
}

/*!
 * @fn              remote_io_cpu_post_work
 * @brief           Handles the cpu_msg comming from the backend
 * @param event     Contains the message event
 * @param id      Contains the Remote I/O ID
 * @param cpu_id    Contains the frontend CPU ID of the I/O request
 * @param vcpu_id   Contains the frontend vCPU ID of the I/O request
 * @return          void
 */
static void remote_io_cpu_post_work(uint32_t event, uint8_t id, uint8_t cpu_id, uint8_t vcpu_id)
{
    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (io_device->id == id) {
            spin_lock(&io_device->lock);
            struct remote_io_access* node = &remote_io_requests[cpu_id][vcpu_id];
            spin_unlock(&io_device->lock);

            switch (event) {
                case REMOTE_IO_CPU_MSG_READ:
                    vcpu_writereg(cpu()->vcpu, node->reg, node->value);
                    break;
            }

            spin_lock(&io_device->lock);
            node->state = REMOTE_IO_STATE_FREE;
            spin_unlock(&io_device->lock);

            cpu()->vcpu->active = true;
            break;
        }
    }
}

/*!
 * @fn                  remote_io_cpu_send_msg
 * @brief               Sends a CPU message to the frontend or backend CPUs
 * @param event         Contains the message event
 * @param target_cpu    Contains the target CPU ID
 * @param id            Contains the Remote I/O ID
 * @param cpu_id        Contains the frontend CPU ID of the I/O request
 * @param vcpu_id       Contains the frontend vCPU ID of the I/O request
 * @param interrupt     Contains the interrupt to be injected
 * @return              void
 */
static void remote_io_cpu_send_msg(enum REMOTE_IO_CPU_MSG_EVENT event, unsigned long target_cpu,
    unsigned long id, unsigned long cpu_id, unsigned long long vcpu_id, unsigned long interrupt)
{
    union remote_io_cpu_msg_data data = {
        .id = id,
        .cpu_id = cpu_id,
        .vcpu_id = vcpu_id,
        .interrupt = interrupt,
    };
    struct cpu_msg msg = { REMOTE_IO_CPUMSG_ID, event, data.raw };
    cpu_send_msg(target_cpu, &msg);
}

unsigned long remote_io_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
    unsigned long ret = -HC_E_SUCCESS;
    unsigned long virt_remote_io_id = cpu()->vcpu->regs.x[2];
    unsigned long addr = cpu()->vcpu->regs.x[3];
    unsigned long op = cpu()->vcpu->regs.x[4];
    unsigned long value = cpu()->vcpu->regs.x[5];
    unsigned long cpu_id = cpu()->vcpu->regs.x[6];
    unsigned long vcpu_id = cpu()->vcpu->regs.x[7];
    struct remote_io* remote_io = NULL;

    if (virt_remote_io_id >= config.vmlist[cpu()->vcpu->vm->id].platform.remote_io_dev_num) {
        WARNING("Remote I/O ID (%d) is out of range", virt_remote_io_id);
        return -HC_E_FAILURE;
    }
    unsigned long abs_remote_io_id =
        config.vmlist[cpu()->vcpu->vm->id].platform.remote_io_devs[virt_remote_io_id].id;

    list_foreach (remote_io_list, struct remote_io, io_device) {
        if (cpu()->vcpu->vm->id == io_device->instance.backend_vm_id &&
            io_device->id == abs_remote_io_id) {
            remote_io = io_device;
            break;
        }
    }

    if (!remote_io) {
        WARNING("The Remote I/O backend device (%d) does not belong to the current backend VM (%d)",
            virt_remote_io_id, cpu()->vcpu->vm->id);
        return -HC_E_FAILURE;
    }

    switch (op) {
        case REMOTE_IO_HYP_WRITE:
        case REMOTE_IO_HYP_READ:
            if (!remote_io_w_r_operation(abs_remote_io_id, addr, value, cpu_id, vcpu_id)) {
                ret = -HC_E_FAILURE;
            } else {
                remote_io_cpu_send_msg(op == REMOTE_IO_HYP_WRITE ? REMOTE_IO_CPU_MSG_WRITE :
                                                                   REMOTE_IO_CPU_MSG_READ,
                    cpu_id, abs_remote_io_id, cpu_id, vcpu_id, 0);
            }
            break;
        case REMOTE_IO_HYP_ASK:
            if (addr != 0 || value != 0) {
                ret = -HC_E_FAILURE;
                break;
            }
            struct remote_io_access_event* node =
                (struct remote_io_access_event*)list_pop(&remote_io->requests);

            if (!node) {
                ret = -HC_E_FAILURE;
                break;
            }

            ret = list_size(&remote_io->requests);

            spin_lock(&remote_io->lock);
            struct remote_io_access* request = &remote_io_requests[node->cpu_id][node->vcpu_id];
            request->state = REMOTE_IO_STATE_PROCESSING;
            spin_unlock(&remote_io->lock);

            vcpu_writereg(cpu()->vcpu, 1, virt_remote_io_id);
            vcpu_writereg(cpu()->vcpu, 2, request->addr);
            vcpu_writereg(cpu()->vcpu, 3, request->op);
            vcpu_writereg(cpu()->vcpu, 4, request->value);
            vcpu_writereg(cpu()->vcpu, 5, request->access_width);
            vcpu_writereg(cpu()->vcpu, 6, node->cpu_id);
            vcpu_writereg(cpu()->vcpu, 7, node->vcpu_id);

            objpool_free(&remote_io_access_event_pool, node);
            break;
        case REMOTE_IO_HYP_NOTIFY:
            remote_io_cpu_send_msg(REMOTE_IO_CPU_MSG_NOTIFY, remote_io->instance.frontend_cpu_id, 0,
                0, 0, remote_io->instance.frontend_interrupt);
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
    volatile int i = 0;

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
        if (io_device->id == dev.id) {
            struct remote_io_access_event* node = objpool_alloc(&remote_io_access_event_pool);
            struct remote_io_access request;
            request.addr = acc->addr;
            request.reg = acc->reg;
            request.access_width = acc->width;
            request.state = REMOTE_IO_STATE_PENDING;
            node->cpu_id = cpu()->id;
            node->vcpu_id = cpu()->vcpu->id;

            if (acc->write) {
                int value = vcpu_readreg(cpu()->vcpu, acc->reg);
                request.op = REMOTE_IO_HYP_WRITE;
                request.value = value;
            } else {
                request.op = REMOTE_IO_HYP_READ;
                request.value = 0;
            }

            spin_lock(&io_device->lock);
            remote_io_requests[node->cpu_id][node->vcpu_id] = request;
            spin_unlock(&io_device->lock);
            list_push(&io_device->requests, (node_t*)node);
            if (!config.vmlist[io_device->instance.backend_vm_id].platform.remote_io_pooling) {
                remote_io_cpu_send_msg(REMOTE_IO_CPU_MSG_NOTIFY, io_device->instance.backend_cpu_id,
                    0, 0, 0, io_device->instance.backend_interrupt);
            }
            vcpu_writepc(cpu()->vcpu, vcpu_readpc(cpu()->vcpu) + 4);
            cpu()->vcpu->active = false;
            cpu_idle();
            return true;
        }
    }
    return false;
}

/*!
 * @fn              remote_io_cpu_handler
 * @brief           Manages incoming cpu_msg from the frontend or backend
 * @param event     Contains the message event
 * @param data      Contains the Remote I/O ID
 * @return          void
 */
static void remote_io_cpu_handler(uint32_t event, uint64_t data)
{
    union remote_io_cpu_msg_data ipc_data = { .raw = data };
    switch (event) {
        case REMOTE_IO_CPU_MSG_WRITE:
        case REMOTE_IO_CPU_MSG_READ:
            remote_io_cpu_post_work(event, ipc_data.id, ipc_data.cpu_id, ipc_data.vcpu_id);
            break;
        case REMOTE_IO_CPU_MSG_NOTIFY:
            vcpu_inject_irq(cpu()->vcpu, ipc_data.interrupt);
            break;
    }
}
