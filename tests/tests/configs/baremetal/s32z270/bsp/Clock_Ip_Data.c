/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Data.c
*   @version    2.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


#include "Clock_Ip_Private.h"

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_DATA_VENDOR_ID_C                      43
#define CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_DATA_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_DATA_SW_MINOR_VERSION_C               0
#define CLOCK_IP_DATA_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_DATA_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Data.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_DATA_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_DATA_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Clock_Ip_Data.c file and RegLockMacros.h file are of the same Autosar version */
    #if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Clock_Ip_Data.c and RegLockMacros.h are different"
    #endif
    #endif
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/



#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_HWMUX_DIV_CMU                 1U
#define CLOCK_IP_PCFS_DFS                      1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_CMU                     2U
#define CLOCK_IP_PCFS_PLL_OUT                  2U
#define CLOCK_IP_PLL                           2U
#define CLOCK_IP_DFS                           2U
#define CLOCK_IP_HWMUX_CMU_GATE                3U
#define CLOCK_IP_PLL_OUT                       3U
#define CLOCK_IP_LFASTPLL                      3U
#define CLOCK_IP_CMU                           4U
#define CLOCK_IP_HWMUX                         4U
#define CLOCK_IP_FAST_XOSC_CMU                 5U
#define CLOCK_IP_HWMUX_DIV                     5U
#define CLOCK_IP_HWMUX_AE                      6U
#define CLOCK_IP_HWMUX_DIV_TRIGGER             7U
#define CLOCK_IP_SWMUX_DIV                     8U
#define CLOCK_IP_CLKOUT                        9U
#define CLOCK_IP_CLKOUT_CMU                    9U
#define CLOCK_IP_HWMUX_MUL_DIV                 10U
#define CLOCK_IP_HWMUX_DIV_PCFS                11U

#define CLOCK_IP_DDR_EXTENSION                          0U
#define CLOCK_IP_P0_SYS_EXTENSION                       1U
#define CLOCK_IP_P1_SYS_EXTENSION                       2U
#define CLOCK_IP_P1_SYS_DIV2_EXTENSION                  3U
#define CLOCK_IP_P1_SYS_DIV4_EXTENSION                  4U
#define CLOCK_IP_P2_SYS_EXTENSION                       5U
#define CLOCK_IP_CORE_M33_EXTENSION                     6U
#define CLOCK_IP_P2_SYS_DIV2_EXTENSION                  7U
#define CLOCK_IP_P2_SYS_DIV4_EXTENSION                  8U
#define CLOCK_IP_P3_SYS_EXTENSION                       9U
#define CLOCK_IP_CE_SYS_DIV2_EXTENSION                  10U
#define CLOCK_IP_CE_SYS_DIV4_EXTENSION                  11U
#define CLOCK_IP_P3_SYS_DIV2_NOC_EXTENSION              12U
#define CLOCK_IP_P3_SYS_DIV4_EXTENSION                  13U
#define CLOCK_IP_P4_SYS_EXTENSION                       14U
#define CLOCK_IP_P4_SYS_DIV2_EXTENSION                  15U
#define CLOCK_IP_HSE_SYS_DIV2_EXTENSION                 16U
#define CLOCK_IP_P5_SYS_EXTENSION                       17U
#define CLOCK_IP_P5_SYS_DIV2_EXTENSION                  18U
#define CLOCK_IP_P5_SYS_DIV4_EXTENSION                  19U
#define CLOCK_IP_P2_MATH_EXTENSION                      20U
#define CLOCK_IP_P2_MATH_DIV3_EXTENSION                 21U
#define CLOCK_IP_GLB_LBIST_EXTENSION                    22U
#define CLOCK_IP_RTU0_CORE_EXTENSION                    23U
#define CLOCK_IP_RTU0_CORE_DIV2_EXTENSION               24U
#define CLOCK_IP_RTU1_CORE_EXTENSION                    25U
#define CLOCK_IP_RTU1_CORE_DIV2_EXTENSION               26U
#define CLOCK_IP_P0_PSI5_S_UTIL_EXTENSION               27U
#define CLOCK_IP_P4_PSI5_S_UTIL_EXTENSION               28U
#define CLOCK_IP_CLKOUT0_EXTENSION                      29U
#define CLOCK_IP_CLKOUT1_EXTENSION                      30U
#define CLOCK_IP_CLKOUT2_EXTENSION                      31U
#define CLOCK_IP_CLKOUT3_EXTENSION                      32U
#define CLOCK_IP_CLKOUT4_EXTENSION                      33U
#define CLOCK_IP_ETH0_TX_MII_EXTENSION                  34U
#define CLOCK_IP_P3_CAN_PE_EXTENSION                    35U
#define CLOCK_IP_P0_FR_PE_EXTENSION                     36U
#define CLOCK_IP_P0_LIN_BAUD_EXTENSION                  37U
#define CLOCK_IP_P1_LIN_BAUD_EXTENSION                  38U
#define CLOCK_IP_P4_LIN_BAUD_EXTENSION                  39U
#define CLOCK_IP_P5_LIN_BAUD_EXTENSION                  40U
#define CLOCK_IP_P0_CLKOUT_SRC_EXTENSION                41U
#define CLOCK_IP_P0_CTU_PER_EXTENSION                   42U
#define CLOCK_IP_P0_DSPI_MSC_EXTENSION                  43U
#define CLOCK_IP_P0_EMIOS_LCU_EXTENSION                 44U
#define CLOCK_IP_P0_GTM_EXTENSION                       45U
#define CLOCK_IP_P0_GTM_NOC_EXTENSION                   46U
#define CLOCK_IP_P0_GTM_TS_EXTENSION                    47U
#define CLOCK_IP_P0_LIN_EXTENSION                       48U
#define CLOCK_IP_P0_NANO_EXTENSION                      49U
#define CLOCK_IP_P0_PSI5_125K_EXTENSION                 50U
#define CLOCK_IP_P0_PSI5_189K_EXTENSION                 51U
#define CLOCK_IP_P0_PSI5_S_BAUD_EXTENSION               52U
#define CLOCK_IP_P0_PSI5_S_CORE_EXTENSION               53U
#define CLOCK_IP_P0_PSI5_S_TRIG0_EXTENSION              54U
#define CLOCK_IP_P0_PSI5_S_TRIG1_EXTENSION              55U
#define CLOCK_IP_P0_PSI5_S_TRIG2_EXTENSION              56U
#define CLOCK_IP_P0_PSI5_S_TRIG3_EXTENSION              57U
#define CLOCK_IP_P0_PSI5_S_UART_EXTENSION               58U
#define CLOCK_IP_P0_PSI5_S_WDOG0_EXTENSION              59U
#define CLOCK_IP_P0_PSI5_S_WDOG1_EXTENSION              60U
#define CLOCK_IP_P0_PSI5_S_WDOG2_EXTENSION              61U
#define CLOCK_IP_P0_PSI5_S_WDOG3_EXTENSION              62U
#define CLOCK_IP_P0_REG_INTF_2X_EXTENSION               63U
#define CLOCK_IP_P0_REG_INTF_EXTENSION                  64U
#define CLOCK_IP_P1_CLKOUT_SRC_EXTENSION                65U
#define CLOCK_IP_P1_DSPI60_EXTENSION                    66U
#define CLOCK_IP_P1_LFAST0_REF_EXTENSION                67U
#define CLOCK_IP_P1_LFAST1_REF_EXTENSION                68U
#define CLOCK_IP_P1_NETC_AXI_EXTENSION                  69U
#define CLOCK_IP_P1_LIN_EXTENSION                       70U
#define CLOCK_IP_ETH_TS_EXTENSION                       71U
#define CLOCK_IP_ETH_TS_DIV4_EXTENSION                  72U
#define CLOCK_IP_ETH0_REF_RMII_EXTENSION                73U
#define CLOCK_IP_ETH0_RX_MII_EXTENSION                  74U
#define CLOCK_IP_ETH0_RX_RGMII_EXTENSION                75U
#define CLOCK_IP_ETH0_TX_RGMII_EXTENSION                76U
#define CLOCK_IP_ETH0_TX_RGMII_LPBK_EXTENSION           77U
#define CLOCK_IP_ETH1_REF_RMII_EXTENSION                78U
#define CLOCK_IP_ETH1_RX_MII_EXTENSION                  79U
#define CLOCK_IP_ETH1_RX_RGMII_EXTENSION                80U
#define CLOCK_IP_ETH1_TX_MII_EXTENSION                  81U
#define CLOCK_IP_ETH1_TX_RGMII_EXTENSION                82U
#define CLOCK_IP_ETH1_TX_RGMII_LPBK_EXTENSION           83U
#define CLOCK_IP_P1_REG_INTF_EXTENSION                  84U
#define CLOCK_IP_P2_DBG_ATB_EXTENSION                   85U
#define CLOCK_IP_P2_REG_INTF_EXTENSION                  86U
#define CLOCK_IP_P3_AES_EXTENSION                       87U
#define CLOCK_IP_P3_CLKOUT_SRC_EXTENSION                88U
#define CLOCK_IP_P3_DBG_TS_EXTENSION                    89U
#define CLOCK_IP_P3_REG_INTF_EXTENSION                  90U
#define CLOCK_IP_P4_CLKOUT_SRC_EXTENSION                91U
#define CLOCK_IP_P4_DSPI60_EXTENSION                    92U
#define CLOCK_IP_P4_EMIOS_LCU_EXTENSION                 93U
#define CLOCK_IP_P4_LIN_EXTENSION                       94U
#define CLOCK_IP_P4_PSI5_125K_EXTENSION                 95U
#define CLOCK_IP_P4_PSI5_189K_EXTENSION                 96U
#define CLOCK_IP_P4_PSI5_S_BAUD_EXTENSION               97U
#define CLOCK_IP_P4_PSI5_S_CORE_EXTENSION               98U
#define CLOCK_IP_P4_PSI5_S_TRIG0_EXTENSION              99U
#define CLOCK_IP_P4_PSI5_S_TRIG1_EXTENSION              100U
#define CLOCK_IP_P4_PSI5_S_TRIG2_EXTENSION              101U
#define CLOCK_IP_P4_PSI5_S_TRIG3_EXTENSION              102U
#define CLOCK_IP_P4_PSI5_S_UART_EXTENSION               103U
#define CLOCK_IP_P4_PSI5_S_WDOG0_EXTENSION              104U
#define CLOCK_IP_P4_PSI5_S_WDOG1_EXTENSION              105U
#define CLOCK_IP_P4_PSI5_S_WDOG2_EXTENSION              106U
#define CLOCK_IP_P4_PSI5_S_WDOG3_EXTENSION              107U
#define CLOCK_IP_P4_QSPI0_2X_EXTENSION                  108U
#define CLOCK_IP_P4_QSPI0_1X_EXTENSION                  109U
#define CLOCK_IP_P4_QSPI1_2X_EXTENSION                  110U
#define CLOCK_IP_P4_QSPI1_1X_EXTENSION                  111U
#define CLOCK_IP_P4_REG_INTF_2X_EXTENSION               112U
#define CLOCK_IP_P4_REG_INTF_EXTENSION                  113U
#define CLOCK_IP_P4_SDHC_IP_EXTENSION                   114U
#define CLOCK_IP_P4_SDHC_IP_DIV2_EXTENSION              115U
#define CLOCK_IP_P5_AE_EXTENSION                        116U
#define CLOCK_IP_P5_CANXL_PE_EXTENSION                  117U
#define CLOCK_IP_P5_CANXL_CHI_EXTENSION                 118U
#define CLOCK_IP_P5_CLKOUT_SRC_EXTENSION                119U
#define CLOCK_IP_P5_LIN_EXTENSION                       120U
#define CLOCK_IP_P5_REG_INTF_EXTENSION                  121U
#define CLOCK_IP_P6_REG_INTF_EXTENSION                  122U
#define CLOCK_IP_P0_PSI5_1US_EXTENSION                  123U
#define CLOCK_IP_P4_PSI5_1US_EXTENSION                  124U
#define CLOCK_IP_RTU0_REG_INTF_EXTENSION                125U
#define CLOCK_IP_RTU1_REG_INTF_EXTENSION                126U
#define CLOCK_IP_P4_SDHC_EXTENSION                      127U
#define CLOCK_IP_P0_DSPI_EXTENSION                      128U
#define CLOCK_IP_P1_DSPI_EXTENSION                      129U
#define CLOCK_IP_P4_DSPI_EXTENSION                      130U
#define CLOCK_IP_P5_DSPI_EXTENSION                      131U

#define CLOCK_IP_COREPLL_INSTANCE                       0U
#define CLOCK_IP_PERIPHPLL_INSTANCE                     1U
#define CLOCK_IP_DDRPLL_INSTANCE                        2U

#define CLOCK_IP_COREDFS_INSTANCE                       0U
#define CLOCK_IP_PERIPHDFS_INSTANCE                     1U

#define CLOCK_IP_LFAST0_PLL_INSTANCE                   0U
#define CLOCK_IP_LFAST1_PLL_INSTANCE                   1U

#define CLOCK_IP_CGM0_INSTANCE                          0U
#define CLOCK_IP_CGM1_INSTANCE                          1U
#define CLOCK_IP_CGM2_INSTANCE                          2U
#define CLOCK_IP_CGM3_INSTANCE                          3U
#define CLOCK_IP_CGM4_INSTANCE                          4U
#define CLOCK_IP_CGM5_INSTANCE                          5U
#define CLOCK_IP_CGM6_INSTANCE                          6U
#define CLOCK_IP_CGM7_INSTANCE                          7U
#define CLOCK_IP_CGM8_INSTANCE                          8U
#define CLOCK_IP_CGM_AE_INSTANCE                        9U

#define CLOCK_IP_GPR0_INSTANCE                          0U
#define CLOCK_IP_GPR1_INSTANCE                          1U
#define CLOCK_IP_GPR3_INSTANCE                          3U
#define CLOCK_IP_GPR4_INSTANCE                          4U
#define CLOCK_IP_GPR5_INSTANCE                          5U

#define CLOCK_IP_SMU_CMU_FC_INSTANCE                    0U
#define CLOCK_IP_CMU_FC_0_INSTANCE                      1U
#define CLOCK_IP_CMU_FC_1_INSTANCE                      2U
#define CLOCK_IP_CMU_FC_2A_INSTANCE                     3U
#define CLOCK_IP_CMU_FC_2B_INSTANCE                     4U
#define CLOCK_IP_CMU_FC_2C_INSTANCE                     5U
#define CLOCK_IP_CMU_FC_3_INSTANCE                      6U
#define CLOCK_IP_CMU_FC_4_INSTANCE                      7U
#define CLOCK_IP_CMU_FC_5_INSTANCE                      8U
#define CLOCK_IP_CMU_FC_6_INSTANCE                      9U
#define CLOCK_IP_CE_CMU_FC_0_INSTANCE                   10U
#define CLOCK_IP_CE_CMU_FC_1_INSTANCE                   11U
#define CLOCK_IP_CE_CMU_FC_2_INSTANCE                   12U
#define CLOCK_IP_RTU0_CMU_FC_0_INSTANCE                 13U
#define CLOCK_IP_RTU0_CMU_FC_1_INSTANCE                 14U
#define CLOCK_IP_RTU0_CMU_FC_2_INSTANCE                 15U
#define CLOCK_IP_RTU0_CMU_FC_3_INSTANCE                 16U
#define CLOCK_IP_RTU0_CMU_FC_4_INSTANCE                 17U
#define CLOCK_IP_RTU1_CMU_FC_0_INSTANCE                 18U
#define CLOCK_IP_RTU1_CMU_FC_1_INSTANCE                 19U
#define CLOCK_IP_RTU1_CMU_FC_2_INSTANCE                 20U
#define CLOCK_IP_RTU1_CMU_FC_3_INSTANCE                 21U
#define CLOCK_IP_RTU1_CMU_FC_4_INSTANCE                 22U
#define CLOCK_IP_CMU_FC_DEBUG_1_INSTANCE                23U
#define CLOCK_IP_CMU_FC_DEBUG_2_INSTANCE                24U
#define CLOCK_IP_CMU_FC_AE_1_INSTANCE                   25U
#define CLOCK_IP_CMU_FC_AE_2_INSTANCE                   26U
#define CLOCK_IP_CMU_FC_AE_3_INSTANCE                   27U

#define CLOCK_IP_P6_GROUP_0_BIT0_INDEX                       0U
#define CLOCK_IP_P0_GROUP_13_BIT0_INDEX                      1U
#define CLOCK_IP_P0_GROUP_12_BIT0_INDEX                      2U
#define CLOCK_IP_P3_GROUP_1_BIT0_INDEX                       3U
#define CLOCK_IP_P3_GROUP_27_BIT0_INDEX                      4U
#define CLOCK_IP_P3_GROUP_28_BIT0_INDEX                      5U
#define CLOCK_IP_P3_GROUP_29_BIT0_INDEX                      6U
#define CLOCK_IP_P3_GROUP_30_BIT0_INDEX                      7U
#define CLOCK_IP_P3_GROUP_31_BIT0_INDEX                      8U
#define CLOCK_IP_P3_GROUP_32_BIT0_INDEX                      9U
#define CLOCK_IP_P0_GROUP_20_BIT0_INDEX                      10U
#define CLOCK_IP_P0_GROUP_5_BIT1_INDEX                       11U
#define CLOCK_IP_P1_GROUP_1_BIT1_INDEX                       12U
#define CLOCK_IP_P4_GROUP_2_BIT1_INDEX                       13U
#define CLOCK_IP_P5_GROUP_0_BIT1_INDEX                       14U
#define CLOCK_IP_P0_GROUP_5_BIT2_INDEX                       15U
#define CLOCK_IP_P1_GROUP_1_BIT2_INDEX                       16U
#define CLOCK_IP_P4_GROUP_2_BIT2_INDEX                       17U
#define CLOCK_IP_P5_GROUP_0_BIT2_INDEX                       18U
#define CLOCK_IP_P0_GROUP_5_BIT0_INDEX                       19U
#define CLOCK_IP_P1_GROUP_1_BIT0_INDEX                       20U
#define CLOCK_IP_P3_GROUP_0_BIT0_INDEX                       21U
#define CLOCK_IP_P4_GROUP_2_BIT0_INDEX                       22U
#define CLOCK_IP_P5_GROUP_0_BIT0_INDEX                       23U
#define CLOCK_IP_P1_GROUP_12_BIT0_INDEX                      24U
#define CLOCK_IP_P3_GROUP_3_BIT0_INDEX                       25U
#define CLOCK_IP_P3_GROUP_4_BIT0_INDEX                       26U
#define CLOCK_IP_P3_GROUP_5_BIT0_INDEX                       27U
#define CLOCK_IP_P3_GROUP_6_BIT0_INDEX                       28U
#define CLOCK_IP_P3_GROUP_7_BIT0_INDEX                       29U
#define CLOCK_IP_P3_GROUP_8_BIT0_INDEX                       30U
#define CLOCK_IP_P3_GROUP_9_BIT0_INDEX                       31U
#define CLOCK_IP_P3_GROUP_10_BIT0_INDEX                      32U
#define CLOCK_IP_P3_GROUP_11_BIT0_INDEX                      33U
#define CLOCK_IP_P3_GROUP_12_BIT0_INDEX                      34U
#define CLOCK_IP_P3_GROUP_13_BIT0_INDEX                      35U
#define CLOCK_IP_P3_GROUP_14_BIT0_INDEX                      36U
#define CLOCK_IP_P3_GROUP_15_BIT0_INDEX                      37U
#define CLOCK_IP_P3_GROUP_16_BIT0_INDEX                      38U
#define CLOCK_IP_P3_GROUP_17_BIT0_INDEX                      39U
#define CLOCK_IP_P3_GROUP_18_BIT0_INDEX                      40U
#define CLOCK_IP_P3_GROUP_19_BIT0_INDEX                      41U
#define CLOCK_IP_P3_GROUP_20_BIT0_INDEX                      42U
#define CLOCK_IP_P3_GROUP_21_BIT0_INDEX                      43U
#define CLOCK_IP_P3_GROUP_22_BIT0_INDEX                      44U
#define CLOCK_IP_P3_GROUP_23_BIT0_INDEX                      45U
#define CLOCK_IP_P3_GROUP_24_BIT0_INDEX                      46U
#define CLOCK_IP_P3_GROUP_25_BIT0_INDEX                      47U
#define CLOCK_IP_P3_GROUP_26_BIT0_INDEX                      48U
#define CLOCK_IP_P0_GROUP_2_BIT0_INDEX                       49U
#define CLOCK_IP_P0_GROUP_3_BIT0_INDEX                       50U
#define CLOCK_IP_P0_GROUP_22_BIT0_INDEX                      51U
#define CLOCK_IP_P0_GROUP_4_BIT0_INDEX                       52U
#define CLOCK_IP_P1_GROUP_0_BIT0_INDEX                       53U
#define CLOCK_IP_P4_GROUP_11_BIT0_INDEX                      54U
#define CLOCK_IP_P0_GROUP_8_BIT0_INDEX                       55U
#define CLOCK_IP_P0_GROUP_9_BIT0_INDEX                       56U
#define CLOCK_IP_P0_GROUP_10_BIT0_INDEX                      57U
#define CLOCK_IP_P1_GROUP_5_BIT0_INDEX                       58U
#define CLOCK_IP_P1_GROUP_6_BIT0_INDEX                       59U
#define CLOCK_IP_P1_GROUP_7_BIT0_INDEX                       60U
#define CLOCK_IP_P4_GROUP_6_BIT0_INDEX                       61U
#define CLOCK_IP_P4_GROUP_7_BIT0_INDEX                       62U
#define CLOCK_IP_P4_GROUP_8_BIT0_INDEX                       63U
#define CLOCK_IP_P5_GROUP_3_BIT0_INDEX                       64U
#define CLOCK_IP_P5_GROUP_4_BIT0_INDEX                       65U
#define CLOCK_IP_P5_GROUP_5_BIT0_INDEX                       66U
#define CLOCK_IP_P0_GROUP_6_BIT0_INDEX                       67U
#define CLOCK_IP_P0_GROUP_11_BIT0_INDEX                      68U
#define CLOCK_IP_P0_GROUP_22_BIT1_INDEX                      69U
#define CLOCK_IP_P0_GROUP_5_BIT3_INDEX                       70U
#define CLOCK_IP_P1_GROUP_1_BIT3_INDEX                       71U
#define CLOCK_IP_P4_GROUP_2_BIT3_INDEX                       72U
#define CLOCK_IP_P5_GROUP_0_BIT3_INDEX                       73U
#define CLOCK_IP_P0_GROUP_19_BIT0_INDEX                      74U
#define CLOCK_IP_P4_GROUP_12_BIT0_INDEX                      75U
#define CLOCK_IP_P0_GROUP_23_BIT0_INDEX                      76U
#define CLOCK_IP_P4_GROUP_14_BIT0_INDEX                      77U
#define CLOCK_IP_P4_GROUP_0_BIT0_INDEX                       78U
#define CLOCK_IP_P4_GROUP_1_BIT0_INDEX                       79U
#define CLOCK_IP_P3_GROUP_33_BIT0_INDEX                      80U
#define CLOCK_IP_P4_GROUP_9_BIT0_INDEX                       81U
#define CLOCK_IP_P0_GROUP_24_BIT0_INDEX                      82U
#define CLOCK_IP_P1_GROUP_8_BIT0_INDEX                       83U
#define CLOCK_IP_P1_GROUP_9_BIT0_INDEX                       84U
#define CLOCK_IP_P0_GROUP_21_BIT0_INDEX                      85U
#define CLOCK_IP_P1_GROUP_14_BIT0_INDEX                      86U
#define CLOCK_IP_P4_GROUP_13_BIT0_INDEX                      87U
#define CLOCK_IP_P5_GROUP_6_BIT0_INDEX                       88U
#define CLOCK_IP_P0_GROUP_1_BIT0_INDEX                       89U
#define CLOCK_IP_P0_GROUP_7_BIT0_INDEX                       90U
#define CLOCK_IP_P1_GROUP_2_BIT0_INDEX                       91U
#define CLOCK_IP_P1_GROUP_3_BIT0_INDEX                       92U
#define CLOCK_IP_P1_GROUP_4_BIT0_INDEX                       93U
#define CLOCK_IP_P4_GROUP_3_BIT0_INDEX                       94U
#define CLOCK_IP_P4_GROUP_4_BIT0_INDEX                       95U
#define CLOCK_IP_P4_GROUP_5_BIT0_INDEX                       96U
#define CLOCK_IP_P5_GROUP_1_BIT0_INDEX                       97U
#define CLOCK_IP_P5_GROUP_2_BIT0_INDEX                       98U
#define CLOCK_IP_P1_GROUP_10_BIT0_INDEX                      99U
#define CLOCK_IP_P4_GROUP_10_BIT0_INDEX                      100U

#define CLOCK_IP_GATE_0_INDEX                           0U
#define CLOCK_IP_GATE_1_INDEX                           1U
#define CLOCK_IP_GATE_2_INDEX                           2U
#define CLOCK_IP_GATE_3_INDEX                           3U
#define CLOCK_IP_GATE_4_INDEX                           4U
#define CLOCK_IP_GATE_5_INDEX                           5U
#define CLOCK_IP_GATE_6_INDEX                           6U
#define CLOCK_IP_GATE_7_INDEX                           7U
#define CLOCK_IP_GATE_8_INDEX                           8U
#define CLOCK_IP_GATE_9_INDEX                           9U
#define CLOCK_IP_GATE_10_INDEX                          10U
#define CLOCK_IP_GATE_11_INDEX                          11U
#define CLOCK_IP_GATE_12_INDEX                          12U
#define CLOCK_IP_GATE_13_INDEX                          13U
#define CLOCK_IP_GATE_14_INDEX                          14U
#define CLOCK_IP_GATE_15_INDEX                          15U
#define CLOCK_IP_GATE_16_INDEX                          16U
#define CLOCK_IP_GATE_17_INDEX                          17U
#define CLOCK_IP_GATE_18_INDEX                          18U
#define CLOCK_IP_GATE_19_INDEX                          19U
#define CLOCK_IP_GATE_20_INDEX                          20U
#define CLOCK_IP_GATE_21_INDEX                          21U
#define CLOCK_IP_GATE_22_INDEX                          22U
#define CLOCK_IP_GATE_23_INDEX                          23U
#define CLOCK_IP_GATE_24_INDEX                          24U
#define CLOCK_IP_GATE_25_INDEX                          25U
#define CLOCK_IP_GATE_26_INDEX                          26U
#define CLOCK_IP_GATE_27_INDEX                          27U
#define CLOCK_IP_GATE_28_INDEX                          28U
#define CLOCK_IP_GATE_29_INDEX                          29U
#define CLOCK_IP_GATE_30_INDEX                          30U
#define CLOCK_IP_GATE_31_INDEX                          31U
#define CLOCK_IP_GATE_32_INDEX                          32U
#define CLOCK_IP_GATE_33_INDEX                          33U

#define CLOCK_IP_GROUP_0_INDEX                          0U
#define CLOCK_IP_GROUP_1_INDEX                          1U
#define CLOCK_IP_GROUP_3_INDEX                          3U
#define CLOCK_IP_GROUP_4_INDEX                          4U
#define CLOCK_IP_GROUP_5_INDEX                          5U
#define CLOCK_IP_GROUP_6_INDEX                          6U

#define CLOCK_IP_DIV_0_INDEX         0U
#define CLOCK_IP_DIV_1_INDEX         1U
#define CLOCK_IP_DIV_2_INDEX         2U
#define CLOCK_IP_DIV_3_INDEX         3U
#define CLOCK_IP_DIV_4_INDEX         4U
#define CLOCK_IP_DIV_5_INDEX         5U
#define CLOCK_IP_DIV_6_INDEX         6U
#define CLOCK_IP_DIV_7_INDEX         7U

#define CLOCK_IP_GATE_PCTL_0         0U
#define CLOCK_IP_GATE_PCTL_1         1U
#define CLOCK_IP_GATE_PCTL_2         2U
#define CLOCK_IP_GATE_PCTL_3         3U


#define CLOCK_IP_SEL_0_INDEX         0U
#define CLOCK_IP_SEL_1_INDEX         1U
#define CLOCK_IP_SEL_2_INDEX         2U
#define CLOCK_IP_SEL_3_INDEX         3U
#define CLOCK_IP_SEL_4_INDEX         4U
#define CLOCK_IP_SEL_5_INDEX         5U
#define CLOCK_IP_SEL_6_INDEX         6U
#define CLOCK_IP_SEL_7_INDEX         7U
#define CLOCK_IP_SEL_8_INDEX         8U
#define CLOCK_IP_SEL_9_INDEX         9U
#define CLOCK_IP_SEL_10_INDEX        10
#define CLOCK_IP_SEL_11_INDEX        11
#define CLOCK_IP_SEL_12_INDEX        12
#define CLOCK_IP_SEL_13_INDEX        13
#define CLOCK_IP_SEL_14_INDEX        14

#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
#define CLOCK_IP_PCFS_1_INDEX        1U
#endif
#define CLOCK_IP_PCFS_2_INDEX        2U
#define CLOCK_IP_PCFS_9_INDEX        9U
#define CLOCK_IP_PCFS_10_INDEX       10U
#define CLOCK_IP_PCFS_11_INDEX       11U
#define CLOCK_IP_PCFS_14_INDEX       14U
#define CLOCK_IP_PCFS_39_INDEX       39U

#if defined(IP_RTU0__MC_CGM)
    #define CLOCK_IP_RTU0__MC_CGM IP_RTU0__MC_CGM
#endif
#if defined(IP_RTU1__MC_CGM)
    #define CLOCK_IP_RTU1__MC_CGM IP_RTU1__MC_CGM
#endif

#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
    #define CLOCK_IP_SAFE_POWER_MODE  0U
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    #define CLOCK_IP_DRUN_POWER_MODE  1U
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
    #define CLOCK_IP_RUN0_POWER_MODE  2U
#endif

#define CLOCK_IP_COREPLL_DIVIDER_COUNT                      1U
#define CLOCK_IP_PERIPHPLL_DIVIDER_COUNT                    7U
#define CLOCK_IP_DDRPLL_DIVIDER_COUNT                       1U
/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_8
#include "Mcu_MemMap.h"

const uint8 Clock_Ip_au8DividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV_CMU */
    CLOCK_IP_PLLDIG_PLL0DIV_DE_DIV_OUTPUT,                      /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_PLLDIG_PLL0DIV_DE_DIV_OUTPUT,                      /* CLOCK_IP_PLL_OUT */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WITH_TRIGGER,      /* CLOCK_IP_HWMUX_DIV_TRIGGER */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /*CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_FMT_STAT_WITHOUT_PHASE,               /* CLOCK_IP_HWMUX_MUL_DIV */
#if defined(CLOCK_IP_MC_ME_AE_GS_S_SYSCLK)
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV_PCFS */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};
const uint8 Clock_Ip_au8DividerTriggerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_HWMUX_DIV_TRIGGER */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8XoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL,                       /* CLOCK_IP_FAST_XOSC_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8GateCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CONTROL_ENABLE_GPR_PCTL,                     /* CLOCK_IP_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CONTROL_ENABLE_GPR_PCTL,                     /* CLOCK_IP_HWMUX_CMU_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8FractionalDividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_DFS_MFI_MFN,                                       /* CLOCK_IP_PCFS_DFS */
    CLOCK_IP_DFS_MFI_MFN,                                       /* CLOCK_IP_DFS */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8PllCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE,/* CLOCK_IP_PLL_MOD */
    CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN,                         /* CLOCK_IP_PLL */
    CLOCK_IP_LFASTPLL_ENABLE,                                   /* CLOCK_IP_LFASTPLL */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8SelectorCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV_CMU */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_CMU */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_CMU_GATE */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV */
#if defined(CLOCK_IP_MC_ME_AE_GS_S_SYSCLK)
    CLOCK_IP_MC_ME_AE_GS_S_SYSCLK,                              /* CLOCK_IP_HWMUX_AE */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV_TRIGGER */
    CLOCK_IP_CGM_X_CSC_CSS_CS_GRIP,                             /* CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_GPR_X_CLKOUT_SEL_MUXSEL,                           /* CLOCK_IP_CLKOUT */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_MUL_DIV */
#if defined(CLOCK_IP_MC_ME_AE_GS_S_SYSCLK)
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV_PCFS */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};
const uint8 Clock_Ip_au8PcfsCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* CLOCK_IP_PCFS_DFS */
    CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#if defined(CLOCK_IP_MC_ME_AE_GS_S_SYSCLK)
    CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* CLOCK_IP_HWMUX_DIV_PCFS */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
};
const uint8 Clock_Ip_au8CmuCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_HWMUX_DIV_CMU */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_HWMUX_CMU */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_HWMUX_CMU_GATE */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_CMU */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_FAST_XOSC_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_CLKOUT_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};




/* Clock features mapping */
const uint8 Clock_Ip_au8ClockFeatures[CLOCK_IP_NAMES_NO][CLOCK_IP_FEATURES_NO] =
/*   \
***************************************************************************************************************************************************************************************************************************************************************************************************************************************  \
************************************     ******************************       ********************************   E   ********************************       *************       **********************       ***********************       ****************************       **********************       ****************************  \
************************************  I  ******************************   C   ********************************   X   ********************************       *************   S   **********************   D   ***********************       ****************************       **********************       ****************************  \
************************************  N  ******************************   A   ********************************   T   ********************************   P   *************   E   **********************   I   ***********************   G   ****************************   P   **********************       ****************************  \
************************************  S  ******************************   L   ********************************   E   ********************************   O   *************   L   **********************   V   ***********************   A   ****************************   C   **********************   C   ****************************  \
************************************  T  ******************************   L   ********************************   N   ********************************   W   *************   E   **********************   I   ***********************   T   ****************************   F   **********************   M   ****************************  \
************************************  A  ******************************   B   ********************************   S   ********************************   E   *************   C   **********************   D   ***********************   E   ****************************   S   **********************   U   ****************************  \
************************************  N  ******************************   A   ********************************   I   ********************************   R   *************   T   **********************   E   ***********************       ****************************       **********************       ****************************  \
************************************  C  ******************************   C   ********************************   O   ********************************       *************   O   **********************   R   ***********************       ****************************       **********************       ****************************  \
************************************  E  ******************************   K   ********************************   N   ********************************       *************   R   **********************       ***********************       ****************************       **********************       ****************************  \
************************************     ******************************       ********************************       *******************************        *************       **********************       ***********************       ****************************       **********************       ****************************  \
***************************************************************************************************************************************************************************************************************************************************************************************************************************************/
{
/*   CLOCK_IS_OFF clock         */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   CLOCK_IS_OFF               */
/*   FIRC_CLK clock             */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_2A_INSTANCE},       /*   FIRC_CLK clock             */
/*   FXOSC_CLK clock            */ {0U,                               CLOCK_IP_FAST_XOSC_CMU,                0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_2B_INSTANCE},       /*   FXOSC_CLK clock            */
/*   SIRC_CLK clock             */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   SIRC_CLK clock             */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
/*   FIRC_AE_CLK clock          */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               CLOCK_IP_PCFS_1_INDEX,       CLOCK_IP_CMU_FC_2A_INSTANCE},       /*   FIRC_AE_CLK clock          */
#endif
/*   COREPLL_CLK clock          */ {CLOCK_IP_COREPLL_INSTANCE,        CLOCK_IP_PLL_MOD,                      0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   COREPLL_CLK clock          */
/*   PERIPHPLL_CLK clock        */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   PERIPHPLL_CLK clock        */
/*   DDRPLL_CLK clock           */ {CLOCK_IP_DDRPLL_INSTANCE,         CLOCK_IP_PLL_MOD,                      0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   DDRPLL_CLK clock           */
/*   LFAST0_PLL_CLK clock       */ {CLOCK_IP_LFAST0_PLL_INSTANCE,     CLOCK_IP_LFASTPLL,                     0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   LFAST0_PLL_CLK clock       */
/*   LFAST1_PLL_CLK clock       */ {CLOCK_IP_LFAST1_PLL_INSTANCE,     CLOCK_IP_LFASTPLL,                     0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   LFAST1_PLL_CLK clock       */
/*   COREPLL_PHI0 clock         */ {CLOCK_IP_COREPLL_INSTANCE,        CLOCK_IP_PCFS_PLL_OUT,                 0U,                                      0U,                 0U,                          CLOCK_IP_DIV_0_INDEX,        0U,                               CLOCK_IP_PCFS_9_INDEX,       0U},                                /*   COREPLL_PHI0 clock         */
/*   COREPLL_DFS0 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_PCFS_DFS,                     0U,                                      0U,                 0U,                          CLOCK_IP_DIV_0_INDEX,        0U,                               CLOCK_IP_PCFS_10_INDEX,      0U},                                /*   COREPLL_DFS0 clock         */
/*   COREPLL_DFS1 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_PCFS_DFS,                     0U,                                      0U,                 0U,                          CLOCK_IP_DIV_1_INDEX,        0U,                               CLOCK_IP_PCFS_11_INDEX,      0U},                                /*   COREPLL_DFS1 clock         */
/*   COREPLL_DFS2 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   COREPLL_DFS2 clock         */
/*   COREPLL_DFS3 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   COREPLL_DFS3 clock         */
/*   COREPLL_DFS4 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_PCFS_DFS,                     0U,                                      0U,                 0U,                          CLOCK_IP_DIV_4_INDEX,        0U,                               CLOCK_IP_PCFS_14_INDEX,      0U},                                /*   COREPLL_DFS4 clock         */
/*   COREPLL_DFS5 clock         */ {CLOCK_IP_COREDFS_INSTANCE,        CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   COREPLL_DFS5 clock         */
/*   PERIPHPLL_PHI0 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI0 clock       */
/*   PERIPHPLL_PHI1 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI1 clock       */
/*   PERIPHPLL_PHI2 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI2 clock       */
/*   PERIPHPLL_PHI3 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI3 clock       */
/*   PERIPHPLL_PHI4 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI4 clock       */
/*   PERIPHPLL_PHI5 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI5 clock       */
/*   PERIPHPLL_PHI6 clock       */ {CLOCK_IP_PERIPHPLL_INSTANCE,      CLOCK_IP_PLL_OUT,                      0U,                                      0U,                 0U,                          CLOCK_IP_DIV_6_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_PHI6 clock       */
/*   PERIPHPLL_DFS0 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS0 clock       */
/*   PERIPHPLL_DFS1 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS1 clock       */
/*   PERIPHPLL_DFS2 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS2 clock       */
/*   PERIPHPLL_DFS3 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS3 clock       */
/*   PERIPHPLL_DFS4 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS4 clock       */
/*   PERIPHPLL_DFS5 clock       */ {CLOCK_IP_PERIPHDFS_INSTANCE,      CLOCK_IP_DFS,                          0U,                                      0U,                 0U,                          CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   PERIPHPLL_DFS5 clock       */
/*   DDRPLL_PHI0 clock          */ {CLOCK_IP_DDRPLL_INSTANCE,         CLOCK_IP_PCFS_PLL_OUT,                 0U,                                      0U,                 0U,                          CLOCK_IP_DIV_0_INDEX,        0U,                               CLOCK_IP_PCFS_39_INDEX,      0U},                                /*   DDRPLL_PHI0 clock          */
/*   LFAST0_PLL_PH0_CLK clock   */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   LFAST0_PLL_PH0_CLK clock   */
/*   LFAST0_PLL_PH0_CLK clock   */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   LFAST0_PLL_PH0_CLK clock   */
/*   eth_rgmii_ref clock        */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   eth_rgmii_ref clock        */
/*   tmr_1588_ref clock         */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   tmr_1588_ref clock           */
/*   eth0_ext_rx clock          */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   eth0_ext_rx clock          */
/*   eth0_ext_tx clock          */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   eth0_ext_tx clock          */
/*   eth1_ext_rx clock          */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   eth1_ext_rx clock          */
/*   eth1_ext_tx clock          */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   eth1_ext_tx clock          */
/*   lfast0_ext_ref clock       */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   lfast0_ext_ref clock       */
/*   lfast1_ext_ref clock       */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   lfast1_ext_ref clock       */
/*   DDR_CLK clock              */ {CLOCK_IP_CGM6_INSTANCE,           CLOCK_IP_HWMUX_DIV_CMU,                CLOCK_IP_DDR_EXTENSION,                  0U,                 CLOCK_IP_SEL_0_INDEX,        CLOCK_IP_DIV_0_INDEX,        CLOCK_IP_P6_GROUP_0_BIT0_INDEX,   0U,                          CLOCK_IP_CMU_FC_6_INSTANCE},        /*   DDR_CLK clock              */
/*   P0_SYS_CLK clock           */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P0_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_SYS_CLK clock           */
/*   P1_SYS_CLK clock           */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P1_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_SYS_CLK clock           */
/*   P1_SYS_DIV2_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P1_SYS_DIV2_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_SYS_DIV2_CLK clock      */
/*   P1_SYS_DIV4_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P1_SYS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_SYS_DIV4_CLK clock      */
/*   P2_SYS_CLK clock           */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_HWMUX_CMU,                    CLOCK_IP_P2_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          CLOCK_IP_SMU_CMU_FC_INSTANCE},      /*   P2_SYS_CLK clock           */
/*   CORE_M33_CLK clock         */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_CORE_M33_EXTENSION,             0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   CORE_M33_CLK clock         */
/*   P2_SYS_DIV2_CLK clock      */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P2_SYS_DIV2_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P2_SYS_DIV2_CLK clock      */
/*   P2_SYS_DIV4_CLK clock      */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P2_SYS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P2_SYS_DIV4_CLK clock      */
/*   P3_SYS_CLK clock           */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P3_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P3_SYS_CLK clock           */
/*   CE_SYS_DIV2_CLK clock      */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_CMU,                          CLOCK_IP_CE_SYS_DIV2_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          CLOCK_IP_CE_CMU_FC_2_INSTANCE},     /*   CE_SYS_DIV2_CLK clock      */
/*   CE_SYS_DIV4_CLK clock      */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_CE_SYS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   CE_SYS_DIV4_CLK clock      */
/*   P3_SYS_DIV2_NOC_CLK clock  */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P3_SYS_DIV2_NOC_EXTENSION,      0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P3_SYS_DIV2_NOC_CLK clock  */
/*   P3_SYS_DIV4_CLK clock      */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P3_SYS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P3_SYS_DIV4_CLK clock      */
/*   P4_SYS_CLK clock           */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_SYS_CLK clock           */
/*   P4_SYS_DIV2_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P4_SYS_DIV2_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_SYS_DIV2_CLK clock      */
/*   HSE_SYS_DIV2_CLK clock     */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_HSE_SYS_DIV2_EXTENSION,         0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   HSE_SYS_DIV2_CLK clock     */
/*   P5_SYS_CLK clock           */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P5_SYS_EXTENSION,               0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_SYS_CLK clock           */
/*   P5_SYS_DIV2_CLK clock      */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P5_SYS_DIV2_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_SYS_DIV2_CLK clock      */
/*   P5_SYS_DIV4_CLK clock      */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P5_SYS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_SYS_DIV4_CLK clock      */
/*   P2_MATH_CLK clock          */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_HWMUX_CMU,                    CLOCK_IP_P2_MATH_EXTENSION,              0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_2C_INSTANCE},       /*   P2_MATH_CLK clock          */
/*   P2_MATH_DIV3_CLK clock     */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_P2_MATH_DIV3_EXTENSION,         0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P2_MATH_DIV3_CLK clock     */
/*   GLB_LBIST_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_GLB_LBIST_EXTENSION,            0U,                 CLOCK_IP_SEL_8_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   GLB_LBIST_CLK clock        */
/*   RTU0_CORE_CLK clock        */ {CLOCK_IP_CGM7_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_RTU0_CORE_EXTENSION,            0U,                 CLOCK_IP_SEL_0_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   RTU0_CORE_CLK clock        */
/*   RTU0_CORE_DIV2_CLK clock   */ {CLOCK_IP_CGM7_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_RTU0_CORE_DIV2_EXTENSION,       0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   RTU0_CORE_DIV2_CLK clock   */
/*   RTU1_CORE_CLK clock        */ {CLOCK_IP_CGM8_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_RTU1_CORE_EXTENSION,            0U,                 CLOCK_IP_SEL_0_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   RTU1_CORE_CLK clock        */
/*   RTU1_CORE_DIV2_CLK clock   */ {CLOCK_IP_CGM8_INSTANCE,           CLOCK_IP_NO_CALLBACK,                  CLOCK_IP_RTU1_CORE_DIV2_EXTENSION,       0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   RTU1_CORE_DIV2_CLK clock   */
/*   P0_PSI5_S_UTIL_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_UTIL_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_UTIL_CLK clock   */
/*   P4_PSI5_S_UTIL_CLK clock   */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_UTIL_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_UTIL_CLK clock   */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
/*   SYSTEM_DRUN_CLK clock      */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_HWMUX_AE,                     0U,                                      CLOCK_IP_DRUN_POWER_MODE,0U,                     0U,                          0U,                               0U,                          0U},                                /*   SYSTEM_DRUN_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
/*   SYSTEM_RUN0_CLK clock      */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_HWMUX_AE,                     0U,                                      CLOCK_IP_RUN0_POWER_MODE,0U,                     0U,                          0U,                               0U,                          0U},                                /*   SYSTEM_RUN0_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
/*   SYSTEM_SAFE_CLK clock      */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_HWMUX_AE,                     0U,                                      CLOCK_IP_SAFE_POWER_MODE,0U,                     0U,                          0U,                               0U,                          0U},                                /*   SYSTEM_SAFE_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
/*   SYSTEM_CLK clock           */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   SYSTEM_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
/*   SYSTEM_DIV2_CLK clock      */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_AE_1_INSTANCE},     /*   SYSTEM_DIV2_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
/*   SYSTEM_DIV4_MON1_CLK clock */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_AE_2_INSTANCE},     /*   SYSTEM_DIV4_MON1_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
/*   SYSTEM_DIV4_MON2_CLK clock */ {CLOCK_IP_CGM_AE_INSTANCE,         CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_AE_3_INSTANCE},     /*   SYSTEM_DIV4_MON2_CLK clock      */
#endif
/*   THE_LAST_PRODUCER_CLK      */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          0U},                                /*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_13_BIT0_INDEX,       0U,                          0U},                                /*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_12_BIT0_INDEX,       0U,                          0U},                                /*   ADC1_CLK clock             */
/*   CE_EDMA_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_1_BIT0_INDEX,        0U,                          0U},                                /*   CE_EDMA_CLK clock          */
/*   CE_PIT0_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_27_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT0_CLK clock          */
/*   CE_PIT1_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_28_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT1_CLK clock          */
/*   CE_PIT2_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_29_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT2_CLK clock          */
/*   CE_PIT3_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_30_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT3_CLK clock          */
/*   CE_PIT4_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_31_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT4_CLK clock          */
/*   CE_PIT5_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_32_BIT0_INDEX,       0U,                          0U},                                /*   CE_PIT5_CLK clock          */
/*   CLKOUT0_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_SWMUX_DIV,                    CLOCK_IP_CLKOUT0_EXTENSION,              0U,                 CLOCK_IP_SEL_10_INDEX,       CLOCK_IP_DIV_0_INDEX,        0U,                                    0U,                          0U},                                /*   CLKOUT0_CLK clock          */
/*   CLKOUT1_CLK clock          */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_SWMUX_DIV,                    CLOCK_IP_CLKOUT1_EXTENSION,              0U,                 CLOCK_IP_SEL_10_INDEX,       CLOCK_IP_DIV_0_INDEX,        0U,                                    0U,                          0U},                                /*   CLKOUT1_CLK clock          */
/*   CLKOUT2_CLK clock          */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_SWMUX_DIV,                    CLOCK_IP_CLKOUT2_EXTENSION,              0U,                 CLOCK_IP_SEL_6_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                                    0U,                          0U},                                /*   CLKOUT2_CLK clock          */
/*   CLKOUT3_CLK clock          */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_SWMUX_DIV,                    CLOCK_IP_CLKOUT3_EXTENSION,              0U,                 CLOCK_IP_SEL_4_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                                    0U,                          0U},                                /*   CLKOUT3_CLK clock          */
/*   CLKOUT4_CLK clock          */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_SWMUX_DIV,                    CLOCK_IP_CLKOUT4_EXTENSION,              0U,                 CLOCK_IP_SEL_4_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                                    0U,                          0U},                                /*   CLKOUT4_CLK clock          */
/*   CTU_CLK clock              */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_20_BIT0_INDEX,       0U,                          0U},                                /*   CTU_CLK clock              */
/*   DMACRC0_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_5_BIT1_INDEX,        0U,                          0U},                                /*   DMACRC0_CLK clock          */
/*   DMACRC1_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_1_BIT1_INDEX,        0U,                          0U},                                /*   DMACRC1_CLK clock          */
/*   DMACRC4_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_2_BIT1_INDEX,        0U,                          0U},                                /*   DMACRC4_CLK clock          */
/*   DMACRC5_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_0_BIT1_INDEX,        0U,                          0U},                                /*   DMACRC5_CLK clock          */
/*   DMAMUX0_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_5_BIT2_INDEX,        0U,                          0U},                                /*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_1_BIT2_INDEX,        0U,                          0U},                                /*   DMAMUX1_CLK clock          */
/*   DMAMUX4_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_2_BIT2_INDEX,        0U,                          0U},                                /*   DMAMUX4_CLK clock          */
/*   DMAMUX5_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_0_BIT2_INDEX,        0U,                          0U},                                /*   DMAMUX5_CLK clock          */
/*   EDMA0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_5_BIT0_INDEX,        0U,                          0U},                                /*   EDMA0_CLK clock            */
/*   EDMA1_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_1_BIT0_INDEX,        0U,                          0U},                                /*   EDMA1_CLK clock            */
/*   EDMA3_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_0_BIT0_INDEX,        0U,                          0U},                                /*   EDMA3_CLK clock            */
/*   EDMA4_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_2_BIT0_INDEX,        0U,                          0U},                                /*   EDMA4_CLK clock            */
/*   EDMA5_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_0_BIT0_INDEX,        0U,                          0U},                                /*   EDMA5_CLK clock            */
/*   ETH0_TX_MII_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_TX_MII_EXTENSION,          0U,                 CLOCK_IP_SEL_6_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_TX_MII_CLK clock      */
/*   ENET0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_12_BIT0_INDEX,       0U,                          0U},                                /*   ENET0_CLK clock            */
/*   P3_CAN_PE_CLK clock        */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P3_CAN_PE_EXTENSION,            0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P3_CAN_PE_CLK clock        */
/*   FLEXCAN0_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_3_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_4_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_5_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN2_CLK clock         */
/*   FLEXCAN3_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_6_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN3_CLK clock         */
/*   FLEXCAN4_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_7_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN4_CLK clock         */
/*   FLEXCAN5_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_8_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN5_CLK clock         */
/*   FLEXCAN6_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_9_BIT0_INDEX,        0U,                          0U},                                /*   FLEXCAN6_CLK clock         */
/*   FLEXCAN7_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_10_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN7_CLK clock         */
/*   FLEXCAN8_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_11_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN8_CLK clock         */
/*   FLEXCAN9_CLK clock         */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_12_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN9_CLK clock         */
/*   FLEXCAN10_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_13_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN10_CLK clock        */
/*   FLEXCAN11_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_14_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN11_CLK clock        */
/*   FLEXCAN12_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_15_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN12_CLK clock        */
/*   FLEXCAN13_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_16_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN13_CLK clock        */
/*   FLEXCAN14_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_17_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN14_CLK clock        */
/*   FLEXCAN15_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_18_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN15_CLK clock        */
/*   FLEXCAN16_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_19_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN16_CLK clock        */
/*   FLEXCAN17_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_20_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN17_CLK clock        */
/*   FLEXCAN18_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_21_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN18_CLK clock        */
/*   FLEXCAN19_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_22_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN19_CLK clock        */
/*   FLEXCAN20_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_23_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN20_CLK clock        */
/*   FLEXCAN21_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_24_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN21_CLK clock        */
/*   FLEXCAN22_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_25_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN22_CLK clock        */
/*   FLEXCAN23_CLK clock        */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_26_BIT0_INDEX,       0U,                          0U},                                /*   FLEXCAN23_CLK clock        */
/*   P0_FR_PE_CLK clock         */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_FR_PE_EXTENSION,             0U,                 CLOCK_IP_SEL_6_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_FR_PE_CLK clock         */
/*   FRAY0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_2_BIT0_INDEX,        0U,                          0U},                                /*   FRAY0_CLK clock            */
/*   FRAY1_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_3_BIT0_INDEX,        0U,                          0U},                                /*   FRAY1_CLK clock            */
/*   GTM_CLK clock              */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_22_BIT0_INDEX,       0U,                          0U},                                /*   GTM_CLK clock            */
/*   IIIC0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_4_BIT0_INDEX,        0U,                          0U},                                /*   IIIC0_CLK clock            */
/*   IIIC1_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_0_BIT0_INDEX,        0U,                          0U},                                /*   IIIC1_CLK clock            */
/*   IIIC2_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_11_BIT0_INDEX,       0U,                          0U},                                /*   IIIC2_CLK clock            */
/*   P0_LIN_BAUD_CLK clock      */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_LIN_BAUD_EXTENSION,          0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_LIN_BAUD_CLK clock      */
/*   LIN0_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_8_BIT0_INDEX,        0U,                          0U},                                /*   LIN0_CLK clock             */
/*   LIN1_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_9_BIT0_INDEX,        0U,                          0U},                                /*   LIN1_CLK clock             */
/*   LIN2_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_10_BIT0_INDEX,       0U,                          0U},                                /*   LIN2_CLK clock             */
/*   P1_LIN_BAUD_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P1_LIN_BAUD_EXTENSION,          0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_LIN_BAUD_CLK clock      */
/*   LIN3_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_5_BIT0_INDEX,        0U,                          0U},                                /*   LIN3_CLK clock             */
/*   LIN4_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_6_BIT0_INDEX,        0U,                          0U},                                /*   LIN4_CLK clock             */
/*   LIN5_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_7_BIT0_INDEX,        0U,                          0U},                                /*   LIN5_CLK clock             */
/*   P4_LIN_BAUD_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_LIN_BAUD_EXTENSION,          0U,                 CLOCK_IP_SEL_8_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_LIN_BAUD_CLK clock      */
/*   LIN6_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_6_BIT0_INDEX,        0U,                          0U},                                /*   LIN6_CLK clock             */
/*   LIN7_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_7_BIT0_INDEX,        0U,                          0U},                                /*   LIN7_CLK clock             */
/*   LIN8_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_8_BIT0_INDEX,        0U,                          0U},                                /*   LIN8_CLK clock             */
/*   P5_LIN_BAUD_CLK clock      */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P5_LIN_BAUD_EXTENSION,          0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_LIN_BAUD_CLK clock      */
/*   LIN9_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_3_BIT0_INDEX,        0U,                          0U},                                /*   LIN9_CLK clock             */
/*   LIN10_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_4_BIT0_INDEX,        0U,                          0U},                                /*   LIN10_CLK clock            */
/*   LIN11_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_5_BIT0_INDEX,        0U,                          0U},                                /*   LIN11_CLK clock            */
/*   MSCDSPI_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_6_BIT0_INDEX,        0U,                          0U},                                /*   MSCDSPI_CLK clock          */
/*   MSCLIN_CLK clock           */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_11_BIT0_INDEX,       0U,                          0U},                                /*   MSCLIN_CLK clock            */
/*   NANO_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_22_BIT1_INDEX,       0U,                          0U},                                /*   NANO_CLK clock            */
/*   P0_CLKOUT_SRC_CLK clock    */ {CLOCK_IP_GPR0_INSTANCE,           CLOCK_IP_CLKOUT_CMU,                   CLOCK_IP_P0_CLKOUT_SRC_EXTENSION,        0U,                 CLOCK_IP_SEL_0_INDEX,        0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_DEBUG_1_INSTANCE},  /*   P0_CLKOUT_SRC_CLK clock    */
/*   P0_CTU_PER_CLK clock       */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_CTU_PER_EXTENSION,           0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P0_CTU_PER_CLK clock       */
/*   P0_DSPI_MSC_CLK clock      */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV_TRIGGER,            CLOCK_IP_P0_DSPI_MSC_EXTENSION,          0U,                 CLOCK_IP_SEL_7_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P0_DSPI_MSC_CLK clock      */
/*   P0_EMIOS_LCU_CLK clock     */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P0_EMIOS_LCU_EXTENSION,         0U,                 CLOCK_IP_SEL_9_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_EMIOS_LCU_CLK clock     */
/*   P0_GTM_CLK clock           */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV_TRIGGER,            CLOCK_IP_P0_GTM_EXTENSION,               0U,                 CLOCK_IP_SEL_7_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P0_GTM_CLK clock           */
/*   P0_GTM_NOC_CLK clock       */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_GTM_NOC_EXTENSION,           0U,                 CLOCK_IP_SEL_7_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_GTM_NOC_CLK clock       */
/*   P0_GTM_TS_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_GTM_TS_EXTENSION,            0U,                 CLOCK_IP_SEL_7_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_GTM_TS_CLK clock        */
/*   P0_LIN_CLK clock           */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_LIN_EXTENSION,               0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_LIN_CLK clock           */
/*   P0_NANO_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P0_NANO_EXTENSION,              0U,                 CLOCK_IP_SEL_7_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_NANO_CLK clock          */
/*   P0_PSI5_125K_CLK clock     */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_125K_EXTENSION,         0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_125K_CLK clock     */
/*   P0_PSI5_189K_CLK clock     */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_MUL_DIV,                CLOCK_IP_P0_PSI5_189K_EXTENSION,         0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_189K_CLK clock     */
/*   P0_PSI5_S_BAUD_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_BAUD_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_BAUD_CLK clock   */
/*   P0_PSI5_S_CORE_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_CORE_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_PSI5_S_CORE_CLK clock   */
/*   P0_PSI5_S_TRIG0_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_TRIG0_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_TRIG0_CLK clock  */
/*   P0_PSI5_S_TRIG1_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_TRIG1_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_TRIG1_CLK clock  */
/*   P0_PSI5_S_TRIG2_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_TRIG2_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_TRIG2_CLK clock  */
/*   P0_PSI5_S_TRIG3_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_TRIG3_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_TRIG3_CLK clock  */
/*   P0_PSI5_S_UART_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_UART_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_UART_CLK clock   */
/*   P0_PSI5_S_WDOG0_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_WDOG0_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_WDOG0_CLK clock  */
/*   P0_PSI5_S_WDOG1_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_WDOG1_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_WDOG1_CLK clock  */
/*   P0_PSI5_S_WDOG2_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_WDOG2_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_6_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_WDOG2_CLK clock  */
/*   P0_PSI5_S_WDOG3_CLK clock  */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_S_WDOG3_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_7_INDEX,        0U,                               0U,                          0U},                                /*   P0_PSI5_S_WDOG3_CLK clock  */
/*   P0_REG_INTF_2X_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_REG_INTF_2X_EXTENSION,       0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P0_REG_INTF_2X_CLK clock   */
/*   P0_REG_INTF_CLK clock      */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV_CMU,                CLOCK_IP_P0_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          CLOCK_IP_CMU_FC_0_INSTANCE},        /*   P0_REG_INTF_CLK clock      */
/*   P1_CLKOUT_SRC_CLK clock    */ {CLOCK_IP_GPR1_INSTANCE,           CLOCK_IP_CLKOUT_CMU,                   CLOCK_IP_P1_CLKOUT_SRC_EXTENSION,        0U,                 CLOCK_IP_SEL_1_INDEX,        0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_DEBUG_2_INSTANCE},  /*   P1_CLKOUT_SRC_CLK clock    */
/*   P1_DSPI60_CLK clock        */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P1_DSPI60_EXTENSION,            0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_DSPI60_CLK clock        */
/*   ETH_TS_CLK clock           */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH_TS_EXTENSION,               0U,                 CLOCK_IP_SEL_5_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   ETH_TS_CLK clock           */
/*   ETH_TS_DIV4_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH_TS_DIV4_EXTENSION,          0U,                 CLOCK_IP_SEL_5_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   ETH_TS_DIV4_CLK clock      */
/*   ETH0_REF_RMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_REF_RMII_EXTENSION,        0U,                 CLOCK_IP_SEL_7_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_REF_RMII_CLK clock    */
/*   ETH0_RX_MII_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_RX_MII_EXTENSION,          0U,                 CLOCK_IP_SEL_7_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_RX_MII_CLK clock      */
/*   ETH0_RX_RGMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_RX_RGMII_EXTENSION,        0U,                 CLOCK_IP_SEL_7_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_RX_RGMII_CLK clock    */
/*   ETH0_TX_RGMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_TX_RGMII_EXTENSION,        0U,                 CLOCK_IP_SEL_6_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_TX_RGMII_CLK clock    */
/*   ETH0_PS_TX_CLK             */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH0_TX_RGMII_LPBK_EXTENSION,   0U,                 CLOCK_IP_SEL_6_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH0_PS_TX_CLK     */
/*   ETH1_REF_RMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_REF_RMII_EXTENSION,        0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_REF_RMII_CLK clock    */
/*   ETH1_RX_MII_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_RX_MII_EXTENSION,          0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_RX_MII_CLK clock      */
/*   ETH1_RX_RGMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_RX_RGMII_EXTENSION,        0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_RX_RGMII_CLK clock    */
/*   ETH1_TX_MII_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_TX_MII_EXTENSION,          0U,                 CLOCK_IP_SEL_8_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_TX_MII_CLK clock      */
/*   ETH1_TX_RGMII_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_TX_RGMII_EXTENSION,        0U,                 CLOCK_IP_SEL_8_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_TX_RGMII_CLK clock    */
/*   ETH1_PS_TX_CLK             */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_ETH1_TX_RGMII_LPBK_EXTENSION,   0U,                 CLOCK_IP_SEL_8_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   ETH1_PS_TX_CLK     */
/*   P1_LFAST0_REF_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P1_LFAST0_REF_EXTENSION,        0U,                 CLOCK_IP_SEL_11_INDEX,       CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P1_LFAST0_REF_CLK clock    */
/*   P1_LFAST1_REF_CLK clock    */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P1_LFAST1_REF_EXTENSION,        0U,                 CLOCK_IP_SEL_12_INDEX,       CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P1_LFAST1_REF_CLK clock    */
/*   P1_NETC_AXI_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P1_NETC_AXI_EXTENSION,          0U,                 CLOCK_IP_SEL_14_INDEX,       CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P1_NETC_AXI_CLK clock      */
/*   P1_LIN_CLK clock           */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P1_LIN_EXTENSION,               0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P1_LIN_CLK clock           */
/*   P1_REG_INTF_CLK clock      */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX_DIV_CMU,                CLOCK_IP_P1_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          CLOCK_IP_CMU_FC_1_INSTANCE},        /*   P1_REG_INTF_CLK clock      */
/*   P2_DBG_ATB_CLK clock       */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P2_DBG_ATB_EXTENSION,           0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P2_DBG_ATB_CLK clock       */
/*   P2_REG_INTF_CLK clock      */ {CLOCK_IP_CGM2_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P2_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P2_REG_INTF_CLK clock      */
/*   P3_AES_CLK clock           */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P3_AES_EXTENSION,               0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P3_AES_CLK clock           */
/*   P3_CLKOUT_SRC_CLK clock    */ {CLOCK_IP_GPR3_INSTANCE,           CLOCK_IP_CLKOUT,                       CLOCK_IP_P3_CLKOUT_SRC_EXTENSION,        0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P3_CLKOUT_SRC_CLK clock    */
/*   P3_DBG_TS_CLK clock        */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P3_DBG_TS_EXTENSION,            0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P3_DBG_TS_CLK clock        */
/*   P3_REG_INTF_CLK clock      */ {CLOCK_IP_CGM3_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P3_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P3_REG_INTF_CLK clock      */
/*   P3_SYS_MON1_CLK clock      */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CMU_FC_3_INSTANCE},        /*   P3_SYS_MON1_CLK clock      */
/*   P3_SYS_MON2_CLK clock      */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CE_CMU_FC_0_INSTANCE},     /*   P3_SYS_MON2_CLK clock      */
/*   P3_SYS_MON3_CLK clock      */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_CE_CMU_FC_1_INSTANCE},     /*   P3_SYS_MON3_CLK clock      */
/*   P4_CLKOUT_SRC_CLK clock    */ {CLOCK_IP_GPR4_INSTANCE,           CLOCK_IP_CLKOUT,                       CLOCK_IP_P4_CLKOUT_SRC_EXTENSION,        0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_CLKOUT_SRC_CLK clock    */
/*   P4_DSPI60_CLK clock        */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_DSPI60_EXTENSION,            0U,                 CLOCK_IP_SEL_5_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_DSPI60_CLK clock        */
/*   P4_EMIOS_LCU_CLK clock     */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_EMIOS_LCU_EXTENSION,         0U,                 CLOCK_IP_SEL_11_INDEX,       0U,                          0U,                               0U,                          0U},                                /*   P4_EMIOS_LCU_CLK clock     */
/*   P4_LIN_CLK clock           */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_LIN_EXTENSION,               0U,                 CLOCK_IP_SEL_8_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_LIN_CLK clock           */
/*   P4_PSI5_125K_CLK clock     */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_125K_EXTENSION,         0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_125K_CLK clock     */
/*   P4_PSI5_189K_CLK clock     */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_MUL_DIV,                CLOCK_IP_P4_PSI5_189K_EXTENSION,         0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_189K_CLK clock     */
/*   P4_PSI5_S_BAUD_CLK clock   */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_BAUD_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_BAUD_CLK clock   */
/*   P4_PSI5_S_CORE_CLK clock   */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_CORE_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_PSI5_S_CORE_CLK clock   */
/*   P4_PSI5_S_TRIG0_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_TRIG0_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_TRIG0_CLK clock  */
/*   P4_PSI5_S_TRIG1_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_TRIG1_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_TRIG1_CLK clock  */
/*   P4_PSI5_S_TRIG2_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_TRIG2_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_TRIG2_CLK clock  */
/*   P4_PSI5_S_TRIG3_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_TRIG3_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_3_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_TRIG3_CLK clock  */
/*   P4_PSI5_S_UART_CLK clock   */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_UART_EXTENSION,       0U,                 CLOCK_IP_SEL_2_INDEX,        CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_UART_CLK clock   */
/*   P4_PSI5_S_WDOG0_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_WDOG0_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_4_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_WDOG0_CLK clock  */
/*   P4_PSI5_S_WDOG1_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_WDOG1_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_5_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_WDOG1_CLK clock  */
/*   P4_PSI5_S_WDOG2_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_WDOG2_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_6_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_WDOG2_CLK clock  */
/*   P4_PSI5_S_WDOG3_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_S_WDOG3_EXTENSION,      0U,                 CLOCK_IP_SEL_3_INDEX,        CLOCK_IP_DIV_7_INDEX,        0U,                               0U,                          0U},                                /*   P4_PSI5_S_WDOG3_CLK clock  */
/*   P4_QSPI0_2X_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_QSPI0_2X_EXTENSION,          0U,                 CLOCK_IP_SEL_7_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_QSPI0_2X_CLK clock      */
/*   P4_QSPI0_1X_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_QSPI0_1X_EXTENSION,          0U,                 CLOCK_IP_SEL_7_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_QSPI0_1X_CLK clock      */
/*   P4_QSPI1_2X_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_QSPI1_2X_EXTENSION,          0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P4_QSPI1_2X_CLK clock      */
/*   P4_QSPI1_1X_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_QSPI1_1X_EXTENSION,          0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P4_QSPI1_1X_CLK clock      */
/*   P4_REG_INTF_2X_CLK clock   */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_REG_INTF_2X_EXTENSION,       0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P4_REG_INTF_2X_CLK clock   */
/*   P4_REG_INTF_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV_CMU,                CLOCK_IP_P4_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          CLOCK_IP_CMU_FC_4_INSTANCE},        /*   P4_REG_INTF_CLK clock      */
/*   P4_SDHC_IP_CLK clock       */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_SDHC_IP_EXTENSION,           0U,                 CLOCK_IP_SEL_10_INDEX,       0U,                          0U,                               0U,                          0U},                                /*   P4_SDHC_IP_CLK clock       */
/*   P4_SDHC_IP_DIV2_CLK clock  */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_SDHC_IP_DIV2_EXTENSION,      0U,                 CLOCK_IP_SEL_10_INDEX,       0U,                          0U,                               0U,                          0U},                                /*   P4_SDHC_IP_DIV2_CLK clock  */
/*   P5_DIPORT_CLK clock        */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P5_AE_EXTENSION,                0U,                 CLOCK_IP_SEL_5_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_DIPORT_CLK clock        */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
/*   P5_AE_CLK clock            */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV_PCFS,               CLOCK_IP_P5_AE_EXTENSION,                0U,                 CLOCK_IP_SEL_5_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               CLOCK_IP_PCFS_2_INDEX,       0U},                                /*   P5_AE_CLK clock            */
#else
/*   P5_AE_CLK clock            */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,               CLOCK_IP_P5_AE_EXTENSION,                0U,                 CLOCK_IP_SEL_5_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               CLOCK_IP_PCFS_2_INDEX,       0U},                                /*   P5_AE_CLK clock            */
#endif
/*   P5_CANXL_PE_CLK clock      */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P5_CANXL_PE_EXTENSION,          0U,                 CLOCK_IP_SEL_5_INDEX,        CLOCK_IP_DIV_1_INDEX,        0U,                               0U,                          0U},                                /*   P5_CANXL_PE_CLK clock      */
/*   P5_CANXL_CHI_CLK clock     */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P5_CANXL_CHI_EXTENSION,         0U,                 CLOCK_IP_SEL_5_INDEX,        CLOCK_IP_DIV_2_INDEX,        0U,                               0U,                          0U},                                /*   P5_CANXL_CHI_CLK clock     */
/*   P5_CLKOUT_SRC_CLK clock    */ {CLOCK_IP_GPR5_INSTANCE,           CLOCK_IP_CLKOUT,                       CLOCK_IP_P5_CLKOUT_SRC_EXTENSION,        0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_CLKOUT_SRC_CLK clock    */
/*   P5_LIN_CLK clock           */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P5_LIN_EXTENSION,               0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P5_LIN_CLK clock           */
/*   P5_REG_INTF_CLK clock      */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX_DIV_CMU,                CLOCK_IP_P5_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          CLOCK_IP_CMU_FC_5_INSTANCE},        /*   P5_REG_INTF_CLK clock      */
/*   P6_REG_INTF_CLK clock      */ {CLOCK_IP_CGM6_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P6_REG_INTF_EXTENSION,          0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P6_REG_INTF_CLK clock      */
/*   PIT0_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_5_BIT3_INDEX,        0U,                          0U},                                /*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_1_BIT3_INDEX,        0U,                          0U},                                /*   PIT1_CLK clock             */
/*   PIT4_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_2_BIT3_INDEX,        0U,                          0U},                                /*   PIT4_CLK clock             */
/*   PIT5_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_0_BIT3_INDEX,        0U,                          0U},                                /*   PIT5_CLK clock             */
/*   P0_PSI5_1US_CLK clock      */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P0_PSI5_1US_EXTENSION,          0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P0_PSI5_1US_CLK clock      */
/*   PSI5_0_CLK clock           */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_19_BIT0_INDEX,       0U,                          0U},                                /*   PSI5_0_CLK clock           */
/*   P4_PSI5_1US_CLK clock      */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_PSI5_1US_EXTENSION,          0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   P4_PSI5_1US_CLK clock      */
/*   PSI5_1_CLK clock           */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_12_BIT0_INDEX,       0U,                          0U},                                /*   PSI5_1_CLK clock           */
/*   PSI5S_0_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_23_BIT0_INDEX,       0U,                          0U},                                /*   PSI5S_0_CLK clock          */
/*   PSI5S_1_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_14_BIT0_INDEX,       0U,                          0U},                                /*   PSI5S_1_CLK clock          */
/*   QSPI0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_0_BIT0_INDEX,        0U,                          0U},                                /*   QSPI0_CLK clock            */
/*   QSPI1_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_1_BIT0_INDEX,        0U,                          0U},                                /*   QSPI1_CLK clock            */
/*   RTU0_CORE_MON1_CLK         */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU0_CMU_FC_0_INSTANCE},   /*   RTU0_CORE_MON1_CLK         */
/*   RTU0_CORE_MON2_CLK         */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU0_CMU_FC_3_INSTANCE},   /*   RTU0_CORE_MON2_CLK         */
/*   RTU0_CORE_DIV2_MON1_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU0_CMU_FC_1_INSTANCE},   /*   RTU0_CORE_DIV2_MON1_CLK    */
/*   RTU0_CORE_DIV2_MON2_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU0_CMU_FC_2_INSTANCE},   /*   RTU0_CORE_DIV2_MON2_CLK    */
/*   RTU0_CORE_DIV2_MON3_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU0_CMU_FC_4_INSTANCE},   /*   RTU0_CORE_DIV2_MON3_CLK    */
/*   RTU0_REG_INTF_CLK clock    */ {CLOCK_IP_CGM7_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_RTU0_REG_INTF_EXTENSION,        0U,                 CLOCK_IP_SEL_1_INDEX,        0U,                          0U,                               0U,                          0U},                                /*   RTU0_REG_INTF_CLK clock    */
/*   RTU1_CORE_MON1_CLK         */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU1_CMU_FC_0_INSTANCE},   /*   RTU1_CORE_MON1_CLK         */
/*   RTU1_CORE_MON2_CLK         */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU1_CMU_FC_3_INSTANCE},   /*   RTU1_CORE_MON2_CLK         */
/*   RTU1_CORE_DIV2_MON1_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU1_CMU_FC_1_INSTANCE},   /*   RTU1_CORE_DIV2_MON1_CLK    */
/*   RTU1_CORE_DIV2_MON2_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU1_CMU_FC_2_INSTANCE},   /*   RTU1_CORE_DIV2_MON2_CLK    */
/*   RTU1_CORE_DIV2_MON3_CLK    */ {0U,                               CLOCK_IP_CMU,                          0U,                                      0U,                 0U,                          0U,                          0U,                               0U,                          CLOCK_IP_RTU1_CMU_FC_4_INSTANCE},   /*   RTU1_CORE_DIV2_MON3_CLK    */
/*   RTU1_REG_INTF_CLK clock    */ {CLOCK_IP_CGM8_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_RTU1_REG_INTF_EXTENSION,        0U,                 CLOCK_IP_SEL_1_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   RTU1_REG_INTF_CLK clock    */
/*   P4_SDHC_CLK clock          */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX_DIV,                    CLOCK_IP_P4_SDHC_EXTENSION,              0U,                 CLOCK_IP_SEL_9_INDEX,        CLOCK_IP_DIV_0_INDEX,        0U,                               0U,                          0U},                                /*   P4_SDHC_CLK clock          */
/*   RXLUT_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P3_GROUP_33_BIT0_INDEX,       0U,                          0U},                                /*   RXLUT_CLK clock            */
/*   SDHC0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_9_BIT0_INDEX,        0U,                          0U},                                /*   SDHC0_CLK clock            */
/*   SINC_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_24_BIT0_INDEX,       0U,                          0U},                                /*   SINC_CLK clock             */
/*   SIPI0_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_8_BIT0_INDEX,        0U,                          0U},                                /*   SIPI0_CLK clock            */
/*   SIPI1_CLK clock            */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_9_BIT0_INDEX,        0U,                          0U},                                /*   SIPI1_CLK clock            */
/*   SIUL2_0_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_21_BIT0_INDEX,       0U,                          0U},                                /*   SIUL2_0_CLK clock          */
/*   SIUL2_1_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_14_BIT0_INDEX,       0U,                          0U},                                /*   SIUL2_1_CLK clock          */
/*   SIUL2_4_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_13_BIT0_INDEX,       0U,                          0U},                                /*   SIUL2_4_CLK clock          */
/*   SIUL2_5_CLK clock          */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_6_BIT0_INDEX,        0U,                          0U},                                /*   SIUL2_5_CLK clock          */
/*   P0_DSPI_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P0_DSPI_EXTENSION,              0U,                 CLOCK_IP_SEL_5_INDEX,        0U,                          0U,                                    0U,                          0U},                                /*   P0_DSPI_CLK clock          */
/*   SPI0_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_1_BIT0_INDEX,        0U,                          0U},                                /*   SPI0_CLK clock             */
/*   SPI1_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P0_GROUP_7_BIT0_INDEX,        0U,                          0U},                                /*   SPI1_CLK clock             */
/*   P1_DSPI_CLK clock          */ {CLOCK_IP_CGM1_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P1_DSPI_EXTENSION,              0U,                 CLOCK_IP_SEL_2_INDEX,        0U,                          0U,                                    0U,                          0U},                                /*   P1_DSPI_CLK clock          */
/*   SPI2_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_2_BIT0_INDEX,        0U,                          0U},                                /*   SPI2_CLK clock             */
/*   SPI3_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_3_BIT0_INDEX,        0U,                          0U},                                /*   SPI3_CLK clock             */
/*   SPI4_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_4_BIT0_INDEX,        0U,                          0U},                                /*   SPI4_CLK clock             */
/*   P4_DSPI_CLK clock          */ {CLOCK_IP_CGM4_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P4_DSPI_EXTENSION,              0U,                 CLOCK_IP_SEL_4_INDEX,        0U,                          0U,                                    0U,                          0U},                                /*   P4_DSPI_CLK clock          */
/*   SPI5_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_3_BIT0_INDEX,        0U,                          0U},                                /*   SPI5_CLK clock             */
/*   SPI6_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_4_BIT0_INDEX,        0U,                          0U},                                /*   SPI6_CLK clock             */
/*   SPI7_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_5_BIT0_INDEX,        0U,                          0U},                                /*   SPI7_CLK clock             */
/*   P5_DSPI_CLK clock          */ {CLOCK_IP_CGM5_INSTANCE,           CLOCK_IP_HWMUX,                        CLOCK_IP_P5_DSPI_EXTENSION,              0U,                 CLOCK_IP_SEL_3_INDEX,        0U,                          0U,                                    0U,                          0U},                                /*   P5_DSPI_CLK clock          */
/*   SPI8_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_1_BIT0_INDEX,        0U,                          0U},                                /*   SPI8_CLK clock             */
/*   SPI9_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P5_GROUP_2_BIT0_INDEX,        0U,                          0U},                                /*   SPI9_CLK clock             */
/*   SRX0_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P1_GROUP_10_BIT0_INDEX,       0U,                          0U},                                /*   SRX0_CLK clock             */
/*   SRX1_CLK clock             */ {0U,                               CLOCK_IP_GATE,                         0U,                                      0U,                 0U,                          0U,                          CLOCK_IP_P4_GROUP_10_BIT0_INDEX,       0U,                          0U},                                /*   SRX1_CLK clock             */
/*   CORE_PLL_REFCLKOUT clock   */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                                    0U,                          0U},                                /*   CORE_PLL_REFCLKOUT clock   */
/*   CORE_PLL_FBCLKOUT clock    */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                                    0U,                          0U},                                /*   CORE_PLL_FBCLKOUT clock    */
/*   PERIPH_PLL_REFCLKOUT clock */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                                    0U,                          0U},                                /*   PERIPH_PLL_REFCLKOUT clock */
/*   PERIPH_PLL_FBCLKOUT clock  */ {0U,                               CLOCK_IP_NO_CALLBACK,                  0U,                                      0U,                 0U,                          0U,                          0U,                                    0U,                          0U},                                /*   PERIPH_PLL_FBCLKOUT clock  */
};


/*!
 * @brief Converts a clock name to a selector entry clkout hardware value
 */
const uint8 Clock_Ip_au8SoftwareMuxResetValue[CLOCK_IP_NAMES_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    0U,                                       /*!< FIRC_CLK                                */
    0U,                                       /*!< FXOSC_CLK                               */
    0U,                                       /*!< SIRC_CLK                                */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    0U,                                       /*!< FIRC_AE_CLK                             */
#endif
    0U,                                       /*!< COREPLL_CLK                             */
    0U,                                       /*!< PERIPHPLL_CLK                           */
    0U,                                       /*!< DDRPLL_CLK                              */
    0U,                                       /*!< LFAST0_PLL_CLK                          */
    0U,                                       /*!< LFAST1_PLL_CLK                          */
    0U,                                       /*!< COREPLL_PHI0_CLK                        */
    0U,                                       /*!< COREPLL_DFS0_CLK                        */
    0U,                                       /*!< COREPLL_DFS1_CLK                        */
    0U,                                       /*!< COREPLL_DFS2_CLK                        */
    0U,                                       /*!< COREPLL_DFS3_CLK                        */
    0U,                                       /*!< COREPLL_DFS4_CLK                        */
    0U,                                       /*!< COREPLL_DFS5_CLK                        */
    0U,                                       /*!< PERIPHPLL_PHI0_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI1_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI2_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI3_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI4_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI5_CLK                      */
    0U,                                       /*!< PERIPHPLL_PHI6_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS0_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS1_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS2_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS3_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS4_CLK                      */
    0U,                                       /*!< PERIPHPLL_DFS5_CLK                      */
    0U,                                       /*!< DDRPLL_PHI0_CLK                         */
    0U,                                       /*!< LFAST0_PLL_PH0_CLK                      */
    0U,                                       /*!< LFAST1_PLL_PH0_CLK                      */
    0U,                                       /*!< ETH_RGMII_REF_CLK                       */
    0U,                                       /*!< TMR_1588_CLK                          */
    0U,                                       /*!< ETH0_EXT_RX_CLK                         */
    0U,                                       /*!< ETH0_EXT_TX_CLK                         */
    0U,                                       /*!< ETH1_EXT_RX_CLK                         */
    0U,                                       /*!< ETH1_EXT_TX_CLK                         */
    0U,                                       /*!< LFAST0_EXT_REF_CLK                      */
    0U,                                       /*!< LFAST1_EXT_REF_CLK                      */
    0U,                                       /*!< DDR_CLK                                 */
    0U,                                       /*!< P0_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_DIV2_CLK                         */
    0U,                                       /*!< P1_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_SYS_CLK                              */
    0U,                                       /*!< CORE_M33_CLK                            */
    0U,                                       /*!< P2_SYS_DIV2_CLK                         */
    0U,                                       /*!< P2_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_CLK                              */
    0U,                                       /*!< CE_SYS_DIV2_CLK                         */
    0U,                                       /*!< CE_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_DIV2_NOC_CLK                     */
    0U,                                       /*!< P3_SYS_DIV4_CLK                         */
    0U,                                       /*!< P4_SYS_CLK                              */
    0U,                                       /*!< P4_SYS_DIV2_CLK                         */
    0U,                                       /*!< HSE_SYS_DIV2_CLK                        */
    0U,                                       /*!< P5_SYS_CLK                              */
    0U,                                       /*!< P5_SYS_DIV2_CLK                         */
    0U,                                       /*!< P5_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_MATH_CLK                             */
    0U,                                       /*!< P2_MATH_DIV3_CLK                        */
    0U,                                       /*!< GLB_LBIST_CLK                           */
    0U,                                       /*!< RTU0_CORE_CLK                           */
    0U,                                       /*!< RTU0_CORE_DIV2_CLK                      */
    0U,                                       /*!< RTU1_CORE_CLK                           */
    0U,                                       /*!< RTU1_CORE_DIV2_CLK                      */
    0U,                                       /*!< P0_PSI5_S_UTIL_CLK                      */
    0U,                                       /*!< P4_PSI5_S_UTIL_CLK                      */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    0U,                                       /*!< SYSTEM_DRUN_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    0U,                                       /*!< SYSTEM_CLK                              */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    0U,                                       /*!< SYSTEM_DIV2_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON2_CLK                         */
#endif
    0U,                                       /*!< THE_LAST_PRODUCER_CLK                   */
    0U,                                       /*!< ADC0_CLK                                */
    0U,                                       /*!< ADC1_CLK                                */
    0U,                                       /*!< CE_EDMA_CLK                             */
    0U,                                       /*!< CE_PIT0_CLK                             */
    0U,                                       /*!< CE_PIT1_CLK                             */
    0U,                                       /*!< CE_PIT2_CLK                             */
    0U,                                       /*!< CE_PIT3_CLK                             */
    0U,                                       /*!< CE_PIT4_CLK                             */
    0U,                                       /*!< CE_PIT5_CLK                             */
    0U,                                       /*!< CLKOUT0_CLK                             */
    0U,                                       /*!< CLKOUT1_CLK                             */
    0U,                                       /*!< CLKOUT2_CLK                             */
    0U,                                       /*!< CLKOUT3_CLK                             */
    0U,                                       /*!< CLKOUT4_CLK                             */
    0U,                                       /*!< CTU_CLK                                 */
    0U,                                       /*!< DMACRC0_CLK                             */
    0U,                                       /*!< DMACRC1_CLK                             */
    0U,                                       /*!< DMACRC4_CLK                             */
    0U,                                       /*!< DMACRC5_CLK                             */
    0U,                                       /*!< DMAMUX0_CLK                             */
    0U,                                       /*!< DMAMUX1_CLK                             */
    0U,                                       /*!< DMAMUX4_CLK                             */
    0U,                                       /*!< DMAMUX5_CLK                             */
    0U,                                       /*!< EDMA0_CLK                               */
    0U,                                       /*!< EDMA1_CLK                               */
    0U,                                       /*!< EDMA3_CLK                               */
    0U,                                       /*!< EDMA4_CLK                               */
    0U,                                       /*!< EDMA5_CLK                               */
    0U,                                       /*!< ETH0_TX_MII_CLK                         */
    0U,                                       /*!< ENET0_CLK                               */
    0U,                                       /*!< P3_CAN_PE_CLK                           */
    0U,                                       /*!< FLEXCAN0_CLK                            */
    0U,                                       /*!< FLEXCAN1_CLK                            */
    0U,                                       /*!< FLEXCAN2_CLK                            */
    0U,                                       /*!< FLEXCAN3_CLK                            */
    0U,                                       /*!< FLEXCAN4_CLK                            */
    0U,                                       /*!< FLEXCAN5_CLK                            */
    0U,                                       /*!< FLEXCAN6_CLK                            */
    0U,                                       /*!< FLEXCAN7_CLK                            */
    0U,                                       /*!< FLEXCAN8_CLK                            */
    0U,                                       /*!< FLEXCAN9_CLK                            */
    0U,                                       /*!< FLEXCAN10_CLK                           */
    0U,                                       /*!< FLEXCAN11_CLK                           */
    0U,                                       /*!< FLEXCAN12_CLK                           */
    0U,                                       /*!< FLEXCAN13_CLK                           */
    0U,                                       /*!< FLEXCAN14_CLK                           */
    0U,                                       /*!< FLEXCAN15_CLK                           */
    0U,                                       /*!< FLEXCAN16_CLK                           */
    0U,                                       /*!< FLEXCAN17_CLK                           */
    0U,                                       /*!< FLEXCAN18_CLK                           */
    0U,                                       /*!< FLEXCAN19_CLK                           */
    0U,                                       /*!< FLEXCAN20_CLK                           */
    0U,                                       /*!< FLEXCAN21_CLK                           */
    0U,                                       /*!< FLEXCAN22_CLK                           */
    0U,                                       /*!< FLEXCAN23_CLK                           */
    0U,                                       /*!< P0_FR_PE_CLK                            */
    0U,                                       /*!< FRAY0_CLK                               */
    0U,                                       /*!< FRAY1_CLK                               */
    0U,                                       /*!< GTM_CLK                                 */
    0U,                                       /*!< IIIC0_CLK                               */
    0U,                                       /*!< IIIC1_CLK                               */
    0U,                                       /*!< IIIC2_CLK                               */
    0U,                                       /*!< P0_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN0_CLK                                */
    0U,                                       /*!< LIN1_CLK                                */
    0U,                                       /*!< LIN2_CLK                                */
    0U,                                       /*!< P1_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN3_CLK                                */
    0U,                                       /*!< LIN4_CLK                                */
    0U,                                       /*!< LIN5_CLK                                */
    0U,                                       /*!< P4_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN6_CLK                                */
    0U,                                       /*!< LIN7_CLK                                */
    0U,                                       /*!< LIN8_CLK                                */
    0U,                                       /*!< P5_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN9_CLK                                */
    0U,                                       /*!< LIN10_CLK                               */
    0U,                                       /*!< LIN11_CLK                               */
    0U,                                       /*!< MSCDSPI_CLK                             */
    0U,                                       /*!< MSCLIN_CLK                              */
    0U,                                       /*!< NANO_CLK                                */
    0U,                                       /*!< P0_CLKOUT_SRC_CLK                       */
    0U,                                       /*!< P0_CTU_PER_CLK                          */
    0U,                                       /*!< P0_DSPI_MSC_CLK                         */
    0U,                                       /*!< P0_EMIOS_LCU_CLK                        */
    0U,                                       /*!< P0_GTM_CLK                              */
    0U,                                       /*!< P0_GTM_NOC_CLK                          */
    0U,                                       /*!< P0_GTM_TS_CLK                           */
    0U,                                       /*!< P0_LIN_CLK                              */
    0U,                                       /*!< P0_NANO_CLK                             */
    0U,                                       /*!< P0_PSI5_125K_CLK                        */
    0U,                                       /*!< P0_PSI5_189K_CLK                        */
    0U,                                       /*!< P0_PSI5_S_BAUD_CLK                      */
    0U,                                       /*!< P0_PSI5_S_CORE_CLK                      */
    0U,                                       /*!< P0_PSI5_S_TRIG0_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG1_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG2_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG3_CLK                     */
    0U,                                       /*!< P0_PSI5_S_UART_CLK                      */
    0U,                                       /*!< P0_PSI5_S_WDOG0_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG1_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG2_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG3_CLK                     */
    0U,                                       /*!< P0_REG_INTF_2X_CLK                      */
    0U,                                       /*!< P0_REG_INTF_CLK                         */
    0U,                                       /*!< P1_CLKOUT_SRC_CLK                       */
    0U,                                       /*!< P1_DSPI60_CLK                           */
    0U,                                       /*!< ETH_TS_CLK                              */
    0U,                                       /*!< ETH_TS_DIV4_CLK                         */
    0U,                                       /*!< ETH0_REF_RMII_CLK                       */
    0U,                                       /*!< ETH0_RX_MII_CLK                         */
    0U,                                       /*!< ETH0_RX_RGMII_CLK                       */
    0U,                                       /*!< ETH0_TX_RGMII_CLK                       */
    0U,                                       /*!< ETH0_PS_TX_CLK                          */
    0U,                                       /*!< ETH1_REF_RMII_CLK                       */
    0U,                                       /*!< ETH1_RX_MII_CLK                         */
    0U,                                       /*!< ETH1_RX_RGMII_CLK                       */
    0U,                                       /*!< ETH1_TX_MII_CLK                         */
    0U,                                       /*!< ETH1_TX_RGMII_CLK                       */
    0U,                                       /*!< ETH1_PS_TX_CLK                          */
    0U,                                       /*!< P1_LFAST0_REF_CLK                       */
    0U,                                       /*!< P1_LFAST1_REF_CLK                       */
    0U,                                       /*!< P1_NETC_AXI_CLK                         */
    0U,                                       /*!< P1_LIN_CLK                              */
    0U,                                       /*!< P1_REG_INTF_CLK                         */
    0U,                                       /*!< P2_DBG_ATB_CLK                          */
    0U,                                       /*!< P2_REG_INTF_CLK                         */
    0U,                                       /*!< P3_AES_CLK                              */
    0U,                                       /*!< P3_CLKOUT_SRC_CLK                       */
    0U,                                       /*!< P3_DBG_TS_CLK                           */
    0U,                                       /*!< P3_REG_INTF_CLK                         */
    0U,                                       /*!< P3_SYS_MON1_CLK                         */
    0U,                                       /*!< P3_SYS_MON2_CLK                         */
    0U,                                       /*!< P3_SYS_MON3_CLK                         */
    0U,                                       /*!< P4_CLKOUT_SRC_CLK                       */
    0U,                                       /*!< P4_DSPI60_CLK                           */
    0U,                                       /*!< P4_EMIOS_LCU_CLK                        */
    0U,                                       /*!< P4_LIN_CLK                              */
    0U,                                       /*!< P4_PSI5_125K_CLK                        */
    0U,                                       /*!< P4_PSI5_189K_CLK                        */
    0U,                                       /*!< P4_PSI5_S_BAUD_CLK                      */
    0U,                                       /*!< P4_PSI5_S_CORE_CLK                      */
    0U,                                       /*!< P4_PSI5_S_TRIG0_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG1_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG2_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG3_CLK                     */
    0U,                                       /*!< P4_PSI5_S_UART_CLK                      */
    0U,                                       /*!< P4_PSI5_S_WDOG0_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG1_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG2_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG3_CLK                     */
    0U,                                       /*!< P4_QSPI0_2X_CLK                         */
    0U,                                       /*!< P4_QSPI0_1X_CLK                         */
    0U,                                       /*!< P4_QSPI1_2X_CLK                         */
    0U,                                       /*!< P4_QSPI1_1X_CLK                         */
    0U,                                       /*!< P4_REG_INTF_2X_CLK                      */
    0U,                                       /*!< P4_REG_INTF_CLK                         */
    0U,                                       /*!< P4_SDHC_IP_CLK                          */
    0U,                                       /*!< P4_SDHC_IP_DIV2_CLK                     */
    0U,                                       /*!< P5_DIPORT_CLK                           */
    0U,                                       /*!< P5_AE_CLK                               */
    0U,                                       /*!< P5_CANXL_PE_CLK                         */
    0U,                                       /*!< P5_CANXL_CHI_CLK                        */
    0U,                                       /*!< P5_CLKOUT_SRC_CLK                       */
    0U,                                       /*!< P5_LIN_CLK                              */
    0U,                                       /*!< P5_REG_INTF_CLK                         */
    0U,                                       /*!< P6_REG_INTF_CLK                         */
    0U,                                       /*!< PIT0_CLK                                */
    0U,                                       /*!< PIT1_CLK                                */
    0U,                                       /*!< PIT4_CLK                                */
    0U,                                       /*!< PIT5_CLK                                */
    0U,                                       /*!< P0_PSI5_1US_CLK                         */
    0U,                                       /*!< PSI5_0_CLK                              */
    0U,                                       /*!< P4_PSI5_1US_CLK                         */
    0U,                                       /*!< PSI5_1_CLK                              */
    0U,                                       /*!< PSI5S_0_CLK                             */
    0U,                                       /*!< PSI5S_1_CLK                             */
    0U,                                       /*!< QSPI0_CLK                               */
    0U,                                       /*!< QSPI1_CLK                               */
    0U,                                       /*!< RTU0_CORE_MON1_CLK                      */
    0U,                                       /*!< RTU0_CORE_MON2_CLK                      */
    0U,                                       /*!< RTU0_CORE_DIV2_MON1_CLK                 */
    0U,                                       /*!< RTU0_CORE_DIV2_MON2_CLK                 */
    0U,                                       /*!< RTU0_CORE_DIV2_MON3_CLK                 */
    0U,                                       /*!< RTU0_REG_INTF_CLK                       */
    0U,                                       /*!< RTU1_CORE_MON1_CLK                      */
    0U,                                       /*!< RTU1_CORE_MON2_CLK                      */
    0U,                                       /*!< RTU1_CORE_DIV2_MON1_CLK                 */
    0U,                                       /*!< RTU1_CORE_DIV2_MON2_CLK                 */
    0U,                                       /*!< RTU1_CORE_DIV2_MON3_CLK                 */
    0U,                                       /*!< RTU1_REG_INTF_CLK                       */
    0U,                                       /*!< P4_SDHC_CLK                             */
    0U,                                       /*!< RXLUT_CLK                               */
    0U,                                       /*!< SDHC0_CLK                               */
    0U,                                       /*!< SINC_CLK                                */
    0U,                                       /*!< SIPI0_CLK                               */
    0U,                                       /*!< SIPI1_CLK                               */
    0U,                                       /*!< SIUL2_0_CLK                             */
    0U,                                       /*!< SIUL2_1_CLK                             */
    0U,                                       /*!< SIUL2_4_CLK                             */
    0U,                                       /*!< SIUL2_5_CLK                             */
    0U,                                       /*!< P0_DSPI_CLK                             */
    0U,                                       /*!< SPI0_CLK                                */
    0U,                                       /*!< SPI1_CLK                                */
    0U,                                       /*!< P1_DSPI_CLK                             */
    0U,                                       /*!< SPI2_CLK                                */
    0U,                                       /*!< SPI3_CLK                                */
    0U,                                       /*!< SPI4_CLK                                */
    0U,                                       /*!< P4_DSPI_CLK                             */
    0U,                                       /*!< SPI5_CLK                                */
    0U,                                       /*!< SPI6_CLK                                */
    0U,                                       /*!< SPI7_CLK                                */
    0U,                                       /*!< P5_DSPI_CLK                             */
    0U,                                       /*!< SPI8_CLK                                */
    0U,                                       /*!< SPI9_CLK                                */
    0U,                                       /*!< SRX0_CLK                                */
    0U,                                       /*!< SRX1_CLK                                */
    0U,                                       /*!< CORE_PLL_REFCLKOUT clock                */
    0U,                                       /*!< CORE_PLL_FBCLKOUT clock                 */
    0U,                                       /*!< PERIPH_PLL_REFCLKOUT clock              */
    0U,                                       /*!< PERIPH_PLL_FBCLKOUT clock               */
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_8
#include "Mcu_MemMap.h"




/* Clock start constant section data */
#define MCU_START_SEC_CONST_16
#include "Mcu_MemMap.h"
/*!
 * @brief Converts a clock name to a selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryHardwareValue[CLOCK_IP_NAMES_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    0U,                                       /*!< FIRC_CLK                                */
    2U,                                       /*!< FXOSC_CLK                               */
    1U,                                       /*!< SIRC_CLK                                */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    0U,                                       /*!< FIRC_AE_CLK                             */
#endif
    0U,                                       /*!< COREPLL_CLK                             */
    0U,                                       /*!< PERIPHPLL_CLK                           */
    0U,                                       /*!< DDRPLL_CLK                              */
    0U,                                       /*!< LFAST0_PLL_CLK                          */
    0U,                                       /*!< LFAST1_PLL_CLK                          */
    10U,                                      /*!< CORE_PLL_PHI0_CLK                       */
    11U,                                      /*!< CORE_PLL_DFS0_CLK                       */
    12U,                                      /*!< CORE_PLL_DFS1_CLK                       */
    13U,                                      /*!< CORE_PLL_DFS2_CLK                       */
    14U,                                      /*!< CORE_PLL_DFS3_CLK                       */
    15U,                                      /*!< CORE_PLL_DFS4_CLK                       */
    16U,                                      /*!< CORE_PLL_DFS5_CLK                       */
    20U,                                      /*!< PERIPH_PLL_PHI0_CLK                     */
    21U,                                      /*!< PERIPH_PLL_PHI1_CLK                     */
    22U,                                      /*!< PERIPH_PLL_PHI2_CLK                     */
    23U,                                      /*!< PERIPH_PLL_PHI3_CLK                     */
    24U,                                      /*!< PERIPH_PLL_PHI4_CLK                     */
    25U,                                      /*!< PERIPH_PLL_PHI5_CLK                     */
    26U,                                      /*!< PERIPH_PLL_PHI6_CLK                     */
    30U,                                      /*!< PERIPH_PLL_DFS0_CLK                     */
    31U,                                      /*!< PERIPH_PLL_DFS1_CLK                     */
    32U,                                      /*!< PERIPH_PLL_DFS2_CLK                     */
    33U,                                      /*!< PERIPH_PLL_DFS3_CLK                     */
    34U,                                      /*!< PERIPH_PLL_DFS4_CLK                     */
    35U,                                      /*!< PERIPH_PLL_DFS5_CLK                     */
    40U,                                      /*!< DDR_PLL_PHI0_CLK                        */
    0U,                                       /*!< LFAST0_PLL_PH0_CLK                      */
    0U,                                       /*!< LFAST1_PLL_PH0_CLK                      */
    47U,                                      /*!< ENET_EXT_REF_CLK                        */
    48U,                                      /*!< ENET_EXT_TS_CLK                         */
    49U,                                      /*!< ENET0_EXT_RX_CLK                        */
    50U,                                      /*!< ENET0_EXT_TX_CLK                        */
    51U,                                      /*!< ENET1_EXT_RX_CLK                        */
    52U,                                      /*!< ENET1_EXT_TX_CLK                        */
    59U,                                      /*!< LFAST0_EXT_TX_CLK                       */
    60U,                                      /*!< LFAST1_EXT_TX_CLK                       */
    0U,                                       /*!< DDR_CLK                                 */
    0U,                                       /*!< P0_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_DIV2_CLK                         */
    0U,                                       /*!< P1_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_SYS_CLK                              */
    0U,                                       /*!< CORE_M33_CLK                            */
    0U,                                       /*!< P2_SYS_DIV2_CLK                         */
    0U,                                       /*!< P2_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_CLK                              */
    0U,                                       /*!< CE_SYS_DIV2_CLK                         */
    0U,                                       /*!< CE_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_DIV2_NOC_CLK                     */
    0U,                                       /*!< P3_SYS_DIV4_CLK                         */
    0U,                                       /*!< P4_SYS_CLK                              */
    0U,                                       /*!< P4_SYS_DIV2_CLK                         */
    0U,                                       /*!< HSE_SYS_DIV2_CLK                        */
    0U,                                       /*!< P5_SYS_CLK                              */
    0U,                                       /*!< P5_SYS_DIV2_CLK                         */
    0U,                                       /*!< P5_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_MATH_CLK                             */
    0U,                                       /*!< P2_MATH_DIV3_CLK                        */
    0U,                                       /*!< GLB_LBIST_CLK                           */
    0U,                                       /*!< RTU0_CORE_CLK                           */
    0U,                                       /*!< RTU0_CORE_DIV2_CLK                      */
    0U,                                       /*!< RTU1_CORE_CLK                           */
    0U,                                       /*!< RTU1_CORE_DIV2_CLK                      */
    62U,                                      /*!< P0_PSI5_S_UTIL_CLK                      */
    62U,                                      /*!< P4_PSI5_S_UTIL_CLK                      */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    0U,                                       /*!< SYSTEM_DRUN_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
    0U,                                       /*!< SYSTEM_RUN0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
    0U,                                       /*!< SYSTEM_SAFE_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    0U,                                       /*!< SYSTEM_CLK                              */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    0U,                                       /*!< SYSTEM_DIV2_CL                          */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON2_CLK                         */
#endif
    0U,                                       /*!<   THE_LAST_PRODUCER_CLK                 */
    0U,                                       /*!<   ADC0_CLK clock                        */
    0U,                                       /*!<   ADC1_CLK clock                        */
    0U,                                       /*!<   CE_EDMA_CLK clock                     */
    0U,                                       /*!<   CE_PIT0_CLK clock                     */
    0U,                                       /*!<   CE_PIT1_CLK clock                     */
    0U,                                       /*!<   CE_PIT2_CLK clock                     */
    0U,                                       /*!<   CE_PIT3_CLK clock                     */
    0U,                                       /*!<   CE_PIT4_CLK clock                     */
    0U,                                       /*!<   CE_PIT5_CLK clock                     */
    0U,                                       /*!<   CLKOUT0_CLK clock                     */
    0U,                                       /*!<   CLKOUT1_CLK clock                     */
    0U,                                       /*!<   CLKOUT2_CLK clock                     */
    0U,                                       /*!<   CLKOUT3_CLK clock                     */
    0U,                                       /*!<   CLKOUT4_CLK clock                     */
    0U,                                       /*!<   CTU_CLK clock                         */
    0U,                                       /*!<   DMACRC0_CLK clock                     */
    0U,                                       /*!<   DMACRC1_CLK clock                     */
    0U,                                       /*!<   DMACRC4_CLK clock                     */
    0U,                                       /*!<   DMACRC5_CLK clock                     */
    0U,                                       /*!<   DMAMUX0_CLK clock                     */
    0U,                                       /*!<   DMAMUX1_CLK clock                     */
    0U,                                       /*!<   DMAMUX4_CLK clock                     */
    0U,                                       /*!<   DMAMUX5_CLK clock                     */
    0U,                                       /*!<   EDMA0_CLK clock                       */
    0U,                                       /*!<   EDMA1_CLK clock                       */
    0U,                                       /*!<   EDMA3_CLK clock                       */
    0U,                                       /*!<   EDMA4_CLK clock                       */
    0U,                                       /*!<   EDMA5_CLK clock                       */
    0U,                                       /*!<   ETH0_TX_MII_CLK clock                 */
    0U,                                       /*!<   ENET0_CLK clock                       */
    0U,                                       /*!<   P3_CAN_PE_CLK clock                   */
    0U,                                       /*!<   FLEXCAN0_CLK clock                    */
    0U,                                       /*!<   FLEXCAN1_CLK clock                    */
    0U,                                       /*!<   FLEXCAN2_CLK clock                    */
    0U,                                       /*!<   FLEXCAN3_CLK clock                    */
    0U,                                       /*!<   FLEXCAN4_CLK clock                    */
    0U,                                       /*!<   FLEXCAN5_CLK clock                    */
    0U,                                       /*!<   FLEXCAN6_CLK clock                    */
    0U,                                       /*!<   FLEXCAN7_CLK clock                    */
    0U,                                       /*!<   FLEXCAN8_CLK clock                    */
    0U,                                       /*!<   FLEXCAN9_CLK clock                    */
    0U,                                       /*!<   FLEXCAN10_CLK clock                   */
    0U,                                       /*!<   FLEXCAN11_CLK clock                   */
    0U,                                       /*!<   FLEXCAN12_CLK clock                   */
    0U,                                       /*!<   FLEXCAN13_CLK clock                   */
    0U,                                       /*!<   FLEXCAN14_CLK clock                   */
    0U,                                       /*!<   FLEXCAN15_CLK clock                   */
    0U,                                       /*!<   FLEXCAN16_CLK clock                   */
    0U,                                       /*!<   FLEXCAN17_CLK clock                   */
    0U,                                       /*!<   FLEXCAN18_CLK clock                   */
    0U,                                       /*!<   FLEXCAN19_CLK clock                   */
    0U,                                       /*!<   FLEXCAN20_CLK clock                   */
    0U,                                       /*!<   FLEXCAN21_CLK clock                   */
    0U,                                       /*!<   FLEXCAN22_CLK clock                   */
    0U,                                       /*!<   FLEXCAN23_CLK clock                   */
    0U,                                       /*!<   P0_FR_PE_CLK clock                    */
    0U,                                       /*!<   FRAY0_CLK clock                       */
    0U,                                       /*!<   FRAY1_CLK clock                       */
    0U,                                       /*!<   GTM_CLK clock                         */
    0U,                                       /*!<   IIIC0_CLK clock                       */
    0U,                                       /*!<   IIIC1_CLK clock                       */
    0U,                                       /*!<   IIIC2_CLK clock                       */
    0U,                                       /*!<   P0_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN0_CLK clock                        */
    0U,                                       /*!<   LIN1_CLK clock                        */
    0U,                                       /*!<   LIN2_CLK clock                        */
    0U,                                       /*!<   P1_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN3_CLK clock                        */
    0U,                                       /*!<   LIN4_CLK clock                        */
    0U,                                       /*!<   LIN5_CLK clock                        */
    0U,                                       /*!<   P4_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN6_CLK clock                        */
    0U,                                       /*!<   LIN7_CLK clock                        */
    0U,                                       /*!<   LIN8_CLK clock                        */
    0U,                                       /*!<   P5_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN9_CLK clock                        */
    0U,                                       /*!<   LIN10_CLK clock                       */
    0U,                                       /*!<   LIN11_CLK clock                       */
    0U,                                       /*!<   MSCDSPI_CLK clock                     */
    0U,                                       /*!<   MSCLIN_CLK clock                      */
    0U,                                       /*!<   NANO_CLK clock                        */
    61U,                                      /*!<   P0_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P0_CTU_PER_CLK clock                  */
    0U,                                       /*!<   P0_DSPI_MSC_CLK clock                 */
    0U,                                       /*!<   P0_EMIOS_LCU_CLK clock                */
    0U,                                       /*!<   P0_GTM_CLK clock                      */
    0U,                                       /*!<   P0_GTM_NOC_CLK clock                  */
    0U,                                       /*!<   P0_GTM_TS_CLK clock                   */
    0U,                                       /*!<   P0_LIN_CLK clock                      */
    0U,                                       /*!<   P0_NANO_CLK clock                     */
    0U,                                       /*!<   P0_PSI5_125K_CLK clock                */
    0U,                                       /*!<   P0_PSI5_189K_CLK clock                */
    0U,                                       /*!<   P0_PSI5_S_BAUD_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_CORE_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_TRIG0_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG1_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG2_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG3_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_UART_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_WDOG0_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG1_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG2_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG3_CLK clock             */
    0U,                                       /*!<   P0_REG_INTF_2X_CLK clock              */
    0U,                                       /*!<   P0_REG_INTF_CLK clock                 */
    61U,                                      /*!<   P1_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P1_DSPI60_CLK clock                   */
    0U,                                       /*!<   ETH_TS_CLK clock                      */
    0U,                                       /*!<   ETH_TS_DIV4_CLK clock                 */
    0U,                                       /*!<   ETH0_REF_RMII_CLK clock               */
    0U,                                       /*!<   ETH0_RX_MII_CLK clock                 */
    0U,                                       /*!<   ETH0_RX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH0_TX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH0_PS_TX_CLK                        */
    0U,                                       /*!<   ETH1_REF_RMII_CLK clock               */
    0U,                                       /*!<   ETH1_RX_MII_CLK clock                 */
    0U,                                       /*!<   ETH1_RX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH1_TX_MII_CLK clock                 */
    0U,                                       /*!<   ETH1_TX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH1_PS_TX_CLK                        */
    0U,                                       /*!<   P1_LFAST0_REF_CLK clock               */
    0U,                                       /*!<   P1_LFAST1_REF_CLK clock               */
    0U,                                       /*!<   P1_NETC_AXI_CLK clock                 */
    0U,                                       /*!<   P1_LIN_CLK clock                      */
    0U,                                       /*!<   P1_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P2_DBG_ATB_CLK clock                  */
    0U,                                       /*!<   P2_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P3_AES_CLK clock                      */
    61U,                                      /*!<   P3_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P3_DBG_TS_CLK clock                   */
    0U,                                       /*!<   P3_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON1_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON2_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON3_CLK clock                 */
    61U,                                      /*!<   P4_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P4_DSPI60_CLK clock                   */
    0U,                                       /*!<   P4_EMIOS_LCU_CLK clock                */
    0U,                                       /*!<   P4_LIN_CLK clock                      */
    0U,                                       /*!<   P4_PSI5_125K_CLK clock                */
    0U,                                       /*!<   P4_PSI5_189K_CLK clock                */
    0U,                                       /*!<   P4_PSI5_S_BAUD_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_CORE_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_TRIG0_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG1_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG2_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG3_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_UART_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_WDOG0_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG1_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG2_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG3_CLK clock             */
    0U,                                       /*!<   P4_QSPI0_2X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI0_1X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI1_2X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI1_1X_CLK clock                 */
    0U,                                       /*!<   P4_REG_INTF_2X_CLK clock              */
    0U,                                       /*!<   P4_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P4_SDHC_IP_CLK clock                  */
    0U,                                       /*!<   P4_SDHC_IP_DIV2_CLK clock             */
    0U,                                       /*!<   P5_DIPORT_CLK clock                   */
    0U,                                       /*!<   P5_AE_CLK clock                       */
    0U,                                       /*!<   P5_CANXL_PE_CLK clock                 */
    0U,                                       /*!<   P5_CANXL_CHI_CLK clock                */
    61U,                                      /*!<   P5_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P5_LIN_CLK clock                      */
    0U,                                       /*!<   P5_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P6_REG_INTF_CLK clock                 */
    0U,                                       /*!<   PIT0_CLK clock                        */
    0U,                                       /*!<   PIT1_CLK clock                        */
    0U,                                       /*!<   PIT4_CLK clock                        */
    0U,                                       /*!<   PIT5_CLK clock                        */
    0U,                                       /*!<   P0_PSI5_1US_CLK clock                 */
    0U,                                       /*!<   PSI5_0_CLK clock                      */
    0U,                                       /*!<   P4_PSI5_1US_CLK clock                 */
    0U,                                       /*!<   PSI5_1_CLK clock                      */
    0U,                                       /*!<   PSI5S_0_CLK clock                     */
    0U,                                       /*!<   PSI5S_1_CLK clock                     */
    0U,                                       /*!<   QSPI0_CLK clock                       */
    0U,                                       /*!<   QSPI1_CLK clock                       */
    0U,                                       /*!<   RTU0_CORE_MON1_CLK                    */
    0U,                                       /*!<   RTU0_CORE_MON2_CLK                    */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON1_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON2_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON3_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON4_CLK               */
    0U,                                       /*!<   RTU0_REG_INTF_CLK clock               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON1_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON2_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON3_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON4_CLK               */
    0U,                                       /*!<   RTU1_REG_INTF_CLK clock               */
    0U,                                       /*!<   P4_SDHC_CLK clock                     */
    0U,                                       /*!<   RXLUT_CLK clock                       */
    0U,                                       /*!<   SDHC0_CLK clock                       */
    0U,                                       /*!<   SINC_CLK clock                        */
    0U,                                       /*!<   SIPI0_CLK clock                       */
    0U,                                       /*!<   SIPI1_CLK clock                       */
    0U,                                       /*!<   SIUL2_0_CLK clock                     */
    0U,                                       /*!<   SIUL2_1_CLK clock                     */
    0U,                                       /*!<   SIUL2_4_CLK clock                     */
    0U,                                       /*!<   SIUL2_5_CLK clock                     */
    0U,                                       /*!<   P0_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI0_CLK clock                        */
    0U,                                       /*!<   SPI1_CLK clock                        */
    0U,                                       /*!<   P1_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI2_CLK clock                        */
    0U,                                       /*!<   SPI3_CLK clock                        */
    0U,                                       /*!<   SPI4_CLK clock                        */
    0U,                                       /*!<   P4_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI5_CLK clock                        */
    0U,                                       /*!<   SPI6_CLK clock                        */
    0U,                                       /*!<   SPI7_CLK clock                        */
    0U,                                       /*!<   P5_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI8_CLK clock                        */
    0U,                                       /*!<   SPI9_CLK clock                        */
    0U,                                       /*!<   SRX0_CLK clock                        */
    0U,                                       /*!<   SRX1_CLK clock                        */
    0U,                                       /*!<   CORE_PLL_REFCLKOUT clock              */
    0U,                                       /*!<   CORE_PLL_FBCLKOUT clock               */
    0U,                                       /*!<   PERIPH_PLL_REFCLKOUT clock            */
    0U,                                       /*!<   PERIPH_PLL_FBCLKOUT clock             */
};

/*!
 * @brief Converts a clock name to a selector entry clkout hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryClkoutHardwareValue[CLOCK_IP_NAMES_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    1U,                                       /*!< FIRC_CLK                                */
    2U,                                       /*!< FXOSC_CLK                               */
    0U,                                       /*!< SIRC_CLK                                */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    0U,                                       /*!< FIRC_AE_CLK                             */
#endif
    0U,                                       /*!< COREPLL_CLK                             */
    0U,                                       /*!< PERIPHPLL_CLK                           */
    0U,                                       /*!< DDRPLL_CLK                              */
    0U,                                       /*!< LFAST0_PLL_CLK                          */
    0U,                                       /*!< LFAST1_PLL_CLK                          */
    3U,                                       /*!< COREPLL_PHI0_CLK                        */
    4U,                                       /*!< COREPLL_DFS0_CLK                        */
    5U,                                       /*!< COREPLL_DFS1_CLK                        */
    6U,                                       /*!< COREPLL_DFS2_CLK                        */
    7U,                                       /*!< COREPLL_DFS3_CLK                        */
    8U,                                       /*!< COREPLL_DFS4_CLK                        */
    9U,                                       /*!< COREPLL_DFS5_CLK                        */
    10U,                                      /*!< PERIPHPLL_PHI0_CLK                      */
    11U,                                      /*!< PERIPHPLL_PHI1_CLK                      */
    12U,                                      /*!< PERIPHPLL_PHI2_CLK                      */
    13U,                                      /*!< PERIPHPLL_PHI3_CLK                      */
    14U,                                      /*!< PERIPHPLL_PHI4_CLK                      */
    15U,                                      /*!< PERIPHPLL_PHI5_CLK                      */
    16U,                                      /*!< PERIPHPLL_PHI6_CLK                      */
    17U,                                      /*!< PERIPHPLL_DFS0_CLK                      */
    18U,                                      /*!< PERIPHPLL_DFS1_CLK                      */
    19U,                                      /*!< PERIPHPLL_DFS2_CLK                      */
    20U,                                      /*!< PERIPHPLL_DFS3_CLK                      */
    21U,                                      /*!< PERIPHPLL_DFS4_CLK                      */
    22U,                                      /*!< PERIPHPLL_DFS5_CLK                      */
    23U,                                      /*!< DDRPLL_PHI0_CLK                         */
    0U,                                       /*!< LFAST0_PLL_PH0_CLK                      */
    1U,                                       /*!< LFAST1_PLL_PH0_CLK                      */
    0U,                                       /*!< ETH_RGMII_REF_CLK                       */
    0U,                                       /*!< TMR_1588_CLK                          */
    0U,                                       /*!< ETH0_EXT_RX_CLK                         */
    0U,                                       /*!< ETH0_EXT_TX_CLK                         */
    0U,                                       /*!< ETH1_EXT_RX_CLK                         */
    0U,                                       /*!< ETH1_EXT_TX_CLK                         */
    0U,                                       /*!< LFAST0_EXT_REF_CLK                      */
    0U,                                       /*!< LFAST1_EXT_REF_CLK                      */
    9U,                                       /*!< DDR_CLK                                 */
    24U,                                      /*!< P0_SYS_CLK                              */
    2U,                                       /*!< P1_SYS_CLK                              */
    3U,                                       /*!< P1_SYS_DIV2_CLK                         */
    4U,                                       /*!< P1_SYS_DIV4_CLK                         */
    6U,                                       /*!< P2_SYS_CLK                              */
    0U,                                       /*!< CORE_M33_CLK                            */
    0U,                                       /*!< P2_SYS_DIV2_CLK                         */
    0U,                                       /*!< P2_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_CLK                              */
    1U,                                       /*!< CE_SYS_DIV2_CLK                         */
    2U,                                       /*!< CE_SYS_DIV4_CLK                         */
    10U,                                      /*!< P3_SYS_DIV2_NOC_CLK                     */
    0U,                                       /*!< P3_SYS_DIV4_CLK                         */
    0U,                                       /*!< P4_SYS_CLK                              */
    1U,                                       /*!< P4_SYS_DIV2_CLK                         */
    2U,                                       /*!< HSE_SYS_DIV2_CLK                        */
    0U,                                       /*!< P5_SYS_CLK                              */
    1U,                                       /*!< P5_SYS_DIV2_CLK                         */
    2U,                                       /*!< P5_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_MATH_CLK                             */
    0U,                                       /*!< P2_MATH_DIV3_CLK                        */
    0U,                                       /*!< GLB_LBIST_CLK                           */
    0U,                                       /*!< RTU0_CORE_CLK                           */
    7U,                                       /*!< RTU0_CORE_DIV2_CLK                      */
    0U,                                       /*!< RTU1_CORE_CLK                           */
    8U,                                       /*!< RTU1_CORE_DIV2_CLK                      */
    30U,                                      /*!< P0_PSI5_S_UTIL_CLK                      */
    8U,                                       /*!< P4_PSI5_S_UTIL_CLK                      */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    0U,                                       /*!< SYSTEM_DRUN_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    0U,                                       /*!< SYSTEM_CLK                              */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    0U,                                       /*!< SYSTEM_DIV2_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON2_CLK                         */
#endif
    0U,                                       /*!< THE_LAST_PRODUCER_CLK                   */
    0U,                                       /*!< ADC0_CLK                                */
    0U,                                       /*!< ADC1_CLK                                */
    0U,                                       /*!< CE_EDMA_CLK                             */
    0U,                                       /*!< CE_PIT0_CLK                             */
    0U,                                       /*!< CE_PIT1_CLK                             */
    0U,                                       /*!< CE_PIT2_CLK                             */
    0U,                                       /*!< CE_PIT3_CLK                             */
    0U,                                       /*!< CE_PIT4_CLK                             */
    0U,                                       /*!< CE_PIT5_CLK                             */
    0U,                                       /*!< CLKOUT0_CLK                             */
    0U,                                       /*!< CLKOUT1_CLK                             */
    0U,                                       /*!< CLKOUT2_CLK                             */
    0U,                                       /*!< CLKOUT3_CLK                             */
    0U,                                       /*!< CLKOUT4_CLK                             */
    0U,                                       /*!< CTU_CLK                                 */
    0U,                                       /*!< DMACRC0_CLK                             */
    0U,                                       /*!< DMACRC1_CLK                             */
    0U,                                       /*!< DMACRC4_CLK                             */
    0U,                                       /*!< DMACRC5_CLK                             */
    0U,                                       /*!< DMAMUX0_CLK                             */
    0U,                                       /*!< DMAMUX1_CLK                             */
    0U,                                       /*!< DMAMUX4_CLK                             */
    0U,                                       /*!< DMAMUX5_CLK                             */
    0U,                                       /*!< EDMA0_CLK                               */
    0U,                                       /*!< EDMA1_CLK                               */
    0U,                                       /*!< EDMA3_CLK                               */
    0U,                                       /*!< EDMA4_CLK                               */
    0U,                                       /*!< EDMA5_CLK                               */
    12U,                                      /*!< ETH0_TX_MII_CLK                         */
    0U,                                       /*!< ENET0_CLK                               */
    5U,                                       /*!< P3_CAN_PE_CLK                           */
    0U,                                       /*!< FLEXCAN0_CLK                            */
    0U,                                       /*!< FLEXCAN1_CLK                            */
    0U,                                       /*!< FLEXCAN2_CLK                            */
    0U,                                       /*!< FLEXCAN3_CLK                            */
    0U,                                       /*!< FLEXCAN4_CLK                            */
    0U,                                       /*!< FLEXCAN5_CLK                            */
    0U,                                       /*!< FLEXCAN6_CLK                            */
    0U,                                       /*!< FLEXCAN7_CLK                            */
    0U,                                       /*!< FLEXCAN8_CLK                            */
    0U,                                       /*!< FLEXCAN9_CLK                            */
    0U,                                       /*!< FLEXCAN10_CLK                           */
    0U,                                       /*!< FLEXCAN11_CLK                           */
    0U,                                       /*!< FLEXCAN12_CLK                           */
    0U,                                       /*!< FLEXCAN13_CLK                           */
    0U,                                       /*!< FLEXCAN14_CLK                           */
    0U,                                       /*!< FLEXCAN15_CLK                           */
    0U,                                       /*!< FLEXCAN16_CLK                           */
    0U,                                       /*!< FLEXCAN17_CLK                           */
    0U,                                       /*!< FLEXCAN18_CLK                           */
    0U,                                       /*!< FLEXCAN19_CLK                           */
    0U,                                       /*!< FLEXCAN20_CLK                           */
    0U,                                       /*!< FLEXCAN21_CLK                           */
    0U,                                       /*!< FLEXCAN22_CLK                           */
    0U,                                       /*!< FLEXCAN23_CLK                           */
    37U,                                      /*!< P0_FR_PE_CLK                            */
    0U,                                       /*!< FRAY0_CLK                               */
    0U,                                       /*!< FRAY1_CLK                               */
    0U,                                       /*!< GTM_CLK                                 */
    0U,                                       /*!< IIIC0_CLK                               */
    0U,                                       /*!< IIIC1_CLK                               */
    0U,                                       /*!< IIIC2_CLK                               */
    34U,                                      /*!< P0_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN0_CLK                                */
    0U,                                       /*!< LIN1_CLK                                */
    0U,                                       /*!< LIN2_CLK                                */
    8U,                                       /*!< P1_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN3_CLK                                */
    0U,                                       /*!< LIN4_CLK                                */
    0U,                                       /*!< LIN5_CLK                                */
    16U,                                      /*!< P4_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN6_CLK                                */
    0U,                                       /*!< LIN7_CLK                                */
    0U,                                       /*!< LIN8_CLK                                */
    4U,                                       /*!< P5_LIN_BAUD_CLK                         */
    0U,                                       /*!< LIN9_CLK                                */
    0U,                                       /*!< LIN10_CLK                               */
    0U,                                       /*!< LIN11_CLK                               */
    0U,                                       /*!< MSCDSPI_CLK                             */
    0U,                                       /*!< MSCLIN_CLK                              */
    0U,                                       /*!< NANO_CLK                                */
    0U,                                       /*!< P0_CLKOUT_SRC_CLK                       */
    43U,                                      /*!< P0_CTU_PER_CLK                          */
    42U,                                      /*!< P0_DSPI_MSC_CLK                         */
    44U,                                      /*!< P0_EMIOS_LCU_CLK                        */
    39U,                                      /*!< P0_GTM_CLK                              */
    40U,                                      /*!< P0_GTM_NOC_CLK                          */
    41U,                                      /*!< P0_GTM_TS_CLK                           */
    35U,                                      /*!< P0_LIN_CLK                              */
    38U,                                      /*!< P0_NANO_CLK                             */
    28U,                                      /*!< P0_PSI5_125K_CLK                        */
    29U,                                      /*!< P0_PSI5_189K_CLK                        */
    32U,                                      /*!< P0_PSI5_S_BAUD_CLK                      */
    33U,                                      /*!< P0_PSI5_S_CORE_CLK                      */
    0U,                                       /*!< P0_PSI5_S_TRIG0_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG1_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG2_CLK                     */
    0U,                                       /*!< P0_PSI5_S_TRIG3_CLK                     */
    31U,                                      /*!< P0_PSI5_S_UART_CLK                      */
    0U,                                       /*!< P0_PSI5_S_WDOG0_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG1_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG2_CLK                     */
    0U,                                       /*!< P0_PSI5_S_WDOG3_CLK                     */
    26U,                                      /*!< P0_REG_INTF_2X_CLK                      */
    25U,                                      /*!< P0_REG_INTF_CLK                         */
    0U,                                       /*!< P1_CLKOUT_SRC_CLK                       */
    7U,                                       /*!< P1_DSPI60_CLK                           */
    10U,                                      /*!< ETH_TS_CLK                              */
    11U,                                      /*!< ETH_TS_DIV4_CLK                         */
    16U,                                      /*!< ETH0_REF_RMII_CLK                       */
    14U,                                      /*!< ETH0_RX_MII_CLK                         */
    15U,                                      /*!< ETH0_RX_RGMII_CLK                       */
    13U,                                      /*!< ETH0_TX_RGMII_CLK                       */
    0U,                                       /*!< ETH0_PS_TX_CLK                          */
    21U,                                      /*!< ETH1_REF_RMII_CLK                       */
    19U,                                      /*!< ETH1_RX_MII_CLK                         */
    20U,                                      /*!< ETH1_RX_RGMII_CLK                       */
    17U,                                      /*!< ETH1_TX_MII_CLK                         */
    18U,                                      /*!< ETH1_TX_RGMII_CLK                       */
    0U,                                       /*!< ETH1_PS_TX_CLK                          */
    0U,                                       /*!< P1_LFAST0_REF_CLK                       */
    0U,                                       /*!< P1_LFAST1_REF_CLK                       */
    0U,                                       /*!< P1_NETC_AXI_CLK                         */
    9U,                                       /*!< P1_LIN_CLK                              */
    5U,                                       /*!< P1_REG_INTF_CLK                         */
    0U,                                       /*!< P2_DBG_ATB_CLK                          */
    0U,                                       /*!< P2_REG_INTF_CLK                         */
    5U,                                       /*!< P3_AES_CLK                              */
    0U,                                       /*!< P3_CLKOUT_SRC_CLK                       */
    4U,                                       /*!< P3_DBG_TS_CLK                           */
    3U,                                       /*!< P3_REG_INTF_CLK                         */
    0U,                                       /*!< P3_SYS_MON1_CLK                         */
    0U,                                       /*!< P3_SYS_MON2_CLK                         */
    0U,                                       /*!< P3_SYS_MON3_CLK                         */
    0U,                                       /*!< P4_CLKOUT_SRC_CLK                       */
    13U,                                      /*!< P4_DSPI60_CLK                           */
    23U,                                      /*!< P4_EMIOS_LCU_CLK                        */
    17U,                                      /*!< P4_LIN_CLK                              */
    6U,                                       /*!< P4_PSI5_125K_CLK                        */
    7U,                                       /*!< P4_PSI5_189K_CLK                        */
    10U,                                      /*!< P4_PSI5_S_BAUD_CLK                      */
    11U,                                      /*!< P4_PSI5_S_CORE_CLK                      */
    0U,                                       /*!< P4_PSI5_S_TRIG0_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG1_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG2_CLK                     */
    0U,                                       /*!< P4_PSI5_S_TRIG3_CLK                     */
    9U,                                       /*!< P4_PSI5_S_UART_CLK                      */
    0U,                                       /*!< P4_PSI5_S_WDOG0_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG1_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG2_CLK                     */
    0U,                                       /*!< P4_PSI5_S_WDOG3_CLK                     */
    14U,                                      /*!< P4_QSPI0_2X_CLK                         */
    15U,                                      /*!< P4_QSPI0_1X_CLK                         */
    19U,                                      /*!< P4_QSPI1_2X_CLK                         */
    20U,                                      /*!< P4_QSPI1_1X_CLK                         */
    4U,                                       /*!< P4_REG_INTF_2X_CLK                      */
    3U,                                       /*!< P4_REG_INTF_CLK                         */
    21U,                                      /*!< P4_SDHC_IP_CLK                          */
    22U,                                      /*!< P4_SDHC_IP_DIV2_CLK                     */
    7U,                                       /*!< P5_DIPORT_CLK                           */
    8U,                                       /*!< P5_AE_CLK                               */
    9U,                                       /*!< P5_CANXL_PE_CLK                         */
    10U,                                      /*!< P5_CANXL_CHI_CLK                        */
    0U,                                       /*!< P5_CLKOUT_SRC_CLK                       */
    5U,                                       /*!< P5_LIN_CLK                              */
    3U,                                       /*!< P5_REG_INTF_CLK                         */
    0U,                                       /*!< P6_REG_INTF_CLK                         */
    0U,                                       /*!< PIT0_CLK                                */
    0U,                                       /*!< PIT1_CLK                                */
    0U,                                       /*!< PIT4_CLK                                */
    0U,                                       /*!< PIT5_CLK                                */
    27U,                                      /*!< P0_PSI5_1US_CLK                         */
    0U,                                       /*!< PSI5_0_CLK                              */
    5U,                                       /*!< P4_PSI5_1US_CLK                         */
    0U,                                       /*!< PSI5_1_CLK                              */
    0U,                                       /*!< PSI5S_0_CLK                             */
    0U,                                       /*!< PSI5S_1_CLK                             */
    0U,                                       /*!< QSPI0_CLK                               */
    0U,                                       /*!< QSPI1_CLK                               */
    0U,                                       /*!< RTU0_CORE_MON1_CLK                      */
    0U,                                       /*!< RTU0_CORE_MON2_CLK                      */
    0U,                                       /*!< RTU0_CORE_DIV2_MON1_CLK                 */
    0U,                                       /*!< RTU0_CORE_DIV2_MON2_CLK                 */
    0U,                                       /*!< RTU0_CORE_DIV2_MON3_CLK                 */
    0U,                                       /*!< RTU0_REG_INTF_CLK                       */
    0U,                                       /*!< RTU1_CORE_MON1_CLK                      */
    0U,                                       /*!< RTU1_CORE_MON2_CLK                      */
    0U,                                       /*!< RTU1_CORE_DIV2_MON1_CLK                 */
    0U,                                       /*!< RTU1_CORE_DIV2_MON2_CLK                 */
    0U,                                       /*!< RTU1_CORE_DIV2_MON3_CLK                 */
    0U,                                       /*!< RTU1_REG_INTF_CLK                       */
    18U,                                      /*!< P4_SDHC_CLK                             */
    0U,                                       /*!< RXLUT_CLK                               */
    0U,                                       /*!< SDHC0_CLK                               */
    0U,                                       /*!< SINC_CLK                                */
    0U,                                       /*!< SIPI0_CLK                               */
    0U,                                       /*!< SIPI1_CLK                               */
    0U,                                       /*!< SIUL2_0_CLK                             */
    0U,                                       /*!< SIUL2_1_CLK                             */
    0U,                                       /*!< SIUL2_4_CLK                             */
    0U,                                       /*!< SIUL2_5_CLK                             */
    36U,                                      /*!< P0_DSPI_CLK                             */
    0U,                                       /*!< SPI0_CLK                                */
    0U,                                       /*!< SPI1_CLK                                */
    6U,                                       /*!< P1_DSPI_CLK                             */
    0U,                                       /*!< SPI2_CLK                                */
    0U,                                       /*!< SPI3_CLK                                */
    0U,                                       /*!< SPI4_CLK                                */
    12U,                                      /*!< P4_DSPI_CLK                             */
    0U,                                       /*!< SPI5_CLK                                */
    0U,                                       /*!< SPI6_CLK                                */
    0U,                                       /*!< SPI7_CLK                                */
    6U,                                       /*!< P5_DSPI_CLK                             */
    0U,                                       /*!< SPI8_CLK                                */
    0U,                                       /*!< SPI9_CLK                                */
    0U,                                       /*!< SRX0_CLK                                */
    0U,                                       /*!< SRX1_CLK                                */
    45U,                                       /*!< CORE_PLL_REFCLKOUT clock                */
    46U,                                       /*!< CORE_PLL_FBCLKOUT clock                 */
    47U,                                       /*!< PERIPH_PLL_REFCLKOUT clock              */
    48U,                                       /*!< PERIPH_PLL_FBCLKOUT clock               */
};


#ifdef CLOCK_IP_MC_ME_AE_GS_S_SYSCLK
/*!
 * @brief Converts a clock name to a AE selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryAeHardwareValue[CLOCK_IP_FEATURE_NAMES_NO] = {
    0U,                                       /*!< CLOCK_IS_OFF                            */
    0U,                                       /*!< FIRC_CLK                                */
    0U,                                       /*!< FXOSC_CLK                               */
    0U,                                       /*!< SIRC_CLK                                */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    0U,                                       /*!< FIRC_AE_CLK                             */
#endif
    0U,                                       /*!< COREPLL_CLK                             */
    0U,                                       /*!< PERIPHPLL_CLK                           */
    0U,                                       /*!< DDRPLL_CLK                              */
    0U,                                       /*!< LFAST0_PLL_CLK                          */
    0U,                                       /*!< LFAST1_PLL_CLK                          */
    0U,                                       /*!< CORE_PLL_PHI0_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS0_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS1_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS2_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS3_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS4_CLK                       */
    0U,                                       /*!< CORE_PLL_DFS5_CLK                       */
    0U,                                       /*!< PERIPH_PLL_PHI0_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI1_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI2_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI3_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI4_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI5_CLK                     */
    0U,                                       /*!< PERIPH_PLL_PHI6_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS0_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS1_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS2_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS3_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS4_CLK                     */
    0U,                                       /*!< PERIPH_PLL_DFS5_CLK                     */
    0U,                                       /*!< DDR_PLL_PHI0_CLK                        */
    0U,                                       /*!< LFAST0_PLL_PH0_CLK                      */
    0U,                                       /*!< LFAST1_PLL_PH0_CLK                      */
    0U,                                       /*!< ENET_EXT_REF_CLK                        */
    0U,                                       /*!< ENET_EXT_TS_CLK                         */
    0U,                                       /*!< ENET0_EXT_RX_CLK                        */
    0U,                                       /*!< ENET0_EXT_TX_CLK                        */
    0U,                                       /*!< ENET1_EXT_RX_CLK                        */
    0U,                                       /*!< ENET1_EXT_TX_CLK                        */
    0U,                                       /*!< LFAST0_EXT_TX_CLK                       */
    0U,                                       /*!< LFAST1_EXT_TX_CLK                       */
    0U,                                       /*!< DDR_CLK                                 */
    0U,                                       /*!< P0_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_CLK                              */
    0U,                                       /*!< P1_SYS_DIV2_CLK                         */
    0U,                                       /*!< P1_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_SYS_CLK                              */
    0U,                                       /*!< CORE_M33_CLK                            */
    0U,                                       /*!< P2_SYS_DIV2_CLK                         */
    0U,                                       /*!< P2_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_CLK                              */
    0U,                                       /*!< CE_SYS_DIV2_CLK                         */
    0U,                                       /*!< CE_SYS_DIV4_CLK                         */
    0U,                                       /*!< P3_SYS_DIV2_NOC_CLK                     */
    0U,                                       /*!< P3_SYS_DIV4_CLK                         */
    0U,                                       /*!< P4_SYS_CLK                              */
    0U,                                       /*!< P4_SYS_DIV2_CLK                         */
    0U,                                       /*!< HSE_SYS_DIV2_CLK                        */
    0U,                                       /*!< P5_SYS_CLK                              */
    0U,                                       /*!< P5_SYS_DIV2_CLK                         */
    0U,                                       /*!< P5_SYS_DIV4_CLK                         */
    0U,                                       /*!< P2_MATH_CLK                             */
    0U,                                       /*!< P2_MATH_DIV3_CLK                        */
    0U,                                       /*!< GLB_LBIST_CLK                           */
    0U,                                       /*!< RTU0_CORE_CLK                           */
    0U,                                       /*!< RTU0_CORE_DIV2_CLK                      */
    0U,                                       /*!< RTU1_CORE_CLK                           */
    0U,                                       /*!< RTU1_CORE_DIV2_CLK                      */
    0U,                                       /*!< P0_PSI5_S_UTIL_CLK                      */
    0U,                                       /*!< P4_PSI5_S_UTIL_CLK                      */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    0U,                                       /*!< SYSTEM_DRUN_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
    0U,                                       /*!< SYSTEM_RUN0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
    0U,                                       /*!< SYSTEM_SAFE_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    0U,                                       /*!< SYSTEM_CLK                              */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    0U,                                       /*!< SYSTEM_DIV2_CL                          */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    0U,                                       /*!< SYSTEM_DIV4_MON2_CLK                         */
#endif
    0U,                                       /*!<   THE_LAST_PRODUCER_CLK                 */
    0U,                                       /*!<   ADC0_CLK clock                        */
    0U,                                       /*!<   ADC1_CLK clock                        */
    0U,                                       /*!<   CE_EDMA_CLK clock                     */
    0U,                                       /*!<   CE_PIT0_CLK clock                     */
    0U,                                       /*!<   CE_PIT1_CLK clock                     */
    0U,                                       /*!<   CE_PIT2_CLK clock                     */
    0U,                                       /*!<   CE_PIT3_CLK clock                     */
    0U,                                       /*!<   CE_PIT4_CLK clock                     */
    0U,                                       /*!<   CE_PIT5_CLK clock                     */
    0U,                                       /*!<   CLKOUT0_CLK clock                     */
    0U,                                       /*!<   CLKOUT1_CLK clock                     */
    0U,                                       /*!<   CLKOUT2_CLK clock                     */
    0U,                                       /*!<   CLKOUT3_CLK clock                     */
    0U,                                       /*!<   CLKOUT4_CLK clock                     */
    0U,                                       /*!<   CTU_CLK clock                         */
    0U,                                       /*!<   DMACRC0_CLK clock                     */
    0U,                                       /*!<   DMACRC1_CLK clock                     */
    0U,                                       /*!<   DMACRC4_CLK clock                     */
    0U,                                       /*!<   DMACRC5_CLK clock                     */
    0U,                                       /*!<   DMAMUX0_CLK clock                     */
    0U,                                       /*!<   DMAMUX1_CLK clock                     */
    0U,                                       /*!<   DMAMUX4_CLK clock                     */
    0U,                                       /*!<   DMAMUX5_CLK clock                     */
    0U,                                       /*!<   EDMA0_CLK clock                       */
    0U,                                       /*!<   EDMA1_CLK clock                       */
    0U,                                       /*!<   EDMA3_CLK clock                       */
    0U,                                       /*!<   EDMA4_CLK clock                       */
    0U,                                       /*!<   EDMA5_CLK clock                       */
    0U,                                       /*!<   ETH0_TX_MII_CLK clock                 */
    0U,                                       /*!<   ENET0_CLK clock                       */
    0U,                                       /*!<   P3_CAN_PE_CLK clock                   */
    0U,                                       /*!<   FLEXCAN0_CLK clock                    */
    0U,                                       /*!<   FLEXCAN1_CLK clock                    */
    0U,                                       /*!<   FLEXCAN2_CLK clock                    */
    0U,                                       /*!<   FLEXCAN3_CLK clock                    */
    0U,                                       /*!<   FLEXCAN4_CLK clock                    */
    0U,                                       /*!<   FLEXCAN5_CLK clock                    */
    0U,                                       /*!<   FLEXCAN6_CLK clock                    */
    0U,                                       /*!<   FLEXCAN7_CLK clock                    */
    0U,                                       /*!<   FLEXCAN8_CLK clock                    */
    0U,                                       /*!<   FLEXCAN9_CLK clock                    */
    0U,                                       /*!<   FLEXCAN10_CLK clock                   */
    0U,                                       /*!<   FLEXCAN11_CLK clock                   */
    0U,                                       /*!<   FLEXCAN12_CLK clock                   */
    0U,                                       /*!<   FLEXCAN13_CLK clock                   */
    0U,                                       /*!<   FLEXCAN14_CLK clock                   */
    0U,                                       /*!<   FLEXCAN15_CLK clock                   */
    0U,                                       /*!<   FLEXCAN16_CLK clock                   */
    0U,                                       /*!<   FLEXCAN17_CLK clock                   */
    0U,                                       /*!<   FLEXCAN18_CLK clock                   */
    0U,                                       /*!<   FLEXCAN19_CLK clock                   */
    0U,                                       /*!<   FLEXCAN20_CLK clock                   */
    0U,                                       /*!<   FLEXCAN21_CLK clock                   */
    0U,                                       /*!<   FLEXCAN22_CLK clock                   */
    0U,                                       /*!<   FLEXCAN23_CLK clock                   */
    0U,                                       /*!<   P0_FR_PE_CLK clock                    */
    0U,                                       /*!<   FRAY0_CLK clock                       */
    0U,                                       /*!<   FRAY1_CLK clock                       */
    0U,                                       /*!<   GTM_CLK clock                         */
    0U,                                       /*!<   IIIC0_CLK clock                       */
    0U,                                       /*!<   IIIC1_CLK clock                       */
    0U,                                       /*!<   IIIC2_CLK clock                       */
    0U,                                       /*!<   P0_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN0_CLK clock                        */
    0U,                                       /*!<   LIN1_CLK clock                        */
    0U,                                       /*!<   LIN2_CLK clock                        */
    0U,                                       /*!<   P1_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN3_CLK clock                        */
    0U,                                       /*!<   LIN4_CLK clock                        */
    0U,                                       /*!<   LIN5_CLK clock                        */
    0U,                                       /*!<   P4_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN6_CLK clock                        */
    0U,                                       /*!<   LIN7_CLK clock                        */
    0U,                                       /*!<   LIN8_CLK clock                        */
    0U,                                       /*!<   P5_LIN_BAUD_CLK clock                 */
    0U,                                       /*!<   LIN9_CLK clock                        */
    0U,                                       /*!<   LIN10_CLK clock                       */
    0U,                                       /*!<   LIN11_CLK clock                       */
    0U,                                       /*!<   MSCDSPI_CLK clock                     */
    0U,                                       /*!<   MSCLIN_CLK clock                      */
    0U,                                       /*!<   NANO_CLK clock                        */
    0U,                                       /*!<   P0_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P0_CTU_PER_CLK clock                  */
    0U,                                       /*!<   P0_DSPI_MSC_CLK clock                 */
    0U,                                       /*!<   P0_EMIOS_LCU_CLK clock                */
    0U,                                       /*!<   P0_GTM_CLK clock                      */
    0U,                                       /*!<   P0_GTM_NOC_CLK clock                  */
    0U,                                       /*!<   P0_GTM_TS_CLK clock                   */
    0U,                                       /*!<   P0_LIN_CLK clock                      */
    0U,                                       /*!<   P0_NANO_CLK clock                     */
    0U,                                       /*!<   P0_PSI5_125K_CLK clock                */
    0U,                                       /*!<   P0_PSI5_189K_CLK clock                */
    0U,                                       /*!<   P0_PSI5_S_BAUD_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_CORE_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_TRIG0_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG1_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG2_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_TRIG3_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_UART_CLK clock              */
    0U,                                       /*!<   P0_PSI5_S_WDOG0_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG1_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG2_CLK clock             */
    0U,                                       /*!<   P0_PSI5_S_WDOG3_CLK clock             */
    0U,                                       /*!<   P0_REG_INTF_2X_CLK clock              */
    0U,                                       /*!<   P0_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P1_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P1_DSPI60_CLK clock                   */
    0U,                                       /*!<   ETH_TS_CLK clock                      */
    0U,                                       /*!<   ETH_TS_DIV4_CLK clock                 */
    0U,                                       /*!<   ETH0_REF_RMII_CLK clock               */
    0U,                                       /*!<   ETH0_RX_MII_CLK clock                 */
    0U,                                       /*!<   ETH0_RX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH0_TX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH0_PS_TX_CLK                        */
    0U,                                       /*!<   ETH1_REF_RMII_CLK clock               */
    0U,                                       /*!<   ETH1_RX_MII_CLK clock                 */
    0U,                                       /*!<   ETH1_RX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH1_TX_MII_CLK clock                 */
    0U,                                       /*!<   ETH1_TX_RGMII_CLK clock               */
    0U,                                       /*!<   ETH1_PS_TX_CLK                        */
    0U,                                       /*!<   P1_LFAST0_REF_CLK clock               */
    0U,                                       /*!<   P1_LFAST1_REF_CLK clock               */
    0U,                                       /*!<   P1_NETC_AXI_CLK clock                 */
    0U,                                       /*!<   P1_LIN_CLK clock                      */
    0U,                                       /*!<   P1_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P2_DBG_ATB_CLK clock                  */
    0U,                                       /*!<   P2_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P3_AES_CLK clock                      */
    0U,                                       /*!<   P3_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P3_DBG_TS_CLK clock                   */
    0U,                                       /*!<   P3_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON1_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON2_CLK clock                 */
    0U,                                       /*!<   P3_SYS_MON3_CLK clock                 */
    0U,                                       /*!<   P4_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P4_DSPI60_CLK clock                   */
    0U,                                       /*!<   P4_EMIOS_LCU_CLK clock                */
    0U,                                       /*!<   P4_LIN_CLK clock                      */
    0U,                                       /*!<   P4_PSI5_125K_CLK clock                */
    0U,                                       /*!<   P4_PSI5_189K_CLK clock                */
    0U,                                       /*!<   P4_PSI5_S_BAUD_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_CORE_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_TRIG0_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG1_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG2_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_TRIG3_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_UART_CLK clock              */
    0U,                                       /*!<   P4_PSI5_S_WDOG0_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG1_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG2_CLK clock             */
    0U,                                       /*!<   P4_PSI5_S_WDOG3_CLK clock             */
    0U,                                       /*!<   P4_QSPI0_2X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI0_1X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI1_2X_CLK clock                 */
    0U,                                       /*!<   P4_QSPI1_1X_CLK clock                 */
    0U,                                       /*!<   P4_REG_INTF_2X_CLK clock              */
    0U,                                       /*!<   P4_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P4_SDHC_IP_CLK clock                  */
    0U,                                       /*!<   P4_SDHC_IP_DIV2_CLK clock             */
    0U,                                       /*!<   P5_DIPORT_CLK clock                   */
    1U,                                       /*!<   P5_AE_CLK clock                       */
    0U,                                       /*!<   P5_CANXL_PE_CLK clock                 */
    0U,                                       /*!<   P5_CANXL_CHI_CLK clock                */
    0U,                                       /*!<   P5_CLKOUT_SRC_CLK clock               */
    0U,                                       /*!<   P5_LIN_CLK clock                      */
    0U,                                       /*!<   P5_REG_INTF_CLK clock                 */
    0U,                                       /*!<   P6_REG_INTF_CLK clock                 */
    0U,                                       /*!<   PIT0_CLK clock                        */
    0U,                                       /*!<   PIT1_CLK clock                        */
    0U,                                       /*!<   PIT4_CLK clock                        */
    0U,                                       /*!<   PIT5_CLK clock                        */
    0U,                                       /*!<   P0_PSI5_1US_CLK clock                 */
    0U,                                       /*!<   PSI5_0_CLK clock                      */
    0U,                                       /*!<   P4_PSI5_1US_CLK clock                 */
    0U,                                       /*!<   PSI5_1_CLK clock                      */
    0U,                                       /*!<   PSI5S_0_CLK clock                     */
    0U,                                       /*!<   PSI5S_1_CLK clock                     */
    0U,                                       /*!<   QSPI0_CLK clock                       */
    0U,                                       /*!<   QSPI1_CLK clock                       */
    0U,                                       /*!<   RTU0_CORE_MON1_CLK                    */
    0U,                                       /*!<   RTU0_CORE_MON2_CLK                    */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON1_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON2_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON3_CLK               */
    0U,                                       /*!<   RTU0_CORE_DIV2_MON4_CLK               */
    0U,                                       /*!<   RTU0_REG_INTF_CLK clock               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON1_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON2_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON3_CLK               */
    0U,                                       /*!<   RTU1_CORE_DIV2_MON4_CLK               */
    0U,                                       /*!<   RTU1_REG_INTF_CLK clock               */
    0U,                                       /*!<   P4_SDHC_CLK clock                     */
    0U,                                       /*!<   RXLUT_CLK clock                       */
    0U,                                       /*!<   SDHC0_CLK clock                       */
    0U,                                       /*!<   SINC_CLK clock                        */
    0U,                                       /*!<   SIPI0_CLK clock                       */
    0U,                                       /*!<   SIPI1_CLK clock                       */
    0U,                                       /*!<   SIUL2_0_CLK clock                     */
    0U,                                       /*!<   SIUL2_1_CLK clock                     */
    0U,                                       /*!<   SIUL2_4_CLK clock                     */
    0U,                                       /*!<   SIUL2_5_CLK clock                     */
    0U,                                       /*!<   P0_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI0_CLK clock                        */
    0U,                                       /*!<   SPI1_CLK clock                        */
    0U,                                       /*!<   P1_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI2_CLK clock                        */
    0U,                                       /*!<   SPI3_CLK clock                        */
    0U,                                       /*!<   SPI4_CLK clock                        */
    0U,                                       /*!<   P4_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI5_CLK clock                        */
    0U,                                       /*!<   SPI6_CLK clock                        */
    0U,                                       /*!<   SPI7_CLK clock                        */
    0U,                                       /*!<   P5_DSPI_CLK clock                     */
    0U,                                       /*!<   SPI8_CLK clock                        */
    0U,                                       /*!<   SPI9_CLK clock                        */
    0U,                                       /*!<   SRX0_CLK clock                        */
    0U,                                       /*!<   SRX1_CLK clock                        */
    0U,                                       /*!<   CORE_PLL_REFCLKOUT clock              */
    0U,                                       /*!<   CORE_PLL_FBCLKOUT clock               */
    0U,                                       /*!<   PERIPH_PLL_REFCLKOUT clock            */
    0U,                                       /*!<   PERIPH_PLL_FBCLKOUT clock             */
};
#endif


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_16
#include "Mcu_MemMap.h"




/* Clock start constant section data */
#define MCU_START_SEC_CONST_32
#include "Mcu_MemMap.h"

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
    #if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
/* Clock name types */
const uint32 Clock_Ip_au8ClockNameTypes[CLOCK_IP_NAMES_NO] =
{
/*   CLOCK_IS_OFF clock         */ 0U,                                                                                                                                                                                          /*   CLOCK_IS_OFF               */
/*   FIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FIRC_CLK clock             */
/*   FXOSC_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FXOSC_CLK clock            */
/*   SIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIRC_CLK clock             */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
/*   FIRC_AE_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FIRC_AE_CLK clock             */
#endif
/*   COREPLL_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_CLK clock          */
/*   PERIPHPLL_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_CLK clock        */
/*   DDRPLL_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DDRPLL_CLK clock           */
/*   LFAST0_PLL_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LFAST0_PLL_CLK clock       */
/*   LFAST1_PLL_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LFAST1_PLL_CLK clock       */
/*   COREPLL_PHI0 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_PHI0 clock         */
/*   COREPLL_DFS0 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS0 clock         */
/*   COREPLL_DFS1 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS1 clock         */
/*   COREPLL_DFS2 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS2 clock         */
/*   COREPLL_DFS3 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS3 clock         */
/*   COREPLL_DFS4 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS4 clock         */
/*   COREPLL_DFS5 clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   COREPLL_DFS5 clock         */
/*   PERIPHPLL_PHI0 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI0 clock       */
/*   PERIPHPLL_PHI1 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI1 clock       */
/*   PERIPHPLL_PHI2 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI2 clock       */
/*   PERIPHPLL_PHI3 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI3 clock       */
/*   PERIPHPLL_PHI4 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI4 clock       */
/*   PERIPHPLL_PHI5 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI5 clock       */
/*   PERIPHPLL_PHI6 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_PHI6 clock       */
/*   PERIPHPLL_DFS0 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS0 clock       */
/*   PERIPHPLL_DFS1 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS1 clock       */
/*   PERIPHPLL_DFS2 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS2 clock       */
/*   PERIPHPLL_DFS3 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS3 clock       */
/*   PERIPHPLL_DFS4 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS4 clock       */
/*   PERIPHPLL_DFS5 clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPHPLL_DFS5 clock       */
/*   DDRPLL_PHI0 clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DDRPLL_PHI0 clock          */
/*   LFAST0_PLL_PH0_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LFAST0_PLL_PH0_CLK clock   */
/*   LFAST1_PLL_PH0_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LFAST0_PLL_PH0_CLK clock   */
/*   eth_rgmii_ref clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   eth_rgmii_ref clock        */
/*   tmr_1588_ref clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   tmr_1588_ref clock           */
/*   eth0_ext_rx clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   eth0_ext_rx clock          */
/*   eth0_ext_tx clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   eth0_ext_tx clock          */
/*   eth1_ext_rx clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   eth1_ext_rx clock          */
/*   eth1_ext_tx clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   eth1_ext_tx clock          */
/*   lfast0_ext_ref clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   lfast0_ext_ref clock       */
/*   lfast1_ext_ref clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   lfast1_ext_ref clock       */
/*   DDR_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DDR_CLK clock              */
/*   P0_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_SYS_CLK clock           */
/*   P1_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_SYS_CLK clock           */
/*   P1_SYS_DIV2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_SYS_DIV2_CLK clock      */
/*   P1_SYS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_SYS_DIV4_CLK clock      */
/*   P2_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_SYS_CLK clock           */
/*   CORE_M33_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CORE_M33_CLK clock         */
/*   P2_SYS_DIV2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_SYS_DIV2_CLK clock      */
/*   P2_SYS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_SYS_DIV4_CLK clock      */
/*   P3_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_CLK clock           */
/*   CE_SYS_DIV2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_SYS_DIV2_CLK clock      */
/*   CE_SYS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_SYS_DIV4_CLK clock      */
/*   P3_SYS_DIV2_NOC_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_DIV2_NOC_CLK clock  */
/*   P3_SYS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_DIV4_CLK clock      */
/*   P4_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_SYS_CLK clock           */
/*   P4_SYS_DIV2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_SYS_DIV2_CLK clock      */
/*   HSE_SYS_DIV2_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   HSE_SYS_DIV2_CLK clock     */
/*   P5_SYS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_SYS_CLK clock           */
/*   P5_SYS_DIV2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_SYS_DIV2_CLK clock      */
/*   P5_SYS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_SYS_DIV4_CLK clock      */
/*   P2_MATH_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_MATH_CLK clock          */
/*   P2_MATH_DIV3_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_MATH_DIV3_CLK clock     */
/*   GLB_LBIST_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   GLB_LBIST_CLK clock        */
/*   RTU0_CORE_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_CLK clock        */
/*   RTU0_CORE_DIV2_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_DIV2_CLK clock   */
/*   RTU1_CORE_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_CLK clock        */
/*   RTU1_CORE_DIV2_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_DIV2_CLK clock   */
/*   P0_PSI5_S_UTIL_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_UTIL_CLK clock   */
/*   P4_PSI5_S_UTIL_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_UTIL_CLK clock   */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
/*   SYSTEM_DRUN_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_DRUN_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
/*   SYSTEM_RUN0_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_RUN0_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
/*   SYSTEM_SAFE_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_SAFE_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
/*   SYSTEM_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
/*   SYSTEM_DIV2_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_DIV2_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
/*   SYSTEM_DIV4_MON1_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_DIV4_MON1_CLK clock   */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
/*   SYSTEM_DIV4_MON2_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SYSTEM_DIV4_MON2_CLK clock   */
#endif
/*   THE_LAST_PRODUCER_CLK      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ADC1_CLK clock             */
/*   CE_EDMA_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_EDMA_CLK clock          */
/*   CE_PIT0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT0_CLK clock          */
/*   CE_PIT1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT1_CLK clock          */
/*   CE_PIT2_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT2_CLK clock          */
/*   CE_PIT3_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT3_CLK clock          */
/*   CE_PIT4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT4_CLK clock          */
/*   CE_PIT5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CE_PIT5_CLK clock          */
/*   CLKOUT0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CLKOUT0_CLK clock          */
/*   CLKOUT1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CLKOUT1_CLK clock          */
/*   CLKOUT3_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CLKOUT3_CLK clock          */
/*   CLKOUT4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CLKOUT4_CLK clock          */
/*   CLKOUT5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CLKOUT5_CLK clock          */
/*   CTU_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CTU_CLK clock              */
/*   DMACRC0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMACRC0_CLK clock          */
/*   DMACRC1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMACRC1_CLK clock          */
/*   DMACRC4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMACRC4_CLK clock          */
/*   DMACRC5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMACRC5_CLK clock          */
/*   DMAMUX0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMAMUX1_CLK clock          */
/*   DMAMUX4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMAMUX4_CLK clock          */
/*   DMAMUX5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   DMAMUX5_CLK clock          */
/*   EDMA0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   EDMA0_CLK clock            */
/*   EDMA1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   EDMA1_CLK clock            */
/*   EDMA3_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   EDMA3_CLK clock            */
/*   EDMA4_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   EDMA4_CLK clock            */
/*   EDMA5_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   EDMA5_CLK clock            */
/*   ETH0_TX_MII_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_TX_MII_CLK clock      */
/*   ENET0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ENET0_CLK clock            */
/*   P3_CAN_PE_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_CAN_PE_CLK clock        */
/*   FLEXCAN0_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN2_CLK clock         */
/*   FLEXCAN3_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN3_CLK clock         */
/*   FLEXCAN4_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN4_CLK clock         */
/*   FLEXCAN5_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN5_CLK clock         */
/*   FLEXCAN6_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN6_CLK clock         */
/*   FLEXCAN7_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN7_CLK clock         */
/*   FLEXCAN8_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN8_CLK clock         */
/*   FLEXCAN9_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN9_CLK clock         */
/*   FLEXCAN10_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN10_CLK clock        */
/*   FLEXCAN11_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN11_CLK clock        */
/*   FLEXCAN12_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN12_CLK clock        */
/*   FLEXCAN13_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN13_CLK clock        */
/*   FLEXCAN14_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN14_CLK clock        */
/*   FLEXCAN15_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN15_CLK clock        */
/*   FLEXCAN16_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN16_CLK clock        */
/*   FLEXCAN17_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN17_CLK clock        */
/*   FLEXCAN18_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN18_CLK clock        */
/*   FLEXCAN19_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN19_CLK clock        */
/*   FLEXCAN20_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN20_CLK clock        */
/*   FLEXCAN21_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN21_CLK clock        */
/*   FLEXCAN22_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN22_CLK clock        */
/*   FLEXCAN23_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FLEXCAN23_CLK clock        */
/*   P0_FR_PE_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_FR_PE_CLK clock         */
/*   FRAY0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FRAY0_CLK clock            */
/*   FRAY1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   FRAY1_CLK clock            */
/*   GTM_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   GTM_CLK clock              */
/*   IIIC0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   IIIC0_CLK clock            */
/*   IIIC1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   IIIC1_CLK clock            */
/*   IIIC2_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   IIIC2_CLK clock            */
/*   P0_LIN_BAUD_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_LIN_BAUD_CLK clock      */
/*   LIN0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN0_CLK clock             */
/*   LIN1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN1_CLK clock             */
/*   LIN2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN2_CLK clock             */
/*   P1_LIN_BAUD_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_LIN_BAUD_CLK clock      */
/*   LIN3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN3_CLK clock             */
/*   LIN4_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN4_CLK clock             */
/*   LIN5_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN5_CLK clock             */
/*   P4_LIN_BAUD_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_LIN_BAUD_CLK clock      */
/*   LIN6_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN6_CLK clock             */
/*   LIN7_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN7_CLK clock             */
/*   LIN8_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN8_CLK clock             */
/*   P5_LIN_BAUD_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_LIN_BAUD_CLK clock      */
/*   LIN9_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN9_CLK clock             */
/*   LIN10_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN10_CLK clock            */
/*   LIN11_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   LIN11_CLK clock            */
/*   MSCDSPI_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   MSCDSPI_CLK clock          */
/*   MSCLIN_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   MSCLIN_CLK clock           */
/*   NANO_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   NANO_CLK clock             */
/*   P0_CLKOUT_SRC_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_CLKOUT_SRC_CLK clock    */
/*   P0_CTU_PER_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_CTU_PER_CLK clock       */
/*   P0_DSPI_MSC_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_DSPI_MSC_CLK clock      */
/*   P0_EMIOS_LCU_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_EMIOS_LCU_CLK clock     */
/*   P0_GTM_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_GTM_CLK clock           */
/*   P0_GTM_NOC_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_GTM_NOC_CLK clock       */
/*   P0_GTM_TS_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_GTM_TS_CLK clock        */
/*   P0_LIN_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_LIN_CLK clock           */
/*   P0_NANO_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_NANO_CLK clock          */
/*   P0_PSI5_125K_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_125K_CLK clock     */
/*   P0_PSI5_189K_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_189K_CLK clock     */
/*   P0_PSI5_S_BAUD_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_BAUD_CLK clock   */
/*   P0_PSI5_S_CORE_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_CORE_CLK clock   */
/*   P0_PSI5_S_TRIG0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_TRIG0_CLK clock  */
/*   P0_PSI5_S_TRIG1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_TRIG1_CLK clock  */
/*   P0_PSI5_S_TRIG2_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_TRIG2_CLK clock  */
/*   P0_PSI5_S_TRIG3_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_TRIG3_CLK clock  */
/*   P0_PSI5_S_UART_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_UART_CLK clock   */
/*   P0_PSI5_S_WDOG0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_WDOG0_CLK clock  */
/*   P0_PSI5_S_WDOG1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_WDOG1_CLK clock  */
/*   P0_PSI5_S_WDOG2_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_WDOG2_CLK clock  */
/*   P0_PSI5_S_WDOG3_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_S_WDOG3_CLK clock  */
/*   P0_REG_INTF_2X_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_REG_INTF_2X_CLK clock   */
/*   P0_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_REG_INTF_CLK clock      */
/*   P1_CLKOUT_SRC_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_CLKOUT_SRC_CLK clock    */
/*   P1_DSPI60_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_DSPI60_CLK clock        */
/*   ETH_TS_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH_TS_CLK clock           */
/*   ETH_TS_DIV4_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH_TS_DIV4_CLK clock      */
/*   ETH0_REF_RMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_REF_RMII_CLK clock    */
/*   ETH0_RX_MII_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_RX_MII_CLK clock      */
/*   ETH0_RX_RGMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_RX_RGMII_CLK clock    */
/*   ETH0_TX_RGMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_TX_RGMII_CLK clock    */
/*   ETH0_PS_TX_CLK             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH0_PS_TX_CLK     */
/*   ETH1_REF_RMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_REF_RMII_CLK clock    */
/*   ETH1_RX_MII_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_RX_MII_CLK clock      */
/*   ETH1_RX_RGMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_RX_RGMII_CLK clock    */
/*   ETH1_TX_MII_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_TX_MII_CLK clock      */
/*   ETH1_TX_RGMII_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_TX_RGMII_CLK clock    */
/*   ETH1_PS_TX_CLK             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   ETH1_PS_TX_CLK     */
/*   P1_LFAST0_REF_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_LFAST0_REF_CLK clock    */
/*   P1_LFAST1_REF_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_LFAST1_REF_CLK clock    */
/*   P1_NETC_AXI_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_NETC_AXI_CLK clock      */
/*   P1_LIN_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_LIN_CLK clock           */
/*   P1_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_REG_INTF_CLK clock      */
/*   P2_DBG_ATB_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_DBG_ATB_CLK clock       */
/*   P2_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P2_REG_INTF_CLK clock      */
/*   P3_AES_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_AES_CLK clock           */
/*   P3_CLKOUT_SRC_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_CLKOUT_SRC_CLK clock    */
/*   P3_DBG_TS_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_DBG_TS_CLK clock        */
/*   P3_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_REG_INTF_CLK clock      */
/*   P3_SYS_MON1_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_MON1_CLK clock      */
/*   P3_SYS_MON2_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_MON2_CLK clock      */
/*   P3_SYS_MON3_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P3_SYS_MON3_CLK clock      */
/*   P4_CLKOUT_SRC_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_CLKOUT_SRC_CLK clock    */
/*   P4_DSPI60_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_DSPI60_CLK clock        */
/*   P4_EMIOS_LCU_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_EMIOS_LCU_CLK clock     */
/*   P4_LIN_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_LIN_CLK clock           */
/*   P4_PSI5_125K_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_125K_CLK clock     */
/*   P4_PSI5_189K_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_189K_CLK clock     */
/*   P4_PSI5_S_BAUD_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_BAUD_CLK clock   */
/*   P4_PSI5_S_CORE_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_CORE_CLK clock   */
/*   P4_PSI5_S_TRIG0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_TRIG0_CLK clock  */
/*   P4_PSI5_S_TRIG1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_TRIG1_CLK clock  */
/*   P4_PSI5_S_TRIG2_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_TRIG2_CLK clock  */
/*   P4_PSI5_S_TRIG3_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_TRIG3_CLK clock  */
/*   P4_PSI5_S_UART_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_UART_CLK clock   */
/*   P4_PSI5_S_WDOG0_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_WDOG0_CLK clock  */
/*   P4_PSI5_S_WDOG1_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_WDOG1_CLK clock  */
/*   P4_PSI5_S_WDOG2_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_WDOG2_CLK clock  */
/*   P4_PSI5_S_WDOG3_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_S_WDOG3_CLK clock  */
/*   P4_QSPI0_2X_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_QSPI0_2X_CLK clock      */
/*   P4_QSPI0_1X_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_QSPI0_1X_CLK clock      */
/*   P4_QSPI1_2X_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_QSPI1_2X_CLK clock      */
/*   P4_QSPI1_1X_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_QSPI1_1X_CLK clock      */
/*   P4_REG_INTF_2X_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_REG_INTF_2X_CLK clock   */
/*   P4_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_REG_INTF_CLK clock      */
/*   P4_SDHC_IP_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_SDHC_IP_CLK clock       */
/*   P4_SDHC_IP_DIV2_CLK clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_SDHC_IP_DIV2_CLK clock  */
/*   P5_DIPORT_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_DIPORT_CLK clock        */
/*   P5_AE_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_AE_CLK clock            */
/*   P5_CANXL_PE_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_CANXL_PE_CLK clock      */
/*   P5_CANXL_CHI_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_CANXL_CHI_CLK clock     */
/*   P5_CLKOUT_SRC_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_CLKOUT_SRC_CLK clock    */
/*   P5_LIN_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_LIN_CLK clock           */
/*   P5_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_REG_INTF_CLK clock      */
/*   P6_REG_INTF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P6_REG_INTF_CLK clock      */
/*   PIT0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PIT1_CLK clock             */
/*   PIT4_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PIT4_CLK clock             */
/*   PIT5_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PIT5_CLK clock             */
/*   P0_PSI5_1US_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_PSI5_1US_CLK clock      */
/*   PSI5_0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PSI5_0_CLK clock           */
/*   P4_PSI5_1US_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_PSI5_1US_CLK clock      */
/*   PSI5_1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PSI5_1_CLK clock           */
/*   PSI5S_0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PSI5S_0_CLK clock          */
/*   PSI5S_1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PSI5S_1_CLK clock          */
/*   QSPI0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   QSPI0_CLK clock            */
/*   QSPI1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   QSPI1_CLK clock            */
/*   RTU0_CORE_MON1_CLK         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_MON1_CLK         */
/*   RTU0_CORE_MON2_CLK         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_MON2_CLK         */
/*   RTU0_CORE_DIV2_MON1_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_DIV2_MON1_CLK    */
/*   RTU0_CORE_DIV2_MON2_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_DIV2_MON2_CLK    */
/*   RTU0_CORE_DIV2_MON3_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_CORE_DIV2_MON3_CLK    */
/*   RTU0_REG_INTF_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU0_REG_INTF_CLK clock    */
/*   RTU1_CORE_MON1_CLK         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_MON1_CLK         */
/*   RTU1_CORE_MON2_CLK         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_MON2_CLK         */
/*   RTU1_CORE_DIV2_MON1_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_DIV2_MON1_CLK    */
/*   RTU1_CORE_DIV2_MON2_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_DIV2_MON2_CLK    */
/*   RTU1_CORE_DIV2_MON3_CLK    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_CORE_DIV2_MON3_CLK    */
/*   RTU1_REG_INTF_CLK clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RTU1_REG_INTF_CLK clock    */
/*   P4_SDHC_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_SDHC_CLK clock          */
/*   RXLUT clock                */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   RXLUT clock                */
/*   SDHC0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SDHC0_CLK clock            */
/*   SINC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SINC_CLK clock             */
/*   SIPI0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIPI0_CLK clock            */
/*   SIPI1_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIPI1_CLK clock            */
/*   SIUL2_0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIUL2_0_CLK clock          */
/*   SIUL2_1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIUL2_1_CLK clock          */
/*   SIUL2_4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIUL2_4_CLK clock          */
/*   SIUL2_5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SIUL2_5_CLK clock          */
/*   P0_DSPI_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P0_DSPI_CLK clock          */
/*   SPI0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI0_CLK clock             */
/*   SPI1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI1_CLK clock             */
/*   P1_DSPI_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P1_DSPI_CLK clock          */
/*   SPI2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI2_CLK clock             */
/*   SPI3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI3_CLK clock             */
/*   SPI4_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI4_CLK clock             */
/*   P4_DSPI_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P4_DSPI_CLK clock          */
/*   SPI5_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI5_CLK clock             */
/*   SPI6_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI6_CLK clock             */
/*   SPI7_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI7_CLK clock             */
/*   P5_DSPI_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   P5_DSPI_CLK clock          */
/*   SPI8_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI8_CLK clock             */
/*   SPI9_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SPI9_CLK clock             */
/*   SRX0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SRX0_CLK clock             */
/*   SRX1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   SRX1_CLK clock             */
/*   CORE_PLL_REFCLKOUT clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CORE_PLL_REFCLKOUT clock   */
/*   CORE_PLL_FBCLKOUT clock    */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   CORE_PLL_FBCLKOUT clock    */
/*   PERIPH_PLL_REFCLKOUT clock */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPH_PLL_REFCLKOUT clock */
/*   PERIPH_PLL_FBCLKOUT clock  */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,    /*   PERIPH_PLL_FBCLKOUT clock  */
};
    #endif /* CLOCK_IP_DEV_ERROR_DETECT == STD_ON */
#endif /* CLOCK_IP_DEV_ERROR_DETECT */
/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_32
#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

Clock_Ip_CgmMuxType* const Clock_Ip_apxCgm[CLOCK_IP_MC_CGM_INSTANCES_COUNT][CLOCK_IP_MC_CGM_MUXS_COUNT] =
{
    {
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_3_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_4_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_5_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_6_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_7_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_8_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_9_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_0->MUX_10_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_3_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_4_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_5_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_6_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_7_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_8_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_9_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_10_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_11_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_12_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_13_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_1->MUX_14_CSC),
    },


    {
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_2->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_2->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_2->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_2->MUX_3_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_3->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_3->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_3->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_3->MUX_3_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_3->MUX_4_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {   (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_3_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_4_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_5_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_6_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_7_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_8_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_9_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_10_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_4->MUX_11_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {   (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_1_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_2_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_3_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_4_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_5->MUX_5_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {   (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_6->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&IP_MC_CGM_6->MUX_1_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {   (Clock_Ip_CgmMuxType*)(&CLOCK_IP_RTU0__MC_CGM->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&CLOCK_IP_RTU0__MC_CGM->MUX_1_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },


    {   (Clock_Ip_CgmMuxType*)(&CLOCK_IP_RTU1__MC_CGM->MUX_0_CSC),
        (Clock_Ip_CgmMuxType*)(&CLOCK_IP_RTU1__MC_CGM->MUX_1_CSC),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },

  /* No mux is implemented in CGM_AE */
    {   NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },

};
volatile Clock_Ip_CgmPcfsType* const Clock_Ip_apxCgmPcfs[CLOCK_IP_MC_CGM_INSTANCES_COUNT] =
{
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_0->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_1->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_2->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_3->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_4->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_5->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_6->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(CLOCK_IP_RTU0__MC_CGM->PCFS_SDUR)),
    (volatile Clock_Ip_CgmPcfsType*)(&(CLOCK_IP_RTU1__MC_CGM->PCFS_SDUR)),
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    (volatile Clock_Ip_CgmPcfsType*)(&(IP_MC_CGM_AE->PCS_SDUR)),
#else
    NULL_PTR,
#endif
};

volatile uint32* const Clock_Ip_apxGprClkout[CLOCK_IP_GPR_INSTANCES_COUNT][CLOCK_IP_CLKOUTS_COUNT] =
{
    /* GPR0 instance */
    {
        (volatile uint32*)(&IP_GPR0->CLKOUT0SEL),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },

    /* GPR1 instance */
    {
        NULL_PTR,
        (volatile uint32*)(&IP_GPR1->CLKOUT1SEL),
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },

    /* GPR2 instance */
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
    },

    /* GPR3 instance */
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        (volatile uint32*)(&IP_GPR3->CLKOUT4SEL),
    },

    /* GPR4 instance */
    {
        NULL_PTR,
        NULL_PTR,
        (volatile uint32*)(&IP_GPR4->CLKOUT2SEL),
        NULL_PTR,
        NULL_PTR,

    },

    /* GPR5 instance */
    {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR,
        (volatile uint32*)(&IP_GPR5->CLKOUT3SEL),
        NULL_PTR,

    },
};

#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
Clock_Ip_SystemClockType* const Clock_Ip_apxSystemClock = (Clock_Ip_SystemClockType*)(&(IP_MC_ME_AE->SAFE_MC));
#endif

Clock_Ip_ExtOSCType* const Clock_Ip_apxXosc[CLOCK_IP_XOSC_INSTANCES_ARRAY_SIZE] = {(Clock_Ip_ExtOSCType*)IP_FXOSC};
Clock_Ip_PllType const Clock_Ip_apxPll[CLOCK_IP_PLL_INSTANCES_ARRAY_SIZE] = {
    {
        IP_CORE_PLL,
        CLOCK_IP_COREPLL_DIVIDER_COUNT,
    },
    {
        IP_PERIPH_PLL,
        CLOCK_IP_PERIPHPLL_DIVIDER_COUNT,
    },
    {
        IP_DDR_PLL,
        CLOCK_IP_DDRPLL_DIVIDER_COUNT,
    }
};

Clock_Ip_LfastPllType const Clock_Ip_apxLfastPll[CLOCK_IP_LFASTPLL_INSTANCES_ARRAY_SIZE] =
{
    {
        IP_LFAST_0,
    },
    {
        IP_LFAST_1,
    },
};

DFS_Type* const Clock_Ip_apxDfs[CLOCK_IP_DFS_INSTANCES_ARRAY_SIZE] = {
    IP_CORE_DFS,
    IP_PERIPH_DFS,
};
Clock_Ip_ClockMonitorType* const Clock_Ip_apxCmu[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
    (Clock_Ip_ClockMonitorType*)IP_SMU__CMU_FC_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_0_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_1_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2A_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2B_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2C_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_3_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_4_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_5_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_6_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_0_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_1_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_2_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_0_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_1_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_2_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_3_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_4_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_0_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_1_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_2_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_3_BASE,
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_4_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_DEBUG_1_BASE,
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_DEBUG_2_BASE,
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_1_BASE,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_2_BASE,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_3_BASE,
#endif
};
Clock_Ip_NameType const Clock_Ip_aeCmuNames[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
    P2_SYS_CLK,
    P0_REG_INTF_CLK,
    P1_REG_INTF_CLK,
    FIRC_CLK,
    FXOSC_CLK,
    P2_MATH_CLK,
    P3_SYS_MON1_CLK,
    P4_REG_INTF_CLK,
    P5_REG_INTF_CLK,
    DDR_CLK,
    P3_SYS_MON2_CLK,
    P3_SYS_MON3_CLK,
    CE_SYS_DIV2_CLK,
    RTU0_CORE_MON1_CLK,
    RTU0_CORE_DIV2_MON1_CLK,
    RTU0_CORE_DIV2_MON2_CLK,
    RTU0_CORE_MON2_CLK,
    RTU0_CORE_DIV2_MON3_CLK,
    RTU1_CORE_MON1_CLK,
    RTU1_CORE_DIV2_MON1_CLK,
    RTU1_CORE_DIV2_MON2_CLK,
    RTU1_CORE_MON2_CLK,
    RTU1_CORE_DIV2_MON3_CLK,
    P0_CLKOUT_SRC_CLK,
    P1_CLKOUT_SRC_CLK,
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    SYSTEM_DIV2_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    SYSTEM_DIV4_MON1_CLK,
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    SYSTEM_DIV4_MON2_CLK,
#endif
};

Clock_Ip_CmuInfoType const Clock_Ip_axCmuInfo[CLOCK_IP_CMU_INFO_SIZE] =  {

/* CLOCK_IP_SMU_CMU_FC_INSTANCE */
{
    P2_SYS_CLK,                                      /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P2_SYS_DIV4_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_SMU__CMU_FC,      /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_0_INSTANCE */
{
    P0_REG_INTF_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P0_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_0,         /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_1_INSTANCE */
{
    P1_REG_INTF_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P1_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_1,         /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_2A_INSTANCE */
{
    FIRC_CLK,                                        /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P2_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2A,        /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_2B_INSTANCE */
{
    FXOSC_CLK,                                       /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                        /* Name of the reference clock */
    P2_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2B,        /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_2C_INSTANCE */
{
    P2_MATH_CLK,                                     /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P2_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_2C,        /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_3_INSTANCE */
{
    P3_SYS_MON1_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P3_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_3,         /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_4_INSTANCE */
{
    P4_REG_INTF_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P4_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_4,         /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_5_INSTANCE */
{
    P5_REG_INTF_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P5_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_5,         /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_6_INSTANCE */
{
    DDR_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P6_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_6,         /* Cmu instance */
},
/* CLOCK_IP_CE_CMU_FC_0_INSTANCE */
{
    P3_SYS_MON2_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    CE_SYS_DIV4_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_0,      /* Cmu instance */
},
/* CLOCK_IP_CE_CMU_FC_1_INSTANCE */
{
    P3_SYS_MON3_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    CE_SYS_DIV4_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_1,      /* Cmu instance */
},
/* CLOCK_IP_CE_CMU_FC_2_INSTANCE */
{
    CE_SYS_DIV2_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    CE_SYS_DIV4_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CE_CMU_FC_2,      /* Cmu instance */
},
/* CLOCK_IP_RTU0_CMU_FC_0_INSTANCE */
{
    RTU0_CORE_MON1_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU0_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_0,   /* Cmu instance */
},
/* CLOCK_IP_RTU0_CMU_FC_1_INSTANCE */
{
    RTU0_CORE_DIV2_MON1_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU0_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_1,   /* Cmu instance */
},
/* CLOCK_IP_RTU0_CMU_FC_2_INSTANCE */
{
    RTU0_CORE_DIV2_MON2_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU0_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_2,   /* Cmu instance */
},
/* CLOCK_IP_RTU0_CMU_FC_3_INSTANCE */
{
    RTU0_CORE_MON2_CLK,                              /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU0_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_3,   /* Cmu instance */
},
/* CLOCK_IP_RTU0_CMU_FC_4_INSTANCE */
{
    RTU0_CORE_DIV2_MON3_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU0_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU0__CMU_FC_4,   /* Cmu instance */
},
/* CLOCK_IP_RTU1_CMU_FC_0_INSTANCE */
{
    RTU1_CORE_MON1_CLK,                              /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU1_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_0,   /* Cmu instance */
},
/* CLOCK_IP_RTU1_CMU_FC_1_INSTANCE */
{
    RTU1_CORE_DIV2_MON1_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU1_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_1,   /* Cmu instance */
},
/* CLOCK_IP_RTU1_CMU_FC_2_INSTANCE */
{
    RTU1_CORE_DIV2_MON2_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU1_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_2,   /* Cmu instance */
},
/* CLOCK_IP_RTU1_CMU_FC_3_INSTANCE */
{
    RTU1_CORE_MON2_CLK,                              /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU1_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_3,   /* Cmu instance */
},
/* CLOCK_IP_RTU1_CMU_FC_4_INSTANCE */
{
    RTU1_CORE_DIV2_MON3_CLK,                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    RTU1_REG_INTF_CLK,                               /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_RTU1__CMU_FC_4,   /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_DEBUG_1_INSTANCE */
{
    P0_CLKOUT_SRC_CLK,                               /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P0_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_DEBUG_1,   /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_DEBUG_2_INSTANCE */
{
    P1_CLKOUT_SRC_CLK,                               /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    P1_REG_INTF_CLK,                                 /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_DEBUG_2,   /* Cmu instance */
},

#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
/* CLOCK_IP_CMU_FC_AE_1_INSTANCE */
{
    SYSTEM_DIV2_CLK,                                 /* Name of the clock that supports cmu (clock monitor) */
    FIRC_AE_CLK,                                       /* Name of the reference clock */
    SYSTEM_DIV2_CLK,                                    /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_1,      /* Cmu instance */
},
#else
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,   /* Cmu instance */
},
#endif

#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
/* CLOCK_IP_CMU_FC_AE_2_INSTANCE */
{
    SYSTEM_DIV4_MON1_CLK,                            /* Name of the clock that supports cmu (clock monitor) */
    FIRC_AE_CLK,                                       /* Name of the reference clock */
    SYSTEM_DIV2_CLK,                                    /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_2,      /* Cmu instance */
},
#else
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,   /* Cmu instance */
},
#endif

#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
/* CLOCK_IP_CMU_FC_AE_3_INSTANCE */
{
    SYSTEM_DIV4_MON2_CLK,                            /* Name of the clock that supports cmu (clock monitor) */
    FIRC_AE_CLK,                                       /* Name of the reference clock */
    SYSTEM_DIV2_CLK,                                    /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_FC_AE_3,      /* Cmu instance */
},
#else
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,   /* Cmu instance */
},
#endif
};


Clock_Ip_GprClockControlEnable_Type* const Clock_Ip_apxGprClockControlEnable[CLOCK_IP_PERIPHERAL_GROUPS_COUNT] =
{
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR0_PCTL_BASE),
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR1_PCTL_BASE),
    NULL_PTR,
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR3_PCTL_BASE),
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR4_PCTL_BASE),
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR5_PCTL_BASE),
    (Clock_Ip_GprClockControlEnable_Type*)(IP_GPR6_PCTL_BASE),
};

const Clock_Ip_ClockNameSourceType Clock_Ip_aeSourceTypeClockName[CLOCK_IP_PRODUCERS_NO] = {
    UKNOWN_TYPE,                               /*!< CLOCK_IS_OFF                            */
    IRCOSC_TYPE,                               /*!< FIRC_CLK                                */
    XOSC_TYPE,                                 /*!< FXOSC_CLK                               */
    IRCOSC_TYPE,                               /*!< SIRC_CLK                                */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    IRCOSC_TYPE,                               /*!< FIRC_AE_CLK                             */
#endif
    PLL_TYPE,                                  /*!< COREPLL_CLK                             */
    PLL_TYPE,                                  /*!< PERIPHPLL_CLK                           */
    PLL_TYPE,                                  /*!< DDRPLL_CLK                              */
    PLL_TYPE,                                  /*!< LFAST0_PLL_CLK                          */
    PLL_TYPE,                                  /*!< LFAST1_PLL_CLK                          */
    PLL_TYPE,                                  /*!< CORE_PLL_PHI0_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS0_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS1_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS2_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS3_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS4_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS5_CLK                       */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI0_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI1_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI2_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI3_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI4_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI5_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI6_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS0_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS1_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS2_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS3_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS4_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS5_CLK                     */
    PLL_TYPE,                                  /*!< DDR_PLL_PHI0_CLK                        */
    UKNOWN_TYPE,                               /*!< LFAST0_PLL_PH0_CLK                      */
    UKNOWN_TYPE,                               /*!< LFAST1_PLL_PH0_CLK                      */
    EXT_CLK_TYPE,                              /*!< ENET_EXT_REF_CLK                        */
    EXT_CLK_TYPE,                              /*!< ENET_EXT_TS_CLK                         */
    EXT_CLK_TYPE,                              /*!< ENET0_EXT_RX_CLK                        */
    EXT_CLK_TYPE,                              /*!< ENET0_EXT_TX_CLK                        */
    EXT_CLK_TYPE,                              /*!< ENET1_EXT_RX_CLK                        */
    EXT_CLK_TYPE,                              /*!< ENET1_EXT_TX_CLK                        */
    EXT_CLK_TYPE,                              /*!< LFAST0_EXT_TX_CLK                       */
    EXT_CLK_TYPE,                              /*!< LFAST1_EXT_TX_CLK                       */
    UKNOWN_TYPE,                               /*!< DDR_CLK                                 */
    UKNOWN_TYPE,                               /*!< P0_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< P1_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< P1_SYS_DIV2_CLK                         */
    UKNOWN_TYPE,                               /*!< P1_SYS_DIV4_CLK                         */
    UKNOWN_TYPE,                               /*!< P2_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< CORE_M33_CLK                            */
    UKNOWN_TYPE,                               /*!< P2_SYS_DIV2_CLK                         */
    UKNOWN_TYPE,                               /*!< P2_SYS_DIV4_CLK                         */
    UKNOWN_TYPE,                               /*!< P3_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< CE_SYS_DIV2_CLK                         */
    UKNOWN_TYPE,                               /*!< CE_SYS_DIV4_CLK                         */
    UKNOWN_TYPE,                               /*!< P3_SYS_DIV2_NOC_CLK                     */
    UKNOWN_TYPE,                               /*!< P3_SYS_DIV4_CLK                         */
    UKNOWN_TYPE,                               /*!< P4_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< P4_SYS_DIV2_CLK                         */
    UKNOWN_TYPE,                               /*!< HSE_SYS_DIV2_CLK                        */
    UKNOWN_TYPE,                               /*!< P5_SYS_CLK                              */
    UKNOWN_TYPE,                               /*!< P5_SYS_DIV2_CLK                         */
    UKNOWN_TYPE,                               /*!< P5_SYS_DIV4_CLK                         */
    UKNOWN_TYPE,                               /*!< P2_MATH_CLK                             */
    UKNOWN_TYPE,                               /*!< P2_MATH_DIV3_CLK                        */
    UKNOWN_TYPE,                               /*!< GLB_LBIST_CLK                           */
    UKNOWN_TYPE,                               /*!< RTU0_CORE_CLK                           */
    UKNOWN_TYPE,                               /*!< RTU0_CORE_DIV2_CLK                      */
    UKNOWN_TYPE,                               /*!< RTU1_CORE_CLK                           */
    UKNOWN_TYPE,                               /*!< RTU1_CORE_DIV2_CLK                      */
    PLL_TYPE,                                  /*!< P0_PSI5_S_UTIL_CLK                      */
    PLL_TYPE,                                  /*!< P4_PSI5_S_UTIL_CLK                      */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_DRUN_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_RUN0_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_SAFE_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_CLK                              */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_DIV2_CL                          */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_DIV4_MON1_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    UKNOWN_TYPE,                               /*!< SYSTEM_DIV4_MON2_CLK                         */
#endif
};

const Clock_Ip_NameType Clock_Ip_aeHwPllName[CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE] =
{
    COREPLL_CLK,                    /* COREPLL_CLK Clock */
    PERIPHPLL_CLK,                  /* PERIPHPLL_CLK Clock */
    DDRPLL_CLK,                     /* DDRPLL_CLK Clock */
    LFAST0_PLL_CLK,                 /* LFAST0_PLL_CLK Clock */
    LFAST1_PLL_CLK,                 /* LFAST1_PLL_CLK Clock */
};
const Clock_Ip_NameType Clock_Ip_aeHwDfsName[CLOCK_IP_NUMBER_OF_HARDWARE_DFS] =
{
    COREPLL_DFS0_CLK,              /* COREPLL_DFS0_CLK Clock */
    COREPLL_DFS1_CLK,              /* COREPLL_DFS1_CLK Clock */
    COREPLL_DFS2_CLK,              /* COREPLL_DFS2_CLK Clock */
    COREPLL_DFS3_CLK,              /* COREPLL_DFS3_CLK Clock */
    COREPLL_DFS4_CLK,              /* COREPLL_DFS4_CLK Clock */
    COREPLL_DFS5_CLK,              /* COREPLL_DFS5_CLK Clock */
    PERIPHPLL_DFS0_CLK,            /* PERIPHPLL_DFS0_CLK Clock */
    PERIPHPLL_DFS1_CLK,            /* PERIPHPLL_DFS1_CLK Clock */
    PERIPHPLL_DFS2_CLK,            /* PERIPHPLL_DFS2_CLK Clock */
    PERIPHPLL_DFS3_CLK,            /* PERIPHPLL_DFS3_CLK Clock */
    PERIPHPLL_DFS4_CLK,            /* PERIPHPLL_DFS4_CLK Clock */
    PERIPHPLL_DFS5_CLK,            /* PERIPHPLL_DFS5_CLK Clock */

};


const Clock_Ip_ClockExtensionType Clock_Ip_axFeatureExtensions[CLOCK_IP_EXTENSIONS_SIZE] = {
    /* Selector value mask             Selector value shift               Divider value mask                 Divider value shift  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     MC_CGM_MUX_0_DC_0_DIV_MASK,        MC_CGM_MUX_0_DC_0_DIV_SHIFT},      /* CLOCK_IP_DDR_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_SYS_DIV4_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_CORE_M33_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_SYS_DIV4_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P3_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_CE_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_CE_SYS_DIV4_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P3_SYS_DIV2_NOC_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P3_SYS_DIV4_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_HSE_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     MC_CGM_MUX_0_DC_0_DIV_MASK,        MC_CGM_MUX_0_DC_0_DIV_SHIFT},      /* CLOCK_IP_P5_SYS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P5_SYS_DIV2_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,     MC_CGM_MUX_0_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P5_SYS_DIV4_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_MATH_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_MATH_DIV3_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     MC_CGM_MUX_8_DC_0_DIV_MASK,        MC_CGM_MUX_8_DC_0_DIV_SHIFT},      /* CLOCK_IP_GLB_LBIST_EXTENSION */
    {RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT, RTU_MC_CGM_MUX_0_DC_0_DIV_MASK,    RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT},  /* CLOCK_IP_RTU0_CORE_EXTENSION */
    {RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT, 0U,                                0U},                               /* CLOCK_IP_RTU0_CORE_DIV2_EXTENSION */
    {RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT, RTU_MC_CGM_MUX_0_DC_0_DIV_MASK,    RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT},  /* CLOCK_IP_RTU1_CORE_EXTENSION */
    {RTU_MC_CGM_MUX_0_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_0_CSC_SELCTL_SHIFT, 0U,                                0U},                               /* CLOCK_IP_RTU1_CORE_DIV2_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_3_DIV_MASK,        MC_CGM_MUX_2_DC_3_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_UTIL_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_3_DIV_MASK,        MC_CGM_MUX_2_DC_3_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_UTIL_EXTENSION */
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,    MC_CGM_MUX_10_CSC_SELCTL_SHIFT,    MC_CGM_MUX_10_DC_0_DIV_MASK,       MC_CGM_MUX_10_DC_0_DIV_SHIFT},     /* CLOCK_IP_CLKOUT0_EXTENSION */
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,    MC_CGM_MUX_10_CSC_SELCTL_SHIFT,    MC_CGM_MUX_10_DC_0_DIV_MASK,       MC_CGM_MUX_10_DC_0_DIV_SHIFT},     /* CLOCK_IP_CLKOUT1_EXTENSION */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,     MC_CGM_MUX_6_CSC_SELCTL_SHIFT,     MC_CGM_MUX_6_DC_0_DIV_MASK,        MC_CGM_MUX_6_DC_0_DIV_SHIFT},      /* CLOCK_IP_CLKOUT2_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     MC_CGM_MUX_4_DC_0_DIV_MASK,        MC_CGM_MUX_4_DC_0_DIV_SHIFT},      /* CLOCK_IP_CLKOUT3_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     MC_CGM_MUX_4_DC_0_DIV_MASK,        MC_CGM_MUX_4_DC_0_DIV_SHIFT},      /* CLOCK_IP_CLKOUT4_EXTENSION */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,     MC_CGM_MUX_6_CSC_SELCTL_SHIFT,     MC_CGM_MUX_6_DC_0_DIV_MASK,        MC_CGM_MUX_6_DC_0_DIV_SHIFT},      /* P1_ETH0_TX_MII_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_0_DIV_MASK,        MC_CGM_MUX_3_DC_0_DIV_SHIFT},      /* CLOCK_IP_P3_CAN_PE_EXTENSION */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,     MC_CGM_MUX_6_CSC_SELCTL_SHIFT,     MC_CGM_MUX_6_DC_0_DIV_MASK,        MC_CGM_MUX_6_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_FR_PE_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     MC_CGM_MUX_4_DC_0_DIV_MASK,        MC_CGM_MUX_4_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_LIN_BAUD_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     MC_CGM_MUX_4_DC_0_DIV_MASK,        MC_CGM_MUX_4_DC_0_DIV_SHIFT},      /* CLOCK_IP_P1_LIN_BAUD_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     MC_CGM_MUX_8_DC_0_DIV_MASK,        MC_CGM_MUX_8_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_LIN_BAUD_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_0_DIV_MASK,        MC_CGM_MUX_2_DC_0_DIV_SHIFT},      /* CLOCK_IP_P5_LIN_BAUD_EXTENSION */
    {GPR0_CLKOUT0SEL_MUXSEL_MASK,      GPR0_CLKOUT0SEL_MUXSEL_SHIFT,      0U,                                0U},                               /* CLOCK_IP_P0_CLKOUT_SRC_EXTENSION */            
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_0_DIV_MASK,        MC_CGM_MUX_9_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_CTU_PER_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_1_DIV_MASK,        MC_CGM_MUX_7_DC_1_DIV_SHIFT},      /* CLOCK_IP_P0_DSPI_MSC_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_EMIOS_LCU_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_0_DIV_MASK,        MC_CGM_MUX_7_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_GTM_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_GTM_NOC_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_GTM_TS_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_LIN_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_NANO_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_1_DIV_MASK,        MC_CGM_MUX_2_DC_1_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_125K_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_2_DIV_MASK,        MC_CGM_MUX_2_DC_2_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_189K_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_5_DIV_MASK,        MC_CGM_MUX_2_DC_5_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_BAUD_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_PSI5_S_CORE_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_0_DIV_MASK,        MC_CGM_MUX_3_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_TRIG0_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_1_DIV_MASK,        MC_CGM_MUX_3_DC_1_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_TRIG1_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_2_DIV_MASK,        MC_CGM_MUX_3_DC_2_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_TRIG2_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_3_DIV_MASK,        MC_CGM_MUX_3_DC_3_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_TRIG3_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_4_DIV_MASK,        MC_CGM_MUX_2_DC_4_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_UART_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_4_DIV_MASK,        MC_CGM_MUX_3_DC_4_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_WDOG0_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_5_DIV_MASK,        MC_CGM_MUX_3_DC_5_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_WDOG1_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_6_DIV_MASK,        MC_CGM_MUX_3_DC_6_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_WDOG2_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_7_DIV_MASK,        MC_CGM_MUX_3_DC_7_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_S_WDOG3_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_1_DIV_MASK,        MC_CGM_MUX_1_DC_1_DIV_SHIFT},      /* CLOCK_IP_P0_REG_INTF_2X_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_REG_INTF_EXTENSION */
    {GPR1_CLKOUT1SEL_MUXSEL_MASK,      GPR1_CLKOUT1SEL_MUXSEL_SHIFT,      0U,                                0U},                               /* CLOCK_IP_P1_CLKOUT_SRC_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_DSPI60_EXTENSION */
    {MC_CGM_MUX_11_CSC_SELCTL_MASK,    MC_CGM_MUX_11_CSC_SELCTL_SHIFT,    MC_CGM_MUX_11_DC_0_DIV_MASK,       MC_CGM_MUX_11_DC_0_DIV_SHIFT},     /* CLOCK_IP_P1_LFAST0_REF_EXTENSION */
    {MC_CGM_MUX_12_CSC_SELCTL_MASK,    MC_CGM_MUX_12_CSC_SELCTL_SHIFT,    MC_CGM_MUX_11_DC_0_DIV_MASK,       MC_CGM_MUX_12_DC_0_DIV_SHIFT},     /* CLOCK_IP_P1_LFAST1_REF_EXTENSION */
    {MC_CGM_MUX_14_CSC_SELCTL_MASK,    MC_CGM_MUX_14_CSC_SELCTL_SHIFT,    MC_CGM_MUX_14_DC_0_DIV_MASK,       MC_CGM_MUX_14_DC_0_DIV_SHIFT},     /* CLOCK_IP_P1_NETC_AXI_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_LIN_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     MC_CGM_MUX_5_DC_0_DIV_MASK,        MC_CGM_MUX_5_DC_0_DIV_SHIFT},      /* P1_ETH_TS_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     MC_CGM_MUX_5_DC_0_DIV_MASK,        MC_CGM_MUX_5_DC_0_DIV_SHIFT},      /* P1_ETH_TS_DIV4_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_2_DIV_MASK,        MC_CGM_MUX_7_DC_2_DIV_SHIFT},      /* P1_ETH0_REF_RMII_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_0_DIV_MASK,        MC_CGM_MUX_7_DC_0_DIV_SHIFT},      /* P1_ETH0_RX_MII_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_1_DIV_MASK,        MC_CGM_MUX_7_DC_1_DIV_SHIFT},      /* P1_ETH0_RX_RGMII_EXTENSION */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,     MC_CGM_MUX_6_CSC_SELCTL_SHIFT,     MC_CGM_MUX_6_DC_1_DIV_MASK,        MC_CGM_MUX_6_DC_1_DIV_SHIFT},      /* P1_ETH0_TX_RGMII_EXTENSION */
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,     MC_CGM_MUX_6_CSC_SELCTL_SHIFT,     MC_CGM_MUX_6_DC_1_DIV_MASK,        MC_CGM_MUX_6_DC_1_DIV_SHIFT},      /* P1_ETH0_TX_RGMII_LPBK_EXTENION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_2_DIV_MASK,        MC_CGM_MUX_9_DC_2_DIV_SHIFT},      /* P1_ETH1_REF_RMII_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_0_DIV_MASK,        MC_CGM_MUX_9_DC_0_DIV_SHIFT},      /* P1_ETH1_RX_MII_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_1_DIV_MASK,        MC_CGM_MUX_9_DC_1_DIV_SHIFT},      /* P1_ETH1_RX_RGMII_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     MC_CGM_MUX_8_DC_0_DIV_MASK,        MC_CGM_MUX_8_DC_0_DIV_SHIFT},      /* P1_ETH1_TX_MII_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     MC_CGM_MUX_8_DC_1_DIV_MASK,        MC_CGM_MUX_8_DC_1_DIV_SHIFT},      /* P1_ETH1_TX_RGMII_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     MC_CGM_MUX_8_DC_1_DIV_MASK,        MC_CGM_MUX_8_DC_1_DIV_SHIFT},      /* P1_ETH1_TX_RGMII_LPBK_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P1_REG_INTF_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P2_DBG_ATB_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P2_REG_INTF_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_1_DIV_MASK,        MC_CGM_MUX_2_DC_1_DIV_SHIFT},      /* CLOCK_IP_P3_AES_EXTENSION */
    {GPR3_CLKOUT4SEL_MUXSEL_MASK,      GPR3_CLKOUT4SEL_MUXSEL_SHIFT,      0U,                                0U},                               /* CLOCK_IP_P3_CLKOUT_SRC_EXTENSION */        
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_0_DIV_MASK,        MC_CGM_MUX_2_DC_0_DIV_SHIFT},      /* CLOCK_IP_P3_DBG_TS_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P3_REG_INTF_EXTENSION */
    {GPR4_CLKOUT2SEL_MUXSEL_MASK,      GPR4_CLKOUT2SEL_MUXSEL_SHIFT,      0U,                                0U},                               /* CLOCK_IP_P4_CLKOUT_SRC_EXTENSION */    
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_DSPI60_EXTENSION */
    {MC_CGM_MUX_11_CSC_SELCTL_MASK,    MC_CGM_MUX_11_CSC_SELCTL_SHIFT,    0U,                                0U},                               /* CLOCK_IP_P4_EMIOS_LCU_EXTENSION */
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,     MC_CGM_MUX_8_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_LIN_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_1_DIV_MASK,        MC_CGM_MUX_2_DC_1_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_125K_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_2_DIV_MASK,        MC_CGM_MUX_2_DC_2_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_189K_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_5_DIV_MASK,        MC_CGM_MUX_2_DC_5_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_BAUD_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_PSI5_S_CORE_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_0_DIV_MASK,        MC_CGM_MUX_3_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_TRIG0_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_1_DIV_MASK,        MC_CGM_MUX_3_DC_1_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_TRIG1_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_2_DIV_MASK,        MC_CGM_MUX_3_DC_2_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_TRIG2_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_3_DIV_MASK,        MC_CGM_MUX_3_DC_3_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_TRIG3_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_4_DIV_MASK,        MC_CGM_MUX_2_DC_4_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_UART_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_4_DIV_MASK,        MC_CGM_MUX_3_DC_4_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_WDOG0_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_5_DIV_MASK,        MC_CGM_MUX_3_DC_5_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_WDOG1_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_6_DIV_MASK,        MC_CGM_MUX_3_DC_6_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_WDOG2_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     MC_CGM_MUX_3_DC_7_DIV_MASK,        MC_CGM_MUX_3_DC_7_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_S_WDOG3_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     MC_CGM_MUX_7_DC_0_DIV_MASK,        MC_CGM_MUX_7_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_QSPI0_2X_EXTENSION */
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,     MC_CGM_MUX_7_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_QSPI0_1X_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_1_DIV_MASK,        MC_CGM_MUX_9_DC_1_DIV_SHIFT},      /* CLOCK_IP_P4_QSPI1_2X_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_1_DIV_MASK,        MC_CGM_MUX_9_DC_1_DIV_SHIFT},      /* CLOCK_IP_P4_QSPI1_1X_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_1_DIV_MASK,        MC_CGM_MUX_1_DC_1_DIV_SHIFT},      /* CLOCK_IP_P4_REG_INTF_2X_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_REG_INTF_EXTENSION */
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,    MC_CGM_MUX_10_CSC_SELCTL_SHIFT,    0U,                                0U},                               /* CLOCK_IP_P4_SDHC_IP_EXTENSION */
    {MC_CGM_MUX_10_CSC_SELCTL_MASK,    MC_CGM_MUX_10_CSC_SELCTL_SHIFT,    0U,                                0U},                               /* CLOCK_IP_P4_SDHC_IP_DIV2_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     MC_CGM_MUX_5_DC_0_DIV_MASK,        MC_CGM_MUX_5_DC_0_DIV_SHIFT},      /* CLOCK_IP_P5_AE_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     MC_CGM_MUX_5_DC_1_DIV_MASK,        MC_CGM_MUX_5_DC_1_DIV_SHIFT},      /* CLOCK_IP_P5_CANXL_PE_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     MC_CGM_MUX_5_DC_2_DIV_MASK,        MC_CGM_MUX_5_DC_2_DIV_SHIFT},      /* CLOCK_IP_P5_CANXL_CHI_EXTENSION */
    {GPR5_CLKOUT3SEL_MUXSEL_MASK,      GPR5_CLKOUT3SEL_MUXSEL_SHIFT,      0U,                                0U},                               /* CLOCK_IP_P5_CLKOUT_SRC_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P5_LIN_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P5_REG_INTF_EXTENSION */
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,     MC_CGM_MUX_1_CSC_SELCTL_SHIFT,     MC_CGM_MUX_1_DC_0_DIV_MASK,        MC_CGM_MUX_1_DC_0_DIV_SHIFT},      /* CLOCK_IP_P6_REG_INTF_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_0_DIV_MASK,        MC_CGM_MUX_2_DC_0_DIV_SHIFT},      /* CLOCK_IP_P0_PSI5_1US_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     MC_CGM_MUX_2_DC_0_DIV_MASK,        MC_CGM_MUX_2_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_PSI5_1US_EXTENSION */
    {RTU_MC_CGM_MUX_1_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_1_CSC_SELCTL_SHIFT, RTU_MC_CGM_MUX_1_DC_0_DIV_MASK,    RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT},  /* CLOCK_IP_RTU0_REG_INTF_EXTENSION */
    {RTU_MC_CGM_MUX_1_CSC_SELCTL_MASK, RTU_MC_CGM_MUX_1_CSC_SELCTL_SHIFT, RTU_MC_CGM_MUX_1_DC_0_DIV_MASK,    RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT},  /* CLOCK_IP_RTU1_REG_INTF_EXTENSION */
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,     MC_CGM_MUX_9_CSC_SELCTL_SHIFT,     MC_CGM_MUX_9_DC_0_DIV_MASK,        MC_CGM_MUX_9_DC_0_DIV_SHIFT},      /* CLOCK_IP_P4_SDHC_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,     MC_CGM_MUX_5_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P0_DSPI_EXTENSION */
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,     MC_CGM_MUX_2_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P1_DSPI_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,     MC_CGM_MUX_4_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P4_DSPI_EXTENSION */
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,     MC_CGM_MUX_3_CSC_SELCTL_SHIFT,     0U,                                0U},                               /* CLOCK_IP_P5_DSPI_EXTENSION */
};

Clock_Ip_GateInfoType const Clock_Ip_axGateInfo[CLOCK_IP_GATE_INFO_SIZE] =  {
    /* Group index      Gate index */
    {CLOCK_IP_GROUP_6_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P6_GROUP_0_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_13_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_13_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_12_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_12_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_1_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_27_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_27_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_28_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_28_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_29_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_29_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_30_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_30_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_31_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_31_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_32_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_32_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_20_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_20_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_1},     /* CLOCK_IP_P0_GROUP_5_BIT1_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_1},     /* CLOCK_IP_P1_GROUP_1_BIT1_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_1},     /* CLOCK_IP_P4_GROUP_2_BIT1_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_1},     /* CLOCK_IP_P5_GROUP_0_BIT1_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_2},     /* CLOCK_IP_P0_GROUP_5_BIT2_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_2},     /* CLOCK_IP_P1_GROUP_1_BIT2_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_2},     /* CLOCK_IP_P4_GROUP_2_BIT2_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_2},     /* CLOCK_IP_P5_GROUP_0_BIT2_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_5_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_1_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_0_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_2_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_0_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_12_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_12_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_3_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_3_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_4_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_4_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_5_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_6_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_6_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_7_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_7_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_8_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_8_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_9_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_9_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_10_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_10_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_11_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_11_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_12_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_12_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_13_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_13_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_14_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_14_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_15_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_15_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_16_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_16_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_17_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_17_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_18_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_18_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_19_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_19_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_20_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_20_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_21_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_21_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_22_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_22_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_23_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_23_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_24_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_24_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_25_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_25_BIT0_INDEX */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_26_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_26_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_2_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_3_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_3_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_22_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_22_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_4_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_4_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_0_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_11_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_11_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_8_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_8_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_9_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_9_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_10_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_10_BIT0_INDEX */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_5_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_6_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_6_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_7_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_7_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_6_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_6_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_7_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_7_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_8_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_8_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_3_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_3_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_4_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_4_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_5_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_6_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_6_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_11_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_11_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_22_INDEX,      CLOCK_IP_GATE_PCTL_1},     /* CLOCK_IP_P0_GROUP_22_BIT1_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_3},     /* CLOCK_IP_P0_GROUP_5_BIT3_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_3},     /* CLOCK_IP_P1_GROUP_1_BIT3_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_3},     /* CLOCK_IP_P4_GROUP_2_BIT3_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_3},     /* CLOCK_IP_P5_GROUP_0_BIT3_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_19_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_19_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_12_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_12_BIT0_INDEX */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_23_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_23_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_14_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_14_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_0_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_0_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_1_BIT0_INDEX  */
    {CLOCK_IP_GROUP_3_INDEX,     CLOCK_IP_GATE_33_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P3_GROUP_33_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_9_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_9_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_24_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_24_BIT0_INDEX */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_8_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_8_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_9_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_9_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_21_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_21_BIT0_INDEX */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_14_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_14_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_13_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_13_BIT0_INDEX */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_6_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_6_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_1_BIT0_INDEX  */
    {CLOCK_IP_GROUP_0_INDEX,     CLOCK_IP_GATE_7_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P0_GROUP_7_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_2_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_3_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_3_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_4_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_4_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_3_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_3_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_4_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_4_BIT0_INDEX  */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_5_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_5_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_1_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_1_BIT0_INDEX  */
    {CLOCK_IP_GROUP_5_INDEX,     CLOCK_IP_GATE_2_INDEX,       CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P5_GROUP_2_BIT0_INDEX  */
    {CLOCK_IP_GROUP_1_INDEX,     CLOCK_IP_GATE_10_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P1_GROUP_10_BIT0_INDEX */
    {CLOCK_IP_GROUP_4_INDEX,     CLOCK_IP_GATE_10_INDEX,      CLOCK_IP_GATE_PCTL_0},     /* CLOCK_IP_P4_GROUP_10_BIT0_INDEX */
};



/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/




#ifdef __cplusplus
}
#endif

/** @} */

