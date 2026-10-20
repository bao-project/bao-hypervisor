/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>

/**
 * With -fno-omit-frame-pointer every frame record holds the caller's frame pointer at fp and the
 * return address at fp + 8. The walk only follows records that lie inside this CPU's stack, are
 * 16-byte aligned and move towards the stack top, so a guest x29 left behind by a VM exit or a
 * corrupted record ends the walk instead of faulting.
 */
size_t cpu_arch_backtrace(uintptr_t fp, uintptr_t* pcs, size_t max_depth)
{
    uintptr_t stack_base = (uintptr_t)cpu()->stack;
    uintptr_t stack_top = stack_base + STACK_SIZE;
    size_t depth = 0;

    while (depth < max_depth && fp >= stack_base && fp <= stack_top - 16 && IS_ALIGNED(fp, 16)) {
        const uintptr_t* frame = (const uintptr_t*)fp;
        pcs[depth] = frame[1];
        depth++;
        if (frame[0] <= fp) {
            break;
        }
        fp = frame[0];
    }

    return depth;
}
