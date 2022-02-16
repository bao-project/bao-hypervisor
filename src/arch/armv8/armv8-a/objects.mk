## 
 # Bao, a Lightweight Static Partitioning Hypervisor 
 #
 # Copyright (c) Bao Project (www.bao-project.org), 2019-
 #
 # Authors:
 #      Jose Martins <jose.martins@bao-project.org>
 #
 # Bao is free software; you can redistribute it and/or modify it under the
 # terms of the GNU General Public License version 2 as published by the Free
 # Software Foundation, with a special exception exempting guest code from such
 # license. See the COPYING file in the top-level directory for details. 
 #
##

cpu-objs-y+=$(ARCH_PROFILE)/boot.o
cpu-objs-y+=$(ARCH_PROFILE)/exceptions.o
cpu-objs-y+=$(ARCH_PROFILE)/pagetables.o
cpu-objs-y+=$(ARCH_PROFILE)/page_table.o
cpu-objs-y+=$(ARCH_PROFILE)/cpu.o
cpu-objs-y+=$(ARCH_PROFILE)/mem.o
cpu-objs-y+=$(ARCH_PROFILE)/vm.o
cpu-objs-y+=$(ARCH_PROFILE)/vmm.o
cpu-objs-y+=$(ARCH_PROFILE)/smc.o
cpu-objs-y+=$(ARCH_PROFILE)/psci.o
cpu-objs-y+=$(ARCH_PROFILE)/relocate.o
cpu-objs-y+=$(ARCH_PROFILE)/smmuv2.o
cpu-objs-y+=$(ARCH_PROFILE)/iommu.o
cpu-objs-y+=$(ARCH_PROFILE)/aborts.o
