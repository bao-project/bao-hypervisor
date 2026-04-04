/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>

#ifndef __ARCH_IPIR_H__
#define __ARCH_IPIR_H__

#define IPIR_CH0_IRQ_ID   (0)
#define IPIR_CH1_IRQ_ID   (1)
#define IPIR_CH2_IRQ_ID   (2)
#define IPIR_CH3_IRQ_ID   (3)
#define IPIR_NUM_CHANNELS (4)

/* We reserve the last IPIR channel for Bao */
#define IPI_HYP_IRQ_ID    (IPIR_CH3_IRQ_ID)

typedef enum { IPInEN, IPInFLG, IPInFCLR, IPInREQ, IPInRCLR } ipir_reg_t;

struct ipir_chann {
    uint8_t IPInEN;
    uint8_t pad0[0x4 - 0x1];
    uint8_t IPInFLG;
    uint8_t pad1[0x8 - 0x5];
    uint8_t IPInFCLR;
    uint8_t pad2[0x10 - 0x9];
    uint8_t IPInREQ;
    uint8_t pad3[0x14 - 0x11];
    uint8_t IPInRCLR;
    uint8_t pad4[0x20 - 0x15];
};

struct ipir_hw {
    struct ipir_chann self[IPIR_NUM_CHANNELS];
    uint8_t pad[0x800 - 0x80];
    struct {
        struct ipir_chann chann[IPIR_NUM_CHANNELS];
        uint8_t pad[0x100 - 0x80];
    } pe[PLAT_CPU_NUM];
};

void ipir_send_ipi(cpuid_t cpu_target);
void ipir_init(void);

#endif /* __ARCH_IPIR_H__ */
