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

# Default to SMMUv2 so platforms that don't care about the IOMMU (or predate
# the v2/v3 split) keep compiling. Platforms select v3 in their platform.mk.
SMMU_VERSION?=2
arch-cppflags+=-DSMMU_VERSION=$(SMMU_VERSION)
ifeq ($(CC_IS_GCC),y)
arch-cflags+=-mgeneral-regs-only
endif
arch-asflags+=
arch-ldflags+=

