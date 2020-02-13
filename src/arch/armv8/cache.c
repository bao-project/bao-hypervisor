/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#include <cache.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <bit.h>

extern cache_t cache_dscr;

void cache_arch_enumerate()
{
    uint64_t clidr = 0;
    uint64_t temp = 0;
    bool first_unified = false;

    cache_dscr.lvls = 0;

    MRS(clidr, CLIDR_EL1);
    for (int i = 0; i < CLIDR_CTYPE_NUM; i++) {
        if ((temp = bit_extract(clidr, i * CLIDR_CTYPE_LEN, CLIDR_CTYPE_LEN)) !=
            0) {
            cache_dscr.lvls++;
            switch (temp) {
                case CLIDR_CTYPE_IO:
                    cache_dscr.type[i] = INSTRUCTION;
                    break;
                case CLIDR_CTYPE_DO:
                    cache_dscr.type[i] = DATA;
                    break;
                case CLIDR_CTYPE_SP:
                    cache_dscr.type[i] = SEPARATE;
                    break;
                case CLIDR_CTYPE_UN:
                    cache_dscr.type[i] = UNIFIED;
                    break;
            }
        } else {
            break;
        }
    }

    for (int lvl = 0; lvl < cache_dscr.lvls; lvl++) {
        uint64_t csselr = 0;
        uint64_t ccsidr = 0;
        uint64_t ctr = 0;
        csselr = bit_insert(csselr, lvl, CSSELR_LVL_OFF, CSSELR_LVL_LEN);

        if (cache_dscr.type[lvl] == UNIFIED && first_unified == false) {
            first_unified = true;
            cache_dscr.min_shared_lvl = lvl;
        }

        if (cache_dscr.type[lvl] != INSTRUCTION) {
            csselr = bit_clear(csselr, CSSELR_IND_BIT);
            MSR(CSSELR_EL1, csselr);
            MRS(ccsidr, CCSIDR_EL1);

            cache_dscr.line_size[lvl][UNIFIED] =
                1UL << (bit_extract(ccsidr, CCSIDR_LINESIZE_OFF,
                                    CCSIDR_LINESIZE_LEN) +
                        4);
            cache_dscr.assoc[lvl][UNIFIED] =
                bit_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF,
                            CCSIDR_ASSOCIATIVITY_LEN) +
                1;
            cache_dscr.numset[lvl][UNIFIED] =
                bit_extract(ccsidr, CCSIDR_NUMSETS_OFF, CCSIDR_NUMSETS_LEN) + 1;

            cache_dscr.indexed[lvl][UNIFIED] = PIPT;
        }

        if (cache_dscr.type[lvl] == SEPARATE ||
            cache_dscr.type[lvl] == INSTRUCTION) {
            csselr = bit_set(csselr, CSSELR_IND_BIT);
            MSR(CSSELR_EL1, csselr);
            MRS(ccsidr, CCSIDR_EL1);

            cache_dscr.line_size[lvl][INSTRUCTION] =
                1UL << (bit_extract(ccsidr, CCSIDR_LINESIZE_OFF,
                                    CCSIDR_LINESIZE_LEN) +
                        4);
            cache_dscr.assoc[lvl][INSTRUCTION] =
                bit_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF,
                            CCSIDR_ASSOCIATIVITY_LEN) +
                1;
            cache_dscr.numset[lvl][INSTRUCTION] =
                bit_extract(ccsidr, CCSIDR_NUMSETS_OFF, CCSIDR_NUMSETS_LEN) + 1;

            MRS(ctr, CTR_EL0);
            if ((ctr & BIT_MASK(CTR_L1LP_OFF, CTR_L1LP_LEN)) == CTR_L1LP_PIPT) {
                cache_dscr.indexed[lvl][INSTRUCTION] = PIPT;
            } else {
                cache_dscr.indexed[lvl][INSTRUCTION] = VIPT;
            }
        }
    }
}

void cache_cleanall(enum cache_type type)
{
    if (type > INSTRUCTION) return;

    for (int i = 0; i < cache_dscr.lvls; i++) {
        /* Fast log2 counting leading zeroes */
        uint32_t way_position = bit_clz32(cache_dscr.assoc[i][type]);
        uint64_t line_size = cache_dscr.line_size[i][type];

        for (int j = 0; j < cache_dscr.assoc[i][type]; j++) {
            for (int k = 0; k < cache_dscr.numset[i][type]; k++) {
                uint64_t line = (j << way_position) | i; /* Way */
                line |= (k << line_size);                /* Set */

                asm volatile("dc csw, %0\n\t" ::"r"(line));
            }
        }
    }

    DMB(ish);
}

void cache_flush_range(void* base, uint64_t size)
{
    uint64_t cache_addr = (uint64_t)base;
    uint64_t ctr;
    MRS(ctr, CTR_EL0);
    uint64_t min_line_size =
        1UL << bit_extract(ctr, CTR_DMINLINE_OFF, CTR_DMINLINE_LEN);

    while (cache_addr < ((uint64_t)base + size)) {
        asm volatile("dc cvac, %0\n\t" ::"r"(cache_addr));
        cache_addr += min_line_size;
    }

    DMB(ish);
}
