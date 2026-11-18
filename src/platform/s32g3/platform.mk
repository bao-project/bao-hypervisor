## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.



drivers = linflexd_uart

platform_description:=s32g3_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
