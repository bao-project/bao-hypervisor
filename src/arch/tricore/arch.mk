## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= tricore-elf-


arch-cppflags+=
arch-cflags = 
arch-asflags = 
arch-ldflags = 

arch_mem_prot:=mpu
PAGE_SIZE:=0x1000
