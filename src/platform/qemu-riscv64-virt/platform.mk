## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=riscv
# CPU definition
CPU:=
# Interrupt controller definition
IRQC:=PLIC
# Core IPIs controller
IPIC:=IPIC_SBI

drivers := sbi_uart

platform_description:=virt_desc.c

platform-cppflags =-DIPIC=$(IPIC)
platform-cflags = 
platform-asflags =
platform-ldflags =
