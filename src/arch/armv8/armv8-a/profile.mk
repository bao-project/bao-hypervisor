## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

arch-cppflags+= 
arch-cflags+= -march=armv8-a
arch-asflags+=
arch-ldflags+=

arch_mem_prot:=mmu
PAGE_SIZE:=0x1000
