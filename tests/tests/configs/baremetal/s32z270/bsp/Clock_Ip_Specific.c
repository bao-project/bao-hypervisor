/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Specific.c
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

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_SPECIFIC_VENDOR_ID_C                      43
#define CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_SPECIFIC_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_SPECIFIC_SW_MINOR_VERSION_C               0
#define CLOCK_IP_SPECIFIC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_SPECIFIC_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Specific.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Specific.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Specific.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_SPECIFIC_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_SPECIFIC_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Specific.c and Clock_Ip_Private.h are different"
#endif

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Clock_Ip_Specific.c file and RegLockMacros.h file are of the same Autosar version */
    #if ((CLOCK_IP_SPECIFIC_AR_RELEASE_MAJOR_VERSION    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (CLOCK_IP_SPECIFIC_AR_RELEASE_MINOR_VERSION    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Clock_Ip_Specific.c and RegLockMacros.h are different"
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

#define CLOCK_IP_DFS_DVPORT      (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U))
#define CLOCK_IP_DFS_PORT_RESET  (DFS_PORTRESET_RESET0_MASK | DFS_PORTRESET_RESET1_MASK | DFS_PORTRESET_RESET2_MASK | DFS_PORTRESET_RESET3_MASK | DFS_PORTRESET_RESET4_MASK | DFS_PORTRESET_RESET5_MASK)

#define CLOCK_IP_RTU0_CORE_CLK_MAX_FREQUENCY 900000000U
#define CLOCK_IP_RTU0_CORE_CLK_THRESHOLD0_FREQUENCY (CLOCK_IP_RTU0_CORE_CLK_MAX_FREQUENCY>>2U)
#define CLOCK_IP_RTU0_CORE_CLK_THRESHOLD1_FREQUENCY (CLOCK_IP_RTU0_CORE_CLK_THRESHOLD0_FREQUENCY*(2U))
#define CLOCK_IP_RTU0_CORE_CLK_THRESHOLD2_FREQUENCY (CLOCK_IP_RTU0_CORE_CLK_THRESHOLD0_FREQUENCY*(3U))

#define CLOCK_IP_RTU1_CORE_CLK_MAX_FREQUENCY 900000000U
#define CLOCK_IP_RTU1_CORE_CLK_THRESHOLD0_FREQUENCY (CLOCK_IP_RTU1_CORE_CLK_MAX_FREQUENCY>>2U)
#define CLOCK_IP_RTU1_CORE_CLK_THRESHOLD1_FREQUENCY (CLOCK_IP_RTU1_CORE_CLK_THRESHOLD0_FREQUENCY*(2U))
#define CLOCK_IP_RTU1_CORE_CLK_THRESHOLD2_FREQUENCY (CLOCK_IP_RTU1_CORE_CLK_THRESHOLD0_FREQUENCY*(3U))

#define CLOCK_IP_SMU_M33_CORE_CLK_MAX_FREQUENCY 400000000U
#define CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD0_FREQUENCY (CLOCK_IP_SMU_M33_CORE_CLK_MAX_FREQUENCY>>2U)
#define CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD1_FREQUENCY (CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD0_FREQUENCY*(2U))
#define CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD2_FREQUENCY (CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD0_FREQUENCY*(3U))

#define CLOCK_IP_CE_M33_CORE_CLK_MAX_FREQUENCY 405000000U
#define CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD0_FREQUENCY (CLOCK_IP_CE_M33_CORE_CLK_MAX_FREQUENCY>>2U)
#define CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD1_FREQUENCY (CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD0_FREQUENCY*(2U))
#define CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD2_FREQUENCY (CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD0_FREQUENCY*(3U))


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

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES
static uint32 Clock_Ip_GetIwsSetting(uint32 ConfiguredCoreClockFrequnecy,
                                     uint32 Threshold0,
                                     uint32 Threshold1,
                                     uint32 Threshold2);
#endif

static void Clock_Ip_SpecificPlatformInitClock(Clock_Ip_ClockConfigType const * Config);
/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES
/* Calculate ram wait states value */
static uint32 Clock_Ip_GetIwsSetting(uint32 ConfiguredCoreClockFrequnecy, uint32 Threshold0, uint32 Threshold1, uint32 Threshold2)
{
    uint32 IwsSetting = 0U;

    if (ConfiguredCoreClockFrequnecy >= Threshold2)
    {
        IwsSetting = 3U;
    }
    else if (ConfiguredCoreClockFrequnecy >= Threshold1)
    {
        IwsSetting = 2U;
    }
    else if (ConfiguredCoreClockFrequnecy >= Threshold0)
    {
        IwsSetting = 1U;
    }
    else
    {
        /* Nothing else to be done. */
    }

    return IwsSetting;
}


#endif

static void Clock_Ip_SpecificPlatformInitClock(Clock_Ip_ClockConfigType const * Config)
{
    uint32 RegValue;
    uint32 CoreDfsIsInReset = IP_CORE_DFS->CTL & DFS_CTL_DFS_RESET_MASK;            /* if master core dfs is in reset */
    uint32 PeriphDfsIsInReset = IP_PERIPH_DFS->CTL & DFS_CTL_DFS_RESET_MASK;        /* if master periph dfs is in reset */

    (void)Config;

    if ((CoreDfsIsInReset != 0U) && (PeriphDfsIsInReset != 0U))
    {
        if ((IP_CORE_PLL->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if CORE_PLL is not enabled */
        {
            IP_CORE_PLL->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            RegValue = IP_CORE_PLL->PLLDV;
            RegValue &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            IP_CORE_PLL->PLLDV = (RegValue | (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U)) );          /* /1 * 30 */

            IP_CORE_PLL->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */
            IP_CORE_PLL->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start CORE_PLL */
        }

        if ((IP_PERIPH_PLL->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if PERIPH_PLL is not enabled */
        {
            IP_PERIPH_PLL->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            RegValue = IP_PERIPH_PLL->PLLDV;
            RegValue &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            IP_PERIPH_PLL->PLLDV = (RegValue | (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U)) );          /* /1 * 30 */

            IP_PERIPH_PLL->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */
            IP_PERIPH_PLL->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start PERIPH_PLL */
        }

        IP_CORE_DFS->PORTRESET |= CLOCK_IP_DFS_PORT_RESET;
        IP_CORE_DFS->DVPORT[0U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[1U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[2U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[3U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[4U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[5U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        IP_CORE_DFS->PORTRESET &= ~CLOCK_IP_DFS_PORT_RESET;

        IP_PERIPH_DFS->PORTRESET |= CLOCK_IP_DFS_PORT_RESET;
        IP_PERIPH_DFS->DVPORT[0U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[1U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[2U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[3U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[4U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[5U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        IP_PERIPH_DFS->PORTRESET &= ~CLOCK_IP_DFS_PORT_RESET;
    }
    else if (CoreDfsIsInReset != 0U)
    {
        if ((IP_CORE_PLL->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if CORE_PLL is not enabled */
        {
            IP_CORE_PLL->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            RegValue = IP_CORE_PLL->PLLDV;
            RegValue &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            IP_CORE_PLL->PLLDV = (RegValue | (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U)) );          /* /1 * 30 */

            IP_CORE_PLL->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */
            IP_CORE_PLL->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start CORE_PLL */
        }

        IP_CORE_DFS->PORTRESET |= CLOCK_IP_DFS_PORT_RESET;
        IP_CORE_DFS->DVPORT[0U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[1U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[2U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[3U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[4U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->DVPORT[5U] = CLOCK_IP_DFS_DVPORT;
        IP_CORE_DFS->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        IP_CORE_DFS->PORTRESET &= ~CLOCK_IP_DFS_PORT_RESET;
    }
    else if (PeriphDfsIsInReset != 0U)
    {
        if ((IP_PERIPH_PLL->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if PERIPH_PLL is not enabled */
        {
            IP_PERIPH_PLL->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            RegValue = IP_PERIPH_PLL->PLLDV;
            RegValue &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            IP_PERIPH_PLL->PLLDV = (RegValue | (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U)) );          /* /1 * 30 */

            IP_PERIPH_PLL->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */
            IP_PERIPH_PLL->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start PERIPH_PLL */
        }

        IP_PERIPH_DFS->PORTRESET |= CLOCK_IP_DFS_PORT_RESET;
        IP_PERIPH_DFS->DVPORT[0U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[1U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[2U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[3U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[4U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->DVPORT[5U] = CLOCK_IP_DFS_DVPORT;
        IP_PERIPH_DFS->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        IP_PERIPH_DFS->PORTRESET &= ~CLOCK_IP_DFS_PORT_RESET;
    }
    else
    {
        /* periph Dfs and core Dfs are not in reset */
    }
    /* enable clock gate for DDR PLL PHI0 to input CLKOUT0 clock source */
    IP_GPR0->CLKOUT0SEL |= GPR0_CLKOUT0SEL_CGEN(1U);
}


#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #if (defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK))
void Clock_Ip_SpecificSetUserAccessAllowed(void)
{

#if (defined(MCAL_CMU_AE_REG_PROT_AVAILABLE))
  #if(STD_ON == MCAL_CMU_AE_REG_PROT_AVAILABLE)

    /* CMU_AE SetUserAccessAllowed */
    #if (defined(IP_CMU_FC_AE_1_BASE) || defined(IP_CMU_FC_AE_2_BASE))
    SET_USER_ACCESS_ALLOWED(IP_CMU_FM_AE_0_BASE, CMU_AE_PROT_MEM_U32);
    #endif

#endif
#endif /* MCAL_CMU_AE_REG_PROT_AVAILABLE */

}
#endif /* (defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK)) */
#endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES


/* Clock start rom section code */
#define MCU_START_SEC_CODE_AC
#include "Mcu_MemMap.h"

/* Set Ram IWS */
void Clock_Ip_SRAMControllerSetRamIWS(uint32 SmuM33CoreClk_IwsSetting, uint32 Rtu0CoreClk_IwsSetting, uint32 Rtu1CoreClk_IwsSetting, uint32 CeM33CoreClk_IwsSetting)
{
#if (1 == 1)
    (void)SmuM33CoreClk_IwsSetting;
    (void)Rtu0CoreClk_IwsSetting;
    (void)Rtu1CoreClk_IwsSetting;
    (void)CeM33CoreClk_IwsSetting;
#else
    IP_SMU__SRAMCTL_0->RAMCR |= ((IP_SMU__SRAMCTL_0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(SmuM33CoreClk_IwsSetting));
    IP_SMU__SRAMCTL_1->RAMCR |= ((IP_SMU__SRAMCTL_1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(SmuM33CoreClk_IwsSetting));
    IP_SMU__SRAMCTL_2->RAMCR |= ((IP_SMU__SRAMCTL_2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(SmuM33CoreClk_IwsSetting));
    IP_SMU__SRAMCTL_3->RAMCR |= ((IP_SMU__SRAMCTL_3->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(SmuM33CoreClk_IwsSetting));
    
    IP_RTU0__SRAMCTL_C0->RAMCR |= ((IP_RTU0__SRAMCTL_C0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C1->RAMCR |= ((IP_RTU0__SRAMCTL_C1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C2->RAMCR |= ((IP_RTU0__SRAMCTL_C2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C3->RAMCR |= ((IP_RTU0__SRAMCTL_C3->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C4->RAMCR |= ((IP_RTU0__SRAMCTL_C4->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C5->RAMCR |= ((IP_RTU0__SRAMCTL_C5->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_C6->RAMCR |= ((IP_RTU0__SRAMCTL_C6->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_D0->RAMCR |= ((IP_RTU0__SRAMCTL_D0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_D1->RAMCR |= ((IP_RTU0__SRAMCTL_D1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    IP_RTU0__SRAMCTL_D2->RAMCR |= ((IP_RTU0__SRAMCTL_D2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu0CoreClk_IwsSetting));
    
    IP_RTU1__SRAMCTL_C0->RAMCR |= ((IP_RTU1__SRAMCTL_C0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C1->RAMCR |= ((IP_RTU1__SRAMCTL_C1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C2->RAMCR |= ((IP_RTU1__SRAMCTL_C2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C3->RAMCR |= ((IP_RTU1__SRAMCTL_C3->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C4->RAMCR |= ((IP_RTU1__SRAMCTL_C4->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C5->RAMCR |= ((IP_RTU1__SRAMCTL_C5->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_C6->RAMCR |= ((IP_RTU1__SRAMCTL_C6->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_D0->RAMCR |= ((IP_RTU1__SRAMCTL_D0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_D1->RAMCR |= ((IP_RTU1__SRAMCTL_D1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));
    IP_RTU1__SRAMCTL_D2->RAMCR |= ((IP_RTU1__SRAMCTL_D2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(Rtu1CoreClk_IwsSetting));

    IP_CE_SRAMCTL_0->RAMCR |= ((IP_CE_SRAMCTL_0->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(CeM33CoreClk_IwsSetting));
    IP_CE_SRAMCTL_1->RAMCR |= ((IP_CE_SRAMCTL_1->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(CeM33CoreClk_IwsSetting));
    IP_CE_SRAMCTL_2->RAMCR |= ((IP_CE_SRAMCTL_2->RAMCR & ~SRAMCTL_RAMCR_IWS_MASK) | SRAMCTL_RAMCR_IWS(CeM33CoreClk_IwsSetting));
#endif
}

/* Clock stop rom section code */
#define MCU_STOP_SEC_CODE_AC
#include "Mcu_MemMap.h"
#endif

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
/* Clock start rom section code */
#define MCU_START_SEC_CODE_AC
#include "Mcu_MemMap.h"


#ifdef CLOCK_IP_HAS_RAM_WAIT_STATES
/* Function set ram wait states */
void Clock_Ip_SetRamWaitStates(void)
{
   /* Process configured frequency values */
    uint32 Rtu0CoreClk_IwsSetting = 0U;
    uint32 Rtu0CoreClk_ConfiguredFrequency = 0U;

    uint32 Rtu1CoreClk_IwsSetting = 0U;
    uint32 Rtu1CoreClk_ConfiguredFrequency = 0U;

    uint32 SmuM33CoreClk_IwsSetting = 0U;
    uint32 SmuM33CoreClk_ConfiguredFrequency = 0U;

    uint32 CeM33CoreClk_IwsSetting = 0U;
    uint32 CeM33CoreClk_ConfiguredFrequency = 0U;

#if defined(CLOCK_IP_HAS_RTU0_CORE_CLK)
    Rtu0CoreClk_ConfiguredFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[RTU0_CORE_CLK]].ConfiguredFrequencyValue;
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_CLK)
    Rtu1CoreClk_ConfiguredFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[RTU1_CORE_CLK]].ConfiguredFrequencyValue;
#endif
#if defined(CLOCK_IP_HAS_SMU_M33_CORE_CLK)
    SmuM33CoreClk_ConfiguredFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[SMU_M33_CORE_CLK]].ConfiguredFrequencyValue;
#endif
#if defined(CLOCK_IP_HAS_CE_M33_CORE_CLK)
    CeM33CoreClk_ConfiguredFrequency = (*Clock_Ip_pxConfig->ConfiguredFrequencies)[Clock_Ip_FreqIds[CE_M33_CORE_CLK]].ConfiguredFrequencyValue;
#endif

#if (defined(CLOCK_IP_DEV_ERROR_DETECT) && (CLOCK_IP_DEV_ERROR_DETECT == STD_ON))
#if defined(CLOCK_IP_HAS_RTU0_CORE_CLK)
    CLOCK_IP_DEV_ASSERT(Rtu0CoreClk_ConfiguredFrequency != 0U);
#endif
#if defined(CLOCK_IP_HAS_RTU1_CORE_CLK)
    CLOCK_IP_DEV_ASSERT(Rtu1CoreClk_ConfiguredFrequency != 0U);
#endif
#if defined(CLOCK_IP_HAS_SMU_M33_CORE_CLK)
    CLOCK_IP_DEV_ASSERT(SmuM33CoreClk_ConfiguredFrequency != 0U);
#endif
#if defined(CLOCK_IP_HAS_CE_M33_CORE_CLK)
    CLOCK_IP_DEV_ASSERT(CeM33CoreClk_ConfiguredFrequency != 0U);
#endif
#endif

    SmuM33CoreClk_IwsSetting = Clock_Ip_GetIwsSetting(SmuM33CoreClk_ConfiguredFrequency, CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD0_FREQUENCY, CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD1_FREQUENCY, CLOCK_IP_SMU_M33_CORE_CLK_THRESHOLD2_FREQUENCY);
    Rtu0CoreClk_IwsSetting = Clock_Ip_GetIwsSetting(Rtu0CoreClk_ConfiguredFrequency, CLOCK_IP_RTU0_CORE_CLK_THRESHOLD0_FREQUENCY, CLOCK_IP_RTU0_CORE_CLK_THRESHOLD1_FREQUENCY, CLOCK_IP_RTU0_CORE_CLK_THRESHOLD2_FREQUENCY);
    Rtu1CoreClk_IwsSetting = Clock_Ip_GetIwsSetting(Rtu1CoreClk_ConfiguredFrequency, CLOCK_IP_RTU1_CORE_CLK_THRESHOLD0_FREQUENCY, CLOCK_IP_RTU1_CORE_CLK_THRESHOLD1_FREQUENCY, CLOCK_IP_RTU1_CORE_CLK_THRESHOLD2_FREQUENCY);
    CeM33CoreClk_IwsSetting = Clock_Ip_GetIwsSetting(CeM33CoreClk_ConfiguredFrequency, CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD0_FREQUENCY, CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD1_FREQUENCY, CLOCK_IP_CE_M33_CORE_CLK_THRESHOLD2_FREQUENCY);

    #ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
        #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
            OsIf_Trusted_Call4params(Clock_Ip_SRAMControllerSetRamIWS, (SmuM33CoreClk_IwsSetting), (Rtu0CoreClk_IwsSetting), (Rtu1CoreClk_IwsSetting), (CeM33CoreClk_IwsSetting));
        #else
            Clock_Ip_SRAMControllerSetRamIWS(SmuM33CoreClk_IwsSetting, Rtu0CoreClk_IwsSetting, Rtu1CoreClk_IwsSetting, CeM33CoreClk_IwsSetting);
        #endif
    #else
        Clock_Ip_SRAMControllerSetRamIWS(SmuM33CoreClk_IwsSetting, Rtu0CoreClk_IwsSetting, Rtu1CoreClk_IwsSetting, CeM33CoreClk_IwsSetting);
    #endif
}
#endif /* CLOCK_IP_HAS_RAM_WAIT_STATES */

void Clock_Ip_McMeEnterKey(void)
{
    IP_MC_ME->CTL_KEY = 0x5AF0;                                         /* Enter key */

    IP_MC_ME->CTL_KEY = 0xA50F;                                         /* Enter inverted key */
}


void Clock_Ip_Command(Clock_Ip_ClockConfigType const * Config, Clock_Ip_CommandType Command)
{
    switch(Command)
    {
        case CLOCK_IP_INITIALIZE_PLATFORM_COMMAND:
            Clock_Ip_SpecificPlatformInitClock(Config);
            break;
#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
        #if (defined(CLOCK_IP_HAS_SYSTEM_DIV2_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON1_CLK) || defined(CLOCK_IP_HAS_SYSTEM_DIV4_MON2_CLK))
        case CLOCK_IP_SET_USER_ACCESS_ALLOWED_COMMAND:
            OsIf_Trusted_Call(Clock_Ip_SpecificSetUserAccessAllowed);
            break;
        #endif
    #endif
#endif
        default:
            /* Command is not implemented on this platform */
            break;
    }
}


/* Clock stop rom section code */
#define MCU_STOP_SEC_CODE_AC
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

