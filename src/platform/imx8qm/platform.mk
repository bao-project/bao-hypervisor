## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a53

GIC_VERSION:=GICV3

drivers = nxp_uart

platform_description:=imx8qm_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
