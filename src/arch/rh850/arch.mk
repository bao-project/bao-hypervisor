## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Default CROSS_COMPILE
CROSS_COMPILE ?= v850-elf-

# RH850 specific flags for compiler
arch-cflags+=-mv850e3v5
arch-cflags+=-mrh850-abi
arch-cflags+=-m8byte-align
arch-cflags+=-msoft-float
arch-cflags+=-fno-leading-underscore

# RH850 specific flags for assembler
arch-asflags+=-mv850e3v5
arch-asflags+=-mrh850-abi
arch-asflags+=-m8byte-align

arch_mem_prot:=mpu
PAGE_SIZE:=64
