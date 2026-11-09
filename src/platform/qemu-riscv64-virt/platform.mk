## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=riscv
# CPU definition
CPU:=
# Interrupt controller definition
IRQC:=AIA
# Core IPIs controller
IPIC:=IPIC_SBI

drivers := sbi_uart

CONFIG_EARLYCON ?= n
CONFIG_RISCV_EARLYCON_SBI ?= y
ifeq ($(CONFIG_EARLYCON),y)
ifeq ($(CONFIG_RISCV_EARLYCON_SBI),y)
drivers += sbi_earlycon
endif
endif

platform_description:=virt_desc.c

platform-cppflags =-DIPIC=$(IPIC)
platform-cflags = 
platform-asflags =
platform-ldflags =
