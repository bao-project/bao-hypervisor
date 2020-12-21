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

cpu-objs-y+=boot.o
cpu-objs-y+=exceptions.o
cpu-objs-y+=pagetables.o
cpu-objs-y+=page_table.o
cpu-objs-y+=cache.o
cpu-objs-y+=interrupts.o
cpu-objs-y+=mem.o
cpu-objs-y+=vmm.o
cpu-objs-y+=vm.o
cpu-objs-y+=aborts.o
cpu-objs-y+=smc.o
cpu-objs-y+=psci.o
cpu-objs-y+=cpu.o
cpu-objs-y+=platform.o
cpu-objs-y+=relocate.o
cpu-objs-y+=iommu.o
cpu-objs-y+=smmuv2.o
cpu-objs-y+=gic.o
cpu-objs-y+=vgic.o
cpu-objs-y+=config.o

ifeq ($(GIC_VERSION), GICV2)
	cpu-objs-y+=vgicv2.o
	cpu-objs-y+=gicv2.o
else ifeq ($(GIC_VERSION), GICV3)
	cpu-objs-y+=vgicv3.o
	cpu-objs-y+=gicv3.o
else ifeq ($(GIC_VERSION),)
$(error Platform must define GIC_VERSION)
else
$(error Invalid GIC version $(GIC_VERSION))
endif
