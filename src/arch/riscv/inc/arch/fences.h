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
#ifndef __FENCES_ARCH_H__
#define __FENCES_ARCH_H__

static inline void fence_ord_write()
{
    asm volatile("fence w, rw\n\t" ::: "memory");
}

static inline void fence_ord_read()
{
    asm volatile("fence r, rw\n\t" ::: "memory");
}

static inline void fence_ord()
{
    asm volatile("fence rw, rw\n\t" ::: "memory");
}

static inline void fence_sync_write()
{
    asm volatile("fence ow, iorw\n\t" ::: "memory");
}

static inline void fence_sync_read()
{
    asm volatile("fence ir, iorw\n\t" ::: "memory");
}

static inline void fence_sync()
{
    asm volatile("fence iorw, iorw\n\t" ::: "memory");
}

#endif /* __FENCES_ARCH_H__ */