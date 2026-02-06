/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/linflexd_uart.h>
#include <cpu.h>
#include <platform.h>

// #define LINFlexD_FRAME_ERROR_INT        (0x100)
// #define LINFlexD_BUFFER_OVERRUN_INT     (0x80U)
#define clk_freq (123500000UL)

// #define LIN_9_TX 0
// #define LIN_9_RX 1
// #define LIN_0_TX 2
// #define LIN_0_RX 3

linflexd_uart_user_config_t linflexdUartInitConfig0 = { .transferType =
                                                            LINFLEXD_UART_USING_INTERRUPTS,
    .baudRate = 115200UL,
    .parityCheck = false,
    .parityType = LINFLEXD_UART_PARITY_ZERO,
    .stopBitsCount = LINFLEXD_UART_ONE_STOP_BIT,
    .wordLength = LINFLEXD_UART_8_BITS,
    .rxDMAChannel = 0UL,
    .txDMAChannel = 0UL };

#define NUM_OF_CONFIGURED_PINS0 4
/* Array of pin configuration structures */
pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] = {
    {
        // Tx   LINFLEXD9
        .base = SIUL2_5,
        .pinPortIdx = 150u,
        .mux = PORT_MUX_ALT1,
        .safeMode = PORT_SAFE_MODE_DISABLED,
        .receiverSel = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer = PORT_INPUT_BUFFER_DISABLED,
        .openDrain = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        // Rx   LINFLEXD9
        .base = SIUL2_5,
        .pinPortIdx = 151u,      // 42u
        .mux = PORT_MUX_AS_GPIO, // 0
        .safeMode = PORT_SAFE_MODE_DISABLED,
        .receiverSel = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer = PORT_INPUT_BUFFER_ENABLED,
        .openDrain = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer = PORT_OUTPUT_BUFFER_DISABLED,
        .intConfig = { .intEdgeSel = SIUL2_INT_DISABLE },
        .inputMux[0] = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0] = 466u, // 0u,
        .inputMux[1] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7] = PORT_INPUT_MUX_NO_INIT,
        .interleaveBase = NULL,
    },
    {
        // Tx   LINFLEXD0
        .base = SIUL2_0,
        .pinPortIdx = 0u,
        .mux = PORT_MUX_ALT1,
        .safeMode = PORT_SAFE_MODE_DISABLED,
        .receiverSel = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer = PORT_INPUT_BUFFER_DISABLED,
        .openDrain = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer = PORT_OUTPUT_BUFFER_ENABLED,
    },
    {
        // Rx   LINFLEXD0
        .base = SIUL2_0,
        .pinPortIdx = 1u, // 42u
        .mux = PORT_MUX_ALT2,
        .safeMode = PORT_SAFE_MODE_DISABLED,
        .receiverSel = PORT_RECEIVER_ENABLE_DIFFERENTIAL_VREF,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .slewRateCtrlSel = PORT_SLEW_RATE_CONTROL4,
        .inputBuffer = PORT_INPUT_BUFFER_ENABLED,
        .openDrain = PORT_OPEN_DRAIN_DISABLED,
        .outputBuffer = PORT_OUTPUT_BUFFER_DISABLED,
        .intConfig = { .intEdgeSel = SIUL2_INT_DISABLE },
        .inputMux[0] = PORT_INPUT_MUX_ALT2,
        .inputMuxReg[0] = 466u, // 0u,
        .inputMux[1] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[2] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[3] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[4] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[5] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[6] = PORT_INPUT_MUX_NO_INIT,
        .inputMux[7] = PORT_INPUT_MUX_NO_INIT,
        .interleaveBase = NULL,
    }
};

static void LINFLEXD_SetUartWordLength(volatile struct LINFlexD_Type* base,
    linflexd_uart_word_length_t length)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_WL0_MASK);
    regValTemp |= LINFlexD_UARTCR_WL0((uint32_t)length & 1U);
    regValTemp &= ~(LINFlexD_UARTCR_WL1_MASK);
    regValTemp |= LINFlexD_UARTCR_WL1(((uint32_t)length >> 1U) & 1U);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetTxDataFieldLength(volatile struct LINFlexD_Type* base, uint8_t length)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_TDFL_TFC_MASK);
    regValTemp |= LINFlexD_UARTCR_TDFL_TFC(length);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetRxDataFieldLength(volatile struct LINFlexD_Type* base, uint8_t length)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_RDFL_RFC_MASK);
    regValTemp |= LINFlexD_UARTCR_RDFL_RFC(length);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetParityControl(volatile struct LINFlexD_Type* base, bool enable)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_PCE_MASK);
    regValTemp |= LINFlexD_UARTCR_PCE(enable ? 1UL : 0UL);
    base->UARTCR = regValTemp;
}

static uint8_t LINFLEXD_GetRxDataBuffer1Byte(volatile struct LINFlexD_Type* base)
{
    return (uint8_t)(base->BDRM & LINFlexD_BDRM_DATA4_MASK);
}

static void LINFLEXD_SetTxMode(volatile struct LINFlexD_Type* base, linflexd_uart_rxtx_mode_t mode)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_TFBM_MASK);
    regValTemp |= LINFlexD_UARTCR_TFBM((uint32_t)mode);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetRxMode(volatile struct LINFlexD_Type* base, linflexd_uart_rxtx_mode_t mode)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_RFBM_MASK);
    regValTemp |= LINFlexD_UARTCR_RFBM((uint32_t)mode);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetRxEnable(volatile struct LINFlexD_Type* base, uint32_t enable)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp |= LINFlexD_UARTCR_RxEn((uint32_t)enable);
    base->UARTCR = regValTemp;

    regValTemp = base->LINIER;
    regValTemp |= (uint32_t)LINIER_DRIE;
    base->LINIER = regValTemp;
}

// static void LINFLEXD_SetInterruptMode(volatile struct LINFlexD_Type * base, uint32_t intSrc, bool
// enable)
// {
//     uint32_t regValTemp;
//
//     regValTemp = base->LINIER;
//     if (enable)
//     {
//         regValTemp |= (uint32_t)intSrc;
//     }
//     else
//     {
//         regValTemp &= ~(uint32_t)intSrc;
//     }
//     base->LINIER = regValTemp;
// }

static void LINFLEXD_SetTransmitterState(volatile struct LINFlexD_Type* base, bool enable)
{
    uint32_t regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_TxEn_MASK);
    regValTemp |= LINFlexD_UARTCR_TxEn(enable ? 1UL : 0UL);
    base->UARTCR = regValTemp;
}

static void LINFLEXD_SetTxDataBuffer1Byte(volatile struct LINFlexD_Type* base, int8_t data)
{
    uint32_t regValTemp;

    regValTemp = base->BDRL;
    regValTemp &= ~(LINFlexD_BDRL_DATA0_MASK);
    regValTemp |= LINFlexD_BDRL_DATA0(data);
    base->BDRL = regValTemp;
}

static inline uint8_t LINFLEXD_GetLinState(volatile struct LINFlexD_Type* base)
{
    uint8_t state =
        (uint8_t)((base->LINSR & LINFlexD_LINSR_LINS_MASK) >> LINFlexD_LINSR_LINS_SHIFT);
    return state;
}

static void LINFLEXD_UART_DRV_SendData(volatile struct LINFlexD_Type* instance, const int8_t* txBuff)
{
    /* Enable the transmitter */
    LINFLEXD_SetTransmitterState(instance, true);

    /* Clear the tx empty flag to make sure the transmission of the first byte
     * doesn't occur right after enabling the tx interrupt
     */
    instance->UARTSR = LINFlexD_UART_DATA_TRANSMITTED_FLAG;

    /* Enable transmission complete interrupt */
    // LINFLEXD_SetInterruptMode(base, 1 /*LINFlexD_DATA_TRANSMITTED_INT*/, true);

    /* Wait for transmission to end */
    while (LINFLEXD_GetLinState(instance) == 7 || LINFLEXD_GetLinState(instance) == 8)
        ;
    LINFLEXD_SetTxDataBuffer1Byte(instance, *txBuff);
}

// static void PINS_WritePin(GPIO_Type * const base,
//                                  pins_channel_type_t pin,
//                                  pins_level_type_t value)
// {
//     pins_channel_type_t pin_values = (pins_channel_type_t)base->PGPDO;
//     pin_values &= (pins_channel_type_t)(~((pins_channel_type_t)1U << (15U - pin)));
//     pin_values |= (pins_channel_type_t)(((pins_channel_type_t)value & 1U) << (15U - pin));
//     base->PGPDO = pin_values;
// }

// static void PINS_Init(const pin_settings_config_t * config)
// {
//     uint32_t pin_values = 0U;
//     uint8_t input_mux;

//     /* Get the SIUL2 base for interrupt pin if using */
//     //interruptBase = SIUL2_1;

// 	pin_values |= SIUL2_1_MSCR_OBE(config->outputBuffer);
//     pin_values |= SIUL2_1_MSCR_ODE(config->openDrain);
//     pin_values |= SIUL2_1_MSCR_IBE(config->inputBuffer);
//     pin_values |= SIUL2_1_MSCR_SRE(config->slewRateCtrlSel);
//     pin_values |= SIUL2_1_MSCR_RCVR(config->receiverSel);
//     pin_values |= SIUL2_1_MSCR_SMC(config->safeMode);
//     pin_values |= SIUL2_1_MSCR_SSS(config->mux);

//     /* Configure initial value for GPIO pin in GPIO mux */
//     if ((PORT_MUX_AS_GPIO == config->mux) && (PORT_OUTPUT_BUFFER_ENABLED ==
//     config->outputBuffer))
//     {
//         PINS_WritePin((GPIO_Type *) config->base->MSCR[config->pinPortIdx],
//                         (pins_channel_type_t)(config->pinPortIdx % SIUL2_NUM_OF_PIN_PORT),
//                         pin_values);
//     }

//     /* Write to Multiplexed Signal Configuration Register register */
//     config->base->MSCR[config->pinPortIdx] = pin_values;

//     // INPUT (Rx) Config Only
//     if (PORT_INPUT_BUFFER_ENABLED == config->inputBuffer)
//     {
//         for (input_mux = 0U; input_mux < FEATURE_SIUL2_INPUT_MUX_WIDTH; input_mux++)
//         {
//             /* Check if input mux information needs to be configured */
//             if (PORT_INPUT_MUX_NO_INIT != config->inputMux[input_mux])
//             {
//                 /* Write to Input Mux register */
//                 config->base->IMCR[config->inputMuxReg[input_mux]] =
//                         SIUL2_AE_IMCR_SSS(config->inputMux[input_mux]);
//             }
//         }
//     }
// }

void uart_disable(volatile struct LINFlexD_Type* ptr_uart)
{
    UNUSED_ARG(ptr_uart);
    /*	uint32_t ctrl_reg = ptr_uart->control;
        ctrl_reg &= ((~UART_CR_UARTEN) | (~UART_CR_TXE) | (~UART_CR_RXE));
        ptr_uart->control = ctrl_reg;
    */
}

void uart_enable(volatile struct LINFlexD_Type* ptr_uart)
{
    UNUSED_ARG(ptr_uart);
    /*
    uint32_t ctrl_reg = ptr_uart->control;
    ctrl_reg |= (UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE);
    ptr_uart->control = ctrl_reg;		*/
}

static inline void LINFLEXD_EnterInitMode(volatile struct LINFlexD_Type* base)
{
    uint32_t regValTemp;
    regValTemp = base->LINCR1;
    regValTemp &= ~(LINFlexD_LINCR1_SLEEP_MASK);
    regValTemp |= LINFlexD_LINCR1_INIT(1UL);
    base->LINCR1 = regValTemp;
}

static inline void LINFLEXD_EnterNormalMode(volatile struct LINFlexD_Type* base)
{
    uint32_t regValTemp;
    regValTemp = base->LINCR1;
    regValTemp &= ~(LINFlexD_LINCR1_SLEEP_MASK);
    regValTemp &= ~(LINFlexD_LINCR1_INIT_MASK);
    base->LINCR1 = regValTemp;
}

static inline void LINFLEXD_SetIntegerBaudRate(volatile struct LINFlexD_Type* base, uint32_t ibr)
{
    uint32_t regValTemp;
    regValTemp = base->LINIBRR;
    regValTemp &= ~(LINFlexD_LINIBRR_IBR_MASK);
    regValTemp |= LINFlexD_LINIBRR_IBR(ibr);
    base->LINIBRR = regValTemp;
}

static inline void LINFLEXD_SetMode(volatile struct LINFlexD_Type* base, linflexd_mode_t mode)
{
    uint32_t regValTemp;
    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFlexD_UARTCR_UART_MASK);
    regValTemp |= LINFlexD_UARTCR_UART((uint32_t)mode);
    base->UARTCR = regValTemp;
}

// static void clock_init(volatile struct LINFlexD_Type * base){
//     uint32_t *clock_mux = 0;
//     switch(((uint32_t) base)){
//         case LINFlexD_0_BASE:
//         case LINFlexD_1_BASE:
//         case LINFlexD_2_BASE:
//             clock_mux = (uint32_t *) (MC_CGM_0 + MUX_CSC_4_OFFSET);
//             break;
//         case LINFlexD_3_BASE:
//         case LINFlexD_4_BASE:
//         case LINFlexD_5_BASE:
//             clock_mux = (uint32_t *) (MC_CGM_1 + MUX_CSC_4_OFFSET);
//             break;
//         case LINFlexD_6_BASE:
//         case LINFlexD_7_BASE:
//         case LINFlexD_8_BASE:
//             clock_mux = (uint32_t *) (MC_CGM_4 + MUX_CSC_8_OFFSET);
//             break;
//         case LINFlexD_9_BASE:
//         case LINFlexD_10_BASE:
//         case LINFlexD_11_BASE:
//             clock_mux = (uint32_t *) (MC_CGM_5 + MUX_CSC_2_OFFSET);
//             break;
//         default: break;
//     }

//     mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, (uint32_t) INVALID_VA, (paddr_t) clock_mux,
//                        NUM_PAGES(MUX_SIZE));
//     *clock_mux = 0x00000000;
//     *clock_mux |= SAFE_CLK_MASK(1);
//     clock_mux = clock_mux + MUX_DIV0_OFFSET;
//     *clock_mux = 0x80000000;
//     mem_unmap(&cpu()->as, (paddr_t) clock_mux, NUM_PAGES(MUX_SIZE), false);
// }

static void LINFLEXD_UART_DRV_SetBaudRate(volatile struct LINFlexD_Type* base, uint32_t baudrate)
{
    uint32_t mantissa;
    bool resetIdle = false;

    /* Compute the values for baud rate divider mantissa and fraction */
    mantissa = clk_freq / (baudrate * DEFAULT_OSR);

    if (LINFLEXD_GetLinState(base) != LINFlexD_STATE_INIT_MODE) {
        /* Request init mode and wait until the mode entry is complete */
        LINFLEXD_EnterInitMode(base);
        while (LINFLEXD_GetLinState(base) != LINFlexD_STATE_INIT_MODE) { }
        resetIdle = true;
    }

    /* Write the computed values to registers */
    LINFLEXD_SetIntegerBaudRate(base, mantissa);

    if (resetIdle == true) {
        /* Enter normal mode */
        LINFLEXD_EnterNormalMode(base);
    }
}

void uart_init(volatile struct LINFlexD_Type* ptr_uart)
{
    linflexd_uart_user_config_t* uartUserConfig = &linflexdUartInitConfig0;

    // mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, (uint32_t) INVALID_VA,
    //                     (uint32_t) g_pin_mux_InitConfigArr0->base,
    //                     NUM_PAGES(sizeof(SIUL2_Type)));

    // PINS_Init(&g_pin_mux_InitConfigArr0[LIN_9_TX]);
    // PINS_Init(&g_pin_mux_InitConfigArr0[LIN_9_RX]);

    // /* unmap SIUL2_x region */
    // mem_unmap(&cpu()->as, (uint32_t) g_pin_mux_InitConfigArr0->base,
    //             NUM_PAGES(sizeof(SIUL2_Type)), false);

    // /* init uart clock */
    // clock_init(ptr_uart);
    // clock_init(LINFlexD_9);
    // clock_init(LINFlexD_0);

    /* Request init mode and wait until the mode entry is complete */
    LINFLEXD_EnterInitMode(ptr_uart);

    /* Set UART mode */
    LINFLEXD_SetMode(ptr_uart, LINFlexD_UART_MODE);

    /* Set the baud rate */
    LINFLEXD_UART_DRV_SetBaudRate(ptr_uart, uartUserConfig->baudRate);

    /* Set word length */
    LINFLEXD_SetUartWordLength(ptr_uart, uartUserConfig->wordLength);
    LINFLEXD_SetTxDataFieldLength(ptr_uart, 0);
    LINFLEXD_SetRxDataFieldLength(ptr_uart, 0);

    LINFLEXD_SetParityControl(ptr_uart, false);

    LINFLEXD_SetTxMode(ptr_uart, LINFLEXD_UART_RXTX_BUFFER_MODE);
    LINFLEXD_SetRxMode(ptr_uart, LINFLEXD_UART_RXTX_BUFFER_MODE);
    LINFLEXD_SetRxEnable(ptr_uart, 1);

    /* Enter normal mode */
    LINFLEXD_EnterNormalMode(ptr_uart);
}

uint32_t uart_getc(volatile struct LINFlexD_Type* ptr_uart)
{
    // uint32_t data = 0;
    // uint32_t* base = (uint32_t*) s_LINFlexDBase[LINFlexD_instance];
    // while(!(*base & 0x200));
    // data = LINFLEXD_GetRxDataBuffer1Byte((struct LINFlexD_Type *)ptr_uart);
    // return data;

    while (!((ptr_uart->LINCR1) & 0x200))
        ;
    return LINFLEXD_GetRxDataBuffer1Byte(ptr_uart);
}

void uart_putc(volatile struct LINFlexD_Type* ptr_uart, int8_t c)
{
    LINFLEXD_UART_DRV_SendData(ptr_uart, &c);
}

void uart_puts(volatile struct LINFlexD_Type* ptr_uart, const char* s)
{
    while (*s) {
        uart_putc(ptr_uart, (int8_t)*s);
        s++;
    }
}

void linflexd_enable_rxirq(volatile struct LINFlexD_Type* ptr_uart)
{
    ptr_uart->LINIER = (1U << 2);
}

void linflexd_clear_rxirq(volatile struct LINFlexD_Type* ptr_uart)
{
    ptr_uart->UARTSR = (1U << 2);
    while (ptr_uart->UARTSR & (1U << 2))
        ;
}
