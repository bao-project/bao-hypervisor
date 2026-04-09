/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
*   @file       OsIf_Cfg.h
*   @version 2.0.0
*
*
*   @addtogroup OSIF_DRIVER
*   @{
*/

#ifndef OSIF_CFG_H
#define OSIF_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "OsIf_ArchCfg.h"
#include "Std_Types.h"

#include "S32Z2_SYSTICK.h"
#include "S32Z2_MSCM.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_CFG_VENDOR_ID                    43
#define OSIF_CFG_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_CFG_AR_RELEASE_MINOR_VERSION     7
#define OSIF_CFG_AR_RELEASE_REVISION_VERSION  0
#define OSIF_CFG_SW_MAJOR_VERSION             2
#define OSIF_CFG_SW_MINOR_VERSION             0
#define OSIF_CFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Cfg.h file and OsIf_ArchCfg.h file are of the same vendor */
#if (OSIF_CFG_VENDOR_ID != OSIF_ARCHCFG_VENDOR_ID)
    #error "OsIf_Cfg.h and OsIf_ArchCfg.h have different vendor ids"
#endif
/* Check if OsIf_Cfg.h file and OsIf_ArchCfg.h file are of the same Autosar version */
#if ((OSIF_CFG_AR_RELEASE_MAJOR_VERSION    != OSIF_ARCHCFG_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_MINOR_VERSION    != OSIF_ARCHCFG_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_CFG_AR_RELEASE_REVISION_VERSION != OSIF_ARCHCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of OsIf_Cfg.h and OsIf_ArchCfg.h are different"
#endif
/* Check if OsIf_Cfg.h file and OsIf_ArchCfg.h file are of the same Software version */
#if ((OSIF_CFG_SW_MAJOR_VERSION != OSIF_ARCHCFG_SW_MAJOR_VERSION) || \
     (OSIF_CFG_SW_MINOR_VERSION != OSIF_ARCHCFG_SW_MINOR_VERSION) || \
     (OSIF_CFG_SW_PATCH_VERSION != OSIF_ARCHCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of OsIf_Cfg.h and OsIf_ArchCfg.h are different"
#endif

/* Check if OsIf_Cfg.h file and Std_Types.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((OSIF_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (OSIF_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of OsIf_Cfg.h and Std_Types.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* General OSIF configuration */
#define OSIF_MODULE_ID                   (255U)

#define OSIF_DRIVER_INSTANCE             (255U)

#define OSIF_ENABLE_USER_MODE_SUPPORT     (STD_OFF)

#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == OSIF_ENABLE_USER_MODE_SUPPORT)
        #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running OsIf in user mode, MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
    #endif /* (STD_ON == OSIF_ENABLE_USER_MODE_SUPPORT */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

#define OSIF_ENABLE_MULTICORE_SUPPORT    (STD_OFF)

#define OSIF_MAX_COREIDX_SUPPORTED       (1U)

#define OSIF_MAX_APPIDX_SUPPORTED        (1U) 

#define OSIF_DEV_ERROR_DETECT            (STD_OFF)
#define USING_COHORT_DOMAIN_ID     (STD_OFF)
#define USING_OS_BAREMETAL

//#define USING_GET_CORE_ID

#define OSIF_USE_SYSTEM_TIMER            (STD_OFF)

#define OSIF_USE_CUSTOM_TIMER            (STD_OFF)


#define OSIF_GET_PHYSICAL_CORE_ID_ENABLE  (STD_OFF)

/* Autosar OS Specific */

/* Baremetal Specific */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OSIF_CFG_H */
/** @} */
