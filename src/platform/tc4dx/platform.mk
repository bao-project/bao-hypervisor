## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=tricore

drivers = asclin_uart

platform_description:=tc4dx_desc.c

TRICORE_MCPU=tc4DAx

platform-cppflags =
platform-cflags=-mcpu=$(TRICORE_MCPU) -gdwarf-4
platform-asflags=-mcpu=$(TRICORE_MCPU)
platform-ldflags=--mcpu=tc18 --no-warn-rwx-segments