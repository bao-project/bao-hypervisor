/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Frequency.c
*   @version    2.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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

#if defined(CLOCK_IP_PLATFORM_SPECIFIC)


#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))


/*==================================================================================================
*                                     SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_FREQUENCY_VENDOR_ID_C                      43
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C               0
#define CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_FREQUENCY_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Frequency.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef struct{

    Clock_Ip_NameType Name;
    uint64 Frequency;

}extSignalFreq;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define CLOCK_IP_SELECTOR_SOURCE_NO  64U
#define CLOCK_IP_EXT_SIGNALS_NO      8U
#define CLOCK_IP_DFS_MASK_0_CHANNEL  1U
#define CLOCK_IP_DFS_MASK_1_CHANNEL  2U
#define CLOCK_IP_DFS_MASK_2_CHANNEL  4U
#define CLOCK_IP_DFS_MASK_3_CHANNEL  8U
#define CLOCK_IP_DFS_MASK_4_CHANNEL  16U
#define CLOCK_IP_DFS_MASK_5_CHANNEL  32U
#define CLOCK_IP_MUL_BY_16384        14U
#define CLOCK_IP_MUL_BY_2048         11U
#define CLOCK_IP_MUL_BY_32           5U
#define CLOCK_IP_MUL_BY_16           4U
#define CLOCK_IP_MUL_BY_4            2U
#define CLOCK_IP_MUL_BY_2            1U
#define CLOCK_IP_DISABLED            0U
#define CLOCK_IP_ENABLED             0xFFFFFFFFFFFFFFFFU

#define CLOCK_IP_ETH_RGMII_REF_CLK_INDEX_ENTRY       0U
#define CLOCK_IP_TMR_1588_CLK_INDEX_ENTRY          1U
#define CLOCK_IP_ETH0_EXT_RX_CLK_INDEX_ENTRY         2U
#define CLOCK_IP_ETH0_EXT_TX_CLK_INDEX_ENTRY         3U
#define CLOCK_IP_ETH1_EXT_RX_CLK_INDEX_ENTRY         4U
#define CLOCK_IP_ETH1_EXT_TX_CLK_INDEX_ENTRY         5U
#define CLOCK_IP_LFAST0_EXT_REF_CLK_INDEX_ENTRY      6U
#define CLOCK_IP_LFAST1_EXT_REF_CLK_INDEX_ENTRY      7U


#define CLOCK_IP_CLKOUT_INDEX0                       0U
#define CLOCK_IP_CLKOUT_INDEX1                       1U
#define CLOCK_IP_CLKOUT_INDEX2                       2U
#define CLOCK_IP_CLKOUT_INDEX3                       3U
#define CLOCK_IP_CLKOUT_INDEX4                       4U
#define CLOCK_IP_CLKOUT_NO                           5U


#define CLOCK_IP_CLKPSI5_S_UTIL_INDEX0                       0U
#define CLOCK_IP_CLKPSI5_S_UTIL_INDEX1                       1U
#define CLOCK_IP_CLKPSI5_S_UTIL_NO                           2U


#define CLOCK_IP_COREPLL_FREQ                        2000000000U
#define CLOCK_IP_COREPLL_CHECKSUM                    4147U
#define CLOCK_IP_PERIPHPLL_FREQ                      2000000000U
#define CLOCK_IP_PERIPHPLL_CHECKSUM                  4147U
#define CLOCK_IP_DDRPLL_FREQ                         1600000000U
#define CLOCK_IP_DDRPLL_CHECKSUM                     4137U
#define CLOCK_IP_COREDFS1_FREQ                       800000000U
#define CLOCK_IP_COREDFS1_CHECKSUM                   5694U
#define CLOCK_IP_COREDFS2_FREQ                       800000000U
#define CLOCK_IP_COREDFS2_CHECKSUM                   5694U
#define CLOCK_IP_COREDFS3_FREQ                       0U
#define CLOCK_IP_COREDFS3_CHECKSUM                   5943U
#define CLOCK_IP_COREDFS4_FREQ                       0U
#define CLOCK_IP_COREDFS4_CHECKSUM                   5943U
#define CLOCK_IP_COREDFS5_FREQ                       0U
#define CLOCK_IP_COREDFS5_CHECKSUM                   5943U
#define CLOCK_IP_COREDFS6_FREQ                       0U
#define CLOCK_IP_COREDFS6_CHECKSUM                   5943U
#define CLOCK_IP_PERIPHDFS1_FREQ                     800000000U
#define CLOCK_IP_PERIPHDFS1_CHECKSUM                 5694U
#define CLOCK_IP_PERIPHDFS2_FREQ                     631578947U
#define CLOCK_IP_PERIPHDFS2_CHECKSUM                 5666U
#define CLOCK_IP_PERIPHDFS3_FREQ                     0U
#define CLOCK_IP_PERIPHDFS3_CHECKSUM                 5943U
#define CLOCK_IP_PERIPHDFS4_FREQ                     1000000000U
#define CLOCK_IP_PERIPHDFS4_CHECKSUM                 5687U
#define CLOCK_IP_PERIPHDFS5_FREQ                     1000000000U
#define CLOCK_IP_PERIPHDFS5_CHECKSUM                 5687U
#define CLOCK_IP_PERIPHDFS6_FREQ                     1000000000U
#define CLOCK_IP_PERIPHDFS6_CHECKSUM                 5687U

/*==================================================================================================
                                   GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

static uint64 Clock_Ip_Get_PLL_VCO(const PLLDIG_Type *Base);
static uint64 Clock_Ip_Get_LFAST_PLL_VCO(const LFAST_Type *Base);
static uint64 Clock_Ip_Get_DFS_OUTPUT(const DFS_Type *Base, uint32 Channel, uint64 Fin);
static uint64 Clock_Ip_Get_Zero_Frequency(void);
static uint64 Clock_Ip_Get_FIRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FXOSC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIRC_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
static uint64 Clock_Ip_Get_FIRC_AE_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_COREPLL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DDRPLL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LFAST0_PLL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LFAST1_PLL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_PHI0_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS0_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS1_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS2_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS3_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS4_Frequency(void);
static uint64 Clock_Ip_Get_COREPLL_DFS5_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI0_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI1_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI2_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI3_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI4_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI5_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_PHI6_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS0_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS1_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS2_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS3_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS4_Frequency(void);
static uint64 Clock_Ip_Get_PERIPHPLL_DFS5_Frequency(void);
static uint64 Clock_Ip_Get_DDRPLL_PHI0_Frequency(void);
static uint64 Clock_Ip_Get_eth_rgmii_ref_Frequency(void);
static uint64 Clock_Ip_Get_tmr_1588_ref_Frequency(void);
static uint64 Clock_Ip_Get_eth0_ext_rx_Frequency(void);
static uint64 Clock_Ip_Get_eth0_ext_tx_Frequency(void);
static uint64 Clock_Ip_Get_eth1_ext_rx_Frequency(void);
static uint64 Clock_Ip_Get_eth1_ext_tx_Frequency(void);
static uint64 Clock_Ip_Get_lfast0_ext_ref_Frequency(void);
static uint64 Clock_Ip_Get_lfast1_ext_ref_Frequency(void);
static uint64 Clock_Ip_Get_DDR_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_SYS_DIV4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_SYS_DIV4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_SYS_DIV2_NOC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_SYS_DIV4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_HSE_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_SYS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_SYS_DIV4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_MATH_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_MATH_DIV3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_GLB_LBIST_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU0_CORE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU1_CORE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_UTIL_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_UTIL_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
static uint64 Clock_Ip_Get_SYSTEM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
static uint64 Clock_Ip_Get_SYSTEM_DIV2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
static uint64 Clock_Ip_Get_SYSTEM_DIV4_MON1_CLK_Frequency(void);
#endif
static uint64 Clock_Ip_Get_ADC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ADC1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_EDMA_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_PIT5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CTU_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMACRC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMACRC1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMACRC4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMACRC5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_DMAMUX5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CLKOUT0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CLKOUT1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CLKOUT2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CLKOUT3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CLKOUT4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_EDMA5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_TX_MII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ENET0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_CAN_PE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN6_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN7_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN8_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN9_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN10_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN11_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN12_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN13_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN14_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN15_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN16_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN17_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN18_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN19_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN20_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN21_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN22_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FLEXCAN23_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_FR_PE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FRAY0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_FRAY1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_GTM_CLK_Frequency(void);
static uint64 Clock_Ip_Get_IIIC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_IIIC1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_IIIC2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_LIN_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_LIN_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_LIN_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN6_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN7_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN8_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_LIN_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN9_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN10_CLK_Frequency(void);
static uint64 Clock_Ip_Get_LIN11_CLK_Frequency(void);
static uint64 Clock_Ip_Get_MSCDSPI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_MSCLIN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_NANO_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_CTU_PER_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_DSPI_MSC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_EMIOS_LCU_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_GTM_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_GTM_NOC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_GTM_TS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_LIN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_NANO_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_125K_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_189K_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_CORE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_UART_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_REG_INTF_2X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_DSPI60_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH_TS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH_TS_DIV4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_REF_RMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_RX_MII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_RX_RGMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_TX_RGMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH0_PS_TX_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_REF_RMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_RX_MII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_RX_RGMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_TX_MII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_TX_RGMII_CLK_Frequency(void);
static uint64 Clock_Ip_Get_ETH1_PS_TX_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_LFAST0_REF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_LFAST1_REF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_NETC_AXI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_LIN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_DBG_ATB_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P2_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_AES_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_DBG_TS_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P3_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_DSPI60_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_EMIOS_LCU_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_LIN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_125K_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_189K_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_BAUD_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_CORE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_UART_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_QSPI0_2X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_QSPI0_1X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_QSPI1_2X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_QSPI1_1X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_REG_INTF_2X_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_SDHC_IP_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_SDHC_IP_DIV2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_CANXL_PE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_CANXL_CHI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_DIPORT_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_AE_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_LIN_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P6_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PIT0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PIT1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PIT4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PIT5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_PSI5_1US_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PSI5_0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_PSI5_1US_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PSI5_1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PSI5S_0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_PSI5S_1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_QSPI0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_QSPI1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU0_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RTU1_REG_INTF_CLK_Frequency(void);
static uint64 Clock_Ip_Get_RXLUT_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_SDHC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SDHC0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SINC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIPI0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIPI1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIUL2_0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIUL2_1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIUL2_4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SIUL2_5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P0_DSPI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P1_DSPI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI2_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI3_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI4_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P4_DSPI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI5_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI6_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI7_CLK_Frequency(void);
static uint64 Clock_Ip_Get_P5_DSPI_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI8_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SPI9_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SRX0_CLK_Frequency(void);
static uint64 Clock_Ip_Get_SRX1_CLK_Frequency(void);
static uint64 Clock_Ip_Get_CORE_PLL_REFCLKOUT_Frequency(void);
static uint64 Clock_Ip_Get_PERIPH_PLL_REFCLKOUT_Frequency(void);
static uint64 Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency(void);
static uint64 Clock_Ip_Get_Px_PSI5_S_UTIL_CLK_Frequency(void);

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

static const uint64 Clock_Ip_au32EnableDivider[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};
static const uint64 Clock_Ip_u64EnableGate[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};



typedef uint64 (*getFreqType)(void);

static const getFreqType Clock_Ip_apfFreqTableClkSrc[CLOCK_IP_SELECTOR_SOURCE_NO]    = {
    &Clock_Ip_Get_FIRC_CLK_Frequency,                      /* clock name for 0  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 1  hardware value */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                     /* clock name for 2  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 3  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 4  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 5  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 6  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 7  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 8  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 9  hardware value */
    &Clock_Ip_Get_COREPLL_PHI0_Frequency,                  /* clock name for 10 hardware value */
    &Clock_Ip_Get_COREPLL_DFS0_Frequency,                  /* clock name for 11 hardware value */
    &Clock_Ip_Get_COREPLL_DFS1_Frequency,                  /* clock name for 12 hardware value */
    &Clock_Ip_Get_COREPLL_DFS2_Frequency,                  /* clock name for 13 hardware value */
    &Clock_Ip_Get_COREPLL_DFS3_Frequency,                  /* clock name for 14 hardware value */
    &Clock_Ip_Get_COREPLL_DFS4_Frequency,                  /* clock name for 15 hardware value */
    &Clock_Ip_Get_COREPLL_DFS5_Frequency,                  /* clock name for 16 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 17 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 18 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 19 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI0_Frequency,                /* clock name for 20 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI1_Frequency,                /* clock name for 21 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI2_Frequency,                /* clock name for 22 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI3_Frequency,                /* clock name for 23 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI4_Frequency,                /* clock name for 24 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI5_Frequency,                /* clock name for 25 hardware value */
    &Clock_Ip_Get_PERIPHPLL_PHI6_Frequency,                /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS0_Frequency,                /* clock name for 30 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS1_Frequency,                /* clock name for 31 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS2_Frequency,                /* clock name for 32 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS3_Frequency,                /* clock name for 33 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS4_Frequency,                /* clock name for 34 hardware value */
    &Clock_Ip_Get_PERIPHPLL_DFS5_Frequency,                /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_DDRPLL_PHI0_Frequency,                   /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_eth_rgmii_ref_Frequency,                 /* clock name for 47 hardware value */
    &Clock_Ip_Get_tmr_1588_ref_Frequency,                  /* clock name for 48 hardware value */
    &Clock_Ip_Get_eth0_ext_rx_Frequency,                   /* clock name for 49 hardware value */
    &Clock_Ip_Get_eth0_ext_tx_Frequency,                   /* clock name for 50 hardware value */
    &Clock_Ip_Get_eth1_ext_rx_Frequency,                   /* clock name for 51 hardware value */
    &Clock_Ip_Get_eth1_ext_tx_Frequency,                   /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_lfast0_ext_ref_Frequency,                /* clock name for 59 hardware value */
    &Clock_Ip_Get_lfast1_ext_ref_Frequency,                /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Px_PSI5_S_UTIL_CLK_Frequency,            /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT0SEL[CLOCK_IP_SELECTOR_SOURCE_NO] = {
    &Clock_Ip_Get_SIRC_CLK_Frequency,                      /* clock name for 0  hardware value SIRC_CLK */
    &Clock_Ip_Get_FIRC_CLK_Frequency,                      /* clock name for 1  hardware value FIRC_CLK */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                     /* clock name for 2  hardware value FXOSC_CLK */
    &Clock_Ip_Get_COREPLL_PHI0_Frequency,                  /* clock name for 3  hardware value COREPLL_PHI0_CLK */
    &Clock_Ip_Get_COREPLL_DFS0_Frequency,                  /* clock name for 4  hardware value COREDFS0_CLK */
    &Clock_Ip_Get_COREPLL_DFS1_Frequency,                  /* clock name for 5  hardware value COREDFS1_CLK */
    &Clock_Ip_Get_COREPLL_DFS2_Frequency,                  /* clock name for 6  hardware value COREDFS2_CLK */
    &Clock_Ip_Get_COREPLL_DFS3_Frequency,                  /* clock name for 7  hardware value COREDFS3_CLK */
    &Clock_Ip_Get_COREPLL_DFS4_Frequency,                  /* clock name for 8  hardware value COREDFS4_CLK */
    &Clock_Ip_Get_COREPLL_DFS5_Frequency,                  /* clock name for 9  hardware value COREDFS5_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI0_Frequency,                /* clock name for 10 hardware value PERIPHPLL_PHI0_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI1_Frequency,                /* clock name for 11 hardware value PERIPHPLL_PHI1_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI2_Frequency,                /* clock name for 12 hardware value PERIPHPLL_PHI2_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI3_Frequency,                /* clock name for 13 hardware value PERIPHPLL_PHI3_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI4_Frequency,                /* clock name for 14 hardware value PERIPHPLL_PHI4_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI5_Frequency,                /* clock name for 15 hardware value PERIPHPLL_PHI5_CLK */
    &Clock_Ip_Get_PERIPHPLL_PHI6_Frequency,                /* clock name for 16 hardware value PERIPHPLL_PHI6_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS0_Frequency,                /* clock name for 17 hardware value PERIPHDFS0_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS1_Frequency,                /* clock name for 18 hardware value PERIPHDFS1_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS2_Frequency,                /* clock name for 19 hardware value PERIPHDFS2_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS3_Frequency,                /* clock name for 20 hardware value PERIPHDFS3_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS4_Frequency,                /* clock name for 21 hardware value PERIPHDFS4_CLK */
    &Clock_Ip_Get_PERIPHPLL_DFS5_Frequency,                /* clock name for 22 hardware value PERIPHDFS5_CLK */
    &Clock_Ip_Get_DDRPLL_PHI0_Frequency,                   /* clock name for 23 hardware value DDRPLL_PHI0_CLK */
    &Clock_Ip_Get_P0_SYS_CLK_Frequency,                    /* clock name for 24 hardware value P0_SYS_CLK */
    &Clock_Ip_Get_P0_REG_INTF_CLK_Frequency,               /* clock name for 25 hardware value P0_REG_INTF_CLK */
    &Clock_Ip_Get_P0_REG_INTF_2X_CLK_Frequency,            /* clock name for 26 hardware value P0_REG_INTF_2X_CLK */
    &Clock_Ip_Get_P0_PSI5_1US_CLK_Frequency,               /* clock name for 27 hardware value P0_PSI5_1US_CLK */
    &Clock_Ip_Get_P0_PSI5_125K_CLK_Frequency,              /* clock name for 28 hardware value P0_PSI5_125K_CLK */
    &Clock_Ip_Get_P0_PSI5_189K_CLK_Frequency,              /* clock name for 29 hardware value P0_PSI5_189K_CLK */
    &Clock_Ip_Get_P0_PSI5_S_UTIL_CLK_Frequency,            /* clock name for 30 hardware value P0_PSI5_S_UTIL_CLK */
    &Clock_Ip_Get_P0_PSI5_S_UART_CLK_Frequency,            /* clock name for 31 hardware value P0_PSI5_S_UART_CLK */
    &Clock_Ip_Get_P0_PSI5_S_BAUD_CLK_Frequency,            /* clock name for 32 hardware value P0_PSI5_S_BAUD_CLK */
    &Clock_Ip_Get_P0_PSI5_S_CORE_CLK_Frequency,            /* clock name for 33 hardware value P0_PSI5_S_CORE_CLK */
    &Clock_Ip_Get_P0_LIN_BAUD_CLK_Frequency,               /* clock name for 34 hardware value P0_LIN_BAUD_CLK */
    &Clock_Ip_Get_P0_LIN_CLK_Frequency,                    /* clock name for 35 hardware value P0_LIN_CLK */
    &Clock_Ip_Get_P0_DSPI_CLK_Frequency,                   /* clock name for 36 hardware value P0_DSPI_CLK */
    &Clock_Ip_Get_P0_FR_PE_CLK_Frequency,                  /* clock name for 37 hardware value P0_FR_PE_CLK */
    &Clock_Ip_Get_P0_NANO_CLK_Frequency,                   /* clock name for 38 hardware value P0_NANO_CLK */
    &Clock_Ip_Get_P0_GTM_CLK_Frequency,                    /* clock name for 39 hardware value P0_GTM_CLK */
    &Clock_Ip_Get_P0_GTM_NOC_CLK_Frequency,                /* clock name for 40 hardware value P0_GTM_NOC_CLK */
    &Clock_Ip_Get_P0_GTM_TS_CLK_Frequency,                 /* clock name for 41 hardware value P0_GTM_TS_CLK */
    &Clock_Ip_Get_P0_DSPI_MSC_CLK_Frequency,               /* clock name for 42 hardware value P0_DSPI_MSC_CLK */
    &Clock_Ip_Get_P0_CTU_PER_CLK_Frequency,                /* clock name for 43 hardware value P0_CTU_PER_CLK */
    &Clock_Ip_Get_P0_EMIOS_LCU_CLK_Frequency,              /* clock name for 44 hardware value P0_EMIOS_LCU_CLK */
    &Clock_Ip_Get_CORE_PLL_REFCLKOUT_Frequency,            /* clock name for 45 hardware value CORE_PLL_REFCLKOUT */
    &Clock_Ip_Get_COREPLL_CLK_Frequency,                   /* clock name for 46 hardware value CORE_PLL_FBCLKOUT */
    &Clock_Ip_Get_PERIPH_PLL_REFCLKOUT_Frequency,          /* clock name for 47 hardware value PERIPH_PLL_REFCLKOUT */
    &Clock_Ip_Get_PERIPHPLL_CLK_Frequency,                 /* clock name for 48 hardware value PERIPH_PLL_FBCLKOUT */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT1SEL[CLOCK_IP_SELECTOR_SOURCE_NO] = {
    &Clock_Ip_Get_LFAST0_PLL_CLK_Frequency,                /* clock name for 0  hardware value LFAST0_PLL_PH0_CLK */
    &Clock_Ip_Get_LFAST1_PLL_CLK_Frequency,                /* clock name for 1  hardware value LFAST1_PLL_PH0_CLK */
    &Clock_Ip_Get_P1_SYS_CLK_Frequency,                    /* clock name for 2  hardware value P1_SYS_CLK */
    &Clock_Ip_Get_P1_SYS_DIV2_CLK_Frequency,               /* clock name for 3  hardware value P1_SYS_DIV2_CLK */
    &Clock_Ip_Get_P1_SYS_DIV4_CLK_Frequency,               /* clock name for 4  hardware value P1_SYS_DIV4_CLK */
    &Clock_Ip_Get_P1_REG_INTF_CLK_Frequency,               /* clock name for 5  hardware value P1_REG_INTF_CLK */
    &Clock_Ip_Get_P1_DSPI_CLK_Frequency,                   /* clock name for 6  hardware value P1_DSPI_CLK */
    &Clock_Ip_Get_P1_DSPI60_CLK_Frequency,                 /* clock name for 7  hardware value P1_DSPI60_CLK */
    &Clock_Ip_Get_P1_LIN_BAUD_CLK_Frequency,               /* clock name for 8  hardware value P1_LIN_BAUD_CLK */
    &Clock_Ip_Get_P1_LIN_CLK_Frequency,                    /* clock name for 9  hardware value P1_LIN_CLK */
    &Clock_Ip_Get_ETH_TS_CLK_Frequency,                    /* clock name for 10 hardware value ETH_TS_CLK */
    &Clock_Ip_Get_ETH_TS_DIV4_CLK_Frequency,               /* clock name for 11 hardware value ETH_TS_DIV4_CLK */
    &Clock_Ip_Get_ETH0_TX_MII_CLK_Frequency,               /* clock name for 12 hardware value ETH0_TX_MII_CLK */
    &Clock_Ip_Get_ETH0_TX_RGMII_CLK_Frequency,             /* clock name for 13 hardware value ETH0_TX_RGMII_CLK */
    &Clock_Ip_Get_ETH0_RX_MII_CLK_Frequency,               /* clock name for 14 hardware value ETH0_RX_MII_CLK */
    &Clock_Ip_Get_ETH0_RX_RGMII_CLK_Frequency,             /* clock name for 15 hardware value ETH0_RX_RGMII_CLK */
    &Clock_Ip_Get_ETH0_REF_RMII_CLK_Frequency,             /* clock name for 16 hardware value ETH0_REF_RMII_CLK */
    &Clock_Ip_Get_ETH1_TX_MII_CLK_Frequency,               /* clock name for 17 hardware value ETH1_TX_MII_CLK */
    &Clock_Ip_Get_ETH1_TX_RGMII_CLK_Frequency,             /* clock name for 18 hardware value ETH1_TX_RGMII_CLK */
    &Clock_Ip_Get_ETH1_RX_MII_CLK_Frequency,               /* clock name for 19 hardware value ETH1_RX_MII_CLK */
    &Clock_Ip_Get_ETH1_RX_RGMII_CLK_Frequency,             /* clock name for 20 hardware value ETH1_RX_RGMII_CLK */
    &Clock_Ip_Get_ETH1_REF_RMII_CLK_Frequency,             /* clock name for 21 hardware value ETH1_REF_RMII_CLK */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 22 hardware value ETH_AXI_CLK */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 23 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 24 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 25 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 30 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 32 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 33 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 34 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 47 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 48 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT2SEL[CLOCK_IP_SELECTOR_SOURCE_NO] = {
    &Clock_Ip_Get_P4_SYS_CLK_Frequency,                    /* clock name for 0  hardware value P4_SYS_CLK */
    &Clock_Ip_Get_P4_SYS_DIV2_CLK_Frequency,               /* clock name for 1  hardware value P4_SYS_DIV2_CLK */
    &Clock_Ip_Get_HSE_SYS_DIV2_CLK_Frequency,              /* clock name for 2  hardware value HSE_SYS_DIV2_CLK */
    &Clock_Ip_Get_P4_REG_INTF_CLK_Frequency,               /* clock name for 3  hardware value P4_REG_INTF_CLK */
    &Clock_Ip_Get_P4_REG_INTF_2X_CLK_Frequency,            /* clock name for 4  hardware value P4_REG_INTF_2X_CLK */
    &Clock_Ip_Get_P4_PSI5_1US_CLK_Frequency,               /* clock name for 5  hardware value P4_PSI5_1US_CLK */
    &Clock_Ip_Get_P4_PSI5_125K_CLK_Frequency,              /* clock name for 6  hardware value P4_PSI5_125K_CLK */
    &Clock_Ip_Get_P4_PSI5_189K_CLK_Frequency,              /* clock name for 7  hardware value P4_PSI5_189K_CLK */
    &Clock_Ip_Get_P4_PSI5_S_UTIL_CLK_Frequency,            /* clock name for 8  hardware value P4_PSI5_S_UTIL_CLK */
    &Clock_Ip_Get_P4_PSI5_S_UART_CLK_Frequency,            /* clock name for 9  hardware value P4_PSI5_S_UART_CLK */
    &Clock_Ip_Get_P4_PSI5_S_BAUD_CLK_Frequency,            /* clock name for 10 hardware value P4_PSI5_S_BAUD_CLK */
    &Clock_Ip_Get_P4_PSI5_S_CORE_CLK_Frequency,            /* clock name for 11 hardware value P4_PSI5_S_CORE_CLK */
    &Clock_Ip_Get_P4_DSPI_CLK_Frequency,                   /* clock name for 12 hardware value P4_DSPI_CLK */
    &Clock_Ip_Get_P4_DSPI60_CLK_Frequency,                 /* clock name for 13 hardware value P4_DSPI60_CLK */
    &Clock_Ip_Get_P4_QSPI0_2X_CLK_Frequency,               /* clock name for 14 hardware value P4_QSPI0_2X_CLK */
    &Clock_Ip_Get_P4_QSPI0_1X_CLK_Frequency,               /* clock name for 15 hardware value P4_QSPI0_1X_CLK */
    &Clock_Ip_Get_P4_LIN_BAUD_CLK_Frequency,               /* clock name for 16 hardware value P4_LIN_BAUD_CLK */
    &Clock_Ip_Get_P4_LIN_CLK_Frequency,                    /* clock name for 17 hardware value P4_LIN_CLK */
    &Clock_Ip_Get_P4_SDHC_CLK_Frequency,                   /* clock name for 18 hardware value P4_SDHC_CLK */
    &Clock_Ip_Get_P4_QSPI1_2X_CLK_Frequency,               /* clock name for 19 hardware value P4_QSPI1_2X_CLK */
    &Clock_Ip_Get_P4_QSPI1_1X_CLK_Frequency,               /* clock name for 20 hardware value P4_QSPI1_1X_CLK */
    &Clock_Ip_Get_P4_SDHC_IP_CLK_Frequency,                /* clock name for 21 hardware value P4_SDHC_IP_CLK */
    &Clock_Ip_Get_P4_SDHC_IP_DIV2_CLK_Frequency,           /* clock name for 22 hardware value P4_SDHC_IP_DIV2_CLK */
    &Clock_Ip_Get_P4_EMIOS_LCU_CLK_Frequency,              /* clock name for 23 hardware value P4_EMIOS_LCU_CLK */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 24 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 25 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 30 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 32 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 33 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 34 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 47 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 48 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT3SEL[CLOCK_IP_SELECTOR_SOURCE_NO] = {
    &Clock_Ip_Get_P5_SYS_CLK_Frequency,                    /* clock name for 0  hardware value P5_SYS_CLK */
    &Clock_Ip_Get_P5_SYS_DIV2_CLK_Frequency,               /* clock name for 1  hardware value P5_SYS_DIV2_CLK */
    &Clock_Ip_Get_P5_SYS_DIV4_CLK_Frequency,               /* clock name for 2  hardware value P5_SYS_DIV4_CLK */
    &Clock_Ip_Get_P5_REG_INTF_CLK_Frequency,               /* clock name for 3  hardware value P5_REG_INTF_CLK */
    &Clock_Ip_Get_P5_LIN_BAUD_CLK_Frequency,               /* clock name for 4  hardware value P5_LIN_BAUD_CLK */
    &Clock_Ip_Get_P5_LIN_CLK_Frequency,                    /* clock name for 5  hardware value P5_LIN_CLK */
    &Clock_Ip_Get_P5_DSPI_CLK_Frequency,                   /* clock name for 6  hardware value P5_DSPI_CLK */
    &Clock_Ip_Get_P5_DIPORT_CLK_Frequency,                 /* clock name for 7  hardware value P5_DIPORT_CLK */
    &Clock_Ip_Get_P5_AE_CLK_Frequency,                     /* clock name for 8  hardware value P5_AE_CLK */
    &Clock_Ip_Get_P5_CANXL_PE_CLK_Frequency,               /* clock name for 9  hardware value P5_CANXL_PE_CLK */
    &Clock_Ip_Get_P5_CANXL_CHI_CLK_Frequency,              /* clock name for 10 hardware value P5_CANXL_CHI_CLK */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 11 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 12 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 13 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 14 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 15 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 16 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 17 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 18 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 19 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 20 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 21 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 22 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 23 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 24 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 25 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 30 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 32 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 33 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 34 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 47 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 48 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT4SEL[CLOCK_IP_SELECTOR_SOURCE_NO] = {
    &Clock_Ip_Get_P3_SYS_CLK_Frequency,                    /* clock name for 0  hardware value P3_SYS_CLK */
    &Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency,               /* clock name for 1  hardware value CE_SYS_DIV2_CLK */
    &Clock_Ip_Get_P3_SYS_DIV4_CLK_Frequency,               /* clock name for 2  hardware value CE_SYS_DIV4_CLK */
    &Clock_Ip_Get_P3_REG_INTF_CLK_Frequency,               /* clock name for 3  hardware value P3_REG_INTF_CLK */
    &Clock_Ip_Get_P3_DBG_TS_CLK_Frequency,                 /* clock name for 4  hardware value P3_DBG_TS_CLK */
    &Clock_Ip_Get_P3_CAN_PE_CLK_Frequency,                 /* clock name for 5  hardware value P3_CAN_PE_CLK */
    &Clock_Ip_Get_P2_SYS_CLK_Frequency,                    /* clock name for 6  hardware value P2_SYS_CLK */
    &Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency,            /* clock name for 7  hardware value RTU0_CORE_DIV2_CLK */
    &Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency,            /* clock name for 8  hardware value RTU1_CORE_DIV2_CLK */
    &Clock_Ip_Get_DDR_CLK_Frequency,                       /* clock name for 9  hardware value DDR_CLK */
    &Clock_Ip_Get_P3_SYS_DIV2_NOC_CLK_Frequency,           /* clock name for 10 hardware value P3_SYS_DIV2_NOC_CLK */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 11 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 12 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 13 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 14 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 15 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 16 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 17 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 18 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 19 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 20 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 21 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 22 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 23 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 24 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 25 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 30 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 32 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 33 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 34 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 47 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 48 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableCLKOUT_MULTIPLEX[CLOCK_IP_CLKOUT_NO] = {
    &Clock_Ip_Get_P0_CLKOUT_SRC_CLK_Frequency,                   /* clock name for 0  hardware value CLKOUT0_CLK */
    &Clock_Ip_Get_P1_CLKOUT_SRC_CLK_Frequency,                   /* clock name for 1  hardware value CLKOUT1_CLK */
    &Clock_Ip_Get_P4_CLKOUT_SRC_CLK_Frequency,                   /* clock name for 2  hardware value CLKOUT2_CLK */
    &Clock_Ip_Get_P5_CLKOUT_SRC_CLK_Frequency,                   /* clock name for 3  hardware value CLKOUT3_CLK */
    &Clock_Ip_Get_P3_CLKOUT_SRC_CLK_Frequency,                   /* clock name for 4  hardware value CLKOUT4_CLK */
};

static const getFreqType Clock_Ip_apfFreqTablePSI5_S_UTIL_MULTIPLEX[CLOCK_IP_CLKPSI5_S_UTIL_NO] = {
    &Clock_Ip_Get_P0_PSI5_S_UTIL_CLK_Frequency,                   /* clock name for 0  hardware value P0_PSI5_S_UTIL_CLK */
    &Clock_Ip_Get_P4_PSI5_S_UTIL_CLK_Frequency,                   /* clock name for 1  hardware value P4_PSI5_S_UTIL_CLK */
};

static const getFreqType Clock_Ip_apfFreqTable[CLOCK_IP_NAMES_NO] =
{
    &Clock_Ip_Get_Zero_Frequency,                                    /* CLOCK_IS_OFF                        */
    &Clock_Ip_Get_FIRC_CLK_Frequency,                                /* FIRC_CLK clock                      */
    &Clock_Ip_Get_FXOSC_CLK_Frequency,                               /* FXOSC_CLK clock                     */
    &Clock_Ip_Get_SIRC_CLK_Frequency,                                /* SIRC_CLK clock                      */
#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
    &Clock_Ip_Get_FIRC_AE_CLK_Frequency,                             /* FIRC_AE_CLK clock                      */
#endif
    &Clock_Ip_Get_COREPLL_CLK_Frequency,                             /* COREPLL_CLK clock                   */
    &Clock_Ip_Get_PERIPHPLL_CLK_Frequency,                           /* PERIPHPLL_CLK clock                 */
    &Clock_Ip_Get_DDRPLL_CLK_Frequency,                              /* DDRPLL_CLK clock                    */
    &Clock_Ip_Get_LFAST0_PLL_CLK_Frequency,                          /* LFAST0_PLL_CLK clock                */
    &Clock_Ip_Get_LFAST1_PLL_CLK_Frequency,                          /* LFAST1_PLL_CLK clock                */
    &Clock_Ip_Get_COREPLL_PHI0_Frequency,                            /* COREPLL_PHI0 clock                  */
    &Clock_Ip_Get_COREPLL_DFS0_Frequency,                            /* COREPLL_DFS0 clock                  */
    &Clock_Ip_Get_COREPLL_DFS1_Frequency,                            /* COREPLL_DFS1 clock                  */
    &Clock_Ip_Get_COREPLL_DFS2_Frequency,                            /* COREPLL_DFS2 clock                  */
    &Clock_Ip_Get_COREPLL_DFS3_Frequency,                            /* COREPLL_DFS3 clock                  */
    &Clock_Ip_Get_COREPLL_DFS4_Frequency,                            /* COREPLL_DFS4 clock                  */
    &Clock_Ip_Get_COREPLL_DFS5_Frequency,                            /* COREPLL_DFS5 clock                  */
    &Clock_Ip_Get_PERIPHPLL_PHI0_Frequency,                          /* PERIPHPLL_PHI0 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI1_Frequency,                          /* PERIPHPLL_PHI1 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI2_Frequency,                          /* PERIPHPLL_PHI2 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI3_Frequency,                          /* PERIPHPLL_PHI3 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI4_Frequency,                          /* PERIPHPLL_PHI4 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI5_Frequency,                          /* PERIPHPLL_PHI5 clock                */
    &Clock_Ip_Get_PERIPHPLL_PHI6_Frequency,                          /* PERIPHPLL_PHI6 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS0_Frequency,                          /* PERIPHPLL_DFS0 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS1_Frequency,                          /* PERIPHPLL_DFS1 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS2_Frequency,                          /* PERIPHPLL_DFS2 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS3_Frequency,                          /* PERIPHPLL_DFS3 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS4_Frequency,                          /* PERIPHPLL_DFS4 clock                */
    &Clock_Ip_Get_PERIPHPLL_DFS5_Frequency,                          /* PERIPHPLL_DFS5 clock                */
    &Clock_Ip_Get_DDRPLL_PHI0_Frequency,                             /* DDRPLL_PHI0 clock                   */
    &Clock_Ip_Get_LFAST0_PLL_CLK_Frequency,                          /* LFAST0_PLL_PH0_CLK clock            */
    &Clock_Ip_Get_LFAST1_PLL_CLK_Frequency,                          /* LFAST1_PLL_PH0_CLK clock            */
    &Clock_Ip_Get_eth_rgmii_ref_Frequency,                           /* eth_rgmii_ref clock                 */
    &Clock_Ip_Get_tmr_1588_ref_Frequency,                            /* tmr_1588_ref clock                    */
    &Clock_Ip_Get_eth0_ext_rx_Frequency,                             /* eth0_ext_rx clock                   */
    &Clock_Ip_Get_eth0_ext_tx_Frequency,                             /* eth0_ext_tx clock                   */
    &Clock_Ip_Get_eth1_ext_rx_Frequency,                             /* eth1_ext_rx clock                   */
    &Clock_Ip_Get_eth1_ext_tx_Frequency,                             /* eth1_ext_tx clock                   */
    &Clock_Ip_Get_lfast0_ext_ref_Frequency,                          /* lfast0_ext_ref clock                */
    &Clock_Ip_Get_lfast1_ext_ref_Frequency,                          /* lfast1_ext_ref clock                */
    &Clock_Ip_Get_DDR_CLK_Frequency,                                 /* DDR_CLK clock                       */
    &Clock_Ip_Get_P0_SYS_CLK_Frequency,                              /* P0_SYS_CLK clock                    */
    &Clock_Ip_Get_P1_SYS_CLK_Frequency,                              /* P1_SYS_CLK clock                    */
    &Clock_Ip_Get_P1_SYS_DIV2_CLK_Frequency,                         /* P1_SYS_DIV2_CLK clock               */
    &Clock_Ip_Get_P1_SYS_DIV4_CLK_Frequency,                         /* P1_SYS_DIV4_CLK clock               */
    &Clock_Ip_Get_P2_SYS_CLK_Frequency,                              /* P2_SYS_CLK clock                    */
    &Clock_Ip_Get_P2_SYS_CLK_Frequency,                              /* CORE_M33_CLK clock                  */
    &Clock_Ip_Get_P2_SYS_DIV2_CLK_Frequency,                         /* P2_SYS_DIV2_CLK clock               */
    &Clock_Ip_Get_P2_SYS_DIV4_CLK_Frequency,                         /* P2_SYS_DIV4_CLK clock               */
    &Clock_Ip_Get_P3_SYS_CLK_Frequency,                              /* P3_SYS_CLK clock                    */
    &Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency,                         /* CE_SYS_DIV2_CLK clock               */
    &Clock_Ip_Get_P3_SYS_DIV4_CLK_Frequency,                         /* CE_SYS_DIV4_CLK clock               */
    &Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency,                         /* P3_SYS_DIV2_NOC_CLK clock           */
    &Clock_Ip_Get_P3_SYS_DIV4_CLK_Frequency,                         /* P3_SYS_DIV4_CLK clock               */
    &Clock_Ip_Get_P4_SYS_CLK_Frequency,                              /* P4_SYS_CLK clock                    */
    &Clock_Ip_Get_P4_SYS_DIV2_CLK_Frequency,                         /* P4_SYS_DIV2_CLK clock               */
    &Clock_Ip_Get_P4_SYS_DIV2_CLK_Frequency,                         /* HSE_SYS_DIV2_CLK clock              */
    &Clock_Ip_Get_P5_SYS_CLK_Frequency,                              /* P5_SYS_CLK clock                    */
    &Clock_Ip_Get_P5_SYS_DIV2_CLK_Frequency,                         /* P5_SYS_DIV2_CLK clock               */
    &Clock_Ip_Get_P5_SYS_DIV4_CLK_Frequency,                         /* P5_SYS_DIV4_CLK clock               */
    &Clock_Ip_Get_P2_MATH_CLK_Frequency,                             /* P2_MATH_CLK clock                   */
    &Clock_Ip_Get_P2_MATH_DIV3_CLK_Frequency,                        /* P2_MATH_DIV3_CLK clock              */
    &Clock_Ip_Get_GLB_LBIST_CLK_Frequency,                           /* GLB_LBIST_CLK clock                 */
    &Clock_Ip_Get_RTU0_CORE_CLK_Frequency,                           /* RTU0_CORE_CLK clock                 */
    &Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency,                      /* RTU0_CORE_DIV2_CLK clock            */
    &Clock_Ip_Get_RTU1_CORE_CLK_Frequency,                           /* RTU1_CORE_CLK clock                 */
    &Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency,                      /* RTU1_CORE_DIV2_CLK clock            */
    &Clock_Ip_Get_P0_PSI5_S_UTIL_CLK_Frequency,                      /* P0_PSI5_S_UTIL_CLK clock            */
    &Clock_Ip_Get_P4_PSI5_S_UTIL_CLK_Frequency,                      /* P4_PSI5_S_UTIL_CLK clock            */
#if defined(CLOCK_IP_HAS_SYSTEM_DRUN_CLK)
    &Clock_Ip_Get_SYSTEM_CLK_Frequency,                              /* SYSTEM_DRUN_CLK clock               */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_RUN0_CLK)
    &Clock_Ip_Get_Zero_Frequency,                                    /* SYSTEM_RUN0_CLK clock               */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_SAFE_CLK)
    &Clock_Ip_Get_Zero_Frequency,                                    /* SYSTEM_SAFE_CLK clock               */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
    &Clock_Ip_Get_SYSTEM_CLK_Frequency,                              /* SYSTEM_CLK clock                    */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
    &Clock_Ip_Get_SYSTEM_DIV2_CLK_Frequency,                         /* SYSTEM_DIV2_CLK clock               */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
    &Clock_Ip_Get_SYSTEM_DIV4_MON1_CLK_Frequency,                    /* SYSTEM_DIV4_MON1_CLK clock               */
#endif
#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)
    &Clock_Ip_Get_SYSTEM_DIV4_MON1_CLK_Frequency,                    /* SYSTEM_DIV4_MON2_CLK clock               */
#endif
    NULL_PTR,                                                        /* THE_LAST_PRODUCER_CLK*/
    &Clock_Ip_Get_ADC0_CLK_Frequency,                                /* ADC0_CLK clock                      */
    &Clock_Ip_Get_ADC1_CLK_Frequency,                                /* ADC1_CLK clock                      */
    &Clock_Ip_Get_CE_EDMA_CLK_Frequency,                             /* CE_EDMA_CLK clock                      */
    &Clock_Ip_Get_CE_PIT0_CLK_Frequency,                             /* CE_PIT0_CLK clock                      */
    &Clock_Ip_Get_CE_PIT1_CLK_Frequency,                             /* CE_PIT1_CLK clock                      */
    &Clock_Ip_Get_CE_PIT2_CLK_Frequency,                             /* CE_PIT2_CLK clock                      */
    &Clock_Ip_Get_CE_PIT3_CLK_Frequency,                             /* CE_PIT3_CLK clock                      */
    &Clock_Ip_Get_CE_PIT4_CLK_Frequency,                             /* CE_PIT4_CLK clock                      */
    &Clock_Ip_Get_CE_PIT5_CLK_Frequency,                             /* CE_PIT5_CLK clock                      */
    &Clock_Ip_Get_CLKOUT0_CLK_Frequency,                             /* CLKOUT0_CLK clock                   */
    &Clock_Ip_Get_CLKOUT1_CLK_Frequency,                             /* CLKOUT1_CLK clock                   */
    &Clock_Ip_Get_CLKOUT2_CLK_Frequency,                             /* CLKOUT2_CLK clock                   */
    &Clock_Ip_Get_CLKOUT3_CLK_Frequency,                             /* CLKOUT3_CLK clock                   */
    &Clock_Ip_Get_CLKOUT4_CLK_Frequency,                             /* CLKOUT4_CLK clock                   */
    &Clock_Ip_Get_CTU_CLK_Frequency,                                 /* CTU_CLK clock                      */
    &Clock_Ip_Get_DMACRC0_CLK_Frequency,                             /* DMACRC0_CLK clock                      */
    &Clock_Ip_Get_DMACRC1_CLK_Frequency,                             /* DMACRC1_CLK clock                      */
    &Clock_Ip_Get_DMACRC4_CLK_Frequency,                             /* DMACRC4_CLK clock                      */
    &Clock_Ip_Get_DMACRC5_CLK_Frequency,                             /* DMACRC5_CLK clock                      */
    &Clock_Ip_Get_DMAMUX0_CLK_Frequency,                             /* DMAMUX0_CLK clock                      */
    &Clock_Ip_Get_DMAMUX1_CLK_Frequency,                             /* DMAMUX1_CLK clock                      */
    &Clock_Ip_Get_DMAMUX4_CLK_Frequency,                             /* DMAMUX4_CLK clock                      */
    &Clock_Ip_Get_DMAMUX5_CLK_Frequency,                             /* DMAMUX5_CLK clock                      */
    &Clock_Ip_Get_EDMA0_CLK_Frequency,                               /* EDMA0_CLK clock                     */
    &Clock_Ip_Get_EDMA1_CLK_Frequency,                               /* EDMA1_CLK clock                     */
    &Clock_Ip_Get_EDMA3_CLK_Frequency,                               /* EDMA3_CLK clock                     */
    &Clock_Ip_Get_EDMA4_CLK_Frequency,                               /* EDMA4_CLK clock                     */
    &Clock_Ip_Get_EDMA5_CLK_Frequency,                               /* EDMA5_CLK clock                     */
    &Clock_Ip_Get_ETH0_TX_MII_CLK_Frequency,                         /* ETH0_TX_MII_CLK clock               */
    &Clock_Ip_Get_ENET0_CLK_Frequency,                               /* ENET0_CLK clock                     */
    &Clock_Ip_Get_P3_CAN_PE_CLK_Frequency,                           /* P3_CAN_PE_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN0_CLK_Frequency,                            /* FLEXCAN0_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN1_CLK_Frequency,                            /* FLEXCAN1_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN2_CLK_Frequency,                            /* FLEXCAN2_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN3_CLK_Frequency,                            /* FLEXCAN3_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN4_CLK_Frequency,                            /* FLEXCAN4_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN5_CLK_Frequency,                            /* FLEXCAN5_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN6_CLK_Frequency,                            /* FLEXCAN6_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN7_CLK_Frequency,                            /* FLEXCAN7_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN8_CLK_Frequency,                            /* FLEXCAN8_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN9_CLK_Frequency,                            /* FLEXCAN9_CLK clock                  */
    &Clock_Ip_Get_FLEXCAN10_CLK_Frequency,                           /* FLEXCAN10_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN11_CLK_Frequency,                           /* FLEXCAN11_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN12_CLK_Frequency,                           /* FLEXCAN12_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN13_CLK_Frequency,                           /* FLEXCAN13_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN14_CLK_Frequency,                           /* FLEXCAN14_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN15_CLK_Frequency,                           /* FLEXCAN15_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN16_CLK_Frequency,                           /* FLEXCAN16_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN17_CLK_Frequency,                           /* FLEXCAN17_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN18_CLK_Frequency,                           /* FLEXCAN18_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN19_CLK_Frequency,                           /* FLEXCAN19_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN20_CLK_Frequency,                           /* FLEXCAN20_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN21_CLK_Frequency,                           /* FLEXCAN21_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN22_CLK_Frequency,                           /* FLEXCAN22_CLK clock                 */
    &Clock_Ip_Get_FLEXCAN23_CLK_Frequency,                           /* FLEXCAN23_CLK clock                 */
    &Clock_Ip_Get_P0_FR_PE_CLK_Frequency,                            /* P0_FR_PE_CLK clock                  */
    &Clock_Ip_Get_FRAY0_CLK_Frequency,                               /* FRAY0_CLK clock                     */
    &Clock_Ip_Get_FRAY1_CLK_Frequency,                               /* FRAY1_CLK clock                     */
    &Clock_Ip_Get_GTM_CLK_Frequency,                                 /* GTM_CLK clock                     */
    &Clock_Ip_Get_IIIC0_CLK_Frequency,                               /* IIIC0_CLK clock                     */
    &Clock_Ip_Get_IIIC1_CLK_Frequency,                               /* IIIC1_CLK clock                     */
    &Clock_Ip_Get_IIIC2_CLK_Frequency,                               /* IIIC2_CLK clock                     */
    &Clock_Ip_Get_P0_LIN_BAUD_CLK_Frequency,                         /* P0_LIN_BAUD_CLK clock               */
    &Clock_Ip_Get_LIN0_CLK_Frequency,                                /* LIN0_CLK clock                      */
    &Clock_Ip_Get_LIN1_CLK_Frequency,                                /* LIN1_CLK clock                      */
    &Clock_Ip_Get_LIN2_CLK_Frequency,                                /* LIN2_CLK clock                      */
    &Clock_Ip_Get_P1_LIN_BAUD_CLK_Frequency,                         /* P1_LIN_BAUD_CLK clock               */
    &Clock_Ip_Get_LIN3_CLK_Frequency,                                /* LIN3_CLK clock                      */
    &Clock_Ip_Get_LIN4_CLK_Frequency,                                /* LIN4_CLK clock                      */
    &Clock_Ip_Get_LIN5_CLK_Frequency,                                /* LIN5_CLK clock                      */
    &Clock_Ip_Get_P4_LIN_BAUD_CLK_Frequency,                         /* P4_LIN_BAUD_CLK clock               */
    &Clock_Ip_Get_LIN6_CLK_Frequency,                                /* LIN6_CLK clock                      */
    &Clock_Ip_Get_LIN7_CLK_Frequency,                                /* LIN7_CLK clock                      */
    &Clock_Ip_Get_LIN8_CLK_Frequency,                                /* LIN8_CLK clock                      */
    &Clock_Ip_Get_P5_LIN_BAUD_CLK_Frequency,                         /* P5_LIN_BAUD_CLK clock               */
    &Clock_Ip_Get_LIN9_CLK_Frequency,                                /* LIN9_CLK clock                      */
    &Clock_Ip_Get_LIN10_CLK_Frequency,                               /* LIN10_CLK clock                     */
    &Clock_Ip_Get_LIN11_CLK_Frequency,                               /* LIN11_CLK clock                     */
    &Clock_Ip_Get_MSCDSPI_CLK_Frequency,                             /* MSCDSPI_CLK clock                  */
    &Clock_Ip_Get_MSCLIN_CLK_Frequency,                              /* MSCLIN_CLK clock                   */
    &Clock_Ip_Get_NANO_CLK_Frequency,                                /* NANO_CLK clock                     */
    &Clock_Ip_Get_P0_CLKOUT_SRC_CLK_Frequency,                       /* P0_CLKOUT_SRC_CLK clock             */
    &Clock_Ip_Get_P0_CTU_PER_CLK_Frequency,                          /* P0_CTU_PER_CLK clock                */
    &Clock_Ip_Get_P0_DSPI_MSC_CLK_Frequency,                         /* P0_DSPI_MSC_CLK clock               */
    &Clock_Ip_Get_P0_EMIOS_LCU_CLK_Frequency,                        /* P0_EMIOS_LCU_CLK clock              */
    &Clock_Ip_Get_P0_GTM_CLK_Frequency,                              /* P0_GTM_CLK clock                    */
    &Clock_Ip_Get_P0_GTM_NOC_CLK_Frequency,                          /* P0_GTM_NOC_CLK clock                */
    &Clock_Ip_Get_P0_GTM_TS_CLK_Frequency,                           /* P0_GTM_TS_CLK clock                 */
    &Clock_Ip_Get_P0_LIN_CLK_Frequency,                              /* P0_LIN_CLK clock                    */
    &Clock_Ip_Get_P0_NANO_CLK_Frequency,                             /* P0_NANO_CLK clock                   */
    &Clock_Ip_Get_P0_PSI5_125K_CLK_Frequency,                        /* P0_PSI5_125K_CLK clock              */
    &Clock_Ip_Get_P0_PSI5_189K_CLK_Frequency,                        /* P0_PSI5_189K_CLK clock              */
    &Clock_Ip_Get_P0_PSI5_S_BAUD_CLK_Frequency,                      /* P0_PSI5_S_BAUD_CLK clock            */
    &Clock_Ip_Get_P0_PSI5_S_CORE_CLK_Frequency,                      /* P0_PSI5_S_CORE_CLK clock            */
    &Clock_Ip_Get_P0_PSI5_S_TRIG0_CLK_Frequency,                     /* P0_PSI5_S_TRIG0_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_TRIG1_CLK_Frequency,                     /* P0_PSI5_S_TRIG1_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_TRIG2_CLK_Frequency,                     /* P0_PSI5_S_TRIG2_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_TRIG3_CLK_Frequency,                     /* P0_PSI5_S_TRIG3_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_UART_CLK_Frequency,                      /* P0_PSI5_S_UART_CLK clock            */
    &Clock_Ip_Get_P0_PSI5_S_WDOG0_CLK_Frequency,                     /* P0_PSI5_S_WDOG0_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_WDOG1_CLK_Frequency,                     /* P0_PSI5_S_WDOG1_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_WDOG2_CLK_Frequency,                     /* P0_PSI5_S_WDOG2_CLK clock           */
    &Clock_Ip_Get_P0_PSI5_S_WDOG3_CLK_Frequency,                     /* P0_PSI5_S_WDOG3_CLK clock           */
    &Clock_Ip_Get_P0_REG_INTF_2X_CLK_Frequency,                      /* P0_REG_INTF_2X_CLK clock            */
    &Clock_Ip_Get_P0_REG_INTF_CLK_Frequency,                         /* P0_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P1_CLKOUT_SRC_CLK_Frequency,                       /* P1_CLKOUT_SRC_CLK clock             */
    &Clock_Ip_Get_P1_DSPI60_CLK_Frequency,                           /* P1_DSPI60_CLK clock                 */
    &Clock_Ip_Get_ETH_TS_CLK_Frequency,                              /* ETH_TS_CLK clock                    */
    &Clock_Ip_Get_ETH_TS_DIV4_CLK_Frequency,                         /* ETH_TS_DIV4_CLK clock               */
    &Clock_Ip_Get_ETH0_REF_RMII_CLK_Frequency,                       /* ETH0_REF_RMII_CLK clock             */
    &Clock_Ip_Get_ETH0_RX_MII_CLK_Frequency,                         /* ETH0_RX_MII_CLK clock               */
    &Clock_Ip_Get_ETH0_RX_RGMII_CLK_Frequency,                       /* ETH0_RX_RGMII_CLK clock             */
    &Clock_Ip_Get_ETH0_TX_RGMII_CLK_Frequency,                       /* ETH0_TX_RGMII_CLK clock             */
    &Clock_Ip_Get_ETH0_PS_TX_CLK_Frequency,                          /* ETH0_PS_TX_CLK clock          */
    &Clock_Ip_Get_ETH1_REF_RMII_CLK_Frequency,                       /* ETH1_REF_RMII_CLK clock             */
    &Clock_Ip_Get_ETH1_RX_MII_CLK_Frequency,                         /* ETH1_RX_MII_CLK clock               */
    &Clock_Ip_Get_ETH1_RX_RGMII_CLK_Frequency,                       /* ETH1_RX_RGMII_CLK clock             */
    &Clock_Ip_Get_ETH1_TX_MII_CLK_Frequency,                         /* ETH1_TX_MII_CLK clock               */
    &Clock_Ip_Get_ETH1_TX_RGMII_CLK_Frequency,                       /* ETH1_TX_RGMII_CLK clock             */
    &Clock_Ip_Get_ETH1_PS_TX_CLK_Frequency,                          /* ETH1_PS_TX_CLK clock          */
    &Clock_Ip_Get_P1_LFAST0_REF_CLK_Frequency,                       /* P1_LFAST0_REF_CLK clock             */
    &Clock_Ip_Get_P1_LFAST1_REF_CLK_Frequency,                       /* P1_LFAST1_REF_CLK clock             */
    &Clock_Ip_Get_P1_NETC_AXI_CLK_Frequency,                         /* P1_NETC_AXI_CLK clock               */
    &Clock_Ip_Get_P1_LIN_CLK_Frequency,                              /* P1_LIN_CLK clock                    */
    &Clock_Ip_Get_P1_REG_INTF_CLK_Frequency,                         /* P1_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P2_DBG_ATB_CLK_Frequency,                          /* P2_DBG_ATB_CLK clock                */
    &Clock_Ip_Get_P2_REG_INTF_CLK_Frequency,                         /* P2_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P3_AES_CLK_Frequency,                              /* P3_AES_CLK clock                    */
    &Clock_Ip_Get_P3_CLKOUT_SRC_CLK_Frequency,                       /* P3_CLKOUT_SRC_CLK clock             */
    &Clock_Ip_Get_P3_DBG_TS_CLK_Frequency,                           /* P3_DBG_TS_CLK clock                 */
    &Clock_Ip_Get_P3_REG_INTF_CLK_Frequency,                         /* P3_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P3_SYS_CLK_Frequency,                              /* P3_SYS_MON1_CLK clock               */
    &Clock_Ip_Get_P3_SYS_CLK_Frequency,                              /* P3_SYS_MON2_CLK clock               */
    &Clock_Ip_Get_P3_SYS_CLK_Frequency,                              /* P3_SYS_MON3_CLK clock               */
    &Clock_Ip_Get_P4_CLKOUT_SRC_CLK_Frequency,                       /* P4_CLKOUT_SRC_CLK clock             */
    &Clock_Ip_Get_P4_DSPI60_CLK_Frequency,                           /* P4_DSPI60_CLK clock                 */
    &Clock_Ip_Get_P4_EMIOS_LCU_CLK_Frequency,                        /* P4_EMIOS_LCU_CLK clock              */
    &Clock_Ip_Get_P4_LIN_CLK_Frequency,                              /* P4_LIN_CLK clock                    */
    &Clock_Ip_Get_P4_PSI5_125K_CLK_Frequency,                        /* P4_PSI5_125K_CLK clock              */
    &Clock_Ip_Get_P4_PSI5_189K_CLK_Frequency,                        /* P4_PSI5_189K_CLK clock              */
    &Clock_Ip_Get_P4_PSI5_S_BAUD_CLK_Frequency,                      /* P4_PSI5_S_BAUD_CLK clock            */
    &Clock_Ip_Get_P4_PSI5_S_CORE_CLK_Frequency,                      /* P4_PSI5_S_CORE_CLK clock            */
    &Clock_Ip_Get_P4_PSI5_S_TRIG0_CLK_Frequency,                     /* P4_PSI5_S_TRIG0_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_TRIG1_CLK_Frequency,                     /* P4_PSI5_S_TRIG1_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_TRIG2_CLK_Frequency,                     /* P4_PSI5_S_TRIG2_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_TRIG3_CLK_Frequency,                     /* P4_PSI5_S_TRIG3_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_UART_CLK_Frequency,                      /* P4_PSI5_S_UART_CLK clock            */
    &Clock_Ip_Get_P4_PSI5_S_WDOG0_CLK_Frequency,                     /* P4_PSI5_S_WDOG0_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_WDOG1_CLK_Frequency,                     /* P4_PSI5_S_WDOG1_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_WDOG2_CLK_Frequency,                     /* P4_PSI5_S_WDOG2_CLK clock           */
    &Clock_Ip_Get_P4_PSI5_S_WDOG3_CLK_Frequency,                     /* P4_PSI5_S_WDOG3_CLK clock           */
    &Clock_Ip_Get_P4_QSPI0_2X_CLK_Frequency,                         /* P4_QSPI0_2X_CLK clock               */
    &Clock_Ip_Get_P4_QSPI0_1X_CLK_Frequency,                         /* P4_QSPI0_1X_CLK clock               */
    &Clock_Ip_Get_P4_QSPI1_2X_CLK_Frequency,                         /* P4_QSPI1_2X_CLK clock               */
    &Clock_Ip_Get_P4_QSPI1_1X_CLK_Frequency,                         /* P4_QSPI1_1X_CLK clock               */
    &Clock_Ip_Get_P4_REG_INTF_2X_CLK_Frequency,                      /* P4_REG_INTF_2X_CLK clock            */
    &Clock_Ip_Get_P4_REG_INTF_CLK_Frequency,                         /* P4_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P4_SDHC_IP_CLK_Frequency,                          /* P4_SDHC_IP_CLK clock                */
    &Clock_Ip_Get_P4_SDHC_IP_DIV2_CLK_Frequency,                     /* P4_SDHC_IP_DIV2_CLK clock           */
    &Clock_Ip_Get_P5_DIPORT_CLK_Frequency,                           /* P5_DIPORT_CLK clock                 */
    &Clock_Ip_Get_P5_AE_CLK_Frequency,                               /* P5_AE_CLK clock                     */
    &Clock_Ip_Get_P5_CANXL_PE_CLK_Frequency,                         /* P5_CANXL_PE_CLK clock               */
    &Clock_Ip_Get_P5_CANXL_CHI_CLK_Frequency,                        /* P5_CANXL_CHI_CLK clock              */
    &Clock_Ip_Get_P5_CLKOUT_SRC_CLK_Frequency,                       /* P5_CLKOUT_SRC_CLK clock             */
    &Clock_Ip_Get_P5_LIN_CLK_Frequency,                              /* P5_LIN_CLK clock                    */
    &Clock_Ip_Get_P5_REG_INTF_CLK_Frequency,                         /* P5_REG_INTF_CLK clock               */
    &Clock_Ip_Get_P6_REG_INTF_CLK_Frequency,                         /* P6_REG_INTF_CLK clock               */
    &Clock_Ip_Get_PIT0_CLK_Frequency,                                /* PIT0_CLK clock                      */
    &Clock_Ip_Get_PIT1_CLK_Frequency,                                /* PIT1_CLK clock                      */
    &Clock_Ip_Get_PIT4_CLK_Frequency,                                /* PIT4_CLK clock                      */
    &Clock_Ip_Get_PIT5_CLK_Frequency,                                /* PIT5_CLK clock                      */
    &Clock_Ip_Get_P0_PSI5_1US_CLK_Frequency,                         /* P0_PSI5_1US_CLK clock               */
    &Clock_Ip_Get_PSI5_0_CLK_Frequency,                              /* PSI5_0_CLK clock                    */
    &Clock_Ip_Get_P4_PSI5_1US_CLK_Frequency,                         /* P4_PSI5_1US_CLK clock               */
    &Clock_Ip_Get_PSI5_1_CLK_Frequency,                              /* PSI5_1_CLK clock                    */
    &Clock_Ip_Get_PSI5S_0_CLK_Frequency,                             /* PSI5S_0_CLK clock                   */
    &Clock_Ip_Get_PSI5S_1_CLK_Frequency,                             /* PSI5S_1_CLK clock                   */
    &Clock_Ip_Get_QSPI0_CLK_Frequency,                               /* QSPI0_CLK clock                     */
    &Clock_Ip_Get_QSPI1_CLK_Frequency,                               /* QSPI1_CLK clock                     */
    &Clock_Ip_Get_RTU0_CORE_CLK_Frequency,                           /* RTU0_CORE_MON1_CLK clock            */
    &Clock_Ip_Get_RTU0_CORE_CLK_Frequency,                           /* RTU0_CORE_MON2_CLK clock            */
    &Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency,                      /* RTU0_CORE_DIV2_MON1_CLK clock       */
    &Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency,                      /* RTU0_CORE_DIV2_MON2_CLK clock       */
    &Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency,                      /* RTU0_CORE_DIV2_MON3_CLK clock       */
    &Clock_Ip_Get_RTU0_REG_INTF_CLK_Frequency,                       /* RTU0_REG_INTF_CLK clock             */
    &Clock_Ip_Get_RTU1_CORE_CLK_Frequency,                           /* RTU1_CORE_MON1_CLK clock            */
    &Clock_Ip_Get_RTU1_CORE_CLK_Frequency,                           /* RTU1_CORE_MON2_CLK clock            */
    &Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency,                      /* RTU1_CORE_DIV2_MON1_CLK clock       */
    &Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency,                      /* RTU1_CORE_DIV2_MON2_CLK clock       */
    &Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency,                      /* RTU1_CORE_DIV2_MON3_CLK clock       */
    &Clock_Ip_Get_RTU1_REG_INTF_CLK_Frequency,                       /* RTU1_REG_INTF_CLK clock             */
    &Clock_Ip_Get_P4_SDHC_CLK_Frequency,                             /* P4_SDHC_CLK clock                   */
    &Clock_Ip_Get_RXLUT_CLK_Frequency,                               /* RXLUT_CLK clock                     */
    &Clock_Ip_Get_SDHC0_CLK_Frequency,                               /* SDHC0_CLK clock                     */
    &Clock_Ip_Get_SINC_CLK_Frequency,                                /* SINC_CLK clock                      */
    &Clock_Ip_Get_SIPI0_CLK_Frequency,                               /* SIPI0_CLK clock                     */
    &Clock_Ip_Get_SIPI1_CLK_Frequency,                               /* SIPI1_CLK clock                     */
    &Clock_Ip_Get_SIUL2_0_CLK_Frequency,                             /* SIUL2_0_CLK clock                   */
    &Clock_Ip_Get_SIUL2_1_CLK_Frequency,                             /* SIUL2_1_CLK clock                   */
    &Clock_Ip_Get_SIUL2_4_CLK_Frequency,                             /* SIUL2_4_CLK clock                   */
    &Clock_Ip_Get_SIUL2_5_CLK_Frequency,                             /* SIUL2_5_CLK clock                   */
    &Clock_Ip_Get_P0_DSPI_CLK_Frequency,                             /* P0_DSPI_CLK clock                   */
    &Clock_Ip_Get_SPI0_CLK_Frequency,                                /* SPI0_CLK clock                      */
    &Clock_Ip_Get_SPI1_CLK_Frequency,                                /* SPI1_CLK clock                      */
    &Clock_Ip_Get_P1_DSPI_CLK_Frequency,                             /* P1_DSPI_CLK clock                   */
    &Clock_Ip_Get_SPI2_CLK_Frequency,                                /* SPI2_CLK clock                      */
    &Clock_Ip_Get_SPI3_CLK_Frequency,                                /* SPI3_CLK clock                      */
    &Clock_Ip_Get_SPI4_CLK_Frequency,                                /* SPI4_CLK clock                      */
    &Clock_Ip_Get_P4_DSPI_CLK_Frequency,                             /* P4_DSPI_CLK clock                   */
    &Clock_Ip_Get_SPI5_CLK_Frequency,                                /* SPI5_CLK clock                      */
    &Clock_Ip_Get_SPI6_CLK_Frequency,                                /* SPI6_CLK clock                      */
    &Clock_Ip_Get_SPI7_CLK_Frequency,                                /* SPI7_CLK clock                      */
    &Clock_Ip_Get_P5_DSPI_CLK_Frequency,                             /* P5_DSPI_CLK clock                   */
    &Clock_Ip_Get_SPI8_CLK_Frequency,                                /* SPI8_CLK clock                      */
    &Clock_Ip_Get_SPI9_CLK_Frequency,                                /* SPI9_CLK clock                      */
    &Clock_Ip_Get_SRX0_CLK_Frequency,                                /* SRX0_CLK clock                      */
    &Clock_Ip_Get_SRX1_CLK_Frequency,                                /* SRX1_CLK clock                      */
    &Clock_Ip_Get_CORE_PLL_REFCLKOUT_Frequency,                      /* CORE_PLL_REFCLKOUT clock            */
    &Clock_Ip_Get_COREPLL_CLK_Frequency,                             /* CORE_PLL_FBCLKOUT clock             */
    &Clock_Ip_Get_PERIPH_PLL_REFCLKOUT_Frequency,                    /* PERIPH_PLL_REFCLKOUT clock          */
    &Clock_Ip_Get_PERIPHPLL_CLK_Frequency,                           /* PERIPH_PLL_FBCLKOUT clock           */
};

#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
static const getFreqType Clock_Ip_apfFreqTableAeClkSrc[CLOCK_IP_SELECTOR_SOURCE_NO] =
{
    &Clock_Ip_Get_FIRC_AE_CLK_Frequency,                   /* clock name for 0  hardware value */
    &Clock_Ip_Get_P5_AE_CLK_Frequency,                     /* clock name for 1  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 2  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 3  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 4  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 5  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 6  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 7  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 8  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 9  hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 10 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 11 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 12 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 13 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 14 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 15 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 16 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 17 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 18 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 19 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 20 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 21 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 22 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 23 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 24 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 25 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 26 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 27 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 28 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 29 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 30 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 31 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 32 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 33 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 34 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 35 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 36 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 37 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 38 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 39 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 40 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 41 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 42 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 43 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 44 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 45 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 46 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 47 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 48 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 49 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 50 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 51 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 52 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 53 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 54 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 55 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 56 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 57 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 58 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 59 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 60 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 61 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 62 hardware value */
    &Clock_Ip_Get_Zero_Frequency,                          /* clock name for 63 hardware value */
};
#endif

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/* External oscillators */
static uint64 Clock_Ip_u64Fxosc = CLOCK_IP_DEFAULT_FXOSC_FREQUENCY;
static extSignalFreq Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EXT_SIGNALS_NO] =  {{ETH_RGMII_REF_CLK,0U},{TMR_1588_CLK,0U},{ETH0_EXT_RX_CLK,0U},{ETH0_EXT_TX_CLK,0U},{ETH1_EXT_RX_CLK,0U},{ETH1_EXT_TX_CLK,0U},{LFAST0_EXT_REF_CLK,0U},{LFAST1_EXT_REF_CLK,0U}};

static uint64 Clock_Ip_u64CorePllFreq        = CLOCK_IP_COREPLL_FREQ;
static uint64 Clock_Ip_u64CorePllChecksum    = CLOCK_IP_COREPLL_CHECKSUM;
static uint64 Clock_Ip_u64PeriphPllFreq      = CLOCK_IP_PERIPHPLL_FREQ;
static uint64 Clock_Ip_u64PeriphPllChecksum  = CLOCK_IP_PERIPHPLL_CHECKSUM;
static uint64 Clock_Ip_u64DdrPllFreq         = CLOCK_IP_DDRPLL_FREQ;
static uint64 Clock_Ip_u64DdrPllChecksum     = CLOCK_IP_DDRPLL_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs1Freq       = CLOCK_IP_COREDFS1_FREQ;
static uint64 Clock_Ip_u64CoreDfs1Checksum   = CLOCK_IP_COREDFS1_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs2Freq       = CLOCK_IP_COREDFS2_FREQ;
static uint64 Clock_Ip_u64CoreDfs2Checksum   = CLOCK_IP_COREDFS2_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs3Freq       = CLOCK_IP_COREDFS3_FREQ;
static uint64 Clock_Ip_u64CoreDfs3Checksum   = CLOCK_IP_COREDFS3_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs4Freq       = CLOCK_IP_COREDFS4_FREQ;
static uint64 Clock_Ip_u64CoreDfs4Checksum   = CLOCK_IP_COREDFS4_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs5Freq       = CLOCK_IP_COREDFS5_FREQ;
static uint64 Clock_Ip_u64CoreDfs5Checksum   = CLOCK_IP_COREDFS5_CHECKSUM;
static uint64 Clock_Ip_u64CoreDfs6Freq       = CLOCK_IP_COREDFS6_FREQ;
static uint64 Clock_Ip_u64CoreDfs6Checksum   = CLOCK_IP_COREDFS6_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs1Freq     = CLOCK_IP_PERIPHDFS1_FREQ;
static uint64 Clock_Ip_u64PeriphDfs1Checksum = CLOCK_IP_PERIPHDFS1_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs2Freq     = CLOCK_IP_PERIPHDFS2_FREQ;
static uint64 Clock_Ip_u64PeriphDfs2Checksum = CLOCK_IP_PERIPHDFS2_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs3Freq     = CLOCK_IP_PERIPHDFS3_FREQ;
static uint64 Clock_Ip_u64PeriphDfs3Checksum = CLOCK_IP_PERIPHDFS3_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs4Freq     = CLOCK_IP_PERIPHDFS4_FREQ;
static uint64 Clock_Ip_u64PeriphDfs4Checksum = CLOCK_IP_PERIPHDFS4_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs5Freq     = CLOCK_IP_PERIPHDFS5_FREQ;
static uint64 Clock_Ip_u64PeriphDfs5Checksum = CLOCK_IP_PERIPHDFS5_CHECKSUM;
static uint64 Clock_Ip_u64PeriphDfs6Freq     = CLOCK_IP_PERIPHDFS6_FREQ;
static uint64 Clock_Ip_u64PeriphDfsChecksum = CLOCK_IP_PERIPHDFS6_CHECKSUM;

static uint64 Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX0;
static uint64 Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"



/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/* Return zero frequency */
static uint64 Clock_Ip_Get_Zero_Frequency(void)
{
    return 0U;
}
/* Return FIRC_CLK frequency */
static uint64 Clock_Ip_Get_FIRC_CLK_Frequency(void) {

    return CLOCK_IP_FIRC_FREQUENCY;
}
/* Return FXOSC_CLK frequency */
static uint64 Clock_Ip_Get_FXOSC_CLK_Frequency(void) {

    return Clock_Ip_u64Fxosc;
}
/* Return SIRC_CLK frequency */
static uint64 Clock_Ip_Get_SIRC_CLK_Frequency(void) {

    return CLOCK_IP_SIRC_FREQUENCY;
}

#if defined(CLOCK_IP_HAS_FIRC_AE_CLK)
/* Return FIRC_AE_CLK frequency */
static uint64 Clock_Ip_Get_FIRC_AE_CLK_Frequency(void){

    return CLOCK_IP_FIRC_AE_FREQUENCY;
}
#endif

/* Return COREPLL_CLK frequency */
static uint64 Clock_Ip_Get_COREPLL_CLK_Frequency(void) {

    if (Clock_Ip_u64CorePllChecksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD))
    {
        Clock_Ip_u64CorePllChecksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD);
        Clock_Ip_u64CorePllFreq = Clock_Ip_Get_PLL_VCO(IP_CORE_PLL);
    }
    return (((IP_CORE_PLL->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u64CorePllFreq : 0U;
}
/* Return PERIPHPLL_CLK frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_CLK_Frequency(void) {

    if (Clock_Ip_u64PeriphPllChecksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD))
    {
        Clock_Ip_u64PeriphPllChecksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD);
        Clock_Ip_u64PeriphPllFreq = Clock_Ip_Get_PLL_VCO(IP_PERIPH_PLL);
    }
    return (((IP_PERIPH_PLL->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u64PeriphPllFreq : 0U;
}
/* Return DDRPLL_CLK frequency */
static uint64 Clock_Ip_Get_DDRPLL_CLK_Frequency(void) {

    if (Clock_Ip_u64DdrPllChecksum != (uint64)((uint64)IP_DDR_PLL->PLLCLKMUX ^ (uint64)IP_DDR_PLL->PLLDV ^ (uint64)IP_DDR_PLL->PLLFD))
    {
        Clock_Ip_u64DdrPllChecksum = (uint64)((uint64)IP_DDR_PLL->PLLCLKMUX ^ (uint64)IP_DDR_PLL->PLLDV ^ (uint64)IP_DDR_PLL->PLLFD);
        Clock_Ip_u64DdrPllFreq = Clock_Ip_Get_PLL_VCO(IP_DDR_PLL);
    }
    return (((IP_DDR_PLL->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u64DdrPllFreq : 0U;
}
/* Return COREPLL_PHI0 frequency */
static uint64 Clock_Ip_Get_COREPLL_PHI0_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_COREPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_CORE_PLL->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_CORE_PLL->PLLODIV[0U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

/* Return COREPLL_DFS0 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS0_Frequency(void) {

    if (Clock_Ip_u64CoreDfs1Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[0U]))
    {
        Clock_Ip_u64CoreDfs1Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[0U]);
        Clock_Ip_u64CoreDfs1Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,0U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_0_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs1Freq : 0U;
}
/* Return COREPLL_DFS1 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS1_Frequency(void) {

    if (Clock_Ip_u64CoreDfs2Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[1U]))
    {
        Clock_Ip_u64CoreDfs2Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[1U]);
        Clock_Ip_u64CoreDfs2Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,1U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_1_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs2Freq : 0U;
}
/* Return COREPLL_DFS2 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS2_Frequency(void) {

    if (Clock_Ip_u64CoreDfs3Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[2U]))
    {
        Clock_Ip_u64CoreDfs3Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[2U]);
        Clock_Ip_u64CoreDfs3Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,2U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_2_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs3Freq : 0U;
}
/* Return COREPLL_DFS3 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS3_Frequency(void) {

    if (Clock_Ip_u64CoreDfs4Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[3U]))
    {
        Clock_Ip_u64CoreDfs4Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[3U]);
        Clock_Ip_u64CoreDfs4Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,3U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_3_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs4Freq : 0U;
}
/* Return COREPLL_DFS4 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS4_Frequency(void) {

    if (Clock_Ip_u64CoreDfs5Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[4U]))
    {
        Clock_Ip_u64CoreDfs5Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[4U]);
        Clock_Ip_u64CoreDfs5Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,4U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_4_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs5Freq : 0U;
}
/* Return COREPLL_DFS5 frequency */
static uint64 Clock_Ip_Get_COREPLL_DFS5_Frequency(void) {

    if (Clock_Ip_u64CoreDfs6Checksum != (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[5U]))
    {
        Clock_Ip_u64CoreDfs6Checksum = (uint64)((uint64)IP_CORE_PLL->PLLCLKMUX ^ (uint64)IP_CORE_PLL->PLLDV ^ (uint64)IP_CORE_PLL->PLLFD ^ (uint64)IP_CORE_PLL->PLLSR ^ (uint64)IP_CORE_DFS->DVPORT[5U]);
        Clock_Ip_u64CoreDfs6Freq = Clock_Ip_Get_DFS_OUTPUT(IP_CORE_DFS,5U,Clock_Ip_Get_COREPLL_CLK_Frequency());
    }
    return ((((IP_CORE_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_5_CHANNEL) != 0U) ? Clock_Ip_u64CoreDfs6Freq : 0U;
}
/* Return PERIPHPLL_PHI0 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI0_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[0U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

/* Return PERIPHPLL_PHI1 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI1_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[1U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[1U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}
/* Return PERIPHPLL_PHI2 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI2_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[2U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[2U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}
/* Return PERIPHPLL_PHI3 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI3_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[3U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[3U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}
/* Return PERIPHPLL_PHI4 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI4_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[4U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[4U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}
/* Return PERIPHPLL_PHI5 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI5_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[5U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[5U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}
/* Return PERIPHPLL_PHI6 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_PHI6_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_PERIPHPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_PERIPH_PLL->PLLODIV[6U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_PERIPH_PLL->PLLODIV[6U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

/* Return PERIPHPLL_DFS0 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS0_Frequency(void) {

    if (Clock_Ip_u64PeriphDfs1Checksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[0U]))
    {
        Clock_Ip_u64PeriphDfs1Checksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[0U]);
        Clock_Ip_u64PeriphDfs1Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,0U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_0_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs1Freq : 0U;
}
/* Return PERIPHPLL_DFS1 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS1_Frequency(void) {

    if (Clock_Ip_u64PeriphDfs2Checksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[1U]))
    {
        Clock_Ip_u64PeriphDfs2Checksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[1U]);
        Clock_Ip_u64PeriphDfs2Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,1U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_1_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs2Freq : 0U;
}
/* Return PERIPHPLL_DFS2 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS2_Frequency(void) {

    if (Clock_Ip_u64PeriphDfs3Checksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[2U]))
    {
        Clock_Ip_u64PeriphDfs3Checksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[2U]);
        Clock_Ip_u64PeriphDfs3Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,2U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_2_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs3Freq : 0U;
}
/* Return PERIPHPLL_DFS3 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS3_Frequency(void) {

    if (Clock_Ip_u64PeriphDfs4Checksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[3U]))
    {
        Clock_Ip_u64PeriphDfs4Checksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[3U]);
        Clock_Ip_u64PeriphDfs4Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,3U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_3_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs4Freq : 0U;
}
/* Return PERIPHPLL_DFS4 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS4_Frequency(void) {

    if (Clock_Ip_u64PeriphDfs5Checksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[4U]))
    {
        Clock_Ip_u64PeriphDfs5Checksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[4U]);
        Clock_Ip_u64PeriphDfs5Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,4U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_4_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs5Freq : 0U;
}
/* Return PERIPHPLL_DFS5 frequency */
static uint64 Clock_Ip_Get_PERIPHPLL_DFS5_Frequency(void) {

    if (Clock_Ip_u64PeriphDfsChecksum != (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[5U]))
    {
        Clock_Ip_u64PeriphDfsChecksum = (uint64)((uint64)IP_PERIPH_PLL->PLLCLKMUX ^ (uint64)IP_PERIPH_PLL->PLLDV ^ (uint64)IP_PERIPH_PLL->PLLFD ^ (uint64)IP_PERIPH_PLL->PLLSR ^ (uint64)IP_PERIPH_DFS->DVPORT[5U]);
        Clock_Ip_u64PeriphDfs6Freq = Clock_Ip_Get_DFS_OUTPUT(IP_PERIPH_DFS,5U,Clock_Ip_Get_PERIPHPLL_CLK_Frequency());
    }
    return ((((IP_PERIPH_DFS->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & CLOCK_IP_DFS_MASK_5_CHANNEL) != 0U) ? Clock_Ip_u64PeriphDfs6Freq : 0U;
}
/* Return DDRPLL_PHI0 frequency */
static uint64 Clock_Ip_Get_DDRPLL_PHI0_Frequency(void) {

    uint64 Frequency = Clock_Ip_Get_DDRPLL_CLK_Frequency();
    Frequency &= Clock_Ip_au32EnableDivider[((IP_DDR_PLL->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_DDR_PLL->PLLODIV[0U] & (uint64)PLLDIG_PLLODIV_DIV_MASK) >> (uint64)PLLDIG_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

/* Return eth_rgmii_ref frequency */
static uint64 Clock_Ip_Get_eth_rgmii_ref_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_ETH_RGMII_REF_CLK_INDEX_ENTRY].Frequency;
}

/* Return tmr_1588_ref frequency */
static uint64 Clock_Ip_Get_tmr_1588_ref_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_TMR_1588_CLK_INDEX_ENTRY].Frequency;
}

/* Return eth0_ext_rx frequency */
static uint64 Clock_Ip_Get_eth0_ext_rx_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_ETH0_EXT_RX_CLK_INDEX_ENTRY].Frequency;
}
/* Return eth0_ext_tx frequency */
static uint64 Clock_Ip_Get_eth0_ext_tx_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_ETH0_EXT_TX_CLK_INDEX_ENTRY].Frequency;
}

/* Return eth1_ext_rx frequency */
static uint64 Clock_Ip_Get_eth1_ext_rx_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_ETH1_EXT_RX_CLK_INDEX_ENTRY].Frequency;
}
/* Return eth1_ext_tx frequency */
static uint64 Clock_Ip_Get_eth1_ext_tx_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_ETH1_EXT_TX_CLK_INDEX_ENTRY].Frequency;
}

/* Return lfast0_ext_ref frequency */
static uint64 Clock_Ip_Get_lfast0_ext_ref_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_LFAST0_EXT_REF_CLK_INDEX_ENTRY].Frequency;
}
/* Return lfast1_ext_ref frequency */
static uint64 Clock_Ip_Get_lfast1_ext_ref_Frequency(void) {

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_LFAST1_EXT_REF_CLK_INDEX_ENTRY].Frequency;
}

/* Return P0_FR_PE_CLK frequency */
static uint64 Clock_Ip_Get_P0_FR_PE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return FRAY0_CLK frequency */
static uint64 Clock_Ip_Get_FRAY0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->FR0PCTL & GPR0_PCTL_FR0PCTL_PCTL_MASK) >> GPR0_PCTL_FR0PCTL_PCTL_SHIFT)];             /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return FRAY1_CLK frequency */
static uint64 Clock_Ip_Get_FRAY1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->FR1PCTL & GPR0_PCTL_FR1PCTL_PCTL_MASK) >> GPR0_PCTL_FR1PCTL_PCTL_SHIFT)];             /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return GTM_CLK frequency */
static uint64 Clock_Ip_Get_GTM_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->GTMNANOPCTL & GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_MASK) >> GPR0_PCTL_GTMNANOPCTL_PCTL_GTM_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return P0_LIN_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P0_LIN_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return LIN0_CLK frequency */
static uint64 Clock_Ip_Get_LIN0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->LIN0PCTL & GPR0_PCTL_LIN0PCTL_PCTL_MASK) >> GPR0_PCTL_LIN0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN1_CLK frequency */
static uint64 Clock_Ip_Get_LIN1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->LIN1PCTL & GPR0_PCTL_LIN1PCTL_PCTL_MASK) >> GPR0_PCTL_LIN1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN2_CLK frequency */
static uint64 Clock_Ip_Get_LIN2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->LIN2PCTL & GPR0_PCTL_LIN2PCTL_PCTL_MASK) >> GPR0_PCTL_LIN2PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return P1_LIN_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P1_LIN_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return LIN3_CLK frequency */
static uint64 Clock_Ip_Get_LIN3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->LIN3PCTL & GPR1_PCTL_LIN3PCTL_PCTL_MASK) >> GPR1_PCTL_LIN3PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN4_CLK frequency */
static uint64 Clock_Ip_Get_LIN4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->LIN4PCTL & GPR1_PCTL_LIN4PCTL_PCTL_MASK) >> GPR1_PCTL_LIN4PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN5_CLK frequency */
static uint64 Clock_Ip_Get_LIN5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->LIN5PCTL & GPR1_PCTL_LIN5PCTL_PCTL_MASK) >> GPR1_PCTL_LIN5PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN9_CLK frequency */
static uint64 Clock_Ip_Get_LIN9_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->LIN9PCTL & GPR5_PCTL_LIN9PCTL_PCTL_MASK) >> GPR5_PCTL_LIN9PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN10_CLK frequency */
static uint64 Clock_Ip_Get_LIN10_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->LIN10PCTL & GPR5_PCTL_LIN10PCTL_PCTL_MASK) >> GPR5_PCTL_LIN10PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return LIN11_CLK frequency */
static uint64 Clock_Ip_Get_LIN11_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->LIN11PCTL & GPR5_PCTL_LIN11PCTL_PCTL_MASK) >> GPR5_PCTL_LIN11PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return MSCDSPI_CLK frequency */
static uint64 Clock_Ip_Get_MSCDSPI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_1 & MC_CGM_MUX_7_DC_1_DE_MASK) >> MC_CGM_MUX_7_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_7_DC_1 & (uint64)MC_CGM_MUX_7_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->MSCDSPIPCTL & GPR0_PCTL_MSCDSPIPCTL_PCTL_MASK) >> GPR0_PCTL_MSCDSPIPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return MSCLIN_CLK frequency */
static uint64 Clock_Ip_Get_MSCLIN_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->MSCLINPCTL & GPR0_PCTL_MSCLINPCTL_PCTL_MASK) >> GPR0_PCTL_MSCLINPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return NANO_CLK frequency */
static uint64 Clock_Ip_Get_NANO_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->GTMNANOPCTL & GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_MASK) >> GPR0_PCTL_GTMNANOPCTL_PCTL_NANO_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return P5_LIN_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P5_LIN_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P0_DSPI_CLK frequency */
static uint64 Clock_Ip_Get_P0_DSPI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}
/* Return SPI0_CLK frequency */
static uint64 Clock_Ip_Get_SPI0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->DSPI0PCTL & GPR0_PCTL_DSPI0PCTL_PCTL_MASK) >> GPR0_PCTL_DSPI0PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SPI1_CLK frequency */
static uint64 Clock_Ip_Get_SPI1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->DSPI1PCTL & GPR0_PCTL_DSPI1PCTL_PCTL_MASK) >> GPR0_PCTL_DSPI1PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return P0_NANO_CLK frequency */
static uint64 Clock_Ip_Get_P0_NANO_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}
/* Return P0_PSI5_1US_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_1US_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return PSI5_0_CLK frequency */
static uint64 Clock_Ip_Get_PSI5_0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->PSI50PCTL & GPR0_PCTL_PSI50PCTL_PCTL_MASK) >> GPR0_PCTL_PSI50PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return P0_PSI5_S_TRIG0_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG0_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DE_MASK) >> MC_CGM_MUX_3_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P0_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P0_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P1_DSPI_CLK frequency */
static uint64 Clock_Ip_Get_P1_DSPI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}
/* Return SPI2_CLK frequency */
static uint64 Clock_Ip_Get_SPI2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->DSPI2PCTL & GPR1_PCTL_DSPI2PCTL_PCTL_MASK) >> GPR1_PCTL_DSPI2PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SPI3_CLK frequency */
static uint64 Clock_Ip_Get_SPI3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->DSPI3PCTL & GPR1_PCTL_DSPI3PCTL_PCTL_MASK) >> GPR1_PCTL_DSPI3PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SPI4_CLK frequency */
static uint64 Clock_Ip_Get_SPI4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->DSPI4PCTL & GPR1_PCTL_DSPI4PCTL_PCTL_MASK) >> GPR1_PCTL_DSPI4PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return P1_LFAST0_REF_CLK frequency */
static uint64 Clock_Ip_Get_P1_LFAST0_REF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_11_CSS & MC_CGM_MUX_11_CSS_SELSTAT_MASK) >> MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_11_DC_0 & MC_CGM_MUX_11_DC_0_DE_MASK) >> MC_CGM_MUX_11_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_11_DC_0 & (uint64)MC_CGM_MUX_11_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_11_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}
/* Return P1_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P1_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P2_DBG_ATB_CLK frequency */
static uint64 Clock_Ip_Get_P2_DBG_ATB_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}
/* Return P2_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P2_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_2->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_2->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P5_DSPI_CLK frequency */
static uint64 Clock_Ip_Get_P5_DSPI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}
/* Return SPI8_CLK frequency */
static uint64 Clock_Ip_Get_SPI8_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->DSPI8PCTL & GPR5_PCTL_DSPI8PCTL_PCTL_MASK) >> GPR5_PCTL_DSPI8PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SPI9_CLK frequency */
static uint64 Clock_Ip_Get_SPI9_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->DSPI9PCTL & GPR5_PCTL_DSPI9PCTL_PCTL_MASK) >> GPR5_PCTL_DSPI9PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return P5_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P5_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return DDR_CLK frequency */
static uint64 Clock_Ip_Get_DDR_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_6->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_6->MUX_0_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR6_PCTL->DDRPCTL & GPR6_PCTL_DDRPCTL_PCTL_MASK) >> GPR6_PCTL_DDRPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return P0_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P0_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P1_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P1_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P1_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_P1_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P1_SYS_DIV4_CLK frequency */
static uint64 Clock_Ip_Get_P1_SYS_DIV4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    return Frequency;
}

/* Return P2_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P2_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}


/* Return P2_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_P2_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P2_SYS_DIV4_CLK frequency */
static uint64 Clock_Ip_Get_P2_SYS_DIV4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    return Frequency;
}

/* Return P3_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P3_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return CE_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_CE_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P3_SYS_DIV2_NOC_CLK frequency */
static uint64 Clock_Ip_Get_P3_SYS_DIV2_NOC_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P3_SYS_DIV4_CLK frequency */
static uint64 Clock_Ip_Get_P3_SYS_DIV4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    return Frequency;
}

/* Return P4_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P4_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P4_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_P4_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return HSE_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_HSE_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P5_SYS_CLK frequency */
static uint64 Clock_Ip_Get_P5_SYS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P5_SYS_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_P5_SYS_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P5_SYS_DIV4_CLK frequency */
static uint64 Clock_Ip_Get_P5_SYS_DIV4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency = Frequency >> 2U;
    return Frequency;
}

/* Return P2_MATH_CLK frequency */
static uint64 Clock_Ip_Get_P2_MATH_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P2_MATH_DIV3_CLK frequency */
static uint64 Clock_Ip_Get_P2_MATH_DIV3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_2->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)3U;
    return Frequency;
}

/* Return GLB_LBIST_CLK frequency */
static uint64 Clock_Ip_Get_GLB_LBIST_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RTU0_CORE_CLK frequency */
static uint64 Clock_Ip_Get_RTU0_CORE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_RTU0__MC_CGM->MUX_0_CSS & RTU_MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> RTU_MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_RTU0__MC_CGM->MUX_0_DC_0 & RTU_MC_CGM_MUX_0_DC_0_DE_MASK) >> RTU_MC_CGM_MUX_0_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_RTU0__MC_CGM->MUX_0_DC_0 & (uint64)RTU_MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RTU0_CORE_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_RTU0_CORE_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_Get_RTU0_CORE_CLK_Frequency();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return RTU1_CORE_CLK frequency */
static uint64 Clock_Ip_Get_RTU1_CORE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_RTU1__MC_CGM->MUX_0_CSS & RTU_MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> RTU_MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_RTU1__MC_CGM->MUX_0_DC_0 & RTU_MC_CGM_MUX_0_DC_0_DE_MASK) >> RTU_MC_CGM_MUX_0_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_RTU1__MC_CGM->MUX_0_DC_0 & (uint64)RTU_MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)RTU_MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RTU1_CORE_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_RTU1_CORE_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_Get_RTU1_CORE_CLK_Frequency();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}

/* Return P0_PSI5_S_UTIL_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_UTIL_CLK_Frequency(void) {

    uint64 Frequency;
    if (0U == ((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_PERIPHPLL_PHI4_Frequency();
    }
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_3 & MC_CGM_MUX_2_DC_3_DE_MASK) >> MC_CGM_MUX_2_DC_3_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_3 & (uint64)MC_CGM_MUX_2_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_UTIL_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_UTIL_CLK_Frequency(void) {

    uint64 Frequency;
    if (0U == ((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_PERIPHPLL_PHI4_Frequency();
    }
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_3 & MC_CGM_MUX_2_DC_3_DE_MASK) >> MC_CGM_MUX_2_DC_3_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_3 & (uint64)MC_CGM_MUX_2_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

#if defined(CLOCK_IP_HAS_SYSTEM_CLK)
/* Return SYSTEM_CLK frequency */
static uint64 Clock_Ip_Get_SYSTEM_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableAeClkSrc[((IP_MC_ME_AE->GS & MC_ME_AE_GS_S_SYSCLK_MASK) >> MC_ME_AE_GS_S_SYSCLK_SHIFT)]();/*  Selector value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK)
/* Return SYSTEM_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_SYSTEM_DIV2_CLK_Frequency(void)
{
    return Clock_Ip_Get_SYSTEM_CLK_Frequency() >> 1U;
}
#endif

#if defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK)
/* Return SYSTEM_DIV4_MON1_CLK frequency */
static uint64 Clock_Ip_Get_SYSTEM_DIV4_MON1_CLK_Frequency(void)
{
    return Clock_Ip_Get_SYSTEM_CLK_Frequency() >> 2U;
}
#endif


/* Return ADC0_CLK frequency */
static uint64 Clock_Ip_Get_ADC0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->ADC0PCTL & GPR0_PCTL_ADC0PCTL_PCTL_MASK) >> GPR0_PCTL_ADC0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return ADC1_CLK frequency */
static uint64 Clock_Ip_Get_ADC1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->ADC1PCTL & GPR0_PCTL_ADC1PCTL_PCTL_MASK) >> GPR0_PCTL_ADC1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT0_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT0PCTL & GPR3_PCTL_PIT0PCTL_PCTL_MASK) >> GPR3_PCTL_PIT0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT1_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT1PCTL & GPR3_PCTL_PIT1PCTL_PCTL_MASK) >> GPR3_PCTL_PIT1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT2_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT2PCTL & GPR3_PCTL_PIT2PCTL_PCTL_MASK) >> GPR3_PCTL_PIT2PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT3_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT3PCTL & GPR3_PCTL_PIT3PCTL_PCTL_MASK) >> GPR3_PCTL_PIT3PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT4_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT4PCTL & GPR3_PCTL_PIT4PCTL_PCTL_MASK) >> GPR3_PCTL_PIT4PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CE_PIT5_CLK frequency */
static uint64 Clock_Ip_Get_CE_PIT5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 2U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->PIT5PCTL & GPR3_PCTL_PIT5PCTL_PCTL_MASK) >> GPR3_PCTL_PIT5PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CTU_CLK frequency */
static uint64 Clock_Ip_Get_CTU_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->CTUPCTL & GPR0_PCTL_CTUPCTL_PCTL_MASK) >> GPR0_PCTL_CTUPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMACRC0_CLK frequency */
static uint64 Clock_Ip_Get_DMACRC0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->EDMA0PCTL & GPR0_PCTL_EDMA0PCTL_PCTL_1_MASK) >> GPR0_PCTL_EDMA0PCTL_PCTL_1_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMACRC1_CLK frequency */
static uint64 Clock_Ip_Get_DMACRC1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->EDMA1PCTL & GPR1_PCTL_EDMA1PCTL_PCTL_1_MASK) >> GPR1_PCTL_EDMA1PCTL_PCTL_1_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMACRC4_CLK frequency */
static uint64 Clock_Ip_Get_DMACRC4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->EDMA4PCTL & GPR4_PCTL_EDMA4PCTL_PCTL_1_MASK) >> GPR4_PCTL_EDMA4PCTL_PCTL_1_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMACRC5_CLK frequency */
static uint64 Clock_Ip_Get_DMACRC5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->EDMA5PCTL & GPR5_PCTL_EDMA5PCTL_PCTL_1_MASK) >> GPR5_PCTL_EDMA5PCTL_PCTL_1_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMAMUX0_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->EDMA0PCTL & GPR0_PCTL_EDMA0PCTL_PCTL_2_MASK) >> GPR0_PCTL_EDMA0PCTL_PCTL_2_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMAMUX1_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->EDMA1PCTL & GPR1_PCTL_EDMA1PCTL_PCTL_2_MASK) >> GPR1_PCTL_EDMA1PCTL_PCTL_2_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMAMUX4_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->EDMA4PCTL & GPR4_PCTL_EDMA4PCTL_PCTL_2_MASK) >> GPR4_PCTL_EDMA4PCTL_PCTL_2_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return DMAMUX5_CLK frequency */
static uint64 Clock_Ip_Get_DMAMUX5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->EDMA5PCTL & GPR5_PCTL_EDMA5PCTL_PCTL_2_MASK) >> GPR5_PCTL_EDMA5PCTL_PCTL_2_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return CLKOUT0_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT0_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX0;
    if (0U == ((IP_MC_CGM_0->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency();
    }
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_10_DC_0 & (uint64)MC_CGM_MUX_10_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return CLKOUT1_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT1_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX1;
    if (0U == ((IP_MC_CGM_1->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency();
    }
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_10_DC_0 & (uint64)MC_CGM_MUX_10_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return CLKOUT2_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT2_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX2;
    if (0U == ((IP_MC_CGM_4->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency();
    }
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return CLKOUT3_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT3_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX3;
    if (0U == ((IP_MC_CGM_5->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency();
    }
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return CLKOUT4_CLK frequency */
static uint64 Clock_Ip_Get_CLKOUT4_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64ClkoutIndex = CLOCK_IP_CLKOUT_INDEX4;
    if (0U == ((IP_MC_CGM_3->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT))
    {
        Frequency = Clock_Ip_Get_FIRC_CLK_Frequency();
    }
    else
    {
        Frequency = Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency();
    }
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return EDMA_CLK frequency */
static uint64 Clock_Ip_Get_CE_EDMA_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->EDMACEPCTL & GPR3_PCTL_EDMACEPCTL_PCTL_MASK) >> GPR3_PCTL_EDMACEPCTL_PCTL_SHIFT)];    /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return EDMA0_CLK frequency */
static uint64 Clock_Ip_Get_EDMA0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->EDMA0PCTL & GPR0_PCTL_EDMA0PCTL_PCTL_0_MASK) >> GPR0_PCTL_EDMA0PCTL_PCTL_0_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return EDMA1_CLK frequency */
static uint64 Clock_Ip_Get_EDMA1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->EDMA1PCTL & GPR1_PCTL_EDMA1PCTL_PCTL_0_MASK) >> GPR1_PCTL_EDMA1PCTL_PCTL_0_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return EDMA3_CLK frequency */
static uint64 Clock_Ip_Get_EDMA3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->EDMA3PCTL & GPR3_PCTL_EDMA3PCTL_PCTL_MASK) >> GPR3_PCTL_EDMA3PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return EDMA4_CLK frequency */
static uint64 Clock_Ip_Get_EDMA4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->EDMA4PCTL & GPR4_PCTL_EDMA4PCTL_PCTL_0_MASK) >> GPR4_PCTL_EDMA4PCTL_PCTL_0_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return EDMA5_CLK frequency */
static uint64 Clock_Ip_Get_EDMA5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_0_DC_0 & (uint64)MC_CGM_MUX_0_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->EDMA5PCTL & GPR5_PCTL_EDMA5PCTL_PCTL_0_MASK) >> GPR5_PCTL_EDMA5PCTL_PCTL_0_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return ETH0_TX_MII_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_TX_MII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ENET0_CLK frequency */
static uint64 Clock_Ip_Get_ENET0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->ENET0PCTL & GPR1_PCTL_ENET0PCTL_PCTL_MASK) >> GPR1_PCTL_ENET0PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_6_DC_0 & (uint64)MC_CGM_MUX_6_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P3_CAN_PE_CLK frequency */
static uint64 Clock_Ip_Get_P3_CAN_PE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_3->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DE_MASK) >> MC_CGM_MUX_3_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN0_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN0PCTL & GPR3_PCTL_CAN0PCTL_PCTL_MASK) >> GPR3_PCTL_CAN0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN1_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN1PCTL & GPR3_PCTL_CAN1PCTL_PCTL_MASK) >> GPR3_PCTL_CAN1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN2_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN2PCTL & GPR3_PCTL_CAN2PCTL_PCTL_MASK) >> GPR3_PCTL_CAN2PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN3_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN3PCTL & GPR3_PCTL_CAN3PCTL_PCTL_MASK) >> GPR3_PCTL_CAN3PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN4_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN4PCTL & GPR3_PCTL_CAN4PCTL_PCTL_MASK) >> GPR3_PCTL_CAN4PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN5_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN5PCTL & GPR3_PCTL_CAN5PCTL_PCTL_MASK) >> GPR3_PCTL_CAN5PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN6_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN6_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN6PCTL & GPR3_PCTL_CAN6PCTL_PCTL_MASK) >> GPR3_PCTL_CAN6PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN7_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN7_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN7PCTL & GPR3_PCTL_CAN7PCTL_PCTL_MASK) >> GPR3_PCTL_CAN7PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN8_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN8_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN8PCTL & GPR3_PCTL_CAN8PCTL_PCTL_MASK) >> GPR3_PCTL_CAN8PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN9_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN9_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN9PCTL & GPR3_PCTL_CAN9PCTL_PCTL_MASK) >> GPR3_PCTL_CAN9PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN10_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN10_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN10PCTL & GPR3_PCTL_CAN10PCTL_PCTL_MASK) >> GPR3_PCTL_CAN10PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN11_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN11_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN11PCTL & GPR3_PCTL_CAN11PCTL_PCTL_MASK) >> GPR3_PCTL_CAN11PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN12_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN12_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN12PCTL & GPR3_PCTL_CAN12PCTL_PCTL_MASK) >> GPR3_PCTL_CAN12PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN13_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN13_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN13PCTL & GPR3_PCTL_CAN13PCTL_PCTL_MASK) >> GPR3_PCTL_CAN13PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN14_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN14_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN14PCTL & GPR3_PCTL_CAN14PCTL_PCTL_MASK) >> GPR3_PCTL_CAN14PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN15_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN15_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN15PCTL & GPR3_PCTL_CAN15PCTL_PCTL_MASK) >> GPR3_PCTL_CAN15PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN16_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN16_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN16PCTL & GPR3_PCTL_CAN16PCTL_PCTL_MASK) >> GPR3_PCTL_CAN16PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN17_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN17_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN17PCTL & GPR3_PCTL_CAN17PCTL_PCTL_MASK) >> GPR3_PCTL_CAN17PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN18_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN18_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN18PCTL & GPR3_PCTL_CAN18PCTL_PCTL_MASK) >> GPR3_PCTL_CAN18PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN19_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN19_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN19PCTL & GPR3_PCTL_CAN19PCTL_PCTL_MASK) >> GPR3_PCTL_CAN19PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN20_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN20_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN20PCTL & GPR3_PCTL_CAN20PCTL_PCTL_MASK) >> GPR3_PCTL_CAN20PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN21_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN21_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN21PCTL & GPR3_PCTL_CAN21PCTL_PCTL_MASK) >> GPR3_PCTL_CAN21PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN22_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN22_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN22PCTL & GPR3_PCTL_CAN22PCTL_PCTL_MASK) >> GPR3_PCTL_CAN22PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN23_CLK frequency */
static uint64 Clock_Ip_Get_FLEXCAN23_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->CAN23PCTL & GPR3_PCTL_CAN23PCTL_PCTL_MASK) >> GPR3_PCTL_CAN23PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return IIIC0_CLK frequency */
static uint64 Clock_Ip_Get_IIIC0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->I3C0PCTL & GPR0_PCTL_I3C0PCTL_PCTL_MASK) >> GPR0_PCTL_I3C0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return IIIC1_CLK frequency */
static uint64 Clock_Ip_Get_IIIC1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->I3C1PCTL & GPR1_PCTL_I3C1PCTL_PCTL_MASK) >> GPR1_PCTL_I3C1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return IIIC2_CLK frequency */
static uint64 Clock_Ip_Get_IIIC2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->I3C2PCTL & GPR4_PCTL_I3C2PCTL_PCTL_MASK) >> GPR4_PCTL_I3C2PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}


/* Return P4_LIN_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P4_LIN_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return LIN6_CLK frequency */
static uint64 Clock_Ip_Get_LIN6_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->LIN6PCTL & GPR4_PCTL_LIN6PCTL_PCTL_MASK) >> GPR4_PCTL_LIN6PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return LIN7_CLK frequency */
static uint64 Clock_Ip_Get_LIN7_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->LIN7PCTL & GPR4_PCTL_LIN7PCTL_PCTL_MASK) >> GPR4_PCTL_LIN7PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return LIN8_CLK frequency */
static uint64 Clock_Ip_Get_LIN8_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->LIN8PCTL & GPR4_PCTL_LIN8PCTL_PCTL_MASK) >> GPR4_PCTL_LIN8PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_P0_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT0SEL[((IP_GPR0->CLKOUT0SEL & GPR0_CLKOUT0SEL_MUXSEL_MASK) >> GPR0_CLKOUT0SEL_MUXSEL_SHIFT)]();/*  Selector value */
}

/* Return P0_CTU_PER_CLK frequency */
static uint64 Clock_Ip_Get_P0_CTU_PER_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_DSPI_MSC_CLK frequency */
static uint64 Clock_Ip_Get_P0_DSPI_MSC_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_1 & MC_CGM_MUX_7_DC_1_DE_MASK) >> MC_CGM_MUX_7_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_7_DC_1 & (uint64)MC_CGM_MUX_7_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_EMIOS_LCU_CLK frequency */
static uint64 Clock_Ip_Get_P0_EMIOS_LCU_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P0_GTM_CLK frequency */
static uint64 Clock_Ip_Get_P0_GTM_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_GTM_NOC_CLK frequency */
static uint64 Clock_Ip_Get_P0_GTM_NOC_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P0_GTM_TS_CLK frequency */
static uint64 Clock_Ip_Get_P0_GTM_TS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_0->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U) * 5U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P0_LIN_CLK frequency */
static uint64 Clock_Ip_Get_P0_LIN_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_0->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}


/* Return P0_PSI5_125K_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_125K_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_1 & MC_CGM_MUX_2_DC_1_DE_MASK) >> MC_CGM_MUX_2_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_1 & (uint64)MC_CGM_MUX_2_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_189K_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_189K_CLK_Frequency(void) {

    uint64 Frequency;
    uint64 Multi;
    uint64 Div;
    uint64 Fin;

    if(((IP_MC_CGM_0->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 1U)
    {
        Multi = 10U;
    }
    else if(((IP_MC_CGM_0->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 2U)
    {
        Multi = 100U;
    }
    else if(((IP_MC_CGM_0->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 3U)
    {
        Multi = 1000U;
    }
    else
    {
        Multi = 1U;
    }
    Fin = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Fin &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DE_MASK) >> MC_CGM_MUX_2_DC_2_DE_SHIFT)];         /*  Divider enable/disable */
    Div = (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_2 & (uint64)MC_CGM_MUX_2_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_2_DIV_SHIFT) + 1U);                             /*  Apply divider value */

    if(0U == Fin)
    {
        Frequency = 0;
    }
    else
    {
        if (Multi == ((uint64)(Multi * Fin) / Fin))
        {
            Frequency = ((Multi * Fin)/Div);                                        /* calculate when Multi * Fin <= 2^32-1 */
        }
        else if (Div == ((uint64)(Fin/Div) * Fin))
        {
            Frequency = ((Fin/Div)*Multi);                                          /* calculate when Fin % Div == 0*/
        }
        else
        {
            Frequency = (Fin/Div)*Multi;                        /*calculate with even part*/
            Frequency += ((Fin - ((Fin/Div)*Div) )*Multi)/Div;  /*calculate with remainder*/
        }
    }
    return Frequency;
}

/* Return P0_PSI5_S_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_5 & MC_CGM_MUX_2_DC_5_DE_MASK) >> MC_CGM_MUX_2_DC_5_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_5 & (uint64)MC_CGM_MUX_2_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_5_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_CORE_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_CORE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_5 & MC_CGM_MUX_2_DC_5_DE_MASK) >> MC_CGM_MUX_2_DC_5_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_0->MUX_2_DC_5 & (uint64)MC_CGM_MUX_2_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_5_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_TRIG1_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG1_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_1 & MC_CGM_MUX_3_DC_1_DE_MASK) >> MC_CGM_MUX_3_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_1 & (uint64)MC_CGM_MUX_3_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_TRIG2_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG2_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_2 & MC_CGM_MUX_3_DC_2_DE_MASK) >> MC_CGM_MUX_3_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_2 & (uint64)MC_CGM_MUX_3_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_TRIG3_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_TRIG3_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_3 & MC_CGM_MUX_3_DC_3_DE_MASK) >> MC_CGM_MUX_3_DC_3_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_3 & (uint64)MC_CGM_MUX_3_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_UART_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_UART_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_2_DC_4 & MC_CGM_MUX_2_DC_4_DE_MASK) >> MC_CGM_MUX_2_DC_4_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_4 & (uint64)MC_CGM_MUX_2_DC_4_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_4_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_WDOG0_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG0_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_4 & MC_CGM_MUX_3_DC_4_DE_MASK) >> MC_CGM_MUX_3_DC_4_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_4 & (uint64)MC_CGM_MUX_3_DC_4_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_4_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_WDOG1_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG1_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_5 & MC_CGM_MUX_3_DC_5_DE_MASK) >> MC_CGM_MUX_3_DC_5_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_5 & (uint64)MC_CGM_MUX_3_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_5_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_WDOG2_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG2_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_6 & MC_CGM_MUX_3_DC_6_DE_MASK) >> MC_CGM_MUX_3_DC_6_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_6 & (uint64)MC_CGM_MUX_3_DC_6_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_6_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_PSI5_S_WDOG3_CLK frequency */
static uint64 Clock_Ip_Get_P0_PSI5_S_WDOG3_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX0;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_3_DC_7 & MC_CGM_MUX_3_DC_7_DE_MASK) >> MC_CGM_MUX_3_DC_7_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_3_DC_7 & (uint64)MC_CGM_MUX_3_DC_7_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_7_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P0_REG_INTF_2X_CLK frequency */
static uint64 Clock_Ip_Get_P0_REG_INTF_2X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_1 & MC_CGM_MUX_1_DC_1_DE_MASK) >> MC_CGM_MUX_1_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_1 & (uint64)MC_CGM_MUX_1_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P1_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_P1_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT1SEL[((IP_GPR1->CLKOUT1SEL & GPR1_CLKOUT1SEL_MUXSEL_MASK) >> GPR1_CLKOUT1SEL_MUXSEL_SHIFT)]();/*  Selector value */
}


/* Return P1_DSPI60_CLK frequency */
static uint64 Clock_Ip_Get_P1_DSPI60_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return ETH_TS_CLK frequency */
static uint64 Clock_Ip_Get_ETH_TS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DE_MASK) >> MC_CGM_MUX_5_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_5_DC_0 & (uint64)MC_CGM_MUX_5_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH_TS_DIV4_CLK frequency */
static uint64 Clock_Ip_Get_ETH_TS_DIV4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DE_MASK) >> MC_CGM_MUX_5_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_1->MUX_5_DC_0 & (uint64)MC_CGM_MUX_5_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_0_DIV_SHIFT) + 1U) * 4U);                       /*  Apply divider value */
    return Frequency;
}

/* Return ETH0_REF_RMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_REF_RMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_7_DC_2 & MC_CGM_MUX_7_DC_2_DE_MASK) >> MC_CGM_MUX_7_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_7_DC_2 & (uint64)MC_CGM_MUX_7_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH0_RX_MII_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_RX_MII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH0_RX_RGMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_RX_RGMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_7_DC_1 & MC_CGM_MUX_7_DC_1_DE_MASK) >> MC_CGM_MUX_7_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_7_DC_1 & (uint64)MC_CGM_MUX_7_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH0_TX_RGMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_TX_RGMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_6_DC_1 & MC_CGM_MUX_6_DC_1_DE_MASK) >> MC_CGM_MUX_6_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_6_DC_1 & (uint64)MC_CGM_MUX_6_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH0_PS_TX_CLK frequency */
static uint64 Clock_Ip_Get_ETH0_PS_TX_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_6_DC_1 & MC_CGM_MUX_6_DC_1_DE_MASK) >> MC_CGM_MUX_6_DC_1_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_6_DC_1 & (uint64)MC_CGM_MUX_6_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_6_DC_1_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_REF_RMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_REF_RMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_9_DC_2 & MC_CGM_MUX_9_DC_2_DE_MASK) >> MC_CGM_MUX_9_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_9_DC_2 & (uint64)MC_CGM_MUX_9_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_RX_MII_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_RX_MII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_RX_RGMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_RX_RGMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_9_DC_1 & MC_CGM_MUX_9_DC_1_DE_MASK) >> MC_CGM_MUX_9_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_9_DC_1 & (uint64)MC_CGM_MUX_9_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_TX_MII_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_TX_MII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_TX_RGMII_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_TX_RGMII_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_8_DC_1 & MC_CGM_MUX_8_DC_1_DE_MASK) >> MC_CGM_MUX_8_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_8_DC_1 & (uint64)MC_CGM_MUX_8_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return ETH1_PS_TX_CLK frequency */
static uint64 Clock_Ip_Get_ETH1_PS_TX_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_8_DC_1 & MC_CGM_MUX_8_DC_1_DE_MASK) >> MC_CGM_MUX_8_DC_1_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_8_DC_1 & (uint64)MC_CGM_MUX_8_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_1_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P1_LFAST1_REF_CLK frequency */
static uint64 Clock_Ip_Get_P1_LFAST1_REF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_12_CSS & MC_CGM_MUX_12_CSS_SELSTAT_MASK) >> MC_CGM_MUX_12_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_12_DC_0 & MC_CGM_MUX_12_DC_0_DE_MASK) >> MC_CGM_MUX_12_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_12_DC_0 & (uint64)MC_CGM_MUX_12_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_12_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P1_NETC_AXI_CLK frequency */
static uint64 Clock_Ip_Get_P1_NETC_AXI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_14_CSS & MC_CGM_MUX_14_CSS_SELSTAT_MASK) >> MC_CGM_MUX_14_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_14_DC_0 & MC_CGM_MUX_14_DC_0_DE_MASK) >> MC_CGM_MUX_14_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_14_DC_0 & (uint64)MC_CGM_MUX_14_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_14_DC_0_DIV_SHIFT) + 1U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P1_LIN_CLK frequency */
static uint64 Clock_Ip_Get_P1_LIN_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_1->MUX_4_DC_0 & (uint64)MC_CGM_MUX_4_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P3_AES_CLK frequency */
static uint64 Clock_Ip_Get_P3_AES_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_3->MUX_2_DC_1 & MC_CGM_MUX_2_DC_1_DE_MASK) >> MC_CGM_MUX_2_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_2_DC_1 & (uint64)MC_CGM_MUX_2_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P3_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_P3_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT4SEL[((IP_GPR3->CLKOUT4SEL & GPR3_CLKOUT4SEL_MUXSEL_MASK) >> GPR3_CLKOUT4SEL_MUXSEL_SHIFT)]();/*  Selector value */
}


/* Return P3_DBG_TS_CLK frequency */
static uint64 Clock_Ip_Get_P3_DBG_TS_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_3->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P3_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P3_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_3->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_3->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_P4_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT2SEL[((IP_GPR4->CLKOUT2SEL & GPR4_CLKOUT2SEL_MUXSEL_MASK) >> GPR4_CLKOUT2SEL_MUXSEL_SHIFT)]();/*  Selector value */
}


/* Return P4_DSPI60_CLK frequency */
static uint64 Clock_Ip_Get_P4_DSPI60_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P4_EMIOS_LCU_CLK frequency */
static uint64 Clock_Ip_Get_P4_EMIOS_LCU_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_11_CSS & MC_CGM_MUX_11_CSS_SELSTAT_MASK) >> MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P4_LIN_CLK frequency */
static uint64 Clock_Ip_Get_P4_LIN_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_8_DC_0 & (uint64)MC_CGM_MUX_8_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_125K_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_125K_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_1 & MC_CGM_MUX_2_DC_1_DE_MASK) >> MC_CGM_MUX_2_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_1 & (uint64)MC_CGM_MUX_2_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_189K_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_189K_CLK_Frequency(void) {

    uint64 Frequency;
    uint64 Multi;
    uint64 Div;
    uint64 Fin;

    if(((IP_MC_CGM_4->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 1U)
    {
        Multi = 10U;
    }
    else if(((IP_MC_CGM_4->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 2U)
    {
        Multi = 100U;
    }
    else if(((IP_MC_CGM_4->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK) >> MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) == 3U)
    {
        Multi = 1000U;
    }
    else
    {
        Multi = 1U;
    }
    Fin = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Fin &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_2 & MC_CGM_MUX_2_DC_2_DE_MASK) >> MC_CGM_MUX_2_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Div = (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_2 & (uint64)MC_CGM_MUX_2_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */

    if(0U == Fin)
    {
        Frequency = 0;
    }
    else
    {
        if (Multi == ((uint64)(Multi * Fin) / Fin))
        {
            Frequency = ((Multi * Fin)/Div);                                        /* calculate when Multi * Fin <= 2^32-1 */
        }
        else if (Div == ((uint64)(Fin/Div) * Fin))
        {
            Frequency = ((Fin/Div)*Multi);                                          /* calculate when Fin % Div == 0*/
        }
        else
        {
            Frequency = (Fin/Div)*Multi;                        /*calculate with even part*/
            Frequency += ((Fin - ((Fin/Div)*Div) )*Multi)/Div;  /*calculate with remainder*/
        }
    }
    return Frequency;
}

/* Return P4_PSI5_S_BAUD_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_BAUD_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_5 & MC_CGM_MUX_2_DC_5_DE_MASK) >> MC_CGM_MUX_2_DC_5_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_5 & (uint64)MC_CGM_MUX_2_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_5_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_CORE_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_CORE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_5 & MC_CGM_MUX_2_DC_5_DE_MASK) >> MC_CGM_MUX_2_DC_5_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_2_DC_5 & (uint64)MC_CGM_MUX_2_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_5_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_TRIG0_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG0_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DE_MASK) >> MC_CGM_MUX_3_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_0 & (uint64)MC_CGM_MUX_3_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_TRIG1_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG1_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_1 & MC_CGM_MUX_3_DC_1_DE_MASK) >> MC_CGM_MUX_3_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_1 & (uint64)MC_CGM_MUX_3_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_TRIG2_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG2_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_2 & MC_CGM_MUX_3_DC_2_DE_MASK) >> MC_CGM_MUX_3_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_2 & (uint64)MC_CGM_MUX_3_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_TRIG3_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_TRIG3_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_3 & MC_CGM_MUX_3_DC_3_DE_MASK) >> MC_CGM_MUX_3_DC_3_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_3 & (uint64)MC_CGM_MUX_3_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_UART_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_UART_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_4 & MC_CGM_MUX_2_DC_4_DE_MASK) >> MC_CGM_MUX_2_DC_4_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_4 & (uint64)MC_CGM_MUX_2_DC_4_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_4_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_WDOG0_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG0_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_4 & MC_CGM_MUX_3_DC_4_DE_MASK) >> MC_CGM_MUX_3_DC_4_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_4 & (uint64)MC_CGM_MUX_3_DC_4_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_4_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_WDOG1_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG1_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_5 & MC_CGM_MUX_3_DC_5_DE_MASK) >> MC_CGM_MUX_3_DC_5_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_5 & (uint64)MC_CGM_MUX_3_DC_5_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_5_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_WDOG2_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG2_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_6 & MC_CGM_MUX_3_DC_6_DE_MASK) >> MC_CGM_MUX_3_DC_6_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_6 & (uint64)MC_CGM_MUX_3_DC_6_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_6_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_PSI5_S_WDOG3_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_S_WDOG3_CLK_Frequency(void) {

    uint64 Frequency;
    Clock_Ip_u64PSI5_S_UTILIndex = CLOCK_IP_CLKPSI5_S_UTIL_INDEX1;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_3_DC_7 & MC_CGM_MUX_3_DC_7_DE_MASK) >> MC_CGM_MUX_3_DC_7_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_3_DC_7 & (uint64)MC_CGM_MUX_3_DC_7_DIV_MASK) >> (uint64)MC_CGM_MUX_3_DC_7_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_QSPI0_2X_CLK frequency */
static uint64 Clock_Ip_Get_P4_QSPI0_2X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_QSPI0_1X_CLK frequency */
static uint64 Clock_Ip_Get_P4_QSPI0_1X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P4_QSPI1_2X_CLK frequency */
static uint64 Clock_Ip_Get_P4_QSPI1_2X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_9_DC_1 & MC_CGM_MUX_9_DC_1_DE_MASK) >> MC_CGM_MUX_9_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_9_DC_1 & (uint64)MC_CGM_MUX_9_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_QSPI1_1X_CLK frequency */
static uint64 Clock_Ip_Get_P4_QSPI1_1X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_9_DC_1 & MC_CGM_MUX_9_DC_1_DE_MASK) >> MC_CGM_MUX_9_DC_1_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_9_DC_1 & (uint64)MC_CGM_MUX_9_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_1_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P4_REG_INTF_2X_CLK frequency */
static uint64 Clock_Ip_Get_P4_REG_INTF_2X_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_1 & MC_CGM_MUX_1_DC_1_DE_MASK) >> MC_CGM_MUX_1_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_1 & (uint64)MC_CGM_MUX_1_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P4_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P4_SDHC_IP_CLK frequency */
static uint64 Clock_Ip_Get_P4_SDHC_IP_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P4_SDHC_IP_DIV2_CLK frequency */
static uint64 Clock_Ip_Get_P4_SDHC_IP_DIV2_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    return Frequency;
}
/* Return P5_DIPORT_CLK frequency */
static uint64 Clock_Ip_Get_P5_DIPORT_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return P5_AE_CLK frequency */
static uint64 Clock_Ip_Get_P5_AE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DE_MASK) >> MC_CGM_MUX_5_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_5_DC_0 & (uint64)MC_CGM_MUX_5_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P5_CANXL_PE_CLK frequency */
static uint64 Clock_Ip_Get_P5_CANXL_PE_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_5_DC_1 & MC_CGM_MUX_5_DC_1_DE_MASK) >> MC_CGM_MUX_5_DC_1_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_5_DC_1 & (uint64)MC_CGM_MUX_5_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_1_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}
/* Return P5_CANXL_CHI_CLK frequency */
static uint64 Clock_Ip_Get_P5_CANXL_CHI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_5_DC_2 & MC_CGM_MUX_5_DC_2_DE_MASK) >> MC_CGM_MUX_5_DC_2_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_5_DC_2 & (uint64)MC_CGM_MUX_5_DC_2_DIV_MASK) >> (uint64)MC_CGM_MUX_5_DC_2_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return P5_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_P5_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT3SEL[((IP_GPR5->CLKOUT3SEL & GPR5_CLKOUT3SEL_MUXSEL_MASK) >> GPR5_CLKOUT3SEL_MUXSEL_SHIFT)]();/*  Selector value */
}


/* Return P5_LIN_CLK frequency */
static uint64 Clock_Ip_Get_P5_LIN_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                 /*  Divider enable/disable */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_5->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U) * 2U);                       /*  Apply divider value */
    return Frequency;
}

/* Return P6_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_P6_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_6->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_6->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_6->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return PIT0_CLK frequency */
static uint64 Clock_Ip_Get_PIT0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->EDMA0PCTL & GPR0_PCTL_EDMA0PCTL_PCTL_3_MASK) >> GPR0_PCTL_EDMA0PCTL_PCTL_3_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return PIT1_CLK frequency */
static uint64 Clock_Ip_Get_PIT1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->EDMA1PCTL & GPR1_PCTL_EDMA1PCTL_PCTL_3_MASK) >> GPR1_PCTL_EDMA1PCTL_PCTL_3_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return PIT4_CLK frequency */
static uint64 Clock_Ip_Get_PIT4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->EDMA4PCTL & GPR4_PCTL_EDMA4PCTL_PCTL_3_MASK) >> GPR4_PCTL_EDMA4PCTL_PCTL_3_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return PIT5_CLK frequency */
static uint64 Clock_Ip_Get_PIT5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_5->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_5->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_5->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->EDMA5PCTL & GPR5_PCTL_EDMA5PCTL_PCTL_3_MASK) >> GPR5_PCTL_EDMA5PCTL_PCTL_3_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return P4_PSI5_1US_CLK frequency */
static uint64 Clock_Ip_Get_P4_PSI5_1US_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return PSI5_1_CLK frequency */
static uint64 Clock_Ip_Get_PSI5_1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->PSI51PCTL & GPR4_PCTL_PSI51PCTL_PCTL_MASK) >> GPR4_PCTL_PSI51PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_0 & (uint64)MC_CGM_MUX_2_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return PSI5S_0_CLK frequency */
static uint64 Clock_Ip_Get_PSI5S_0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->PSI5S0PCTL & GPR0_PCTL_PSI5S0PCTL_PCTL_MASK) >> GPR0_PCTL_PSI5S0PCTL_PCTL_SHIFT)];    /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_2_DC_3 & (uint64)MC_CGM_MUX_2_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return PSI5S_1_CLK frequency */
static uint64 Clock_Ip_Get_PSI5S_1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->PSI5S1PCTL & GPR4_PCTL_PSI5S1PCTL_PCTL_MASK) >> GPR4_PCTL_PSI5S1PCTL_PCTL_SHIFT)];    /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_2_DC_3 & (uint64)MC_CGM_MUX_2_DC_3_DIV_MASK) >> (uint64)MC_CGM_MUX_2_DC_3_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return QSPI0_CLK frequency */
static uint64 Clock_Ip_Get_QSPI0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->QSPI0PCTL & GPR4_PCTL_QSPI0PCTL_PCTL_MASK) >> GPR4_PCTL_QSPI0PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_7_DC_0 & (uint64)MC_CGM_MUX_7_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U) * 2U);                          /*  Apply divider value */
    return Frequency;
}

/* Return QSPI1_CLK frequency */
static uint64 Clock_Ip_Get_QSPI1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->QSPI1PCTL & GPR4_PCTL_QSPI1PCTL_PCTL_MASK) >> GPR4_PCTL_QSPI1PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    Frequency /= (uint64)(((((uint64)IP_MC_CGM_4->MUX_9_DC_1 & (uint64)MC_CGM_MUX_9_DC_1_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_1_DIV_SHIFT) + 1U) * 2U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RTU0_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_RTU0_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_RTU0__MC_CGM->MUX_1_CSS & RTU_MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> RTU_MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_RTU0__MC_CGM->MUX_1_DC_0 & RTU_MC_CGM_MUX_1_DC_0_DE_MASK) >> RTU_MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_RTU0__MC_CGM->MUX_1_DC_0 & (uint64)RTU_MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RTU1_REG_INTF_CLK frequency */
static uint64 Clock_Ip_Get_RTU1_REG_INTF_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_RTU1__MC_CGM->MUX_1_CSS & RTU_MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> RTU_MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_RTU1__MC_CGM->MUX_1_DC_0 & RTU_MC_CGM_MUX_1_DC_0_DE_MASK) >> RTU_MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_RTU1__MC_CGM->MUX_1_DC_0 & (uint64)RTU_MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)RTU_MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return RXLUT_CLK frequency */
static uint64 Clock_Ip_Get_RXLUT_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_3->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency = Frequency >> 1U;
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR3_PCTL->RXLUTPCTL & GPR3_PCTL_RXLUTPCTL_PCTL_MASK) >> GPR3_PCTL_RXLUTPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return P4_SDHC_CLK frequency */
static uint64 Clock_Ip_Get_P4_SDHC_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return SDHC0_CLK frequency */
static uint64 Clock_Ip_Get_SDHC0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->SDHCPCTL & GPR4_PCTL_SDHCPCTL_PCTL_MASK) >> GPR4_PCTL_SDHCPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_9_DC_0 & (uint64)MC_CGM_MUX_9_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    return Frequency;
}

/* Return SINC_CLK frequency */
static uint64 Clock_Ip_Get_SINC_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_0->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_0->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_0->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->SINCPCTL & GPR0_PCTL_SINCPCTL_PCTL_MASK) >> GPR0_PCTL_SINCPCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIPI0_CLK frequency */
static uint64 Clock_Ip_Get_SIPI0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->SIPI0PCTL & GPR1_PCTL_SIPI0PCTL_PCTL_MASK) >> GPR1_PCTL_SIPI0PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIPI1_CLK frequency */
static uint64 Clock_Ip_Get_SIPI1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->SIPI1PCTL & GPR1_PCTL_SIPI1PCTL_PCTL_MASK) >> GPR1_PCTL_SIPI1PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIUL2_0_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_Get_FIRC_CLK_Frequency();
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR0_PCTL->SIUL0PCTL & GPR0_PCTL_SIUL0PCTL_PCTL_MASK) >> GPR0_PCTL_SIUL0PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIUL2_1_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_Get_FIRC_CLK_Frequency();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->SIUL1PCTL & GPR1_PCTL_SIUL1PCTL_PCTL_MASK) >> GPR1_PCTL_SIUL1PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIUL2_4_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_4_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  =  Clock_Ip_Get_FIRC_CLK_Frequency();
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->SIUL4PCTL & GPR4_PCTL_SIUL4PCTL_PCTL_MASK) >> GPR4_PCTL_SIUL4PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SIUL2_5_CLK frequency */
static uint64 Clock_Ip_Get_SIUL2_5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_Get_FIRC_CLK_Frequency();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR5_PCTL->SIUL5PCTL & GPR5_PCTL_SIUL5PCTL_PCTL_MASK) >> GPR5_PCTL_SIUL5PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}


/* Return P4_DSPI_CLK frequency */
static uint64 Clock_Ip_Get_P4_DSPI_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    return Frequency;
}

/* Return SPI5_CLK frequency */
static uint64 Clock_Ip_Get_SPI5_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->DSPI5PCTL & GPR4_PCTL_DSPI5PCTL_PCTL_MASK) >> GPR4_PCTL_DSPI5PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SPI6_CLK frequency */
static uint64 Clock_Ip_Get_SPI6_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->DSPI6PCTL & GPR4_PCTL_DSPI6PCTL_PCTL_MASK) >> GPR4_PCTL_DSPI6PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}


/* Return SPI7_CLK frequency */
static uint64 Clock_Ip_Get_SPI7_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->DSPI7PCTL & GPR4_PCTL_DSPI7PCTL_PCTL_MASK) >> GPR4_PCTL_DSPI7PCTL_PCTL_SHIFT)];       /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SRX0_CLK frequency */
static uint64 Clock_Ip_Get_SRX0_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_1->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_1->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_1->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR1_PCTL->SRX0PCTL & GPR1_PCTL_SRX0PCTL_PCTL_MASK) >> GPR1_PCTL_SRX0PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}

/* Return SRX1_CLK frequency */
static uint64 Clock_Ip_Get_SRX1_CLK_Frequency(void) {

    uint64 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM_4->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();/*  Selector value */
    Frequency &= Clock_Ip_au32EnableDivider[((IP_MC_CGM_4->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                    /*  Divider enable/disable */
    Frequency /= (uint64)((((uint64)IP_MC_CGM_4->MUX_1_DC_0 & (uint64)MC_CGM_MUX_1_DC_0_DIV_MASK) >> (uint64)MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                          /*  Apply divider value */
    Frequency &= Clock_Ip_u64EnableGate[((IP_GPR4_PCTL->SRX1PCTL & GPR4_PCTL_SRX1PCTL_PCTL_MASK) >> GPR4_PCTL_SRX1PCTL_PCTL_SHIFT)];          /*  Apply peripheral clock gate */
    return Frequency;
}
/* Return CORE_PLL_REFCLKOUT frequency */
static uint64 Clock_Ip_Get_CORE_PLL_REFCLKOUT_Frequency(void) {

    uint64 Frequency;
    Frequency  = (((IP_CORE_PLL->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT) == 0U) ? Clock_Ip_Get_FIRC_CLK_Frequency() : Clock_Ip_Get_FXOSC_CLK_Frequency();/*  Selector value */
    return Frequency;
}

/* Return PERIPH_PLL_REFCLKOUT frequency */
static uint64 Clock_Ip_Get_PERIPH_PLL_REFCLKOUT_Frequency(void) {

    uint64 Frequency;
    Frequency  = (((IP_PERIPH_PLL->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT) == 0U) ? Clock_Ip_Get_FIRC_CLK_Frequency() : Clock_Ip_Get_FXOSC_CLK_Frequency();/*  Selector value */
    return Frequency;
}


/* Return Px_CLKOUT_SRC_CLK frequency */
static uint64 Clock_Ip_Get_Px_CLKOUT_SRC_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTableCLKOUT_MULTIPLEX[Clock_Ip_u64ClkoutIndex]();/*  Selector value */
}


/* Return Px_PSI5_S_UTIL_CLK frequency */
static uint64 Clock_Ip_Get_Px_PSI5_S_UTIL_CLK_Frequency(void) {

    return Clock_Ip_apfFreqTablePSI5_S_UTIL_MULTIPLEX[Clock_Ip_u64PSI5_S_UTILIndex]();/*  Selector value */
}

/* Return PLL_VCO frequency */
#define CLOCK_IP_PLL_VCO_MAX_FREQ             (2400000000U)
static uint64 Clock_Ip_Get_PLL_VCO(const PLLDIG_Type *Base)
{
    uint64 Fin;
    uint64 Rdiv;
    uint64 Mfi;
    uint64 Mfn;
    uint64 Fout = 0U;
    uint64 Var1;
    uint64 Var2;
    uint64 Var3;
    uint64 Var4;
    uint64 Var5;
    boolean Overflow = FALSE;

    Fin  = (((Base->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT) == 0U) ? Clock_Ip_Get_FIRC_CLK_Frequency() : Clock_Ip_Get_FXOSC_CLK_Frequency();   /* input freq */
    Rdiv = ((uint64)((uint64)Base->PLLDV & (uint64)PLLDIG_PLLDV_RDIV_MASK) >> (uint64)PLLDIG_PLLDV_RDIV_SHIFT);              /* Rdiv */
    Mfi  = ((uint64)((uint64)Base->PLLDV & (uint64)PLLDIG_PLLDV_MFI_MASK) >> (uint64)PLLDIG_PLLDV_MFI_SHIFT);                /* Mfi */
    Mfn  = ((uint64)((uint64)Base->PLLFD & (uint64)PLLDIG_PLLFD_MFN_MASK) >> (uint64)PLLDIG_PLLFD_MFN_SHIFT);                /* Mfn */


    Var1 = Mfi / Rdiv;                                      /* Mfi divided by Rdiv */
    Var2 = Mfi - (Var1 * Rdiv);                             /* Mfi minus Var1 multiplied by Rdiv */
    Var3 = (Rdiv << CLOCK_IP_MUL_BY_16384) + (Rdiv << CLOCK_IP_MUL_BY_2048);  /* Rdiv multiplied by 18432 */
    Var4 = Fin / Var3;                                      /* Fin divide by (Rdiv multiplied by 18432) */
    Var5 = Fin - (Var4 * Var3);                               /* Fin minus Var4 multiplied by (Rdiv mul 18432) */

    if (0U != Fin)
    {
        if (Var1 == ((uint64)(Var1 * Fin) / Fin))
        {
            Fout = Var1 * Fin;                                      /* Var1 multipied by Fin */
        }
        else
        {
            Overflow = TRUE;
        }

        if ((Var2 == ((uint64)(Fin * Var2) / Fin)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
        {
            Fout += Fin / Rdiv * Var2;                              /* Fin divided by Rdiv and multiplied by Var2 */
        }
        else
        {
            Overflow = TRUE;
        }

        if (0U != Var4)
        {
            if ((Mfn == ((uint64)(Var4 * Mfn) / Var4)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
            {
                Fout += Var4 * Mfn;                                     /* Mfn multiplied by Var4 */
            }
            else
            {
                Overflow = TRUE;
            }
        }

        if (0U != Mfn)
        {
            if ((Var5  == ((uint64)(Var5 * Mfn) / Mfn)) && (CLOCK_IP_PLL_VCO_MAX_FREQ >= Fout))
            {
                Fout += Var5 * Mfn / Var3;                              /* Var5 multiplied by Mfn and divide by (Rdiv mul 18432) */
            }
            else
            {
                Overflow = TRUE;
            }
        }
    }

    if (TRUE == Overflow)
    {
        Fout = 0U;
    }

    return Fout;
}

/* Return LFAST_PLL_VCO frequency */
#define CLOCK_IP_LFAST_PLL_VCO_MAX_FREQ             (2400000000U)
static uint64 Clock_Ip_Get_LFAST_PLL_VCO(const LFAST_Type *Base)
{
    uint64 Fin;
    uint32 Prediv;
    uint32 PllMode;
    uint32 Fbdiv;
    uint64 Fout = 0U;
    boolean Overflow = FALSE;

    /* Input frequency */
    if (Base == IP_LFAST_0) {
        Fin  =  Clock_Ip_Get_P1_LFAST0_REF_CLK_Frequency();
    }
    else if (Base == IP_LFAST_1) {
        Fin  =  Clock_Ip_Get_P1_LFAST1_REF_CLK_Frequency();
    }
    else {
        Fin = 0U;
    }

    Prediv = ((Base->PLLCR & LFAST_PLLCR_PREDIV_MASK) >> LFAST_PLLCR_PREDIV_SHIFT) + 1U;              /* Prediv */
    Fbdiv  = ((Base->PLLCR & LFAST_PLLCR_FBDIV_MASK) >> LFAST_PLLCR_FBDIV_SHIFT);                /* multiplied */
    PllMode = ((Base->PLLCR & LFAST_PLLCR_FDIVEN_MASK) >> LFAST_PLLCR_FDIVEN_SHIFT);             /* Pll mode */

    if (0U != Fin)
    {
        if (Fbdiv == ((uint64)(Fin * Fbdiv) / Fin))
        {
            Fout += (uint64)((Fin * Fbdiv )/ Prediv);
        }
        else
        {
            Overflow = TRUE;
        }

        if ((PllMode == ((uint64)(Fin * PllMode) / Fin)) && (CLOCK_IP_LFAST_PLL_VCO_MAX_FREQ >= Fout))
        {
            if(((Fin / Prediv) > ((Fin * PllMode)/(2U*Prediv))) && (Fout < (Fout + (Fin/Prediv))))
            {
                /*Fout += (Fin/Prediv) when PllMode = 0 and Fout += (Fin/(2*Prediv)) when PllMode = 1*/
                Fout += (uint64)((Fin/Prediv) - ((Fin * PllMode)/(2U*Prediv)));
            }
            else
            {
                Overflow = TRUE;
            }
        }
        else
        {
            Overflow = TRUE;
        }
    }

    if ((1U != ((Base->PLLLSR & LFAST_PLLLSR_PLDCR_MASK) >> LFAST_PLLLSR_PLDCR_SHIFT)) || (TRUE == Overflow))
    {
        Fout = 0U;
    }

    return Fout;
}

/* Return DFS_OUTPUT frequency */
static uint64 Clock_Ip_Get_DFS_OUTPUT(const DFS_Type *Base, uint32 Channel, uint64 Fin)
{
    uint32 Mfi;
    uint32 Mfn;
    uint32 Divider;
    uint64 DividerResult;
    uint64 DividerModulo;
    uint64 Fout = 0U;
    boolean Overflow = FALSE;

    Mfi = ((Base->DVPORT[Channel] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* Mfi */
    Mfn = ((Base->DVPORT[Channel] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* Mfn */

    Divider = ((Mfi << CLOCK_IP_MUL_BY_32) + (Mfi << CLOCK_IP_MUL_BY_4) + Mfn);               /* mfi multiplied by 36 add mfn */
    DividerResult = (uint64)((Divider != 0U) ? (Fin / Divider) : 0U);                 /* Fin divide by Divider */
    DividerModulo = (uint64)(Fin - (Divider * DividerResult));                        /* Fin minus DividerResult multiplied by Divider */

    if (Divider != 0U)
    {
        if ((DividerResult << CLOCK_IP_MUL_BY_16) <= ((DividerResult << CLOCK_IP_MUL_BY_16) + (DividerResult << CLOCK_IP_MUL_BY_2)))
        {
            Fout += (DividerResult << CLOCK_IP_MUL_BY_16) + (DividerResult << CLOCK_IP_MUL_BY_2);
        }
        else
        {
            Overflow = TRUE;
        }

        if (Fout <= (Fout + (((DividerModulo << CLOCK_IP_MUL_BY_16) + (DividerModulo << CLOCK_IP_MUL_BY_2)) / Divider)))
        {
            Fout += ((DividerModulo << CLOCK_IP_MUL_BY_16) + (DividerModulo << CLOCK_IP_MUL_BY_2)) / Divider;
        }
        else
        {
            Overflow = TRUE;
        }
    }

    if (TRUE == Overflow)
    {
        Fout = 0U;
    }

    return Fout;
}

/* Get external frequency */
void Clock_Ip_SetExternalOscillatorFrequency(Clock_Ip_NameType ExtOscName, uint64 Frequency)
{
    (void)ExtOscName;
    Clock_Ip_u64Fxosc = Frequency;
}

/* Return LFAST0_PLL_CLK_ frequency */
static uint64 Clock_Ip_Get_LFAST0_PLL_CLK_Frequency(void)
{
    return (((IP_LFAST_0->PLLLSR & LFAST_PLLLSR_PLDCR_MASK) >> LFAST_PLLLSR_PLDCR_SHIFT) == 1U) ? Clock_Ip_Get_LFAST_PLL_VCO(IP_LFAST_0) : 0U;
}
/* Return LFAST0_PLL_CLK_ frequency */
static uint64 Clock_Ip_Get_LFAST1_PLL_CLK_Frequency(void)
{
    return (((IP_LFAST_1->PLLLSR & LFAST_PLLLSR_PLDCR_MASK) >> LFAST_PLLLSR_PLDCR_SHIFT) == 1U) ? Clock_Ip_Get_LFAST_PLL_VCO(IP_LFAST_1) : 0U;
}
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/* Return frequency value */
uint64 Clock_Ip_GetFreq(Clock_Ip_NameType ClockName)
{
    return Clock_Ip_apfFreqTable[ClockName]();
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#endif  /* #if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON)) */

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/* Set frequency value for External Signal */
void Clock_Ip_SetExternalSignalFrequency(Clock_Ip_NameType SignalName, uint64 Frequency)
{
#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))
    uint32 Index;
    for (Index = 0U; Index < CLOCK_IP_EXT_SIGNALS_NO; Index++)
    {
        if (SignalName == Clock_Ip_axExtSignalFreqEntries[Index].Name)
        {
            Clock_Ip_axExtSignalFreqEntries[Index].Frequency = Frequency;
            break;
        }
    }
#else
    (void)SignalName;
    (void)Frequency;
#endif
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#endif /* (CLOCK_IP_PLATFORM_SPECIFIC) */


#ifdef __cplusplus
}
#endif

/** @} */

