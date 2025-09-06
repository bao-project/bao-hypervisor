## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= tricore-elf-

clang_arch_target:=tricore-unknown-unknown-elf

arch-cppflags+=
#arch-cflags=-march=tc18
#arch-asflags=-march=tc18
arch-ldflags=

arch_mem_prot:=mpu
plat_mem:=non_unified
PAGE_SIZE:=64
