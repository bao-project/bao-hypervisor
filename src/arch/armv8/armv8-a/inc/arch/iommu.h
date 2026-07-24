/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __IOMMU_ARCH_H__
#define __IOMMU_ARCH_H__

#include <bao.h>
#include <arch/smmu.h>

#if (SMMU_VERSION == 3)
/*
 * SMMUv3 is stage-2-only here: each bound stream gets a Stream Table Entry that
 * points directly at the VM's stage-2 page table (vm->as.pt.root) tagged with
 * the VM's id as S2VMID. No per-VM context banks, so the only per-VM state we
 * track is whether the STE(s) have been installed.
 */
struct iommu_vm_arch {
    bool initialized;
};
#else
struct iommu_vm_arch {
    streamid_t global_mask;
    ssize_t ctx_id;
};
#endif

#endif
