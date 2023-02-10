## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a72

GIC_VERSION:=GICV2
RPI4_MEM_GB:=4

drivers = 8250_uart

platform_description:=rpi4_desc.c

platform-cppflags = -DRPI4_MEM_GB=$(RPI4_MEM_GB)
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
