/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_INTERRUPTS_H__
#define __ARCH_INTERRUPTS_H__

#include <bao.h>
#include <platform.h>

#define ARCH_MAX_INTERRUPTS    2048
#define MAX_INTERRUPTS         PLAT_MAX_INTERRUPTS
#define MAX_GUEST_INTERRUPTS   (MAX_INTERRUPTS)

#define MAX_INTERRUPT_LINES    MAX_INTERRUPTS
#define MAX_INTERRUPT_HANDLERS MAX_INTERRUPTS

/* TODO platform dependent */
#define IPI_CPU_MSG            1304

#define IPIR_CHANNEL_NUM 4
#define IPI_IRQ_ID       0

struct ipir {
    struct {
        volatile uint8_t IPI_ENS;   // Offset: 0x000 + 0x020 * n
        volatile uint8_t PAD0[3];
        volatile uint8_t IPI_FLGS;  // Offset: 0x004 + 0x020 * n
        volatile uint8_t PAD1[3];
        volatile uint8_t IPI_FCLRS; // Offset: 0x008 + 0x020 * n
        volatile uint8_t PAD2[7];
        volatile uint8_t IPI_REQS;  // Offset: 0x010 + 0x020 * n
        volatile uint8_t PAD3[3];
        volatile uint8_t IPI_RCLRS; // Offset: 0x014 + 0x020 * n
        volatile uint8_t PAD4[11];
    } channel[IPIR_CHANNEL_NUM];
};

void interrupts_arch_handle(void);
void interrupts_arch_ipi_enable(void);
void ipir_handle(irqid_t int_id);

#endif /* __ARCH_INTERRUPTS_H__ */
