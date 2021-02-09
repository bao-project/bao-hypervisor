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

#ifndef __RISCV_ENCODING_H__
#define __RISCV_ENCODING_H__

#include <arch/opcodes.h>

#define INS_COMPRESSED(ins) (!((ins & 3) == 3))
#define INS_SIZE(ins) ((ins & 3) == 3 ? 4 : 2)

#define INS_OPCODE(ins) ((ins)&0x7f)
#define INS_FUNCT3(ins) ((ins >> 12) & 0x7)
#define INS_RD(ins) (((ins) >> 7) & 0x1f)
#define INS_RS1(ins) (((ins) >> 15) & 0x1f)
#define INS_RS2(ins) (((ins) >> 20) & 0x1f)
#define MATCH_LOAD (0x03)
#define MATCH_STORE (0x23)

#define INS_C_OPCODE(ins) ((ins)&0xe003)
#define INS_C_RD_RS2(ins) ((ins >> 2) & 0x7)
#define MATCH_C_LOAD (0x4000)
#define MATCH_C_STORE (0xc000)

#endif /* __RISCV_ENCODING_H__ */