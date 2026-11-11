## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

## Milk-V Megrez / ESWIN EIC7700X (4x SiFive P550, RV64GC + H)

# The EIC7700X UARTs are Synopsys DesignWare APB blocks, which are 8250-compatible.
drivers := 8250_uart

platform_description:=megrez_desc.c

platform-cppflags =-DIPIC=$(IPIC)
platform-cflags =
platform-asflags =
platform-ldflags =
