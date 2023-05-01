## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8

GIC_VERSION:=GICV3

drivers = pl011_uart

platform-cppflags =
platform-cflags = -gdwarf-4
platform-asflags =
platform-ldflags =

platform_description:=fvpa_desc.c
