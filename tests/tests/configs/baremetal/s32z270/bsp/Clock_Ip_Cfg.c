/*
 * Copyright 2022-2024 NXP
*
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
*   @file       Clock_Ip_Cfg.c
*   @version    2.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Clock_Ip_Private.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_CFG_VENDOR_ID_C                      43
#define CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_CFG_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_CFG_SW_MINOR_VERSION_C               0
#define CLOCK_IP_CFG_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Cfg.c and Std_Types.h are different"
#endif
#endif    /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
/* Check if source file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_CFG_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Cfg.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if source file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Cfg.c and Clock_Ip_Private.h are different"
#endif

/* Check if source file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_CFG_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_CFG_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_CFG_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Cfg.c and Clock_Ip_Private.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"



static const Clock_Ip_XoscConfigType Clock_Ip_XoscConfigurations_0[CLOCK_IP_CONFIGURED_XOSCS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_XOSCS_0_NO > 0U
    {
        FXOSC_CLK,              /* Clock name associated to xosc */
        40000000U,              /* External oscillator frequency. */ 
        1U,                     /* Enable xosc. */
        157U,                    /* Startup stabilization time. */
        0U,                     /* XOSC bypass option */ 
        1U,                     /* Comparator enable */ 
        12U,                    /* TransConductance */
        0U,                     /* Gain value */
        0U,                     /* Monitor type */
        0U,                     /* Automatic level controller */
    },
    #endif
};


static const Clock_Ip_PllConfigType Clock_Ip_PllConfigurations_0[CLOCK_IP_CONFIGURED_PLLS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_PLLS_0_NO > 0U
    {
        COREPLL_CLK,                /* name */
        1U,                     /* enable */
        FXOSC_CLK,                     /* inputReference */
        0U,                     /* Bypass */
        2U,                      /* predivider */
        0U,                      /* multiplier */
        0U,                      /* postdivider */
        0U,                     /* numeratorFracLoopDiv */
        100U,                   /* mulFactorDiv */
        1U,                     /* ModulationBypass */
        0U,                     /* Modulation type: Spread spectrum modulation bypassed */ 
        0U,                     /* modulationPeriod */
        0U,                     /* incrementStep */
        0U,                     /* sigmaDelta */
        0U,                     /* ditherControl */
        0U,                     /* ditherControlValue */
        0U,                     /* Monitor type */
        {                      /* Dividers */
            0U,
            0U,
            0U,
        },
        0U,                     /* SoftwareDisable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_PLLS_0_NO > 1U
    {
        PERIPHPLL_CLK,                /* name */
        1U,                     /* enable */
        FXOSC_CLK,                     /* inputReference */
        0U,                     /* Bypass */
        2U,                      /* predivider */
        0U,                      /* multiplier */
        0U,                      /* postdivider */
        0U,                     /* numeratorFracLoopDiv */
        120U,                   /* mulFactorDiv */
        0U,                     /* ModulationBypass */
        0U,                     /* Modulation type: Spread spectrum modulation bypassed */
        0U,                     /* modulationPeriod */
        0U,                     /* incrementStep */
        0U,                     /* sigmaDelta */
        0U,                     /* ditherControl */
        0U,                     /* ditherControlValue */
        0U,                     /* Monitor type */
        {                      /* Dividers */
            0U,
            0U,
            0U,
        },
        0U,                     /* SoftwareDisable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_PLLS_0_NO > 2U
    {
        DDRPLL_CLK,                /* name */
        1U,                     /* enable */
        FXOSC_CLK,                     /* inputReference */
        0U,                     /* Bypass */
        1U,                      /* predivider */
        0U,                      /* multiplier */
        0U,                      /* postdivider */
        0U,                     /* numeratorFracLoopDiv */
        40U,                   /* mulFactorDiv */
        1U,                     /* ModulationBypass */
        0U,                     /* Modulation type: Spread spectrum modulation bypassed */ 
        0U,                     /* modulationPeriod */
        0U,                     /* incrementStep */
        0U,                     /* sigmaDelta */
        0U,                     /* ditherControl */
        0U,                     /* ditherControlValue */
        0U,                     /* Monitor type */
        {                      /* Dividers */
            0U,
            0U,
            0U,
        },
        0U,                     /* SoftwareDisable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_PLLS_0_NO > 3U
    {
        LFAST0_PLL_CLK,                /* name */
        1U,                     /* enable */
        P1_LFAST0_REF_CLK,             /* inputReference */
        0U,                     /* Bypass */
        1U,                      /* predivider */
        0U,                      /* multiplier */
        0U,                      /* postdivider */
        0U,                     /* numeratorFracLoopDiv */
        20U,                      /* mulFactorDiv */
        0U,                     /* ModulationBypass */
        0U,                     /* Modulation type: Spread spectrum modulation bypassed */
        0U,                     /* modulationPeriod */
        0U,                     /* incrementStep */
        0U,                     /* sigmaDelta */
        0U,                     /* ditherControl */
        0U,                     /* ditherControlValue */
        0U,                     /* Monitor type */
        {                      /* Dividers */
            0U,
            0U,
            0U,
        },
        0U,                     /* SoftwareDisable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_PLLS_0_NO > 4U
    {
        LFAST1_PLL_CLK,                /* name */
        1U,                     /* enable */
        P1_LFAST1_REF_CLK,             /* inputReference */
        0U,                     /* Bypass */
        1U,                      /* predivider */
        0U,                      /* multiplier */
        0U,                      /* postdivider */
        0U,                     /* numeratorFracLoopDiv */
        20U,                      /* mulFactorDiv */
        0U,                     /* ModulationBypass */
        0U,                     /* Modulation type: Spread spectrum modulation bypassed */
        0U,                     /* modulationPeriod */
        0U,                     /* incrementStep */
        0U,                     /* sigmaDelta */
        0U,                     /* ditherControl */
        0U,                     /* ditherControlValue */
        0U,                     /* Monitor type */
        {                      /* Dividers */
            0U,
            0U,
            0U,
        },
        0U,                     /* SoftwareDisable */
    },
    #endif
};

static const Clock_Ip_SelectorConfigType Clock_Ip_SelectorConfigurations_0[CLOCK_IP_CONFIGURED_SELECTORS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 0U
    {
        P0_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 1U
    {
        P0_REG_INTF_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS4_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 2U
    {
        P0_PSI5_1US_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 3U
    {
        P0_PSI5_S_TRIG0_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 4U
    {
        P0_LIN_BAUD_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 5U
    {
        P0_DSPI_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 6U
    {
        P0_FR_PE_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 7U
    {
        P0_NANO_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI0_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 8U
    {
        GLB_LBIST_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS5_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 9U
    {
        P0_EMIOS_LCU_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 10U
    {
        CLKOUT0_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 11U
    {
        P1_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 12U
    {
        P1_REG_INTF_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS4_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 13U
    {
        P1_DSPI_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 14U
    {
        P1_DSPI60_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI2_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 15U
    {
        P1_LIN_BAUD_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 16U
    {
        ETH_TS_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 17U
    {
        ETH0_TX_MII_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS3_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 18U
    {
        ETH0_RX_MII_CLK,                    /* Clock name associated to selector */
        ETH0_EXT_RX_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 19U
    {
        ETH1_TX_MII_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS3_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 20U
    {
        ETH1_RX_MII_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS3_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 21U
    {
        CLKOUT1_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 22U
    {
        P1_LFAST0_REF_CLK,                    /* Clock name associated to selector */
        FXOSC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 23U
    {
        P1_LFAST1_REF_CLK,                    /* Clock name associated to selector */
        FXOSC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 24U
    {
        P1_NETC_AXI_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_DFS5_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 25U
    {
        P2_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS4_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 26U
    {
        P2_REG_INTF_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 27U
    {
        P2_DBG_ATB_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 28U
    {
        P2_MATH_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS2_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 29U
    {
        P3_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 30U
    {
        P3_REG_INTF_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 31U
    {
        P3_DBG_TS_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 32U
    {
        P3_CAN_PE_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI5_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 33U
    {
        CLKOUT4_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 34U
    {
        P4_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS4_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 35U
    {
        P4_REG_INTF_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 36U
    {
        P4_PSI5_1US_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 37U
    {
        P4_PSI5_S_TRIG0_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 38U
    {
        P4_DSPI_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 39U
    {
        P4_DSPI60_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI2_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 40U
    {
        CLKOUT2_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 41U
    {
        P4_QSPI0_2X_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_DFS0_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 42U
    {
        P4_LIN_BAUD_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 43U
    {
        P4_SDHC_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_DFS2_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 44U
    {
        P4_SDHC_IP_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 45U
    {
        P4_EMIOS_LCU_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 46U
    {
        P5_SYS_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS4_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 47U
    {
        P5_REG_INTF_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 48U
    {
        P5_LIN_BAUD_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 49U
    {
        P5_DSPI_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_PHI1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 50U
    {
        CLKOUT3_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 51U
    {
        P5_DIPORT_CLK,                    /* Clock name associated to selector */
        PERIPHPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 52U
    {
        DDR_CLK,                    /* Clock name associated to selector */
        DDRPLL_PHI0_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 53U
    {
        P6_REG_INTF_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 54U
    {
        RTU0_CORE_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS0_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 55U
    {
        RTU0_REG_INTF_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 56U
    {
        RTU1_CORE_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS0_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 57U
    {
        RTU1_REG_INTF_CLK,                    /* Clock name associated to selector */
        COREPLL_DFS1_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 58U
    {
        P0_CLKOUT_SRC_CLK,                    /* Clock name associated to selector */
        FIRC_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 59U
    {
        P1_CLKOUT_SRC_CLK,                    /* Clock name associated to selector */
        P1_SYS_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 60U
    {
        P3_CLKOUT_SRC_CLK,                    /* Clock name associated to selector */
        P3_SYS_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 61U
    {
        P4_CLKOUT_SRC_CLK,                    /* Clock name associated to selector */
        P4_SYS_CLK,                    /* Name of the selected input source */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_SELECTORS_0_NO > 62U
    {
        P5_CLKOUT_SRC_CLK,                    /* Clock name associated to selector */
        P5_SYS_CLK,                    /* Name of the selected input source */
    },
    #endif
};


static const Clock_Ip_DividerConfigType Clock_Ip_DividerConfigurations_0[CLOCK_IP_CONFIGURED_DIVIDERS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 0U
    {
        CLKOUT0_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 1U
    {
        CLKOUT1_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 2U
    {
        COREPLL_PHI0_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 3U
    {
        DDR_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 4U
    {
        DDRPLL_PHI0_CLK,                    /* name */
        4U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 5U
    {
        ETH_TS_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 6U
    {
        ETH0_REF_RMII_CLK,                    /* name */
        5U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 7U
    {
        ETH0_RX_MII_CLK,                    /* name */
        5U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 8U
    {
        ETH0_RX_RGMII_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 9U
    {
        ETH0_TX_MII_CLK,                    /* name */
        20U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 10U
    {
        ETH0_TX_RGMII_CLK,                    /* name */
        4U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 11U
    {
        ETH1_REF_RMII_CLK,                    /* name */
        10U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 12U
    {
        ETH1_RX_MII_CLK,                    /* name */
        20U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 13U
    {
        ETH1_RX_RGMII_CLK,                    /* name */
        10U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 14U
    {
        ETH1_TX_MII_CLK,                    /* name */
        20U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 15U
    {
        ETH1_TX_RGMII_CLK,                    /* name */
        4U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 16U
    {
        GLB_LBIST_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 17U
    {
        P0_CTU_PER_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 18U
    {
        P0_DSPI_MSC_CLK,                    /* name */
        10U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 19U
    {
        P0_FR_PE_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 20U
    {
        P0_GTM_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 21U
    {
        P0_LIN_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 22U
    {
        P0_PSI5_125K_CLK,                    /* name */
        12U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 23U
    {
        P0_PSI5_189K_CLK,                    /* name */
        3306U,                              /* value */
        {
            2U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 24U
    {
        P0_PSI5_1US_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 25U
    {
        P0_PSI5_S_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 26U
    {
        P0_PSI5_S_TRIG0_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 27U
    {
        P0_PSI5_S_TRIG1_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 28U
    {
        P0_PSI5_S_TRIG2_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 29U
    {
        P0_PSI5_S_TRIG3_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 30U
    {
        P0_PSI5_S_UART_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 31U
    {
        P0_PSI5_S_UTIL_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 32U
    {
        P0_PSI5_S_WDOG0_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 33U
    {
        P0_PSI5_S_WDOG1_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 34U
    {
        P0_PSI5_S_WDOG2_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 35U
    {
        P0_PSI5_S_WDOG3_CLK,                    /* name */
        513U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 36U
    {
        P1_LFAST0_REF_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 37U
    {
        P1_LFAST1_REF_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 38U
    {
        P1_LIN_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 39U
    {
        P1_NETC_AXI_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 40U
    {
        P1_REG_INTF_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 41U
    {
        P2_REG_INTF_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 42U
    {
        P3_AES_CLK,                    /* name */
        200U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 43U
    {
        P3_CAN_PE_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 44U
    {
        CLKOUT4_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 45U
    {
        P3_DBG_TS_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 46U
    {
        P3_REG_INTF_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 47U
    {
        CLKOUT2_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 48U
    {
        P4_LIN_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 49U
    {
        P4_PSI5_125K_CLK,                    /* name */
        12U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 50U
    {
        P4_PSI5_189K_CLK,                    /* name */
        3306U,                              /* value */
        {
            2U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 51U
    {
        P4_PSI5_1US_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 52U
    {
        P4_PSI5_S_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 53U
    {
        P4_PSI5_S_TRIG0_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 54U
    {
        P4_PSI5_S_TRIG1_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 55U
    {
        P4_PSI5_S_TRIG2_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 56U
    {
        P4_PSI5_S_TRIG3_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 57U
    {
        P4_PSI5_S_UART_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 58U
    {
        P4_PSI5_S_UTIL_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 59U
    {
        P4_PSI5_S_WDOG0_CLK,                    /* name */
        481U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 60U
    {
        P4_PSI5_S_WDOG1_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 61U
    {
        P4_PSI5_S_WDOG2_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 62U
    {
        P4_PSI5_S_WDOG3_CLK,                    /* name */
        48U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 63U
    {
        P4_QSPI0_2X_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 64U
    {
        P4_QSPI1_2X_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 65U
    {
        P5_AE_CLK,                    /* name */
        6U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 66U
    {
        P5_CANXL_PE_CLK,                    /* name */
        10U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 67U
    {
        P5_CANXL_CHI_CLK,                    /* name */
        5U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 68U
    {
        CLKOUT3_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 69U
    {
        P5_LIN_BAUD_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 70U
    {
        P5_REG_INTF_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 71U
    {
        P5_SYS_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 72U
    {
        P6_REG_INTF_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 73U
    {
        PERIPHPLL_PHI0_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 74U
    {
        PERIPHPLL_PHI1_CLK,                    /* name */
        24U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 75U
    {
        PERIPHPLL_PHI2_CLK,                    /* name */
        20U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 76U
    {
        PERIPHPLL_PHI3_CLK,                    /* name */
        9U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 77U
    {
        PERIPHPLL_PHI4_CLK,                    /* name */
        12U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 78U
    {
        PERIPHPLL_PHI5_CLK,                    /* name */
        15U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 79U
    {
        PERIPHPLL_PHI6_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 80U
    {
        RTU0_CORE_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 81U
    {
        RTU0_REG_INTF_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 82U
    {
        RTU1_CORE_CLK,                    /* name */
        1U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 83U
    {
        RTU1_REG_INTF_CLK,                    /* name */
        3U,                              /* value */
        {
            0U,
        }
    },
    #endif

    #if CLOCK_IP_CONFIGURED_DIVIDERS_0_NO > 84U
    {
        P4_SDHC_CLK,                    /* name */
        2U,                              /* value */
        {
            0U,
        }
    },
    #endif
};


static const Clock_Ip_DividerTriggerConfigType Clock_Ip_DividerTriggerConfigurations_0[CLOCK_IP_CONFIGURED_DIVIDER_TRIGGERS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_DIVIDER_TRIGGERS_0_NO > 0U
    {
        P0_GTM_CLK,          /* divider name */
        IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
        P0_GTM_CLK,          /* input source name */
    },
    #endif
};


static const Clock_Ip_FracDivConfigType Clock_Ip_FracDivsConfigurations_0[CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 0U
    {
        COREPLL_DFS0_CLK,                    /* name */
        1U,          /* Enabled */
        {
            1U,          /* integer part */
            0U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 1U
    {
        COREPLL_DFS1_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 2U
    {
        COREPLL_DFS2_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 3U
    {
        COREPLL_DFS3_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            0U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 4U
    {
        COREPLL_DFS4_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 5U
    {
        COREPLL_DFS5_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 6U
    {
        PERIPHPLL_DFS0_CLK,                    /* name */
        1U,          /* Enabled */
        {
            1U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 7U
    {
        PERIPHPLL_DFS1_CLK,                    /* name */
        1U,          /* Enabled */
        {
            1U,          /* integer part */
            18U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 8U
    {
        PERIPHPLL_DFS2_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            0U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 9U
    {
        PERIPHPLL_DFS3_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            14U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 10U
    {
        PERIPHPLL_DFS4_CLK,                    /* name */
        1U,          /* Enabled */
        {
            2U,          /* integer part */
            14U,          /* fractional part */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO > 11U
    {
        PERIPHPLL_DFS5_CLK,                    /* name */
        1U,          /* Enabled */
        {
            4U,          /* integer part */
            0U,          /* fractional part */
        },
    },
    #endif
};


static const Clock_Ip_ExtClkConfigType Clock_Ip_ExtClkConfigurations_0[CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO] = {

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 0U
    {
        ETH_RGMII_REF_CLK,                    /* name */
        50000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 1U
    {
        TMR_1588_CLK,                    /* name */
        0U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 2U
    {
        ETH0_EXT_RX_CLK,                    /* name */
        125000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 3U
    {
        ETH0_EXT_TX_CLK,                    /* name */
        50000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 4U
    {
        ETH1_EXT_RX_CLK,                    /* name */
        125000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 5U
    {
        ETH1_EXT_TX_CLK,                    /* name */
        50000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 6U
    {
        LFAST0_EXT_REF_CLK,                    /* name */
        20000000U,                              /* value */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO > 7U
    {
        LFAST1_EXT_REF_CLK,                    /* name */
        20000000U,                              /* value */
    },
    #endif
};


static const Clock_Ip_GateConfigType Clock_Ip_GatesConfigurations_0[CLOCK_IP_CONFIGURED_GATES_0_NO] = {

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 0U
    {
        DDR_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 1U
    {
        ADC0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 2U
    {
        ADC1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 3U
    {
        CE_EDMA_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 4U
    {
        CE_PIT0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 5U
    {
        CE_PIT1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 6U
    {
        CE_PIT2_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 7U
    {
        CE_PIT3_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 8U
    {
        CE_PIT4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 9U
    {
        CE_PIT5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 10U
    {
        CTU_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 11U
    {
        DMACRC0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 12U
    {
        DMACRC1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 13U
    {
        DMACRC4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 14U
    {
        DMACRC5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 15U
    {
        DMAMUX0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 16U
    {
        DMAMUX1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 17U
    {
        DMAMUX4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 18U
    {
        DMAMUX5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 19U
    {
        EDMA0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 20U
    {
        EDMA1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 21U
    {
        EDMA3_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 22U
    {
        EDMA4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 23U
    {
        EDMA5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 24U
    {
        ENET0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 25U
    {
        FLEXCAN0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 26U
    {
        FLEXCAN1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 27U
    {
        FLEXCAN2_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 28U
    {
        FLEXCAN3_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 29U
    {
        FLEXCAN4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 30U
    {
        FLEXCAN5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 31U
    {
        FLEXCAN6_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 32U
    {
        FLEXCAN7_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 33U
    {
        FLEXCAN8_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 34U
    {
        FLEXCAN9_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 35U
    {
        FLEXCAN10_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 36U
    {
        FLEXCAN11_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 37U
    {
        FLEXCAN12_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 38U
    {
        FLEXCAN13_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 39U
    {
        FLEXCAN14_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 40U
    {
        FLEXCAN15_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 41U
    {
        FLEXCAN16_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 42U
    {
        FLEXCAN17_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 43U
    {
        FLEXCAN18_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 44U
    {
        FLEXCAN19_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 45U
    {
        FLEXCAN20_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 46U
    {
        FLEXCAN21_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 47U
    {
        FLEXCAN22_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 48U
    {
        FLEXCAN23_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 49U
    {
        FRAY0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 50U
    {
        FRAY1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 51U
    {
        GTM_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 52U
    {
        IIIC0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 53U
    {
        IIIC1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 54U
    {
        IIIC2_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 55U
    {
        LIN0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 56U
    {
        LIN1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 57U
    {
        LIN2_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 58U
    {
        LIN3_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 59U
    {
        LIN4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 60U
    {
        LIN5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 61U
    {
        LIN6_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 62U
    {
        LIN7_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 63U
    {
        LIN8_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 64U
    {
        LIN9_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 65U
    {
        LIN10_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 66U
    {
        LIN11_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 67U
    {
        MSCDSPI_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 68U
    {
        MSCLIN_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 69U
    {
        NANO_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 70U
    {
        PIT0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 71U
    {
        PIT1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 72U
    {
        PIT4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 73U
    {
        PIT5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 74U
    {
        PSI5_0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 75U
    {
        PSI5_1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 76U
    {
        PSI5S_0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 77U
    {
        PSI5S_1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 78U
    {
        QSPI0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 79U
    {
        QSPI1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 80U
    {
        RXLUT_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 81U
    {
        SDHC0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 82U
    {
        SINC_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 83U
    {
        SIPI0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 84U
    {
        SIPI1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 85U
    {
        SIUL2_0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 86U
    {
        SIUL2_1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 87U
    {
        SIUL2_4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 88U
    {
        SIUL2_5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 89U
    {
        SPI0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 90U
    {
        SPI1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 91U
    {
        SPI2_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 92U
    {
        SPI3_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 93U
    {
        SPI4_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 94U
    {
        SPI5_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 95U
    {
        SPI6_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 96U
    {
        SPI7_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 97U
    {
        SPI8_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 98U
    {
        SPI9_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 99U
    {
        SRX0_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif

    #if CLOCK_IP_CONFIGURED_GATES_0_NO > 100U
    {
        SRX1_CLK,                    /* name */
        1U,                           /* enable */
    },
    #endif
};


static const Clock_Ip_CmuConfigType Clock_Ip_CmuConfigurations_0[CLOCK_IP_CONFIGURED_CMUS_0_NO] = {


    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 0U
    {
        P2_SYS_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor SMU__CMU_FC */
        (                                           /* IER for SMU__CMU_FC */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 1U
    {
        P0_REG_INTF_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_0 */
        (                                           /* IER for CMU_FC_0 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        133333333U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 2U
    {
        P1_REG_INTF_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_1 */
        (                                           /* IER for CMU_FC_1 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        133333333U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 3U
    {
        FIRC_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_2A */
        (                                           /* IER for CMU_FC_2A */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        48000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 4U
    {
        FXOSC_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_2B */
        (                                           /* IER for CMU_FC_2B */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        40000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 5U
    {
        P2_MATH_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_2C */
        (                                           /* IER for CMU_FC_2C */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 6U
    {
        P3_SYS_MON1_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_3 */
        (                                           /* IER for CMU_FC_3 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 7U
    {
        P4_REG_INTF_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_4 */
        (                                           /* IER for CMU_FC_4 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        133333333U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 8U
    {
        P5_REG_INTF_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_5 */
        (                                           /* IER for CMU_FC_5 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        48000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 9U
    {
        DDR_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_6 */
        (                                           /* IER for CMU_FC_6 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        200000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 10U
    {
        P3_SYS_MON2_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CE_CMU_FC_0 */
        (                                           /* IER for CE_CMU_FC_0 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 11U
    {
        P3_SYS_MON3_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CE_CMU_FC_1 */
        (                                           /* IER for CE_CMU_FC_1 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 12U
    {
        CE_SYS_DIV2_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CE_CMU_FC_2 */
        (                                           /* IER for CE_CMU_FC_2 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        200000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 13U
    {
        P0_CLKOUT_SRC_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_DEBUG_1 */
        (                                           /* IER for CMU_FC_DEBUG_1 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        48000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif

    #if CLOCK_IP_CONFIGURED_CMUS_0_NO > 14U
    {
        P1_CLKOUT_SRC_CLK,            /* Clock name associated to clock monitor. */
        0U,                   /*Enable/disable clock monitor CMU_FC_DEBUG_2 */
        (                                           /* IER for CMU_FC_DEBUG_2 */
            CMU_FC_IER_FLLIE(0) |
            CMU_FC_IER_FHHIE(0) |
            CMU_FC_IER_FLLAIE(0) |
            CMU_FC_IER_FHHAIE(0)
        ),
        400000000U,
        {
            0U,          /* Start index in register values array */
            0U,          /* End index in register values array */
        },
    },
    #endif
};


static const Clock_Ip_ConfiguredFrequencyType Clock_Ip_ConfiguredFrequencyConfigurations_0[CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT] = {

    {
        CLOCK_IS_OFF,
        0U,
    },

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 1U
    {
        FIRC_CLK,
        48000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 2U
    {
        FXOSC_CLK,
        40000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 3U
    {
        CE_SYS_DIV4_CLK,
        100000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 4U
    {
        P0_REG_INTF_CLK,
        133333333U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 5U
    {
        P1_REG_INTF_CLK,
        133333333U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 6U
    {
        P2_MATH_DIV3_CLK,
        133333333U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 7U
    {
        P2_REG_INTF_CLK,
        16000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 8U
    {
        P2_SYS_DIV4_CLK,
        100000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 9U
    {
        P3_REG_INTF_CLK,
        48000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 10U
    {
        P4_REG_INTF_CLK,
        133333333U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 11U
    {
        P5_REG_INTF_CLK,
        48000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 12U
    {
        P6_REG_INTF_CLK,
        48000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 13U
    {
        RTU0_CORE_CLK,
        1000000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 14U
    {
        RTU0_REG_INTF_CLK,
        133333333U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 15U
    {
        RTU1_CORE_CLK,
        1000000000U,
    },
    #endif

    #if CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT > 16U
    {
        RTU1_REG_INTF_CLK,
        133333333U,
    },
    #endif
};


/* *************************************************************************
 * Configuration structure for Clock Configuration 
 * ************************************************************************* */
const Clock_Ip_ClockConfigType Clock_Ip_aClockConfig[1U] = {

    /*! @brief User Configuration structure clock_Cfg_0 */
    {
        0U,                          /* clkConfigId */

        (NULL_PTR),               /* Register data if register value optimization is enabled */
        0U,                       /* ircoscsCount */
        1U,                       /* xoscsCount */
        5U,                       /* pllsCount */
        63U,                       /* selectorsCount */
        85U,                       /* dividersCount */
        1U,                       /* dividerTriggersCount */
        12U,                       /* fracDivsCount */
        8U,                       /* extClksCount */
        101U,                       /* gatesCount */
        0U,                       /* pcfsCount */
        15U,                       /* cmusCount */
        17U,                       /* configureFrequenciesCount */

        (NULL_PTR),                       /* Ircosc configurations */
        (&Clock_Ip_XoscConfigurations_0),                      /* Xosc configurations */
        (&Clock_Ip_PllConfigurations_0),                       /* Pll configurations */
        (&Clock_Ip_SelectorConfigurations_0),                  /* Selectors configurations */
        (&Clock_Ip_DividerConfigurations_0),                   /* dividers configurations */
        (&Clock_Ip_DividerTriggerConfigurations_0),            /* dividerTriggers configurations */
        (&Clock_Ip_FracDivsConfigurations_0),            /* fracDivs configurations */
        (&Clock_Ip_ExtClkConfigurations_0),                    /* extClks configurations */
        (&Clock_Ip_GatesConfigurations_0),                     /* gates configurations */
        (NULL_PTR),                       /* pcfs configurations */
        (&Clock_Ip_CmuConfigurations_0),                       /* cmus configurations */
        (&Clock_Ip_ConfiguredFrequencyConfigurations_0),       /* configureFrequencies configurations */
    },
};


#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
