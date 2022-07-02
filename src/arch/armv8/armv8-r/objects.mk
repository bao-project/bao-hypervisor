## SPDX-License-Identifier: GPL-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_PROFILE)/cpu.o
cpu-objs-y+=$(ARCH_PROFILE)/mem.o
cpu-objs-y+=$(ARCH_PROFILE)/vmm.o
cpu-objs-y+=$(ARCH_PROFILE)/vm.o
