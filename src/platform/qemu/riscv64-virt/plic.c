/** 
 * baohu separation kernel
 *
 * Copyright (c) Jose Martins, Sandro Pinto
 *
 * Authors:
 *      Jose Martins <josemartins90@gmail.com>
 *
 * baohu is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#include <arch/plic.h>
#include <arch/csrs.h>

int plic_plat_cntxt_to_id(plic_cntxt_t cntxt){
    if(cntxt.mode != PRIV_M && cntxt.mode != PRIV_S) return -1;
    return (cntxt.hart_id*2) + (cntxt.mode == PRIV_M ? 0 : 1);
}

plic_cntxt_t plic_plat_id_to_cntxt(int id){
    plic_cntxt_t cntxt;
    if(id < PLIC_PLAT_CNTXT_NUM){
        cntxt.hart_id = id/2;
        cntxt.mode = (id%2) == 0 ? PRIV_M : PRIV_S; 
    } else {
        return (plic_cntxt_t){-1};
    }
    return cntxt;
}