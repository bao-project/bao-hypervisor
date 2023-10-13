/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __BAO_H__
#define __BAO_H__

#include <arch/bao.h>

#ifndef __ASSEMBLER__

#include <types.h>
#include <console.h>
#include <util.h>

#define INFO(args, ...) \
    console_printk("BAO INFO: " args "\n" __VA_OPT__(, ) __VA_ARGS__);

#define WARNING(args, ...) \
    console_printk("BAO WARNING: " args "\n" __VA_OPT__(, ) __VA_ARGS__);

#define ERROR(args, ...)                                                    \
    {                                                                       \
        console_printk("BAO ERROR: " args "\n" __VA_OPT__(, ) __VA_ARGS__); \
        while (1)                                                           \
            ;                                                               \
    }

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
