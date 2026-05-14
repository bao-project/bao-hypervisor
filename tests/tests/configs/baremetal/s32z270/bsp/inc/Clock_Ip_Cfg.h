/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
*   @file       Clock_Ip_Cfg.h
*   @version    2.0.0
*
*   @brief   AUTOSAR Mcu - Clock configuration header file.
*   @details This file is the header containing all the necessary information for CLOCK
*            module configuration(s).
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/

#ifndef CLOCK_IP_CFG_H
#define CLOCK_IP_CFG_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Clock_Ip_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_CFG_VENDOR_ID                      43
#define CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION       4
#define CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION       7
#define CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION    0
#define CLOCK_IP_CFG_SW_MAJOR_VERSION               2
#define CLOCK_IP_CFG_SW_MINOR_VERSION               0
#define CLOCK_IP_CFG_SW_PATCH_VERSION               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Cfg.h file and Clock_Ip_Types.h file are of the same vendor */
#if (CLOCK_IP_CFG_VENDOR_ID != CLOCK_IP_TYPES_VENDOR_ID)
    #error "Clock_Ip_Cfg.h and Clock_Ip_Types.h have different vendor ids"
#endif

/* Check if Clock_Ip_Cfg.h file and Clock_Ip_Types.h file are of the same Autosar version */
#if ((CLOCK_IP_CFG_AR_RELEASE_MAJOR_VERSION != CLOCK_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_CFG_AR_RELEASE_MINOR_VERSION != CLOCK_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_CFG_AR_RELEASE_REVISION_VERSION != CLOCK_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Cfg.h and Clock_Ip_Types.h are different"
#endif

/* Check if Clock_Ip_Cfg.h file and Clock_Ip_Types.h file are of the same Software version */
#if ((CLOCK_IP_CFG_SW_MAJOR_VERSION != CLOCK_IP_TYPES_SW_MAJOR_VERSION) || \
     (CLOCK_IP_CFG_SW_MINOR_VERSION != CLOCK_IP_TYPES_SW_MINOR_VERSION) || \
     (CLOCK_IP_CFG_SW_PATCH_VERSION != CLOCK_IP_TYPES_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of Clock_Ip_Cfg.h and Clock_Ip_Types.h are different"
#endif

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Pre-processor switch for enabling the default error detection and reporting to the DET.
*                   The detection of default errors is configurable (ON / OFF) at pre-compile time.
*/
#define CLOCK_IP_DEV_ERROR_DETECT         (STD_OFF)

#define CLOCK_IP_TIMEOUT_TYPE                (OSIF_COUNTER_DUMMY)

#define CLOCK_IP_TIMEOUT_VALUE_US            (50000)

/**
* @brief        Support for User mode.
*               If this parameter has been configured to 'TRUE' the Clock can be executed from both supervisor and user mode.
*/
#define CLOCK_IP_ENABLE_USER_MODE_SUPPORT  (STD_OFF)

/** Check the driver user mode is enabled only when the MCAL_ENABLE_USER_MODE_SUPPORT is enabled */
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Clock in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
  #endif /* (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT) */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

#ifdef CLOCK_IP_PREPARE_MEMORY_CONFIG
/**
* @brief            The stage of the flash and ram controllers configuration.
* @details          This is used to specify the entry and exit point of the flash and ram controllers configuration.
*/
typedef enum
{
    CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY_POINT      = 0x77U,
    CLOCK_IP_RAM_MEMORY_CONFIG_EXIT_POINT       = 0x88U,
    CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY_POINT    = 0x89U,
    CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT_POINT     = 0x90U
 
} Clock_Ip_MemoryConfigStageType;
#endif


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#if CLOCK_IP_CMUS_COUNT > 0U

/**
* @brief        This function clear the CMU interrupt flag from CMU module.
* @details      Called by RGM ISR routine when a user notification for CMU FCCU events is configured
*
* @return       void
*
*/
ISR(Mcu_Cmu_ClockFail_IRQHandler);

#endif
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"


/* *************************************************************************
 * Configuration structure for Clock Configuration 
 * ************************************************************************* */

extern const Clock_Ip_ClockConfigType Clock_Ip_aClockConfig[];


#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_IP_CFG_H */

/** @} */
