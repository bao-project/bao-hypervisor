/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Gate.c
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
#define CLOCK_IP_GATE_VENDOR_ID_C                      43
#define CLOCK_IP_GATE_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_GATE_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_GATE_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_GATE_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_GATE_SW_MINOR_VERSION_C               0
#define CLOCK_IP_GATE_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_GATE_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Gate.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_GATE_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_GATE_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_GATE_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Gate.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Gate.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_GATE_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_GATE_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_GATE_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Gate.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_ClockSetGateEmpty(Clock_Ip_GateConfigType const* Config);
static void Clock_Ip_ClockUpdateGateEmpty(Clock_Ip_NameType ClockName, boolean Gate);
#ifdef CLOCK_IP_CONTROL_ENABLE_GPR_PCTL
static void Clock_Ip_ClockSetGateClockControlEnableGprPctl(Clock_Ip_GateConfigType const* Config);
static void Clock_Ip_ClockUpdateGateClockControlEnableGprPctl(Clock_Ip_NameType ClockName, boolean Gate);
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

static void Clock_Ip_ClockSetGateEmpty(Clock_Ip_GateConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static void Clock_Ip_ClockUpdateGateEmpty(Clock_Ip_NameType ClockName, boolean Gate)
{
    (void)ClockName;
    (void)Gate;
    /* No implementation */
}

#ifdef CLOCK_IP_CONTROL_ENABLE_GPR_PCTL
/* Write configuration of clock gate to register */
static void Clock_Ip_ClockSetGateClockControlEnableGprPctl(Clock_Ip_GateConfigType const* Config)
{
    const Clock_Ip_GateInfoType * GateInformation;
    uint32 GroupIndex;
    uint32 GateIndex;
    uint32 GateBitField;

    if (NULL_PTR != Config)
    {
        GateInformation = &Clock_Ip_axGateInfo[Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_GATE_INDEX]];
        GroupIndex      = GateInformation->GroupIndex;
        GateIndex       = GateInformation->GateIndex;
        GateBitField    = GateInformation->GateBitField;

        if (Config->Enable != 0U)
        {
            Clock_Ip_apxGprClockControlEnable[GroupIndex]->PCTL[GateIndex] |= ((uint32)GPR_PCTL_MASK << GateBitField);
        }
        else
        {
            Clock_Ip_apxGprClockControlEnable[GroupIndex]->PCTL[GateIndex] &= ~((uint32)GPR_PCTL_MASK << GateBitField);
        }
    }
    else
    {
        (void)GateInformation;
        (void)GroupIndex;
        (void)GateIndex;
        (void)GateBitField;
    }
}
static void Clock_Ip_ClockUpdateGateClockControlEnableGprPctl(Clock_Ip_NameType ClockName, boolean Gate)
{
    Clock_Ip_GateConfigType Config;

    Config.Name = ClockName;
    if (TRUE == Gate)
    {
        Config.Enable = 0U;
    }
    else
    {
        Config.Enable = 1U;
    }
    /* Write configuration to register */
    Clock_Ip_ClockSetGateClockControlEnableGprPctl(&Config);
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

const Clock_Ip_GateCallbackType Clock_Ip_axGateCallbacks[CLOCK_IP_GATE_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_ClockSetGateEmpty,     /* Set */
        &Clock_Ip_ClockUpdateGateEmpty,  /* Update */
    },
#ifdef CLOCK_IP_CONTROL_ENABLE_GPR_PCTL
    {
        &Clock_Ip_ClockSetGateClockControlEnableGprPctl,       /* Set */
        &Clock_Ip_ClockUpdateGateClockControlEnableGprPctl,    /* Update */
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
