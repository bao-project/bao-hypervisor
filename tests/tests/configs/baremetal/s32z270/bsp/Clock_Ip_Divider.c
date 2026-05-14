/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Divider.c
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


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_DIVIDER_VENDOR_ID_C                      43
#define CLOCK_IP_DIVIDER_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_DIVIDER_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_DIVIDER_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_DIVIDER_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_DIVIDER_SW_MINOR_VERSION_C               0
#define CLOCK_IP_DIVIDER_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Divider.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_DIVIDER_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Divider.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Divider.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_DIVIDER_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_DIVIDER_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_DIVIDER_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Divider.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Divider.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_DIVIDER_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_DIVIDER_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_DIVIDER_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Divider.c and Clock_Ip_Private.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void Clock_Ip_Callback_DividerEmpty(Clock_Ip_DividerConfigType const* Config);
#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE
static void Clock_Ip_SetCgmXDeDivStatWithoutPhase(Clock_Ip_DividerConfigType const* Config);
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_FMT_STAT_WITHOUT_PHASE
static void Clock_Ip_SetCgmXDeDivFmtStatWithoutPhase(Clock_Ip_DividerConfigType const* Config);
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WITH_TRIGGER
static void Clock_Ip_SetCgmXDeDivStatWithoutPhaseWithTrigger(Clock_Ip_DividerConfigType const* Config);
#endif

#ifdef CLOCK_IP_PLLDIG_PLL0DIV_DE_DIV_OUTPUT
static void Clock_Ip_SetPlldigPll0divDeDivOutput(Clock_Ip_DividerConfigType const* Config);
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/* Clock start section code */

#include "Mcu_MemMap.h"

static void Clock_Ip_Callback_DividerEmpty(Clock_Ip_DividerConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}

#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE
static void Clock_Ip_SetCgmXDeDivStatWithoutPhase(Clock_Ip_DividerConfigType const* Config)
{
    uint32 Instance;
    uint32 SelectorIndex;
    uint32 DividerIndex;

    uint32 DividerMask;
    uint32 DividerShift;

    uint32 RegValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        SelectorIndex = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_SELECTOR_INDEX];
        DividerIndex  = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];
        DividerMask   = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueMask;
        DividerShift  = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueShift;
        RegValue = Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex];

        /* Program divider value */
        if (Config->Value != 0U)
        {
            RegValue &= ~DividerMask;
            RegValue |= (((Config->Value-1U) << DividerShift) & DividerMask);

        #ifdef CLOCK_IP_DIVIDER_HAVE_DIV_FMT
            if((Instance == 0U)  && (SelectorIndex == 2U) && (DividerIndex == 2U))
            {
                RegValue &= ~MC_CGM_MUX_2_DC_2_DIV_FMT_MASK;
            }
            else if((Instance == 4U) && (SelectorIndex == 2U) && (DividerIndex == 2U))
            {
                RegValue &= ~MC_CGM_MUX_2_DC_2_DIV_FMT_MASK;
            }
            else
            {
                /* Do nothing */
            }
        #endif

            /* Enable divider */
            RegValue |= MC_CGM_MUX_DC_DE_MASK;
        }
        else
        {
            RegValue &= ~MC_CGM_MUX_DC_DE_MASK;
        }

        Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex] = RegValue;

        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait for acknowledge to be cleared. */
        do
        {
            DividerStatus = (Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING == DividerStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
        }
    }
    else
    {
        (void)Instance;
        (void)SelectorIndex;
        (void)DividerIndex;
        (void)DividerMask;
        (void)DividerShift;
        (void)RegValue;
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)DividerStatus;
    }
}
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_FMT_STAT_WITHOUT_PHASE
static void Clock_Ip_SetCgmXDeDivFmtStatWithoutPhase(Clock_Ip_DividerConfigType const* Config)
{
    uint32 Instance;
    uint32 SelectorIndex;
    uint32 DividerIndex;

    uint32 DividerMask;
    uint32 DividerShift;

    uint32 RegValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        SelectorIndex = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_SELECTOR_INDEX];
        DividerIndex  = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];
        DividerMask  = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueMask;
        DividerShift = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueShift;
        RegValue = Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex];

        /* Program divider value */
        if (Config->Value != 0U)
        {
            RegValue &= ~DividerMask;
            RegValue |= (((Config->Value-1U) << DividerShift) & DividerMask);

            RegValue &= ~MC_CGM_MUX_2_DC_2_DIV_FMT_MASK;
            RegValue |= (((uint32)(Config->Options[0]) << MC_CGM_MUX_2_DC_2_DIV_FMT_SHIFT) & MC_CGM_MUX_2_DC_2_DIV_FMT_MASK);

            /* Enable divider */
            RegValue |= MC_CGM_MUX_DC_DE_MASK;
        }
        else
        {
            RegValue &= ~MC_CGM_MUX_DC_DE_MASK;
        }

        Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex] = RegValue;

        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait for acknowledge to be cleared. */
        do
        {
            DividerStatus = (Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING == DividerStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
        }
    }
    else
    {
        (void)Instance;
        (void)SelectorIndex;
        (void)DividerIndex;
        (void)DividerMask;
        (void)DividerShift;
        (void)RegValue;
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)DividerStatus;
    }
}
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WITH_TRIGGER
static void Clock_Ip_SetCgmXDeDivStatWithoutPhaseWithTrigger(Clock_Ip_DividerConfigType const* Config)
{
    uint32 Instance;
    uint32 SelectorIndex;
    uint32 DividerIndex;

    uint32 DividerMask;
    uint32 DividerShift;

    uint32 RegValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        SelectorIndex = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_SELECTOR_INDEX];
        DividerIndex  = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];
        DividerMask  = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueMask;
        DividerShift = Clock_Ip_axFeatureExtensions[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_EXTENSION_INDEX]].DividerValueShift;
        RegValue = Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex];


        /* Program divider value */
        if (Config->Value != 0U)
        {
            RegValue &= ~DividerMask;
            RegValue |= ((Config->Value-1U) << DividerShift) & DividerMask;

            /* Enable divider */
            RegValue |= MC_CGM_MUX_DC_DE_MASK;
        }
        else
        {
            RegValue &= ~MC_CGM_MUX_DC_DE_MASK;
        }

        Clock_Ip_apxCgm[Instance][SelectorIndex]->Divider[DividerIndex] = RegValue;

        /* Immediate update is triggered. */
        if ((Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_TRIG_CTRL & MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK) != MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE)
        {
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            /* Wait for acknowledge to be cleared. */
            do
            {
                DividerStatus = (Clock_Ip_apxCgm[Instance][SelectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while ((MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING == DividerStatus) && (FALSE == TimeoutOccurred));
        }

        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, Config->Name);
        }
    }
    else
    {
        (void)Instance;
        (void)SelectorIndex;
        (void)DividerIndex;
        (void)DividerMask;
        (void)DividerShift;
        (void)RegValue;
        (void)TimeoutOccurred;
        (void)StartTime;
        (void)ElapsedTime;
        (void)TimeoutTicks;
        (void)DividerStatus;
    }
}
#endif

#ifdef CLOCK_IP_PLLDIG_PLL0DIV_DE_DIV_OUTPUT
static void Clock_Ip_SetPlldigPll0divDeDivOutput(Clock_Ip_DividerConfigType const* Config)
{

    uint32 Instance;
    uint32 DividerIndex;
    uint32 RegValue;

    if (NULL_PTR != Config)
    {
        Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        DividerIndex  = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];
        /* Check that divider is already disabled */
        CLOCK_IP_DEV_ASSERT(!(Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] & PLLDIG_PLLODIV_DE_MASK));

        /* Check if divider is enabled */
        if (Config->Value != 0U)
        {
            RegValue = Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex];
            RegValue |= PLLDIG_PLLODIV_DE_MASK;
            RegValue &= ~PLLDIG_PLLODIV_DIV_MASK;
            RegValue |= PLLDIG_PLLODIV_DIV(Config->Value - 1U);
#ifdef CLOCK_IP_HAS_PLL_PLLODIV_PHASE
            RegValue &= ~PLLDIG_PLLODIV_PHASE_MASK;
            RegValue |= PLLDIG_PLLODIV_PHASE(Config->Options[0]);
#endif
            Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] = RegValue;
        }
    }
    else
    {
        (void)Instance;
        (void)DividerIndex;
        (void)RegValue;
    }
}
#endif


/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/


/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

const Clock_Ip_DividerCallbackType Clock_Ip_axDividerCallbacks[CLOCK_IP_DIVIDER_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_Callback_DividerEmpty,                  /* Set */
    },
#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE
    {
        &Clock_Ip_SetCgmXDeDivStatWithoutPhase,           /* Set */
    },
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_FMT_STAT_WITHOUT_PHASE
    {
        &Clock_Ip_SetCgmXDeDivFmtStatWithoutPhase,           /* Set */
    },
#endif

#ifdef CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE_WITH_TRIGGER
    {
        &Clock_Ip_SetCgmXDeDivStatWithoutPhaseWithTrigger,               /* Set */
    },
#endif

#ifdef CLOCK_IP_PLLDIG_PLL0DIV_DE_DIV_OUTPUT
    {
        &Clock_Ip_SetPlldigPll0divDeDivOutput,            /* Set */
    },
#endif


};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
