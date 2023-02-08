## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

arch-cppflags+= 
arch-cflags+=-march=armv8-r -mgeneral-regs-only
arch-asflags+=
arch-ldflags+=

arch_mem_prot:=mpu
PAGE_SIZE:=64
