/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_FracDiv.c
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
#define CLOCK_IP_FRACDIV_VENDOR_ID_C                      43
#define CLOCK_IP_FRACDIV_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_FRACDIV_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_FRACDIV_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_FRACDIV_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_FRACDIV_SW_MINOR_VERSION_C               0
#define CLOCK_IP_FRACDIV_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_FRACDIV_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_FracDiv.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_FRACDIV_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_FRACDIV_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_FRACDIV_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_FracDiv.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_FracDiv.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_FRACDIV_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_FRACDIV_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_FRACDIV_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_FracDiv.c and Clock_Ip_Private.h are different"
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

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_CallbackFracDivEmpty(Clock_Ip_FracDivConfigType const* Config);
static Clock_Ip_DfsStatusType Clock_Ip_CallbackFracDivEmptyComplete(Clock_Ip_NameType DfsName);
#ifdef CLOCK_IP_DFS_MFI_MFN
static void Clock_Ip_ResetDfsMfiMfn(Clock_Ip_FracDivConfigType const *Config);
static void Clock_Ip_SetDfsMfiMfn(Clock_Ip_FracDivConfigType const *Config);
static Clock_Ip_DfsStatusType Clock_Ip_CompleteDfsMfiMfn(Clock_Ip_NameType DfsName);
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_CallbackFracDivEmpty(Clock_Ip_FracDivConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}

static Clock_Ip_DfsStatusType Clock_Ip_CallbackFracDivEmptyComplete(Clock_Ip_NameType DfsName)
{
    (void)DfsName;
    /* No implementation */
    return STATUS_DFS_NOT_ENABLED;
}

#ifdef CLOCK_IP_DFS_MFI_MFN
static void Clock_Ip_ResetDfsMfiMfn(Clock_Ip_FracDivConfigType const *Config)
{

    uint32 Instance      = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
    uint32 DividerIndex  = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];

    /* Put this fractional divider in reset state */
    Clock_Ip_apxDfs[Instance]->PORTRESET |= (1UL << DividerIndex);
}
static void Clock_Ip_SetDfsMfiMfn(Clock_Ip_FracDivConfigType const *Config)
{

    uint32 Instance;
    uint32 DividerIndex;
    uint32 IntegerPart;          /* Integer part. */
    uint32 FractionalPart;          /* Fractional part. */

    uint32 Value = 0U;

    if (NULL_PTR != Config)
    {
        Instance        = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];
        DividerIndex    = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_DIVIDER_INDEX];
        IntegerPart     = Config->Value[0U];
        FractionalPart  = Config->Value[1U];

        /* Check whether fractional divider is enabled */
        if (0U != Config->Enable)
        {
            /* Write the value by which input signal is divided */
            Value |= DFS_DVPORT_MFN(FractionalPart);
            Value |= DFS_DVPORT_MFI(IntegerPart);
            Clock_Ip_apxDfs[Instance]->DVPORT[DividerIndex] = Value;

            /* Get corresponding port out of reset state */
            Clock_Ip_apxDfs[Instance]->PORTRESET &= ~(1UL << DividerIndex);
        }
    }
}
static Clock_Ip_DfsStatusType Clock_Ip_CompleteDfsMfiMfn(Clock_Ip_NameType DfsName)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DfsPortStatus;

    Clock_Ip_DfsStatusType Status = STATUS_DFS_LOCKED;

    uint32 Instance      = Clock_Ip_au8ClockFeatures[DfsName][CLOCK_IP_MODULE_INSTANCE];
    uint32 DividerIndex  = Clock_Ip_au8ClockFeatures[DfsName][CLOCK_IP_DIVIDER_INDEX];

    /* Check whether fractional divider is enabled */
    if (0U == (Clock_Ip_apxDfs[Instance]->PORTRESET & (1UL << DividerIndex)))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this port is locked */
        do
        {
            DfsPortStatus = (((Clock_Ip_apxDfs[Instance]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & (1UL << DividerIndex));
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U == DfsPortStatus) && (FALSE == TimeoutOccurred));

        if (FALSE != TimeoutOccurred)
        {
            Status = STATUS_DFS_UNLOCKED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, DfsName);
        }
    }
    else
    {
        Status = STATUS_DFS_NOT_ENABLED;
    }

    return Status;
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

const Clock_Ip_FracDivCallbackType Clock_Ip_axFracDivCallbacks[CLOCK_IP_FRACTIONAL_DIVIDER_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_CallbackFracDivEmpty,            /* Reset */
        &Clock_Ip_CallbackFracDivEmpty,            /* Set */
        &Clock_Ip_CallbackFracDivEmptyComplete,    /* Complete */
    },
#ifdef CLOCK_IP_DFS_MFI_MFN
    {
        &Clock_Ip_ResetDfsMfiMfn,                   /* Reset */
        &Clock_Ip_SetDfsMfiMfn,                     /* Set */
        &Clock_Ip_CompleteDfsMfiMfn,                /* Complete */
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
