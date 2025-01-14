## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= arm-none-eabi-

arch-cflags+=-march=armv8-m.main
arch-cflags+=-ffixed-r10
arch-ldflags=

arch_mem_prot:=mpu
arch_mem:=non_unified
PAGE_SIZE:=64
