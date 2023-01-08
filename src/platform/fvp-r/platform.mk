## SPDX-License-Identifier: GPL-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
ARCH_PROFILE:=armv8-r

GIC_VERSION:=GICV3

drivers = pl011_uart

platform_description:=fvpr_desc.c

platform-cppflags =
platform-cflags =
platform-asflags =
platform-ldflags =
