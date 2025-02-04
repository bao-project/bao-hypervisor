## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= arm-none-eabi-

arch-cflags+=-march=armv8-m.main
arch-cflags+=-mfloat-abi=hard
arch-cflags+=-mfpu=fpv5-sp-d16
arch-cflags+=-mthumb
arch-ldflags=

arch_mem_prot:=mpu
arch_mem:=non_unified
PAGE_SIZE:=64
