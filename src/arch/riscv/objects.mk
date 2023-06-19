## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=boot.o
cpu-objs-y+=exceptions.o
cpu-objs-y+=root_pt.o
cpu-objs-y+=sbi.o
cpu-objs-y+=page_table.o
cpu-objs-y+=mem.o
cpu-objs-y+=vm.o
cpu-objs-y+=vmm.o
cpu-objs-y+=plic.o 
cpu-objs-y+=interrupts.o
cpu-objs-y+=sync_exceptions.o
cpu-objs-y+=vplic.o
cpu-objs-y+=cpu.o
cpu-objs-y+=cache.o
cpu-objs-y+=iommu.o
cpu-objs-y+=relocate.o
