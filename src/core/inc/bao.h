/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __BAO_H__
#define __BAO_H__

#include <arch/bao.h>

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <printk.h>
#include <util.h>

#define INFO(args, ...) \
    printk("BAO INFO: " args "\n" __VA_OPT__(, ) __VA_ARGS__);

#define WARNING(args, ...) \
    printk("BAO WARNING: " args "\n" __VA_OPT__(, ) __VA_ARGS__);

#define ERROR(args, ...)                                            \
    {                                                               \
        printk("BAO ERROR: " args "\n" __VA_OPT__(, ) __VA_ARGS__); \
        while (1)                                                   \
            ;                                                       \
    }

#endif /* __ASSEMBLER__ */

#endif /* __BAO_H__ */
