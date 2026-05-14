/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <clock_control_nxp_s32.h>

#define IRQ_MASK_BITS   (0x80U)
#define FIQ_MASK_BITS   (0x40U)
#define DISABLE_IRQS    (IRQ_MASK_BITS | FIQ_MASK_BITS)

#define CORE_ID_0       (0x0)
#define CORE_ID_1       (0x1)
#define CORE_ID_2       (0x2)
#define CORE_ID_3       (0x3)
#define CORE_ID_4       (0x4)
#define CORE_ID_5       (0x5)
#define CORE_ID_6       (0x6)
#define CORE_ID_7       (0x7)
#define CORE_ID_8       (0x8)
#define CORE_ID_12      (0xC)
#define CORE_ID_13      (0xD)

void bsp_entrypoint(void)
{
    nxp_s32_clock_init();
}

Clock_Ip_StatusType nxp_s32_clock_init(void)
{
    Clock_Ip_StatusType status;

    status = Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);

    uint64_t volatile freq0 = Clock_Ip_GetClockFrequency(RTU0_CORE_CLK);
    (void)freq0;

    return status;
}

static void Core_EL1ResumeInterrupts(void)
{
    uint32_t cpsr = 0;

    __asm__ volatile("mrs %0, cpsr\n" : "=r"(cpsr));

    cpsr &= (uint32_t)~DISABLE_IRQS;

    __asm__ volatile("msr cpsr, %0\n" : : "r"(cpsr));

    return;
}

void Sys_EL1ResumeInterrupts(void)
{
    Core_EL1ResumeInterrupts();
}

static void Core_EL1SuspendInterrupts(void)
{
    uint32_t cpsr = 0;

    __asm__ volatile("mrs %0, cpsr\n" : "=r"(cpsr));

    cpsr |= DISABLE_IRQS;

    __asm__ volatile("msr cpsr, %0\n" : : "r"(cpsr));

    return;
}

void Sys_EL1SuspendInterrupts(void)
{
    Core_EL1SuspendInterrupts();
}

uint8 Sys_GetCoreID(void)
{
    uint8 core_id = IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK;

    switch (core_id) {
        case CORE_ID_0:
        case CORE_ID_4:
        case CORE_ID_8:
        case CORE_ID_12:
            return 0x0;

        case CORE_ID_1:
        case CORE_ID_5:
        case CORE_ID_13:
            return 0x1;

        case CORE_ID_2:
        case CORE_ID_6:
            return 0x2;

        case CORE_ID_3:
        case CORE_ID_7:
            return 0x3;

        default:
            while (1) {
                /* Invalid core, loop forever */
            }
    }
}
