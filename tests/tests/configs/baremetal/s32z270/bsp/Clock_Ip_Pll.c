/*
 * Copyright 2021-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
*   @file       Clock_Ip_Pll.c
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
#define CLOCK_IP_PLL_VENDOR_ID_C                      43
#define CLOCK_IP_PLL_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_PLL_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_PLL_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_PLL_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_PLL_SW_MINOR_VERSION_C               0
#define CLOCK_IP_PLL_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_PLL_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Pll.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_PLL_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_PLL_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_PLL_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Pll.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Pll.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_PLL_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_PLL_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_PLL_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Pll.c and Clock_Ip_Private.h are different"
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

static void Clock_Ip_CallbackPllEmpty(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CallbackPllEmptyComplete(Clock_Ip_NameType PllName);
static void Clock_Ip_CallbackPllEmptyDisable(Clock_Ip_NameType PllName);

#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void Clock_Ip_ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
static void Clock_Ip_SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_NameType PllName);
static void Clock_Ip_EnablePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config);
#endif

#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN
static void Clock_Ip_ResetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config);
static void Clock_Ip_SetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePlldigRdivMfiMfnSdmen(Clock_Ip_NameType PllName);
static void Clock_Ip_EnablePlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config);
#endif

#ifdef CLOCK_IP_LFASTPLL_ENABLE
static void Clock_Ip_ResetLfastPLL(Clock_Ip_PllConfigType const* Config);
static void Clock_Ip_SetLfastPLL(Clock_Ip_PllConfigType const* Config);
static Clock_Ip_PllStatusReturnType Clock_Ip_CompleteLfastPLL(Clock_Ip_NameType PllName);
static void Clock_Ip_EnableLfastPLL(Clock_Ip_PllConfigType const* Config);
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


static void Clock_Ip_CallbackPllEmpty(Clock_Ip_PllConfigType const* Config)
{
    (void)Config;
    /* No implementation */
}
static Clock_Ip_PllStatusReturnType Clock_Ip_CallbackPllEmptyComplete(Clock_Ip_NameType PllName)
{
    (void)PllName;
    /* No implementation */
    return STATUS_PLL_LOCKED;
}
static void Clock_Ip_CallbackPllEmptyDisable(Clock_Ip_NameType PllName)
{
    (void)PllName;
    /* No implementation */
}

#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
#ifndef CLOCK_IP_FIRC_PLL_REFERENCE
    #define CLOCK_IP_FIRC_PLL_REFERENCE 0U
#endif
#ifndef CLOCK_IP_FXOSC_PLL_REFERENCE
    #define CLOCK_IP_FXOSC_PLL_REFERENCE 1U
#endif
static void Clock_Ip_ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint8 DividerIndex;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable output dividers */
        for (DividerIndex = 0U; DividerIndex < Clock_Ip_apxPll[Instance].DivsNo; DividerIndex++)
        {
            Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] &= ~PLLDIG_PLLODIV_DE_MASK;
        }

        /* Power down PLL */
        Clock_Ip_apxPll[Instance].PllInstance->PLLCR |= PLLDIG_PLLCR_PLLPD_MASK;
    }
    else
    {
        (void)Instance;
        (void)DividerIndex;
    }
}
static void Clock_Ip_SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint32 Value;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            /* Name of the input reference clock */
            switch (Config->InputReference)
            {
                case FIRC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FIRC_PLL_REFERENCE);
                    break;
                case FXOSC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FXOSC_PLL_REFERENCE);
                    break;
                default:
                    /* Command is not implemented on this platform */
                    break;
            }

            /* Configure PLL: predivider and multiplier */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLDV;
            Value &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            Value |= (uint32) (PLLDIG_PLLDV_RDIV(Config->Predivider)   |
                                PLLDIG_PLLDV_MFI(Config->MulFactorDiv));
            Clock_Ip_apxPll[Instance].PllInstance->PLLDV = Value;
            /* Set numerator fractional loop divider and sigma delta modulation */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLFD;
            Value &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);
            Value |=  PLLDIG_PLLFD_MFN(Config->NumeratorFracLoopDiv);
            Value |= PLLDIG_PLLFD_SDMEN(Config->SigmaDelta);
            Clock_Ip_apxPll[Instance].PllInstance->PLLFD = Value;
            /* Configure modulation */
            Value = (uint32) (PLLDIG_PLLFM_SSCGBYP(Config->FrequencyModulationBypass)               |
                              PLLDIG_PLLFM_SPREADCTL(Config->ModulationType)                        |
                              PLLDIG_PLLFM_STEPNO(Config->IncrementStep)                            |
                              PLLDIG_PLLFM_STEPSIZE(Config->ModulationPeriod));
            Clock_Ip_apxPll[Instance].PllInstance->PLLFM = Value;
        }
    }
    else
    {
        (void)Instance;
        (void)Value;
    }
}

static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_NameType PllName)
{
    Clock_Ip_PllStatusReturnType PllStatus = STATUS_PLL_LOCKED;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 Instance = Clock_Ip_au8ClockFeatures[PllName][CLOCK_IP_MODULE_INSTANCE];

    if (0U == (Clock_Ip_apxPll[Instance].PllInstance->PLLCR & PLLDIG_PLLCR_PLLPD_MASK))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            PllLockStatus = ((Clock_Ip_apxPll[Instance].PllInstance->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U == PllLockStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            PllStatus = STATUS_PLL_UNLOCKED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
        }
    }
    else
    {
        PllStatus = STATUS_PLL_NOT_ENABLED;
    }

    return PllStatus;
}
static void Clock_Ip_EnablePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure PLL. */
        if (1U == Config->Enable)
        {
            /* Send command to enable PLL device. */
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
    }
}
#endif

#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN
#ifndef CLOCK_IP_FIRC_PLL_REFERENCE
    #define CLOCK_IP_FIRC_PLL_REFERENCE 0U
#endif
#ifndef CLOCK_IP_FXOSC_PLL_REFERENCE
    #define CLOCK_IP_FXOSC_PLL_REFERENCE 1U
#endif
static void Clock_Ip_ResetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint8 DividerIndex;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Disable output dividers */
        for (DividerIndex = 0U; DividerIndex < Clock_Ip_apxPll[Instance].DivsNo; DividerIndex++)
        {
            Clock_Ip_apxPll[Instance].PllInstance->PLLODIV[DividerIndex] &= ~PLLDIG_PLLODIV_DE_MASK;
        }

        /* Power down PLL */
        Clock_Ip_apxPll[Instance].PllInstance->PLLCR |= PLLDIG_PLLCR_PLLPD_MASK;
    }
    else
    {
        (void)Instance;
        (void)DividerIndex;
    }
}
static void Clock_Ip_SetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
    uint32 Value;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        if (Config->Enable != 0U)
        {
            /* Name of the input reference clock */
            switch (Config->InputReference)
            {
                case FIRC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FIRC_PLL_REFERENCE);
                    break;
                case FXOSC_CLK:
                    /* Select input reference. */
                    Clock_Ip_apxPll[Instance].PllInstance->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(CLOCK_IP_FXOSC_PLL_REFERENCE);
                    break;
                default:
                    /* Command is not implemented on this platform */
                    break;
            }

            /* Configure PLL: predivider and multiplier */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLDV;
            Value &= ~(PLLDIG_PLLDV_RDIV_MASK | PLLDIG_PLLDV_MFI_MASK);
            Value |= (uint32) (PLLDIG_PLLDV_RDIV(Config->Predivider)   |
                                PLLDIG_PLLDV_MFI(Config->MulFactorDiv));
            Clock_Ip_apxPll[Instance].PllInstance->PLLDV = Value;
            /* Set numerator fractional loop divider and sigma delta modulation */
            Value = Clock_Ip_apxPll[Instance].PllInstance->PLLFD;
            Value &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);
            Value |=  PLLDIG_PLLFD_MFN(Config->NumeratorFracLoopDiv);
            Value |= PLLDIG_PLLFD_SDMEN(Config->SigmaDelta);
            Clock_Ip_apxPll[Instance].PllInstance->PLLFD = Value;
        }
    }
    else
    {
        (void)Instance;
        (void)Value;
    }
}
static Clock_Ip_PllStatusReturnType Clock_Ip_CompletePlldigRdivMfiMfnSdmen(Clock_Ip_NameType PllName)
{
    Clock_Ip_PllStatusReturnType PllStatus = STATUS_PLL_LOCKED;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 Instance = Clock_Ip_au8ClockFeatures[PllName][CLOCK_IP_MODULE_INSTANCE];

    if (0U == (Clock_Ip_apxPll[Instance].PllInstance->PLLCR & PLLDIG_PLLCR_PLLPD_MASK))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            PllLockStatus = ((Clock_Ip_apxPll[Instance].PllInstance->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U == PllLockStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            PllStatus = STATUS_PLL_UNLOCKED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
        }
    }
    else
    {
        PllStatus = STATUS_PLL_NOT_ENABLED;
    }
    return PllStatus;
}
static void Clock_Ip_EnablePlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure PLL. */
        if (1U == Config->Enable)
        {
            /* Send command to enable PLL device. */
            Clock_Ip_apxPll[Instance].PllInstance->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;
        }
    }
    else
    {
        (void)Instance;
    }
}
#endif

#ifdef CLOCK_IP_LFASTPLL_ENABLE
#ifdef ERR_IPV_LFAST_PLL_051380
#define CLOCK_IP_LFASTPLL_PLLCR_RESERVED_RWBIT_MASK    (0xE0000000U)
#endif
static void Clock_Ip_ResetLfastPLL(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
#ifdef ERR_IPV_LFAST_PLL_051380
    uint32 RegValue;
#endif
    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

    #ifndef ERR_IPV_LFAST_PLL_051380
        /* Power down PLL */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_SWPOFF(1);
        /* Accept write register LFAST */
        Clock_Ip_apxLfastPll[Instance].PllInstance->MCR &= (~((uint32)LFAST_MCR_DRFEN_MASK));
        /* Clear FBDIV bit field */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_FBDIV_MASK));
        /* Clear PREDIV bit field */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_PREDIV_MASK));
        /* Clear FDIVEN bit field */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_FDIVEN_MASK));
    #else
        RegValue = Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR;
        RegValue &= ~(CLOCK_IP_LFASTPLL_PLLCR_RESERVED_RWBIT_MASK);
        RegValue |= 0xC0000000U;

        RegValue &= (~((uint32)LFAST_PLLCR_FBDIV_MASK));
        RegValue |= LFAST_PLLCR_FBDIV((uint8)(Config->MulFactorDiv));

        RegValue &= (~((uint32)LFAST_PLLCR_PREDIV_MASK));
        RegValue |= LFAST_PLLCR_PREDIV((uint8)(Config->Predivider - 1U));

        RegValue &= (~((uint32)LFAST_PLLCR_FDIVEN_MASK));

        RegValue &= (~((uint32)LFAST_PLLCR_LPCFG_MASK));
        if (Config->MulFactorDiv <= 21U)
        {
            RegValue |= LFAST_PLLCR_LPCFG(3U);
        }
        else if (Config->MulFactorDiv >= 28U)
        {
            RegValue |= LFAST_PLLCR_LPCFG(1U);
        }
        else
        {
            /* Do nothing */
        }

        /* Accept write register LFAST */
        Clock_Ip_apxLfastPll[Instance].PllInstance->MCR &= (~((uint32)LFAST_MCR_DRFEN_MASK));

        /* 1. Discharge the charge pump by switching the PLL to the closed loop mode */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR = RegValue;

        /* 2. Turn off the PLL */
        Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_SWPOFF(1);

    #endif /* ERR_IPV_LFAST_PLL_051380 */
    }
    else
    {
        (void)Instance;
    }
}
static void Clock_Ip_SetLfastPLL(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;
#ifdef ERR_IPV_LFAST_PLL_051380
    uint32 RegValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
#endif

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure LFAST PLL. */
        if (1U == Config->Enable)
        {
            /* Accept write register LFAST */
            Clock_Ip_apxLfastPll[Instance].PllInstance->MCR &= (~((uint32)LFAST_MCR_DRFEN_MASK));
        #ifndef ERR_IPV_LFAST_PLL_051380
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_FBDIV_MASK));
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_FBDIV((uint8)(Config->MulFactorDiv));

            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_PREDIV_MASK));
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_PREDIV((uint8)(Config->Predivider - 1U));

            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= (~((uint32)LFAST_PLLCR_FDIVEN_MASK));
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_FDIVEN(Config->SigmaDelta);
        #else
            /* 3. Turn on the PLL  */
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_SWPON(1);

            /* 4. Wait for 10us */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, 10U);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while (FALSE == TimeoutOccurred);

            /* 5. Enable VCO control voltage pumping */
            RegValue = Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR;
            RegValue &= ~(CLOCK_IP_LFASTPLL_PLLCR_RESERVED_RWBIT_MASK);
            RegValue |= 0xE0000000U;
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR = RegValue;

            /* 6. Wait for 10us */
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, 10U);
            do
            {
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while (FALSE == TimeoutOccurred);
        #endif
        }
        else
        {
            (void)Instance;
        }
    }
    else
    {
        (void)Instance;
    }
}
static Clock_Ip_PllStatusReturnType Clock_Ip_CompleteLfastPLL(Clock_Ip_NameType PllName)
{
    Clock_Ip_PllStatusReturnType PllStatus = STATUS_PLL_LOCKED;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 PllEnableStatus;
    uint32 Instance = Clock_Ip_au8ClockFeatures[PllName][CLOCK_IP_MODULE_INSTANCE];
    if (1U == ((Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR & LFAST_PLLCR_SWPON_MASK) >> LFAST_PLLCR_SWPON_SHIFT))
    {
        Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
        /* Wait until this pll is enable */
        do
        {
            PllEnableStatus = ((Clock_Ip_apxLfastPll[Instance].PllInstance->PLLLSR & LFAST_PLLLSR_PLLDIS_MASK) >> LFAST_PLLLSR_PLLDIS_SHIFT);
            TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((0U != PllEnableStatus) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            PllStatus = STATUS_PLL_NOT_ENABLED;
            /* Report timeout error */
            Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
        }
        else
        {
            Clock_Ip_StartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_IP_TIMEOUT_VALUE_US);
            /* Wait until this pll is locked */
            do
            {
                PllLockStatus = ((Clock_Ip_apxLfastPll[Instance].PllInstance->PLLLSR & LFAST_PLLLSR_PLDCR_MASK) >> LFAST_PLLLSR_PLDCR_SHIFT);
                TimeoutOccurred = Clock_Ip_TimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while ((1U != PllLockStatus) && (FALSE == TimeoutOccurred));

            if (TRUE == TimeoutOccurred)
            {
                PllStatus = STATUS_PLL_UNLOCKED;
                /* Report timeout error */
                Clock_Ip_ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, PllName);
            }
        }
    }
    else
    {
        PllStatus = STATUS_PLL_NOT_ENABLED;
    }

    return PllStatus;
}
static void Clock_Ip_EnableLfastPLL(Clock_Ip_PllConfigType const* Config)
{
    uint32 Instance;

    if (NULL_PTR != Config)
    {
        Instance = Clock_Ip_au8ClockFeatures[Config->Name][CLOCK_IP_MODULE_INSTANCE];

        /* Configure LFAST PLL. */
        if (1U == Config->Enable)
        {
        #ifndef ERR_IPV_LFAST_PLL_051380
            /* Enable LFAST PLL */
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR |= LFAST_PLLCR_SWPON(1);
        #else
            /* 7. Switch to the functional mode */
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= ~(CLOCK_IP_LFASTPLL_PLLCR_RESERVED_RWBIT_MASK);

            /* 8. Set PLLCR[LPCFG] = 00b */
            Clock_Ip_apxLfastPll[Instance].PllInstance->PLLCR &= ~(LFAST_PLLCR_LPCFG_MASK);
        #endif /* ERR_IPV_LFAST_PLL_051380 */
        }
        else
        {
            (void)Instance;
        }
    }
    else
    {
        (void)Instance;
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
const Clock_Ip_PllCallbackType Clock_Ip_axPllCallbacks[CLOCK_IP_PLL_CALLBACKS_COUNT] =
{
    {
        &Clock_Ip_CallbackPllEmpty,            /* Reset */
        &Clock_Ip_CallbackPllEmpty,            /* Set */
        &Clock_Ip_CallbackPllEmptyComplete,    /* Complete */
        &Clock_Ip_CallbackPllEmpty,            /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,     /* Disable */
    },
#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
    {
        &Clock_Ip_ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,              /* Reset */
        &Clock_Ip_SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,                /* Set */
        &Clock_Ip_CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,           /* Complete */
        &Clock_Ip_EnablePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,             /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,                                               /* Disable */
    },
#endif

#ifdef CLOCK_IP_PLLDIG_RDIV_MFI_MFN_SDMEN
    {
        &Clock_Ip_ResetPlldigRdivMfiMfnSdmen,          /* Reset */
        &Clock_Ip_SetPlldigRdivMfiMfnSdmen,            /* Set */
        &Clock_Ip_CompletePlldigRdivMfiMfnSdmen,       /* Complete */
        &Clock_Ip_EnablePlldigRdivMfiMfnSdmen,         /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,            /* Disable */
    },
#endif

#ifdef CLOCK_IP_LFASTPLL_ENABLE
    {
        &Clock_Ip_ResetLfastPLL,                                      /* Reset */
        &Clock_Ip_SetLfastPLL,                                        /* Set */
        &Clock_Ip_CompleteLfastPLL,                                   /* Complete */
        &Clock_Ip_EnableLfastPLL,                                     /* Enable */
        &Clock_Ip_CallbackPllEmptyDisable,                            /* Disable */
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
