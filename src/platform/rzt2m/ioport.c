/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>


static ioport_instance_ctrl_t g_ioport_ctrl;
static ioport_extend_cfg_t g_ioport_cfg_extend;

extern const ioport_pin_cfg_t g_bsp_pin_cfg_data[PLAT_NUM_PINS];

static const ioport_cfg_t g_bsp_pin_cfg = { 
    .number_of_pins = sizeof(g_bsp_pin_cfg_data) / sizeof(ioport_pin_cfg_t),
    .p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
    .p_extend = &g_ioport_cfg_extend,
};


static void ioport_event_config (const ioport_extend_cfg_t * p_extend_cfg_data)
{
    uint8_t               event_num;
    uint8_t               temp_value    = 0x00;
    uint8_t               single_enable = 0x00;
    uint8_t               group_enable  = 0x00;
    R_PORT_COMMON_Type  * p_ioport_regs;

    /* Unlock GPIO protection registers. */
    register_protect_disable(BSP_REG_PROTECT_GPIO);

    /* Get register address */
    p_ioport_regs = R_PORT_NSR;

    /* Single port configuration */
    for (event_num = 0U; event_num < IOPORT_SINGLE_PORT_NUM; event_num++)
    {
        uint8_t port =
            (uint8_t) ((p_extend_cfg_data->single_port_cfg[event_num].port_num & IOPORT_PRV_PORT_BITS) >> IOPORT_PRV_PORT_OFFSET);
        uint8_t pin_num = (uint8_t) p_extend_cfg_data->single_port_cfg[event_num].port_num & IOPORT_PRV_PIN_BITS;

        temp_value = p_ioport_regs->ELC_PEL[event_num] & IOPORT_ELC_PEL_MASK;

        /* Port selection */
        if ((BSP_IO_PORT_16 >> IOPORT_PRV_PORT_OFFSET) == port)
        {
            temp_value |= 1U << 3;
        }
        else if ((BSP_IO_PORT_18 >> IOPORT_PRV_PORT_OFFSET) == port)
        {
            temp_value |= 1U << 4;
        }
        else
        {
            /* Do Nothing */
        }

        temp_value |= pin_num;         // Pin number setting

        /* When the pin specified as single input port, Set edge detection */
        /* When the pin specified as single output port, Set output operation */
        if (IOPORT_EVENT_DIRECTION_INPUT == p_extend_cfg_data->single_port_cfg[event_num].direction)
        {
            temp_value |= (uint8_t) (p_extend_cfg_data->single_port_cfg[event_num].edge_detection << 5); // Edge detection

            /* Edge detection enable */
            p_ioport_regs->ELC_DPTC |= (uint8_t) (1U << event_num);
        }
        else
        {
            temp_value |= (uint8_t) (p_extend_cfg_data->single_port_cfg[event_num].operation << 5); // Output operation
        }

        /* Set to ELC port setting register */
        p_ioport_regs->ELC_PEL[event_num] = temp_value;

        /* Single port event link function enable */
        if (IOPORT_EVENT_CONTROL_ENABLE == p_extend_cfg_data->single_port_cfg[event_num].event_control)
        {
            single_enable |= (uint8_t) (1U << event_num);
        }
    }

    /* Port group configuration */
    for (event_num = 0U; event_num < IOPORT_PORT_GROUP_NUM; event_num++)
    {
        /* Pin selection */
        uint8_t group_pin = p_extend_cfg_data->port_group_input_cfg[event_num].pin_select |
                            p_extend_cfg_data->port_group_output_cfg[event_num].pin_select;
        p_ioport_regs->ELC_PGR[event_num] = group_pin;

        if (IOPORT_EVENT_CONTROL_ENABLE == p_extend_cfg_data->port_group_input_cfg[event_num].event_control)
        {
            /* Input port group control */
            temp_value  = p_ioport_regs->ELC_PGC[event_num] & IOOPRT_ELC_PGC_MASK;
            temp_value |= (uint8_t) (p_extend_cfg_data->port_group_input_cfg[event_num].edge_detection);           // Edge detection
            temp_value |= (uint8_t) (p_extend_cfg_data->port_group_input_cfg[event_num].overwrite_control << 2U);  // Overwrite setting

            /* Buffer register initialization */
            p_ioport_regs->ELC_PDBF[event_num].BY = p_extend_cfg_data->port_group_input_cfg[event_num].buffer_init_value;

            /* Input port group event link function enable */
            group_enable |= (uint8_t) (1U << event_num);
        }

        /* Output port group operation */
        temp_value |= (uint8_t) (p_extend_cfg_data->port_group_output_cfg[event_num].operation << 4);

        /* Set to port group control register */
        p_ioport_regs->ELC_PGC[event_num] = temp_value;
    }

    /* Set to ELC port event control register */
    p_ioport_regs->ELC_ELSR2 = (uint8_t) ((single_enable << 4) | (group_enable << 2));

    /* Lock GPIO protection registers. */
    register_protect_enable(BSP_REG_PROTECT_GPIO);
}

static void ioport_pin_set (bsp_io_port_pin_t pin, const ioport_cfg_data_t * p_cfg_data)
{
    R_PORT_COMMON_Type * p_ioport_regs;
    uint32_t             temp_value;

    /* Get port and pin number */
    uint32_t port    = (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin) >> IOPORT_PRV_PORT_OFFSET;
    uint32_t pin_num = (IOPORT_PRV_PIN_BITS & (ioport_size_t) pin);

    /* Setting for Safety region or Non safety region */
    if (p_cfg_data->rsel_reg == 1U)    // Setting for Non safety region
    {
        R_PTADR->RSELP[port] |= (uint8_t) (1U << pin_num);
        p_ioport_regs         = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_NSAFE);
    }
    else                               // Setting for Safety region
    {
        R_PTADR->RSELP[port] &= (uint8_t) (~(1U << pin_num));
        p_ioport_regs         = IOPORT_PRV_PORT_ADDRESS(IOPORT_REGION_SEL_SAFE);
    }

    /* Setting DRCTL register */
    if (3U >= pin_num)
    {
        temp_value = p_ioport_regs->DRCTL[port].L & ~(IOPORT_DRTCL_BIT_MASK << (pin_num * 8U));
        p_ioport_regs->DRCTL[port].L = temp_value | (uint32_t) (p_cfg_data->drct_reg << (pin_num * 8U));
    }
    else if (3U < pin_num)
    {
        temp_value = p_ioport_regs->DRCTL[port].H & ~(IOPORT_DRTCL_BIT_MASK << ((pin_num - 4U) * 8U));
        p_ioport_regs->DRCTL[port].H = temp_value | (uint32_t) (p_cfg_data->drct_reg << ((pin_num - 4U) * 8U));
    }
    else
    {
        /* Do Nothing */
    }

    /* Setting for GPIO or peripheral */
    if (1U == p_cfg_data->pmc_reg)                                                                  // Setting for peripheral
    {
        temp_value               = p_ioport_regs->PFC[port] & ~(IOPORT_PFC_BIT_MASK << (pin_num * 4U));
        p_ioport_regs->PFC[port] = temp_value | (uint32_t) (p_cfg_data->pfc_reg << (pin_num * 4U)); // Setting PFC register

        /* Setting peripheral for port mode */
        p_ioport_regs->PMC[port] |= (uint8_t) (p_cfg_data->pmc_reg << pin_num);                     // Setting PMC register
    }
    else // Setting for GPIO
    {
        /* Setting GPIO for port mode */
        p_ioport_regs->PMC[port] &= (uint8_t) (~(1U << pin_num)); // Setting PMC register

        /* Setting for input or output */
        if (1U == p_cfg_data->pm_reg)                             // Setting for input
        {
            /* Setting PM register. */
            /* 01b: Input           */
            temp_value              = (uint32_t) (p_ioport_regs->PM[port] & ~(IOPORT_PM_BIT_MASK << (pin_num * 2U)));
            p_ioport_regs->PM[port] = (uint16_t) (temp_value | (uint32_t) (1U << (pin_num * 2U)));
        }
        else if (1U < p_cfg_data->pm_reg)     // Setting for two kinds of Output
        {
            /* Setting P register */
            if (0U == p_cfg_data->p_reg)      // Low output setting
            {
                p_ioport_regs->P[port] &= (uint8_t) (~(1U << pin_num));
            }
            else if (1U == p_cfg_data->p_reg) // High output setting
            {
                p_ioport_regs->P[port] |= (uint8_t) (1U << pin_num);
            }
            else
            {
                /* Do Nothing */
            }

            /* Setting PM register.                              */
            /* 10b: Output                                       */
            /* 11b: Output(output data is input to input buffer) */
            temp_value              = (uint32_t) (p_ioport_regs->PM[port] & ~(IOPORT_PM_BIT_MASK << (pin_num * 2U)));
            p_ioport_regs->PM[port] = (uint16_t) (temp_value | (uint32_t) (p_cfg_data->pm_reg << (pin_num * 2U)));
        }
        else
        {
            /* Do Nothing */
        }
    }
}

static void ioport_pins_config (const ioport_cfg_t * p_cfg)
{
    /* Unlock GPIO protection registers. */
    register_protect_disable(BSP_REG_PROTECT_GPIO); 

    for(uint16_t pin_count = 0U; pin_count < p_cfg->number_of_pins; pin_count++) {
        ioport_pin_set(p_cfg->p_pin_cfg_data[pin_count].pin,
            (const ioport_cfg_data_t *) &p_cfg->p_pin_cfg_data[pin_count].pin_cfg);
    }

    /* Lock GPIO protection registers. */
    register_protect_enable(BSP_REG_PROTECT_GPIO); 
}

void rzt2m_ioport_open(void)
{
    ioport_instance_ctrl_t* p_instance_ctrl = (ioport_instance_ctrl_t *) &g_ioport_ctrl;

    /* Set driver status to open */
    p_instance_ctrl->open = IOPORT_OPEN;

    p_instance_ctrl->p_cfg = &g_bsp_pin_cfg;

    ioport_pins_config(&g_bsp_pin_cfg);

    ioport_event_config(g_bsp_pin_cfg.p_extend);
}