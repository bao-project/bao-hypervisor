/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/**
 * @file remio.c
 * @brief This source file contains the Remote I/O implementation
 */

#include "inc/bao.h"
#include "inc/types.h"
#include <remio.h>
#include <cpu.h>
#include <vm.h>
#include <hypercall.h>
#include <objpool.h>
#include <config.h>
#include <spinlock.h>
#include <util.h>

#define REMIO_MAX_DEVICES          32
#define REMIO_DEVICE_UNINITIALIZED -1
#define REMIO_CPU_NUM              PLAT_CPU_NUM
#define REMIO_VCPU_NUM             PLAT_CPU_NUM
#define REMIO_NUM_DEV_TYPES        (REMIO_DEV_BACKEND - REMIO_DEV_FRONTEND + 1)

/**
 * @enum REMIO_HYP_EVENT
 * @brief This enum represents the Remote I/O hypercall events
 * @note Used by the backend VM to specify the operation to be performed
 */
enum REMIO_HYP_EVENT {
    REMIO_HYP_WRITE,  /**< Write operation */
    REMIO_HYP_READ,   /**< Read operation */
    REMIO_HYP_ASK,    /**< Ask operation (used to request a new pending I/O request) */
    REMIO_HYP_NOTIFY, /**< Notify operation (used buffer or configuration change) */
};

/**
 * @enum REMIO_CPU_MSG_EVENT
 * @brief This enum represents the Remote I/O CPU message events
 */
enum REMIO_CPU_MSG_EVENT {
    REMIO_CPU_MSG_WRITE,  /**< Write notification */
    REMIO_CPU_MSG_READ,   /**< Read notification */
    REMIO_CPU_MSG_NOTIFY, /**< Notify notification (used to inject an interrupt into the
                                 frontend or backend VM) */
};

/**
 * @enum REMIO_STATE
 * @brief This enum represents the I/O request states
 */
enum REMIO_STATE {
    REMIO_STATE_FREE,       /**< The I/O request slot is free */
    REMIO_STATE_PENDING,    /**< The I/O request is pending to be processed by the backend VM */
    REMIO_STATE_PROCESSING, /**< The I/O request is being processed by the backend VM */
    REMIO_STATE_COMPLETE,   /**< The I/O request was completed by the backend VM but not yet
                                   completed on frontend VM's eyes */
};

/**
 * @union remio_cpu_msg_data
 * @brief This union represents the Remote I/O CPU message data
 */
union remio_cpu_msg_data {
    struct {
        uint8_t id;        /**< Remote I/O ID */
        uint8_t cpu_id;    /**< Frontend CPU ID */
        uint8_t vcpu_id;   /**< Frontend vCPU ID */
        uint8_t interrupt; /**< Interrupt ID */
    };
    uint64_t raw;          /**< Raw data */
};

/**
 * @struct remio_request
 * @brief This structure contains the information of a Remote I/O request
 */
struct remio_request {
    vaddr_t addr;               /**< Address of the accessed MMIO Register */
    unsigned long access_width; /**< Access width */
    unsigned long op;           /**< MMIO operation type (read or write) */
    unsigned long value;        /**< Value to be written or read */
    unsigned long reg;          /**< vCPU resgiter used during the MMIO access */
    enum REMIO_STATE state;     /**< I/O request state */
};

/**
 * @struct remio_request_event
 * @brief This structure contains the information of a Remote I/O request event
 * @note  This is used to only advertise the backend VM that a new I/O request is available
 *        and the backend VM can ask for it, avoiding the need to iterate over all the
 *        CPUs and vCPUs slots to find the next I/O request to be processed
 */
struct remio_request_event {
    node_t node;      /** Node */
    cpuid_t cpu_id;   /** CPU ID of the frontend VM that issued the I/O request */
    vcpuid_t vcpu_id; /** vCPU ID of the frontend VM that issued the I/O request */
};

/**
 * @struct remio_device_config
 * @brief This structure holds the static information regarding a Remote I/O device
 */
struct remio_device_config {
    struct {
        cpuid_t cpu_id;    /**< Backend VM CPU ID */
        vmid_t vm_id;      /**< Backend VM ID */
        irqid_t interrupt; /**< Backend interrupt ID */
    } backend;
    struct {
        cpuid_t cpu_id;    /**< Frontend VM CPU ID */
        vmid_t vm_id;      /**< Frontend VM ID */
        irqid_t interrupt; /**< Frontend interrupt ID */
    } frontend;
};

/**
 * @struct remio_device
 * @brief This structure comprises all the information needed about a Remote I/O device
 */
struct remio_device {
    node_t node;                       /**< Node */
    remio_id_t id;                     /**< Remote I/O device ID */
    struct remio_device_config config; /**< Remote I/O device configuration */
    struct list request_event_list;    /**< List of pending I/O requests events */
};

/** List of Remote I/O devices */
struct list remio_device_list;

/** Array of Remote I/O requests */
struct remio_request remio_requests[REMIO_CPU_NUM][REMIO_VCPU_NUM];

/**
 * @brief Remote I/O CPU message handler
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param data Remote I/O CPU message data (remio_cpu_msg_data)
 */
static void remio_cpu_handler(uint32_t event, uint64_t data);

/** Associate the Remote I/O CPU message handler with a new Remote I/O CPU message ID */
CPU_MSG_HANDLER(remio_cpu_handler, REMIO_CPUMSG_ID)

/** Object pool to allocate Remote I/O devices */
OBJPOOL_ALLOC(remio_device_pool, struct remio_device, sizeof(struct remio_device));

/** Object pool to allocate pending Remote I/O requests events */
OBJPOOL_ALLOC(remio_request_event_pool, struct remio_request_event,
    sizeof(struct remio_request_event));

/**
 * @brief Creates a new Remote I/O request based on the MMIO access information
 * @param acc Pointer to the emul_access structure containing the MMIO access information
 * @return Returns the Remote I/O request
 */
static struct remio_request remio_create_request(struct emul_access* acc)
{
    struct remio_request request;
    request.addr = acc->addr;
    request.reg = acc->reg;
    request.access_width = acc->width;
    request.state = REMIO_STATE_PENDING;

    if (acc->write) {
        long unsigned int value = vcpu_readreg(cpu()->vcpu, acc->reg);
        request.op = REMIO_HYP_WRITE;
        request.value = value;
    } else {
        request.op = REMIO_HYP_READ;
        request.value = 0;
    }

    return request;
}

/**
 * @brief Gets the Remote I/O request indexed by the CPU ID and vCPU ID
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @return Returns the Remote I/O request
 */
static struct remio_request* remio_get_request(unsigned long cpu_id, unsigned long vcpu_id)
{
    return &remio_requests[cpu_id][vcpu_id];
}

/**
 * @brief Inserts a new Remote I/O request
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @param request Pointer to the Remote I/O request
 */
static void remio_insert_request(unsigned long cpu_id, unsigned long vcpu_id,
    struct remio_request* request)
{
    remio_requests[cpu_id][vcpu_id] = *request;
}

/**
 * @brief Sets the state of a Remote I/O request
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @param state New state of the I/O request
 */
static void remio_set_request_state(unsigned long cpu_id, unsigned long vcpu_id,
    enum REMIO_STATE state)
{
    struct remio_request* request = remio_get_request(cpu_id, vcpu_id);
    request->state = state;
}

/**
 * @brief Gets the state of a Remote I/O request
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @return Returns the state of the I/O request
 */
static enum REMIO_STATE remio_get_request_state(unsigned long cpu_id, unsigned long vcpu_id)
{
    struct remio_request* request = remio_get_request(cpu_id, vcpu_id);
    return request->state;
}

/**
 * @brief Sets the value of a Remote I/O request
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @param value New value of the I/O request
 */
static void remio_set_request_value(unsigned long cpu_id, unsigned long vcpu_id, unsigned long value)
{
    struct remio_request* request = remio_get_request(cpu_id, vcpu_id);
    request->value = value;
}

/**
 * @brief Creates a new Remote I/O request event
 * @return Returns the Remote I/O request event or NULL if the allocation failed
 */
static struct remio_request_event* remio_create_event(void)
{
    struct remio_request_event* event = objpool_alloc(&remio_request_event_pool);
    if (event == NULL) {
        return NULL;
    }

    /** Fill the I/O request event information */
    event->cpu_id = cpu()->id;
    event->vcpu_id = cpu()->vcpu->id;

    return event;
}

/**
 * @brief Push a new Remote I/O request event into the list of pending I/O requests events
 * @param device Pointer to the Remote I/O device
 * @param event Pointer to the Remote I/O request event
 */
static void remio_push_request_event(struct remio_device* device, struct remio_request_event* event)
{
    list_push(&device->request_event_list, (node_t*)event);
}

/**
 * @brief Pop the next I/O request event from the list of pending I/O requests events
 * @param device Pointer to the Remote I/O device
 * @return Returns the next pending I/O request event or NULL if there is no pending I/O request
 */
static struct remio_request_event* remio_pop_request_event(struct remio_device* device)
{
    struct remio_request_event* event =
        (struct remio_request_event*)list_pop(&device->request_event_list);
    return event;
}

/**
 * @brief Gets the number of pending I/O requests
 * @param device Pointer to the Remote I/O device
 * @return Returns the number of pending I/O requests
 */
static size_t remio_get_request_event_count(struct remio_device* device)
{
    return list_size(&device->request_event_list);
}

/**
 * @brief Finds the Remote I/O device based on the Remote I/O device ID
 * @param id Remote I/O device ID
 * @return Returns the Remote I/O device or NULL if the device was not found
 */
static struct remio_device* remio_find_dev_by_id(remio_id_t id)
{
    struct remio_device* device = NULL;
    list_foreach (remio_device_list, struct remio_device, dev) {
        if (id == dev->id) {
            device = dev;
            break;
        }
    }
    return device;
}

/**
 * @brief Finds the Remote I/O device associated with a VM based on the Remote I/O device ID
 * @param vm Pointer to the VM structure
 * @param id Remote I/O device ID
 * @return Returns the Remote I/O device or NULL if the device was not found
 */
static struct remio_device* remio_find_vm_dev_by_id(struct vm* vm, unsigned long id)
{
    struct remio_dev* dev = NULL;
    struct remio_device* device = NULL;

    /** Find the Remote I/O device VM configuration based on the Remote I/O device ID */
    for (size_t i = 0; i < vm->remio_dev_num; i++) {
        dev = &vm->remio_devs[i];
        if (dev->id == id) {
            break;
        }
    }

    if (dev == NULL) {
        return NULL;
    }

    /** Find the Remote I/O device based on the Remote I/O device ID */
    device = remio_find_dev_by_id(id);
    if (device == NULL) {
        return NULL;
    }

    /** Check if the Remote I/O device is associated with the VM */
    if (dev->type == REMIO_DEV_BACKEND && vm->id == device->config.backend.vm_id) {
        return device;
    } else if (dev->type == REMIO_DEV_FRONTEND && vm->id == device->config.frontend.vm_id) {
        return device;
    } else {
        return NULL;
    }

    return NULL;
}

/**
 * @brief Finds the Remote I/O device associated with a VM based on the MMIO access address
 * @param vm Pointer to the VM structure
 * @param addr MMIO access address
 * @return Returns the Remote I/O device or NULL if the device was not found
 */
static struct remio_device* remio_find_vm_dev_by_addr(struct vm* vm, unsigned long addr)
{
    struct remio_dev* dev = NULL;

    for (size_t i = 0; i < vm->remio_dev_num; i++) {
        dev = &vm->remio_devs[i];
        if (in_range(addr, dev->va, dev->size)) {
            break;
        }
    }

    if (dev == NULL) {
        return NULL;
    }

    return remio_find_vm_dev_by_id(vm, dev->id);
}

/**
 * @brief Sends a Remote I/O CPU message to the target CPU
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param target_cpu Target CPU ID
 * @param id Remote I/O device ID
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @param interrupt Interrupt ID
 */
static void remio_cpu_send_msg(enum REMIO_CPU_MSG_EVENT event, unsigned long target_cpu,
    unsigned long id, unsigned long cpu_id, unsigned long long vcpu_id, unsigned long interrupt)
{
    union remio_cpu_msg_data data = {
        .id = (uint8_t)id,
        .cpu_id = (uint8_t)cpu_id,
        .vcpu_id = (uint8_t)vcpu_id,
        .interrupt = (uint8_t)interrupt,
    };
    struct cpu_msg msg = { (uint32_t)REMIO_CPUMSG_ID, event, data.raw };
    cpu_send_msg(target_cpu, &msg);
}

void remio_init(void)
{
    size_t frontend_cnt = 0, backend_cnt = 0;
    int devices[REMIO_MAX_DEVICES][REMIO_NUM_DEV_TYPES];

    /** Only execute the Remote I/O initialization routine on the master CPU */
    if (!cpu_is_master()) {
        return;
    }

    objpool_init(&remio_device_pool);
    objpool_init(&remio_request_event_pool);
    list_init(&remio_device_list);

    for (size_t i = 0; i < REMIO_MAX_DEVICES; i++) {
        devices[i][REMIO_DEV_FRONTEND] = REMIO_DEVICE_UNINITIALIZED;
        devices[i][REMIO_DEV_BACKEND] = REMIO_DEVICE_UNINITIALIZED;
    }

    /** Create the Remote I/O devices based on the VM configuration */
    for (size_t vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
            struct remio_dev* dev = &vm_config->platform.remio_devs[i];
            if (devices[dev->id][dev->type] != REMIO_DEVICE_UNINITIALIZED) {
                ERROR("Failed to link backend to the frontend, more than one %s was "
                      "atributed to the Remote I/O device %d",
                    dev->type == REMIO_DEV_BACKEND ? "backend" : "frontend", dev->id);
            }
            if (dev->type == REMIO_DEV_BACKEND) {
                struct remio_device* device = objpool_alloc(&remio_device_pool);
                if (device == NULL) {
                    ERROR("Failed allocating Remote I/O device node");
                }
                device->id = dev->id;
                list_init(&device->request_event_list);
                list_push(&remio_device_list, (node_t*)device);
                backend_cnt++;
                devices[dev->id][REMIO_DEV_BACKEND] = (int)vm_id;
            } else if (dev->type == REMIO_DEV_FRONTEND) {
                frontend_cnt++;
                devices[dev->id][REMIO_DEV_FRONTEND] = (int)vm_id;
            } else {
                ERROR("Unknown Remote I/O device type");
            }
        }
    }

    /** Check if there is a 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend */
    if (backend_cnt != frontend_cnt) {
        ERROR("There is no 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend");
    }

    /** Update the Remote I/O device configuration */
    for (size_t vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
            struct remio_dev* dev = &vm_config->platform.remio_devs[i];
            struct remio_device* device = remio_find_dev_by_id(dev->id);
            if (device == NULL) {
                ERROR("Failed to find Remote I/O device %d", dev->id);
            }
            if (dev->type == REMIO_DEV_BACKEND) {
                device->config.backend.vm_id = vm_id;
                device->config.backend.interrupt = dev->interrupt;
                device->config.backend.cpu_id = (cpuid_t)-1;
            } else if (dev->type == REMIO_DEV_FRONTEND) {
                device->config.frontend.vm_id = vm_id;
                device->config.frontend.interrupt = dev->interrupt;
                device->config.frontend.cpu_id = (cpuid_t)-1;
            } else {
                ERROR("Unknown Remote I/O device type");
            }
        }
    }

    /** Initialize the Remote I/O requests array */
    for (size_t cpu_idx = 0; cpu_idx < REMIO_CPU_NUM; cpu_idx++) {
        for (size_t vcpu_idx = 0; vcpu_idx < REMIO_VCPU_NUM; vcpu_idx++) {
            remio_set_request_state(cpu_idx, vcpu_idx, REMIO_STATE_FREE);
        }
    }
}

void remio_assign_vm_cpus(struct vm* vm)
{
    list_foreach (remio_device_list, struct remio_device, dev) {
        if (vm->id == dev->config.backend.vm_id) {
            dev->config.backend.cpu_id = min(dev->config.backend.cpu_id, cpu()->id);
        } else if (vm->id == dev->config.frontend.vm_id) {
            dev->config.frontend.cpu_id = min(dev->config.frontend.cpu_id, cpu()->id);
        }
    }
}

/**
 * @brief Handles the Remote I/O ask operation
 * @param addr Should always be zero (convention)
 * @param value Should always be zero (convention)
 * @param device Pointer to the Remote I/O device
 * @return Returns the number of pending I/O requests
 */
static long int remio_handle_ask(unsigned long addr, unsigned long value,
    struct remio_device* device)
{
    long int ret = -HC_E_FAILURE;

    /** By convention, the addr and value fields must be zero */
    if (addr != 0 || value != 0) {
        return ret;
    }

    struct remio_request_event* event = remio_pop_request_event(device);
    if (event == NULL) {
        return ret;
    }

    if (remio_get_request_state(event->cpu_id, event->vcpu_id) != REMIO_STATE_PENDING) {
        objpool_free(&remio_request_event_pool, event);
        return ret;
    }

    /** Calculate the remaining number of pending I/O requests */
    ret = (long int)remio_get_request_event_count(device);

    remio_set_request_state(event->cpu_id, event->vcpu_id, REMIO_STATE_PROCESSING);

    struct remio_request* request = remio_get_request(event->cpu_id, event->vcpu_id);

    /** Write the I/O request information to the backend VM's vCPU registers */
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(0), request->addr);
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(1), request->op);
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(2), request->value);
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(3), request->access_width);
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(4), event->cpu_id);
    vcpu_writereg(cpu()->vcpu, HYPCALL_OUT_ARG_REG(5), event->vcpu_id);

    objpool_free(&remio_request_event_pool, event);

    return ret;
}

/**
 * @brief Handles the Remote I/O read and write operations
 * @param value Value to be written or read
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @return Returns true if the operation was successful, false otherwise
 */
static bool remio_handle_rw(unsigned long value, unsigned long cpu_id, unsigned long vcpu_id)
{
    if (remio_get_request_state(cpu_id, vcpu_id) != REMIO_STATE_PROCESSING) {
        return false;
    }
    remio_set_request_value(cpu_id, vcpu_id, value);
    remio_set_request_state(cpu_id, vcpu_id, REMIO_STATE_COMPLETE);
    return true;
}

/**
 * @brief Performs the post work after the completion of the I/O request
 * @note This function is executed by the frontend VM and is responsible for updating the
 *       vCPU register in case of a read operation and activating the frontend vCPU
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param cpu_id CPU ID of the frontend VM that issued the I/O request
 * @param vcpu_id vCPU ID of the frontend VM that issued the I/O request
 * @return Returns true if the operation was successful, false otherwise
 */
static bool remio_cpu_post_work(uint32_t event, uint8_t cpu_id, uint8_t vcpu_id)
{
    if (remio_get_request_state(cpu_id, vcpu_id) != REMIO_STATE_COMPLETE) {
        return false;
    }
    struct remio_request* request = remio_get_request(cpu_id, vcpu_id);

    switch (event) {
        case REMIO_CPU_MSG_READ:
            vcpu_writereg(cpu()->vcpu, request->reg, request->value);
            break;
        default:
            break;
    }

    remio_set_request_state(cpu_id, vcpu_id, REMIO_STATE_FREE);

    cpu()->vcpu->active = true;

    return true;
}

long int remio_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
    long int ret = -HC_E_SUCCESS;
    unsigned long virt_remio_dev_id = arg0;
    unsigned long addr = arg1;
    unsigned long op = arg2;
    unsigned long value = vcpu_readreg(cpu()->vcpu, HYPCALL_IN_ARG_REG(3));
    unsigned long cpu_id = vcpu_readreg(cpu()->vcpu, HYPCALL_IN_ARG_REG(4));
    unsigned long vcpu_id = vcpu_readreg(cpu()->vcpu, HYPCALL_IN_ARG_REG(5));
    struct remio_device* device = NULL;
    struct vm* vm = cpu()->vcpu->vm;

    /** Check if the virtual Remote I/O device ID is within the valid range */
    if (virt_remio_dev_id >= vm->remio_dev_num) {
        ERROR("Remote I/O ID (%d) exceeds the valid range for backend VM (%d)", virt_remio_dev_id,
            vm->id);
        return -HC_E_FAILURE;
    }

    /** Get the Remote I/O device ID based on the virtual Remote I/O device ID */
    unsigned long remio_dev_id = vm->remio_devs[virt_remio_dev_id].id;

    /** Find the Remote I/O device associated with the current backend VM */
    device = remio_find_vm_dev_by_id(vm, remio_dev_id);
    if (device == NULL) {
        ERROR("The Remote I/O backend device (%d) is not associated with the current backend VM "
              "(%d)",
            virt_remio_dev_id, vm->id);
        return -HC_E_FAILURE;
    }

    switch (op) {
        case REMIO_HYP_WRITE:
        case REMIO_HYP_READ:
            if (!remio_handle_rw(value, cpu_id, vcpu_id)) {
                ret = -HC_E_FAILURE;
            } else {
                /** Send a CPU message to the backend VM to execute the post work */
                remio_cpu_send_msg(op == REMIO_HYP_WRITE ? REMIO_CPU_MSG_WRITE : REMIO_CPU_MSG_READ,
                    cpu_id, remio_dev_id, cpu_id, vcpu_id, 0);
            }
            break;
        case REMIO_HYP_ASK:
            ret = remio_handle_ask(addr, value, device);
            break;
        case REMIO_HYP_NOTIFY:
            /** Send a CPU message to the frontend VM to inject an interrupt */
            remio_cpu_send_msg(REMIO_CPU_MSG_NOTIFY, device->config.frontend.cpu_id, 0, 0, 0,
                device->config.frontend.interrupt);
            break;
        default:
            ret = -HC_E_INVAL_ARGS;
            break;
    }

    return ret;
}

bool remio_mmio_emul_handler(struct emul_access* acc)
{
    struct remio_device* device = NULL;

    /** Find the Remote I/O device based on the MMIO access address */
    device = remio_find_vm_dev_by_addr(cpu()->vcpu->vm, acc->addr);
    if (device == NULL) {
        return false;
    }

    /** Create a new Remote I/O request based on the MMIO access information */
    struct remio_request request = remio_create_request(acc);

    /** Create a new Remote I/O request event */
    struct remio_request_event* event = remio_create_event();

    /** Insert the I/O request into the Remote I/O request array */
    remio_insert_request(event->cpu_id, event->vcpu_id, &request);

    /** Push the I/O request event into the Remote I/O device list */
    remio_push_request_event(device, event);

    /** Send a CPU message to the backend VM to then inject an interrupt */
    remio_cpu_send_msg(REMIO_CPU_MSG_NOTIFY, device->config.backend.cpu_id, 0, 0, 0,
        device->config.backend.interrupt);

    /** Pause the current vCPU to wait for the MMIO emulation to be completed */
    cpu()->vcpu->active = false;

    return true;
}

static void remio_cpu_handler(uint32_t event, uint64_t data)
{
    union remio_cpu_msg_data ipc_data = { .raw = data };
    switch (event) {
        case REMIO_CPU_MSG_WRITE:
        case REMIO_CPU_MSG_READ:
            if (!remio_cpu_post_work(event, ipc_data.cpu_id, ipc_data.vcpu_id)) {
                ERROR("Failed to perform the post work after the completion of the I/O request");
            }
            break;
        case REMIO_CPU_MSG_NOTIFY:
            vcpu_inject_irq(cpu()->vcpu, ipc_data.interrupt);
            break;
        default:
            WARNING("Unknown Remote I/O CPU message event");
            break;
    }
}
