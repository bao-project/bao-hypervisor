/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <interrupts.h>
#include <vm.h>
#include <ipir.h>

volatile struct ipir_hw* ipir;
static bool ipir_ready = false;

extern irqid_t interrupts_ipi_id;

static void ipir_handle(irqid_t int_id)
{
    UNUSED_ARG(int_id);

    /* Clear IPI */
    uint8_t src_cpu_idx = ipir->self[IPI_HYP_IRQ_ID].IPInFLG;
    ipir->self[IPI_HYP_IRQ_ID].IPInFCLR = src_cpu_idx;

    cpu_msg_handler();
}

void ipir_send_ipi(cpuid_t cpu_target)
{
    if (ipir_ready) {
        ipir->self[IPI_HYP_IRQ_ID].IPInREQ = (uint8_t)(1U << cpu_target);
    }
}

void ipir_init(void)
{
    if (cpu_is_master()) {
        vaddr_t ipir_ptr = mem_alloc_map_dev(&cpu()->as, SEC_HYP_GLOBAL, INVALID_VA,
            platform.arch.ipir_addr, NUM_PAGES(sizeof(struct ipir_hw)));
        if (ipir_ptr == INVALID_VA) {
            ERROR("Mapping IPIR failed");
        }
        ipir = (struct ipir_hw*)ipir_ptr;

        interrupts_ipi_id = interrupts_reserve(IPI_HYP_IRQ_ID, ipir_handle);
        if (interrupts_ipi_id == INVALID_IRQID) {
            ERROR("Failed to reserve IPIR interrupt");
        }

        ipir_ready = true;
    }

    cpu_sync_and_clear_msgs(&cpu_glb_sync);

    ipir->self[IPI_HYP_IRQ_ID].IPInEN = ((1 << PLAT_CPU_NUM) - 1);
}
