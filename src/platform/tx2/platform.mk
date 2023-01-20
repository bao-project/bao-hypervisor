## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a57

GIC_VERSION:=GICV2

# TODO: Driver missing, should be 8250 compatible
drivers = 8250_uart

platform_description:=tx2_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
