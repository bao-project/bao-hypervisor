## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=tricore



drivers = 8250_uart

platform_description:=tc49_desc.c

TRICORE_MCPU=tc49Ax

platform-cppflags =
platform-cflags = -gdwarf-4
platform-asflags =
platform-ldflags =
