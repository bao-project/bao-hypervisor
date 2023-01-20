## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=cache.o
cpu-objs-y+=interrupts.o
cpu-objs-y+=vm.o
cpu-objs-y+=aborts.o
cpu-objs-y+=cpu.o
cpu-objs-y+=platform.o
cpu-objs-y+=gic.o
cpu-objs-y+=vgic.o
cpu-objs-y+=vmm.o
cpu-objs-y+=psci.o

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
