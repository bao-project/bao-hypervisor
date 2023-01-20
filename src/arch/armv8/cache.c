/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <cache.h>
#include <arch/sysregs.h>
#include <fences.h>
#include <bit.h>
#include <platform.h>

void cache_arch_enumerate(struct cache *dscrp)
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

    clidr = sysreg_clidr_el1_read();
    for(size_t i = 0; i < CLIDR_CTYPE_NUM; i++){
        if((temp = bit64_extract(clidr, i*CLIDR_CTYPE_LEN, CLIDR_CTYPE_LEN)) != 0){
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

    for(size_t lvl = 0; lvl < dscrp->lvls; lvl++){
        
        uint64_t csselr = 0;
        uint64_t ccsidr = 0;
        uint64_t ctr = 0;
        csselr = bit64_insert(csselr, lvl, CSSELR_LVL_OFF, CSSELR_LVL_LEN);

        if(dscrp->type[lvl] == UNIFIED && first_unified == false){
            first_unified = true;
            dscrp->min_shared_lvl = lvl;
        }

        if(dscrp->type[lvl] != INSTRUCTION){
            csselr = bit64_clear(csselr, CSSELR_IND_BIT);
            sysreg_csselr_el1_write(csselr);
            ccsidr = sysreg_ccsidr_el1_read();

            dscrp->line_size[lvl][0] = 1UL << (bit64_extract(ccsidr, 
                CCSIDR_LINESIZE_OFF, CCSIDR_LINESIZE_LEN) + 4);
            dscrp->assoc[lvl][0] = bit64_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF, 
                CCSIDR_ASSOCIATIVITY_LEN) + 1;
            dscrp->numset[lvl][0] = bit64_extract(ccsidr, CCSIDR_NUMSETS_OFF, 
                CCSIDR_NUMSETS_LEN) + 1;

            dscrp->indexed[lvl][0] = PIPT;
        }
        
        if(dscrp->type[lvl] == SEPARATE || dscrp->type[lvl] == INSTRUCTION){
            csselr = bit64_set(csselr, CSSELR_IND_BIT);
            sysreg_csselr_el1_write(csselr);
            ccsidr = sysreg_ccsidr_el1_read();

            dscrp->line_size[lvl][1] = 1UL << (bit64_extract(ccsidr, 
                CCSIDR_LINESIZE_OFF, CCSIDR_LINESIZE_LEN) + 4);
            dscrp->assoc[lvl][1] = bit64_extract(ccsidr, CCSIDR_ASSOCIATIVITY_OFF, 
                CCSIDR_ASSOCIATIVITY_LEN) + 1;
            dscrp->numset[lvl][1] = bit64_extract(ccsidr, CCSIDR_NUMSETS_OFF, 
                CCSIDR_NUMSETS_LEN) + 1;

            ctr = sysreg_ctr_el0_read();
            if((ctr & BIT64_MASK(CTR_L1LP_OFF, CTR_L1LP_LEN)) == CTR_L1LP_PIPT){
                dscrp->indexed[lvl][1] = PIPT;
            } else {
                dscrp->indexed[lvl][1] = VIPT;
            }
        }

    }
}

void cache_flush_range(vaddr_t base, size_t size)
{
    vaddr_t cache_addr = base;
    uint64_t ctr = sysreg_ctr_el0_read();
    size_t min_line_size = 1UL << bit64_extract(ctr, CTR_DMINLINE_OFF,
        CTR_DMINLINE_LEN);

    while(cache_addr < (base + size)){
        arm_dc_civac(cache_addr);
        cache_addr += min_line_size;
    }

    DMB(ish);
}
