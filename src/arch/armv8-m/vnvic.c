/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/vnvic.h>
#include <arch/nvic.h>
#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>
#include <arch/vm.h>
#include <platform.h>

enum VNVIC_EVENTS { VNVIC_UPDATE_ENABLE, VNVIC_ROUTE, VNVIC_INJECT, VNVIC_SET_REG };
extern volatile const size_t VNVIC_IPI_ID;
extern volatile bitmap_granule_t* valid;

#define NVIC_IS_REG(REG, offset)                        \
    (((offset) >= offsetof(struct nvic_int_hw, REG)) && \
        (offset) < (offsetof(struct nvic_int_hw, REG) + sizeof(nvic_int->REG)))

#define NVIC_REG_GROUP(REG) ((offsetof(struct nvic_int_hw, REG) & 0xffff) >> 8)
#define NVIC_REG_MASK(ADDR) ((ADDR) & (0xffffUL))

/* #define IRD_REG_IND(REG)   (offsetof(struct ird_hw, REG) & 0x7f) */

#define VNVIC_MSG_DATA(VM_ID, VIRRID, INT_ID, REG, VAL)                  \
    (((uint64_t)(VM_ID) << 48) | (((uint64_t)(VIRRID) & 0xffff) << 32) | \
        (((INT_ID) & 0x7fff) << 16) | (((REG) & 0xff) << 8) | ((VAL) & 0xff))
#define VNVIC_MSG_VM(DATA)     ((DATA) >> 48)
#define VNVIC_MSG_VIRRID(DATA) (((DATA) >> 32) & 0xffff)
#define VNVIC_MSG_INTID(DATA)  (((DATA) >> 16) & 0x7fff)
#define VNVIC_MSG_REG(DATA)    (((DATA) >> 8) & 0xff)
#define VNVIC_MSG_VAL(DATA)    ((DATA) & 0xff)

void vnvic_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vnvic_ipi_handler, VNVIC_IPI_ID)

struct vnvic_src* vnvic_get_int(struct vcpu* vcpu, irqid_t int_id, vcpuid_t vcpu_id)
{
    /* if (int_id >= vcpu->vm->arch.nvic_int.int_num) { */
    /*     return NULL; */
    /* } */
    (void)vcpu_id;

    return &vcpu->vm->arch.vnvic_src[int_id];
}

bool vnvic_get_ownership(struct vcpu* vcpu, struct vnvic_src* interrupt)
{
    bool ret = false;

    if (interrupt->owner == vcpu) {
        ret = true;
    } else if (interrupt->owner == NULL) {
        interrupt->owner = vcpu;
        ret = true;
    }

    return ret;
}

static bool vnvic_owns(struct vcpu* vcpu, struct vnvic_src* interrupt)
{
    return interrupt->owner == vcpu;
}

void vnvic_yield_ownership(struct vcpu* vcpu, struct vnvic_src* interrupt)
{
    if (!vnvic_owns(vcpu, interrupt)) {
        return;
    }

    interrupt->owner = NULL;
}

void vnvic_send_sgi_msg(struct vcpu* vcpu, cpumap_t pcpu_mask, irqid_t int_id)
{
    UNUSED_ARG(vcpu);

    struct cpu_msg msg = {
        (uint32_t)VNVIC_IPI_ID,
        VNVIC_INJECT,
        VNVIC_MSG_DATA(cpu()->vcpu->vm->id, 0, int_id, 0, cpu()->vcpu->id),
    };

    for (size_t i = 0; i < platform.cpu_num; i++) {
        if (pcpu_mask & (1ULL << i)) {
            cpu_send_msg(i, &msg);
        }
    }
}

static void nvic_int_emul_accen_access(struct emul_access* acc, cpuid_t vcpuid,
    volatile struct NVIC_ACCESSEN* accen)
{
    (void)vcpuid;
    (void)acc;
    (void)accen;
}

static void nvic_int_emul_accensrb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static void vnvic_emul_icu_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static void vnvic_emul_tos_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static void vnvic_emul_gpsrg_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static void vnvic_emul_srb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static void vnvic_emul_misc_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)acc;
    (void)vcpuid;
}

static bool vnvic_int_set_prio(struct vcpu* vcpu, struct vnvic_src* interrupt, unsigned long prio)
{
    UNUSED_ARG(vcpu);
    uint8_t prev_prio = interrupt->prio;
    return prev_prio != prio;
}

static unsigned long vnvic_int_get_prio(struct vcpu* vcpu, struct vnvic_src* interrupt)
{
    UNUSED_ARG(vcpu);
    return (unsigned long)interrupt->prio;
}

struct vnvic_reg_handler_info nvic_int_misc_info = {
    vnvic_emul_misc_access,
    0x2,
};

struct vnvic_reg_handler_info nvic_int_accensrb_info = {
    nvic_int_emul_accensrb_access,
    0x2,
};

struct vnvic_reg_handler_info nvic_int_tos_info = {
    vnvic_emul_tos_access,
    0x2,
};

struct vnvic_reg_handler_info nvic_int_gpsrg_info = {
    vnvic_emul_gpsrg_access,
    0x2,
};

struct vnvic_reg_handler_info nvic_int_srb_info = {
    vnvic_emul_srb_access,
    0x2,
};

struct vnvic_reg_handler_info nvic_int_icu_info = {
    vnvic_emul_icu_access,
    0x2,
};

bool vnvic_check_reg_alignment(struct emul_access* acc, struct vnvic_reg_handler_info* handlers)
{
    if (!(handlers->alignment & acc->width) || ((acc->addr & (acc->width - 1)) != 0)) {
        return false;
    }

    return true;
}

static void vnvic_emul_src_access(struct emul_access* acc, struct vcpu* vcpu,
    struct vnvic_src* interrupt)
{
    UNUSED_ARG(acc);
    UNUSED_ARG(vcpu);
    UNUSED_ARG(interrupt);
}

bool nvic_src_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    return false;
}

bool nvic_int_emul_handler(struct emul_access* acc)
{
    UNUSED_ARG(acc);
    return false;
}

void vnvic_inject(struct vcpu* vcpu, irqid_t id)
{
    UNUSED_ARG(vcpu);
    UNUSED_ARG(id);
}

void vnvic_ipi_handler(uint32_t event, uint64_t data)
{
    UNUSED_ARG(event);
    UNUSED_ARG(data);
}

void vnvic_init(struct vm* vm, const struct vnvic_dscrp* vnvic_dscrp)
{
    UNUSED_ARG(vm);
    UNUSED_ARG(vnvic_dscrp);
}

void vnvic_vcpu_init(struct vcpu* vcpu)
{
    nvic_assign_icu_to_vm(cpu()->id, vcpu->vm);
}
