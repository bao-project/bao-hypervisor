/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <cpu.h>

/**
 * The trap vector re-bases sp to the stack top, so after an internal trap the chain steps from the
 * handler frames down to the frames of the trapped code, and the handler frames may have
 * overwritten some of those. A record that points back at a frame already visited ends the walk.
 */
static bool seen_before(const uintptr_t* seen, size_t n, uintptr_t fp)
{
    for (size_t i = 0; i < n; i++) {
        if (seen[i] == fp) {
            return true;
        }
    }
    return false;
}

/**
 * With -fno-omit-frame-pointer the frame pointer (s0) points just above the frame record: the
 * return address sits at fp - REGLEN and the caller's frame pointer at fp - 2 * REGLEN. The walk
 * only follows records inside this CPU's stack, aligned to the register size, that it has not
 * visited before.
 */
size_t cpu_arch_backtrace(uintptr_t fp, uintptr_t* pcs, size_t max_depth)
{
    uintptr_t stack_base = (uintptr_t)cpu()->stack;
    uintptr_t stack_top = stack_base + STACK_SIZE;
    uintptr_t seen[BACKTRACE_MAX_DEPTH];
    size_t depth = 0;

    if (max_depth > BACKTRACE_MAX_DEPTH) {
        max_depth = BACKTRACE_MAX_DEPTH;
    }

    while (depth < max_depth && fp >= stack_base + (2 * REGLEN) && fp <= stack_top &&
        IS_ALIGNED(fp, REGLEN) && !seen_before(seen, depth, fp)) {
        const uintptr_t* frame = (const uintptr_t*)(fp - (2 * REGLEN));
        seen[depth] = fp;
        pcs[depth] = frame[1];
        depth++;
        fp = frame[0];
    }

    return depth;
}
