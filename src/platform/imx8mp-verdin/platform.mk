## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a53

GIC_VERSION:=GICV3

drivers = imx_uart

platform_description:=desc.c

platform-cppflags =
platform-cflags = -mcpu=$(CPU)
platform-asflags =
platform-ldflags =
