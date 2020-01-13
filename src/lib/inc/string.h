/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Sandro Pinto <sandro.pinto@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __STRING_H_
#define __STRING_H_

#include <bao.h>

#define WORD_TYPE unsigned long
#define WORD_SIZE (sizeof(WORD_TYPE *))

void *memcpy(void *dst, const void *src, uint32_t count);
void *memset(void *dest, uint32_t c, uint32_t count);

char *strcat(char *dest, char *src);
uint32_t strlen(const char *s);
uint32_t strnlen(const char *s, size_t n);
char *strcpy(char *dest, char *src);

#endif /* __STRING_H_ */
