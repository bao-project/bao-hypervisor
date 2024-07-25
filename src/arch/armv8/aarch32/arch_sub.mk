## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= arm-none-eabi-

arch-cppflags+=-DAARCH32
arch-cflags+= -mfloat-abi=soft
arch-asflags+=
arch-ldflags+=

clang_arch_target:=arm
