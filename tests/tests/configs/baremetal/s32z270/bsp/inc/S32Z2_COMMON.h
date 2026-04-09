/*
 * Copyright 1997-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!
 * @file S32Z2.h
 * @version 2.3
 * @date 2024-05-03
 * @brief Peripheral Access Layer for S32Z2
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
 * The SoC header defines typedef for all modules.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
 * The SoC header defines macros for all modules and registers.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
 * These are generated macros used for accessing the bit-fields from registers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
 * This type qualifier is needed to ensure correct I/O access and addressing.
 */

/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(S32Z2_COMMON_H_) /* Check if memory map has not been already included */
#define S32Z2_COMMON_H_
#define MCU_S32Z2

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
#error S32Z2 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include "BasicTypes.h"

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION       0x0200U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0003U

/* ----------------------------------------------------------------------------
   -- Generic macros
   ---------------------------------------------------------------------------- */

/* IO definitions (access restrictions to peripheral registers) */
/**
 *   IO Type Qualifiers are used
 *   \li to specify the access to peripheral variables.
 *   \li for automatic generation of peripheral register debug information.
 */
#ifndef __IO
#ifdef __cplusplus
#define __I volatile       /*!< Defines 'read only' permissions                 */
#else
#define __I volatile const /*!< Defines 'read only' permissions                 */
#endif
#define __O  volatile      /*!< Defines 'write only' permissions                */
#define __IO volatile      /*!< Defines 'read / write' permissions              */
#endif

/**
 * @brief 32 bits memory read macro.
 */
#if !defined(REG_READ32)
#define REG_READ32(address) (*(volatile uint32_t*)(address))
#endif

/**
 * @brief 32 bits memory write macro.
 */
#if !defined(REG_WRITE32)
#define REG_WRITE32(address, value) ((*(volatile uint32_t*)(address)) = (uint32_t)(value))
#endif

/**
 * @brief 32 bits bits setting macro.
 */
#if !defined(REG_BIT_SET32)
#define REG_BIT_SET32(address, mask) ((*(volatile uint32_t*)(address)) |= (uint32_t)(mask))
#endif

/**
 * @brief 32 bits bits clearing macro.
 */
#if !defined(REG_BIT_CLEAR32)
#define REG_BIT_CLEAR32(address, mask) \
    ((*(volatile uint32_t*)(address)) &= ((uint32_t) ~((uint32_t)(mask))))
#endif

/**
 * @brief 32 bit clear bits and set with new value
 * @note It is user's responsability to make sure that value has only "mask" bits set -
 * (value&~mask)==0
 */
#if !defined(REG_RMW32)
#define REG_RMW32(address, mask, value) \
    (REG_WRITE32((address),             \
        ((REG_READ32(address) & ((uint32_t) ~((uint32_t)(mask)))) | ((uint32_t)(value)))))
#endif

/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define SMU_NUMBER_OF_INT_VECTORS 496 /**< Number of interrupts in the Vector table */

typedef enum {
    /* Auxiliary constants */
    SMU_NotAvail_IRQn = -128, /**< Not available device specific interrupt */

    /* Core interrupts */
    SMU_NonMaskableInt_IRQn = -14,   /**< Non Maskable Interrupt */
    SMU_HardFault_IRQn = -13,        /**< Cortex-M33 SV Hard Fault Interrupt */
    SMU_MemoryManagement_IRQn = -12, /**< Cortex-M33 Memory Management Interrupt */
    SMU_BusFault_IRQn = -11,         /**< Cortex-M33 Bus Fault Interrupt */
    SMU_UsageFault_IRQn = -10,       /**< Cortex-M33 Usage Fault Interrupt */
    SMU_SecureFault_IRQn = -9,       /**< Cortex-M33 Secure Fault Interrupt */
    SMU_SVCall_IRQn = -5,            /**< Cortex-M33 SV Call Interrupt */
    SMU_DebugMonitor_IRQn = -4,      /**< Cortex-M33 Debug Monitor Interrupt */
    SMU_PendSV_IRQn = -2,            /**< Cortex-M33 Pend SV Interrupt */
    SMU_SysTick_IRQn = -1,           /**< Cortex-M33 System Tick Interrupt */

    /* Device specific interrupts */
    SMU_SWT0_IRQn = 0,                  /**< Watchdog timer interrupt */
    SMU_STM0_IRQn = 1,                  /**< Single vector for all 4 channels */
    SMU_CTI_0_IRQn = 2,                 /**< CTI interrupt[0] */
    SMU_CTI_1_IRQn = 3,                 /**< CTI interrupt[1] */
    SMU_MCM_IRQn = 4,                   /**< Cortex M33 interrupt for FPU events and TCM errors */
    SMU_CMU_FC_EIC_IRQn = 20,           /**< Error Injection Complete */
    SMU_CE_CMU_FC_IRQn = 21,            /**< Fault Injection Complete */
    SMU_STM2_IRQn = 22,                 /**< Single vector for all 4 channels */
    SMU_ERM2_SBEC_IRQn = 24,            /**< Single bit ECC error */
    SMU_ERM2_MBEC_IRQn = 25,            /**< Multi bit ECC error */
    SMU_ERM1_SBEC_IRQn = 28,            /**< Single bit ECC error */
    SMU_ERM1_MBEC_IRQn = 29,            /**< Multi bit ECC error */
    SMU_XRDC_IRQn = 31,                 /**< xRDC.TBD Error Interrupt */
    SMU_MRU_INT0_IRQn = 36,             /**< MRQ's IRQ0 */
    SMU_MRU_INT1_IRQn = 37,             /**< MRQ's IRQ0 */
    SMU_SBSW_tmwdp_IRQn = 38,           /**< tmwdp ena irq */
    SMU_SBSW_timer_IRQn = 39,           /**< timer irq */
    SMU_C_VFCCU_CFRI0_IRQn = 40,        /**< Central FCCU reaction index0 */
    SMU_C_VFCCU_CFRI1_IRQn = 41,        /**< Central FCCU reaction index1 */
    SMU_DMA0_ERR_IRQn = 48,             /**< DMA Error interrupt request */
    SMU_DMA0_0_15_IRQn = 49,            /**< Interrupt for DMA CH0-15 */
    SMU_DMA0_16_31_IRQn = 50,           /**< Interrupt for DMA CH16-31,DMA0_CH0_31_INT */
    SMU_DMA1_ERR_IRQn = 51,             /**< DMA Error interrupt request */
    SMU_DMA1_0_15_IRQn = 52,            /**< Interrupt for DMA CH0-15, DMA1_CH0_15_INT */
    SMU_DMA4_ERR_IRQn = 53,             /**< DMA Error interrupt request */
    SMU_DMA4_0_15_IRQn = 54,            /**< Interrupt for DMA CH0-15, DMA4_CH0_15_INT */
    SMU_DMA5_ERR_IRQn = 55,             /**< DMA Error interrupt request */
    SMU_DMA5_0_15_IRQn = 56,            /**< Interrupt for DMA CH0-15, DMA5_CH0_15_INT */
    SMU_DMA3_ERR_IRQn = 57,             /**< DMA Error interrupt request */
    SMU_DMA3_0_15_IRQn = 58,            /**< Interrupt for DMA CH0-15 */
    SMU_DMA3_16_31_IRQn = 59,           /**< Interrupt for DMA CH16-31, DMA3_CH0_31_INT */
    SMU_QuadSPI0_Ored_IRQn = 60,        /**< All interrupts ORed output */
    SMU_QuadSPI0_FLASH_A_ERR_IRQn = 61, /**< Flash A Error interrupt */
    SMU_QuadSPI1_Ored_IRQn = 62,        /**< All interrupts ORed output */
    SMU_QuadSPI1_FLASH_A_ERR_IRQn = 63, /**< Flash A Error interrupt */
    SMU_QuadSPI1_FLASH_B_ERR_IRQn = 64, /**< Flash B Error interrupt */
    SMU_CSTCU_IRQn = 65,                /**< SLFTEST_END_INT */
    SMU_USDHC_IRQn = 66,                /**< uSDHC Interrupt */
    SMU_PIT0_IRQn = 67,                 /**< Ored all Interrupt Channels */
    SMU_PIT1_IRQn = 68,                 /**< Ored all Interrupt Channels */
    SMU_PIT4_IRQn = 69,                 /**< Ored all Interrupt Channels */
    SMU_PIT5_IRQn = 70,                 /**< Ored all Interrupt Channels */
    SMU_NETC_IRQn = 72,                 /**< NETC Interrupt */
    SMU_ADC0_EOC_IRQn = 76,             /**< End of conv. Interrupt */
    SMU_ADC0_ERR_IRQn = 77,             /**< Error interrupt */
    SMU_ADC0_WDT_IRQn = 78,             /**< Analog watchdog interrupt */
    SMU_FR0_NCERR_IRQn = 79,            /**< LRAM and DRAM Non-Corrected Error interrupt */
    SMU_FR0_CERR_IRQn = 80,             /**< LRAM and DRAM Corrected Error interrupt */
    SMU_FR0_FIFO_CHA_IRQn = 81,         /**< Receive FIFO channel A not empty interrupt */
    SMU_FR0_FIFO_CHB_IRQn = 82,         /**< Receive FIFO channel B not empty interrupt */
    SMU_FR0_WKUP_IRQn = 83,             /**< Wakeup interrupt */
    SMU_FR0_STATUS_IRQn = 84,           /**< Combined protocol status and error interrupt */
    SMU_FR0_CMBERR_IRQn = 85,           /**< Combined CHI error interrupt */
    SMU_FR0_TX_BUFF_IRQn = 86,          /**< Combined transmit message buffer interrupt */
    SMU_FR0_RX_BUFF_IRQn = 87,          /**< Combined receive message buffer interrupt */
    SMU_FR0_MODULE_IRQn = 88,           /**< Combined module interrupt */
    SMU_FR1_NCERR_IRQn = 89,            /**< LRAM and DRAM Non-Corrected Error interrupt */
    SMU_FR1_CERR_IRQn = 90,             /**< LRAM and DRAM Corrected Error interrupt */
    SMU_FR1_FIFO_CHA_IRQn = 91,         /**< Receive FIFO channel A not empty interrupt */
    SMU_FR1_FIFO_CHB_IRQn = 92,         /**< Receive FIFO channel B not empty interrupt */
    SMU_FR1_WKUP_IRQn = 93,             /**< Wakeup interrupt */
    SMU_FR1_STATUS_IRQn = 94,           /**< Combined protocol status and error interrupt */
    SMU_FR1_CMBERR_IRQn = 95,           /**< Combined CHI error interrupt */
    SMU_FR1_TX_BUFF_IRQn = 96,          /**< Combined transmit message buffer interrupt */
    SMU_FR1_RX_BUFF_IRQn = 97,          /**< Combined receive message buffer interrupt */
    SMU_FR1_MODULE_IRQn = 98,           /**< Combined module interrupt */
    SMU_DSPI0_IRQn = 99,                /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI1_IRQn = 100,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI2_IRQn = 101,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI3_IRQn = 102,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI4_IRQn = 103,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI5_IRQn = 104,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI6_IRQn = 105,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI7_IRQn = 106,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI8_IRQn = 107,               /**< OR'ed DSPI Global Interrupt */
    SMU_DSPI9_IRQn = 108,               /**< OR'ed DSPI Global Interrupt */
    SMU_ADC1_EOC_IRQn = 109,            /**< End of conv. Interrupt */
    SMU_ADC1_ERR_IRQn = 110,            /**< Error interrupt */
    SMU_ADC1_WDT_IRQn = 111,            /**< Analog watchdog interrupt */
    SMU_MSC0_DSPI_IRQn = 112,           /**< DSPI Global Interrupt (OR of all interrupt lines) */
    SMU_MSC0_LIN_IRQn = 113,   /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LCU0_CELL2_IRQn = 114, /**< Logic Cell 2 Interrupt, Logic Cell 0 Interrupt, Logic Cell 1
                                  Interrupt */
    SMU_LCU1_CELL2_IRQn = 115, /**< Logic Cell 2 Interrupt */
    SMU_LINFLEXD0_IRQn = 116,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD1_IRQn = 117,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD2_IRQn = 118,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD3_IRQn = 119,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD4_IRQn = 120,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD5_IRQn = 121,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD6_IRQn = 122,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD7_IRQn = 123,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD8_IRQn = 124,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD9_IRQn = 125,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD10_IRQn = 126, /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    SMU_LINFLEXD11_IRQn = 127, /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request,  */
    SMU_CANXL0_INT_RX_TX_DATA_IRQn = 128, /**< CANXL: CAN frame data */
    SMU_CANXL0_INT_ERR_IRQn = 129,        /**< CANXL: error occurred in CANXL */
    SMU_CANXL1_INT_RX_TX_DATA_IRQn = 130, /**< 'CANXL: CAN frame data */
    SMU_CANXL1_INT_ERR_IRQn = 131,        /**< CANXL: error occurred in CANXL */
    SMU_I3C0_IRQn = 132,                  /**< Interrupt Request */
    SMU_LPI2C1_IRQn = 133,                /**< Interrupt Request */
    SMU_LPI2C2_IRQn = 134,                /**< Interrupt Request */
    SMU_MC_RGM_IRQn = 135,                /**< Interrupt Request to System */
    SMU_HSE_MU0_TX_IRQn = 136,            /**< Ored tx interrupt to MU-0 */
    SMU_HSE_MU0_RX_IRQn = 137,            /**< Ored rx interrupt to MU-0 */
    SMU_HSE_MU0_ORED_IRQn = 138,          /**< ORed general purpose interrupt request to MU-0 */
    SMU_HSE_MU1_TX_IRQn = 139,            /**< Ored tx interrupt to MU-1 */
    SMU_HSE_MU1_RX_IRQn = 140,            /**< Ored rx interrupt to MU-1 */
    SMU_HSE_MU1_ORED_IRQn = 141,          /**< ORed general purpose interrupt request to MU-1 */
    SMU_DDR_SCRUB_IRQn = 142, /**< Scrubber interrupt indicating one full address range sweep */
    SMU_DDR_PHY_IRQn = 143,   /**< PHY address decoding error inside DDR SS */
    SMU_DDR_PM_IRQn = 144,    /**< Performance Monitoring Interrupt */
    SMU_TMU_IRQn = 145, /**< Level sensitive temperature alarm interrupt | Level sensitive citical
                           temperature alarm interrupt */
    SMU_EMIOS0_OVRFL_IRQn = 146,  /**< Overflow interrupt */
    SMU_EMIOS0_CH0_IRQn = 147,    /**< Interrupt request channel 0 */
    SMU_EMIOS0_CH1_IRQn = 148,    /**< Interrupt request channel 1 */
    SMU_EMIOS0_CH2_IRQn = 149,    /**< Interrupt request channel 2 */
    SMU_EMIOS0_CH3_IRQn = 150,    /**< Interrupt request channel 3 */
    SMU_EMIOS0_CH4_IRQn = 151,    /**< Interrupt request channel 4 */
    SMU_EMIOS0_CH5_IRQn = 152,    /**< Interrupt request channel 5 */
    SMU_EMIOS0_CH6_IRQn = 153,    /**< Interrupt request channel 6 */
    SMU_EMIOS0_CH7_IRQn = 154,    /**< Interrupt request channel 7 */
    SMU_EMIOS0_CH8_IRQn = 155,    /**< Interrupt request channel 8 */
    SMU_EMIOS0_CH10_IRQn = 156,   /**< Interrupt request channel 10 */
    SMU_EMIOS0_CH12_IRQn = 157,   /**< Interrupt request channel 12 */
    SMU_EMIOS0_CH14_IRQn = 158,   /**< Interrupt request channel 14 */
    SMU_EMIOS0_CH16_IRQn = 159,   /**< Interrupt request channel 16 */
    SMU_EMIOS0_CH17_IRQn = 160,   /**< Interrupt request channel 17 */
    SMU_EMIOS0_CH18_IRQn = 161,   /**< Interrupt request channel 18 */
    SMU_EMIOS0_CH19_IRQn = 162,   /**< Interrupt request channel 19 */
    SMU_EMIOS0_CH20_IRQn = 163,   /**< Interrupt request channel 20 */
    SMU_EMIOS0_CH21_IRQn = 164,   /**< Interrupt request channel 21 */
    SMU_EMIOS0_CH22_IRQn = 165,   /**< Interrupt request channel 22 */
    SMU_EMIOS0_CH23_IRQn = 166,   /**< Interrupt request channel 23 */
    SMU_EMIOS0_CH24_IRQn = 167,   /**< Interrupt request channel 24 */
    SMU_EMIOS0_CH25_IRQn = 168,   /**< Interrupt request channel 25 */
    SMU_EMIOS0_CH26_IRQn = 169,   /**< Interrupt request channel 26 */
    SMU_EMIOS0_CH27_IRQn = 170,   /**< Interrupt request channel 27 */
    SMU_EMIOS0_CH28_IRQn = 171,   /**< Interrupt request channel 28 */
    SMU_EMIOS0_CH29_IRQn = 172,   /**< Interrupt request channel 29 */
    SMU_EMIOS0_CH30_IRQn = 173,   /**< Interrupt request channel 30 */
    SMU_EMIOS0_CH31_IRQn = 174,   /**< Interrupt request channel 31 */
    SMU_EMIOS1_OVRFL_IRQn = 175,  /**< Overflow interrupt */
    SMU_EMIOS1_CH0_IRQn = 176,    /**< Interrupt request channel 0 */
    SMU_EMIOS1_CH1_IRQn = 177,    /**< Interrupt request channel 1 */
    SMU_EMIOS1_CH2_IRQn = 178,    /**< Interrupt request channel 2 */
    SMU_EMIOS1_CH3_IRQn = 179,    /**< Interrupt request channel 3 */
    SMU_EMIOS1_CH4_IRQn = 180,    /**< Interrupt request channel 4 */
    SMU_EMIOS1_CH5_IRQn = 181,    /**< Interrupt request channel 5 */
    SMU_EMIOS1_CH6_IRQn = 182,    /**< Interrupt request channel 6 */
    SMU_EMIOS1_CH7_IRQn = 183,    /**< Interrupt request channel 7 */
    SMU_EMIOS1_CH8_IRQn = 184,    /**< Interrupt request channel 8 */
    SMU_EMIOS1_CH10_IRQn = 185,   /**< Interrupt request channel 10 */
    SMU_EMIOS1_CH12_IRQn = 186,   /**< Interrupt request channel 12 */
    SMU_EMIOS1_CH14_IRQn = 187,   /**< Interrupt request channel 14 */
    SMU_EMIOS1_CH16_IRQn = 188,   /**< Interrupt request channel 16 */
    SMU_EMIOS1_CH17_IRQn = 189,   /**< Interrupt request channel 17 */
    SMU_EMIOS1_CH18_IRQn = 190,   /**< Interrupt request channel 18 */
    SMU_EMIOS1_CH19_IRQn = 191,   /**< Interrupt request channel 19 */
    SMU_EMIOS1_CH20_IRQn = 192,   /**< Interrupt request channel 20 */
    SMU_EMIOS1_CH21_IRQn = 193,   /**< Interrupt request channel 21 */
    SMU_EMIOS1_CH22_IRQn = 194,   /**< Interrupt request channel 22 */
    SMU_EMIOS1_CH23_IRQn = 195,   /**< Interrupt request channel 23 */
    SMU_EMIOS1_CH24_IRQn = 196,   /**< Interrupt request channel 24 */
    SMU_EMIOS1_CH25_IRQn = 197,   /**< Interrupt request channel 25 */
    SMU_EMIOS1_CH26_IRQn = 198,   /**< Interrupt request channel 26 */
    SMU_EMIOS1_CH27_IRQn = 199,   /**< Interrupt request channel 27 */
    SMU_EMIOS1_CH28_IRQn = 200,   /**< Interrupt request channel 28 */
    SMU_EMIOS1_CH29_IRQn = 201,   /**< Interrupt request channel 29 */
    SMU_EMIOS1_CH30_IRQn = 202,   /**< Interrupt request channel 30 */
    SMU_EMIOS1_CH31_IRQn = 203,   /**< Interrupt request channel 31 */
    SMU_PSI50_CH0_DMA_IRQn = 204, /**< PSI5 channel 0 DMA combined interrupt- DMA transfer to SMC
                                     frame register complete, DMAtransfer complete, FIFO full, SMC
                                     frame, DMA undeflow, Data underflow */
    SMU_PSI50_CH0_GEN_INT_IRQn = 205,   /**< PSI5 channel 0 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI50_CH0_NEW_MSG_IRQn = 206,   /**< PSI5 channel 0 new message received */
    SMU_PSI50_CH0_MSG_OVRWR_IRQn = 207, /**< PSI5 channel 0 message overwrite */
    SMU_PSI50_CH0_ERR_IRQn = 208,       /**< PSI5 channel 0 error */
    SMU_PSI50_CH0_COMB_IRQn = 209, /**< PSI5 channel 0 combined interrupt- All PSI5 interrupts */
    SMU_PSI50_CH1_DMA_IRQn = 210,  /**< PSI5 channel 1 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI50_CH1_GEN_INT_IRQn = 211,   /**< PSI5 channel 1 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI50_CH1_NEW_MSG_IRQn = 212,   /**< PSI5 channel 1 new message received */
    SMU_PSI50_CH1_MSG_OVRWR_IRQn = 213, /**< PSI5 channel 1 message overwrite */
    SMU_PSI50_CH1_ERR_IRQn = 214,       /**< PSI5 channel 1 error */
    SMU_PSI50_CH1_COMB_IRQn = 215, /**< PSI5 channel 1 combined interrupt- All PSI5 interrupts */
    SMU_PSI50_CH2_DMA_IRQn = 216,  /**< PSI5 channel 2 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI50_CH2_GEN_INT_IRQn = 217,   /**< PSI5 channel 2 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI50_CH2_NEW_MSG_IRQn = 218,   /**< PSI5 channel 2 new message received */
    SMU_PSI50_CH2_MSG_OVRWR_IRQn = 219, /**< PSI5 channel 2 message overwrite */
    SMU_PSI50_CH2_ERR_IRQn = 220,       /**< PSI5 channel 2 error */
    SMU_PSI50_CH2_COMB_IRQn = 221, /**< PSI5 channel 2 combined interrupt- All PSI5 interrupts */
    SMU_PSI50_CH3_DMA_IRQn = 222,  /**< PSI5 channel 3 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI50_CH3_GEN_INT_IRQn = 223,   /**< PSI5 channel 3 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI50_CH3_NEW_MSG_IRQn = 224,   /**< PSI5 channel 3 new message received */
    SMU_PSI50_CH3_MSG_OVRWR_IRQn = 225, /**< PSI5 channel 3 message overwrite */
    SMU_PSI50_CH3_ERR_IRQn = 226,       /**< PSI5 channel 3 error */
    SMU_PSI50_CH3_COMB_IRQn = 227, /**< PSI5 channel 3 combined interrupt- All PSI5 interrupts */
    SMU_PSI51_CH0_DMA_IRQn = 228,  /**< PSI5 channel 0 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI51_CH0_GEN_INT_IRQn = 229,   /**< PSI5 channel 0 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI51_CH0_NEW_MSG_IRQn = 230,   /**< PSI5 channel 0 new message received */
    SMU_PSI51_CH0_MSG_OVRWR_IRQn = 231, /**< PSI5 channel 0 message overwrite */
    SMU_PSI51_CH0_ERR_IRQn = 232,       /**< PSI5 channel 0 error */
    SMU_PSI51_CH0_COMB_IRQn = 233, /**< PSI5 channel 0 combined interrupt- All PSI5 interrupts */
    SMU_PSI51_CH1_DMA_IRQn = 234,  /**< PSI5 channel 1 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI51_CH1_GEN_INT_IRQn = 235,   /**< PSI5 channel 1 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI51_CH1_NEW_MSG_IRQn = 236,   /**< PSI5 channel 1 new message received */
    SMU_PSI51_CH1_MSG_OVRWR_IRQn = 237, /**< PSI5 channel 1 message overwrite */
    SMU_PSI51_CH1_ERR_IRQn = 238,       /**< PSI5 channel 1 error */
    SMU_PSI51_CH1_COMB_IRQn = 239, /**< PSI5 channel 1 combined interrupt- All PSI5 interrupts */
    SMU_PSI51_CH2_DMA_IRQn = 240,  /**< PSI5 channel 2 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI51_CH2_GEN_INT_IRQn = 241,   /**< PSI5 channel 2 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI51_CH2_NEW_MSG_IRQn = 242,   /**< PSI5 channel 2 new message received */
    SMU_PSI51_CH2_MSG_OVRWR_IRQn = 243, /**< PSI5 channel 2 message overwrite */
    SMU_PSI51_CH2_ERR_IRQn = 244,       /**< PSI5 channel 2 error */
    SMU_PSI51_CH2_COMB_IRQn = 245, /**< PSI5 channel 2 combined interrupt- All PSI5 interrupts */
    SMU_PSI51_CH3_DMA_IRQn = 246,  /**< PSI5 channel 3 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    SMU_PSI51_CH3_GEN_INT_IRQn = 247,   /**< PSI5 channel 3 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    SMU_PSI51_CH3_NEW_MSG_IRQn = 248,   /**< PSI5 channel 3 new message received */
    SMU_PSI51_CH3_MSG_OVRWR_IRQn = 249, /**< PSI5 channel 3 message overwrite */
    SMU_PSI51_CH3_ERR_IRQn = 250,       /**< PSI5 channel 3 error */
    SMU_PSI51_CH3_COMB_IRQn = 251,   /**< PSI5 channel 3 combined interrupt- All PSI5 interrupts */
    SMU_PSI5_S0_SR0_IRQn = 252,      /**< PS_SR_IRQ[0] */
    SMU_PSI5_S0_SR1_IRQn = 253,      /**< PS_SR_IRQ[1] */
    SMU_PSI5_S0_SR2_IRQn = 254,      /**< PS_SR_IRQ[2] */
    SMU_PSI5_S0_SR3_IRQn = 255,      /**< PS_SR_IRQ[3] */
    SMU_PSI5_S0_SR4_IRQn = 256,      /**< PS_SR_IRQ[4] */
    SMU_PSI5_S0_SR5_IRQn = 257,      /**< PS_SR_IRQ[5] */
    SMU_PSI5_S0_SR6_IRQn = 258,      /**< PS_SR_IRQ[6] */
    SMU_PSI5_S0_SR7_IRQn = 259,      /**< PS_SR_IRQ[7] */
    SMU_PSI5_S0_E2SSR1_IRQn = 260,   /**< PSI5_E2SSR[1] */
    SMU_PSI5_S0_E2SSR2_IRQn = 261,   /**< PSI5_E2SSR[2] */
    SMU_PSI5_S0_E2SSR3_IRQn = 262,   /**< PSI5_E2SSR[3] */
    SMU_PSI5_S0_E2SSR4_IRQn = 263,   /**< PSI5_E2SSR[4] */
    SMU_PSI5_S0_E2SSR5_IRQn = 264,   /**< PSI5_E2SSR[5] */
    SMU_PSI5_S0_E2SSR6_IRQn = 265,   /**< PSI5_E2SSR[6] */
    SMU_PSI5_S0_E2SSR7_IRQn = 266,   /**< PSI5_E2SSR[7] */
    SMU_PSI5_S0_GISR_IRQn = 267,     /**< PS_GLSR */
    SMU_PSI5_S0_UART_RX_IRQn = 268,  /**< PSI5_S_0_UART_RX */
    SMU_PSI5_S0_UART_TX_IRQn = 269,  /**< PSI5_S_0_UART_TX */
    SMU_PSI5_S0_UART_ERR_IRQn = 270, /**< PSI5_S_0_UART_ERR */
    SMU_PSI5_S1_SR0_IRQn = 271,      /**< PS_SR_IRQ[0] */
    SMU_PSI5_S1_SR1_IRQn = 272,      /**< PS_SR_IRQ[1] */
    SMU_PSI5_S1_SR2_IRQn = 273,      /**< PS_SR_IRQ[2] */
    SMU_PSI5_S1_SR3_IRQn = 274,      /**< PS_SR_IRQ[3] */
    SMU_PSI5_S1_SR4_IRQn = 275,      /**< PS_SR_IRQ[4] */
    SMU_PSI5_S1_SR5_IRQn = 276,      /**< PS_SR_IRQ[5] */
    SMU_PSI5_S1_SR6_IRQn = 277,      /**< PS_SR_IRQ[6] */
    SMU_PSI5_S1_SR7_IRQn = 278,      /**< PS_SR_IRQ[7] */
    SMU_PSI5_S1_E2SSR1_IRQn = 279,   /**< PSI5_E2SSR[1] */
    SMU_PSI5_S1_E2SSR2_IRQn = 280,   /**< PSI5_E2SSR[2] */
    SMU_PSI5_S1_E2SSR3_IRQn = 281,   /**< PSI5_E2SSR[3] */
    SMU_PSI5_S1_E2SSR4_IRQn = 282,   /**< PSI5_E2SSR[4] */
    SMU_PSI5_S1_E2SSR5_IRQn = 283,   /**< PSI5_E2SSR[5] */
    SMU_PSI5_S1_E2SSR6_IRQn = 284,   /**< PSI5_E2SSR[6] */
    SMU_PSI5_S1_E2SSR7_IRQn = 285,   /**< PSI5_E2SSR[7] */
    SMU_PSI5_S1_GISR_IRQn = 286,     /**< PS_GLSR */
    SMU_PSI5_S1_UART_RX_IRQn = 287,  /**< PSI5_S_0_UART_RX */
    SMU_PSI5_S1_UART_TX_IRQn = 288,  /**< PSI5_S_0_UART_TX */
    SMU_PSI5_S1_UART_ERR_IRQn = 289, /**< PSI5_S_0_UART_ERR */
    SMU_SRX0_COMBINED_FAST_0_IRQn = 290,  /**< SENT_COMBINED_FAST_0 */
    SMU_SRX0_COMBINED_SLOW_0_IRQn = 291,  /**< SENT_COMBINED_SLOW_0 */
    SMU_SRX0_COMBINED_ERR_0_IRQn = 292,   /**< SENT_COMBINED_ERR_0 */
    SMU_SRX0_CH0_FAST_IRQn = 293,         /**< SENT_CH0_FAST */
    SMU_SRX0_CH0_SLOW_IRQn = 294,         /**< SENT_CH0_SLOW */
    SMU_SRX0_CH0_CH0_ERR_IRQn = 295,      /**< SENT_CH0_ERR */
    SMU_SRX0_CH1_FAST_IRQn = 296,         /**< SENT_CH1_FAST */
    SMU_SRX0_CH1_SLOW_IRQn = 297,         /**< SENT_CH1_SLOW */
    SMU_SRX0_CH1_CH0_ERR_IRQn = 298,      /**< SENT_CH1_ERR */
    SMU_SRX0_CH2_FAST_IRQn = 299,         /**< SENT_CH2_FAST */
    SMU_SRX0_CH2_SLOW_IRQn = 300,         /**< SENT_CH2_SLOW */
    SMU_SRX0_CH2_CH0_ERR_IRQn = 301,      /**< SENT_CH2_ERR */
    SMU_SRX0_CH3_FAST_IRQn = 302,         /**< SENT_CH3_FAST */
    SMU_SRX0_CH3_SLOW_IRQn = 303,         /**< SENT_CH3_SLOW */
    SMU_SRX0_CH3_CH0_ERR_IRQn = 304,      /**< SENT_CH3_ERR */
    SMU_SRX0_CH4_FAST_IRQn = 305,         /**< SENT_CH4_FAST */
    SMU_SRX0_CH4_SLOW_IRQn = 306,         /**< SENT_CH4_SLOW */
    SMU_SRX0_CH4_CH0_ERR_IRQn = 307,      /**< SENT_CH4_ERR */
    SMU_SRX0_CH5_FAST_IRQn = 308,         /**< SENT_CH5_FAST */
    SMU_SRX0_CH5_SLOW_IRQn = 309,         /**< SENT_CH5_SLOW */
    SMU_SRX0_CH5_CH0_ERR_IRQn = 310,      /**< SENT_CH5_ERR */
    SMU_SRX0_CH6_FAST_IRQn = 311,         /**< SENT_CH6_FAST */
    SMU_SRX0_CH6_SLOW_IRQn = 312,         /**< SENT_CH6_SLOW */
    SMU_SRX0_CH6_CH0_ERR_IRQn = 313,      /**< SENT_CH6_ERR */
    SMU_SRX0_CH7_FAST_IRQn = 314,         /**< SENT_CH7_FAST */
    SMU_SRX0_CH7_SLOW_IRQn = 315,         /**< SENT_CH7_SLOW */
    SMU_SRX0_CH7_CH0_ERR_IRQn = 316,      /**< SENT_CH7_ERR */
    SMU_SRX1_COMBINED_FAST_0_IRQn = 317,  /**< SENT_COMBINED_FAST_0 */
    SMU_SRX1_COMBINED_SLOW_0_IRQn = 318,  /**< SENT_COMBINED_SLOW_0 */
    SMU_SRX1_COMBINED_ERR_0_IRQn = 319,   /**< SENT_COMBINED_ERR_0 */
    SMU_SRX1_CH0_FAST_IRQn = 320,         /**< SENT_CH0_FAST */
    SMU_SRX1_CH0_SLOW_IRQn = 321,         /**< SENT_CH0_SLOW */
    SMU_SRX1_CH0_CH0_ERR_IRQn = 322,      /**< SENT_CH0_ERR */
    SMU_SRX1_CH1_FAST_IRQn = 323,         /**< SENT_CH1_FAST */
    SMU_SRX1_CH1_SLOW_IRQn = 324,         /**< SENT_CH1_SLOW */
    SMU_SRX1_CH1_CH0_ERR_IRQn = 325,      /**< SENT_CH1_ERR */
    SMU_SRX1_CH2_FAST_IRQn = 326,         /**< SENT_CH2_FAST */
    SMU_SRX1_CH2_SLOW_IRQn = 327,         /**< SENT_CH2_SLOW */
    SMU_SRX1_CH2_CH0_ERR_IRQn = 328,      /**< SENT_CH2_ERR */
    SMU_SRX1_CH3_FAST_IRQn = 329,         /**< SENT_CH3_FAST */
    SMU_SRX1_CH3_SLOW_IRQn = 330,         /**< SENT_CH3_SLOW */
    SMU_SRX1_CH3_CH0_ERR_IRQn = 331,      /**< SENT_CH3_ERR */
    SMU_SRX1_CH4_FAST_IRQn = 332,         /**< SENT_CH4_FAST */
    SMU_SRX1_CH4_SLOW_IRQn = 333,         /**< SENT_CH4_SLOW */
    SMU_SRX1_CH4_CH0_ERR_IRQn = 334,      /**< SENT_CH4_ERR */
    SMU_SRX1_CH5_FAST_IRQn = 335,         /**< SENT_CH5_FAST */
    SMU_SRX1_CH5_SLOW_IRQn = 336,         /**< SENT_CH5_SLOW */
    SMU_SRX1_CH5_CH0_ERR_IRQn = 337,      /**< SENT_CH5_ERR */
    SMU_SRX1_CH6_FAST_IRQn = 338,         /**< SENT_CH6_FAST */
    SMU_SRX1_CH6_SLOW_IRQn = 339,         /**< SENT_CH6_SLOW */
    SMU_SRX1_CH6_CH0_ERR_IRQn = 340,      /**< SENT_CH6_ERR */
    SMU_SRX1_CH7_FAST_IRQn = 341,         /**< SENT_CH7_FAST */
    SMU_SRX1_CH7_SLOW_IRQn = 342,         /**< SENT_CH7_SLOW */
    SMU_SRX1_CH7_CH0_ERR_IRQn = 343,      /**< SENT_CH7_ERR */
    SMU_SIUL2_0_IRQn = 376,               /**< Logical OR of all pin interrupts */
    SMU_SIUL2_1_IRQn = 377,               /**< Logical OR of all pin interrupts */
    SMU_SIUL2_4_IRQn = 378,               /**< Logical OR of all pin interrupts */
    SMU_SIUL2_5_IRQn = 379,               /**< Logical OR of all pin interrupts */
    SMU_CE_eDMA_MP_DMA_ERR_IRQn = 380,    /**< DMA Error interrupt request */
    SMU_CE_eDMA_MP_CH_0_15_IRQn = 381,    /**< Interrupt for DMA Channels 0-15 */
    SMU_CE_eDMA_MP_CH_16_31_IRQn = 382,   /**< Interrupt for DMA Channels 16-31 */
    SMU_CE_MRU_COMB0_IRQn = 383,          /**< ORed interrupt0 from all MRUs */
    SMU_CE_MRU_COMB1_IRQn = 384,          /**< ORed interrupt1 from all MRUs */
    SMU_CE_CAN0_INIT_OR_ERROR_IRQn = 385, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    SMU_CE_CAN0_RXFIFO_DATA_IRQn = 386,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    SMU_CE_CAN0_MB_31_0_IRQn = 387,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    SMU_CE_CAN0_MB_63_32_IRQn = 388,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    SMU_CE_CAN0_MB_95_64_IRQn = 389,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    SMU_CE_CAN0_MB_127_96_IRQn = 390, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    SMU_AES_APP_0_IRQn = 391,         /**< app_ipi_int[0] */
    SMU_AES_APP_1_IRQn = 392,         /**< app_ipi_int[1] */
    SMU_AES_APP_2_IRQn = 393,         /**< app_ipi_int[2] */
    SMU_AES_APP_3_IRQn = 394,         /**< app_ipi_int[3] */
    SMU_AES_APP_4_IRQn = 395,         /**< app_ipi_int[4] */
    SMU_AES_APP_5_IRQn = 396,         /**< app_ipi_int[5] */
    SMU_AES_APP_6_IRQn = 397,         /**< app_ipi_int[6] */
    SMU_AES_APP_7_IRQn = 398,         /**< app_ipi_int[7] */
    SMU_AES_FEED_DMA_ERR_IRQn = 399,  /**< feed_dma_ipi_err_int */
    SMU_AES_RESULT_DMA_ERR_INT_IRQn = 400, /**< result_dma_ipi_err_int */
    SMU_SIPI0_CH1_IRQn = 401,              /**< Read interrupt channel 1 */
    SMU_SIPI0_CH2_IRQn = 402,              /**< Read interrupt channel 2 */
    SMU_SIPI0_CH3_IRQn = 403,              /**< Read interrupt channel 3 */
    SMU_SIPI0_CH4_IRQn = 404,              /**< Read interrupt channel 4 */
    SMU_SIPI0_TRIG_IRQn = 405,             /**< Trigger command interrupt */
    SMU_SIPI0_ERR1_IRQn = 406,             /**< Error interrupt 1 */
    SMU_SIPI0_ERR2_IRQn = 407,             /**< Error interrupt 2 */
    SMU_LFAST0_TX_IRQn = 408,              /**< Tx interrupt */
    SMU_LFAST0_TX_EXP_IRQn = 409,          /**< Tx exception */
    SMU_LFAST0_RX_IRQn = 410,              /**< Rx interrupt */
    SMU_LFAST0_RX_EXP_IRQn = 411,          /**< Rx exception */
    SMU_LFAST0_ICLC_RX_IRQn = 412,         /**< ICLC Rx interrupt */
    SMU_SIPI1_CH1_IRQn = 413,              /**< Read interrupt channel 1 */
    SMU_SIPI1_CH2_IRQn = 414,              /**< Read interrupt channel 2 */
    SMU_SIPI1_CH3_IRQn = 415,              /**< Read interrupt channel 3 */
    SMU_SIPI1_CH4_IRQn = 416,              /**< Read interrupt channel 4 */
    SMU_SIPI1_TRIG_IRQn = 417,             /**< Trigger command interrupt */
    SMU_SIPI1_ERR_1_IRQn = 418,            /**< Error interrupt 1 */
    SMU_SIPI1_ERR_2_IRQn = 419,            /**< Error interrupt 2 */
    SMU_LFAST1_TX_IRQn = 420,              /**< Tx interrupt */
    SMU_LFAST1_TX_EXP_IRQn = 421,          /**< Tx exception */
    SMU_LFAST1_RX_IRQn = 422,              /**< Rx interrupt */
    SMU_LFAST1_RX_EXP_IRQn = 423,          /**< Rx exception */
    SMU_LFAST1_ICLC_RX_IRQn = 424,         /**< ICLC Rx interrupt */
    SMU_GTM_AEI_IRQn = 425,                /**< GTM_AEI_IRQ AEI Shared interrupt */
    SMU_GTM_ARU0_IRQn = 426,               /**< GTM_ARU_IRQ[0] */
    SMU_GTM_ARU1_IRQn = 427,               /**< GTM_ARU_IRQ[1] */
    SMU_GTM_ARU2_IRQn = 428,               /**< GTM_ARU_IRQ[2] */
    SMU_GTM_BRC_IRQn = 429,                /**< GTM_BRC_IRQ BRC Shared interrupt */
    SMU_GTM_CMP_IRQn = 430,                /**< GTM_CMP_IRQ CMP Shared interrupt */
    SMU_GTM_TIM0_IRQn = 431,               /**< GTM_TIM[0]_IRQ[x] TIM Shared interrupts */
    SMU_GTM_TIM1_IRQn = 432,               /**< GTM_TIM[1]_IRQ[x] TIM Shared interrupts */
    SMU_GTM_TIM2_IRQn = 433,               /**< GTM_TIM[2]_IRQ[x] TIM Shared interrupts */
    SMU_GTM_MCS0_IRQn = 434,               /**< GTM_MCS[0]_IRQ[x] MCS Interrupt for channel x  */
    SMU_GTM_MCS1_IRQn = 435,               /**< GTM_MCS[1]_IRQ[x] MCS Interrupt for channel x  */
    SMU_GTM_MCS2_IRQn = 436,               /**< GTM_MCS[2]_IRQ[x] MCS Interrupt for channel x  */
    SMU_GTM_MCS3_IRQn = 437,               /**< GTM_MCS[3]_IRQ[x] MCS Interrupt for channel x  */
    SMU_GTM_TOM0_IRQn = 438,          /**< GTM_TOM[0]_IRQ[x] TOM Shared interrupts for x:0..7 */
    SMU_GTM_TOM1_IRQn = 439,          /**< GTM_TOM[1]_IRQ[x] TOM Shared interrupts for x:0..7 */
    SMU_GTM_ATOM0_IRQn = 440,         /**< GTM_ATOM[0]_IRQ[x] ATOM Shared interrupts */
    SMU_GTM_ATOM1_IRQn = 441,         /**< GTM_ATOM[1]_IRQ[x] ATOM Shared interrupts */
    SMU_GTM_ATOM2_IRQn = 442,         /**< GTM_ATOM[2]_IRQ[x] ATOM Shared interrupts */
    SMU_GTM_ATOM3_IRQn = 443,         /**< GTM_ATOM[3]_IRQ[x] ATOM Shared interrupts */
    SMU_GTM_TIO0_IRQn = 444,          /**< GTM_TIO[0] Timer Input/Output interrupts */
    SMU_GTM_TIO1_IRQn = 445,          /**< GTM_TIO[1] Timer Input/Output interrupts */
    SMU_GTM_TIO2_IRQn = 446,          /**< GTM_TIO[2] Timer Input/Output interrupts */
    SMU_GTM_DPLL_IRQn = 447,          /**< GTM_DPLL interrupt */
    SMU_GTM_FIFO0_IRQn = 448,         /**< GTM_FIFO_0 interrupt */
    SMU_GTM_SPE0_IRQn = 449,          /**< GTM_SPE[0] interrupt */
    SMU_GTM_SPE1_IRQn = 450,          /**< GTM_SPE[1] interrupt */
    SMU_GTM_ERR_IRQn = 451,           /**< GTM_ERR_IRQ GTM Error Interrupt */
    SMU_GTM_DPLL_CDSI_IRQn = 452,     /**< GTM_DPLL_CDSI_IRQ */
    SMU_GTM_DPLL_CDTI_IRQn = 453,     /**< GTM_DPLL_CDTI_IRQ */
    SMU_GTM_DPLL_TE0_IRQn = 454,      /**< GTM_DPLL_TE0_IRQ */
    SMU_DEBUG_TRACE_NW_IRQn = 462,    /**< s250_dbg_trace_nw.dbg_cti2_irq_out */
    SMU_DEBUG_TRACE_NORTH_IRQn = 463, /**< s250_dbg_trace_north.dbg_etrf_bufirq */
    SMU_CTU_FIFO_3_0_IRQn = 466, /**< FIFO0 full  or empty or overflow or overrun interrupt, FIFO1
                                    full  or empty or overflow or overrun interrupt, FIFO2 full  or
                                    empty or overflow or overrun interrupt, FIFO3 full  or empty or
                                    overflow or overrun interrupt */
    SMU_CTU_FIFO_MAS_RELOAD_IRQn = 467, /**< Master reload interrupt */
    SMU_CTU_TRIG_IRQn = 468,    /**< Trigger0 interrupt, Trigger1 interrupt, Trigger2 interrupt,
                                   Trigger3 interrupt, Trigger4 interrupt, Trigger5 interrupt, Trigger6
                                   interrupt, Trigger7 interrupt */
    SMU_CTU_ADC_CMD_IRQn = 469, /**< ADC command interrupt */
    SMU_CTU_ERR_IRQn = 470,     /**< CTU_ERR_INT */
    SMU_XRDC0_IRQn = 471,       /**< xRDC_INT0 */
    SMU_XRDC1_IRQn = 472,       /**< xRDC_INT1 */
    SMU_SINC_CH0_IRQn = 473,    /**< ipi_chn_ored_int[0] */
    SMU_SINC_CH1_IRQn = 474,    /**< ipi_chn_ored_int[1] */
    SMU_SINC_CH2_IRQn = 475,    /**< ipi_chn_ored_int[2] */
    SMU_SINC_CH3_IRQn = 476,    /**< ipi_chn_ored_int[3] */
    SMU_MEW_INT0_IRQn = 477,    /**< system_int */
    SMU_MEW_INT1_IRQn = 478,    /**< system_int */
    SMU_CMU_FC_2A_IRQn = 479    /**< async_fhh_evt | async_fll_evt */
} SMU_IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */

/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define RTU_NUMBER_OF_INT_VECTORS 865 /**< Number of interrupts in the Vector table */

typedef enum {
    /* Auxiliary constants */
    RTU_NotAvail_IRQn = -128, /**< Not available device specific interrupt */

    /* Device specific interrupts */
    RTU_SGI0_IRQn = 0,          /**< Software Generated interrupt 0 */
    RTU_SGI1_IRQn = 1,          /**< Software Generated interrupt 1 */
    RTU_SGI2_IRQn = 2,          /**< Software Generated interrupt 2 */
    RTU_SGI3_IRQn = 3,          /**< Software Generated interrupt 3 */
    RTU_SGI4_IRQn = 4,          /**< Software Generated interrupt 4 */
    RTU_SGI5_IRQn = 5,          /**< Software Generated interrupt 5 */
    RTU_SGI6_IRQn = 6,          /**< Software Generated interrupt 6 */
    RTU_SGI7_IRQn = 7,          /**< Software Generated interrupt 7 */
    RTU_SGI8_IRQn = 8,          /**< Software Generated interrupt 8 */
    RTU_SGI9_IRQn = 9,          /**< Software Generated interrupt 9 */
    RTU_SGI10_IRQn = 10,        /**< Software Generated interrupt 10 */
    RTU_SGI11_IRQn = 11,        /**< Software Generated interrupt 11 */
    RTU_SGI12_IRQn = 12,        /**< Software Generated interrupt 12 */
    RTU_SGI13_IRQn = 13,        /**< Software Generated interrupt 13 */
    RTU_SGI14_IRQn = 14,        /**< Software Generated interrupt 14 */
    RTU_SGI15_IRQn = 15,        /**< Software Generated interrupt 15 */
    RTU_MRU0_INT0_IRQn = 17,    /**< Interrupt0  */
    RTU_MRU0_INT1_IRQn = 18,    /**< Interrupt1  */
    RTU_COMM_IRQn = 22,         /**< Per-core interrupt: Communications channel receive or transmit
                                   interrupt request  */
    RTU_PMU_IRQn = 23,          /**< Per-core interrupt: PMU interrupt request */
    RTU_CTI_IRQn = 24,          /**< Per-core interrupt: Cross trigger interface (CTI) interrupt */
    RTU_MAINTENANCE_IRQn = 25,  /**< Per-core interrupt: Virtual CPU Interface Maintenance interrupt
                                 */
    RTU_HYPERV_TIM_IRQn = 26,   /**< Per-core interrupt: Hypervisor timer interrupt */
    RTU_VIRTUAL_TIM_IRQn = 27,  /**< Per-core interrupt: Virtual timer interrupt */
    RTU_EL1_TIM_IRQn = 30,      /**< Per-core interrupt: Non-secure EL1 physical timer */
    RTU_RTUn_SWT0_IRQn = 40,    /**< Interrupt request */
    RTU_RTUn_SWT1_IRQn = 41,    /**< Interrupt request */
    RTU_RTUn_SWT2_IRQn = 42,    /**< Interrupt request */
    RTU_RTUn_SWT3_IRQn = 43,    /**< Interrupt request */
    RTU_RTUn_SWT4_IRQn = 44,    /**< Interrupt request */
    RTU_RTUn_STM0_IRQn = 45,    /**< STM0 interrupt channel request 0, 1, 2, 3 */
    RTU_RTUn_STM1_IRQn = 46,    /**< STM1 interrupt channel request 0, 1, 2, 3 */
    RTU_RTUn_STM2_IRQn = 47,    /**< STM2 interrupt channel request 0, 1, 2, 3 */
    RTU_RTUn_STM3_IRQn = 48,    /**< STM3 interrupt channel request 0, 1, 2, 3 */
    RTU_RTUn_PIT0_IRQn = 51,    /**< Ored all Interrupt Channels */
    RTU_C_VFCCU_OUT0_IRQn = 52, /**< vfccu_reactions_out[0]/[8] */
    RTU_C_VFCCU_OUT1_IRQn = 53, /**< vfccu_reactions_out[1]/[9] */
    RTU_C_VFCCU_OUT2_IRQn = 54, /**< vfccu_reactions_out[2]/[10] */
    RTU_C_VFCCU_OUT3_IRQn = 55, /**< vfccu_reactions_out[3]/[11] */
    RTU_DEBUG_ETR_IRQn = 56,    /**< dbg_etr_bufirq */
    RTU_RTUn_PMC_IRQn = 57,     /**< TEST_ENDED */
    RTU_DEBUG_CTI_IRQn = 58,    /**< dbg_cti_irq */
    RTU_DMA0_ERR_IRQn = 60,     /**< DMA Error interrupt request */
    RTU_DMA0_0_15_IRQn = 61,    /**< Interrupt for DMA CH0-15 */
    RTU_DMA0_16_31_IRQn = 62,   /**< Interrupt for DMA CH16-31 */
    RTU_DMA0_0_IRQn = 63,       /**< Interrupt for DMA Channel 0 */
    RTU_DMA0_1_IRQn = 64,       /**< Interrupt for DMA Channel 1 */
    RTU_DMA0_2_IRQn = 65,       /**< Interrupt for DMA Channel 2 */
    RTU_DMA0_3_IRQn = 66,       /**< Interrupt for DMA Channel 3 */
    RTU_DMA0_4_IRQn = 67,       /**< Interrupt for DMA Channel 4 */
    RTU_DMA0_5_IRQn = 68,       /**< Interrupt for DMA Channel 5 */
    RTU_DMA0_6_IRQn = 69,       /**< Interrupt for DMA Channel 6 */
    RTU_DMA0_7_IRQn = 70,       /**< Interrupt for DMA Channel 7 */
    RTU_DMA0_8_IRQn = 71,       /**< Interrupt for DMA Channel 8 */
    RTU_DMA0_9_IRQn = 72,       /**< Interrupt for DMA Channel 9 */
    RTU_DMA0_10_IRQn = 73,      /**< Interrupt for DMA Channel 10 */
    RTU_DMA0_11_IRQn = 74,      /**< Interrupt for DMA Channel 11 */
    RTU_DMA0_12_IRQn = 75,      /**< Interrupt for DMA Channel 12 */
    RTU_DMA0_13_IRQn = 76,      /**< Interrupt for DMA Channel 13 */
    RTU_DMA0_14_IRQn = 77,      /**< Interrupt for DMA Channel 14 */
    RTU_DMA0_15_IRQn = 78,      /**< Interrupt for DMA Channel 15 */
    RTU_DMA0_16_IRQn = 79,      /**< Interrupt for DMA Channel 16 */
    RTU_DMA0_17_IRQn = 80,      /**< Interrupt for DMA Channel 17 */
    RTU_DMA0_18_IRQn = 81,      /**< Interrupt for DMA Channel 18 */
    RTU_DMA0_19_IRQn = 82,      /**< Interrupt for DMA Channel 19 */
    RTU_DMA0_20_IRQn = 83,      /**< Interrupt for DMA Channel 20 */
    RTU_DMA0_21_IRQn = 84,      /**< Interrupt for DMA Channel 21 */
    RTU_DMA0_22_IRQn = 85,      /**< Interrupt for DMA Channel 22 */
    RTU_DMA0_23_IRQn = 86,      /**< Interrupt for DMA Channel 23 */
    RTU_DMA0_24_IRQn = 87,      /**< Interrupt for DMA Channel 24 */
    RTU_DMA0_25_IRQn = 88,      /**< Interrupt for DMA Channel 25 */
    RTU_DMA0_26_IRQn = 89,      /**< Interrupt for DMA Channel 26 */
    RTU_DMA0_27_IRQn = 90,      /**< Interrupt for DMA Channel 27 */
    RTU_DMA0_28_IRQn = 91,      /**< Interrupt for DMA Channel 28 */
    RTU_DMA0_29_IRQn = 92,      /**< Interrupt for DMA Channel 29 */
    RTU_DMA0_30_IRQn = 93,      /**< Interrupt for DMA Channel 30 */
    RTU_DMA0_31_IRQn = 94,      /**< Interrupt for DMA Channel 31 */
    RTU_DMA1_ERR_IRQn = 95,     /**< DMA Error interrupt request */
    RTU_DMA1_0_15_IRQn = 96,    /**< Interrupt for DMA CH0-15 */
    RTU_DMA1_0_IRQn = 97,       /**< Interrupt for DMA Channel 0 */
    RTU_DMA1_1_IRQn = 98,       /**< Interrupt for DMA Channel 1 */
    RTU_DMA1_2_IRQn = 99,       /**< Interrupt for DMA Channel 2 */
    RTU_DMA1_3_IRQn = 100,      /**< Interrupt for DMA Channel 3 */
    RTU_DMA1_4_IRQn = 101,      /**< Interrupt for DMA Channel 4 */
    RTU_DMA1_5_IRQn = 102,      /**< Interrupt for DMA Channel 5 */
    RTU_DMA1_6_IRQn = 103,      /**< Interrupt for DMA Channel 6 */
    RTU_DMA1_7_IRQn = 104,      /**< Interrupt for DMA Channel 7 */
    RTU_DMA1_8_IRQn = 105,      /**< Interrupt for DMA Channel 8 */
    RTU_DMA1_9_IRQn = 106,      /**< Interrupt for DMA Channel 9 */
    RTU_DMA1_10_IRQn = 107,     /**< Interrupt for DMA Channel 10 */
    RTU_DMA1_11_IRQn = 108,     /**< Interrupt for DMA Channel 11 */
    RTU_DMA1_12_IRQn = 109,     /**< Interrupt for DMA Channel 12 */
    RTU_DMA1_13_IRQn = 110,     /**< Interrupt for DMA Channel 13 */
    RTU_DMA1_14_IRQn = 111,     /**< Interrupt for DMA Channel 14 */
    RTU_DMA1_15_IRQn = 112,     /**< Interrupt for DMA Channel 15 */
    RTU_DMA4_ERR_IRQn = 113,    /**< DMA Error interrupt request */
    RTU_DMA4_0_15_IRQn = 114,   /**< Interrupt for DMA CH0-15 */
    RTU_DMA4_0_IRQn = 115,      /**< Interrupt for DMA Channel 0 */
    RTU_DMA4_1_IRQn = 116,      /**< Interrupt for DMA Channel 1 */
    RTU_DMA4_2_IRQn = 117,      /**< Interrupt for DMA Channel 2 */
    RTU_DMA4_3_IRQn = 118,      /**< Interrupt for DMA Channel 3 */
    RTU_DMA4_4_IRQn = 119,      /**< Interrupt for DMA Channel 4 */
    RTU_DMA4_5_IRQn = 120,      /**< Interrupt for DMA Channel 5 */
    RTU_DMA4_6_IRQn = 121,      /**< Interrupt for DMA Channel 6 */
    RTU_DMA4_7_IRQn = 122,      /**< Interrupt for DMA Channel 7 */
    RTU_DMA4_8_IRQn = 123,      /**< Interrupt for DMA Channel 8 */
    RTU_DMA4_9_IRQn = 124,      /**< Interrupt for DMA Channel 9 */
    RTU_DMA4_10_IRQn = 125,     /**< Interrupt for DMA Channel 10 */
    RTU_DMA4_11_IRQn = 126,     /**< Interrupt for DMA Channel 11 */
    RTU_DMA4_12_IRQn = 127,     /**< Interrupt for DMA Channel 12 */
    RTU_DMA4_13_IRQn = 128,     /**< Interrupt for DMA Channel 13 */
    RTU_DMA4_14_IRQn = 129,     /**< Interrupt for DMA Channel 14 */
    RTU_DMA4_15_IRQn = 130,     /**< Interrupt for DMA Channel 15 */
    RTU_DMA5_ERR_IRQn = 131,    /**< DMA Error interrupt request */
    RTU_DMA5_0_15_IRQn = 132,   /**< Interrupt for DMA CH0-15 */
    RTU_DMA5_0_IRQn = 133,      /**< Interrupt for DMA Channel 0 */
    RTU_DMA5_1_IRQn = 134,      /**< Interrupt for DMA Channel 1 */
    RTU_DMA5_2_IRQn = 135,      /**< Interrupt for DMA Channel 2 */
    RTU_DMA5_3_IRQn = 136,      /**< Interrupt for DMA Channel 3 */
    RTU_DMA5_4_IRQn = 137,      /**< Interrupt for DMA Channel 4 */
    RTU_DMA5_5_IRQn = 138,      /**< Interrupt for DMA Channel 5 */
    RTU_DMA5_6_IRQn = 139,      /**< Interrupt for DMA Channel 6 */
    RTU_DMA5_7_IRQn = 140,      /**< Interrupt for DMA Channel 7 */
    RTU_DMA5_8_IRQn = 141,      /**< Interrupt for DMA Channel 8 */
    RTU_DMA5_9_IRQn = 142,      /**< Interrupt for DMA Channel 9 */
    RTU_DMA5_10_IRQn = 143,     /**< Interrupt for DMA Channel 10 */
    RTU_DMA5_11_IRQn = 144,     /**< Interrupt for DMA Channel 11 */
    RTU_DMA5_12_IRQn = 145,     /**< Interrupt for DMA Channel 12 */
    RTU_DMA5_13_IRQn = 146,     /**< Interrupt for DMA Channel 13 */
    RTU_DMA5_14_IRQn = 147,     /**< Interrupt for DMA Channel 14 */
    RTU_DMA5_15_IRQn = 148,     /**< Interrupt for DMA Channel 15 */
    RTU_DMA3_ERR_IRQn = 149,    /**< DMA Error interrupt request */
    RTU_DMA3_0_15_IRQn = 150,   /**< Interrupt for DMA CH0-15 */
    RTU_DMA3_16_31_IRQn = 151,  /**< Interrupt for DMA CH16-31 */
    RTU_DMA3_0_IRQn = 152,      /**< Interrupt for DMA Channel 0 */
    RTU_DMA3_1_IRQn = 153,      /**< Interrupt for DMA Channel 1 */
    RTU_DMA3_2_IRQn = 154,      /**< Interrupt for DMA Channel 2 */
    RTU_DMA3_3_IRQn = 155,      /**< Interrupt for DMA Channel 3 */
    RTU_DMA3_4_IRQn = 156,      /**< Interrupt for DMA Channel 4 */
    RTU_DMA3_5_IRQn = 157,      /**< Interrupt for DMA Channel 5 */
    RTU_DMA3_6_IRQn = 158,      /**< Interrupt for DMA Channel 6 */
    RTU_DMA3_7_IRQn = 159,      /**< Interrupt for DMA Channel 7 */
    RTU_DMA3_8_IRQn = 160,      /**< Interrupt for DMA Channel 8 */
    RTU_DMA3_9_IRQn = 161,      /**< Interrupt for DMA Channel 9 */
    RTU_DMA3_10_IRQn = 162,     /**< Interrupt for DMA Channel 10 */
    RTU_DMA3_11_IRQn = 163,     /**< Interrupt for DMA Channel 11 */
    RTU_DMA3_12_IRQn = 164,     /**< Interrupt for DMA Channel 12 */
    RTU_DMA3_13_IRQn = 165,     /**< Interrupt for DMA Channel 13 */
    RTU_DMA3_14_IRQn = 166,     /**< Interrupt for DMA Channel 14 */
    RTU_DMA3_15_IRQn = 167,     /**< Interrupt for DMA Channel 15 */
    RTU_DMA3_16_IRQn = 168,     /**< Interrupt for DMA Channel 16 */
    RTU_DMA3_17_IRQn = 169,     /**< Interrupt for DMA Channel 17 */
    RTU_DMA3_18_IRQn = 170,     /**< Interrupt for DMA Channel 18 */
    RTU_DMA3_19_IRQn = 171,     /**< Interrupt for DMA Channel 19 */
    RTU_DMA3_20_IRQn = 172,     /**< Interrupt for DMA Channel 20 */
    RTU_DMA3_21_IRQn = 173,     /**< Interrupt for DMA Channel 21 */
    RTU_DMA3_22_IRQn = 174,     /**< Interrupt for DMA Channel 22 */
    RTU_DMA3_23_IRQn = 175,     /**< Interrupt for DMA Channel 23 */
    RTU_DMA3_24_IRQn = 176,     /**< Interrupt for DMA Channel 24 */
    RTU_DMA3_25_IRQn = 177,     /**< Interrupt for DMA Channel 25 */
    RTU_DMA3_26_IRQn = 178,     /**< Interrupt for DMA Channel 26 */
    RTU_DMA3_27_IRQn = 179,     /**< Interrupt for DMA Channel 27 */
    RTU_DMA3_28_IRQn = 180,     /**< Interrupt for DMA Channel 28 */
    RTU_DMA3_29_IRQn = 181,     /**< Interrupt for DMA Channel 29 */
    RTU_DMA3_30_IRQn = 182,     /**< Interrupt for DMA Channel 30 */
    RTU_DMA3_31_IRQn = 183,     /**< Interrupt for DMA Channel 31 */
    RTU_QuadSPI0_Ored_IRQn = 184,        /**< All interrupts ORed output */
    RTU_QuadSPI0_FLASH_A_ERR_IRQn = 185, /**< Flash A Error interrupt */
    RTU_QuadSPI1_Ored_IRQn = 186,        /**< All interrupts ORed output */
    RTU_QuadSPI1_FLASH_A_ERR_IRQn = 187, /**< Flash A Error interrupt */
    RTU_QuadSPI1_FLASH_B_ERR_IRQn = 188, /**< Flash B Error interrupt */
    RTU_CSTCU_IRQn = 189,                /**< SLFTEST_END_INT */
    RTU_USDHC_IRQn = 190,                /**< uSDHC Interrupt */
    RTU_PIT0_IRQn = 191,                 /**< Ored all Interrupt Channels */
    RTU_PIT1_IRQn = 192,                 /**< Ored all Interrupt Channels */
    RTU_PIT4_IRQn = 193,                 /**< Ored all Interrupt Channels */
    RTU_PIT5_IRQn = 194,                 /**< Ored all Interrupt Channels */
    RTU_NETC_IRQn = 196,                 /**< NETC Interrupt */
    RTU_ADC0_EOC_IRQn = 200,             /**< End of conv. Interrupt */
    RTU_ADC0_ERR_IRQn = 201,             /**< Error interrupt */
    RTU_ADC0_WDT_IRQn = 202,             /**< Analog watchdog interrupt */
    RTU_FR0_NCERR_IRQn = 203,            /**< LRAM and DRAM Non-Corrected Error interrupt */
    RTU_FR0_CERR_IRQn = 204,             /**< LRAM and DRAM Corrected Error interrupt */
    RTU_FR0_FIFO_CHA_IRQn = 205,         /**< Receive FIFO channel A not empty interrupt */
    RTU_FR0_FIFO_CHB_IRQn = 206,         /**< Receive FIFO channel B not empty interrupt */
    RTU_FR0_WKUP_IRQn = 207,             /**< Wakeup interrupt */
    RTU_FR0_STATUS_IRQn = 208,           /**< Combined protocol status and error interrupt */
    RTU_FR0_CMBERR_IRQn = 209,           /**< Combined CHI error interrupt */
    RTU_FR0_TX_BUFF_IRQn = 210,          /**< Combined transmit message buffer interrupt */
    RTU_FR0_RX_BUFF_IRQn = 211,          /**< Combined receive message buffer interrupt */
    RTU_FR0_MODULE_IRQn = 212,           /**< Combined module interrupt */
    RTU_FR1_NCERR_IRQn = 213,            /**< LRAM and DRAM Non-Corrected Error interrupt */
    RTU_FR1_CERR_IRQn = 214,             /**< LRAM and DRAM Corrected Error interrupt */
    RTU_FR1_FIFO_CHA_IRQn = 215,         /**< Receive FIFO channel A not empty interrupt */
    RTU_FR1_FIFO_CHB_IRQn = 216,         /**< Receive FIFO channel B not empty interrupt */
    RTU_FR1_WKUP_IRQn = 217,             /**< Wakeup interrupt */
    RTU_FR1_STATUS_IRQn = 218,           /**< Combined protocol status and error interrupt */
    RTU_FR1_CMBERR_IRQn = 219,           /**< Combined CHI error interrupt */
    RTU_FR1_TX_BUFF_IRQn = 220,          /**< Combined transmit message buffer interrupt */
    RTU_FR1_RX_BUFF_IRQn = 221,          /**< Combined receive message buffer interrupt */
    RTU_FR1_MODULE_IRQn = 222,           /**< Combined module interrupt */
    RTU_DSPI0_IRQn = 223,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI1_IRQn = 224,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI2_IRQn = 225,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI3_IRQn = 226,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI4_IRQn = 227,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI5_IRQn = 228,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI6_IRQn = 229,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI7_IRQn = 230,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI8_IRQn = 231,                /**< OR'ed DSPI Global Interrupt */
    RTU_DSPI9_IRQn = 232,                /**< OR'ed DSPI Global Interrupt */
    RTU_ADC1_EOC_IRQn = 233,             /**< End of conv. Interrupt */
    RTU_ADC1_ERR_IRQn = 234,             /**< Error interrupt */
    RTU_ADC1_WDT_IRQn = 235,             /**< Analog watchdog interrupt */
    RTU_MSC0_DSPI_IRQn = 236,            /**< DSPI Global Interrupt (OR of all interrupt lines) */
    RTU_MSC0_LIN_IRQn = 237,   /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LCU0_CELL0_IRQn = 238, /**< Logic Cell 0 Interrupt */
    RTU_LCU0_CELL1_IRQn = 239, /**< Logic Cell 1 Interrupt */
    RTU_LCU0_CELL2_IRQn = 240, /**< Logic Cell 2 Interrupt */
    RTU_LCU1_CELL0_IRQn = 241, /**< Logic Cell 0 Interrupt */
    RTU_LCU1_CELL1_IRQn = 242, /**< Logic Cell 1 Interrupt */
    RTU_LCU1_CELL2_IRQn = 243, /**< Logic Cell 2 Interrupt */
    RTU_LINFLEXD0_IRQn = 244,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD1_IRQn = 245,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD2_IRQn = 246,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD3_IRQn = 247,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD4_IRQn = 248,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD5_IRQn = 249,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD6_IRQn = 250,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD7_IRQn = 251,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD8_IRQn = 252,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD9_IRQn = 253,  /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD10_IRQn = 254, /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_LINFLEXD11_IRQn = 255, /**< Internal Receiver Interrupt request, Internal Transmitter
                                  interrupt request, Internal Error Interrupt request */
    RTU_CANXL0_INT_RX_TX_DATA_IRQn = 256, /**< CANXL: CAN frame data */
    RTU_CANXL0_INT_ERR_IRQn = 257,        /**< CANXL: error occurred in CANXL */
    RTU_CANXL1_INT_RX_TX_DATA_IRQn = 258, /**< 'CANXL: CAN frame data */
    RTU_CANXL1_INT_ERR_IRQn = 259,        /**< CANXL: error occurred in CANXL */
    RTU_CANXL0_INT_TX_MB_1_IRQn = 260,    /**< ORed Tx Interrupts (Transmit descriptor configuration
                                             for host interrupt 0) */
    RTU_CANXL0_INT_TX_MB_2_IRQn = 261,    /**< ORed Tx Interrupts (Transmit descriptor configuration
                                             for host interrupt 1) */
    RTU_CANXL0_INT_RX_MB_1_IRQn = 262, /**< ORed Rx Interrupts (Receive descriptor configuration for
                                          host interrupt 0) */
    RTU_CANXL0_INT_RX_MB_2_IRQn = 263, /**< ORed Rx Interrupts (Receive descriptor configuration for
                                          host interrupt 1) */
    RTU_CANXL0_INT_RX_FIFO_IRQn = 264, /**< CANXL: the Rx FIFO used for reception of selected CAN
                                          frames has reached its programmeble threshold */
    RTU_CANXL0_INT_MRU_IRQn = 265,     /**< CANXL: interrupt from CANXL Message Recveive Unit */
    RTU_CANXL0_INT_RX_TX_ERR_IRQn = 266,    /**< CANXL: protocol engine error occured related to
                                               reception or transmission of CAN frames. */
    RTU_CANXL0_INT_INTERNAL_ERR_IRQn = 267, /**< CANXL: internal exception is detected */
    RTU_CANXL0_INT_LRAM_ECC_NOCORR_ERR_IRQn = 268, /**< CANXL: non-correctable error occured within
                                                      internal data RAM  */
    RTU_CANXL0_INT_RAM_ECC_CORR_ERR_IRQn = 270,    /**< CANXL: correctable error occured within
                                                      internal data RAM or code RAM */
    RTU_CANXL0_INT_FREEZE_IRQn = 271,  /**< CANXL: IP has entered or exited freeze mode */
    RTU_CANXL1_INT_TX_MB_1_IRQn = 272, /**< CANXL: CAN frame transmission from one of the Tx message
                                          buffers 0-31 completed */
    RTU_CANXL1_INT_TX_MB_2_IRQn = 273, /**< CANXL: CAN frame transmission from one of the Tx message
                                          buffers 32-63 completed */
    RTU_CANXL1_INT_RX_MB_1_IRQn = 274, /**< CANXL: CAN frame reception into one of the Rx message
                                          buffers 0-31 completed */
    RTU_CANXL1_INT_RX_MB_2_IRQn = 275, /**< CANXL: CAN frame reception into one of the Rx message
                                          buffers 32-63 completed */
    RTU_CANXL1_INT_RX_FIFO_IRQn = 276, /**< CANXL: the Rx FIFO used for reception of selected CAN
                                          frames has reached its programmeble threshold */
    RTU_CANXL1_INT_MRU_IRQn = 277,     /**< CANXL: interrupt from CANXL Message Recveive Unit */
    RTU_CANXL1_INT_RX_TX_ERR_IRQn = 278,    /**< CANXL: protocol engine error occured related to
                                               reception or transmission of CAN frames. */
    RTU_CANXL1_INT_INTERNAL_ERR_IRQn = 279, /**< CANXL: internal exception is detected */
    RTU_CANXL1_INT_LRAM_ECC_NOCORR_ERR_IRQn = 280, /**< CANXL: non-correctable error occured within
                                                      internal data RAM  */
    RTU_CANXL1_INT_RAM_ECC_CORR_ERR_IRQn = 282,    /**< CANXL: correctable error occured within
                                                      internal data RAM or code RAM */
    RTU_CANXL1_INT_FREEZE_IRQn = 283, /**< CANXL: IP has entered or exited freeze mode */
    RTU_I3C0_IRQn = 284,              /**< Interrupt Request */
    RTU_LPI2C1_IRQn = 285,            /**< Interrupt Request */
    RTU_LPI2C2_IRQn = 286,            /**< Interrupt Request */
    RTU_MC_RGM_IRQn = 287,            /**< Interrupt Request to System */
    RTU_HSE_MU0_TX_IRQn = 288,        /**< Ored tx interrupt to MU-0 */
    RTU_HSE_MU0_RX_IRQn = 289,        /**< Ored rx interrupt to MU-0 */
    RTU_HSE_MU0_ORED_IRQn = 290,      /**< ORed general purpose interrupt request to MU-0 */
    RTU_HSE_MU1_TX_IRQn = 291,        /**< Ored tx interrupt to MU-1 */
    RTU_HSE_MU1_RX_IRQn = 292,        /**< Ored rx interrupt to MU-1 */
    RTU_HSE_MU1_ORED_IRQn = 293,      /**< ORed general purpose interrupt request to MU-1 */
    RTU_HSE_MU2_TX_IRQn = 294,        /**< Ored tx interrupt to MU-2 */
    RTU_HSE_MU2_RX_IRQn = 295,        /**< Ored rx interrupt to MU-2 */
    RTU_HSE_MU2_ORED_IRQn = 296,      /**< ORed general purpose interrupt request to MU-2 */
    RTU_HSE_MU3_TX_IRQn = 297,        /**< Ored tx interrupt to MU-3 */
    RTU_HSE_MU3_RX_IRQn = 298,        /**< Ored rx interrupt to MU-3 */
    RTU_HSE_MU3_ORED_IRQn = 299,      /**< ORed general purpose interrupt request to MU-3 */
    RTU_HSE_MU4_TX_IRQn = 300,        /**< Ored tx interrupt to MU-4 */
    RTU_HSE_MU4_RX_IRQn = 301,        /**< Ored rx interrupt to MU-4 */
    RTU_HSE_MU4_ORED_IRQn = 302,      /**< ORed general purpose interrupt request to MU-4 */
    RTU_HSE_MU5_TX_IRQn = 303,        /**< Ored tx interrupt to MU-5 */
    RTU_HSE_MU5_RX_IRQn = 304,        /**< Ored rx interrupt to MU-5 */
    RTU_HSE_MU5_ORED_IRQn = 305,      /**< ORed general purpose interrupt request to MU-5 */
    RTU_HSE_MU6_TX_IRQn = 306,        /**< Ored tx interrupt to MU-6 */
    RTU_HSE_MU6_RX_IRQn = 307,        /**< Ored rx interrupt to MU-6 */
    RTU_HSE_MU6_ORED_IRQn = 308,      /**< ORed general purpose interrupt request to MU-6 */
    RTU_HSE_MU7_TX_IRQn = 309,        /**< Ored tx interrupt to MU-7 */
    RTU_HSE_MU7_RX_IRQn = 310,        /**< Ored rx interrupt to MU-7 */
    RTU_HSE_MU7_ORED_IRQn = 311,      /**< ORed general purpose interrupt request to MU-7 */
    RTU_DDR_CTRL_IRQn = 312,          /**< DDR controller detected critical interrupt */
    RTU_DDR_PHY_IRQn = 313,           /**< PHY address decoding error inside DDR SS */
    RTU_DDR_PM_IRQn = 314,            /**< Performance Monitoring Interrupt */
    RTU_TMU_IRQn = 315, /**< Level sensitive temperature alarm interrupt | Level sensitive citical
                           temperature alarm interrupt */
    RTU_EMIOS0_OVRFL_IRQn = 316,  /**< Overflow interrupt */
    RTU_EMIOS0_CH0_IRQn = 317,    /**< Interrupt request channel 0 */
    RTU_EMIOS0_CH1_IRQn = 318,    /**< Interrupt request channel 1 */
    RTU_EMIOS0_CH2_IRQn = 319,    /**< Interrupt request channel 2 */
    RTU_EMIOS0_CH3_IRQn = 320,    /**< Interrupt request channel 3 */
    RTU_EMIOS0_CH4_IRQn = 321,    /**< Interrupt request channel 4 */
    RTU_EMIOS0_CH5_IRQn = 322,    /**< Interrupt request channel 5 */
    RTU_EMIOS0_CH6_IRQn = 323,    /**< Interrupt request channel 6 */
    RTU_EMIOS0_CH7_IRQn = 324,    /**< Interrupt request channel 7 */
    RTU_EMIOS0_CH8_IRQn = 325,    /**< Interrupt request channel 8 */
    RTU_EMIOS0_CH10_IRQn = 326,   /**< Interrupt request channel 10 */
    RTU_EMIOS0_CH12_IRQn = 327,   /**< Interrupt request channel 12 */
    RTU_EMIOS0_CH14_IRQn = 328,   /**< Interrupt request channel 14 */
    RTU_EMIOS0_CH16_IRQn = 329,   /**< Interrupt request channel 16 */
    RTU_EMIOS0_CH17_IRQn = 330,   /**< Interrupt request channel 17 */
    RTU_EMIOS0_CH18_IRQn = 331,   /**< Interrupt request channel 18 */
    RTU_EMIOS0_CH19_IRQn = 332,   /**< Interrupt request channel 19 */
    RTU_EMIOS0_CH20_IRQn = 333,   /**< Interrupt request channel 20 */
    RTU_EMIOS0_CH21_IRQn = 334,   /**< Interrupt request channel 21 */
    RTU_EMIOS0_CH22_IRQn = 335,   /**< Interrupt request channel 22 */
    RTU_EMIOS0_CH23_IRQn = 336,   /**< Interrupt request channel 23 */
    RTU_EMIOS0_CH24_IRQn = 337,   /**< Interrupt request channel 24 */
    RTU_EMIOS0_CH25_IRQn = 338,   /**< Interrupt request channel 25 */
    RTU_EMIOS0_CH26_IRQn = 339,   /**< Interrupt request channel 26 */
    RTU_EMIOS0_CH27_IRQn = 340,   /**< Interrupt request channel 27 */
    RTU_EMIOS0_CH28_IRQn = 341,   /**< Interrupt request channel 28 */
    RTU_EMIOS0_CH29_IRQn = 342,   /**< Interrupt request channel 29 */
    RTU_EMIOS0_CH30_IRQn = 343,   /**< Interrupt request channel 30 */
    RTU_EMIOS0_CH31_IRQn = 344,   /**< Interrupt request channel 31 */
    RTU_EMIOS1_OVRFL_IRQn = 345,  /**< Overflow interrupt */
    RTU_EMIOS1_CH0_IRQn = 346,    /**< Interrupt request channel 0 */
    RTU_EMIOS1_CH1_IRQn = 347,    /**< Interrupt request channel 1 */
    RTU_EMIOS1_CH2_IRQn = 348,    /**< Interrupt request channel 2 */
    RTU_EMIOS1_CH3_IRQn = 349,    /**< Interrupt request channel 3 */
    RTU_EMIOS1_CH4_IRQn = 350,    /**< Interrupt request channel 4 */
    RTU_EMIOS1_CH5_IRQn = 351,    /**< Interrupt request channel 5 */
    RTU_EMIOS1_CH6_IRQn = 352,    /**< Interrupt request channel 6 */
    RTU_EMIOS1_CH7_IRQn = 353,    /**< Interrupt request channel 7 */
    RTU_EMIOS1_CH8_IRQn = 354,    /**< Interrupt request channel 8 */
    RTU_EMIOS1_CH10_IRQn = 355,   /**< Interrupt request channel 10 */
    RTU_EMIOS1_CH12_IRQn = 356,   /**< Interrupt request channel 12 */
    RTU_EMIOS1_CH14_IRQn = 357,   /**< Interrupt request channel 14 */
    RTU_EMIOS1_CH16_IRQn = 358,   /**< Interrupt request channel 16 */
    RTU_EMIOS1_CH17_IRQn = 359,   /**< Interrupt request channel 17 */
    RTU_EMIOS1_CH18_IRQn = 360,   /**< Interrupt request channel 18 */
    RTU_EMIOS1_CH19_IRQn = 361,   /**< Interrupt request channel 19 */
    RTU_EMIOS1_CH20_IRQn = 362,   /**< Interrupt request channel 20 */
    RTU_EMIOS1_CH21_IRQn = 363,   /**< Interrupt request channel 21 */
    RTU_EMIOS1_CH22_IRQn = 364,   /**< Interrupt request channel 22 */
    RTU_EMIOS1_CH23_IRQn = 365,   /**< Interrupt request channel 23 */
    RTU_EMIOS1_CH24_IRQn = 366,   /**< Interrupt request channel 24 */
    RTU_EMIOS1_CH25_IRQn = 367,   /**< Interrupt request channel 25 */
    RTU_EMIOS1_CH26_IRQn = 368,   /**< Interrupt request channel 26 */
    RTU_EMIOS1_CH27_IRQn = 369,   /**< Interrupt request channel 27 */
    RTU_EMIOS1_CH28_IRQn = 370,   /**< Interrupt request channel 28 */
    RTU_EMIOS1_CH29_IRQn = 371,   /**< Interrupt request channel 29 */
    RTU_EMIOS1_CH30_IRQn = 372,   /**< Interrupt request channel 30 */
    RTU_EMIOS1_CH31_IRQn = 373,   /**< Interrupt request channel 31 */
    RTU_PSI50_CH0_DMA_IRQn = 374, /**< PSI5 channel 0 DMA combined interrupt- DMA transfer to SMC
                                     frame register complete, DMAtransfer complete, FIFO full, SMC
                                     frame, DMA undeflow, Data underflow */
    RTU_PSI50_CH0_GEN_INT_IRQn = 375,   /**< PSI5 channel 0 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI50_CH0_NEW_MSG_IRQn = 376,   /**< PSI5 channel 0 new message received */
    RTU_PSI50_CH0_MSG_OVRWR_IRQn = 377, /**< PSI5 channel 0 message overwrite */
    RTU_PSI50_CH0_ERR_IRQn = 378,       /**< PSI5 channel 0 error */
    RTU_PSI50_CH0_COMB_IRQn = 379, /**< PSI5 channel 0 combined interrupt- All PSI5 interrupts */
    RTU_PSI50_CH1_DMA_IRQn = 380,  /**< PSI5 channel 1 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI50_CH1_GEN_INT_IRQn = 381,   /**< PSI5 channel 1 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI50_CH1_NEW_MSG_IRQn = 382,   /**< PSI5 channel 1 new message received */
    RTU_PSI50_CH1_MSG_OVRWR_IRQn = 383, /**< PSI5 channel 1 message overwrite */
    RTU_PSI50_CH1_ERR_IRQn = 384,       /**< PSI5 channel 1 error */
    RTU_PSI50_CH1_COMB_IRQn = 385, /**< PSI5 channel 1 combined interrupt- All PSI5 interrupts */
    RTU_PSI50_CH2_DMA_IRQn = 386,  /**< PSI5 channel 2 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI50_CH2_GEN_INT_IRQn = 387,   /**< PSI5 channel 2 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI50_CH2_NEW_MSG_IRQn = 388,   /**< PSI5 channel 2 new message received */
    RTU_PSI50_CH2_MSG_OVRWR_IRQn = 389, /**< PSI5 channel 2 message overwrite */
    RTU_PSI50_CH2_ERR_IRQn = 390,       /**< PSI5 channel 2 error */
    RTU_PSI50_CH2_COMB_IRQn = 391, /**< PSI5 channel 2 combined interrupt- All PSI5 interrupts */
    RTU_PSI50_CH3_DMA_IRQn = 392,  /**< PSI5 channel 3 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI50_CH3_GEN_INT_IRQn = 393,   /**< PSI5 channel 3 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI50_CH3_NEW_MSG_IRQn = 394,   /**< PSI5 channel 3 new message received */
    RTU_PSI50_CH3_MSG_OVRWR_IRQn = 395, /**< PSI5 channel 3 message overwrite */
    RTU_PSI50_CH3_ERR_IRQn = 396,       /**< PSI5 channel 3 error */
    RTU_PSI50_CH3_COMB_IRQn = 397, /**< PSI5 channel 3 combined interrupt- All PSI5 interrupts */
    RTU_PSI51_CH0_DMA_IRQn = 398,  /**< PSI5 channel 0 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI51_CH0_GEN_INT_IRQn = 399,   /**< PSI5 channel 0 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI51_CH0_NEW_MSG_IRQn = 400,   /**< PSI5 channel 0 new message received */
    RTU_PSI51_CH0_MSG_OVRWR_IRQn = 401, /**< PSI5 channel 0 message overwrite */
    RTU_PSI51_CH0_ERR_IRQn = 402,       /**< PSI5 channel 0 error */
    RTU_PSI51_CH0_COMB_IRQn = 403, /**< PSI5 channel 0 combined interrupt- All PSI5 interrupts */
    RTU_PSI51_CH1_DMA_IRQn = 404,  /**< PSI5 channel 1 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI51_CH1_GEN_INT_IRQn = 405,   /**< PSI5 channel 1 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI51_CH1_NEW_MSG_IRQn = 406,   /**< PSI5 channel 1 new message received */
    RTU_PSI51_CH1_MSG_OVRWR_IRQn = 407, /**< PSI5 channel 1 message overwrite */
    RTU_PSI51_CH1_ERR_IRQn = 408,       /**< PSI5 channel 1 error */
    RTU_PSI51_CH1_COMB_IRQn = 409, /**< PSI5 channel 1 combined interrupt- All PSI5 interrupts */
    RTU_PSI51_CH2_DMA_IRQn = 410,  /**< PSI5 channel 2 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI51_CH2_GEN_INT_IRQn = 411,   /**< PSI5 channel 2 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI51_CH2_NEW_MSG_IRQn = 412,   /**< PSI5 channel 2 new message received */
    RTU_PSI51_CH2_MSG_OVRWR_IRQn = 413, /**< PSI5 channel 2 message overwrite */
    RTU_PSI51_CH2_ERR_IRQn = 414,       /**< PSI5 channel 2 error */
    RTU_PSI51_CH2_COMB_IRQn = 415, /**< PSI5 channel 2 combined interrupt- All PSI5 interrupts */
    RTU_PSI51_CH3_DMA_IRQn = 416,  /**< PSI5 channel 3 DMA combined interrupt- DMA transfer to SMC
                                      frame register complete, DMAtransfer complete, FIFO full, SMC
                                      frame, DMA undeflow, Data underflow */
    RTU_PSI51_CH3_GEN_INT_IRQn = 417,   /**< PSI5 channel 3 combined general interrupt- Received SMC
                                           message CRC error, Sync Pulse triggered timestamp value
                                           refreshed Timestamp vlaue updated by data start sequence,
                                           Data shift register overwrite, Buffer register overwrite,
                                           Data shift register ready for new data, Data preperation
                                           register ready for ew data, SMC message overwrite, New SMC
                                           frame register message available */
    RTU_PSI51_CH3_NEW_MSG_IRQn = 418,   /**< PSI5 channel 3 new message received */
    RTU_PSI51_CH3_MSG_OVRWR_IRQn = 419, /**< PSI5 channel 3 message overwrite */
    RTU_PSI51_CH3_ERR_IRQn = 420,       /**< PSI5 channel 3 error */
    RTU_PSI51_CH3_COMB_IRQn = 421,   /**< PSI5 channel 3 combined interrupt- All PSI5 interrupts */
    RTU_PSI5_S0_SR0_IRQn = 422,      /**< PS_SR_IRQ[0] */
    RTU_PSI5_S0_SR1_IRQn = 423,      /**< PS_SR_IRQ[1] */
    RTU_PSI5_S0_SR2_IRQn = 424,      /**< PS_SR_IRQ[2] */
    RTU_PSI5_S0_SR3_IRQn = 425,      /**< PS_SR_IRQ[3] */
    RTU_PSI5_S0_SR4_IRQn = 426,      /**< PS_SR_IRQ[4] */
    RTU_PSI5_S0_SR5_IRQn = 427,      /**< PS_SR_IRQ[5] */
    RTU_PSI5_S0_SR6_IRQn = 428,      /**< PS_SR_IRQ[6] */
    RTU_PSI5_S0_SR7_IRQn = 429,      /**< PS_SR_IRQ[7] */
    RTU_PSI5_S0_E2SSR1_IRQn = 430,   /**< PSI5_E2SSR[1] */
    RTU_PSI5_S0_E2SSR2_IRQn = 431,   /**< PSI5_E2SSR[2] */
    RTU_PSI5_S0_E2SSR3_IRQn = 432,   /**< PSI5_E2SSR[3] */
    RTU_PSI5_S0_E2SSR4_IRQn = 433,   /**< PSI5_E2SSR[4] */
    RTU_PSI5_S0_E2SSR5_IRQn = 434,   /**< PSI5_E2SSR[5] */
    RTU_PSI5_S0_E2SSR6_IRQn = 435,   /**< PSI5_E2SSR[6] */
    RTU_PSI5_S0_E2SSR7_IRQn = 436,   /**< PSI5_E2SSR[7] */
    RTU_PSI5_S0_GISR_IRQn = 437,     /**< PS_GLSR */
    RTU_PSI5_S0_UART_RX_IRQn = 438,  /**< PSI5_S_0_UART_RX */
    RTU_PSI5_S0_UART_TX_IRQn = 439,  /**< PSI5_S_0_UART_TX */
    RTU_PSI5_S0_UART_ERR_IRQn = 440, /**< PSI5_S_0_UART_ERR */
    RTU_PSI5_S1_SR0_IRQn = 441,      /**< PS_SR_IRQ[0] */
    RTU_PSI5_S1_SR1_IRQn = 442,      /**< PS_SR_IRQ[1] */
    RTU_PSI5_S1_SR2_IRQn = 443,      /**< PS_SR_IRQ[2] */
    RTU_PSI5_S1_SR3_IRQn = 444,      /**< PS_SR_IRQ[3] */
    RTU_PSI5_S1_SR4_IRQn = 445,      /**< PS_SR_IRQ[4] */
    RTU_PSI5_S1_SR5_IRQn = 446,      /**< PS_SR_IRQ[5] */
    RTU_PSI5_S1_SR6_IRQn = 447,      /**< PS_SR_IRQ[6] */
    RTU_PSI5_S1_SR7_IRQn = 448,      /**< PS_SR_IRQ[7] */
    RTU_PSI5_S1_E2SSR1_IRQn = 449,   /**< PSI5_E2SSR[1] */
    RTU_PSI5_S1_E2SSR2_IRQn = 450,   /**< PSI5_E2SSR[2] */
    RTU_PSI5_S1_E2SSR3_IRQn = 451,   /**< PSI5_E2SSR[3] */
    RTU_PSI5_S1_E2SSR4_IRQn = 452,   /**< PSI5_E2SSR[4] */
    RTU_PSI5_S1_E2SSR5_IRQn = 453,   /**< PSI5_E2SSR[5] */
    RTU_PSI5_S1_E2SSR6_IRQn = 454,   /**< PSI5_E2SSR[6] */
    RTU_PSI5_S1_E2SSR7_IRQn = 455,   /**< PSI5_E2SSR[7] */
    RTU_PSI5_S1_GISR_IRQn = 456,     /**< PS_GLSR */
    RTU_PSI5_S1_UART_RX_IRQn = 457,  /**< PSI5_S_0_UART_RX */
    RTU_PSI5_S1_UART_TX_IRQn = 458,  /**< PSI5_S_0_UART_TX */
    RTU_PSI5_S1_UART_ERR_IRQn = 459, /**< PSI5_S_0_UART_ERR */
    RTU_SRX0_COMBINED_FAST_0_IRQn = 460,  /**< SENT_COMBINED_FAST_0 */
    RTU_SRX0_COMBINED_SLOW_0_IRQn = 461,  /**< SENT_COMBINED_SLOW_0 */
    RTU_SRX0_COMBINED_ERR_0_IRQn = 462,   /**< SENT_COMBINED_ERR_0 */
    RTU_SRX0_CH0_FAST_IRQn = 463,         /**< SENT_CH0_FAST */
    RTU_SRX0_CH0_SLOW_IRQn = 464,         /**< SENT_CH0_SLOW */
    RTU_SRX0_CH0_CH0_ERR_IRQn = 465,      /**< SENT_CH0_ERR */
    RTU_SRX0_CH1_FAST_IRQn = 466,         /**< SENT_CH1_FAST */
    RTU_SRX0_CH1_SLOW_IRQn = 467,         /**< SENT_CH1_SLOW */
    RTU_SRX0_CH1_CH0_ERR_IRQn = 468,      /**< SENT_CH1_ERR */
    RTU_SRX0_CH2_FAST_IRQn = 469,         /**< SENT_CH2_FAST */
    RTU_SRX0_CH2_SLOW_IRQn = 470,         /**< SENT_CH2_SLOW */
    RTU_SRX0_CH2_CH0_ERR_IRQn = 471,      /**< SENT_CH2_ERR */
    RTU_SRX0_CH3_FAST_IRQn = 472,         /**< SENT_CH3_FAST */
    RTU_SRX0_CH3_SLOW_IRQn = 473,         /**< SENT_CH3_SLOW */
    RTU_SRX0_CH3_CH0_ERR_IRQn = 474,      /**< SENT_CH3_ERR */
    RTU_SRX0_CH4_FAST_IRQn = 475,         /**< SENT_CH4_FAST */
    RTU_SRX0_CH4_SLOW_IRQn = 476,         /**< SENT_CH4_SLOW */
    RTU_SRX0_CH4_CH0_ERR_IRQn = 477,      /**< SENT_CH4_ERR */
    RTU_SRX0_CH5_FAST_IRQn = 478,         /**< SENT_CH5_FAST */
    RTU_SRX0_CH5_SLOW_IRQn = 479,         /**< SENT_CH5_SLOW */
    RTU_SRX0_CH5_CH0_ERR_IRQn = 480,      /**< SENT_CH5_ERR */
    RTU_SRX0_CH6_FAST_IRQn = 481,         /**< SENT_CH6_FAST */
    RTU_SRX0_CH6_SLOW_IRQn = 482,         /**< SENT_CH6_SLOW */
    RTU_SRX0_CH6_CH0_ERR_IRQn = 483,      /**< SENT_CH6_ERR */
    RTU_SRX0_CH7_FAST_IRQn = 484,         /**< SENT_CH7_FAST */
    RTU_SRX0_CH7_SLOW_IRQn = 485,         /**< SENT_CH7_SLOW */
    RTU_SRX0_CH7_CH0_ERR_IRQn = 486,      /**< SENT_CH7_ERR */
    RTU_SRX1_COMBINED_FAST_0_IRQn = 487,  /**< SENT_COMBINED_FAST_0 */
    RTU_SRX1_COMBINED_SLOW_0_IRQn = 488,  /**< SENT_COMBINED_SLOW_0 */
    RTU_SRX1_COMBINED_ERR_0_IRQn = 489,   /**< SENT_COMBINED_ERR_0 */
    RTU_SRX1_CH0_FAST_IRQn = 490,         /**< SENT_CH0_FAST */
    RTU_SRX1_CH0_SLOW_IRQn = 491,         /**< SENT_CH0_SLOW */
    RTU_SRX1_CH0_CH0_ERR_IRQn = 492,      /**< SENT_CH0_ERR */
    RTU_SRX1_CH1_FAST_IRQn = 493,         /**< SENT_CH1_FAST */
    RTU_SRX1_CH1_SLOW_IRQn = 494,         /**< SENT_CH1_SLOW */
    RTU_SRX1_CH1_CH0_ERR_IRQn = 495,      /**< SENT_CH1_ERR */
    RTU_SRX1_CH2_FAST_IRQn = 496,         /**< SENT_CH2_FAST */
    RTU_SRX1_CH2_SLOW_IRQn = 497,         /**< SENT_CH2_SLOW */
    RTU_SRX1_CH2_CH0_ERR_IRQn = 498,      /**< SENT_CH2_ERR */
    RTU_SRX1_CH3_FAST_IRQn = 499,         /**< SENT_CH3_FAST */
    RTU_SRX1_CH3_SLOW_IRQn = 500,         /**< SENT_CH3_SLOW */
    RTU_SRX1_CH3_CH0_ERR_IRQn = 501,      /**< SENT_CH3_ERR */
    RTU_SRX1_CH4_FAST_IRQn = 502,         /**< SENT_CH4_FAST */
    RTU_SRX1_CH4_SLOW_IRQn = 503,         /**< SENT_CH4_SLOW */
    RTU_SRX1_CH4_CH0_ERR_IRQn = 504,      /**< SENT_CH4_ERR */
    RTU_SRX1_CH5_FAST_IRQn = 505,         /**< SENT_CH5_FAST */
    RTU_SRX1_CH5_SLOW_IRQn = 506,         /**< SENT_CH5_SLOW */
    RTU_SRX1_CH5_CH0_ERR_IRQn = 507,      /**< SENT_CH5_ERR */
    RTU_SRX1_CH6_FAST_IRQn = 508,         /**< SENT_CH6_FAST */
    RTU_SRX1_CH6_SLOW_IRQn = 509,         /**< SENT_CH6_SLOW */
    RTU_SRX1_CH6_CH0_ERR_IRQn = 510,      /**< SENT_CH6_ERR */
    RTU_SRX1_CH7_FAST_IRQn = 511,         /**< SENT_CH7_FAST */
    RTU_SRX1_CH7_SLOW_IRQn = 512,         /**< SENT_CH7_SLOW */
    RTU_SRX1_CH7_CH0_ERR_IRQn = 513,      /**< SENT_CH7_ERR */
    RTU_SIUL2_0_IRQn = 546,               /**< Logical OR of all pin interrupts */
    RTU_SIUL2_1_IRQn = 547,               /**< Logical OR of all pin interrupts */
    RTU_SIUL2_4_IRQn = 548,               /**< Logical OR of all pin interrupts */
    RTU_SIUL2_5_IRQn = 549,               /**< Logical OR of all pin interrupts */
    RTU_CE_eDMA_MP_DMA_ERR_IRQn = 550,    /**< DMA Error interrupt request */
    RTU_CE_eDMA_MP_CH_0_15_IRQn = 551,    /**< Interrupt for DMA Channels 0-15 */
    RTU_CE_eDMA_MP_CH_16_31_IRQn = 552,   /**< Interrupt for DMA Channels 16-31 */
    RTU_CE_eDMA_MP_CH0_IRQn = 553,        /**< DMA CH0 Interrupt req */
    RTU_CE_eDMA_MP_CH1_IRQn = 554,        /**< DMA CH1 Interrupt req */
    RTU_CE_eDMA_MP_CH2_IRQn = 555,        /**< DMA CH2 Interrupt req */
    RTU_CE_eDMA_MP_CH3_IRQn = 556,        /**< DMA CH3 Interrupt req */
    RTU_CE_eDMA_MP_CH4_IRQn = 557,        /**< DMA CH4 Interrupt req */
    RTU_CE_eDMA_MP_CH5_IRQn = 558,        /**< DMA CH5 Interrupt req */
    RTU_CE_eDMA_MP_CH6_IRQn = 559,        /**< DMA CH6 Interrupt req */
    RTU_CE_eDMA_MP_CH7_IRQn = 560,        /**< DMA CH7 Interrupt req */
    RTU_CE_eDMA_MP_CH8_IRQn = 561,        /**< DMA CH8 Interrupt req */
    RTU_CE_eDMA_MP_CH9_IRQn = 562,        /**< DMA CH9 Interrupt req */
    RTU_CE_eDMA_MP_CH10_IRQn = 563,       /**< DMA CH10 Interrupt req */
    RTU_CE_eDMA_MP_CH11_IRQn = 564,       /**< DMA CH11 Interrupt req */
    RTU_CE_eDMA_MP_CH12_IRQn = 565,       /**< DMA CH12 Interrupt req */
    RTU_CE_eDMA_MP_CH13_IRQn = 566,       /**< DMA CH13 Interrupt req */
    RTU_CE_eDMA_MP_CH14_IRQn = 567,       /**< DMA CH14 Interrupt req */
    RTU_CE_eDMA_MP_CH15_IRQn = 568,       /**< DMA CH15 Interrupt req */
    RTU_CE_eDMA_MP_CH16_IRQn = 569,       /**< DMA CH16 Interrupt req */
    RTU_CE_eDMA_MP_CH17_IRQn = 570,       /**< DMA CH17 Interrupt req */
    RTU_CE_eDMA_MP_CH18_IRQn = 571,       /**< DMA CH18 Interrupt req */
    RTU_CE_eDMA_MP_CH19_IRQn = 572,       /**< DMA CH19 Interrupt req */
    RTU_CE_eDMA_MP_CH20_IRQn = 573,       /**< DMA CH20 Interrupt req */
    RTU_CE_eDMA_MP_CH21_IRQn = 574,       /**< DMA CH21 Interrupt req */
    RTU_CE_eDMA_MP_CH22_IRQn = 575,       /**< DMA CH22 Interrupt req */
    RTU_CE_eDMA_MP_CH23_IRQn = 576,       /**< DMA CH23 Interrupt req */
    RTU_CE_eDMA_MP_CH24_IRQn = 577,       /**< DMA CH24 Interrupt req */
    RTU_CE_eDMA_MP_CH25_IRQn = 578,       /**< DMA CH25 Interrupt req */
    RTU_CE_eDMA_MP_CH26_IRQn = 579,       /**< DMA CH26 Interrupt req */
    RTU_CE_eDMA_MP_CH27_IRQn = 580,       /**< DMA CH27 Interrupt req */
    RTU_CE_eDMA_MP_CH28_IRQn = 581,       /**< DMA CH28 Interrupt req */
    RTU_CE_eDMA_MP_CH29_IRQn = 582,       /**< DMA CH29 Interrupt req */
    RTU_CE_eDMA_MP_CH30_IRQn = 583,       /**< DMA CH30 Interrupt req */
    RTU_CE_eDMA_MP_CH31_IRQn = 584,       /**< DMA CH31 Interrupt req */
    RTU_CE_MRU_COMB0_IRQn = 585,          /**< ORed interrupt0 from all MRUs */
    RTU_CE_MRU_COMB1_IRQn = 586,          /**< ORed interrupt1 from all MRUs */
    RTU_CE_MRU0_INT0_IRQn = 587,          /**< ORed interrupt1 from all MRUs */
    RTU_CE_MRU0_INT1_IRQn = 588,          /**< ORed interrupt1 from all MRUs */
    RTU_CE_MRU1_INT0_IRQn = 589,          /**< Interrupt0 */
    RTU_CE_MRU1_INT1_IRQn = 590,          /**< Interrupt1 */
    RTU_CE_MRU2_INT0_IRQn = 591,          /**< Interrupt0 */
    RTU_CE_MRU2_INT1_IRQn = 592,          /**< Interrupt1 */
    RTU_CE_MRU3_INT0_IRQn = 593,          /**< Interrupt0 */
    RTU_CE_MRU3_INT1_IRQn = 594,          /**< Interrupt1 */
    RTU_CE_MRU4_INT0_IRQn = 595,          /**< Interrupt0 */
    RTU_CE_MRU4_INT1_IRQn = 596,          /**< Interrupt1 */
    RTU_CE_MRU5_INT0_IRQn = 597,          /**< Interrupt0 */
    RTU_CE_MRU5_INT1_IRQn = 598,          /**< Interrupt1 */
    RTU_CE_CAN0_INIT_OR_ERROR_IRQn = 613, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN0_RXFIFO_DATA_IRQn = 614,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN0_MB_31_0_IRQn = 615,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN0_MB_63_32_IRQn = 616,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN0_MB_95_64_IRQn = 617,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN0_MB_127_96_IRQn = 618, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN1_INIT_OR_ERROR_IRQn = 619, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN1_RXFIFO_DATA_IRQn = 620,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN1_MB_31_0_IRQn = 621,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN1_MB_63_32_IRQn = 622,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN1_MB_95_64_IRQn = 623,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN1_MB_127_96_IRQn = 624, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN2_INIT_OR_ERROR_IRQn = 625, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN2_RXFIFO_DATA_IRQn = 626,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN2_MB_31_0_IRQn = 627,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN2_MB_63_32_IRQn = 628,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN2_MB_95_64_IRQn = 629,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN2_MB_127_96_IRQn = 630, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN3_INIT_OR_ERROR_IRQn = 631, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN3_RXFIFO_DATA_IRQn = 632,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN3_MB_31_0_IRQn = 633,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN3_MB_63_32_IRQn = 634,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN3_MB_95_64_IRQn = 635,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN3_MB_127_96_IRQn = 636, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN4_INIT_OR_ERROR_IRQn = 637, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN4_RXFIFO_DATA_IRQn = 638,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN4_MB_31_0_IRQn = 639,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN4_MB_63_32_IRQn = 640,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN4_MB_95_64_IRQn = 641,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN4_MB_127_96_IRQn = 642, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN5_INIT_OR_ERROR_IRQn = 643, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN5_RXFIFO_DATA_IRQn = 644,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN5_MB_31_0_IRQn = 645,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN5_MB_63_32_IRQn = 646,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN5_MB_95_64_IRQn = 647,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN5_MB_127_96_IRQn = 648, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN6_INIT_OR_ERROR_IRQn = 649, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN6_RXFIFO_DATA_IRQn = 650,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN6_MB_31_0_IRQn = 651,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN6_MB_63_32_IRQn = 652,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN6_MB_95_64_IRQn = 653,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN6_MB_127_96_IRQn = 654, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN7_INIT_OR_ERROR_IRQn = 655, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN7_RXFIFO_DATA_IRQn = 656,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN7_MB_31_0_IRQn = 657,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN7_MB_63_32_IRQn = 658,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN7_MB_95_64_IRQn = 659,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN7_MB_127_96_IRQn = 660, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN8_INIT_OR_ERROR_IRQn = 661, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN8_RXFIFO_DATA_IRQn = 662,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN8_MB_31_0_IRQn = 663,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN8_MB_63_32_IRQn = 664,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN8_MB_95_64_IRQn = 665,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN8_MB_127_96_IRQn = 666, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN9_INIT_OR_ERROR_IRQn = 667, /**< Interrupt indicating that the CAN bus went to Bus Off
                                             state, Interrupt indicating that the FlexCAN has
                                             completed the Bus Off count process (it has counted 11
                                             recessive bits 128 times) and is ready for bus off
                                             recover, Interrupt indicating Transmit Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating Receive Error Counter
                                             transition from less than 96 to greater than equal to
                                             96, Interrupt indicating that errors were detected on
                                             the CAN bus, Interrupt indicating that errors were
                                             detected on the CAN bus for FD messages in the Fast Bit
                                             Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                             Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN9_RXFIFO_DATA_IRQn = 668,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                             Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN9_MB_31_0_IRQn = 669,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN9_MB_63_32_IRQn = 670,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN9_MB_95_64_IRQn = 671,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN9_MB_127_96_IRQn = 672, /**< Logical OR of Message Buffer Interrupt lines 127 to 96 */
    RTU_CE_CAN10_INIT_OR_ERROR_IRQn = 673, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less  than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN10_RXFIFO_DATA_IRQn = 674,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN10_MB_31_0_IRQn = 675,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN10_MB_63_32_IRQn = 676,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN10_MB_95_64_IRQn = 677,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN10_MB_127_96_IRQn = 678, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN11_INIT_OR_ERROR_IRQn = 679, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN11_RXFIFO_DATA_IRQn = 680,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN11_MB_31_0_IRQn = 681,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN11_MB_63_32_IRQn = 682,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN11_MB_95_64_IRQn = 683,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN11_MB_127_96_IRQn = 684, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN12_INIT_OR_ERROR_IRQn = 685, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN12_RXFIFO_DATA_IRQn = 686,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN12_MB_31_0_IRQn = 687,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN12_MB_63_32_IRQn = 688,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN12_MB_95_64_IRQn = 689,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN12_MB_127_96_IRQn = 690, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN13_INIT_OR_ERROR_IRQn = 691, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN13_RXFIFO_DATA_IRQn = 692,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN13_MB_31_0_IRQn = 693,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN13_MB_63_32_IRQn = 694,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN13_MB_95_64_IRQn = 695,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN13_MB_127_96_IRQn = 696, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN14_INIT_OR_ERROR_IRQn = 697, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN14_RXFIFO_DATA_IRQn = 698,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN14_MB_31_0_IRQn = 699,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN14_MB_63_32_IRQn = 700,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN14_MB_95_64_IRQn = 701,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN14_MB_127_96_IRQn = 702, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN15_INIT_OR_ERROR_IRQn = 703, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN15_RXFIFO_DATA_IRQn = 704,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN15_MB_31_0_IRQn = 705,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN15_MB_63_32_IRQn = 706,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN15_MB_95_64_IRQn = 707,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN15_MB_127_96_IRQn = 708, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN16_INIT_OR_ERROR_IRQn = 709, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN16_RXFIFO_DATA_IRQn = 710,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN16_MB_31_0_IRQn = 711,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN16_MB_63_32_IRQn = 712,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN16_MB_95_64_IRQn = 713,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN16_MB_127_96_IRQn = 714, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN17_INIT_OR_ERROR_IRQn = 715, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN17_RXFIFO_DATA_IRQn = 716,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN17_MB_31_0_IRQn = 717,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN17_MB_63_32_IRQn = 718,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN17_MB_95_64_IRQn = 719,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN17_MB_127_96_IRQn = 720, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN18_INIT_OR_ERROR_IRQn = 721, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN18_RXFIFO_DATA_IRQn = 722,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN18_MB_31_0_IRQn = 723,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN18_MB_63_32_IRQn = 724,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN18_MB_95_64_IRQn = 725,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN18_MB_127_96_IRQn = 726, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN19_INIT_OR_ERROR_IRQn = 727, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN19_RXFIFO_DATA_IRQn = 728,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN19_MB_31_0_IRQn = 729,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN19_MB_63_32_IRQn = 730,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN19_MB_95_64_IRQn = 731,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN19_MB_127_96_IRQn = 732, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN20_INIT_OR_ERROR_IRQn = 733, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN20_RXFIFO_DATA_IRQn = 734,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN20_MB_31_0_IRQn = 735,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN20_MB_63_32_IRQn = 736,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN20_MB_95_64_IRQn = 737,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN20_MB_127_96_IRQn = 738, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN21_INIT_OR_ERROR_IRQn = 739, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN21_RXFIFO_DATA_IRQn = 740,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN21_MB_31_0_IRQn = 741,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN21_MB_63_32_IRQn = 742,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN21_MB_95_64_IRQn = 743,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN21_MB_127_96_IRQn = 744, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN22_INIT_OR_ERROR_IRQn = 745, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN22_RXFIFO_DATA_IRQn = 746,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN22_MB_31_0_IRQn = 747,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN22_MB_63_32_IRQn = 748,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN22_MB_95_64_IRQn = 749,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN22_MB_127_96_IRQn = 750, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_CE_CAN23_INIT_OR_ERROR_IRQn = 751, /**< Interrupt indicating that the CAN bus went to Bus
                                              Off state, Interrupt indicating that the FlexCAN has
                                              completed the Bus Off count process (it has counted 11
                                              recessive bits 128 times) and is ready for bus off
                                              recover, Interrupt indicating Transmit Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating Receive Error Counter
                                              transition from less than 96 to greater than equal to
                                              96, Interrupt indicating that errors were detected on
                                              the CAN bus, Interrupt indicating that errors were
                                              detected on the CAN bus for FD messages in the Fast
                                              Bit Rate region, Enhanced Rx FIFO Underflow Interrupt,
                                              Enhanced Rx FIFO Overflow Interrupt */
    RTU_CE_CAN23_RXFIFO_DATA_IRQn = 752,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                              Enhanced Rx FIFO Data Available Interrupt */
    RTU_CE_CAN23_MB_31_0_IRQn = 753,   /**< Logical OR of Message Buffer Interrupt lines 31 to 0 */
    RTU_CE_CAN23_MB_63_32_IRQn = 754,  /**< Logical OR of Message Buffer Interrupt lines 63 to 32 */
    RTU_CE_CAN23_MB_95_64_IRQn = 755,  /**< Logical OR of Message Buffer Interrupt lines 95 to 64 */
    RTU_CE_CAN23_MB_127_96_IRQn = 756, /**< Logical OR of Message Buffer Interrupt lines 127 to 96
                                        */
    RTU_AES_APP_0_IRQn = 757,          /**< app_ipi_int[0] */
    RTU_AES_APP_1_IRQn = 758,          /**< app_ipi_int[1] */
    RTU_AES_APP_2_IRQn = 759,          /**< app_ipi_int[2] */
    RTU_AES_APP_3_IRQn = 760,          /**< app_ipi_int[3] */
    RTU_AES_APP_4_IRQn = 761,          /**< app_ipi_int[4] */
    RTU_AES_APP_5_IRQn = 762,          /**< app_ipi_int[5] */
    RTU_AES_APP_6_IRQn = 763,          /**< app_ipi_int[6] */
    RTU_AES_APP_7_IRQn = 764,          /**< app_ipi_int[7] */
    RTU_AES_FEED_DMA_ERR_IRQn = 765,   /**< feed_dma_ipi_err_int */
    RTU_AES_RESULT_DMA_ERR_INT_IRQn = 766, /**< result_dma_ipi_err_int */
    RTU_SIPI0_CH1_IRQn = 767,              /**< Read interrupt channel 1 */
    RTU_SIPI0_CH2_IRQn = 768,              /**< Read interrupt channel 2 */
    RTU_SIPI0_CH3_IRQn = 769,              /**< Read interrupt channel 3 */
    RTU_SIPI0_CH4_IRQn = 770,              /**< Read interrupt channel 4 */
    RTU_SIPI0_TRIG_IRQn = 771,             /**< Trigger command interrupt */
    RTU_SIPI0_ERR1_IRQn = 772,             /**< Error interrupt 1 */
    RTU_SIPI0_ERR2_IRQn = 773,             /**< Error interrupt 2 */
    RTU_LFAST0_TX_IRQn = 774,              /**< Tx interrupt */
    RTU_LFAST0_TX_EXP_IRQn = 775,          /**< Tx exception */
    RTU_LFAST0_RX_IRQn = 776,              /**< Rx interrupt */
    RTU_LFAST0_RX_EXP_IRQn = 777,          /**< Rx exception */
    RTU_LFAST0_ICLC_RX_IRQn = 778,         /**< ICLC Rx interrupt */
    RTU_SIPI1_CH1_IRQn = 779,              /**< Read interrupt channel 1 */
    RTU_SIPI1_CH2_IRQn = 780,              /**< Read interrupt channel 2 */
    RTU_SIPI1_CH3_IRQn = 781,              /**< Read interrupt channel 3 */
    RTU_SIPI1_CH4_IRQn = 782,              /**< Read interrupt channel 4 */
    RTU_SIPI1_TRIG_IRQn = 783,             /**< Trigger command interrupt */
    RTU_SIPI1_ERR1_IRQn = 784,             /**< Error interrupt 1 */
    RTU_SIPI1_ERR2_IRQn = 785,             /**< Error interrupt 2 */
    RTU_LFAST1_TX_IRQn = 786,              /**< Tx interrupt */
    RTU_LFAST1_TX_EXP_IRQn = 787,          /**< Tx exception */
    RTU_LFAST1_RX_IRQn = 788,              /**< Rx interrupt */
    RTU_LFAST1_RX_EXP_IRQn = 789,          /**< Rx exception */
    RTU_LFAST1_ICLC_RX_IRQn = 790,         /**< ICLC Rx interrupt */
    RTU_GTM_AEI_IRQn = 791,                /**< GTM_AEI_IRQ AEI Shared interrupt */
    RTU_GTM_ARU0_IRQn = 792,               /**< GTM_ARU_IRQ[0] */
    RTU_GTM_ARU1_IRQn = 793,               /**< GTM_ARU_IRQ[1] */
    RTU_GTM_ARU2_IRQn = 794,               /**< GTM_ARU_IRQ[2] */
    RTU_GTM_BRC_IRQn = 795,                /**< GTM_BRC_IRQ BRC Shared interrupt */
    RTU_GTM_CMP_IRQn = 796,                /**< GTM_CMP_IRQ CMP Shared interrupt */
    RTU_GTM_TIM0_IRQn = 797,               /**< GTM_TIM[0]_IRQ[x] TIM Shared interrupts */
    RTU_GTM_TIM1_IRQn = 798,               /**< GTM_TIM[1]_IRQ[x] TIM Shared interrupts */
    RTU_GTM_TIM2_IRQn = 799,               /**< GTM_TIM[2]_IRQ[x] TIM Shared interrupts */
    RTU_GTM_MCS0_IRQn = 800,               /**< GTM_MCS[0]_IRQ[x] MCS Interrupt for channel x  */
    RTU_GTM_MCS1_IRQn = 801,               /**< GTM_MCS[1]_IRQ[x] MCS Interrupt for channel x  */
    RTU_GTM_MCS2_IRQn = 802,               /**< GTM_MCS[2]_IRQ[x] MCS Interrupt for channel x  */
    RTU_GTM_MCS3_IRQn = 803,               /**< GTM_MCS[3]_IRQ[x] MCS Interrupt for channel x  */
    RTU_GTM_TOM0_IRQn = 804,          /**< GTM_TOM[0]_IRQ[x] TOM Shared interrupts for x:0..7 */
    RTU_GTM_TOM1_IRQn = 805,          /**< GTM_TOM[1]_IRQ[x] TOM Shared interrupts for x:0..7 */
    RTU_GTM_ATOM0_IRQn = 806,         /**< GTM_ATOM[0]_IRQ[x] ATOM Shared interrupts */
    RTU_GTM_ATOM1_IRQn = 807,         /**< GTM_ATOM[1]_IRQ[x] ATOM Shared interrupts */
    RTU_GTM_ATOM2_IRQn = 808,         /**< GTM_ATOM[2]_IRQ[x] ATOM Shared interrupts */
    RTU_GTM_ATOM3_IRQn = 809,         /**< GTM_ATOM[3]_IRQ[x] ATOM Shared interrupts */
    RTU_GTM_TIO0_IRQn = 810,          /**< GTM_TIO[0] Timer Input/Output interrupts */
    RTU_GTM_TIO1_IRQn = 811,          /**< GTM_TIO[1] Timer Input/Output interrupts */
    RTU_GTM_TIO2_IRQn = 812,          /**< GTM_TIO[2] Timer Input/Output interrupts */
    RTU_GTM_DPLL_IRQn = 813,          /**< GTM_DPLL interrupt */
    RTU_GTM_FIFO0_IRQn = 814,         /**< GTM_FIFO_0 interrupt */
    RTU_GTM_SPE0_IRQn = 815,          /**< GTM_SPE[0] interrupt */
    RTU_GTM_SPE1_IRQn = 816,          /**< GTM_SPE[1] interrupt */
    RTU_GTM_ERR_IRQn = 817,           /**< GTM_ERR_IRQ GTM Error Interrupt */
    RTU_GTM_DPLL_CDSI_IRQn = 818,     /**< GTM_DPLL_CDSI_IRQ */
    RTU_GTM_DPLL_CDTI_IRQn = 819,     /**< GTM_DPLL_CDTI_IRQ */
    RTU_GTM_DPLL_TE0_IRQn = 820,      /**< GTM_DPLL_TE0_IRQ */
    RTU_DEBUG_TRACE_NW_IRQn = 828,    /**< s250_dbg_trace_nw.dbg_cti2_irq_out */
    RTU_DEBUG_TRACE_NORTH_IRQn = 829, /**< s250_dbg_trace_north.dbg_etrf_bufirq */
    RTU_CTU_FIFO_3_0_IRQn = 832, /**< FIFO0 full  or empty or overflow or overrun interrupt, FIFO1
                                    full  or empty or overflow or overrun interrupt, FIFO2 full  or
                                    empty or overflow or overrun interrupt, FIFO3 full  or empty or
                                    overflow or overrun interrupt */
    RTU_CTU_FIFO_MAS_RELOAD_IRQn = 833, /**< Master reload interrupt */
    RTU_CTU_TRIG_IRQn = 834,    /**< Trigger0 interrupt, Trigger1 interrupt, Trigger2 interrupt,
                                   Trigger3 interrupt, Trigger4 interrupt, Trigger5 interrupt, Trigger6
                                   interrupt, Trigger7 interrupt */
    RTU_CTU_ADC_CMD_IRQn = 835, /**< ADC command interrupt */
    RTU_CTU_ERR_IRQn = 836,     /**< CTU_ERR_INT */
    RTU_CEVA_SPF2_IRQn = 837,   /**< cevasp_gpout[0] */
    RTU_XRDC0_IRQn = 838,       /**< xRDC_INT0 */
    RTU_XRDC1_IRQn = 839,       /**< xRDC_INT1 */
    RTU_XRDC2_IRQn = 840,       /**< xRDC_INT2 */
    RTU_SINC_CH0_IRQn = 841,    /**< ipi_chn_ored_int[0] */
    RTU_SINC_CH1_IRQn = 842,    /**< ipi_chn_ored_int[1] */
    RTU_SINC_CH2_IRQn = 843,    /**< ipi_chn_ored_int[2] */
    RTU_SINC_CH3_IRQn = 844,    /**< ipi_chn_ored_int[3] */
    RTU_MEW_INT0_IRQn = 845,    /**< system_int */
    RTU_MEW_INT1_IRQn = 846,    /**< system_int */
    RTU_CMU_FC_2A_IRQn = 847,   /**< async_fhh_evt | async_fll_evt */
    RTU_NoC_IRQn = 848          /**< ne_noc_alarm_or.intg_out | north_noc_alarm_or.intg_out |
                                   system_noc.m_rtu0_llc_req_mainStatAlarm
                                   |system_noc.m_rtu0_llc_resp_mainStatAlarm |
                                   system_noc.m_rtu1_llc_req_mainStatAlarm
                                   |system_noc.m_rtu1_llc_resp_mainStatAlarm */
} RTU_IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */

/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define FLEXLLCE_NUMBER_OF_INT_VECTORS 381 /**< Number of interrupts in the Vector table */

typedef enum {
    /* Auxiliary constants */
    FLEXLLCE_NotAvail_IRQn = -128, /**< Not available device specific interrupt */

    /* Device specific interrupts */
    FLEXLLCE_CE_SWT0_IRQn = 0,                 /**< Platform watchdog initial timeout */
    FLEXLLCE_CE_STM0_IRQn = 1,                 /**< Single vector for all 4 channels */
    FLEXLLCE_Core0_CTI_0_IRQn = 2,             /**< Core0_CTI0 Interrupt */
    FLEXLLCE_Core0_CTI_1_IRQn = 3,             /**< Core0_CTI1 Interrupt */
    FLEXLLCE_Core0_CE_MCM_IRQn = 4,            /**< Core0_CE_MCM Interrupt */
    FLEXLLCE_CE_SWT1_IRQn = 10,                /**< Platform watchdog initial timeout */
    FLEXLLCE_CE_STM1_IRQn = 11,                /**< Single vector for all 4 channels */
    FLEXLLCE_Core1_CTI_0_IRQn = 12,            /**< Core0_CTI0 Interrupt */
    FLEXLLCE_Core1_CTI_1_IRQn = 13,            /**< Core0_CTI1 Interrupt */
    FLEXLLCE_Core1_CE_MCM_IRQn = 14,           /**< Core0_CE_MCM Interrupt */
    FLEXLLCE_CE_CMU_FC0_IRQn = 20,             /**< Error Injection Complete */
    FLEXLLCE_CE_CMU_FC1_IRQn = 21,             /**< Fault Injection Complete */
    FLEXLLCE_CE_STM2_IRQn = 22,                /**< Single vector for all 4 channels */
    FLEXLLCE_CE_ERM2_Single_ECC_ERR_IRQn = 24, /**< Single-bit ECC error */
    FLEXLLCE_CE_ERM2_Multi_ECC_ERR_IRQn = 25,  /**< Multi-bit ECC error */
    FLEXLLCE_CE_ERM0_Single_ECC_ERR_IRQn = 26, /**< Single-bit ECC error */
    FLEXLLCE_CE_ERM0_Multi_ECC_ERR_IRQn = 27,  /**< Multi-bit ECC error */
    FLEXLLCE_CE_ERM1_Single_ECC_ERR_IRQn = 28, /**< Single-bit ECC error */
    FLEXLLCE_CE_ERM1_Multi_ECC_ERR_IRQn = 29,  /**< Multi-bit ECC error */
    FLEXLLCE_CE_XRDC_IRQn = 31,                /**< XRDC.TBD Error Interrupt */
    FLEXLLCE_C_VFCCU_INDEX0_IRQn = 40,         /**< Central FCCU reaction index0 */
    FLEXLLCE_C_VFCCU_INDEX1_IRQn = 41,         /**< Central FCCU reaction index0 */
    FLEXLLCE_C_VFCCU_INDEX2_IRQn = 42,         /**< Central FCCU reaction index0 */
    FLEXLLCE_C_VFCCU_INDEX3_IRQn = 43,         /**< Central FCCU reaction index0 */
    FLEXLLCE_CE_eDMA_ERR_IRQn = 48,            /**< DMA Error interrupt request */
    FLEXLLCE_CE_eDMA_CH0_IRQn = 49,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH1_IRQn = 50,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH2_IRQn = 51,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH3_IRQn = 52,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH4_IRQn = 53,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH5_IRQn = 54,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH6_IRQn = 55,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH7_IRQn = 56,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH8_IRQn = 57,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH9_IRQn = 58,            /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH10_IRQn = 59,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH11_IRQn = 60,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH12_IRQn = 61,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH13_IRQn = 62,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH14_IRQn = 63,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH15_IRQn = 64,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH16_IRQn = 65,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH17_IRQn = 66,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH18_IRQn = 67,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH19_IRQn = 68,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH20_IRQn = 69,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH21_IRQn = 70,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH22_IRQn = 71,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH23_IRQn = 72,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH24_IRQn = 73,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH25_IRQn = 74,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH26_IRQn = 75,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH27_IRQn = 76,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH28_IRQn = 77,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH29_IRQn = 78,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH30_IRQn = 79,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_eDMA_CH31_IRQn = 80,           /**< DMA CH0 Interrupt req */
    FLEXLLCE_CE_MRU0_INT0_IRQn = 81,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU0_INT1_IRQn = 82,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU1_INT0_IRQn = 83,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU1_INT1_IRQn = 84,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU2_INT0_IRQn = 85,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU2_INT1_IRQn = 86,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU3_INT0_IRQn = 87,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU3_INT1_IRQn = 88,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU4_INT0_IRQn = 89,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU4_INT1_IRQn = 90,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU5_INT0_IRQn = 91,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU5_INT1_IRQn = 92,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU6_INT0_IRQn = 93,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU6_INT1_IRQn = 94,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU7_INT0_IRQn = 95,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU7_INT1_IRQn = 96,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU8_INT0_IRQn = 97,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU8_INT1_IRQn = 98,           /**< Interrupt1 */
    FLEXLLCE_CE_MRU9_INT0_IRQn = 99,           /**< Interrupt0 */
    FLEXLLCE_CE_MRU9_INT1_IRQn = 100,          /**< Interrupt1 */
    FLEXLLCE_CE_MRU10_INT0_IRQn = 101,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU10_INT1_IRQn = 102,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU11_INT0_IRQn = 103,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU11_INT1_IRQn = 104,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU12_INT0_IRQn = 105,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU12_INT1_IRQn = 106,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU13_INT0_IRQn = 107,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU13_INT1_IRQn = 108,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU14_INT0_IRQn = 109,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU14_INT1_IRQn = 110,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU15_INT0_IRQn = 111,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU15_INT1_IRQn = 112,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU16_INT0_IRQn = 113,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU16_INT1_IRQn = 114,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU17_INT0_IRQn = 115,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU17_INT1_IRQn = 116,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU18_INT0_IRQn = 117,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU18_INT1_IRQn = 118,         /**< Interrupt1 */
    FLEXLLCE_CE_MRU19_INT0_IRQn = 119,         /**< Interrupt0 */
    FLEXLLCE_CE_MRU19_INT1_IRQn = 120,         /**< Interrupt1 */
    FLEXLLCE_CE_PIT0_CH_0_IRQn = 121,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT0_CH_1_IRQn = 122,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT0_CH_2_IRQn = 123,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT0_CH_3_IRQn = 124,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_PIT1_CH_0_IRQn = 125,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT1_CH_1_IRQn = 126,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT1_CH_2_IRQn = 127,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT1_CH_3_IRQn = 128,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_PIT2_CH_0_IRQn = 129,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT2_CH_1_IRQn = 130,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT2_CH_2_IRQn = 131,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT2_CH_3_IRQn = 132,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_PIT3_CH_0_IRQn = 133,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT3_CH_1_IRQn = 134,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT3_CH_2_IRQn = 135,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT3_CH_3_IRQn = 136,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_PIT4_CH_0_IRQn = 137,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT4_CH_1_IRQn = 138,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT4_CH_2_IRQn = 139,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT4_CH_3_IRQn = 140,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_PIT5_CH_0_IRQn = 141,          /**< Interrupt for Channel0 */
    FLEXLLCE_CE_PIT5_CH_1_IRQn = 142,          /**< Interrupt for Channel1 */
    FLEXLLCE_CE_PIT5_CH_2_IRQn = 143,          /**< Interrupt for Channel2 */
    FLEXLLCE_CE_PIT5_CH_3_IRQn = 144,          /**< Interrupt for Channel3 */
    FLEXLLCE_CE_CAN0_INIT_OR_ERROR_IRQn = 145, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN0_RXFIFO_DATA_IRQn = 146,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN0_MB_31_0_IRQn = 147,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN0_MB_63_32_IRQn = 148, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN0_MB_95_64_IRQn = 149, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN0_MB_127_96_IRQn = 150, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN1_INIT_OR_ERROR_IRQn = 151, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN1_RXFIFO_DATA_IRQn = 152,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN1_MB_31_0_IRQn = 153,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN1_MB_63_32_IRQn = 154, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN1_MB_95_64_IRQn = 155, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN1_MB_127_96_IRQn = 156, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN2_INIT_OR_ERROR_IRQn = 157, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN2_RXFIFO_DATA_IRQn = 158,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN2_MB_31_0_IRQn = 159,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN2_MB_63_32_IRQn = 160, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN2_MB_95_64_IRQn = 161, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN2_MB_127_96_IRQn = 162, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN3_INIT_OR_ERROR_IRQn = 163, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN3_RXFIFO_DATA_IRQn = 164,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN3_MB_31_0_IRQn = 165,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN3_MB_63_32_IRQn = 166, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN3_MB_95_64_IRQn = 167, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN3_MB_127_96_IRQn = 168, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN4_INIT_OR_ERROR_IRQn = 169, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN4_RXFIFO_DATA_IRQn = 170,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN4_MB_31_0_IRQn = 171,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN4_MB_63_32_IRQn = 172, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN4_MB_95_64_IRQn = 173, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN4_MB_127_96_IRQn = 174, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN5_INIT_OR_ERROR_IRQn = 175, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN5_RXFIFO_DATA_IRQn = 176,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN5_MB_31_0_IRQn = 177,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN5_MB_63_32_IRQn = 178, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN5_MB_95_64_IRQn = 179, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN5_MB_127_96_IRQn = 180, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN6_INIT_OR_ERROR_IRQn = 181, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN6_RXFIFO_DATA_IRQn = 182,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN6_MB_31_0_IRQn = 183,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN6_MB_63_32_IRQn = 184, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN6_MB_95_64_IRQn = 185, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN6_MB_127_96_IRQn = 186, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN7_INIT_OR_ERROR_IRQn = 187, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN7_RXFIFO_DATA_IRQn = 188,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN7_MB_31_0_IRQn = 189,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN7_MB_63_32_IRQn = 190, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN7_MB_95_64_IRQn = 191, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN7_MB_127_96_IRQn = 192, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN8_INIT_OR_ERROR_IRQn = 193, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN8_RXFIFO_DATA_IRQn = 194,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN8_MB_31_0_IRQn = 195,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN8_MB_63_32_IRQn = 196, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN8_MB_95_64_IRQn = 197, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN8_MB_127_96_IRQn = 198, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN9_INIT_OR_ERROR_IRQn = 199, /**< Interrupt indicating that the CAN bus went to
                                                  Bus Off state, Interrupt indicating that the
                                                  FlexCAN has completed the Bus Off count process
                                                  (it has counted 11 recessive bits 128 times) and
                                                  is ready for bus off recover, Interrupt indicating
                                                  Transmit Error Counter transition from less than
                                                  96 to greater than equal to 96, Interrupt
                                                  indicating Receive Error Counter transition from
                                                  less than 96 to greater than equal to 96,
                                                  Interrupt indicating that errors were detected on
                                                  the CAN bus, Interrupt indicating that errors were
                                                  detected on the CAN bus for FD messages in the
                                                  Fast Bit Rate region, Enhanced Rx FIFO Underflow
                                                  Interrupt, Enhanced Rx FIFO Overflow Interrupt */
    FLEXLLCE_CE_CAN9_RXFIFO_DATA_IRQn = 200,   /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                  Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN9_MB_31_0_IRQn = 201,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                           */
    FLEXLLCE_CE_CAN9_MB_63_32_IRQn = 202, /**< Logical OR of Message Buffer Interrupt lines 63 to 32
                                           */
    FLEXLLCE_CE_CAN9_MB_95_64_IRQn = 203, /**< Logical OR of Message Buffer Interrupt lines 95 to 64
                                           */
    FLEXLLCE_CE_CAN9_MB_127_96_IRQn = 204, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                              96 */
    FLEXLLCE_CE_CAN10_INIT_OR_ERROR_IRQn =
        205, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN10_RXFIFO_DATA_IRQn = 206, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN10_MB_31_0_IRQn = 207,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN10_MB_63_32_IRQn = 208, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN10_MB_95_64_IRQn = 209, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN10_MB_127_96_IRQn = 210, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN11_INIT_OR_ERROR_IRQn =
        211, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN11_RXFIFO_DATA_IRQn = 212, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN11_MB_31_0_IRQn = 213,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN11_MB_63_32_IRQn = 214, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN11_MB_95_64_IRQn = 215, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN11_MB_127_96_IRQn = 216, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN12_INIT_OR_ERROR_IRQn =
        217, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN12_RXFIFO_DATA_IRQn = 218, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN12_MB_31_0_IRQn = 219,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN12_MB_63_32_IRQn = 220, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN12_MB_95_64_IRQn = 221, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN12_MB_127_96_IRQn = 222, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN13_INIT_OR_ERROR_IRQn =
        223, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN13_RXFIFO_DATA_IRQn = 224, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN13_MB_31_0_IRQn = 225,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN13_MB_63_32_IRQn = 226, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN13_MB_95_64_IRQn = 227, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN13_MB_127_96_IRQn = 228, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN14_INIT_OR_ERROR_IRQn =
        229, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN14_RXFIFO_DATA_IRQn = 230, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN14_MB_31_0_IRQn = 231,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN14_MB_63_32_IRQn = 232, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN14_MB_95_64_IRQn = 233, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN14_MB_127_96_IRQn = 234, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN15_INIT_OR_ERROR_IRQn =
        235, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN15_RXFIFO_DATA_IRQn = 236, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN15_MB_31_0_IRQn = 237,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN15_MB_63_32_IRQn = 238, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN15_MB_95_64_IRQn = 239, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN15_MB_127_96_IRQn = 240, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN16_INIT_OR_ERROR_IRQn =
        241, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN16_RXFIFO_DATA_IRQn = 242, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN16_MB_31_0_IRQn = 243,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN16_MB_63_32_IRQn = 244, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN16_MB_95_64_IRQn = 245, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN16_MB_127_96_IRQn = 246, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN17_INIT_OR_ERROR_IRQn =
        247, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN17_RXFIFO_DATA_IRQn = 248, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN17_MB_31_0_IRQn = 249,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN17_MB_63_32_IRQn = 250, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN17_MB_95_64_IRQn = 251, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN17_MB_127_96_IRQn = 252, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN18_INIT_OR_ERROR_IRQn =
        253, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN18_RXFIFO_DATA_IRQn = 254, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN18_MB_31_0_IRQn = 255,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN18_MB_63_32_IRQn = 256, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN18_MB_95_64_IRQn = 257, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN18_MB_127_96_IRQn = 258, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN19_INIT_OR_ERROR_IRQn =
        259, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN19_RXFIFO_DATA_IRQn = 260, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN19_MB_31_0_IRQn = 261,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN19_MB_63_32_IRQn = 262, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN19_MB_95_64_IRQn = 263, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN19_MB_127_96_IRQn = 264, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN20_INIT_OR_ERROR_IRQn =
        265, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN20_RXFIFO_DATA_IRQn = 266, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN20_MB_31_0_IRQn = 267,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN20_MB_63_32_IRQn = 268, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN20_MB_95_64_IRQn = 269, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN20_MB_127_96_IRQn = 270, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN21_INIT_OR_ERROR_IRQn =
        271, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN21_RXFIFO_DATA_IRQn = 272, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN21_MB_31_0_IRQn = 273,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN21_MB_63_32_IRQn = 274, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN21_MB_95_64_IRQn = 275, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN21_MB_127_96_IRQn = 276, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN22_INIT_OR_ERROR_IRQn =
        277, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN22_RXFIFO_DATA_IRQn = 278, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN22_MB_31_0_IRQn = 279,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN22_MB_63_32_IRQn = 280, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN22_MB_95_64_IRQn = 281, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN22_MB_127_96_IRQn = 282, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_CE_CAN23_INIT_OR_ERROR_IRQn =
        283, /**< Interrupt indicating that the CAN bus went to Bus Off state, Interrupt indicating
                that the FlexCAN has completed the Bus Off count process (it has counted 11
                recessive bits 128 times) and is ready for bus off recover, Interrupt indicating
                Transmit Error Counter transition from less than 96 to greater than equal to 96,
                Interrupt indicating Receive Error Counter transition from less than 96 to greater
                than equal to 96, Interrupt indicating that errors were detected on the CAN bus,
                Interrupt indicating that errors were detected on the CAN bus for FD messages in the
                Fast Bit Rate region, Enhanced Rx FIFO Underflow Interrupt, Enhanced Rx FIFO
                Overflow Interrupt */
    FLEXLLCE_CE_CAN23_RXFIFO_DATA_IRQn = 284, /**< Enhanced Rx FIFO Watermark Indication Interrupt,
                                                 Enhanced Rx FIFO Data Available Interrupt */
    FLEXLLCE_CE_CAN23_MB_31_0_IRQn = 285,  /**< Logical OR of Message Buffer Interrupt lines 31 to 0
                                            */
    FLEXLLCE_CE_CAN23_MB_63_32_IRQn = 286, /**< Logical OR of Message Buffer Interrupt lines 63 to
                                              32 */
    FLEXLLCE_CE_CAN23_MB_95_64_IRQn = 287, /**< Logical OR of Message Buffer Interrupt lines 95 to
                                              64 */
    FLEXLLCE_CE_CAN23_MB_127_96_IRQn = 288, /**< Logical OR of Message Buffer Interrupt lines 127 to
                                               96 */
    FLEXLLCE_AES_APP_0_IRQn = 289,          /**< app_ipi_int[0] */
    FLEXLLCE_AES_APP_1_IRQn = 290,          /**< app_ipi_int[1] */
    FLEXLLCE_AES_APP_2_IRQn = 291,          /**< app_ipi_int[2] */
    FLEXLLCE_AES_APP_3_IRQn = 292,          /**< app_ipi_int[3] */
    FLEXLLCE_AES_APP_4_IRQn = 293,          /**< app_ipi_int[4] */
    FLEXLLCE_AES_APP_5_IRQn = 294,          /**< app_ipi_int[5] */
    FLEXLLCE_AES_APP_6_IRQn = 295,          /**< app_ipi_int[6] */
    FLEXLLCE_AES_APP_7_IRQn = 296,          /**< app_ipi_int[7] */
    FLEXLLCE_AES_FEED_DMA_ERR_IRQn = 297,   /**< afeed_dma_ipi_err_int */
    FLEXLLCE_AES_RESULT_DMA_ERR_INT_IRQn = 298, /**< afeed_dma_ipi_err_int */
    FLEXLLCE_CE_RXLUT_IRQn = 299,               /**< ipi_int_rxlut */
    FLEXLLCE_CANXL0_INT_TX_MB_1_IRQn = 300, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 0-31 completed */
    FLEXLLCE_CANXL0_INT_TX_MB_2_IRQn = 301, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 32-63 completed */
    FLEXLLCE_CANXL0_INT_RX_MB_1_IRQn = 302, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 0-31 completed */
    FLEXLLCE_CANXL0_INT_RX_MB_2_IRQn = 303, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 32-63 completed */
    FLEXLLCE_CANXL0_INT_RX_FIFO_IRQn = 304, /**< CANXL: the Rx FIFO used for reception of selected
                                               CAN frames has reached its programmeble threshold. */
    FLEXLLCE_CANXL0_INT_MRU_IRQn = 305, /**< CANXL: interrupt from CANXL Message Recveive Unit */
    FLEXLLCE_CANXL0_INT_RX_TX_ERR_IRQn = 306, /**< CANXL: protocol engine error occured related to
                                                 reception or transmission of CAN frames. */
    FLEXLLCE_CANXL0_INT_INTERNAL_ERR_IRQn = 307, /**< CANXL: internal exception is detected */
    FLEXLLCE_CANXL0_INT_LRAM_ECC_NOCORR_ERR_IRQn = 308, /**< CANXL: non-correctable error occured
                                                           within  internal data RAM  */
    FLEXLLCE_CANXL0_INT_RAM_ECC_CORR_ERR_IRQn = 310,    /**< CANXL: correctable error occured within
                                                           internal data RAM or code RAM */
    FLEXLLCE_CANXL0_INT_FREEZE_IRQn = 311,  /**< CANXL: IP has entered or exited freeze mode */
    FLEXLLCE_CANXL1_INT_TX_MB_1_IRQn = 312, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 0-31 completed */
    FLEXLLCE_CANXL1_INT_TX_MB_2_IRQn = 313, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 32-63 completed */
    FLEXLLCE_CANXL1_INT_RX_MB_1_IRQn = 314, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 0-31 completed */
    FLEXLLCE_CANXL1_INT_RX_MB_2_IRQn = 315, /**< CANXL: CAN frame transmission from one of the Tx
                                               message buffers 32-63 completed */
    FLEXLLCE_CANXL1_INT_RX_FIFO_IRQn = 316, /**< CANXL: the Rx FIFO used for reception of selected
                                               CAN frames has reached its programmeble threshold. */
    FLEXLLCE_CANXL1_INT_MRU_IRQn = 317, /**< CANXL: interrupt from CANXL Message Recveive Unit */
    FLEXLLCE_CANXL1_INT_RX_TX_ERR_IRQn = 318, /**< CANXL: protocol engine error occured related to
                                                 reception or transmission of CAN frames. */
    FLEXLLCE_CANXL1_INT_INTERNAL_ERR_IRQn = 319, /**< CANXL: internal exception is detected */
    FLEXLLCE_CANXL1_INT_LRAM_ECC_NOCORR_ERR_IRQn = 320, /**< CANXL: non-correctable error occured
                                                           within  internal data RAM  */
    FLEXLLCE_CANXL1_INT_RAM_ECC_CORR_ERR_IRQn = 322,    /**< CANXL: correctable error occured within
                                                           internal data RAM or code RAM */
    FLEXLLCE_CANXL1_INT_FREEZE_IRQn = 323, /**< CANXL: IP has entered or exited freeze mode */
    FLEXLLCE_LINFLEXD0_IRQn = 324,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD1_IRQn = 325,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD2_IRQn = 326,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD3_IRQn = 327,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD4_IRQn = 328,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD5_IRQn = 329,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD6_IRQn = 330,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD7_IRQn = 331,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD8_IRQn = 332,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD9_IRQn = 333,     /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD10_IRQn = 334,    /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_LINFLEXD11_IRQn = 335,    /**< Ored of Internal Receiver Interrupt request, Internal
                                          Transmitter interrupt request and Internal Error Interrupt
                                          request */
    FLEXLLCE_FR0_RAM_NCERR_IRQn = 336, /**< LRAM and DRAM Non-Corrected Error interrupt */
    FLEXLLCE_FR0_RAM_CERR_IRQn = 337,  /**< LRAM and DRAM Corrected Error interrupt */
    FLEXLLCE_FR0_FIFO_CHA_IRQn = 338,  /**< Receive FIFO channel A not empty interrupt */
    FLEXLLCE_FR0_FIFO_CHB_IRQn = 339,  /**< Receive FIFO channel B not empty interrupt */
    FLEXLLCE_FR0_WKUP_IRQn = 340,      /**< Wakeup interrupt */
    FLEXLLCE_FR0_STATUS_IRQn = 341,    /**< Combined protocol status and error interrupt */
    FLEXLLCE_FR0_CMBERR_IRQn = 342,    /**< Combined CHI error interrupt */
    FLEXLLCE_FR0_TX_BUFF_IRQn = 343,   /**< Combined transmit message buffer interrupt */
    FLEXLLCE_FR0_RX_BUFF_IRQn = 344,   /**< Combined receive message buffer interrupt */
    FLEXLLCE_FR0_MODULE_IRQn = 345,    /**< Combined module interrupt */
    FLEXLLCE_FR1_RAM_NCERR_IRQn = 346, /**< LRAM Non-Corrected Error interrupt | DRAM Non-Corrected
                                          Error interrupt */
    FLEXLLCE_FR1_RAM_CERR_IRQn = 347, /**< LRAM Corrected Error interrupt | LRAM Non-Corrected Error
                                         interrupt */
    FLEXLLCE_FR1_FIFO_CHA_IRQn = 348, /**< Receive FIFO channel A not empty interrupt */
    FLEXLLCE_FR1_FIFO_CHB_IRQn = 349, /**< Receive FIFO channel B not empty interrupt */
    FLEXLLCE_FR1_WKUP_IRQn = 350,     /**< Wakeup interrupt */
    FLEXLLCE_FR1_STATUS_IRQn = 351,   /**< Combined protocol status and error interrupt */
    FLEXLLCE_FR1_CMBERR_IRQn = 352,   /**< Combined CHI error interrupt */
    FLEXLLCE_FR1_TX_BUFF_IRQn = 353,  /**< Combined transmit message buffer interrupt */
    FLEXLLCE_FR1_RX_BUFF_IRQn = 354,  /**< Combined receive message buffer interrupt */
    FLEXLLCE_FR1_MODULE_IRQn = 355,   /**< Combined module interrupt */
    FLEXLLCE_eDMA0_ERR_IRQn = 356,    /**< DMA Error interrupt request */
    FLEXLLCE_eDMA0_CH_0_15_IRQn = 357,  /**< Interrupt for DMA Channels 0-15 */
    FLEXLLCE_eDMA0_CH_16_31_IRQn = 358, /**< Interrupt for DMA Channels 16-31 */
    FLEXLLCE_eDMA1_ERR_IRQn = 359,      /**< DMA Error interrupt request */
    FLEXLLCE_eDMA1_CH_0_15_IRQn = 360,  /**< Interrupt for DMA Channels 0-15 */
    FLEXLLCE_eDMA4_ERR_IRQn = 361,      /**< DMA Error interrupt request */
    FLEXLLCE_eDMA4_CH_0_15_IRQn = 362,  /**< Interrupt for DMA Channels 0-15 */
    FLEXLLCE_eDMA5_ERR_IRQn = 363,      /**< DMA Error interrupt request */
    FLEXLLCE_eDMA5_CH_0_15_IRQn = 364   /**< Interrupt for DMA Channels 0-15 */
} FLEXLLCE_IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */

/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/* No SDK compatibility issues. */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */

#endif /* #if !defined(S32Z2_COMMON_H_) */
