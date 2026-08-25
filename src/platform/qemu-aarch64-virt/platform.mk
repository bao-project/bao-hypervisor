## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.



drivers = pl011_uart

platform_description:=virt_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
