## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.


ARCH:=armv8
ARCH_SUB:=aarch32
ARCH_PROFILE:=armv8-r

GIC_VERSION:=GICV3

drivers = cmsdk_uart

platform_description:=mps3_desc.c

platform-cppflags =
platform-cflags = -gdwarf-4
platform-asflags =
platform-ldflags =
