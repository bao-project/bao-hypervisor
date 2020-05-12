/**
 * Bao, a Lightweight Static Partitioning Hypervisor
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

#ifndef __EMUL_H__
#define __EMUL_H__

#include <bao.h>

typedef struct {
    uint64_t addr;
    bool write;
    bool sign_ext;
    size_t width;
    uint64_t reg;
    uint64_t reg_width;
} emul_access_t;

typedef bool (*emul_handler_t)(emul_access_t*);

typedef struct {
    uint64_t va_base;
    uint64_t pa_base;
    uint64_t size;
    uint64_t flags;
    emul_handler_t handler;
} emul_mem_t;

typedef struct {
    uint64_t addr;
    emul_handler_t handler;
} emul_reg_t;

bool emul_passthrough(emul_access_t*);

static inline void emul_write(emul_access_t* emul, uint64_t val)
{
    switch (emul->width) {
        case 1:
            *((uint8_t*)emul->addr) = val;
            break;
        case 2:
            *((uint16_t*)emul->addr) = val;
            break;
        case 4:
            *((uint32_t*)emul->addr) = val;
            break;
        case 8:
            *((uint64_t*)emul->addr) = val;
            break;
        default:
            ERROR("unknown emul write size");
    }
}

static inline uint64_t emul_read(emul_access_t* emul)
{
    uint64_t val = 0;

    switch (emul->width) {
        case 1:
            val = emul->sign_ext ? *((int8_t*)emul->addr)
                                 : *((uint8_t*)emul->addr);
            break;
        case 2:
            val = emul->sign_ext ? *((int16_t*)emul->addr)
                                 : *((uint16_t*)emul->addr);
            break;
        case 4:
            val = emul->sign_ext ? *((int32_t*)emul->addr)
                                 : *((uint32_t*)emul->addr);
            break;
        case 8:
            val = *((uint64_t*)emul->addr);
            break;
        default:
            ERROR("unknown emul read size");
    }

    return val;
}

#endif /* __EMUL_H__ */
