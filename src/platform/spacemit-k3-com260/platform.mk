## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# SpacemiT K3 (X100 cluster) - e.g. CoM260 Kit
#
# Only the 8 X100 application harts (cpu@0-7) implement the RISC-V hypervisor
# (H) extension, so Bao runs on those. The A100 harts (cpu@8-15) lack H and are
# intentionally left out of the platform description.

# Architecture definition
ARCH:=riscv
# CPU definition
CPU:=
# Interrupt controller definition (Advanced Interrupt Architecture: APLIC + IMSIC)
IRQC:=AIA
# Core IPIs controller (SBI IPI, provided by the resident M-mode OpenSBI)
IPIC:=IPIC_SBI

# The hypervisor drives the K3 UART0 directly for its own debug output. The K3
# UART (spacemit,k1-uart / intel,xscale-uart) is a 16550/8250-compatible block
# with 32-bit registers spaced 4 bytes apart (reg-shift=2, reg-io-width=4) - the
# same UART OpenSBI drives with its generic 8250 driver - so Bao's stock
# 8250_uart driver covers it directly (see UART8250_REG_WIDTH in platform.h).
# The same UART0 is also passed through to the guest (see configs/spacemit-k3-com260),
# so during early boot the two briefly share the line, which is fine for bring-up.
drivers := 8250_uart

platform_description:=spacemit_k3_desc.c

platform-cppflags =-DIPIC=$(IPIC)
platform-cflags =
platform-asflags =
platform-ldflags =
