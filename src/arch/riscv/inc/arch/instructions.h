/**
 * Bao Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef ARCH_INSTRUCTIONS_H
#define ARCH_INSTRUCTIONS_H

static inline uint64_t hlvb(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x30, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvbu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x30, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}


static inline uint64_t hlvh(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvhu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvxhu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x32, %0, %1, x3\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvw(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvwu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x1\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvxwu(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x34, %0, %1, x3\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

static inline uint64_t hlvd(uintptr_t addr){
    uint64_t value;
    asm volatile(
        ".insn r 0x73, 0x4, 0x36, %0, %1, x0\n\t"
        : "=r"(value): "r"(addr) : "memory");
    return value;
}

#endif /* ARCH_INSTRUCTIONS_H */