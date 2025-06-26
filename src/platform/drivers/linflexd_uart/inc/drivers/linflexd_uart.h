/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __LINFLEXD_UART_H_
#define __LINFLEXD_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** LINFLEXD - Register Layout Typedef */
// typedef struct {
struct LINFlexD_Type {
    uint32_t LINCR1;  /**< LIN Control Register 1, offset: 0x0 */
    uint32_t LINIER;  /**< LIN Interrupt Enable Register, offset: 0x4 */
    uint32_t LINSR;   /**< LIN Status Register, offset: 0x8 */
    uint32_t LINESR;  /**< LIN Error Status Register, offset: 0xC */
    uint32_t UARTCR;  /**< UART Mode Control Register, offset: 0x10 */
    uint32_t UARTSR;  /**< UART Mode Status Register, offset: 0x14 */
    uint32_t LINTCSR; /**< LIN Time-Out Control Status Register, offset: 0x18 */
    uint32_t LINOCR;  /**< LIN Output Compare Register, offset: 0x1C */
    uint32_t LINTOCR; /**< LIN Time-Out Control Register, offset: 0x20 */
    uint32_t LINFBRR; /**< LIN Fractional Baud Rate Register, offset: 0x24 */
    uint32_t LINIBRR; /**< LIN Integer Baud Rate Register, offset: 0x28 */
    uint32_t LINCFR;  /**< LIN Checksum Field Register, offset: 0x2C */
    uint32_t LINCR2;  /**< LIN Control Register 2, offset: 0x30 */
    uint32_t BIDR;    /**< Buffer Identifier Register, offset: 0x34 */
    uint32_t BDRL;    /**< Buffer Data Register Least Significant, offset: 0x38 */
    uint32_t BDRM;    /**< Buffer Data Register Most Significant, offset: 0x3C */
    uint8_t RESERVED_0[12];
    uint32_t GCR;     /**< Global Control Register, offset: 0x4C */
    uint32_t UARTPTO; /**< UART Preset Timeout Register, offset: 0x50 */
    uint32_t UARTCTO; /**< UART Current Timeout Register, offset: 0x54 */
    uint32_t DMATXE;  /**< DMA Tx Enable Register, offset: 0x58 */
    uint32_t DMARXE;  /**< DMA Rx Enable Register, offset: 0x5C */
};

typedef struct LINFlexD_Type bao_uart_t;

/* For printk */

#define serial_puts(str_buffer) uart_puts(1, str_buffer)

/** Number of instances of the LINFlexD module. */
#define LINFlexD_INSTANCE_COUNT (12u)

/* LINFLEXD - Peripheral instance base addresses */
/** Peripheral LINFlexD_0 base address */
#define LINFlexD_0_BASE         (0x40170000)
#define LINFlexD_0              ((struct LINFlexD_Type*)LINFlexD_0_BASE)
/** Peripheral LINFlexD_1 base address */
#define LINFlexD_1_BASE         (0x40180000)
#define LINFlexD_1              ((struct LINFlexD_Type*)LINFlexD_1_BASE)
/** Peripheral LINFlexD_2 base address */
#define LINFlexD_2_BASE         (0x40190000)
#define LINFlexD_2              ((struct LINFlexD_Type*)LINFlexD_2_BASE)
/** Peripheral LINFlexD_3 base address */
#define LINFlexD_3_BASE         (0x40970000)
#define LINFlexD_3              ((struct LINFlexD_Type*)LINFlexD_3_BASE)
/** Peripheral LINFlexD_4 base address */
#define LINFlexD_4_BASE         (0x40980000)
#define LINFlexD_4              ((struct LINFlexD_Type*)LINFlexD_4_BASE)
/** Peripheral LINFlexD_5 base address */
#define LINFlexD_5_BASE         (0x40990000)
#define LINFlexD_5              ((struct LINFlexD_Type*)LINFlexD_5_BASE)
/** Peripheral LINFlexD_6 base address */
#define LINFlexD_6_BASE         (0x42170000)
#define LINFlexD_6              ((struct LINFlexD_Type*)LINFlexD_6_BASE)
/** Peripheral LINFlexD_7 base address */
#define LINFlexD_7_BASE         (0x42180000)
#define LINFlexD_7              ((struct LINFlexD_Type*)LINFlexD_7_BASE)
/** Peripheral LINFlexD_8 base address */
#define LINFlexD_8_BASE         (0x42190000)
#define LINFlexD_8              ((struct LINFlexD_Type*)LINFlexD_8_BASE)
/** Peripheral LINFlexD_9 base address */
#define LINFlexD_9_BASE         (0x42980000)
#define LINFlexD_9              ((struct LINFlexD_Type*)LINFlexD_9_BASE)
/** Peripheral LINFlexD_10 base address */
#define LINFlexD_10_BASE        (0x42990000)
#define LINFlexD_10             ((struct LINFlexD_Type*)LINFlexD_10_BASE)
/** Peripheral LINFlexD_11 base address */
#define LINFlexD_11_BASE        (0x429A0000)
#define LINFlexD_11             ((struct LINFlexD_Type*)LINFlexD_11_BASE)

/** Array initializer of LINFLEXD peripheral base addresses */
#define LINFlexD_BASE_ADDRS                                                                  \
    { LINFlexD_0_BASE, LINFlexD_1_BASE, LINFlexD_2_BASE, LINFlexD_3_BASE, LINFlexD_4_BASE,   \
        LINFlexD_5_BASE, LINFlexD_6_BASE, LINFlexD_7_BASE, LINFlexD_8_BASE, LINFlexD_9_BASE, \
        LINFlexD_10_BASE, LINFlexD_11_BASE }
/** Array initializer of LINFLEXD peripheral base pointers */
#define LINFlexD_BASE_PTRS                                                                \
    { LINFlexD_0, LINFlexD_1, LINFlexD_2, LINFlexD_3, LINFlexD_4, LINFlexD_5, LINFlexD_6, \
        LINFlexD_7, LINFlexD_8, LINFlexD_9, LINFlexD_10, LINFlexD_11 }

/* Table of base addresses for LINFlexD instances. */
static struct LINFlexD_Type* const s_LINFlexDBase[LINFlexD_INSTANCE_COUNT] = LINFlexD_BASE_PTRS;

#define LINFlexD_LINSR_LINS_MASK   (0xF000U)
#define LINFlexD_LINSR_LINS_SHIFT  (12U)

/* LINIBRR - LIN Integer Baud Rate Register */
#define LINFlexD_LINIBRR_IBR_MASK  (0xFFFFFU)
#define LINFlexD_LINIBRR_IBR_SHIFT (0U)
#define LINFlexD_LINIBRR_IBR_WIDTH (20U)
#define LINFlexD_LINIBRR_IBR(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINIBRR_IBR_SHIFT)) & LINFlexD_LINIBRR_IBR_MASK)

/* LINFBRR - LIN Fractional Baud Rate Register */
#define LINFlexD_LINFBRR_FBR_MASK  (0xFU)
#define LINFlexD_LINFBRR_FBR_SHIFT (0U)
#define LINFlexD_LINFBRR_FBR_WIDTH (4U)
#define LINFlexD_LINFBRR_FBR(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINFBRR_FBR_SHIFT)) & LINFlexD_LINFBRR_FBR_MASK)

/* LINCR1 - LIN Control Register 1 */
#define LINFlexD_LINCR1_INIT_MASK  (0x1U)
#define LINFlexD_LINCR1_INIT_SHIFT (0U)
#define LINFlexD_LINCR1_INIT_WIDTH (1U)
#define LINFlexD_LINCR1_INIT(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_LINCR1_INIT_SHIFT)) & LINFlexD_LINCR1_INIT_MASK)
#define LINFlexD_LINCR1_SLEEP_MASK (0x2U)

#define DEFAULT_OSR                16U
#define BAUDRATE_FRACTION_WIDTH    LINFlexD_LINFBRR_FBR_WIDTH

/* UARTCR - UART Mode Control Register */
#define LINFlexD_UARTCR_UART_MASK  (0x1U)
#define LINFlexD_UARTCR_UART_SHIFT (0U)
#define LINFlexD_UARTCR_UART_WIDTH (1U)
#define LINFlexD_UARTCR_UART(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_UART_SHIFT)) & LINFlexD_UARTCR_UART_MASK)
#define LINFlexD_UARTCR_WL0_MASK  (0x2U)
#define LINFlexD_UARTCR_WL0_SHIFT (1U)
#define LINFlexD_UARTCR_WL0(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_WL0_SHIFT)) & LINFlexD_UARTCR_WL0_MASK)
#define LINFlexD_UARTCR_PCE_MASK  (0x4U)
#define LINFlexD_UARTCR_PCE_SHIFT (2U)
#define LINFlexD_UARTCR_PCE(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_PCE_SHIFT)) & LINFlexD_UARTCR_PCE_MASK)
#define LINFlexD_UARTCR_WL1_MASK  (0x80U)
#define LINFlexD_UARTCR_WL1_SHIFT (7U)
#define LINFlexD_UARTCR_WL1(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_WL1_SHIFT)) & LINFlexD_UARTCR_WL1_MASK)
#define LINFlexD_UARTCR_RFBM_MASK  (0x200U)
#define LINFlexD_UARTCR_RFBM_SHIFT (9U)
#define LINFlexD_UARTCR_RFBM(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RFBM_SHIFT)) & LINFlexD_UARTCR_RFBM_MASK)
#define LINFlexD_UARTCR_TFBM_MASK  (0x100U)
#define LINFlexD_UARTCR_TFBM_SHIFT (8U)
#define LINFlexD_UARTCR_TFBM(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TFBM_SHIFT)) & LINFlexD_UARTCR_TFBM_MASK)
#define LINFlexD_UARTCR_TDFL_TFC_MASK  (0xE000U)
#define LINFlexD_UARTCR_TDFL_TFC_SHIFT (13U)
#define LINFlexD_UARTCR_TDFL_TFC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TDFL_TFC_SHIFT)) & \
        LINFlexD_UARTCR_TDFL_TFC_MASK)
#define LINFlexD_UARTCR_RDFL_RFC_MASK  (0x1C00U)
#define LINFlexD_UARTCR_RDFL_RFC_SHIFT (10U)
#define LINFlexD_UARTCR_RDFL_RFC(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RDFL_RFC_SHIFT)) & \
        LINFlexD_UARTCR_RDFL_RFC_MASK)
#define LINFlexD_UARTCR_SBUR_MASK  (0x60000U)
#define LINFlexD_UARTCR_SBUR_SHIFT (17U)
#define LINFlexD_UARTCR_SBUR(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_SBUR_SHIFT)) & LINFlexD_UARTCR_SBUR_MASK)
#define LINFlexD_UARTCR_TxEn_MASK  (0x10U)
#define LINFlexD_UARTCR_TxEn_SHIFT (4U)
#define LINFlexD_UARTCR_TxEn(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_TxEn_SHIFT)) & LINFlexD_UARTCR_TxEn_MASK)
#define LINFlexD_UARTCR_RxEn_MASK  (0x20U)
#define LINFlexD_UARTCR_RxEn_SHIFT (5U)
#define LINFlexD_UARTCR_RxEn(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_UARTCR_RxEn_SHIFT)) & LINFlexD_UARTCR_RxEn_MASK)
#define LINFlexD_BDRM_DATA4_MASK (0xFFU)

/* GCR - Global Control Register */
#define LINFlexD_GCR_STOP_MASK   (0x2U)
#define LINFlexD_GCR_STOP_SHIFT  (1U)
#define LINFlexD_GCR_STOP(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_GCR_STOP_SHIFT)) & LINFlexD_GCR_STOP_MASK)

/* UARTSR - UART Mode Status Register */
#define LINFlexD_UARTSR_NF_MASK     (0x1U)
#define LINFlexD_UARTSR_DTFTFF_MASK (0x2U)
#define LINFlexD_UARTSR_DRFRFE_MASK (0x4U)
#define LINFlexD_UARTSR_TO_MASK     (0x8U)
#define LINFlexD_UARTSR_WUF_MASK    (0x20U)
#define LINFlexD_UARTSR_RDI_MASK    (0x40U)
#define LINFlexD_UARTSR_BOF_MASK    (0x80U)
#define LINFlexD_UARTSR_FEF_MASK    (0x100U)
#define LINFlexD_UARTSR_RMB_MASK    (0x200U)
#define LINFlexD_UARTSR_PE_MASK     (0x3C00U)
#define LINFlexD_UARTSR_OCF_MASK    (0x4000U)
#define LINFlexD_UARTSR_SZF_MASK    (0x8000U)

/* BDRL - Buffer Data Register Least Significant */
#define LINFlexD_BDRL_DATA0_MASK    (0xFFU)
#define LINFlexD_BDRL_DATA0_SHIFT   (0U)
#define LINFlexD_BDRL_DATA0(x) \
    (((uint32_t)(((uint32_t)(x)) << LINFlexD_BDRL_DATA0_SHIFT)) & LINFlexD_BDRL_DATA0_MASK)

#define LINFLEXD0_IRQn                   (114u)
// #define LINFlexD_FRAME_ERROR_INT                 (0x100)
// #define LINFlexD_BUFFER_OVERRUN_INT              (0x80U)
#define LINIER_DRIE                      (4)

/* LINFlexD DMA support */
#define FEATURE_LINFLEXD_HAS_DMA_ENABLED (1U)

/* LINFlexD state. */
typedef enum {
    LINFlexD_STATE_SLEEP_MODE = 0U,
    LINFlexD_STATE_INIT_MODE = 1U,
    LINFlexD_STATE_IDLE_MODE = 2U,
    LINFlexD_STATE_SYNC_BREAK = 3U,
    LINFlexD_STATE_SYNC_DEL = 4U,
    LINFlexD_STATE_SYNC_FIELD = 5U,
    LINFlexD_STATE_IDENTIFIER_FIELD = 6U,
    LINFlexD_STATE_HEADER_RX_TX = 7U,
    LINFlexD_STATE_DATA_RX_TX = 8U,
    LINFlexD_STATE_CHECKSUM = 9U
} linflexd_state_t;

/* LINFlexD mode: UART/LIN. */
typedef enum { LINFlexD_LIN_MODE = 0U, LINFlexD_UART_MODE = 1U } linflexd_mode_t;

/* UART Mode: FIFO/BUFFER. */
typedef enum {
    LINFLEXD_UART_RXTX_BUFFER_MODE = 0U,
    LINFLEXD_UART_RXTX_FIFO_MODE = 1U
} linflexd_uart_rxtx_mode_t;

/* UART Status flags.
 * These identifiers provide both mask and shift for status bits in UARTSR register.
 */
typedef enum {
    LINFlexD_UART_NOISE_FLAG = LINFlexD_UARTSR_NF_MASK,
    LINFlexD_UART_DATA_TRANSMITTED_FLAG = LINFlexD_UARTSR_DTFTFF_MASK,
    LINFlexD_UART_DATA_RECEPTION_COMPLETE_FLAG = LINFlexD_UARTSR_DRFRFE_MASK,
    LINFlexD_UART_TIMEOUT_FLAG = LINFlexD_UARTSR_TO_MASK,
    LINFlexD_UART_WAKEUP_FLAG = LINFlexD_UARTSR_WUF_MASK,
    LINFlexD_UART_RECEIVER_INPUT_STATE_FLAG = LINFlexD_UARTSR_RDI_MASK,
    LINFlexD_UART_BUFFER_OVERRUN_FLAG = LINFlexD_UARTSR_BOF_MASK,
    LINFlexD_UART_FRAME_ERROR_FLAG = LINFlexD_UARTSR_FEF_MASK,
    LINFlexD_UART_MESSAGE_BUFFER_FULL_FLAG = LINFlexD_UARTSR_RMB_MASK,
    LINFlexD_UART_PARITY_ERROR_FLAG = LINFlexD_UARTSR_PE_MASK,
    LINFlexD_UART_OUTPUT_COMPARE_FLAG = LINFlexD_UARTSR_OCF_MASK,
    LINFlexD_UART_STUCK_AT_ZERO_FLAG = LINFlexD_UARTSR_SZF_MASK
} linflexd_uart_status_flag_t;

/* Word length in UART mode. */
typedef enum {
    LINFLEXD_UART_7_BITS = 0U,
    LINFLEXD_UART_8_BITS = 1U,
    LINFLEXD_UART_15_BITS = 2U,
    LINFLEXD_UART_16_BITS = 3U
} linflexd_uart_word_length_t;

/* Number of stop bits. */
typedef enum {
    LINFLEXD_UART_ONE_STOP_BIT = 0U,
    LINFLEXD_UART_TWO_STOP_BIT = 1U
} linflexd_uart_stop_bits_count_t;

/* Parity type. */
typedef enum {
    LINFLEXD_UART_PARITY_EVEN = 0U,
    LINFLEXD_UART_PARITY_ODD = 1U,
    LINFLEXD_UART_PARITY_ZERO = 2U,
    LINFLEXD_UART_PARITY_ONE = 3U
} linflexd_uart_parity_type_t;

/* Type of UART transfer (based on interrupts or DMA). */
typedef enum {
    LINFLEXD_UART_USING_DMA = 0U,       /*!< The driver will use DMA to perform UART transfer */
    LINFLEXD_UART_USING_INTERRUPTS = 1U /*!< The driver will use interrupts to perform UART transfer
                                         */
} linflexd_uart_transfer_type_t;

typedef void(*uart_callback_t);
typedef volatile uint8_t semaphore_t;

/* UART state structure */
typedef struct {
    const uint8_t* txBuff;                  /*!< The buffer of data being sent.*/
    uint8_t* rxBuff;                        /*!< The buffer of received data.*/
    volatile uint32_t txSize;               /*!< The remaining number of bytes to be transmitted. */
    volatile uint32_t rxSize;               /*!< The remaining number of bytes to be received. */
    volatile bool isTxBusy;                 /*!< True if there is an active transmit.*/
    volatile bool isRxBusy;                 /*!< True if there is an active receive.*/
    volatile bool isTxBlocking;             /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking;             /*!< True if receive is blocking transaction. */
    uart_callback_t rxCallback;             /*!< Callback to invoke for data receive */
    void* rxCallbackParam;                  /*!< Receive callback parameter pointer.*/
    uart_callback_t txCallback;             /*!< Callback to invoke for data send */
    void* txCallbackParam;                  /*!< Transmit callback parameter pointer.*/
    uart_callback_t errorCallback;          /*!< Callback to invoke on error conditions */
    void* errorCallbackParam;               /*!< Error callback parameter pointer */
    linflexd_uart_word_length_t wordLength; /*!< Word length (8/16 bits) */
    semaphore_t rxComplete; /*!< Synchronization object for blocking Rx timeout condition */
    semaphore_t txComplete; /*!< Synchronization object for blocking Tx timeout condition */
    linflexd_uart_transfer_type_t transferType; /*!< Type of UART transfer (interrupt/dma based) */
    uint8_t rxDMAChannel;                       /*!< DMA channel number for DMA-based rx. */
    uint8_t txDMAChannel;                       /*!< DMA channel number for DMA-based tx. */
    volatile uint8_t transmitStatus;            /*!< Status of last driver transmit operation */
    volatile uint8_t receiveStatus;             /*!< Status of last driver receive operation */
} linflexd_uart_state_t;

/* UART configuration structure */
typedef struct {
    uint32_t baudRate;                             /*!< baud rate */
    bool parityCheck;                              /*!< parity control - enabled/disabled */
    linflexd_uart_parity_type_t parityType;        /*!< always 0/always 1/even/odd */
    linflexd_uart_stop_bits_count_t stopBitsCount; /*!< number of stop bits, 1 stop bit (default) or
                                                      2 stop bits */
    linflexd_uart_word_length_t wordLength;     /*!< number of bits per transmitted/received word */
    linflexd_uart_transfer_type_t transferType; /*!< Type of UART transfer (interrupt/dma based) */
    uint8_t rxDMAChannel;                       /*!< Channel number for DMA rx channel.
                                                     If DMA mode is not used this field will be ignored. */
    uint8_t txDMAChannel;                       /*!< Channel number for DMA tx channel.
                                                     If DMA mode is not used this field will be ignored. */
} linflexd_uart_user_config_t;

/***************************************************
 **                     CLOCKS                    **
 ***************************************************/

#define MC_CGM_0              (0x40030000U)
#define MC_CGM_1              (0x40830000U)
#define MC_CGM_2              (0x41030000U)
#define MC_CGM_3              (0x41830000U)
#define MC_CGM_4              (0x42030000U)
#define MC_CGM_5              (0x42830000U)
#define MC_CGM_6              (0x44030000U)
// #define SELCTL_OFFSET   (24)
// #define SELCTL_WIDTH    (0xF)
// #define SELCTL_MASK(NUM)    ((NUM & SELCTL_WIDTH) << SELCTL_OFFSET)
#define SAFE_CLK_OFFSET       (3)
#define SAFE_CLK_WIDTH        (1)
#define SAFE_CLK_MASK(NUM)    ((NUM & SAFE_CLK_WIDTH) << SAFE_CLK_OFFSET)
#define MUX_CSC_2_OFFSET      (0x380)
#define MUX_CSC_4_OFFSET      (0x400)
#define MUX_CSC_8_OFFSET      (0x500)
#define MUX_DIV0_OFFSET       (2)
#define MUX_SIZE              (0x40)

/***************************************************
 **                      PINS                     **
 ***************************************************/

#define SIUL2_NUM_OF_PIN_PORT 16u

/*!
 * @brief Type of a GPIO channel representation
 * Implements : pins_channel_type_t_Class
 */
typedef uint16_t pins_channel_type_t;

/*!
 * @brief Type of a port levels representation.
 * Implements : pins_level_type_t_Class
 */
typedef uint8_t pins_level_type_t;

/*!
 * @brief Internal resistor pull feature selection
 * Implements : port_pull_config_t_Class
 */
typedef enum {
    PORT_INTERNAL_PULL_DOWN_ENABLED = 0U, /*!< internal pull-down resistor is enabled.     */
    PORT_INTERNAL_PULL_UP_ENABLED = 1U,   /*!< internal pull-up resistor is enabled.       */
    PORT_INTERNAL_PULL_NOT_ENABLED = 2U   /*!< internal pull-down/up resistor is disabled. */
} port_pull_config_t;

/*!
 * @brief Configures the Pin output muxing selection
 * Implements : port_mux_t_Class
 */
typedef enum {
    PORT_MUX_AS_GPIO = 0U, /*!< corresponding pin is configured as GPIO */
    PORT_MUX_ALT1 = 1U,    /*!< chip-specific                           */
    PORT_MUX_ALT2 = 2U,    /*!< chip-specific                           */
    PORT_MUX_ALT3 = 3U,    /*!< chip-specific                           */
    PORT_MUX_ALT4 = 4U,    /*!< chip-specific                           */
    PORT_MUX_ALT5 = 5U,    /*!< chip-specific                           */
    PORT_MUX_ALT6 = 6U,    /*!< chip-specific                           */
    PORT_MUX_ALT7 = 7U     /*!< chip-specific                           */
} port_mux_t;

/*!
 * @brief Configures the interrupt generation condition.
 * Implements : siul2_interrupt_type_t_Class
 */
typedef enum {
    SIUL2_INT_DISABLE = 0x0U,      /*!< Interrupt disable.         */
    SIUL2_INT_RISING_EDGE = 0x1U,  /*!< Interrupt on rising edge.  */
    SIUL2_INT_FALLING_EDGE = 0x2U, /*!< Interrupt on falling edge. */
    SIUL2_INT_EITHER_EDGE = 0x3U   /*!< Interrupt on either edge.  */
} siul2_interrupt_type_t;

/*!
 * @brief Configures the interrupt DMA select.
 * Implements : siul2_interrupt_dma_select_t_Class
 */
typedef enum {
    SIUL2_INT_USING_INTERUPT = 0x0U, /*!< Executived by an interrupt request */
    SIUL2_INT_USING_DMA = 0x1U       /*!< Executived by an DMA request       */
} siul2_interrupt_dma_select_t;

/*!
 * @brief Interrupt configuration structure.
 * Implements : siul2_interrupt_config_t_Class
 */
typedef struct {
    uint8_t eirqPinIdx;                     /*!< The interrupt pin index */
    siul2_interrupt_type_t intEdgeSel;      /*!< The type of edge event */
    bool digitalFilter;                     /*!< Enables digital filter */
    uint8_t maxCnt;                         /*!< Maximum interrupt filter value */
    siul2_interrupt_dma_select_t intExeSel; /*!< Switch between DMA and interrupt request */
} siul2_interrupt_config_t;

/*!
 * @brief Configures the Open Drain Enable field.
 * Implements : port_open_drain_t_Class
 */
typedef enum {
    PORT_OPEN_DRAIN_DISABLED = 0U, /*!< Output is CMOS       */
    PORT_OPEN_DRAIN_ENABLED = 1U   /*!< Output is open drain */
} port_open_drain_t;

/*!
 * @brief Configures the Output Buffer Enable field.
 * Implements : port_output_buffer_t_Class
 */
typedef enum {
    PORT_OUTPUT_BUFFER_DISABLED = 0U, /*!< Output buffer disabled */
    PORT_OUTPUT_BUFFER_ENABLED = 1U   /*!< Output buffer enabled  */
} port_output_buffer_t;

/*!
 * @brief Configures the Input Buffer Enable field.
 * Implements : port_input_buffer_t_Class
 */
typedef enum {
    PORT_INPUT_BUFFER_DISABLED = 0U, /*!< Input buffer disabled */
    PORT_INPUT_BUFFER_ENABLED = 1U   /*!< Input buffer enabled  */
} port_input_buffer_t;

/*!
 * @brief Configures the Analog Pad Control.
 * Implements : port_analog_pad_t_Class
 */
typedef enum {
    PORT_ANALOG_PAD_CONTROL_DISABLED = 0U, /*!< Disable (the switch is off) */
    PORT_ANALOG_PAD_CONTROL_ENABLED = 1U   /*!< Enable (another module can control the state of the
                                              switch) */
} port_analog_pad_t;

/*!
 * @brief Configures the Pin input muxing selection
 * Implements : port_input_mux_t_Class
 */
typedef enum {
    PORT_INPUT_MUX_ALT0 = 0U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT1 = 1U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT2 = 2U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT3 = 3U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT4 = 4U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT5 = 5U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT6 = 6U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_ALT7 = 7U,   /*!< Chip-specific     */
    PORT_INPUT_MUX_NO_INIT = 8U /*!< No initialization */
} port_input_mux_t;

/*!
 * @brief Configures the Safe Mode Control.
 * Implements : port_safe_mode_t_Class
 */
typedef enum {
    PORT_SAFE_MODE_DISABLED = 0U, /*!< To drive pad in hi-z state using OBE = 0, when FCCU in fault
                                   * state. The OBE will be driven by IP/SIUL when FCCU leaves the
                                   * fault state. */
    PORT_SAFE_MODE_ENABLED = 1U   /*!< No effect on IP/SIUL driven OBE value */
} port_safe_mode_t;

/*!
 * @brief Configures the slew rate control.
 * Implements : port_slew_rate_control_t_Class
 */
typedef enum {
    HALF_STRENGTH_WITH_SLEWRATE_CONTROL = 0u,    /*!< Half Strength with Slewrate Control, apply for
                                                    SIUL2_AE        */
    FULL_STRENGTH_WITH_SLEWRATE_CONTROL = 1u,    /*!< Full Strength with Slewrate Control, apply for
                                                    SIUL2_AE        */
    HALF_STRENGTH_WITHOUT_SLEWRATE_CONTROL = 2u, /*!< Half Strength without Slewrate Control, apply
                                                    for SIUL2_AE     */
    FULL_STRENGTH_WITHOUT_SLEWRATE_CONTROL = 3u, /*!< Full Strength without Slewrate Control, apply
                                                    for SIUL2_AE     */
    PORT_SLEW_RATE_CONTROL0 = 0U, /*!< Fmax=208 MHz (at 1.8V), 166 MHz (at 3.3V), apply for
                                     SIUL2_0/1 */
    PORT_SLEW_RATE_CONTROL4 = 4U, /*!< Fmax=166 MHz (at 1.8V), 150 MHz (at 3.3V, apply for SIUL2_0/1
                                   */
    PORT_SLEW_RATE_CONTROL5 = 5U, /*!< Fmax=150 MHz (at 1.8V), 133 MHz (at 3.3V), apply for
                                     SIUL2_0/1 */
    PORT_SLEW_RATE_CONTROL6 = 6U, /*!< Fmax=133 MHz(at 1.8V), 100 MHz (at 3.3V), apply for SIUL2_0/1
                                   */
    PORT_SLEW_RATE_CONTROL7 = 7U  /*!< Fmax=83 MHz (at 1.8V), 63 MHz (at 3.3V), apply for SIUL2_0/1
                                   */
} port_slew_rate_control_t;

/*!
 * @brief Configures the Receiver Select.
 * Implements : port_receiver_select_t_Class
 */
typedef enum {
    PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF = 0U, /*!< Enables the differential vref based receiver.
                                                  */
    PORT_RECEIVER_ENABLE_SINGLE_ENDED = 1U /*!< Enables the single ended receiver.            */
} port_receiver_select_t;

/* SIUL2 module feature */
/* SIUL2 module input mux numbers for main SIUL2 base */
#define FEATURE_SIUL2_INPUT_MUX_WIDTH            (8U)
/* SIUL2 module input mux numbers for interleave SIUL2 base */
#define FEATURE_SIUL2_INTERLEAVE_INPUT_MUX_WIDTH (4U)

/** SIUL2 - Size of Registers Arrays */
#define SIUL2_IFMCR_COUNT                        28u
#define SIUL2_MSCR_COUNT                         506u
#define SIUL2_IMCR_COUNT                         496u
#define SIUL2_GPDO_COUNT                         512u
#define SIUL2_GPDI_COUNT                         512u
#define SIUL2_PGPDO_COUNT                        32u
#define SIUL2_PGPDI_COUNT                        32u
#define SIUL2_MPGPDO_COUNT                       32u

#define SIUL2_1_MSCR_OBE_MASK                    (0x200000U)
#define SIUL2_1_MSCR_OBE_SHIFT                   (21U)
#define SIUL2_1_MSCR_OBE_WIDTH                   (1U)
#define SIUL2_1_MSCR_OBE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_OBE_SHIFT)) & SIUL2_1_MSCR_OBE_MASK)
#define SIUL2_1_MSCR_ODE_MASK  (0x100000U)
#define SIUL2_1_MSCR_ODE_SHIFT (20U)
#define SIUL2_1_MSCR_ODE_WIDTH (1U)
#define SIUL2_1_MSCR_ODE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_ODE_SHIFT)) & SIUL2_1_MSCR_ODE_MASK)
#define SIUL2_1_MSCR_SRE_MASK  (0x1C000U)
#define SIUL2_1_MSCR_SRE_SHIFT (14U)
#define SIUL2_1_MSCR_SRE_WIDTH (3U)
#define SIUL2_1_MSCR_SRE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_SRE_SHIFT)) & SIUL2_1_MSCR_SRE_MASK)
#define SIUL2_1_MSCR_IBE_MASK  (0x80000U)
#define SIUL2_1_MSCR_IBE_SHIFT (19U)
#define SIUL2_1_MSCR_IBE_WIDTH (1U)
#define SIUL2_1_MSCR_IBE(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_IBE_SHIFT)) & SIUL2_1_MSCR_IBE_MASK)
#define SIUL2_1_MSCR_SSS_MASK  (0x7U)
#define SIUL2_1_MSCR_SSS_SHIFT (0U)
#define SIUL2_1_MSCR_SSS_WIDTH (3U)
#define SIUL2_1_MSCR_SSS(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_SSS_SHIFT)) & SIUL2_1_MSCR_SSS_MASK)
#define SIUL2_1_MSCR_SMC_MASK  (0x20U)
#define SIUL2_1_MSCR_SMC_SHIFT (5U)
#define SIUL2_1_MSCR_SMC_WIDTH (1U)
#define SIUL2_1_MSCR_SMC(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_SMC_SHIFT)) & SIUL2_1_MSCR_SMC_MASK)
#define SIUL2_1_MSCR_RCVR_MASK  (0x400U)
#define SIUL2_1_MSCR_RCVR_SHIFT (10U)
#define SIUL2_1_MSCR_RCVR_WIDTH (1U)
#define SIUL2_1_MSCR_RCVR(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_1_MSCR_RCVR_SHIFT)) & SIUL2_1_MSCR_RCVR_MASK)
#define SIUL2_AE_IMCR_SSS_MASK  (0x7U)
#define SIUL2_AE_IMCR_SSS_SHIFT (0U)
#define SIUL2_AE_IMCR_SSS_WIDTH (3U)
#define SIUL2_AE_IMCR_SSS(x) \
    (((uint32_t)(((uint32_t)(x)) << SIUL2_AE_IMCR_SSS_SHIFT)) & SIUL2_AE_IMCR_SSS_MASK)

/** GPIO - Register Layout Typedef */
typedef struct {
    uint16_t PGPDO; /**< SIUL2 Parallel GPIO Pad Data Out Register, array offset: 0x1700, array
                       step: 0x2 */
    uint16_t RESERVED_1[SIUL2_PGPDO_COUNT - 1U];
    uint16_t PGPDI; /**< SIUL2 Parallel GPIO Pad Data In Register, array offset: 0x1740, array step:
                       0x2 */
} GPIO_Type;

/* SIUL2 - Peripheral instance base addresses */
/** Peripheral SIUL2_0 base address */
#define SIUL2_0_BASE     (0x40520000)
/** Peripheral SIUL2_0 base pointer */
#define SIUL2_0          ((SIUL2_Type*)SIUL2_0_BASE)
/** Peripheral SIUL2_1 base address */
#define SIUL2_1_BASE     (0x40d20000)
/** Peripheral SIUL2_1 base pointer */
#define SIUL2_1          ((SIUL2_Type*)SIUL2_1_BASE)

/** Peripheral SIUL2_5 base address */
#define SIUL2_5_BASE     (0x42D20000)
/** Peripheral SIUL2_5 base pointer */
#define SIUL2_5          ((SIUL2_Type*)SIUL2_5_BASE)

/** Peripheral SIUL2_AE base address */
#define SIUL2_AE_BASE    (0x55624000u)
/** Peripheral SIUL2_AE base pointer */
#define SIUL2_AE         ((SIUL2_Type*)SIUL2_AE_BASE)
/** Array initializer of SIUL2 peripheral base addresses */
#define SIUL2_BASE_ADDRS { SIUL2_0_BASE, SIUL2_1_BASE, SIUL2_AE_BASE }
/** Array initializer of SIUL2 peripheral base pointers */
#define SIUL2_BASE_PTRS  { SIUL2_0, SIUL2_1, SIUL2_AE }

/** SIUL2 - Register Layout Typedef */
typedef struct {
    uint8_t RESERVED_0[4];
    uint32_t MIDR1;  /**< SIUL2 MCU ID Register #1, offset: 0x4 */
    uint32_t MIDR2;  /**< SIUL2 MCU ID Register #2, offset: 0x8 */
    uint8_t RESERVED_1[4];
    uint32_t DISR0;  /**< SIUL2 DMA/Interrupt Status Flag Register0, offset: 0x10 */
    uint8_t RESERVED_2[4];
    uint32_t DIRER0; /**< SIUL2 DMA/Interrupt Request Enable Register0, offset: 0x18 */
    uint8_t RESERVED_3[4];
    uint32_t DIRSR0; /**< SIUL2 DMA/Interrupt Request Select Register0, offset: 0x20 */
    uint8_t RESERVED_4[4];
    uint32_t IREER0; /**< SIUL2 Interrupt Rising-Edge Event Enable Register 0, offset: 0x28 */
    uint8_t RESERVED_5[4];
    uint32_t IFEER0; /**< SIUL2 Interrupt Falling-Edge Event Enable Register 0, offset: 0x30 */
    uint8_t RESERVED_6[4];
    uint32_t IFER0;  /**< SIUL2 Interrupt Filter Enable Register 0, offset: 0x38 */
    uint8_t RESERVED_7[4];
    uint32_t IFMCR[SIUL2_IFMCR_COUNT]; /**< SIUL2 Interrupt Filter Maximum Counter Register, array
                                          offset: 0x40, array step: 0x4 */
                                       /**< SIUL2_0: IFMCR3/6-8/11-27 are reserved */
                                       /**< SIUL2_1: None reserved */
                                       /**< SIUL2_AE: IFMCR4-27 are reserved */
    uint8_t RESERVED_8[16];
    uint32_t IFCPR; /**< SIUL2 Interrupt Filter Clock Prescaler Register, offset: 0xC0 */
    uint8_t RESERVED_9[380];
    uint32_t MSCR[SIUL2_MSCR_COUNT]; /**< SIUL2 Multiplexed Signal Configuration Register, array
                                        offset: 0x240, array step: 0x4 */
                                     /**< SIUL2_0: MSCR102-505 are reserved */
    /**< SIUL2_1: MSCR0-112/117-120/123-143/145/158-159/178/185-191/207/212-239/252/256-499 are
     * reserved */
    /**< SIUL2_AE: MSCR4-7/44-255/324-505 are reserved */
    uint8_t RESERVED_10[24];
    uint32_t IMCR[SIUL2_IMCR_COUNT]; /**< SIUL2 Input Multiplexed Signal Configuration Register,
                                        array offset: 0xAC0, array step: 0x4 */
                                     /**< SIUL2_0: IMCR2/60-67/84-495 are reserved */
                                     /**< SIUL2_1:
                                        IMCR0-57/65-68/76-119/127-129/135-136/148/155/169-172/174/177/179-189/200-205/215/217/219/
                                          221/236-237/239-250/262/264/266/268/290/292/327-397/402-405/410-413/418-421/426-487 are
                                        reserved */
                                     /**< SIUL2_AE: IMCR59-255/288-495 are reserved */
    uint8_t RESERVED_11[256];
    uint8_t GPDO[SIUL2_GPDO_COUNT];  /**< SIUL2 GPIO Pad Data Output Register, array offset: 0x1300,
                                        array step: 0x1 */
                                     /**< SIUL2_0: GPDO100-101/104-511 are reserved */
    /**< SIUL2_1: GPDO0-112/117-120/123-143/145/158-159/178/185-191/207/212-239/252/256-499 are
     * reserved */
    /**< SIUL2_AE: GPDO4-7/44-255/324-505 are reserved */
    uint8_t GPDI[SIUL2_GPDI_COUNT]; /**< SIUL2 GPIO Pad Data Input Register, array offset: 0x1500,
                                       array step: 0x1 */
                                    /**< SIUL2_0: GPDI100-101/104-511 are reserved */
    /**< SIUL2_1: GPDI0-112/117-120/123-143/145/158-159/178/185-191/207/212-239/252/256-499 are
     * reserved */
    /**< SIUL2_AE: GPDI4-7/44-255/324-505 are reserved */
    uint16_t PGPDO[SIUL2_PGPDO_COUNT]; /**< SIUL2 Parallel GPIO Pad Data Out Register, array offset:
                                          0x1700, array step: 0x2 */
                                       /**< SIUL2_0: PGPDO6/8-31 are reserved */
                                       /**< SIUL2_1: PGPDO0-5/7/9/15-16/18-30 are reserved */
                                       /**< SIUL2_AE: PGPDO2/4-31 are reserved */
    uint16_t PGPDI[SIUL2_PGPDI_COUNT]; /**< SIUL2 Parallel GPIO Pad Data In Register, array offset:
                                          0x1740, array step: 0x2 */
                                       /**< SIUL2_0: PGPDI6/8-31 are reserved */
                                       /**< SIUL2_1: PGPDI0-5/7/9/15-16/18-30 are reserved */
                                       /**< SIUL2_AE: PGPDI2/4-31 are reserved */
    uint32_t MPGPDO[SIUL2_MPGPDO_COUNT]; /**< SIUL2 Masked Parallel GPIO Pad Data Out Register,
                                            array offset: 0x1780, array step: 0x4 */
                                         /**< SIUL2_0: MGPDO7-31 are reserved */
                                         /**< SIUL2_1: MGPDO0-6/8/14/17-31 are reserved */
                                         /**< SIUL2_AE: MGPDO3-31 are reserved */
} SIUL2_Type, *SIUL2_MemMapPtr;

/*!
 * @brief Defines the converter configuration
 *
 * This structure is used to configure the pins
 * Implements : pin_settings_config_t_Class
 */
typedef struct {
    SIUL2_Type* base;    /*!< The main SIUL2 base pointer.                               */
    uint32_t pinPortIdx; /*!< Port pin number.                                           */
    port_pull_config_t pullConfig; /*!< Internal resistor pull feature selection. */
    port_mux_t mux; /*!< Pin output muxing selection.                               */
    port_analog_pad_t analogPadCtrlSel; /*!< Configures the Analog Pad Control, apply for SIUL2_AE
                                         */
    port_safe_mode_t safeMode; /*!< Configures the Safe Mode Control, apply for SIUL2_0/1      */
    port_slew_rate_control_t slewRateCtrlSel; /*!< Configures the Slew Rate Control field. */
    port_receiver_select_t receiverSel; /*!< Configures the Receiver Select, apply for SIUL2_0/1 */
    // port_hysteresis_t           hysteresisSelect;  /*!< Configures the Hysteresis Enable, apply
    // for SIUL2_1/AE     */
    port_open_drain_t openDrain; /*!< Configures open drain, apply for SIUL2_0/1                 */
    port_output_buffer_t outputBuffer; /*!< Configures the Output Buffer Enable. */
    port_input_buffer_t inputBuffer;   /*!< Configures the Input Buffer Enable.   */
    port_input_mux_t inputMux[FEATURE_SIUL2_INPUT_MUX_WIDTH];
    /*!< Configures the input muxing for main SIUL2                 */
    uint32_t inputMuxReg[FEATURE_SIUL2_INPUT_MUX_WIDTH];
    /*!< Configures the input muxing register for main SIUL2        */
    SIUL2_Type* interleaveBase; /*!< The interleaved SIUL2 base pointer, NULL if not present
                                 *   when having 2 SIUL2 instances controlling on the given pin,
                                 *   interleaved SIUL2 is set to second SIUL2 base              */
    port_input_mux_t interleaveInputMux[FEATURE_SIUL2_INTERLEAVE_INPUT_MUX_WIDTH];
    /*!< Configures the input muxing for interleaved SIUL2          */
    uint32_t interleaveInputMuxReg[FEATURE_SIUL2_INTERLEAVE_INPUT_MUX_WIDTH];
    /*!< Configures the input muxing register for interleaved SIUL2 */
    siul2_interrupt_config_t intConfig; /*!< Interrupt generation condition. */
    GPIO_Type* gpioBase;         /*!< GPIO base pointer.                                         */
    pins_level_type_t initValue; /*!< Initial value                                              */
} pin_settings_config_t;

/** Public LinflexD UART interfaces */

void uart_disable(volatile struct LINFlexD_Type* ptr_uart);
void uart_enable(volatile struct LINFlexD_Type* ptr_uart);
void uart_set_baud_rate(volatile struct LINFlexD_Type* ptr_uart, uint32_t baud_rate);
void uart_init(volatile struct LINFlexD_Type* ptr_uart);
uint32_t uart_getc(volatile struct LINFlexD_Type* ptr_uart);
void uart_putc(volatile struct LINFlexD_Type* ptr_uart, int8_t c);
void uart_puts(volatile struct LINFlexD_Type* ptr_uart, const char* s);
void LINFLEXD_UART_DRV_SetBaudRate(volatile struct LINFlexD_Type* base, uint32_t baudrate);
void LINFLEXD_UART_DRV_SendData(volatile struct LINFlexD_Type* instance, const int8_t* txBuff);
void LINFLEXD_SetTxDataBuffer1Byte(volatile struct LINFlexD_Type* base, int8_t data);
void LINFLEXD_SetTransmitterState(volatile struct LINFlexD_Type* base, bool enable);
void LINFLEXD_SetInterruptMode(volatile struct LINFlexD_Type* base, uint32_t intSrc, bool enable);
void LINFLEXD_SetRxEnable(volatile struct LINFlexD_Type* base, uint32_t enable);
void LINFLEXD_SetRxMode(volatile struct LINFlexD_Type* base, linflexd_uart_rxtx_mode_t mode);
void LINFLEXD_SetTxMode(volatile struct LINFlexD_Type* base, linflexd_uart_rxtx_mode_t mode);
uint8_t LINFLEXD_GetRxDataBuffer1Byte(volatile struct LINFlexD_Type* base);
void LINFLEXD_SetParityControl(volatile struct LINFlexD_Type* base, bool enable);
void LINFLEXD_SetRxDataFieldLength(volatile struct LINFlexD_Type* base, uint8_t length);
void LINFLEXD_SetTxDataFieldLength(volatile struct LINFlexD_Type* base, uint8_t length);
void LINFLEXD_SetUartWordLength(volatile struct LINFlexD_Type* base,
    linflexd_uart_word_length_t length);

void PINS_Init(const pin_settings_config_t* config);
void PINS_WritePin(GPIO_Type* const base, pins_channel_type_t pin, pins_level_type_t value);

void clock_init(volatile struct LINFlexD_Type* base);

#endif /* __LINFLEXD_UART_H_ */
