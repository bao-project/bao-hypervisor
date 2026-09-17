/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VAPLIC_SELECTOR_H
#define VAPLIC_SELECTOR_H

#include <stddef.h>
#include <stdint.h>

#define VAPLIC_SELECTOR_SOURCES       1024U
#define VAPLIC_SELECTOR_GROUP_SIZE    32U
#define VAPLIC_SELECTOR_GROUPS        (VAPLIC_SELECTOR_SOURCES / VAPLIC_SELECTOR_GROUP_SIZE)
#define VAPLIC_SELECTOR_LEAF_BASE     (VAPLIC_SELECTOR_GROUPS - 1U)
#define VAPLIC_SELECTOR_NODES         (2U * VAPLIC_SELECTOR_GROUPS - 1U)
#define VAPLIC_SELECTOR_LEVELS        5U
#define VAPLIC_SELECTOR_HART_SHIFT    18U
#define VAPLIC_SELECTOR_PRIORITY_MASK 0xffU
#define VAPLIC_SELECTOR_TOPI_SHIFT    16U

/* One per vCPU/IDC. IRQ 0 denotes an empty node, never a priority sentinel. */
struct vaplic_selector {
    uint16_t winner[VAPLIC_SELECTOR_NODES];
};

/* A zero target priority is interpreted as one; priority 255 is valid. */
static inline uint32_t vaplic_selector_priority(uint32_t target)
{
    uint32_t priority = target & VAPLIC_SELECTOR_PRIORITY_MASK;
    return priority == 0U ? 1U : priority;
}

static inline uint16_t vaplic_selector_best(const uint32_t* target, uint16_t a, uint16_t b)
{
    if (a == 0U) {
        return b;
    }
    if (b == 0U) {
        return a;
    }
    uint32_t pa = vaplic_selector_priority(target[a]);
    uint32_t pb = vaplic_selector_priority(target[b]);
    return (pa < pb || (pa == pb && a < b)) ? a : b;
}

/*
 * Caller holds the VM's vAPLIC lock. candidates is the group's active &
 * pending & enabled mask, excluding any sources delivered by hardware.
 * hart is the target-register hart number (virtual in full emulation).
 * Always visit 32 source slots and all five ancestors; no early exit.
 */
static inline void vaplic_selector_update(struct vaplic_selector* selector, const uint32_t* target,
    size_t group, uint32_t candidates, uint32_t hart)
{
    uint16_t winner = 0;
    if (group == 0U) {
        candidates &= ~1U;
    }
    for (size_t bit = 0; bit < VAPLIC_SELECTOR_GROUP_SIZE; bit++) {
        uint16_t irq = (uint16_t)(group * VAPLIC_SELECTOR_GROUP_SIZE + bit);
        if ((candidates & (1U << bit)) != 0U &&
            (target[irq] >> VAPLIC_SELECTOR_HART_SHIFT) == hart) {
            winner = vaplic_selector_best(target, winner, irq);
        }
    }

    size_t node = VAPLIC_SELECTOR_LEAF_BASE + group;
    selector->winner[node] = winner;
    for (size_t level = 0; level < VAPLIC_SELECTOR_LEVELS; level++) {
        node = (node - 1U) / 2U;
        selector->winner[node] = vaplic_selector_best(target, selector->winner[2U * node + 1U],
            selector->winner[2U * node + 2U]);
    }
}

/* Threshold filters TOPI; domaincfg.IE and idelivery only gate the hart line. */
static inline uint32_t vaplic_selector_topi(const struct vaplic_selector* selector,
    const uint32_t* target, uint32_t threshold)
{
    uint16_t irq = selector->winner[0];
    if (irq == 0U) {
        return 0;
    }
    uint32_t priority = vaplic_selector_priority(target[irq]);
    return (threshold == 0U || priority < threshold) ?
        ((uint32_t)irq << VAPLIC_SELECTOR_TOPI_SHIFT) | priority :
        0U;
}

#endif /* VAPLIC_SELECTOR_H */
