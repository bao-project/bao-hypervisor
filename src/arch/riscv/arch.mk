## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= riscv64-unknown-elf-

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

arch-cppflags+=-DIRQC=$(IRQC)
arch-cflags = -mcmodel=medany -march=rv64g -mstrict-align
arch-asflags =
arch-ldflags = 

arch_mem_prot:=mmu
PAGE_SIZE:=0x1000
