## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a72

#needs to be checked
GIC_VERSION:=GICV3

drivers = 8250_uart mailbox firmware

platform_description:=bb-ai64_desc.c

platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
