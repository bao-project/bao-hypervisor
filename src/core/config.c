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

#include <config.h>

void config_adjust_to_va(struct config *config, uint64_t phys)
{
    adjust_ptr(config->shmemlist, config);

    for (int i = 0; i < config->vmlist_size; i++) {
        adjust_ptr(config->vmlist[i].image.load_addr, phys);

	    adjust_ptr(config->vmlist[i].platform.regions, config);

	    if(adjust_ptr(config->vmlist[i].platform.devs, config)){
	        for (int j = 0; j < config->vmlist[i].platform.dev_num; j++) {
	    	    adjust_ptr(config->vmlist[i].platform.devs[j].interrupts, config);
	        }
	    }

	    if(adjust_ptr(config->vmlist[i].platform.ipcs, config)){
	        for (int j = 0; j < config->vmlist[i].platform.ipc_num; j++) {
	    	    adjust_ptr(config->vmlist[i].platform.ipcs[j].interrupts, config);
	        }
	    }
    }

    config_arch_adjust_to_va(config, phys);
}

bool config_is_builtin() {
    extern uint8_t _config_start, _config_end;
    return &_config_start != &_config_end;
}
