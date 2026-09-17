/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#include <stdio.h>
#include <platform.h>
#include <bao.h>

__attribute__((weak)) void arch_platform_defs(void){
    return;
}

/**
 * Whether the architecture's boot code places each cpu's structure through the generated base
 * table (PLAT_CPU_BASES). Ports that do override this in their own platform_defs_gen.c; the
 * others only build with an empty CONFIG_CPU_TCM_MASK.
 */
__attribute__((weak)) bool arch_cpu_private_placement(void){
    return false;
}

#ifndef CONFIG_CPU_TCM_MASK
#define CONFIG_CPU_TCM_MASK 0
#endif

/**
 * The region hosting a cpu's structure: the one affine to it that the description marks as its
 * home (cpu_home), or its only affine region; NULL when it has none. Fails on a description that
 * marks several homes or leaves several affine regions unmarked.
 */
static bool cpu_home_region(size_t cpu, struct mem_region** home)
{
    struct mem_region* only = NULL;
    size_t affine = 0;
    size_t homes = 0;

    *home = NULL;
    for (size_t i = 0; i < platform.region_num; i++) {
        struct mem_region* reg = &platform.regions[i];
        if (reg->cpu_affinity != (1UL << cpu)) {
            continue;
        }
        affine++;
        only = reg;
        if (reg->cpu_home) {
            homes++;
            *home = reg;
        }
    }
    if (homes > 1) {
        fprintf(stderr, "the platform marks %ld regions affine to cpu %ld as its home\n", homes,
            cpu);
        return false;
    }
    if ((homes == 0) && (affine > 1)) {
        fprintf(stderr, "cpu %ld has %ld affine regions but none is marked as its home "
            "(cpu_home)\n", cpu, affine);
        return false;
    }
    if (homes == 0) {
        *home = only;
    }
    return true;
}

/**
 * Cpu structure placement: cpus in CONFIG_CPU_TCM_MASK get the end of their home region
 * (CPU_TCM_END(base, size), resolved in cpu.c so that the structure occupies the last bytes of
 * the region and the guests can use it from its base), the others consecutive slots of a compact
 * global array (see cpu.c). Emits
 * PLAT_CPU_SLOT_NUM, PLAT_CPU_BASES and, when a cpu is placed in a coupled region,
 * PLAT_CPU_PRIVATE_MIN_SIZE, the smallest such region.
 */
static int cpu_placement_defs(void)
{
    unsigned long tcm_mask = CONFIG_CPU_TCM_MASK;
    size_t slot_num = 0;
    size_t min_size = 0;
    bool any_tcm = false;

    if (platform.cpu_num < 8 * sizeof(unsigned long) && (tcm_mask >> platform.cpu_num) != 0) {
        fprintf(stderr, "CONFIG_CPU_TCM_MASK names cpus beyond the platform's %ld cpus\n",
            platform.cpu_num);
        return 1;
    }
    bool has_tcm = false;
    for (size_t i = 0; i < platform.region_num; i++) {
        if (platform.regions[i].cpu_affinity != 0) {
            has_tcm = true;
        }
    }
#ifdef CONFIG_PLAT_HAS_TCM
    if (!has_tcm) {
        fprintf(stderr, "the platform selects PLAT_HAS_TCM but declares no cpu-coupled "
            "memory region\n");
        return 1;
    }
#else
    if (has_tcm) {
        fprintf(stderr, "the platform declares cpu-coupled memory regions but does not select "
            "PLAT_HAS_TCM\n");
        return 1;
    }
#endif
    if (tcm_mask != 0 && !arch_cpu_private_placement()) {
        fprintf(stderr, "CONFIG_CPU_TCM_MASK is not supported by this architecture's boot "
            "code yet\n");
        return 1;
    }

    printf("#define PLAT_CPU_BASES {");
    for (size_t cpu = 0; cpu < platform.cpu_num; cpu++) {
        const char* sep = cpu == 0 ? " " : ", ";
        struct mem_region* reg = NULL;
        if (!cpu_home_region(cpu, &reg)) {
            return 1;
        }
        if ((tcm_mask >> cpu) & 1UL) {
            if (reg == NULL) {
                fprintf(stderr, "cpu %ld is in CONFIG_CPU_TCM_MASK but the platform declares "
                    "no memory region affine to it\n", cpu);
                return 1;
            }
            if (!any_tcm || reg->size < min_size) {
                min_size = reg->size;
            }
            any_tcm = true;
            printf("%sCPU_TCM_END(0x%lx, 0x%lx)", sep, reg->base, reg->size);
        } else {
            printf("%sCPU_SLOT(%ld)", sep, slot_num++);
        }
    }
    printf(" }\n");
    printf("#define PLAT_CPU_SLOT_NUM (%ld)\n", slot_num);
    if (any_tcm) {
        printf("#define PLAT_CPU_PRIVATE_MIN_SIZE (0x%lx)\n", min_size);
    }
    return 0;
}

int main() {

    size_t bitmap_array_size = 0;

    printf("#define PLAT_CPU_NUM (%ld)\n", platform.cpu_num);
    printf("#define PLAT_BASE_ADDR (0x%lx)\n", platform.regions[0].base);

    for(size_t i = 1; i < platform.region_num; i++)
    {
        /*
         * Selects the first memory region with RWX (read, write, execute) permissions, and defines
         * it as PLAT_DATA_ADDR. This region is considered the main data memory that Bao will use
         * for its own purposes.
         */
        if(platform.regions[i].perms == MEM_RWX)
        {
            printf("#define PLAT_DATA_ADDR (0x%lx)\n", platform.regions[i].base);
            break;
        }
    }

    for(size_t i = 0; i < platform.region_num; i++)
    {
        size_t reg_size;
        /* Cpu-affine regions are never page pools */
        if (platform.regions[i].cpu_affinity != 0) {
            continue;
        }

        reg_size = platform.regions[i].size;

        bitmap_array_size += BITMAP_SIZE_IN_BYTES(NUM_PAGES(reg_size));
    }

    printf("#define PLAT_BITMAP_POOL_SIZE (0x%lx)\n", bitmap_array_size);

    if (platform.cpu_master_fixed) {
        printf("#define CPU_MASTER_FIXED (%ld)\n", platform.cpu_master);
    }
    if (cpu_placement_defs() != 0) {
        return 1;
    }

    // Call arch specific platform defines generator
    arch_platform_defs();
    return 0;
}
