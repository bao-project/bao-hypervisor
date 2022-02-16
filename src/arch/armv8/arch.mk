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

ARCH_PROFILE?=armv8-a
arch_profile_dir:=$(cpu_arch_dir)/$(ARCH_PROFILE)
include $(arch_profile_dir)/profile.mk
src_dirs+=$(arch_profile_dir)

arch-cppflags+=-DGIC_VERSION=$(GIC_VERSION)
arch-cflags+=
arch-asflags+=
arch-ldflags+=
