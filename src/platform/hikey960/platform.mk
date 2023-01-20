## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a53

GIC_VERSION:=GICV2

drivers = pl011_uart

platform_description:=hikey960_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
