/**
 * baohu separation kernel
 *
 * Copyright (c) Jose Martins, Sandro Pinto, David Cerdeira
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <josemartins90@gmail.com>
 *
 * baohu is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <iommu.h>
#include <arch/smmuv2.h>

int iommu_arch_init()
{
    smmu_init();

    return 0;
}

static int32_t iommu_vm_arch_init_ctx(vm_t *vm)
{
    int32_t ctx_id = vm->iommu.arch.ctx_id;
    if (ctx_id < 0) {

        /* Set up ctx bank to vm address space in an available ctx. */
        ctx_id = smmu_alloc_ctxbnk();
        if (ctx_id >= 0) {
            uint64_t rootpt;
            mem_translate(&cpu.as, vm->as.pt.root, &rootpt);
            smmu_write_ctxbnk(ctx_id, (void *)rootpt, vm->id);
            vm->iommu.arch.ctx_id = ctx_id;
        } else {
            ERROR("iommu: could not allocate ctx for vm: %d", vm->id);
        }
    }

    /* Ctx is valid when we get here. */
    return ctx_id;
}

static int iommu_vm_arch_add(vm_t *vm, uint16_t mask, uint16_t id)
{
    uint32_t vm_ctx = iommu_vm_arch_init_ctx(vm);
    uint16_t glbl_mask = vm->iommu.arch.global_mask;
    uint16_t prep_mask = (mask & SMMU_ID_MSK) | glbl_mask;
    uint16_t prep_id = (id & SMMU_ID_MSK);
    bool group = (bool) mask;

    if (!smmu_compatible_sme_exists(prep_mask, prep_id, vm_ctx, group)) {
        uint32_t sme = smmu_alloc_sme();
        smmu_write_sme(sme, prep_mask, prep_id, group);
        smmu_write_s2c(sme, vm_ctx);
    }

    return 0;
}

inline int iommu_arch_vm_add_device(vm_t *vm, int id)
{
    return iommu_vm_arch_add(vm, 0, id);
}

int iommu_arch_vm_init(vm_t *vm, const vm_config_t *config)
{
    uint32_t glbl_mask = config->platform.arch.smmu.global_mask;
    vm->iommu.arch.global_mask = glbl_mask;
    vm->iommu.arch.ctx_id = -1;

    /* This section relates only to arm's iommu so we parse it here. */
    for (int i = 0; i < config->platform.arch.smmu.group_num; i++) {
        /* Register each group. */
        const struct smmu_group *group =
            &config->platform.arch.smmu.smmu_groups[i];
        iommu_vm_arch_add(vm, group->group_mask, group->group_id);
    }

    return 0;
}
