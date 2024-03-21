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

#endif /* __EMUL_H__ */
