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
    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);
    (void)acc_addr;
    uint32_t acc_int_offset = 0; // TODO acc_addr - field_offset;

    uint32_t idx = acc_int_offset / sizeof(struct NVIC_ACCESSEN);
    (void)idx;

    /* TODO figure which masters this vm can control */
    unsigned long field_offset = 0;

    switch (field_offset) {
        case offsetof(struct NVIC_ACCESSEN, WRA):
        /* TODO */
        case offsetof(struct NVIC_ACCESSEN, WRB):
        /* TODO */
        case offsetof(struct NVIC_ACCESSEN, RDA):
        /* TODO */
        case offsetof(struct NVIC_ACCESSEN, RDB):
        /* TODO */
        case offsetof(struct NVIC_ACCESSEN, PRS):
        /* TODO */
        default:
            ERROR("Trying to access unauthorized ACCESSEN register 0x%x in 0x%x", field_offset,
                accen);
    }
}

static void nvic_int_emul_accensrb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    /* TODO: does this work? */
    uint32_t offset = offsetof(struct nvic_int_hw, ACCENSRB);

    /* TODO is it okay to modify this? */
    acc->addr -= offset;

    /* TODO get idx */
    unsigned long idx = 0;
    nvic_int_emul_accen_access(acc, vcpuid, &nvic_int->ACCENSRB[idx]);
}

static void vnvic_emul_icu_access(struct emul_access* acc, cpuid_t vcpuid)
{
    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct nvic_int_hw, ICU);
    uint32_t icu_offset = acc_addr - offset;
    uint32_t idx = icu_offset / sizeof(nvic_int->ICU);

    (void)vcpuid;

    /* TODO figure out if VM can access ICU */
    bool can_acces_icu = true;

    if (!can_acces_icu) {
        ERROR("Trying to access unauthorized ICU %u", idx);
    }

    uint32_t field_offset = icu_offset - idx * sizeof(nvic_int->ICU);

    switch (field_offset) {
        case offsetof(struct nvic_int_icu, LASR):
            /* TODO */
        case offsetof(struct nvic_int_icu, ECR):
            /* TODO */
        case offsetof(struct nvic_int_icu, ECTRL):
            /* TODO */
        case offsetof(struct nvic_int_icu, EGEN):
            /* TODO */
        default:
            ERROR("Trying to access unauthorized ICU register 0x%x", offset);
    }
}

static void vnvic_emul_tos_access(struct emul_access* acc, cpuid_t vcpuid)
{
    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct nvic_int_hw, TOS);
    uint32_t tos_offset = acc_addr - offset;
    uint32_t idx = tos_offset / sizeof(nvic_int->TOS);

    /* TODO figure out if VM can access TOS */
    bool can_acces_tos = true;

    if (!can_acces_tos) {
        ERROR("Trying to access unauthorized TOS %u", idx);
    }

    uint32_t field_offset = tos_offset - idx * sizeof(nvic_int->TOS);

    /* TODO cleanup */
    uint32_t accenscfg_offset = offsetof(struct nvic_int_tos, ACCENSCFG);
    uint32_t accensctrl_offset = offsetof(struct nvic_int_tos, ACCENSCTRL);
    uint32_t accen_sz = sizeof(struct NVIC_ACCESSEN);
    if (field_offset >= accenscfg_offset && field_offset < accenscfg_offset + accen_sz) {
        /* TODO ok to do this? */
        acc->addr -= accenscfg_offset;
        nvic_int_emul_accen_access(acc, vcpuid, &nvic_int->TOS[idx].ACCENSCFG);
    } else if (field_offset >= accensctrl_offset && field_offset < accensctrl_offset + accen_sz) {
        /* TODO ok to do this? */
        acc->addr -= accensctrl_offset;
        nvic_int_emul_accen_access(acc, vcpuid, &nvic_int->TOS[idx].ACCENSCTRL);
    } else {
        ERROR("Trying to access unknwon TOS register 0x%x", offset);
    }
}

static void vnvic_emul_gpsrg_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;

    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);
    /* start of gpsrg */
    uint32_t offset = offsetof(struct nvic_int_hw, GPSRG);
    /* offset within the gpsrg array */
    uint32_t gpsrg_offset = acc_addr - offset;
    /* gpsrg array entry */
    uint32_t idx = gpsrg_offset / sizeof(nvic_int->GPSRG);

    /* TODO figure out if VM can access gpsrg */
    bool can_acces_gpsrg = true;

    if (!can_acces_gpsrg) {
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* field_offset offset within correct gpsrg */
    uint32_t field_offset = gpsrg_offset - idx * sizeof(nvic_int->GPSRG);

    /* TODO this is essentially duplicate code */
    /* start of swc */
    offset = offsetof(struct nvic_int_gpsrg, SWC);
    /* offset within the swc array */
    uint32_t swc_offset = field_offset - offset;
    /* swc array entry */
    idx = swc_offset / sizeof(struct nvic_int_gpsrg_swc);

    /* TODO figure out if VM can access SWC */
    bool can_acces_swc = true;

    if (!can_acces_swc) {
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* offset within nvic_int_gpsrg_swc */
    field_offset = swc_offset - idx * sizeof(struct nvic_int_gpsrg_swc);

    /* TODO cleanup */
    switch (offset) {
        case offsetof(struct nvic_int_gpsrg_swc, ACCEN):
            /* TODO */
        case offsetof(struct nvic_int_gpsrg_swc, CR):
            /* TODO */
        default:
            ERROR("Trying to access unknwon gpsrg register 0x%x", offset);
    }
}

static void vnvic_emul_srb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;
    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct nvic_int_hw, SRB);
    uint32_t srb_offset = acc_addr - offset;
    uint32_t idx = srb_offset / sizeof(nvic_int->SRB);

    /* TODO figure out if VM can access TOS */
    bool can_acces_srb = true;

    if (!can_acces_srb) {
        ERROR("Trying to access unauthorized SRB %u", idx);
    }

    /* TODO get correct vcpu */
    uint32_t val = vcpu_readreg(cpu()->vcpu, acc->reg);
    val &= 0x7f; /* TODO */
    /* TODO figure out which CPU ISP this VM can target and if all is well perform the access */

    /* TODO should probably be abstracted in ir.c no? */
    nvic_int->SRB[idx] = val;
}

static void vnvic_emul_misc_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;
    uint32_t acc_addr = NVIC_REG_MASK(acc->addr);

    if (acc_addr == offsetof(struct nvic_int_hw, ID)) {
        /* TODO */
        vcpu_writereg(cpu()->vcpu, acc->reg, nvic_int->ID);
    } else {
        ERROR("unsuported register emulation 0x%x", acc_addr);
    }
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
    /* TODO consider 16bit access */
    if (acc->write) {
        uint32_t val = vcpu_readreg(vcpu, acc->reg);

        uint32_t srpn = NVIC_SRC_GET_SRPN(val);
        (void)srpn;

        uint32_t tos = NVIC_SRC_GET_TOS(val);
        (void)tos;
        /* TODO check which ISP VM can access */

        /* bool sre = NVIC_SRC_GET_SRE(val) != 0; */
        /* if(sre){ */
        /*     vnvic_int_update_enable(vcpu, interrupt, sre); */
        /* } */

        /* bool clrr = NVIC_SRC_GET_CLRR(val) != 0; */
        /* bool setr = NVIC_SRC_GET_SETR(val) != 0; */

        /* if(!(clrr && setr)){ */
        /*     if(setr){ */
        /*         vnvic_int_update_pend(vcpu, interrupt, true); */
        /*     } else if (clrr) { */
        /*         vnvic_int_update_pend(vcpu, interrupt, false); */
        /*     } */
        /* } */

        /* bool iovclr = NVIC_SRC_GET_IOVCLR(val) != 0; */
        /* TODO what should hyp do? */
        unsigned long prio = 0;
        vnvic_int_set_prio(vcpu, interrupt, prio);

    } else {
        uint32_t src_mask = NVIC_SRC_IOVCLR_MASK | NVIC_SRC_IOV_MASK | NVIC_SRC_SETR_MASK |
            NVIC_SRC_CLRR_MASK | NVIC_SRC_SRR_MASK | NVIC_SRC_SRE_MASK | NVIC_SRC_TOS_MASK |
            NVIC_SRC_CS_MASK | NVIC_SRC_SRPN_MASK;
        /* TODO we are SPH we can read directly, diferent with ctx switch */
        uint32_t val = nvic_src->SRC[interrupt->id] & src_mask;
        unsigned long prio = vnvic_int_get_prio(vcpu, interrupt);
        (void)prio;

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

bool nvic_src_emul_handler(struct emul_access* acc)
{
    uint32_t addr = acc->addr;
    uint32_t src_offset = addr - cpu()->vcpu->vm->arch.vnvic_src_addr;

    uint32_t intid = src_offset / sizeof(nvic_src->SRC[0]);

    struct vnvic_src* interrupt = vnvic_get_int(cpu()->vcpu, intid, cpu()->vcpu->id);
    /* TODO check if VM owns intid */
    if (!interrupt) {
        ERROR("Access to unsigned interrupt %u", intid);
    }

    spin_lock(&cpu()->vcpu->vm->arch.vnvic_src_lock);
    vnvic_emul_src_access(acc, cpu()->vcpu, interrupt);
    spin_unlock(&cpu()->vcpu->vm->arch.vnvic_src_lock);
    return true;
}

bool nvic_int_emul_handler(struct emul_access* acc)
{
    struct vnvic_reg_handler_info* handler_info = NULL;
    size_t acc_off = NVIC_REG_MASK(acc->addr);
    if (NVIC_IS_REG(SRB, acc_off)) {
        handler_info = &nvic_int_srb_info;
    } else if (NVIC_IS_REG(ICU, acc_off)) {
        handler_info = &nvic_int_icu_info;
    } else if (NVIC_IS_REG(TOS, acc_off)) {
        handler_info = &nvic_int_tos_info;
    } else if (NVIC_IS_REG(GPSRG, acc_off)) {
        handler_info = &nvic_int_gpsrg_info;
    } else if (NVIC_IS_REG(ACCENSRB, acc_off)) {
        handler_info = &nvic_int_accensrb_info;
    } else if ((NVIC_REG_MASK(acc->addr) >> 7) == NVIC_REG_GROUP(OCS)) {
        handler_info = &nvic_int_misc_info;
    } else {
        // ERROR("Unknown IR register at 0x%x", acc->addr);
    }

    if (!vnvic_check_reg_alignment(acc, handler_info)) {
        return false;
    }

    spin_lock(&cpu()->vcpu->vm->arch.vnvic_int_lock);
    handler_info->reg_access(acc, cpu()->vcpu->id);
    spin_unlock(&cpu()->vcpu->vm->arch.vnvic_int_lock);
    return true;
}

void vnvic_inject(struct vcpu* vcpu, irqid_t id)
{
    struct vnvic_src* interrupt = vnvic_get_int(vcpu, id, vcpu->id);
    spin_lock(&interrupt->lock);
    interrupt->owner = vcpu;

    /* TODO: any other considerations? */
    nvic_set_pend(id);

    spin_unlock(&interrupt->lock);
}

void vnvic_ipi_handler(uint32_t event, uint64_t data)
{
    uint16_t vm_id = (uint16_t)VNVIC_MSG_VM(data);
    uint16_t vnvicr_id = (uint16_t)VNVIC_MSG_VIRRID(data);
    irqid_t int_id = VNVIC_MSG_INTID(data);
    uint64_t val = VNVIC_MSG_VAL(data);

    /* TODO do we need this? */
    (void)event;
    (void)vm_id;
    (void)vnvicr_id;
    (void)int_id;
    (void)val;
}

void vnvic_init(struct vm* vm, const struct vnvic_dscrp* vnvic_dscrp)
{
    /* Although we map the IR unto the VM, we restric VM access by using ICU.VMEN and SRC.VM */

    /* TODO IR and SRC could probably be a single mapping */
    mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)vnvic_dscrp->int_addr,
        (vaddr_t)platform.arch.nvic.int_addr, NUM_PAGES(sizeof(struct nvic_int_hw)));

    vm->arch.vnvic_int_emul = (struct emul_mem){ .va_base = vnvic_dscrp->int_addr,
        .size = ALIGN(sizeof(struct nvic_int_hw), PAGE_SIZE),
        .handler = nvic_int_emul_handler };
    vm_emul_add_mem(vm, &vm->arch.vnvic_int_emul);

    /* TODO Magic number */
    uint32_t src_sz = NVIC_MAX_INTERRUPTS * 4; /* TODO platform number of interrupts */
    mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)vnvic_dscrp->src_addr,
        (vaddr_t)platform.arch.nvic.src_addr, NUM_PAGES(src_sz));

    vm->arch.vnvic_src_emul = (struct emul_mem){ .va_base = vnvic_dscrp->src_addr,
        .size = ALIGN(src_sz, PAGE_SIZE),
        .handler = nvic_src_emul_handler };

    vm_emul_add_mem(vm, &vm->arch.vnvic_src_emul);

    /* This should be aware of the number of interrupts */
    size_t vnvic_interrupt_size = NVIC_MAX_INTERRUPTS * sizeof(struct vnvic_src);
    vm->arch.vnvic_src = mem_alloc_page(NUM_PAGES(vnvic_interrupt_size), SEC_HYP_VM, false);
    if (vm->arch.vnvic_src == NULL) {
        ERROR("failed to alloc vgic");
    }

    for (irqid_t i = 0; i < NVIC_MAX_INTERRUPTS; i++) {
        if (nvic_id_valid(i)) {
            vm->arch.vnvic_src[i].owner = NULL;
            vm->arch.vnvic_src[i].lock = SPINLOCK_INITVAL;
            vm->arch.vnvic_src[i].id = i;
            vm->arch.vnvic_src[i].prio = NVIC_MIN_PRIO;
            vm->arch.vnvic_src[i].target = NVIC_TARGET_NONE;
            vm->arch.vnvic_src[i].enabled = false;
        }
    }
}

void vnvic_vcpu_init(struct vcpu* vcpu)
{
    nvic_assign_icu_to_vm(cpu()->id, vcpu->vm);
}
