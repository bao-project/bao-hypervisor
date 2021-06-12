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

CROSS_COMPILE ?= aarch64-none-elf-

arch-cppflags = -DGIC_VERSION=$(GIC_VERSION)
arch-cflags = -march=armv8-a -mcmodel=large -mgeneral-regs-only
arch-asflags =
arch-ldflags =
