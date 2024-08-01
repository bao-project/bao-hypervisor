/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/scr.h>
#include <arch/csrs.h>
#include <cpu.h>
#include <vm.h>
#include <bit.h>
#include <fences.h>
#include <hypercall.h>

enum { CORE_START };

static void scr_cpumsg_handler(uint32_t event, uint64_t data)
{
    UNUSED_ARG(data);

    switch (event) {
        default:
            WARNING("Unknown SCR IPI event");
            break;
    }
}

CPU_MSG_HANDLER(scr_cpumsg_handler, SCR_MSG_ID)

/* static struct scrret scr_hsm_start_handler() */
/* { */
/*     struct scrret ret; */
/*     vcpuid_t vcore_id = vcpu_readreg(cpu()->vcpu, REG_A0); */

/*     if (vcore_id == cpu()->vcpu->id) { */
/*         ret.error = SCR_ERR_ALREADY_AVAILABLE; */
/*     } else { */
/*         struct vcpu* vcpu = vm_get_vcpu(cpu()->vcpu->vm, vcore_id); */
/*         if (vcpu == NULL) { */
/*             ret.error = SCR_ERR_INVALID_PARAM; */
/*         } else { */
/*             spin_lock(&vcpu->arch.scr_ctx.lock); */
/*             if (vcpu->arch.scr_ctx.state == STARTED) { */
/*                 ret.error = SCR_ERR_ALREADY_AVAILABLE; */
/*             } else if (vcpu->arch.scr_ctx.state != STOPPED) { */
/*                 ret.error = SCR_ERR_FAILURE; */
/*             } else { */
/*                 vaddr_t start_addr = vcpu_readreg(cpu()->vcpu, REG_A1); */
/*                 unsigned priv = (unsigned)vcpu_readreg(cpu()->vcpu, REG_A2); */
/*                 vcpu->arch.scr_ctx.state = START_PENDING; */
/*                 vcpu->arch.scr_ctx.start_addr = start_addr; */
/*                 vcpu->arch.scr_ctx.priv = priv; */

/*                 fence_sync_write(); */

/*                 struct cpu_msg msg = { */
/*                     .handler = (uint32_t)SCR_MSG_ID, */
/*                     .event = CORE_START, */
/*                     .data = 0xdeadbeef, */
/*                 }; */
/*                 cpu_send_msg(vcpu->phys_id, &msg); */

/*                 ret.error = SCR_SUCCESS; */
/*             } */
/*             spin_unlock(&vcpu->arch.scr_ctx.lock); */
/*         } */
/*     } */

/*     return ret; */
/* } */

/* static struct scrret scr_hsm_status_handler() */
/* { */
/*     struct scrret ret; */
/*     vcpuid_t vcore_id = vcpu_readreg(cpu()->vcpu, REG_A0); */
/*     struct vcpu* vcore = vm_get_vcpu(cpu()->vcpu->vm, vcore_id); */

/*     if (vcore != NULL) { */
/*         ret.error = SCR_SUCCESS; */
/*         ret.value = vcore->arch.scr_ctx.state; */
/*     } else { */
/*         ret.error = SCR_ERR_INVALID_PARAM; */
/*     } */

/*     return ret; */
/* } */

/* static struct scrret scr_hsm_handler(unsigned long fid) */
/* { */
/*     struct scrret ret; */

/*     switch (fid) { */
/*         case 0: */
/*         /1* case SCR_CORE_START_FID: *1/ */
/*             ret = scr_hsm_start_handler(); */
/*             break; */
/*         case 1: */
/*         /1* case SCR_CORE_STATUS_FID: *1/ */
/*             ret = scr_hsm_status_handler(); */
/*             break; */
/*         default: */
/*             ret.error = SCR_ERR_NOT_SUPPORTED; */
/*     } */

/*     return ret; */
/* } */


void scr_init()
{
    /* TODO: kick the SCR core */
}
