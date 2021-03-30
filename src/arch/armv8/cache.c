/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
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
#include <platform.h>

void cache_arch_enumerate(cache_t *dscrp)
{
    if(platform.cache.lvls != 0 ) {
        /**
         * No need to probe cache registers, cache topology is described
         * in the platform descrption.
         */
        *dscrp = platform.cache;
    }

    uint64_t clidr = 0;
    uint64_t temp = 0;
    bool first_unified = false;

    dscrp->lvls = 0;

    clidr = MRS(CLIDR_EL1);
    for(int i = 0; i < CLIDR_CTYPE_NUM; i++){
        if((temp = bit_extract(clidr, i*CLIDR_CTYPE_LEN, CLIDR_CTYPE_LEN)) != 0){
            dscrp->lvls++;
            switch(temp){
                case CLIDR_CTYPE_IO:
                dscrp->type[i] = INSTRUCTION;
                break;
                case CLIDR_CTYPE_DO:
                dscrp->type[i] = DATA;
                break;
                case CLIDR_CTYPE_SP:
                dscrp->type[i] = SEPARATE;
                break;
                case CLIDR_CTYPE_UN:
                dscrp->type[i] = UNIFIED;
                break;
            }
        } else {
            break;
        }
    }

    for(int lvl = 0; lvl < dscrp->lvls; lvl++){
        
        uint64_t csselr = 0;
        uint64_t ccsidr = 0;
        uint64_t ctr = 0;
        csselr = bit_insert(csselr, lvl, CSSELR_LVL_OFF, CSSELR_LVL_LEN);

        if(dscrp->type[lvl] == UNIFIED && first_unified == false){
            first_unified = true;
            dscrp->min_shared_lvl = lvl;
        }

        if(dscrp->type[lvl] != INSTRUCTION){
            csselr = bit_clear(csselr, CSSELR_IND_BIT);
            MSR(CSSELR_EL1, csselr);
            ccsidr = MRS(CCSIDR_EL1);

            dscrp->line_size[lvl][0] = 1UL << (bit_extract(ccsidr, 
                CCSIDR_LINESIZE_OFF, CCSIDR_LINESIZE_LEN) + 4);
            dscrp->assoc[lvl][0] = bit_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF, 
                CCSIDR_ASSOCIATIVITY_LEN) + 1;
            dscrp->numset[lvl][0] = bit_extract(ccsidr, CCSIDR_NUMSETS_OFF, 
                CCSIDR_NUMSETS_LEN) + 1;

            dscrp->indexed[lvl][0] = PIPT;
        }
        
        if(dscrp->type[lvl] == SEPARATE || dscrp->type[lvl] == INSTRUCTION){
            csselr = bit_set(csselr, CSSELR_IND_BIT);
            MSR(CSSELR_EL1, csselr);
            ccsidr = MRS(CCSIDR_EL1);

            dscrp->line_size[lvl][1] = 1UL << (bit_extract(ccsidr, 
                CCSIDR_LINESIZE_OFF, CCSIDR_LINESIZE_LEN) + 4);
            dscrp->assoc[lvl][1] = bit_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF, 
                CCSIDR_ASSOCIATIVITY_LEN) + 1;
            dscrp->numset[lvl][1] = bit_extract(ccsidr, CCSIDR_NUMSETS_OFF, 
                CCSIDR_NUMSETS_LEN) + 1;

            ctr = MRS(CTR_EL0);
            if((ctr & BIT_MASK(CTR_L1LP_OFF, CTR_L1LP_LEN)) == CTR_L1LP_PIPT){
                dscrp->indexed[lvl][1] = PIPT;
            } else {
                dscrp->indexed[lvl][1] = VIPT;
            }
        }

    }
}

void cache_flush_range(void* base, uint64_t size)
{
    uint64_t cache_addr = (uint64_t)base;
    uint64_t ctr = MRS(CTR_EL0);
    uint64_t min_line_size = 1UL << bit_extract(ctr, CTR_DMINLINE_OFF, 
        CTR_DMINLINE_LEN);

    while(cache_addr < ((uint64_t)base + size)){
        asm volatile (
            "dc civac, %0\n\t" 
            :: "r"(cache_addr));
        cache_addr += min_line_size;
    }

    DMB(ish);
}
