/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/**
 * @file remio.c
 * @brief This source file contains the Remote I/O implementation
 */

#include <remio.h>
#include <cpu.h>
#include <vm.h>
#include <hypercall.h>
#include <objpool.h>
#include <config.h>
#include <spinlock.h>

#define REMIO_VCPU_NUM             PLAT_CPU_NUM
#define REMIO_NUM_DEV_TYPES        (REMIO_DEV_BACKEND - REMIO_DEV_FRONTEND + 1)
#define REMIO_NEXT_PENDING_REQUEST -1

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
        uint8_t remio_bind_key; /**< Remote I/O bind key */
        uint8_t request_id;     /**< Remote I/O request ID */
        uint8_t interrupt;      /**< Interrupt ID */
    };
    uint64_t raw;               /**< Raw data */
};

/**
 * @struct remio_request
 * @brief This structure contains the information of a Remote I/O request
 */
struct remio_request {
    node_t node;                /** Node */
    objpool_id_t id;            /**< Request ID */
    remio_bind_key_t bind_key;  /**< Remote I/O bind key associated with the request */
    vaddr_t addr;               /**< Address of the accessed MMIO Register */
    unsigned long access_width; /**< Access width */
    unsigned long op;           /**< MMIO operation type (read or write) */
    unsigned long value;        /**< Value to be written or read */
    unsigned long reg;          /**< vCPU resgiter used during the MMIO access */
    cpuid_t cpu_id;             /**< CPU ID of the frontend VM that performed the MMIO access */
    enum REMIO_STATE state;     /**< I/O request state */
};

/**
 * @struct remio_device_config
 * @brief This structure holds the configuration of a Remote I/O device
 */
struct remio_device_config {
    struct {
        remio_bind_key_t bind_key; /**< Backend bind key */
        cpuid_t cpu_id;            /**< Backend VM CPU ID */
        vmid_t vm_id;              /**< Backend VM ID */
        irqid_t interrupt;         /**< Backend interrupt ID */
        struct remio_shmem shmem;  /**< Backend shared memory region */
        bool ready;                /**< Backend ready flag */
    } backend;
    struct {
        remio_bind_key_t bind_key; /**< Frontend bind key */
        cpuid_t cpu_id;            /**< Frontend VM CPU ID */
        vmid_t vm_id;              /**< Frontend VM ID */
        irqid_t interrupt;         /**< Frontend interrupt ID */
        struct remio_shmem shmem;  /**< Frontend shared memory region */
        bool ready;                /**< Frontend ready flag */
    } frontend;
};

/**
 * @struct remio_device
 * @brief This structure comprises all the information needed about a Remote I/O device
 */
struct remio_device {
    node_t node;                       /**< Node */
    volatile bool ready;               /**< Remote I/O device ready flag */
    remio_bind_key_t bind_key;         /**< Remote I/O bind key */
    struct remio_device_config config; /**< Remote I/O device configuration */
    struct list pending_requests_list; /**< List of pending I/O requests */
};

/** List of Remote I/O devices */
struct list remio_device_list;

/**
 * @brief Remote I/O CPU message handler
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param data Remote I/O CPU message data (remio_cpu_msg_data)
 */
static void remio_cpu_msg_handler(uint32_t event, uint64_t data);

/** Associate the Remote I/O CPU message handler with a new Remote I/O CPU message ID */
CPU_MSG_HANDLER(remio_cpu_msg_handler, REMIO_CPUMSG_ID)

/** Object pool to allocate Remote I/O devices */
OBJPOOL_ALLOC(remio_device_pool, struct remio_device,
    CONFIG_REMIO_DEV_NUM ? CONFIG_REMIO_DEV_NUM : 1);

/** Object pool to allocate Remote I/O requests */
OBJPOOL_ALLOC(remio_request_pool, struct remio_request, REMIO_VCPU_NUM);

/**
 * @brief Creates a new Remote I/O request based on the MMIO access information
 * @param device Pointer to the Remote I/O device
 * @param acc Pointer to the emul_access structure containing the MMIO access information
 * @return Returns true if the operation was successful, false otherwise
 */
static bool remio_create_request(struct remio_device* device, struct emul_access* acc)
{
    objpool_id_t id;
    struct remio_request* request = objpool_alloc_with_id(&remio_request_pool, &id);
    if (request == NULL) {
        return false;
    }

    request->id = id;
    request->addr = acc->addr;
    request->reg = acc->reg;
    request->access_width = acc->width;
    request->state = REMIO_STATE_PENDING;
    request->cpu_id = cpu()->id;
    request->bind_key = device->bind_key;

    if (acc->write) {
        long unsigned int value = vcpu_readreg(cpu()->vcpu, acc->reg);
        request->op = REMIO_HYP_WRITE;
        request->value = value;
    } else {
        request->op = REMIO_HYP_READ;
        request->value = 0;
    }

    list_push(&device->pending_requests_list, (node_t*)request);

    return true;
}

/**
 * @brief Gets the Remote I/O request
 * @param device Pointer to the Remote I/O device
 * @param id Remote I/O request ID
 * @return Returns the Remote I/O request or NULL if the request was not found
 */
static inline struct remio_request* remio_get_request(struct remio_device* device, long int id)
{
    struct remio_request* request = NULL;

    if (id == REMIO_NEXT_PENDING_REQUEST) {
        request = (struct remio_request*)list_pop(&device->pending_requests_list);
    } else if (id >= 0) {
        request = objpool_get_by_id(&remio_request_pool, (objpool_id_t)id);
    }

    if (request == NULL || request->bind_key != device->bind_key) {
        return NULL;
    }

    return request;
}

/**
 * @brief Checks if the Remote I/O device has pending I/O requests
 * @param device Pointer to the Remote I/O device
 * @return Returns true if the Remote I/O device has pending I/O requests, false otherwise
 */
static inline bool remio_has_pending_request(struct remio_device* device)
{
    return list_empty(&device->pending_requests_list);
}

/**
 * @brief Finds the Remote I/O device based on the Remote I/O bind key
 * @param bind_key Remote I/O bind key
 * @return Returns the Remote I/O device or NULL if the device was not found
 */
static struct remio_device* remio_find_dev_by_bind_key(remio_bind_key_t bind_key)
{
    struct remio_device* device = NULL;
    list_foreach (remio_device_list, struct remio_device, dev) {
        if (bind_key == dev->bind_key) {
            device = dev;
            break;
        }
    }
    return device;
}

/**
 * @brief Finds the Remote I/O device associated with a VM based on the Remote I/O bind key
 * @param vm Pointer to the VM structure
 * @param bind_key Remote I/O bind key
 * @return Returns the Remote I/O device or NULL if the device was not found
 */
static struct remio_device* remio_find_vm_dev_by_bind_key(struct vm* vm, unsigned long bind_key)
{
    struct remio_dev* dev = NULL;
    struct remio_device* device = NULL;

    /** Find the Remote I/O device VM configuration based on the Remote I/O bind key */
    for (size_t i = 0; i < vm->remio_dev_num; i++) {
        dev = &vm->remio_devs[i];
        if (dev->bind_key == bind_key) {
            break;
        }
    }

    if (dev != NULL) {
        /** Find the Remote I/O device based on the Remote I/O bind key */
        device = remio_find_dev_by_bind_key(bind_key);
        if (device != NULL) {
            /** Check if the Remote I/O device is associated with the VM */
            if ((dev->type == REMIO_DEV_BACKEND && vm->id == device->config.backend.vm_id) ||
                (dev->type == REMIO_DEV_FRONTEND && vm->id == device->config.frontend.vm_id)) {
                return device;
            }
        }
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

    return remio_find_vm_dev_by_bind_key(vm, dev->bind_key);
}

/**
 * @brief Sends a Remote I/O CPU message to the target CPU
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param target_cpu Target CPU ID
 * @param remio_bind_key Remote I/O bind key
 * @param request_id Remote I/O request ID
 * @param interrupt Interrupt ID
 */
static void remio_cpu_send_msg(enum REMIO_CPU_MSG_EVENT event, unsigned long target_cpu,
    unsigned long remio_bind_key, unsigned long request_id, unsigned long interrupt)
{
    union remio_cpu_msg_data data = {
        .remio_bind_key = (uint8_t)remio_bind_key,
        .request_id = (uint8_t)request_id,
        .interrupt = (uint8_t)interrupt,
    };
    struct cpu_msg msg = { (uint32_t)REMIO_CPUMSG_ID, event, data.raw };
    cpu_send_msg(target_cpu, &msg);
}

void remio_init(void)
{
    size_t counter[REMIO_NUM_DEV_TYPES] = { 0 };

    /** Only execute the Remote I/O initialization routine on the master CPU */
    if (!cpu_is_master()) {
        return;
    }

    objpool_init(&remio_device_pool);
    objpool_init(&remio_request_pool);
    list_init(&remio_device_list);

    /** Create the Remote I/O devices based on the VM configuration */
    for (size_t vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
            struct remio_dev* dev = &vm_config->platform.remio_devs[i];
            struct remio_device* device = NULL;
            list_foreach (remio_device_list, struct remio_device, remio_device) {
                if ((dev->bind_key == remio_device->config.backend.bind_key &&
                        dev->type == REMIO_DEV_BACKEND) ||
                    (dev->bind_key == remio_device->config.frontend.bind_key &&
                        dev->type == REMIO_DEV_FRONTEND)) {
                    ERROR("Failed to link backend to the frontend, more than one %s was "
                          "atributed to the Remote I/O device %d",
                        dev->type == REMIO_DEV_BACKEND ? "backend" : "frontend", dev->bind_key);
                } else if ((dev->type == REMIO_DEV_BACKEND &&
                               dev->bind_key == remio_device->config.frontend.bind_key) ||
                    (dev->type == REMIO_DEV_FRONTEND &&
                        dev->bind_key == remio_device->config.backend.bind_key)) {
                    device = remio_device;
                    break;
                }
            }
            if (device == NULL) {
                device = objpool_alloc(&remio_device_pool);
                if (device == NULL) {
                    ERROR("Failed creating Remote I/O device %d", dev->bind_key);
                }
                device->ready = false;
                device->bind_key = dev->bind_key;
                device->config.backend.bind_key = (remio_bind_key_t)-1;
                device->config.frontend.bind_key = (remio_bind_key_t)-1;
                list_init(&device->pending_requests_list);
                list_push(&remio_device_list, (node_t*)device);
            }
            if (dev->type == REMIO_DEV_BACKEND) {
                device->config.backend.bind_key = dev->bind_key;
                device->config.backend.shmem = dev->shmem;
                device->config.backend.ready = false;
            } else if (dev->type == REMIO_DEV_FRONTEND) {
                device->config.frontend.bind_key = dev->bind_key;
                device->config.frontend.shmem = dev->shmem;
                device->config.frontend.ready = false;
            } else {
                ERROR("Unknown Remote I/O device type");
            }
            counter[dev->type]++;
        }
    }

    /** Check if there is a 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend */
    if (counter[REMIO_DEV_FRONTEND] != counter[REMIO_DEV_BACKEND]) {
        ERROR("There is no 1-to-1 mapping between a Remote I/O backend and Remote I/O frontend");
    }

    /** Check if the shared memory regions are correctly configured */
    list_foreach (remio_device_list, struct remio_device, dev) {
        if (dev->config.backend.shmem.base != dev->config.frontend.shmem.base ||
            dev->config.backend.shmem.size != dev->config.frontend.shmem.size ||
            dev->config.backend.shmem.shmem_id != dev->config.frontend.shmem.shmem_id) {
            ERROR("Invalid shared memory region configuration for Remote I/O device %d.\n"
                  "The frontend and backend shared memory regions must be the aligned.",
                dev->bind_key);
        }
    }

    /** Update the Remote I/O device configuration */
    for (size_t vm_id = 0; vm_id < config.vmlist_size; vm_id++) {
        struct vm_config* vm_config = &config.vmlist[vm_id];
        for (size_t i = 0; i < vm_config->platform.remio_dev_num; i++) {
            struct remio_dev* dev = &vm_config->platform.remio_devs[i];
            struct remio_device* device = remio_find_dev_by_bind_key(dev->bind_key);
            if (device == NULL) {
                ERROR("Failed to find Remote I/O device %d", dev->bind_key);
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
}

void remio_assign_vm_cpus(struct vm* vm)
{
    list_foreach (remio_device_list, struct remio_device, dev) {
        if (vm->id == dev->config.backend.vm_id) {
            dev->config.backend.cpu_id = min(dev->config.backend.cpu_id, cpu()->id);
            dev->config.backend.ready = true;
        } else if (vm->id == dev->config.frontend.vm_id) {
            dev->config.frontend.cpu_id = min(dev->config.frontend.cpu_id, cpu()->id);
            dev->config.frontend.ready = true;
        }
        dev->ready = dev->config.backend.ready && dev->config.frontend.ready;
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
    long int ret = -HC_E_SUCCESS;
    bool has_pending_requests = false;
    struct remio_request* request = NULL;

    /** By convention, the addr and value fields must be zero */
    if (addr != 0 || value != 0) {
        return HC_E_FAILURE;
    }

    /** Get the next pending I/O request */
    request = remio_get_request(device, REMIO_NEXT_PENDING_REQUEST);

    if (request == NULL || request->state != REMIO_STATE_PENDING) {
        return HC_E_FAILURE;
    }

    /** Check if the Remote I/O device has other pending I/O requests */
    has_pending_requests = remio_has_pending_request(device);

    /** Update the I/O request state as processing */
    request->state = REMIO_STATE_PROCESSING;

    /** Write the I/O request information to the backend VM's vCPU registers */
    hypercall_set_ret(cpu()->vcpu, 0, request->addr);
    hypercall_set_ret(cpu()->vcpu, 1, request->op);
    hypercall_set_ret(cpu()->vcpu, 2, request->value);
    hypercall_set_ret(cpu()->vcpu, 3, request->access_width);
    hypercall_set_ret(cpu()->vcpu, 4, request->id);
    hypercall_set_ret(cpu()->vcpu, 5, (unsigned long)has_pending_requests);

    return ret;
}

/**
 * @brief Handles the Remote I/O read and write operations
 * @param value Value to be written or read
 * @param request_id Remote I/O request ID
 * @param device Pointer to the Remote I/O device
 * @return Returns true if the operation was successful, false otherwise
 */
static bool remio_handle_rw(unsigned long value, unsigned long request_id,
    struct remio_device* device)
{
    struct remio_request* request = remio_get_request(device, (long int)request_id);
    if (request == NULL) {
        return false;
    }
    if (request->state != REMIO_STATE_PROCESSING) {
        return false;
    }
    request->value = value;
    request->state = REMIO_STATE_COMPLETE;
    return true;
}

/**
 * @brief Performs the post work after the completion of the I/O request
 * @note This function is executed by the frontend VM and is responsible for updating the
 *       vCPU register in case of a read operation and activating the frontend vCPU
 * @param event Message event (REMIO_CPU_MSG_*)
 * @param remio_bind_key Remote I/O bind key
 * @param request_id Remote I/O request ID
 * @return Returns true if the operation was successful, false otherwise
 */
static bool remio_cpu_post_work(uint32_t event, uint8_t remio_bind_key, uint8_t request_id)
{
    struct remio_device* device = remio_find_dev_by_bind_key(remio_bind_key);
    if (device == NULL) {
        return false;
    }

    struct remio_request* request = remio_get_request(device, (long int)request_id);
    if (request == NULL) {
        return false;
    }

    switch (event) {
        case REMIO_CPU_MSG_READ:
            vcpu_writereg(cpu()->vcpu, request->reg, request->value);
            break;
        default:
            break;
    }

    request->state = REMIO_STATE_FREE;
    objpool_free(&remio_request_pool, request);
    cpu()->vcpu->active = true;

    return true;
}

long int remio_hypercall(void)
{
    long int ret = -HC_E_SUCCESS;
    unsigned long dm_id = hypercall_get_arg(cpu()->vcpu, 0);
    unsigned long addr = hypercall_get_arg(cpu()->vcpu, 1);
    unsigned long op = hypercall_get_arg(cpu()->vcpu, 2);
    unsigned long value = hypercall_get_arg(cpu()->vcpu, 3);
    unsigned long request_id = hypercall_get_arg(cpu()->vcpu, 4);
    struct remio_device* device = NULL;
    struct vm* vm = cpu()->vcpu->vm;

    /** Check if the device model ID is within the valid range */
    if (dm_id >= vm->remio_dev_num) {
        return -HC_E_INVAL_ARGS;
    }

    /** Get the Remote I/O bind key based on the device model ID */
    unsigned long remio_dev_bind_key = vm->remio_devs[dm_id].bind_key;

    /** Find the Remote I/O device associated with the current backend VM */
    device = remio_find_vm_dev_by_bind_key(vm, remio_dev_bind_key);
    if (device == NULL) {
        return -HC_E_FAILURE;
    }

    switch (op) {
        case REMIO_HYP_WRITE:
        case REMIO_HYP_READ:
            if (remio_handle_rw(value, request_id, device)) {
                struct remio_request* request = remio_get_request(device, (long int)request_id);
                if (request == NULL) {
                    return -HC_E_FAILURE;
                }
                /** Send a CPU message to the backend VM to execute the post work */
                remio_cpu_send_msg(op == REMIO_HYP_WRITE ? REMIO_CPU_MSG_WRITE : REMIO_CPU_MSG_READ,
                    request->cpu_id, remio_dev_bind_key, request_id, 0);
            } else {
                ret = -HC_E_FAILURE;
            }
            break;
        case REMIO_HYP_ASK:
            ret = remio_handle_ask(addr, value, device);
            break;
        case REMIO_HYP_NOTIFY:
            /** Send a CPU message to the frontend VM to inject an interrupt */
            remio_cpu_send_msg(REMIO_CPU_MSG_NOTIFY, device->config.frontend.cpu_id, 0, 0,
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

    /** Wait until the Remote I/O device is ready */
    while (!device->ready)
        ;

    /** Create a new Remote I/O request based on the MMIO access information */
    if (!remio_create_request(device, acc)) {
        return false;
    }

    /** Send a CPU message to the backend VM to then inject an interrupt */
    remio_cpu_send_msg(REMIO_CPU_MSG_NOTIFY, device->config.backend.cpu_id, 0, 0,
        device->config.backend.interrupt);

    /** Pause the current vCPU to wait for the MMIO emulation to be completed */
    cpu()->vcpu->active = false;

    return true;
}

static void remio_cpu_msg_handler(uint32_t event, uint64_t data)
{
    union remio_cpu_msg_data msg = { .raw = data };
    switch (event) {
        case REMIO_CPU_MSG_WRITE:
        case REMIO_CPU_MSG_READ:
            if (!remio_cpu_post_work(event, msg.remio_bind_key, msg.request_id)) {
                ERROR("Failed to perform the post work after the completion of the I/O request");
            }
            break;
        case REMIO_CPU_MSG_NOTIFY:
            vcpu_inject_irq(cpu()->vcpu, msg.interrupt);
            break;
        default:
            WARNING("Unknown Remote I/O CPU message event");
            break;
    }
}
