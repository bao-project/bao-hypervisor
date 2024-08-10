## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=irqc/$(IRQC_DIR)/aplic.o
cpu-objs-y+=irqc/$(IRQC_DIR)/vaplic.o
ifeq ($(IRQC), AIA)
cpu-objs-y+=irqc/$(IRQC_DIR)/imsic.o
cpu-objs-y+=irqc/$(IRQC_DIR)/vimsic.o
else ifeq ($(IRQC),)
$(error Platform must define IRQC)
endif
