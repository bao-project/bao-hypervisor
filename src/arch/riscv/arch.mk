## SPDX-License-Identifier: GPL-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE := riscv64-unknown-elf-

arch-cppflags = 
arch-cflags = -mcmodel=medany -march=rv64g -mstrict-align
arch-asflags =
arch-ldflags = -z common-page-size=0x1000

arch_mem_prot:=mmu

# Interrupt controller source files
irqc_arch_dir=$(src_dir)/arch/riscv/irqc/$(IRQC)