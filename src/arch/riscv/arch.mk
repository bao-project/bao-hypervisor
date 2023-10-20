## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

ARCH_SUB?=riscv64

ifeq ($(ARCH_SUB), riscv64)
CROSS_COMPILE ?= riscv64-unknown-elf-
riscv_march:=rv64imac_zicsr
riscv_mabi:=lp64
ld_emulation:=elf64lriscv
else ifeq ($(ARCH_SUB), riscv32)
CROSS_COMPILE ?= riscv32-unknown-elf-
riscv_march:=rv32imac_zicsr
riscv_mabi:=ilp32
ld_emulation:=elf32lriscv
else
$(error RISC-V $(ARCH_SUB) not supported!)
endif

# Interrupt controller source files
ifeq ($(IRQC), PLIC)
IRQC_DIR?=plic
else ifeq ($(IRQC), APLIC)
IRQC_DIR?=aia
else ifeq ($(IRQC),)
$(error Platform must define IRQC)
else
$(error Invalid IRQC $(IRQC))
endif

irqc_arch_dir=$(cpu_arch_dir)/irqc/$(IRQC_DIR)
src_dirs+=$(irqc_arch_dir)

ifeq ($(ARCH_SUB), riscv64)
arch-cppflags+=-DRV_XLEN=64
else ifeq ($(ARCH_SUB), riscv32)
arch-cppflags+=-DRV_XLEN=32
endif
arch-cppflags+=-DIRQC=$(IRQC)
arch-cflags = -mcmodel=medany -march=$(riscv_march) -mstrict-align \
	-mabi=$(riscv_mabi)
arch-asflags =
arch-ldflags = -m $(ld_emulation)

arch_mem_prot:=mmu
PAGE_SIZE:=0x1000

clang_arch_target:=riscv64
