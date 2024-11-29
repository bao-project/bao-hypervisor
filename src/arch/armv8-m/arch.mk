## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= arm-none-eabi-

arch-cflags+=-march=armv8-m.main
arch-ldflags=

arch_mem_prot:=mpu
PAGE_SIZE:=64
