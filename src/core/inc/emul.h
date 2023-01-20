/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __EMUL_H__
#define __EMUL_H__

#include <bao.h>
#include <list.h>

struct emul_access {
    vaddr_t addr;
    bool write;
    bool sign_ext;
    size_t width;
    unsigned long reg;
    unsigned long reg_high;
    bool multi_reg;
    size_t reg_width;
};

typedef bool (*emul_handler_t)(struct emul_access*);

struct emul_mem {
    node_t node;
    vaddr_t va_base;
    size_t size;
    emul_handler_t handler;
};

struct emul_reg {
    node_t node;
    vaddr_t addr;
    emul_handler_t handler;
};

bool emul_passthrough(struct emul_access*);

static inline void emul_write(struct emul_access* emul, uint64_t val)
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

static inline unsigned long emul_read(struct emul_access* emul)
{
    unsigned long val = 0;

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
