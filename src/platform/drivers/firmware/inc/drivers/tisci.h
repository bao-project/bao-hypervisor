/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __TISCI_H_
#define __TISCI_H_

#include <arch/spinlock.h>
#include <stddef.h>
#include <stdint.h>
#include <bao.h>
#include <string.h>

/**
 * @brief TISCI Status Codes
 */
typedef enum {
    TISCI_STATUS_CODE_NO_ERROR = 0,
    TISCI_STATUS_CODE_INVALID_MSG_LEN = -1,
    TISCI_STATUS_CODE_MSG_RCV_FAILED = -2,
    TISCI_STATUS_CODE_MSG_SEND_FAILED = -3,
    TISCI_STATUS_CODE_MSG_RX_TIMEOUT = -4,
    TISCI_STATUS_CODE_NO_ACK_RCVD = -5,
} TISCI_STATUS_CODES;

#define TISCI_HOST_DMSC                      (0U)

/* msg request flags */
#define TISCI_MSG_REQ_FLAG_RESERVED0_IDX     (0)
#define TISCI_MSG_REQ_FLAG_AOP_IDX           (1)
#define TISCI_MSG_REQ_FLAG_REQ_NOTFWD2DM_IDX (3)

#define TISCI_MSG_REQ_FLAG_RESERVED0         (1 << TISCI_MSG_REQ_FLAG_RESERVED0_IDX)
#define TISCI_MSG_REQ_FLAG_AOP                                               \
    (1 << TISCI_MSG_REQ_FLAG_AOP_IDX) /* ACK On Processed (AOP) - set if msg \
                                     requires ACK from DMSC */
#define TISCI_MSG_REQ_FLAG_REQ_NOTFWD2DM                 (1 << TISCI_MSG_REQ_FLAG_REQ_NOTFWD2DM_IDX)

/* msg response flags */
#define TISCI_MSG_RSP_FLAG_ACK_IDX                       (1)

#define TISCI_MSG_RSP_FLAG_ACK                           (1 << TISCI_MSG_RSP_FLAG_ACK_IDX)
#define TISCI_MSG_RSP_FLAG_NAK                           (0 << TISCI_MSG_RSP_FLAG_ACK_IDX)

#define TISCI_MSG_MAX_SIZE                               (56U)
#define TISCI_MSG_TXN_TIMEOUT                            (1000) /* 1000ms */
#define TISCI_MSG_NUM_RETRIES                            (5)

#define TISCI_RM_IRQ_VALID_DEST_ID_IDX                   (0U)
#define TISCI_RM_IRQ_VALID_DEST_ID                       (1U << TISCI_RM_IRQ_VALID_DEST_ID_IDX)

#define TISCI_RM_IRQ_VALID_DEST_HOST_IRQ_IDX             (1U)
#define TISCI_RM_IRQ_VALID_DEST_HOST_IRQ                 (1U << TISCI_RM_IRQ_VALID_DEST_HOST_IRQ_IDX)

#define TISCI_RM_IRQ_VALID_IA_ID_IDX                     (2U)
#define TISCI_RM_IRQ_VALID_IA_ID                         (1U << TISCI_RM_IRQ_VALID_IA_ID_IDX)

#define TISCI_RM_IRQ_VALID_VIRT_INT_IDX                  (3U)
#define TISCI_RM_IRQ_VALID_VIRT_INT                      (1U << TISCI_RM_IRQ_VALID_VIRT_INT_IDX)

#define TISCI_RM_IRQ_VALID_GLOBAL_EVENT_IDX              (4U)
#define TISCI_RM_IRQ_VALID_GLOBAL_EVENT                  (1U << TISCI_RM_IRQ_VALID_GLOBAL_EVENT_IDX)

#define TISCI_RM_IRQ_VALID_VIRT_INT_STATUS_BIT_INDEX_IDX (5U)
#define TISCI_RM_IRQ_VALID_VIRT_INT_STATUS_BIT_INDEX \
    (1U << TISCI_RM_IRQ_VALID_VIRT_INT_STATUS_BIT_INDEX_IDX)

#define TISCI_RM_IRQ_VALID_SEC_HOST_IDX (31U)
#define TISCI_RM_IRQ_VALID_SEC_HOST     (1U << TISCI_RM_IRQ_VALID_SEC_HOST_IDX)

/**
 * review the version of the currently running sysfw
 * secure thread msg => NO
 */
#define TISCI_MSG_VERSION               (0x0002U)

/**
 * configure peripherals within the SoC interrupt architecture
 * secure thread msg => NO
 */
#define TISCI_MSG_RM_IRQ_SET            (0x1000U)

/**
 * release an IRQ route between a device peripheral and a host processor
 * secure thread msg => NO
 */
#define TISCI_MSG_RM_IRQ_RELEASE        (0x1001U)

/*
 * tisci msg format
 *
 *          ^  +-----------------------+       +----------------------+
 *          |  |   secure header (4B)  |------>| integrity check (2B) |
 *          |  +-----------------------+       +----------------------+
 * min: 12B |  |                       |       |     reserved (2B)    |
 *          |  |   TISCI header (8B)   |       +----------------------+
 *          |  |                       |
 *          +  +-----------------------+
 *          |  |                       |
 *          |  |                       |
 * max: 56B |  |   payload (max 44B)   |
 *          |  |                       |
 *          |  |                       |
 *          v  +-----------------------+
 *
 */

/**
 * @brief TISCI generic msg header for ALL msg and rsp
 */
typedef struct __attribute__((packed)) {
    /** Message type ID */
    uint16_t type;

    /**
     * logically distinct high level software entity identifier, used to select
     * the set of channels to communicate with the DMSC
     */
    uint8_t host_id;

    /**
     * sequence identifier that will be returned back to the hypervisor for the
     * response corresponding to the message
     */
    uint8_t seq_id;

    /** Message flags */
    uint32_t msg_flags;
} tisci_msg_header;

/**
 * @brief Prefix header for all TISCI msg sent over secure transport.
 */
typedef struct __attribute__((packed)) {
    /** msg integrity checksum, calculated for total msg in the request path */
    uint16_t integ_check;

    /** reserved for future use */
    uint16_t reserved;
} tisci_secure_msg_header;

/**
 * @brief TISCI Transport Operations
 *
 * Platform specific transport operations for sending and receiving messages.
 */
typedef struct {
    /**
     * @brief Send a message over a specific channel.
     *
     * @param chan_id The channel ID to send the message on.
     * @param buffer Pointer to the data to send.
     * @param len Length of the data in bytes.
     *
     * @return TISCI_STATUS_CODE_NO_ERROR on success, error code otherwise.
     */
    int32_t (*send)(uint8_t chan_id, void* buffer, size_t len);

    /**
     * @brief Receive a message from a specific channel.
     *
     * @param chan_id The channel ID to receive the message from.
     * @param buffer Pointer to the buffer to store received data.
     * @param len Maximum length of the buffer.
     *
     * @return TISCI_STATUS_CODE_NO_ERROR on success, error code otherwise.
     */
    int32_t (*recv)(uint8_t chan_id, void* buffer, size_t len);
} tisci_ops;

/**
 * @brief TISCI Driver Context
 *
 * Holds the state and configuration for the TISCI driver instance.
 */
typedef struct {
    /** Transport operations for sending/receiving messages */
    tisci_ops ops;
    /** Lock to protect sequence ID generation */
    spinlock_t seq_id_lock;
    /** Current sequence ID counter */
    uint8_t seq_id;
} tisci_ctx;

/**
 * @brief Response structure for TISCI_MSG_VERSION
 *
 * Returns version information of the currently running System Firmware (SYSFW).
 */
typedef struct __attribute__((packed)) {
    /** Standard TISCI message header */
    tisci_msg_header msg_header;
    /** Description string of the SYSFW */
    char sysfw_desc[32];
    /** SYSFW version number */
    uint16_t sysfw_version;
    /** SYSFW ABI major version */
    uint8_t sysfw_abi_major;
    /** SYSFW ABI minor version */
    uint8_t sysfw_abi_minor;
    /** SYSFW sub-version number */
    uint8_t sysfw_sub_version;
    /** SYSFW patch version number */
    uint8_t sysfw_patch_version;
} tisci_msg_version_rsp;

/**
 * @brief Configures peripheral to processor interrupt route according to the valid configuration
 * provided.
 */
typedef struct __attribute__((packed)) {
    /** Standard TISCI message header */
    tisci_msg_header msg_header;
    /** Bitfield defining validity of interrupt route set parameters */
    uint32_t valid_params;
    /** ID of interrupt source peripheral */
    uint16_t src_id;
    /** Interrupt source index within source peripheral */
    uint16_t src_idx;
    /** SoC IR device ID */
    uint16_t dest_id;
    /** SoC IR output index */
    uint16_t dest_host_irq;
    /** Device ID of interrupt aggregator in which the virtual interrupt resides */
    uint16_t intr_aggr_id;
    /** Virtual interrupt number when configuring an interrupt aggregator */
    uint16_t virt_int;
    /** Global event mapped to interrupt aggregator virtual interrupt status bit */
    uint16_t global_event;
    /** Virtual interrupt status bit to set if the interrupt route utilizes an IA */
    uint8_t virt_int_status_bit_idx;
    /** Secondary host value to replace the host value for the message */
    uint8_t sec_host;
} tisci_msg_rm_irq_set_req;

/**
 * @brief Response to setting a peripheral to processor interrupt route.
 */
typedef struct __attribute__((packed)) {
    /** Standard TISCI message header */
    tisci_msg_header msg_header;
} tisci_msg_rm_irq_set_rsp;

/**
 * @brief Releases peripheral to processor interrupt route according to the valid configuration
 * provided.
 */
typedef struct __attribute__((packed)) {
    /** Standard TISCI message header */
    tisci_msg_header msg_header;
    /** Bitfield defining validity of interrupt route release parameters */
    uint32_t valid_params;
    /** ID of interrupt source peripheral */
    uint16_t src_id;
    /** Interrupt source index within source peripheral */
    uint16_t src_idx;
    /** SoC IR device ID */
    uint16_t dest_id;
    /** SoC IR output index */
    uint16_t dest_host_irq;
    /** Device ID of interrupt aggregator in which the virtual interrupt resides */
    uint16_t intr_aggr_id;
    /** Virtual interrupt number if the interrupt route is through an interrupt aggregator */
    uint16_t virt_int;
    /** Global event mapped to interrupt aggregator virtual interrupt status bit */
    uint16_t global_event;
    /** Virtual interrupt status bit to release if the interrupt route utilizes an IA */
    uint8_t virt_int_status_bit_idx;
    /** Secondary host value to replace the host value for the message */
    uint8_t sec_host;
} tisci_msg_rm_irq_release_req;

/**
 * @brief Response to releasing a peripheral to processor interrupt route.
 */
typedef struct __attribute__((packed)) {
    /** Standard TISCI message header */
    tisci_msg_header msg_header;
} tisci_msg_rm_irq_release_rsp;

/**
 * @brief Retrieves the revision of the System Firmware.
 *
 * @param ctx Pointer to the TISCI driver context.
 * @param host_id The Host ID to be used in the message header.
 * @param tx_chan_id The channel ID to use for the send transaction.
 * @param rx_chan_id The channel ID to use for the recv transaction.
 * @param ver_rsp Pointer to the structure where the version response will be stored.
 *
 * @return TISCI_STATUS_CODE_NO_ERROR on success, or a negative error code on failure.
 */
int32_t tisci_get_revision(tisci_ctx* ctx, uint8_t host_id, uint8_t tx_chan_id, uint8_t rx_chan_id,
    tisci_msg_version_rsp* ver_rsp);

/**
 * @brief Configures peripheral to processor interrupt route.
 *
 * @param ctx Pointer to the TISCI driver context.
 * @param host_id The Host ID to be used in the message header.
 * @param tx_chan_id The channel ID to use for the send transaction.
 * @param rx_chan_id The channel ID to use for the recv transaction.
 * @param irq_set_req Pointer to the interrupt route set request.
 * @param irq_set_rsp Pointer to the interrupt route set response.
 *
 * @return TISCI_STATUS_CODE_NO_ERROR on success, or a negative error code on failure.
 */
int32_t tisci_rm_irq_set(tisci_ctx* ctx, uint8_t host_id, uint8_t tx_chan_id, uint8_t rx_chan_id,
    tisci_msg_rm_irq_set_req* irq_set_req, tisci_msg_rm_irq_set_rsp* irq_set_rsp);

/**
 * @brief Releases peripheral to processor interrupt route.
 *
 * @param ctx Pointer to the TISCI driver context.
 * @param host_id The Host ID to be used in the message header.
 * @param tx_chan_id The channel ID to use for the send transaction.
 * @param rx_chan_id The channel ID to use for the recv transaction.
 * @param irq_release_req Pointer to the interrupt route release request.
 * @param irq_release_rsp Pointer to the interrupt route release response.
 *
 * @return TISCI_STATUS_CODE_NO_ERROR on success, or a negative error code on failure.
 */
int32_t tisci_rm_irq_release(tisci_ctx* ctx, uint8_t host_id, uint8_t tx_chan_id,
    uint8_t rx_chan_id, tisci_msg_rm_irq_release_req* irq_release_req,
    tisci_msg_rm_irq_release_rsp* irq_release_rsp);

#endif /* __TISCI_H_ */
