/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/vir.h>
#include <arch/ir.h>
#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>
#include <arch/vm.h>
#include <platform.h>

enum VIR_EVENTS { VIR_UPDATE_ENABLE, VIR_ROUTE, VIR_INJECT, VIR_SET_REG };
extern volatile const size_t VIR_IPI_ID;

#define IR_IS_REG(REG, offset)                    \
    (((offset) >= offsetof(struct ir_int_hw, REG)) && \
        (offset) < (offsetof(struct ir_int_hw, REG) + sizeof(ir_int->REG)))

#define IR_REG_GROUP(REG) ((offsetof(struct ir_int_hw, REG) & 0xffff) >> 8)
#define IR_REG_MASK(ADDR) ((ADDR) & (0xffffUL))

/* #define IRD_REG_IND(REG)   (offsetof(struct ird_hw, REG) & 0x7f) */

#define VIR_MSG_DATA(VM_ID, VIRRID, INT_ID, REG, VAL)                   \
    (((uint64_t)(VM_ID) << 48) | (((uint64_t)(VIRRID) & 0xffff) << 32) | \
        (((INT_ID) & 0x7fff) << 16) | (((REG) & 0xff) << 8) | ((VAL) & 0xff))
#define VIR_MSG_VM(DATA)      ((DATA) >> 48)
#define VIR_MSG_VIRRID(DATA) (((DATA) >> 32) & 0xffff)
#define VIR_MSG_INTID(DATA)   (((DATA) >> 16) & 0x7fff)
#define VIR_MSG_REG(DATA)     (((DATA) >> 8) & 0xff)
#define VIR_MSG_VAL(DATA)     ((DATA) & 0xff)

void vir_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vir_ipi_handler, VIR_IPI_ID)

inline struct vir_src* vir_get_int(struct vcpu* vcpu, irqid_t int_id, vcpuid_t vcpu_id)
{
    /* if (int_id >= vcpu->vm->arch.ir_int.int_num) { */
    /*     return NULL; */
    /* } */
    (void)vcpu_id;

    return &vcpu->vm->arch.vir_src[int_id];
}

bool vir_get_ownership(struct vcpu* vcpu, struct vir_src* interrupt)
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

static bool vir_owns(struct vcpu* vcpu, struct vir_src* interrupt)
{
    return interrupt->owner == vcpu;
}

void vir_yield_ownership(struct vcpu* vcpu, struct vir_src* interrupt)
{
    if (!vir_owns(vcpu, interrupt))
        return;

    interrupt->owner = NULL;
}

void vir_send_sgi_msg(struct vcpu* vcpu, cpumap_t pcpu_mask, irqid_t int_id)
{
    UNUSED_ARG(vcpu);

    struct cpu_msg msg = {
        (uint32_t)VIR_IPI_ID,
        VIR_INJECT,
        VIR_MSG_DATA(cpu()->vcpu->vm->id, 0, int_id, 0, cpu()->vcpu->id),
    };

    for (size_t i = 0; i < platform.cpu_num; i++) {
        if (pcpu_mask & (1ULL << i)) {
            cpu_send_msg(i, &msg);
        }
    }
}

static void ir_int_emul_accen_access(struct emul_access* acc, cpuid_t vcpuid,
        volatile struct IR_ACCESSEN* accen)
{
    (void)vcpuid;
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    (void)acc_addr;
    uint32_t acc_int_offset = 0;// TODO acc_addr - field_offset;

    uint32_t idx = acc_int_offset / sizeof(struct IR_ACCESSEN);
    (void)idx;

    /* TODO figure which masters this vm can control */
    unsigned long field_offset = 0;

    switch(field_offset){
        case offsetof(struct IR_ACCESSEN, WRA):
        /* TODO */
        case offsetof(struct IR_ACCESSEN, WRB):
        /* TODO */
        case offsetof(struct IR_ACCESSEN, RDA):
        /* TODO */
        case offsetof(struct IR_ACCESSEN, RDB):
        /* TODO */
        case offsetof(struct IR_ACCESSEN, PRS):
        /* TODO */
        default:
            ERROR("Trying to access unauthorized ACCESSEN register 0x%x in 0x%x",
                    field_offset, accen);
    }
}

static void ir_int_emul_accensrb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    /* TODO: does this work? */
    uint32_t offset = offsetof(struct ir_int_hw, ACCENSRB);

    /* TODO is it okay to modify this? */
    acc->addr -= offset;

    /* TODO get idx */
    unsigned long idx = 0;
    ir_int_emul_accen_access(acc, vcpuid, &ir_int->ACCENSRB[idx]);
}

static void vir_emul_icu_access(struct emul_access* acc, cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, ICU);
    uint32_t icu_offset = acc_addr - offset;
    uint32_t idx = icu_offset/sizeof(ir_int->ICU);

    (void)vcpuid;

    /* TODO figure out if VM can access ICU */
    bool can_acces_icu = true;

    if(!can_acces_icu){
        ERROR("Trying to access unauthorized ICU %u", idx);
    }

    uint32_t field_offset = icu_offset - idx * sizeof(ir_int->ICU);

    switch(field_offset){
        case offsetof(struct ir_int_icu, LASR):
            /* TODO */
        case offsetof(struct ir_int_icu, ECR):
            /* TODO */
        case offsetof(struct ir_int_icu, ECTRL):
            /* TODO */
        case offsetof(struct ir_int_icu, EGEN):
            /* TODO */
        default:
            ERROR("Trying to access unauthorized ICU register 0x%x", offset);
    }
}

static void vir_emul_tos_access(struct emul_access* acc, cpuid_t vcpuid)
{
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, TOS);
    uint32_t tos_offset = acc_addr - offset;
    uint32_t idx = tos_offset/sizeof(ir_int->TOS);

    /* TODO figure out if VM can access TOS */
    bool can_acces_tos = true;

    if(!can_acces_tos){
        ERROR("Trying to access unauthorized TOS %u", idx);
    }

    uint32_t field_offset = tos_offset - idx * sizeof(ir_int->TOS);

    /* TODO cleanup */
    uint32_t accenscfg_offset = offsetof(struct ir_int_tos, ACCENSCFG);
    uint32_t accensctrl_offset = offsetof(struct ir_int_tos, ACCENSCTRL);
    uint32_t accen_sz =  sizeof(struct IR_ACCESSEN);
    if(field_offset >= accenscfg_offset && field_offset < accenscfg_offset + accen_sz){
        /* TODO ok to do this? */
        acc->addr -= accenscfg_offset;
        ir_int_emul_accen_access(acc, vcpuid, &ir_int->TOS[idx].ACCENSCFG);
    } else if(field_offset >= accensctrl_offset && field_offset < accensctrl_offset + accen_sz){
        /* TODO ok to do this? */
        acc->addr -= accensctrl_offset;
        ir_int_emul_accen_access(acc, vcpuid, &ir_int->TOS[idx].ACCENSCTRL);
    } else {
        ERROR("Trying to access unknwon TOS register 0x%x", offset);
    }
}

static void vir_emul_gpsrg_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;

    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    /* start of gpsrg */
    uint32_t offset = offsetof(struct ir_int_hw, GPSRG);
    /* offset within the gpsrg array */
    uint32_t gpsrg_offset = acc_addr - offset;
    /* gpsrg array entry */
    uint32_t idx = gpsrg_offset/sizeof(ir_int->GPSRG);

    /* TODO figure out if VM can access gpsrg */
    bool can_acces_gpsrg = true;

    if(!can_acces_gpsrg){
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* field_offset offset within correct gpsrg */
    uint32_t field_offset = gpsrg_offset - idx * sizeof(ir_int->GPSRG);


    /* TODO this is essentially duplicate code */
    /* start of swc */
    offset = offsetof(struct ir_int_gpsrg, SWC);
    /* offset within the swc array */
    uint32_t swc_offset = field_offset - offset;
    /* swc array entry */
    idx = swc_offset/sizeof(struct ir_int_gpsrg_swc);

    /* TODO figure out if VM can access SWC */
    bool can_acces_swc = true;

    if(!can_acces_swc){
        ERROR("Trying to access unauthorized gpsrg %u", idx);
    }

    /* offset within ir_int_gpsrg_swc */
    field_offset = swc_offset - idx * sizeof(struct ir_int_gpsrg_swc);


    /* TODO cleanup */
    switch(offset){
        case offsetof(struct ir_int_gpsrg_swc, ACCEN):
            /* TODO */
        case offsetof(struct ir_int_gpsrg_swc, CR):
                /* TODO */
        default:
                ERROR("Trying to access unknwon gpsrg register 0x%x", offset);
    }
}

static void vir_emul_srb_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;
    uint32_t acc_addr = IR_REG_MASK(acc->addr);
    uint32_t offset = offsetof(struct ir_int_hw, SRB);
    uint32_t srb_offset = acc_addr - offset;
    uint32_t idx = srb_offset/sizeof(ir_int->SRB);

    /* TODO figure out if VM can access TOS */
    bool can_acces_srb = true;

    if(!can_acces_srb){
        ERROR("Trying to access unauthorized SRB %u", idx);
    }

    /* TODO get correct vcpu */
    uint32_t val = vcpu_readreg(cpu()->vcpu, acc->reg);
    val &= 0x7f; /* TODO */
    /* TODO figure out which CPU ISP this VM can target and if all is well perform the access */

    /* TODO should probably be abstracted in ir.c no? */
    ir_int->SRB[idx] = val;
}

static void vir_emul_misc_access(struct emul_access* acc, cpuid_t vcpuid)
{
    (void)vcpuid;
    uint32_t acc_addr = IR_REG_MASK(acc->addr);

    if(acc_addr == offsetof(struct ir_int_hw, ID)){
        /* TODO */
        vcpu_writereg(cpu()->vcpu, acc->reg, ir_int->ID);
    } else {
        ERROR("unsuported register emulation 0x%x", acc_addr);
    }
}

static bool vir_int_set_prio(struct vcpu* vcpu, struct vir_src* interrupt, unsigned long prio)
{
    UNUSED_ARG(vcpu);
    uint8_t prev_prio = interrupt->prio;
    return prev_prio != prio;
}

static unsigned long vir_int_get_prio(struct vcpu* vcpu, struct vir_src* interrupt)
{
    UNUSED_ARG(vcpu);
    return (unsigned long)interrupt->prio;
}


struct vir_reg_handler_info ir_int_misc_info = {
    vir_emul_misc_access,
    0x2,
};

struct vir_reg_handler_info ir_int_accensrb_info = {
    ir_int_emul_accensrb_access,
    0x2,
};

struct vir_reg_handler_info ir_int_tos_info = {
    vir_emul_tos_access,
    0x2,
};

struct vir_reg_handler_info ir_int_gpsrg_info = {
    vir_emul_gpsrg_access,
    0x2,
};

struct vir_reg_handler_info ir_int_srb_info = {
    vir_emul_srb_access,
    0x2,
};

struct vir_reg_handler_info ir_int_icu_info = {
    vir_emul_icu_access,
    0x2,
};

bool vir_check_reg_alignment(struct emul_access* acc, struct vir_reg_handler_info* handlers)
{
    if (!(handlers->alignment & acc->width) || ((acc->addr & (acc->width - 1)) != 0)) {
        return false;
    }

    return true;
}

static void vir_emul_src_access(struct emul_access* acc, struct vcpu *vcpu, struct vir_src* interrupt)
{
    /* TODO consider 16bit access */
    if(acc->write) {
        uint32_t val = vcpu_readreg(vcpu, acc->reg);

        uint32_t srpn = IR_SRC_GET_SRPN(val);
        (void) srpn;

        uint32_t tos = IR_SRC_GET_TOS(val);
        (void)tos;
        /* TODO check which ISP VM can access */

        /* bool sre = IR_SRC_GET_SRE(val) != 0; */
        /* if(sre){ */
        /*     vir_int_update_enable(vcpu, interrupt, sre); */
        /* } */

        /* bool clrr = IR_SRC_GET_CLRR(val) != 0; */
        /* bool setr = IR_SRC_GET_SETR(val) != 0; */

        /* if(!(clrr && setr)){ */
        /*     if(setr){ */
        /*         vir_int_update_pend(vcpu, interrupt, true); */
        /*     } else if (clrr) { */
        /*         vir_int_update_pend(vcpu, interrupt, false); */
        /*     } */
        /* } */

        /* bool iovclr = IR_SRC_GET_IOVCLR(val) != 0; */
        /* TODO what should hyp do? */
        unsigned long prio = 0;
        vir_int_set_prio(vcpu, interrupt, prio);


    } else {
        uint32_t src_mask = IR_SRC_IOVCLR_MASK | IR_SRC_IOV_MASK |
            IR_SRC_SETR_MASK | IR_SRC_CLRR_MASK | IR_SRC_SRR_MASK |
            IR_SRC_SRE_MASK | IR_SRC_TOS_MASK | IR_SRC_CS_MASK | IR_SRC_SRPN_MASK;
        /* TODO we are SPH we can read directly, diferent with ctx switch */
        uint32_t val = ir_src->SRC[interrupt->id] & src_mask;
        unsigned long prio = vir_int_get_prio(vcpu, interrupt);
        (void)prio;

        vcpu_writereg(vcpu, acc->reg, val);
    }
}

bool ir_src_emul_handler(struct emul_access* acc)
{
    uint32_t addr = acc->addr;
    uint32_t src_offset = addr - cpu()->vcpu->vm->arch.vir_src_addr;

    uint32_t intid = src_offset / sizeof(ir_src->SRC[0]);

    struct vir_src* interrupt = vir_get_int(cpu()->vcpu, intid, cpu()->vcpu->id);
    /* TODO check if VM owns intid */
    if(!interrupt)
        ERROR("Access to unsigned interrupt %u", intid);

    spin_lock(&cpu()->vcpu->vm->arch.vir_src_lock);
    vir_emul_src_access(acc, cpu()->vcpu, interrupt);
    spin_unlock(&cpu()->vcpu->vm->arch.vir_src_lock);
    return true;
}

bool ir_int_emul_handler(struct emul_access* acc)
{
    struct vir_reg_handler_info* handler_info = NULL;
    size_t acc_off = IR_REG_MASK(acc->addr);
    if (IR_IS_REG(SRB, acc_off)) {
        handler_info = &ir_int_srb_info;
    } else if (IR_IS_REG(ICU, acc_off)) {
        handler_info = &ir_int_icu_info;
    } else if (IR_IS_REG(TOS, acc_off)) {
        handler_info = &ir_int_tos_info;
    } else if (IR_IS_REG(GPSRG, acc_off)) {
        handler_info = &ir_int_gpsrg_info;
    } else if (IR_IS_REG(ACCENSRB, acc_off)) {
        handler_info = &ir_int_accensrb_info;
    } else if((IR_REG_MASK(acc->addr) >> 7) == IR_REG_GROUP(OCS)){
        handler_info = &ir_int_misc_info;
    } else {
        ERROR("Unknown IR register at 0x%x", acc->addr);
    }

    if (!vir_check_reg_alignment(acc, handler_info)) {
        return false;
    }

    spin_lock(&cpu()->vcpu->vm->arch.vir_int_lock);
    handler_info->reg_access(acc, cpu()->vcpu->id);
    spin_unlock(&cpu()->vcpu->vm->arch.vir_int_lock);
    return true;
}

void vir_inject(struct vcpu* vcpu, irqid_t id)
{
    struct vir_src* interrupt = vir_get_int(vcpu, id, vcpu->id);
    spin_lock(&interrupt->lock);
    interrupt->owner = vcpu;

    /* TODO: any other considerations? */
    ir_set_pend(id);

    spin_unlock(&interrupt->lock);
}

void vir_ipi_handler(uint32_t event, uint64_t data)
{
    uint16_t vm_id = (uint16_t)VIR_MSG_VM(data);
    uint16_t virr_id = (uint16_t)VIR_MSG_VIRRID(data);
    irqid_t int_id = VIR_MSG_INTID(data);
    uint64_t val = VIR_MSG_VAL(data);

    /* TODO do we need this? */
    (void) event;
    (void)vm_id;
    (void)virr_id;
    (void)int_id;
    (void)val;
}

void vir_init(struct vm* vm, const struct vir_dscrp* vir_dscrp)
{
    /* Although we map the IR unto the VM, we restric VM access by using ICU.VMEN and SRC.VM */

    /* TODO IR and SRC could probably be a single mapping */
    mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)vir_dscrp->int_addr,
        (vaddr_t)platform.arch.ir.int_addr, NUM_PAGES(sizeof(struct ir_int_hw)));

    vm->arch.vir_int_emul = (struct emul_mem){ 
        .va_base = vir_dscrp->int_addr,
        .size = ALIGN(sizeof(struct ir_int_hw), PAGE_SIZE),
        .handler = ir_int_emul_handler };
    vm_emul_add_mem(vm, &vm->arch.vir_int_emul);


    /* TODO Magic number */
    uint32_t src_sz = IR_MAX_INTERRUPTS*4; /* TODO platform number of interrupts */
    mem_alloc_map_dev(&vm->as, SEC_VM_ANY, (vaddr_t)vir_dscrp->src_addr,
        (vaddr_t)platform.arch.ir.src_addr, NUM_PAGES(src_sz));

    vm->arch.vir_src_emul = (struct emul_mem){
        .va_base = vir_dscrp->src_addr,
        .size = ALIGN(src_sz, PAGE_SIZE),
        .handler = ir_src_emul_handler
    };

    vm_emul_add_mem(vm, &vm->arch.vir_src_emul);

    /* This should be aware of the number of interrupts */
    size_t vir_interrupt_size = IR_MAX_INTERRUPTS * sizeof(struct vir_src);
    vm->arch.vir_src = mem_alloc_page(NUM_PAGES(vir_interrupt_size), SEC_HYP_VM, false);
    if (vm->arch.vir_src == NULL) {
        ERROR("failed to alloc vgic");
    }

    for (irqid_t i = 0; i < IR_MAX_INTERRUPTS; i++) {
        vm->arch.vir_src[i].owner = NULL;
        vm->arch.vir_src[i].lock = SPINLOCK_INITVAL;
        vm->arch.vir_src[i].id = i;
        vm->arch.vir_src[i].prio = IR_MIN_PRIO;
        vm->arch.vir_src[i].target = IR_TARGET_NONE;
        vm->arch.vir_src[i].enabled = false;
    }
}

void vir_vcpu_init(struct vcpu *vcpu)
{
   ir_assign_icu_to_vm(cpu()->id, vcpu->vm);
}
