## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_PROFILE)/pagetables.o
cpu-objs-y+=$(ARCH_PROFILE)/page_table.o
cpu-objs-y+=$(ARCH_PROFILE)/mem.o
cpu-objs-y+=$(ARCH_PROFILE)/vm.o
cpu-objs-y+=$(ARCH_PROFILE)/vmm.o
cpu-objs-y+=$(ARCH_PROFILE)/psci.o
ifeq ($(SMMU_VERSION), 3)
cpu-objs-y+=$(ARCH_PROFILE)/smmuv3.o
else
cpu-objs-y+=$(ARCH_PROFILE)/smmuv2.o
endif
cpu-objs-y+=$(ARCH_PROFILE)/iommu.o
cpu-objs-y+=$(ARCH_PROFILE)/cpu.o
cpu-objs-y+=$(ARCH_PROFILE)/smc.o
