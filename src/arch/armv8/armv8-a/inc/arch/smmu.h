/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_SMMU_H__
#define __ARCH_SMMU_H__

/*
 * Version-selecting shim. The platform's SMMU_VERSION (default 2, see
 * arch/armv8/arch.mk) picks the concrete driver header. Both headers must
 * provide `typedef deviceid_t streamid_t;` so the generic platform/vm/iommu
 * structures compile regardless of the selected version.
 */
#if (SMMU_VERSION == 3)
#include <arch/smmuv3.h>
#else
#include <arch/smmuv2.h>
#endif

#endif /* __ARCH_SMMU_H__ */
