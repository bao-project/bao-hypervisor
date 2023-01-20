## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_PROFILE)/$(ARCH_SUB)/boot.o
cpu-objs-y+=$(ARCH_PROFILE)/$(ARCH_SUB)/relocate.o
cpu-objs-y+=$(ARCH_PROFILE)/$(ARCH_SUB)/vmm.o
