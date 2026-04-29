## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=riscv
ARCH_SUB:=riscv64

# Interrupt controller: APLIC + IMSIC (AIA)
IRQC:=AIA
# Inter-processor interrupts via SBI (no ACLINT SSWI on AE350)
IPIC:=IPIC_SBI

drivers:=sbi_uart

platform_description:=ae350_desc.c

platform-cppflags=-DIPIC=$(IPIC)
platform-cflags=
platform-asflags=
platform-ldflags=
