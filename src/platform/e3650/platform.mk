## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
ARCH_PROFILE:=armv8-r
ARCH_SUB:=aarch32

GIC_VERSION:=GICV3

drivers=e3650_uart

platform-cppflags=
platform-cflags=-gdwarf-4
platform-asflags=
platform-ldflags=

platform_description:=e3650_desc.c


