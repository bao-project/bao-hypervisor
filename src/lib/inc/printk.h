/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PRINTK_H
#define __PRINTK_H

#include <bao.h>
#include <stdarg.h>

size_t vsnprintk(char* buf, size_t buf_size, const char** fmt,
    va_list* args);

#endif /* __PRINTK_H */
