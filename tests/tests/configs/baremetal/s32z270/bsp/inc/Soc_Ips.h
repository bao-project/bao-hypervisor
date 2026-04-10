/*
 * Copyright 2022-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOC_IPS_H
#define SOC_IPS_H

/**
*   @file    Soc_Ips.h
*   @brief   Include platform types
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "IpVersionMacros.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SOC_IPS_VENDOR_ID                    43
#define SOC_IPS_MODULE_ID                    0
#define SOC_IPS_AR_RELEASE_MAJOR_VERSION     4
#define SOC_IPS_AR_RELEASE_MINOR_VERSION     7
#define SOC_IPS_AR_RELEASE_REVISION_VERSION  0
#define SOC_IPS_SW_MAJOR_VERSION             2
#define SOC_IPS_SW_MINOR_VERSION             0
#define SOC_IPS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((SOC_IPS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (SOC_IPS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Soc_Ips.h and Platform_Types.h are different"
    #endif

    /* Check if source file and IpVersionMacros.h header file are of the same Autosar version */
    #if ((SOC_IPS_AR_RELEASE_MAJOR_VERSION != IPVERSIONMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (SOC_IPS_AR_RELEASE_MINOR_VERSION != IPVERSIONMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Soc_Ips.h and IpVersionMacros.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/
/* 31 = 0x1F = ARM_PLATFORM
 * 53 = 0x35 = S32Z2XX DERIVATIVE ID
 * 01 = 0x01 = Rev. 1
 * 11 = 0x01 = Draft A      (A-B-C-D-E-F-G-H-I-J-K-L-M-N-O-P-Q-R-S-T-U-V-W-X-Y-Z)
*/

/**
* @brief PMC IP Version: PMC v03.00.01.00
* @details  IP Versions
*/
#define IPV_PMC                  (0x1F350101UL)


/**
* @brief PIT_RTI IP Version: PIT_RTI v05.00.06.11
* @details  IP Versions
*/
#define IPV_PIT              (0x1F350101UL)


/**
* @brief RTC IP Version: RTC 00.00.03.06
* @details  IP Versions
*/
#define IPV_RTC                (0x1F350101UL)


/**
* @brief ADCDIG IP Version: v00.00.18.00
* @details  IP Versions
*/
#define IPV_ADCDIG               (0x1F350101UL)


/**
* @brief SIUL2 IP Version: v00.00.00.10
* @details  IP Versions
*/
#define IPV_SIULV2               (0x1F350101UL)

/**
* @brief MC IP Version: D_IP_magic_carpet_SYN_302 [v07.00.02.03]
* @details  IP Versions
*/
#define IPV_MC                (0x1F350101UL)

/**
* @brief PLLDIG IP Version: DA_IP_PLL_SYS_C40ESF3_008 [v00.00.03.04]
* @details  IP Versions
*/
#define IPV_PLLDIG               (0x1F350101UL)

/**
* @brief FXOSC IP Version: DA_IP_FXOSC_C [v40.00.00.02.05]
* @details  IP Versions
*/
#define IPV_FXOSC               (0x1F350101UL)

/**
* @brief FIRC IP Version: D_IP_FIRC_SYN_SPEC [v00.00.00.21]
* @details  IP Versions
*/
#define IPV_FIRC                (0x1F350101UL)

/**
* @brief GMAC IP Version: D_IP_3P_ENET_MAC_SYN_017 [v02.00.00.08]
* @details  IP Versions
*/
#define IPV_GMAC                (0x1F350101UL)

/**
* @brief C40ASF IP Version: M_IP_c40asf_spec [v00.00.00.04]
* @details  IP Versions
*/
#define IPV_C40ASF              (0x1F350101UL)

/**
* @brief PFLASH IP Version: pflash_c40asf_s32k_spec [v00.00.00.11]
* @details  IP Versions
*/
#define IPV_PFLASH              (0x1F350101UL)

/**
* @brief C40ASF IP Version: M_IP_c40asf_spec [v00.00.00.04]
* @details  IP Versions
*/
#define IPV_FLASH_ARRAY         (0x1F350101UL)

/**
* @brief PFLASH IP Version: pflash_c40asf_s32k_spec [v00.00.00.11]
* @details  IP Versions
*/
#define IPV_FLASH_CONTROLLER    (0x1F350101UL)

/**
* @brief QSPI IP Version: QSPI d_ip_quadspi_v2_sync_spec.025
* @details  IP Versions
*/
#define IPV_QSPI                (0x1F350101UL)

/**
* @brief Clock Monitoring Unit Frequency Check (CMU_FC) IP Version
* @details  IP Versions
*/
#define IPV_CMU_FC              (0x1F350101UL)

/*==================================================================================================
*                              REGISTER PROTECTION (REG_PROT)
==================================================================================================*/
/**
* @brief Register Protection IP Version
* @details  IP Versions
*/
#define IPV_REG_PROT                  (0x1F350101UL)

/*==================================================================================================
*                              Software Erratas for Hardware Erratas
==================================================================================================*/
/**
* @brief Hardware errata for LPSPI: (ERR050456)
* @details ERR050456 LPSPI: Reset to fifo does not work as expected
*/
#define ERR_IPV_LPSPIV2_E050456         (STD_ON)

/**
* @brief Hardware errata for LINFlexD: (e007274)
* @details e007274 LINFlexD: Consecutive headers received by LIN Slave triggers the LIN FSM to an unexpected state.
*/
#define ERR_IPV_LINFLEXD_E007274    (STD_ON)

/**
* @brief Hardware errata for MC_RGM: (ERR051163)
* @details ERR051163 MC_RGM: Incorrect destructive reset event status
*/
#define ERR_IPV_MC_RGM_0001         (STD_ON)

/**
* @brief Hardware errata for LFAST PLL: (ERR051380)
* @details ERR051380 LFAST PLL: LFAST PLL Start-up Marginality
*/
#define ERR_IPV_LFAST_PLL_051380    (STD_ON)


/**
* @brief Hardware errata for EMIOS: (ERR009978)
* @details ERR009978 EMIOS: eMIOS: Unexpected channel flag assertion during GPIO to
MCB mode transition
*/
#define ERR_IPV_EMIOS_009978        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR050679)
* @details ERR050679 NETC: Accesses to 64-bit stats registers must be performed atomically
MCB mode transition
*/
#define ERR_IPV_NETC_050679        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051025)
* @details ERR051025 NETC: Preemption verify time longer than specified
MCB mode transition
*/
#define ERR_IPV_NETC_051025        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051124)
* @details ERR051124 NETC: Simultaneous scheduler events result in missed hold assertion
MCB mode transition
*/
#define ERR_IPV_NETC_051124        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051254)
* @details ERR051254 NETC: Administrative gate control list can get configured inadvertently
when an exception is detected and notified
*/
#define ERR_IPV_NETC_051254        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051398)
* @details ERR051398 NETC: FLR or transmit disable may cause frame transfers to underrun in MAC
resulting in bad frame transmission
*/
#define ERR_IPV_NETC_051398        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051260)
* @details ERR051260 NETC: During initial Initialization of NETC, all ENETCs and Switch PCI functions
must be enabled for NETC to accept table management commands for any function
*/
#define ERR_IPV_NETC_051260        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051261)
* @details ERR051261 NETC: Egress ports can violate 802.3 half-duplex jam protocol after collision
event
*/
#define ERR_IPV_NETC_051261        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051130)
* @details ERR051130 NETC: Egress time gate scheduling can get corrupted when functional level reset
is applied or when time gating is disabled.
*/
#define ERR_IPV_NETC_E051130        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051305)
* @details ERR051305 NETC: Entry_id not returned correctly by Stream Gating Instance and Time Gate
Scheduling QUERY table management commands.
*/
#define ERR_IPV_NETC_051305        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051129)
* @details ERR051129 NETC: Errored frames due to parity error are not counted in TFCS and TERR.
*/
#define ERR_IPV_NETC_E051129        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051023)
* @details ERR051023 NETC: Excessive collisions are counted as late collisions.
*/
#define ERR_IPV_NETC_E051023        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051262)
* @details ERR051262 NETC: MAC statistics counters are inaccurate when operating in half-duplex.
*/
#define ERR_IPV_NETC_051262        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051048)
* @details ERR051048 NETC: Management command with search action responds with incorrect
NUM_MATCHED.
*/
#define ERR_IPV_NETC_E051048        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051243)
* @details ERR051243 NETC: Multi-entry SEARCH table management command returns invalid error
code.
*/
#define ERR_IPV_NETC_051243        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051188)
* @details ERR051188 NETC: Register SITSR not accessible for Virtual Station Interfaces
*/
#define ERR_IPV_NETC_051188        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051247)
* @details ERR051247 NETC: System bus error on VSI-to-PSI message is not reported to PSI.
*/
#define ERR_IPV_NETC_051247        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051124)
* @details ERR051124 NETC: Simultaneous scheduler events result in missed hold assertion
MCB mode transition
*/
#define ERR_IPV_NETC_051124        (STD_ON)

/**
* @brief Hardware errata for NETC: (ERR051587)
* @details ERR051587 NETC: Time gate scheduling update command may respond with error when AdminBaseTime specified is near the current time.
*/
#define ERR_IPV_NETC_051587        (STD_ON)

/** @brief Hardware errata for NETC: (ERR051300)
* @details ERR051300 NETC: NETC engine watchdogs do not operate effectively under all
circumstances
*/
#define ERR_IPV_NETC_051300        (STD_ON)
/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief Enable CACHE management feature
* @details Global define to enable CACHE management at runtime
*/
#define MCAL_CACHE_RUNTIME_MNGMNT (STD_ON)

/**
* @brief number of EMIOS channels per each interrupt
* @details  Platform specific Defines/Configurations for EMIOS.
* Can be 1U, 2U, 4U, etc.. depending on the platform
*/
#define EMIOS_CHANNELS_PER_INTERRUPT (4U)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/**
* @brief User Mode feature is enabled
* @details User Mode feature - MCAL is configured to run in supervisor mode, by default.
*/

#ifdef MCAL_ENABLE_SUPERVISOR_MODE
    #undef MCAL_ENABLE_USER_MODE_SUPPORT
#endif
/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


/** @} */

#endif /* SOC_IPS_H */
