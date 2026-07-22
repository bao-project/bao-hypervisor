/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/rzt2m_uart.h>
#include <platform.h>
#include <cpu.h>

static void r_sci_uart_baud_set(volatile R_SCI0_Type *p_sci_reg, baud_setting_t const *const p_baud_setting)
{
    p_sci_reg->CCR2 = (uint32_t)((p_sci_reg->CCR2 & ~(SCI_UART_CCR2_BAUD_SETTING_MASK)) |
                                 (p_baud_setting->ccr2_baudrate_bits & SCI_UART_CCR2_BAUD_SETTING_MASK));
}

static void uart_config_set(volatile R_SCI0_Type *const p_uart, uart_cfg_t const *const p_cfg)
{
    uint32_t ccr3 = SCI_UART_CCR3_DEFAULT_VALUE;
    if (BSP_FEATURE_SCI_UART_FIFO_CHANNELS & (1U << p_cfg->channel))
    {
        p_uart->FCR = SCI_UART_FCR_DEFAULT_VALUE;
    }

    /* Configure data size. */
    if (UART_DATA_BITS_7 == p_cfg->data_bits)
    {
        ccr3 |= (1U << SCI_UART_CCR3_CHR_OFFSET);
    }
    else if (UART_DATA_BITS_9 == p_cfg->data_bits)
    {
        ccr3 &= ~(1U << (SCI_UART_CCR3_CHR_OFFSET + 1));
    }
    else
    {
        /* Do nothing.  Default is 8-bit mode. */
    }

    /* Configure stop bits. */
    ccr3 |= (uint32_t)p_cfg->stop_bits << SCI_UART_CCR3_STP_OFFSET;

    /* Configure CKE bits. */
    const sci_uart_extended_cfg_t *p_extend = (const sci_uart_extended_cfg_t *)p_cfg->p_extend;
    ccr3 |= (p_extend->clock & SCI_UART_CCR3_CKE_VALUE_MASK) << SCI_UART_CCR3_CKE_OFFSET;

    /* Starts reception on falling edge of RXD if enabled in extension (otherwise reception starts at low level
     * of RXD). */
    ccr3 |= (p_extend->rx_edge_start & 1U) << SCI_UART_CCR3_RxDSEL_OFFSET;

    /* Configure SPEN bit. */
    ccr3 |= (p_extend->sync_bypass & 1U) << SCI_UART_CCR3_BPEN_OFFSET;

    /* Write to the CCR3 register. */
    p_uart->CCR3 = ccr3;

    /* CCR1 register setting. */
    uint32_t ccr1 = SCI_UART_CCR1_DEFAULT_VALUE;

    /* Set the default level of the TX pin to 1. */
    ccr1 |= (uint32_t)(1U << SCI_UART_CCR1_SPB2DT_BIT | SCI_UART_CCR1_OUTPUT_ENABLE_MASK);

    /* Configure parity bits. */
    ccr1 |= (uint32_t)(p_cfg->parity & SCI_UART_CCR1_PM_PE_VALUE_MASK) << SCI_UART_CCR1_PE_OFFSET;

    /* Configure CTS flow control if CTS/RTS flow control is enabled. */
    ccr1 |= (uint32_t)(p_extend->ctsrts_en << SCI_UART_CCR1_CTSE_OFFSET);

    if (SCI_UART_NOISE_CANCELLATION_DISABLE != p_extend->noise_cancel)
    {
        /* Select noise filter clock */
        ccr1 |= (uint32_t)(((p_extend->noise_cancel & 0x07U) - 1) & SCI_UART_CCR1_NFCS_VALUE_MASK) << SCI_UART_CCR1_NFCS_OFFSET;

        /* Enables the noise cancellation */
        ccr1 |= (uint32_t)1 << SCI_UART_CCR1_NFEN_OFFSET;
    }

    p_uart->CCR1 = ccr1;

    if ((SCI_UART_CLOCK_EXT8X == p_extend->clock) || (SCI_UART_CLOCK_EXT16X == p_extend->clock))
    {
        /* Use external clock for baud rate */
        p_uart->CCR2_b.BRR = SCI_UART_BRR_DEFAULT_VALUE;

        if (SCI_UART_CLOCK_EXT8X == p_extend->clock)
        {
            /* Set baud rate as (external clock / 8) */
            p_uart->CCR2 |= 1U << SCI_UART_CCR2_ABCS_OFFSET;
        }
    }
    else
    {
        /* Set the baud rate settings for the internal baud rate generator. */
        r_sci_uart_baud_set(p_uart, p_extend->p_baud_setting);
    }
}

static void renesas_uart_init(volatile R_SCI0_Type *const p_uart, uart_cfg_t const *const p_cfg)
{
    register_protect_disable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_SCI, p_cfg->channel);
    register_protect_enable(BSP_REG_PROTECT_LPC_RESET);

    p_uart->CCR0 = SCI_UART_CCR0_DEFAULT_VALUE;
    FSP_HARDWARE_REGISTER_WAIT(p_uart->CCR0_b.RE, 0);
    FSP_HARDWARE_REGISTER_WAIT(p_uart->CCR0_b.TE, 0);
    p_uart->CCR1 = SCI_UART_CCR1_DEFAULT_VALUE;
    p_uart->CCR2 = SCI_UART_CCR2_DEFAULT_VALUE;
    p_uart->CCR3 = SCI_UART_CCR3_DEFAULT_VALUE;
    p_uart->CCR4 = SCI_UART_CCR4_DEFAULT_VALUE;

    /* Set the UART configuration settings provided in ::uart_cfg_t and ::sci_uart_extended_cfg_t. */
    uart_config_set(p_uart, p_cfg);
}

void uart_init(volatile R_SCI0_Type *const p_api_ctrl)
{
    /* Map peripheral MMIO regions for UART initialization */
    // SYSTEM, MSTP - Non-safety Region
    vaddr_t sysc_ns = mem_alloc_map_dev(&cpu()->as, SEC_HYP_ANY, INVALID_VA,
        (paddr_t)R_SYSC_NS_BASE, NUM_PAGES(0x2000));
    if (sysc_ns == INVALID_VA) {
        ERROR("Maping SYSC_NS MMIO failed");
    }
    
    // SYSTEM, MSTP, CLMA, SYSRAM - Safety Region
    vaddr_t sysc_s = mem_alloc_map_dev(&cpu()->as, SEC_HYP_ANY, INVALID_VA,
        (paddr_t)R_SYSC_S_BASE, NUM_PAGES(0x2000));
    if (sysc_s == INVALID_VA) {
        ERROR("Maping SYSC_S MMIO failed");
    }

    baud_setting_t g_uart0_baud_setting = {
        .abcse = 0,
        .abcs = 0,
        .bgdm = 0,
        .cks = 0,
        .brr = 23,
        .mddr = 236,
        .brme = true
    };

    const sci_uart_extended_cfg_t g_uart0_cfg_extend = {
        .clock = SCI_UART_CLOCK_INT,
        .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE,
        .noise_cancel = SCI_UART_NOISE_CANCELLATION_DISABLE,
        .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX,
        .p_baud_setting = &g_uart0_baud_setting,
        .uart_mode = UART_MODE_RS232,
        .ctsrts_en = SCI_UART_CTSRTS_RTS_OUTPUT,
        .sync_bypass = SCI_UART_SYNCHRONIZER_NOT_BYPASS,
    };

    const uart_cfg_t g_uart0_cfg = {
        .channel = (uint8_t)(SCI_UART_CHANN),
        .data_bits = UART_DATA_BITS_8,
        .parity = UART_PARITY_OFF,
        .stop_bits = UART_STOP_BITS_1,
        .p_extend = &g_uart0_cfg_extend,
    };

    renesas_uart_init(p_api_ctrl, &g_uart0_cfg);

    mem_unmap(&cpu()->as, (vaddr_t)R_SYSC_NS_BASE, NUM_PAGES(0x2000), true);
    mem_unmap(&cpu()->as, (vaddr_t)R_SYSC_S_BASE, NUM_PAGES(0x2000), true);
}

void uart_enable(volatile R_SCI0_Type *const p_uart)
{
    uint32_t ccr0 = SCI_UART_CCR0_IDSEL_MASK;

    /* Enable transmit and receive */
    ccr0 |= (SCI_UART_CCR0_RE_MASK | SCI_UART_CCR0_TE_MASK); 
    
    p_uart->CCR0 = ccr0;

    FSP_HARDWARE_REGISTER_WAIT(p_uart->CCR0_b.RE, 1);
    FSP_HARDWARE_REGISTER_WAIT(p_uart->CCR0_b.TE, 1);
}

static void uart_read(volatile R_SCI0_Type *const p_uart, uint8_t *const p_dest)
{
    *p_dest = (uint8_t)p_uart->RDR_b.RDAT;
    FSP_HARDWARE_REGISTER_WAIT(p_uart->FRSR_b.DR,0);
}

char uart_getc(volatile R_SCI0_Type * p_uart)
{
    uint8_t result;
    uart_read(p_uart, &result);
    return (char)result;
}

static void uart_write(volatile R_SCI0_Type *const p_uart, uint8_t const *const p_src)
{
    FSP_HARDWARE_REGISTER_WAIT(p_uart->CSR_b.TEND, 1);

    p_uart->TDR_b.TDAT = *(p_src);
}

void uart_putc(volatile R_SCI0_Type *ptr_uart, int8_t c)
{
    uart_write(ptr_uart, (uint8_t*)&c);
}
