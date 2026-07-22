## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# big.LITTLE (2x A76 + 2x A55); tune for A55 as the common baseline
CPU:=cortex-a55

GIC_VERSION:=GICV3

# Board DDR capacity in GiB; selects mem_regions in agilex5_desc.c.
# Override via configs/<CONFIG>/config.mk or the make command line.
AGX5_MEM_GB ?= 2

drivers = 8250_uart

platform_description:=agilex5_desc.c

platform-cppflags = -DAGX5_MEM_GB=$(AGX5_MEM_GB)
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
