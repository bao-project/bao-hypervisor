## SPDX-License-Identifier: Apache-2.0
ARCH := armv8
CPU := cortex-a53
GIC_VERSION := GICV3
drivers = 8250_uart
platform_description := atk_dlam62xb_desc.c
platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
