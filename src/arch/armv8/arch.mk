## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

ARCH_SUB?=aarch64
arch_sub_dir:=$(cpu_arch_dir)/$(ARCH_SUB)
include $(arch_sub_dir)/arch_sub.mk
src_dirs+=$(arch_sub_dir)

ARCH_PROFILE?=armv8-a
arch_profile_dir:=$(cpu_arch_dir)/$(ARCH_PROFILE)
include $(arch_profile_dir)/profile.mk
src_dirs+=$(arch_profile_dir)

src_dirs+=$(arch_profile_dir)/cpus

arch_profile_sub_dir:=$(arch_profile_dir)/$(ARCH_SUB)
src_dirs+=$(arch_profile_sub_dir)

arch-cppflags+=-DGIC_VERSION=$(GIC_VERSION)
ifeq ($(CC_IS_GCC),y)
arch-cflags+=-mgeneral-regs-only
endif
arch-asflags+=
arch-ldflags+=

