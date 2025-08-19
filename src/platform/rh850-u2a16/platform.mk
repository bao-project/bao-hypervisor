## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=rh850
ARCH_PROFILE:=main
drivers:=renesas_rlin3

platform_description:=u2a16_desc.c

platform-cppflags =
platform-cflags = -gdwarf-4
platform-asflags = -gdwarf-4
platform-ldflags =

plat_mem:=non_unified
