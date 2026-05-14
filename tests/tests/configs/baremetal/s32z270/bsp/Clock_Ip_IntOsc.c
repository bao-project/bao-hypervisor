/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_IntOsc.c
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
#define CLOCK_IP_INTOSC_VENDOR_ID_C                      43
#define CLOCK_IP_INTOSC_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_INTOSC_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_INTOSC_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_INTOSC_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_INTOSC_SW_MINOR_VERSION_C               0
#define CLOCK_IP_INTOSC_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_INTOSC_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_IntOsc.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_INTOSC_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_INTOSC_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_INTOSC_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_IntOsc.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_IntOsc.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_INTOSC_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_INTOSC_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_INTOSC_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_IntOsc.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* Config);
static void Clock_Ip_InternalOscillatorEmpty_Disable(Clock_Ip_NameType Name);
/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

static void Clock_Ip_InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static void Clock_Ip_InternalOscillatorEmpty_Disable(Clock_Ip_NameType Name)
{
    (void)Name;
    /* No implementation */
}


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

const Clock_Ip_IntOscCallbackType Clock_Ip_axIntOscCallbacks[CLOCK_IP_IRCOSC_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_InternalOscillatorEmpty,          /* Set */
        &Clock_Ip_InternalOscillatorEmpty,          /* Enable */
        &Clock_Ip_InternalOscillatorEmpty_Disable,  /* Disable */
    },
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
