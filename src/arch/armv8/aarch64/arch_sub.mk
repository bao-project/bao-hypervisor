## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= aarch64-none-elf-

arch-cppflags+=-DAARCH64
arch-cflags+= -mcmodel=large -mstrict-align
arch-asflags+=
arch-ldflags+=
