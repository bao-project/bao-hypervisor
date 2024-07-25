## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

arch-cppflags+= 
arch-cflags+=-march=armv8-r 
ifeq ($(CC_IS_GCC),y)
	arch-cflags+=-mgeneral-regs-only
endif
arch-asflags+=
arch-ldflags+=

arch_mem_prot:=mpu
PAGE_SIZE:=64
