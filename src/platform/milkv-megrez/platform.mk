## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

## Milk-V Megrez / ESWIN EIC7700X (4x SiFive P550, RV64GC + H)

# Architecture definition
ARCH:=riscv
# CPU definition (riscv march is set by the arch makefile; no -mtune needed)
CPU:=
# Interrupt controller definition: sifive,plic-1.0.0
IRQC:=PLIC
# Core IPIs controller: the EIC7700X exposes no ACLINT SSWI node, so route IPIs
# through SBI
IPIC:=IPIC_SBI
# SiFive P550 is pre-1.12 (OpenSBI reports priv v1.11); no envcfg CSRs.
RISCV_PRIV_VERSION := RISCV_PRIV_VERSION_1_11
# The EIC7700X UARTs are Synopsys DesignWare APB blocks, which are 8250-compatible.
drivers := 8250_uart

platform_description:=megrez_desc.c

platform-cppflags =-DIPIC=$(IPIC)
platform-cflags =
platform-asflags =
platform-ldflags =
