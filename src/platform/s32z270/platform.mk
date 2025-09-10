## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
ARCH_PROFILE:=armv8-r
ARCH_SUB:=aarch32
# CPU definition
CPU:=cortex-r52

GIC_VERSION:=GICV3

drivers = linflexd_uart

platform_description:=s32z270_desc.c

plat_mem:=non_unified

platform-cppflags =
platform-cflags =
platform-asflags =
platform-ldflags =
