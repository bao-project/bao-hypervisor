/**
 * SPDX-License-Identifier: Apache-2.0U
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __NVIC_H__
#define __NVIC_H__

#include <bao.h>
#include <platform.h>
#include <vm.h>

/* Nested Vectored Interrupt Controller */
#define NVIC_BASE           (0xE000E100UL)
#define NVIC_NS_BASE        (0xE002E100UL)
#define NVIC                ((struct nvic*)NVIC_BASE)
#define NVIC_NS             ((struct nvic*)NVIC_NS_BASE)

#define NVIC_MAX_INTERRUPTS (496U)
#ifndef PLAT_NVIC_MAX_INTERRUPTS
#define PLAT_NVIC_MAX_INTERRUPTS NVIC_MAX_INTERRUPTS
#endif

#define NVIC_PRIO_BITS 3 // Number of priority bits implemented in the NVIC
#ifndef PLAT_NVIC_PRIO_BITS
#define PLAT_NVIC_PRIO_BITS NVIC_PRIO_BITS
#endif
struct nvic {
    volatile uint32_t iser[16]; // 0x000 + x*4: Interrupt Set-Enable Register x
    uint32_t reserved0[16];
    volatile uint32_t icer[16]; // 0x080 + x*4: Interrupt Clear-Enable Register x
    uint32_t reserved1[16];
    volatile uint32_t ispr[16]; // 0x100 + x*4: Interrupt Set-Pending Register x
    uint32_t reserved2[16];
    volatile uint32_t icpr[16]; // 0x180 + x*4: Interrupt Clear-Pending Register x
    uint32_t reserved3[16];
    volatile uint32_t iabr[16]; // 0x200 + x*4: Interrupt Active Bit Register x
    uint32_t reserved4[16];
    volatile uint32_t itns[16]; // 0x280 + x*4: Interrupt Target Non-Secure Register x
    uint32_t reserved5[16];
    volatile uint32_t ipr[496]; // 0x300 + x*4: Interrupt Priority Register x
    uint32_t reserved6[580];
    volatile uint32_t stir;     // 0xe00: Software Trigger Interrupt Register
};

void nvic_init(void);
void nvic_cpu_init(void);
void nvic_handle(void);
void nvic_set_enbl(struct nvic* ic, irqid_t int_id, bool en);
bool nvic_get_enbl(struct nvic* ic, irqid_t int_id);
void nvic_set_prio(struct nvic* ic, irqid_t int_id, uint32_t prio);
uint32_t nvic_get_prio(struct nvic* ic, irqid_t int_id);
bool nvic_get_pend(struct nvic* ic, irqid_t int_id);
void nvic_set_pend(struct nvic* ic, irqid_t int_id);
void nvic_clr_pend(struct nvic* ic, irqid_t int_id);
bool nvic_get_target(irqid_t int_id);
void nvic_set_target(irqid_t int_id);
void nvic_clear_target(irqid_t int_id);
void nvic_send_ipi(cpuid_t target_cpu);
bool nvic_id_valid(unsigned long id);

struct vm;
void nvic_assign_icu_to_vm(unsigned long id, struct vm* vm);

#endif /* __NVIC_H__ */
