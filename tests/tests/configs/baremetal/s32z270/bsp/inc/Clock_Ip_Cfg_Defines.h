/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
*   @file       Clock_Ip_Cfg_Defines.h
*   @version    2.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/

#ifndef CLOCK_IP_CFG_DEFINES_H
#define CLOCK_IP_CFG_DEFINES_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "S32Z2_COMMON.h"
#include "S32Z2_MC_CGM.h"
#include "S32Z2_RTU_MC_CGM.h"
#include "S32Z2_FXOSC.h"
#include "S32Z2_PLLDIG.h"
#include "S32Z2_MC_ME.h"
#include "S32Z2_DFS.h"
#include "S32Z2_CMU_FC.h"
#include "S32Z2_GPR0.h"
#include "S32Z2_GPR0_PCTL.h"
#include "S32Z2_GPR1.h"
#include "S32Z2_GPR1_PCTL.h"
#include "S32Z2_GPR3.h"
#include "S32Z2_GPR3_PCTL.h"
#include "S32Z2_GPR4.h"
#include "S32Z2_GPR4_PCTL.h"
#include "S32Z2_GPR5.h"
#include "S32Z2_GPR5_PCTL.h"
#include "S32Z2_GPR6_PCTL.h"
#include "S32Z2_SRAMCTL.h"
#include "S32Z2_LFAST.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_CFG_DEFINES_VENDOR_ID                       43
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_CFG_DEFINES_SW_MAJOR_VERSION                2
#define CLOCK_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define CLOCK_IP_CFG_DEFINES_SW_PATCH_VERSION                0

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Derivative used.
*/
#define CLOCK_IP_DERIVATIVE_001
/**
* @brief            Platform used.
*/
#define CLOCK_IP_PLATFORM_SPECIFIC

/**
* @brief            Max number of internal oscillators
*/
#define CLOCK_IP_IRCOSCS_COUNT       (2U)

/**
* @brief            Max number of external oscillators
*/
#define CLOCK_IP_XOSCS_COUNT       (1U)

/**
* @brief            Max number of pll devices
*/
#define CLOCK_IP_PLLS_COUNT       (5U)

/**
* @brief            Max number of selectors
*/
#define CLOCK_IP_SELECTORS_COUNT       (63U)

/**
* @brief            Max number of dividers
*/
#define CLOCK_IP_DIVIDERS_COUNT       (85U)

/**
* @brief            Max number of divider triggers
*/
#define CLOCK_IP_DIVIDER_TRIGGERS_COUNT       (1U)

/**
* @brief            Max number of fractional dividers
*/
#define CLOCK_IP_FRACTIONAL_DIVIDERS_COUNT       (12U)

/**
* @brief            Max number of external clocks
*/
#define CLOCK_IP_EXT_CLKS_COUNT       (8U)

/**
* @brief            Max number of pcfs
*/
#define CLOCK_IP_PCFS_COUNT       (11U)

/**
* @brief            Max number of clock gates
*/
#define CLOCK_IP_GATES_COUNT       (101U)

/**
* @brief            Max number of clock monitoring units
*/
#define CLOCK_IP_CMUS_COUNT       (25U)

/**
* @brief            Max number of configured frequencies values
*/
#define CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT       (17U)

/**
* @brief            Number of clock configurations 0
*/
#define CLOCK_IP_CONFIGURED_XOSCS_0_NO       (1U)
#define CLOCK_IP_CONFIGURED_PLLS_0_NO       (5U)
#define CLOCK_IP_CONFIGURED_SELECTORS_0_NO       (63U)
#define CLOCK_IP_CONFIGURED_DIVIDERS_0_NO       (85U)
#define CLOCK_IP_CONFIGURED_DIVIDER_TRIGGERS_0_NO       (1U)
#define CLOCK_IP_CONFIGURED_FRACTIONAL_DIVIDERS_0_NO       (12U)
#define CLOCK_IP_CONFIGURED_EXT_CLKS_0_NO       (8U)
#define CLOCK_IP_CONFIGURED_GATES_0_NO       (101U)
#define CLOCK_IP_CONFIGURED_CMUS_0_NO       (15U)

/**
* @brief            Firc frequency.
*/
#define CLOCK_IP_FIRC_FREQUENCY                48000000U

/**
* @brief            Sirc frequency.
*/
#define CLOCK_IP_SIRC_FREQUENCY                32000U

/**
* @brief            Clock ip supports clock frequency.
*/
#define CLOCK_IP_GET_FREQUENCY_API                (STD_ON)

/**
* @brief            Supports wait states configuration
*/
#define CLOCK_IP_SUPPORTS_WAIT_STATES                (STD_ON)


/**
* @brief            Default fxosc frequency.
*/
#define CLOCK_IP_DEFAULT_FXOSC_FREQUENCY                40000000U

/**
* @brief            Clock ip supports ram wait states.
*/
#define CLOCK_IP_HAS_RAM_WAIT_STATES

/**
* @brief            Supported clocks.
*/
#define CLOCK_IP_HAS_FIRC_CLK         1U
#define CLOCK_IP_HAS_FXOSC_CLK         2U
#define CLOCK_IP_HAS_SIRC_CLK         3U
#define CLOCK_IP_HAS_COREPLL_CLK         4U
#define CLOCK_IP_HAS_PERIPHPLL_CLK         5U
#define CLOCK_IP_HAS_DDRPLL_CLK         6U
#define CLOCK_IP_HAS_LFAST0_PLL_CLK         7U
#define CLOCK_IP_HAS_LFAST1_PLL_CLK         8U
#define CLOCK_IP_HAS_COREPLL_PHI0_CLK         9U
#define CLOCK_IP_HAS_COREPLL_DFS0_CLK         10U
#define CLOCK_IP_HAS_COREPLL_DFS1_CLK         11U
#define CLOCK_IP_HAS_COREPLL_DFS2_CLK         12U
#define CLOCK_IP_HAS_COREPLL_DFS3_CLK         13U
#define CLOCK_IP_HAS_COREPLL_DFS4_CLK         14U
#define CLOCK_IP_HAS_COREPLL_DFS5_CLK         15U
#define CLOCK_IP_HAS_PERIPHPLL_PHI0_CLK         16U
#define CLOCK_IP_HAS_PERIPHPLL_PHI1_CLK         17U
#define CLOCK_IP_HAS_PERIPHPLL_PHI2_CLK         18U
#define CLOCK_IP_HAS_PERIPHPLL_PHI3_CLK         19U
#define CLOCK_IP_HAS_PERIPHPLL_PHI4_CLK         20U
#define CLOCK_IP_HAS_PERIPHPLL_PHI5_CLK         21U
#define CLOCK_IP_HAS_PERIPHPLL_PHI6_CLK         22U
#define CLOCK_IP_HAS_PERIPHPLL_DFS0_CLK         23U
#define CLOCK_IP_HAS_PERIPHPLL_DFS1_CLK         24U
#define CLOCK_IP_HAS_PERIPHPLL_DFS2_CLK         25U
#define CLOCK_IP_HAS_PERIPHPLL_DFS3_CLK         26U
#define CLOCK_IP_HAS_PERIPHPLL_DFS4_CLK         27U
#define CLOCK_IP_HAS_PERIPHPLL_DFS5_CLK         28U
#define CLOCK_IP_HAS_DDRPLL_PHI0_CLK         29U
#define CLOCK_IP_HAS_LFAST0_PLL_PH0_CLK         30U
#define CLOCK_IP_HAS_LFAST1_PLL_PH0_CLK         31U
#define CLOCK_IP_HAS_ETH_RGMII_REF_CLK         32U
#define CLOCK_IP_HAS_TMR_1588_CLK         33U
#define CLOCK_IP_HAS_ETH0_EXT_RX_CLK         34U
#define CLOCK_IP_HAS_ETH0_EXT_TX_CLK         35U
#define CLOCK_IP_HAS_ETH1_EXT_RX_CLK         36U
#define CLOCK_IP_HAS_ETH1_EXT_TX_CLK         37U
#define CLOCK_IP_HAS_LFAST0_EXT_REF_CLK         38U
#define CLOCK_IP_HAS_LFAST1_EXT_REF_CLK         39U
#define CLOCK_IP_HAS_DDR_CLK         40U
#define CLOCK_IP_HAS_P0_SYS_CLK         41U
#define CLOCK_IP_HAS_P1_SYS_CLK         42U
#define CLOCK_IP_HAS_P1_SYS_DIV2_CLK         43U
#define CLOCK_IP_HAS_P1_SYS_DIV4_CLK         44U
#define CLOCK_IP_HAS_P2_SYS_CLK         45U
#define CLOCK_IP_HAS_CORE_M33_CLK         46U
#define CLOCK_IP_HAS_P2_SYS_DIV2_CLK         47U
#define CLOCK_IP_HAS_P2_SYS_DIV4_CLK         48U
#define CLOCK_IP_HAS_P3_SYS_CLK         49U
#define CLOCK_IP_HAS_CE_SYS_DIV2_CLK         50U
#define CLOCK_IP_HAS_CE_SYS_DIV4_CLK         51U
#define CLOCK_IP_HAS_P3_SYS_DIV2_NOC_CLK         52U
#define CLOCK_IP_HAS_P3_SYS_DIV4_CLK         53U
#define CLOCK_IP_HAS_P4_SYS_CLK         54U
#define CLOCK_IP_HAS_P4_SYS_DIV2_CLK         55U
#define CLOCK_IP_HAS_HSE_SYS_DIV2_CLK         56U
#define CLOCK_IP_HAS_P5_SYS_CLK         57U
#define CLOCK_IP_HAS_P5_SYS_DIV2_CLK         58U
#define CLOCK_IP_HAS_P5_SYS_DIV4_CLK         59U
#define CLOCK_IP_HAS_P2_MATH_CLK         60U
#define CLOCK_IP_HAS_P2_MATH_DIV3_CLK         61U
#define CLOCK_IP_HAS_GLB_LBIST_CLK         62U
#define CLOCK_IP_HAS_RTU0_CORE_CLK         63U
#define CLOCK_IP_HAS_RTU0_CORE_DIV2_CLK         64U
#define CLOCK_IP_HAS_RTU1_CORE_CLK         65U
#define CLOCK_IP_HAS_RTU1_CORE_DIV2_CLK         66U
#define CLOCK_IP_HAS_P0_PSI5_S_UTIL_CLK         67U
#define CLOCK_IP_HAS_P4_PSI5_S_UTIL_CLK         68U
#define CLOCK_IP_FEATURE_PRODUCERS_NO         69U
#define CLOCK_IP_HAS_ADC0_CLK         70U
#define CLOCK_IP_HAS_ADC1_CLK         71U
#define CLOCK_IP_HAS_CE_EDMA_CLK         72U
#define CLOCK_IP_HAS_CE_PIT0_CLK         73U
#define CLOCK_IP_HAS_CE_PIT1_CLK         74U
#define CLOCK_IP_HAS_CE_PIT2_CLK         75U
#define CLOCK_IP_HAS_CE_PIT3_CLK         76U
#define CLOCK_IP_HAS_CE_PIT4_CLK         77U
#define CLOCK_IP_HAS_CE_PIT5_CLK         78U
#define CLOCK_IP_HAS_CLKOUT0_CLK         79U
#define CLOCK_IP_HAS_CLKOUT1_CLK         80U
#define CLOCK_IP_HAS_CLKOUT2_CLK         81U
#define CLOCK_IP_HAS_CLKOUT3_CLK         82U
#define CLOCK_IP_HAS_CLKOUT4_CLK         83U
#define CLOCK_IP_HAS_CTU_CLK         84U
#define CLOCK_IP_HAS_DMACRC0_CLK         85U
#define CLOCK_IP_HAS_DMACRC1_CLK         86U
#define CLOCK_IP_HAS_DMACRC4_CLK         87U
#define CLOCK_IP_HAS_DMACRC5_CLK         88U
#define CLOCK_IP_HAS_DMAMUX0_CLK         89U
#define CLOCK_IP_HAS_DMAMUX1_CLK         90U
#define CLOCK_IP_HAS_DMAMUX4_CLK         91U
#define CLOCK_IP_HAS_DMAMUX5_CLK         92U
#define CLOCK_IP_HAS_EDMA0_CLK         93U
#define CLOCK_IP_HAS_EDMA1_CLK         94U
#define CLOCK_IP_HAS_EDMA3_CLK         95U
#define CLOCK_IP_HAS_EDMA4_CLK         96U
#define CLOCK_IP_HAS_EDMA5_CLK         97U
#define CLOCK_IP_HAS_ETH0_TX_MII_CLK         98U
#define CLOCK_IP_HAS_ENET0_CLK         99U
#define CLOCK_IP_HAS_P3_CAN_PE_CLK         100U
#define CLOCK_IP_HAS_FLEXCAN0_CLK         101U
#define CLOCK_IP_HAS_FLEXCAN1_CLK         102U
#define CLOCK_IP_HAS_FLEXCAN2_CLK         103U
#define CLOCK_IP_HAS_FLEXCAN3_CLK         104U
#define CLOCK_IP_HAS_FLEXCAN4_CLK         105U
#define CLOCK_IP_HAS_FLEXCAN5_CLK         106U
#define CLOCK_IP_HAS_FLEXCAN6_CLK         107U
#define CLOCK_IP_HAS_FLEXCAN7_CLK         108U
#define CLOCK_IP_HAS_FLEXCAN8_CLK         109U
#define CLOCK_IP_HAS_FLEXCAN9_CLK         110U
#define CLOCK_IP_HAS_FLEXCAN10_CLK         111U
#define CLOCK_IP_HAS_FLEXCAN11_CLK         112U
#define CLOCK_IP_HAS_FLEXCAN12_CLK         113U
#define CLOCK_IP_HAS_FLEXCAN13_CLK         114U
#define CLOCK_IP_HAS_FLEXCAN14_CLK         115U
#define CLOCK_IP_HAS_FLEXCAN15_CLK         116U
#define CLOCK_IP_HAS_FLEXCAN16_CLK         117U
#define CLOCK_IP_HAS_FLEXCAN17_CLK         118U
#define CLOCK_IP_HAS_FLEXCAN18_CLK         119U
#define CLOCK_IP_HAS_FLEXCAN19_CLK         120U
#define CLOCK_IP_HAS_FLEXCAN20_CLK         121U
#define CLOCK_IP_HAS_FLEXCAN21_CLK         122U
#define CLOCK_IP_HAS_FLEXCAN22_CLK         123U
#define CLOCK_IP_HAS_FLEXCAN23_CLK         124U
#define CLOCK_IP_HAS_P0_FR_PE_CLK         125U
#define CLOCK_IP_HAS_FRAY0_CLK         126U
#define CLOCK_IP_HAS_FRAY1_CLK         127U
#define CLOCK_IP_HAS_GTM_CLK         128U
#define CLOCK_IP_HAS_IIIC0_CLK         129U
#define CLOCK_IP_HAS_IIIC1_CLK         130U
#define CLOCK_IP_HAS_IIIC2_CLK         131U
#define CLOCK_IP_HAS_P0_LIN_BAUD_CLK         132U
#define CLOCK_IP_HAS_LIN0_CLK         133U
#define CLOCK_IP_HAS_LIN1_CLK         134U
#define CLOCK_IP_HAS_LIN2_CLK         135U
#define CLOCK_IP_HAS_P1_LIN_BAUD_CLK         136U
#define CLOCK_IP_HAS_LIN3_CLK         137U
#define CLOCK_IP_HAS_LIN4_CLK         138U
#define CLOCK_IP_HAS_LIN5_CLK         139U
#define CLOCK_IP_HAS_P4_LIN_BAUD_CLK         140U
#define CLOCK_IP_HAS_LIN6_CLK         141U
#define CLOCK_IP_HAS_LIN7_CLK         142U
#define CLOCK_IP_HAS_LIN8_CLK         143U
#define CLOCK_IP_HAS_P5_LIN_BAUD_CLK         144U
#define CLOCK_IP_HAS_LIN9_CLK         145U
#define CLOCK_IP_HAS_LIN10_CLK         146U
#define CLOCK_IP_HAS_LIN11_CLK         147U
#define CLOCK_IP_HAS_MSCDSPI_CLK         148U
#define CLOCK_IP_HAS_MSCLIN_CLK         149U
#define CLOCK_IP_HAS_NANO_CLK         150U
#define CLOCK_IP_HAS_P0_CLKOUT_SRC_CLK         151U
#define CLOCK_IP_HAS_P0_CTU_PER_CLK         152U
#define CLOCK_IP_HAS_P0_DSPI_MSC_CLK         153U
#define CLOCK_IP_HAS_P0_EMIOS_LCU_CLK         154U
#define CLOCK_IP_HAS_P0_GTM_CLK         155U
#define CLOCK_IP_HAS_P0_GTM_NOC_CLK         156U
#define CLOCK_IP_HAS_P0_GTM_TS_CLK         157U
#define CLOCK_IP_HAS_P0_LIN_CLK         158U
#define CLOCK_IP_HAS_P0_NANO_CLK         159U
#define CLOCK_IP_HAS_P0_PSI5_125K_CLK         160U
#define CLOCK_IP_HAS_P0_PSI5_189K_CLK         161U
#define CLOCK_IP_HAS_P0_PSI5_S_BAUD_CLK         162U
#define CLOCK_IP_HAS_P0_PSI5_S_CORE_CLK         163U
#define CLOCK_IP_HAS_P0_PSI5_S_TRIG0_CLK         164U
#define CLOCK_IP_HAS_P0_PSI5_S_TRIG1_CLK         165U
#define CLOCK_IP_HAS_P0_PSI5_S_TRIG2_CLK         166U
#define CLOCK_IP_HAS_P0_PSI5_S_TRIG3_CLK         167U
#define CLOCK_IP_HAS_P0_PSI5_S_UART_CLK         168U
#define CLOCK_IP_HAS_P0_PSI5_S_WDOG0_CLK         169U
#define CLOCK_IP_HAS_P0_PSI5_S_WDOG1_CLK         170U
#define CLOCK_IP_HAS_P0_PSI5_S_WDOG2_CLK         171U
#define CLOCK_IP_HAS_P0_PSI5_S_WDOG3_CLK         172U
#define CLOCK_IP_HAS_P0_REG_INTF_2X_CLK         173U
#define CLOCK_IP_HAS_P0_REG_INTF_CLK         174U
#define CLOCK_IP_HAS_P1_CLKOUT_SRC_CLK         175U
#define CLOCK_IP_HAS_P1_DSPI60_CLK         176U
#define CLOCK_IP_HAS_ETH_TS_CLK         177U
#define CLOCK_IP_HAS_ETH_TS_DIV4_CLK         178U
#define CLOCK_IP_HAS_ETH0_REF_RMII_CLK         179U
#define CLOCK_IP_HAS_ETH0_RX_MII_CLK         180U
#define CLOCK_IP_HAS_ETH0_RX_RGMII_CLK         181U
#define CLOCK_IP_HAS_ETH0_TX_RGMII_CLK         182U
#define CLOCK_IP_HAS_ETH0_PS_TX_CLK         183U
#define CLOCK_IP_HAS_ETH1_REF_RMII_CLK         184U
#define CLOCK_IP_HAS_ETH1_RX_MII_CLK         185U
#define CLOCK_IP_HAS_ETH1_RX_RGMII_CLK         186U
#define CLOCK_IP_HAS_ETH1_TX_MII_CLK         187U
#define CLOCK_IP_HAS_ETH1_TX_RGMII_CLK         188U
#define CLOCK_IP_HAS_ETH1_PS_TX_CLK         189U
#define CLOCK_IP_HAS_P1_LFAST0_REF_CLK         190U
#define CLOCK_IP_HAS_P1_LFAST1_REF_CLK         191U
#define CLOCK_IP_HAS_P1_NETC_AXI_CLK         192U
#define CLOCK_IP_HAS_P1_LIN_CLK         193U
#define CLOCK_IP_HAS_P1_REG_INTF_CLK         194U
#define CLOCK_IP_HAS_P2_DBG_ATB_CLK         195U
#define CLOCK_IP_HAS_P2_REG_INTF_CLK         196U
#define CLOCK_IP_HAS_P3_AES_CLK         197U
#define CLOCK_IP_HAS_P3_CLKOUT_SRC_CLK         198U
#define CLOCK_IP_HAS_P3_DBG_TS_CLK         199U
#define CLOCK_IP_HAS_P3_REG_INTF_CLK         200U
#define CLOCK_IP_HAS_P3_SYS_MON1_CLK         201U
#define CLOCK_IP_HAS_P3_SYS_MON2_CLK         202U
#define CLOCK_IP_HAS_P3_SYS_MON3_CLK         203U
#define CLOCK_IP_HAS_P4_CLKOUT_SRC_CLK         204U
#define CLOCK_IP_HAS_P4_DSPI60_CLK         205U
#define CLOCK_IP_HAS_P4_EMIOS_LCU_CLK         206U
#define CLOCK_IP_HAS_P4_LIN_CLK         207U
#define CLOCK_IP_HAS_P4_PSI5_125K_CLK         208U
#define CLOCK_IP_HAS_P4_PSI5_189K_CLK         209U
#define CLOCK_IP_HAS_P4_PSI5_S_BAUD_CLK         210U
#define CLOCK_IP_HAS_P4_PSI5_S_CORE_CLK         211U
#define CLOCK_IP_HAS_P4_PSI5_S_TRIG0_CLK         212U
#define CLOCK_IP_HAS_P4_PSI5_S_TRIG1_CLK         213U
#define CLOCK_IP_HAS_P4_PSI5_S_TRIG2_CLK         214U
#define CLOCK_IP_HAS_P4_PSI5_S_TRIG3_CLK         215U
#define CLOCK_IP_HAS_P4_PSI5_S_UART_CLK         216U
#define CLOCK_IP_HAS_P4_PSI5_S_WDOG0_CLK         217U
#define CLOCK_IP_HAS_P4_PSI5_S_WDOG1_CLK         218U
#define CLOCK_IP_HAS_P4_PSI5_S_WDOG2_CLK         219U
#define CLOCK_IP_HAS_P4_PSI5_S_WDOG3_CLK         220U
#define CLOCK_IP_HAS_P4_QSPI0_2X_CLK         221U
#define CLOCK_IP_HAS_P4_QSPI0_1X_CLK         222U
#define CLOCK_IP_HAS_P4_QSPI1_2X_CLK         223U
#define CLOCK_IP_HAS_P4_QSPI1_1X_CLK         224U
#define CLOCK_IP_HAS_P4_REG_INTF_2X_CLK         225U
#define CLOCK_IP_HAS_P4_REG_INTF_CLK         226U
#define CLOCK_IP_HAS_P4_SDHC_IP_CLK         227U
#define CLOCK_IP_HAS_P4_SDHC_IP_DIV2_CLK         228U
#define CLOCK_IP_HAS_P5_DIPORT_CLK         229U
#define CLOCK_IP_HAS_P5_AE_CLK         230U
#define CLOCK_IP_HAS_P5_CANXL_PE_CLK         231U
#define CLOCK_IP_HAS_P5_CANXL_CHI_CLK         232U
#define CLOCK_IP_HAS_P5_CLKOUT_SRC_CLK         233U
#define CLOCK_IP_HAS_P5_LIN_CLK         234U
#define CLOCK_IP_HAS_P5_REG_INTF_CLK         235U
#define CLOCK_IP_HAS_P6_REG_INTF_CLK         236U
#define CLOCK_IP_HAS_PIT0_CLK         237U
#define CLOCK_IP_HAS_PIT1_CLK         238U
#define CLOCK_IP_HAS_PIT4_CLK         239U
#define CLOCK_IP_HAS_PIT5_CLK         240U
#define CLOCK_IP_HAS_P0_PSI5_1US_CLK         241U
#define CLOCK_IP_HAS_PSI5_0_CLK         242U
#define CLOCK_IP_HAS_P4_PSI5_1US_CLK         243U
#define CLOCK_IP_HAS_PSI5_1_CLK         244U
#define CLOCK_IP_HAS_PSI5S_0_CLK         245U
#define CLOCK_IP_HAS_PSI5S_1_CLK         246U
#define CLOCK_IP_HAS_QSPI0_CLK         247U
#define CLOCK_IP_HAS_QSPI1_CLK         248U
#define CLOCK_IP_HAS_RTU0_CORE_MON1_CLK         249U
#define CLOCK_IP_HAS_RTU0_CORE_MON2_CLK         250U
#define CLOCK_IP_HAS_RTU0_CORE_DIV2_MON1_CLK         251U
#define CLOCK_IP_HAS_RTU0_CORE_DIV2_MON2_CLK         252U
#define CLOCK_IP_HAS_RTU0_CORE_DIV2_MON3_CLK         253U
#define CLOCK_IP_HAS_RTU0_REG_INTF_CLK         254U
#define CLOCK_IP_HAS_RTU1_CORE_MON1_CLK         255U
#define CLOCK_IP_HAS_RTU1_CORE_MON2_CLK         256U
#define CLOCK_IP_HAS_RTU1_CORE_DIV2_MON1_CLK         257U
#define CLOCK_IP_HAS_RTU1_CORE_DIV2_MON2_CLK         258U
#define CLOCK_IP_HAS_RTU1_CORE_DIV2_MON3_CLK         259U
#define CLOCK_IP_HAS_RTU1_REG_INTF_CLK         260U
#define CLOCK_IP_HAS_P4_SDHC_CLK         261U
#define CLOCK_IP_HAS_RXLUT_CLK         262U
#define CLOCK_IP_HAS_SDHC0_CLK         263U
#define CLOCK_IP_HAS_SINC_CLK         264U
#define CLOCK_IP_HAS_SIPI0_CLK         265U
#define CLOCK_IP_HAS_SIPI1_CLK         266U
#define CLOCK_IP_HAS_SIUL2_0_CLK         267U
#define CLOCK_IP_HAS_SIUL2_1_CLK         268U
#define CLOCK_IP_HAS_SIUL2_4_CLK         269U
#define CLOCK_IP_HAS_SIUL2_5_CLK         270U
#define CLOCK_IP_HAS_P0_DSPI_CLK         271U
#define CLOCK_IP_HAS_SPI0_CLK         272U
#define CLOCK_IP_HAS_SPI1_CLK         273U
#define CLOCK_IP_HAS_P1_DSPI_CLK         274U
#define CLOCK_IP_HAS_SPI2_CLK         275U
#define CLOCK_IP_HAS_SPI3_CLK         276U
#define CLOCK_IP_HAS_SPI4_CLK         277U
#define CLOCK_IP_HAS_P4_DSPI_CLK         278U
#define CLOCK_IP_HAS_SPI5_CLK         279U
#define CLOCK_IP_HAS_SPI6_CLK         280U
#define CLOCK_IP_HAS_SPI7_CLK         281U
#define CLOCK_IP_HAS_P5_DSPI_CLK         282U
#define CLOCK_IP_HAS_SPI8_CLK         283U
#define CLOCK_IP_HAS_SPI9_CLK         284U
#define CLOCK_IP_HAS_SRX0_CLK         285U
#define CLOCK_IP_HAS_SRX1_CLK         286U
#define CLOCK_IP_HAS_CORE_PLL_REFCLKOUT         287U
#define CLOCK_IP_HAS_CORE_PLL_FBCLKOUT         288U
#define CLOCK_IP_HAS_PERIPH_PLL_REFCLKOUT         289U
#define CLOCK_IP_HAS_PERIPH_PLL_FBCLKOUT         290U
#define CLOCK_IP_FEATURE_NAMES_NO         291U

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif /* #ifndef CLOCK_IP_CFG_DEFINES_H */

/** @} */
