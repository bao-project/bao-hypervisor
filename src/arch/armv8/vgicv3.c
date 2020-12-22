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

#include <arch/vgic.h>

#include <bit.h>
#include <spinlock.h>
#include <cpu.h>
#include <interrupts.h>
#include <vm.h>

#define GICR_IS_REG(REG, offset)            \
    (((offset) >= offsetof(gicr_t, REG)) && \
     (offset) < (offsetof(gicr_t, REG) + sizeof(gicr[0].REG)))
#define GICR_REG_OFF(REG) (offsetof(gicr_t, REG) & 0x1ffff)
#define GICR_REG_MASK(ADDR) ((ADDR)&0x1ffff)

static inline bool vgic_broadcast(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    return (interrupt->route & GICD_IROUTER_IRM_BIT);
}

bool vgic_int_vcpu_is_target(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool local = priv && (interrupt->phys.redist == vcpu->phys_id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ (MRS(MPIDR_EL1) & MPIDR_AFF_MSK));
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return local || routed_here || any;
}

bool vgic_int_has_other_target(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    bool priv = gic_is_priv(interrupt->id);
    bool routed_here =
        !priv && !(interrupt->phys.route ^ (MRS(MPIDR_EL1) & MPIDR_AFF_MSK));
    bool route_valid = interrupt->phys.route != GICD_IROUTER_INV;
    bool any = !priv && vgic_broadcast(vcpu, interrupt);
    return any || (!routed_here && route_valid);
}

uint64_t vgic_int_ptarget_mask(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if (vgic_broadcast(vcpu, interrupt)) {
        return cpu.vcpu->vm->cpus & ~(1U << cpu.vcpu->phys_id);
    } else {
        return (1ull << interrupt->phys.route);
    }
}

bool vgic_int_set_route(vcpu_t *vcpu, vgic_int_t *interrupt, uint64_t route)
{
    uint64_t phys_route;
    uint64_t prev_route = interrupt->route;

    if (gic_is_priv(interrupt->id)) return false;

    if (route & GICD_IROUTER_IRM_BIT) {
        phys_route = cpu_id_to_mpidr(vcpu->phys_id);
    } else {
        vcpu_t *tvcpu =
            vm_get_vcpu_by_mpidr(vcpu->vm, route & MPIDR_AFF_MSK);
        if (tvcpu != NULL) {
            phys_route = cpu_id_to_mpidr(tvcpu->phys_id) & MPIDR_AFF_MSK;
        } else {
            phys_route = GICD_IROUTER_INV;
        }
    }
    interrupt->phys.route = phys_route;

    interrupt->route = route & GICD_IROUTER_RES0_MSK;
    return prev_route != interrupt->route;
}

uint64_t vgic_int_get_route(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    if (gic_is_priv(interrupt->id)) return 0;
    return interrupt->route;
}

void vgic_int_set_route_hw(vcpu_t *vcpu, vgic_int_t *interrupt)
{
    gicd_set_route(interrupt->id, interrupt->phys.route);
}

void vgicr_emul_ctrl_access(emul_access_t *acc,
                            struct vgic_reg_handler_info *handlers,
                            bool gicr_access, uint64_t vgicr_id)
{
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, 0);
    }
}

void vgicr_emul_typer_access(emul_access_t *acc,
                             struct vgic_reg_handler_info *handlers,
                             bool gicr_access, uint64_t vgicr_id)
{
    if (!acc->write) {
        vcpu_t *vcpu = vm_get_vcpu(cpu.vcpu->vm, vgicr_id);
        vcpu_writereg(cpu.vcpu, acc->reg, vcpu->arch.vgic_priv.vgicr.TYPER);
    }
}

void vgicr_emul_pidr_access(emul_access_t *acc,
                            struct vgic_reg_handler_info *handlers,
                            bool gicr_access, uint64_t vgicr_id)
{
    if (!acc->write) {
        uint64_t pgicr_id = vm_translate_to_pcpuid(cpu.vcpu->vm, vgicr_id);
        vcpu_writereg(cpu.vcpu, acc->reg,
                      gicr[pgicr_id].ID[((acc->addr & 0xff) - 0xd0) / 4]);
    }
}

extern struct vgic_reg_handler_info isenabler_info;
extern struct vgic_reg_handler_info ispendr_info;
extern struct vgic_reg_handler_info isactiver_info;
extern struct vgic_reg_handler_info icenabler_info;
extern struct vgic_reg_handler_info icpendr_info;
extern struct vgic_reg_handler_info iactiver_info;
extern struct vgic_reg_handler_info icfgr_info;
extern struct vgic_reg_handler_info ipriorityr_info;
extern struct vgic_reg_handler_info razwi_info;

struct vgic_reg_handler_info irouter_info = {
    vgic_emul_generic_access,
    0b1000,
    VGIC_IROUTER_ID,
    offsetof(gicd_t, IROUTER),
    64,
    vgic_int_get_route,
    vgic_int_set_route,
    vgic_int_set_route_hw,
};

struct vgic_reg_handler_info vgicr_ctrl_info = {
    vgicr_emul_ctrl_access,
    0b0100,
};
struct vgic_reg_handler_info vgicr_typer_info = {
    vgicr_emul_typer_access,
    0b1000,
};
struct vgic_reg_handler_info vgicr_pidr_info = {
    vgicr_emul_pidr_access,
    0b0100,
};

static inline uint32_t vgicr_get_id(emul_access_t *acc)
{
    return (acc->addr - cpu.vcpu->vm->arch.vgicr_addr) / sizeof(gicr_t);
}

bool vgicr_emul_handler(emul_access_t *acc)
{
    struct vgic_reg_handler_info *handler_info = NULL;
    switch (GICR_REG_MASK(acc->addr)) {
        case GICR_REG_OFF(CTLR):
            handler_info = &vgicr_ctrl_info;
            break;
        case GICR_REG_OFF(TYPER):
            handler_info = &vgicr_typer_info;
            break;
        case GICR_REG_OFF(ISENABLER0):
            handler_info = &isenabler_info;
            break;
        case GICR_REG_OFF(ISPENDR0):
            handler_info = &ispendr_info;
            break;
        case GICR_REG_OFF(ISACTIVER0):
            handler_info = &iactiver_info;
            break;
        case GICR_REG_OFF(ICENABLER0):
            handler_info = &icenabler_info;
            break;
        case GICR_REG_OFF(ICPENDR0):
            handler_info = &icpendr_info;
            break;
        case GICR_REG_OFF(ICACTIVER0):
            handler_info = &icfgr_info;
            break;
        case GICR_REG_OFF(ICFGR0):
        case GICR_REG_OFF(ICFGR1):
            handler_info = &icfgr_info;
            break;
        default: {
            uint64_t base_offset = acc->addr - cpu.vcpu->vm->arch.vgicr_addr;
            uint64_t acc_offset = GICR_REG_MASK(base_offset);
            if (GICR_IS_REG(IPRIORITYR, acc_offset)) {
                handler_info = &ipriorityr_info;
            } else if (GICR_IS_REG(ID, acc_offset)) {
                handler_info = &vgicr_pidr_info;
            } else {
                handler_info = &razwi_info;
            }
        }
    }

    if (vgic_check_reg_alignment(acc, handler_info)) {
        uint64_t vgicr_id = vgicr_get_id(acc);
        vcpu_t *vcpu = vgicr_id == cpu.vcpu->id
                           ? cpu.vcpu
                           : vm_get_vcpu(cpu.vcpu->vm, vgicr_id);
        spin_lock(&vcpu->arch.vgic_priv.vgicr.lock);
        handler_info->reg_access(acc, handler_info, true, vgicr_id);
        spin_unlock(&vcpu->arch.vgic_priv.vgicr.lock);
        return true;
    } else {
        return false;
    }
}

bool vgic_icc_sgir_handler(emul_access_t *acc)
{
    if (acc->write) {
        uint64_t sgir = vcpu_readreg(cpu.vcpu, acc->reg);
        uint64_t int_id = ICC_SGIR_SGIINTID(sgir);
        uint64_t trgtlist;
        if (sgir & ICC_SGIR_IRM_BIT) {
            trgtlist = cpu.vcpu->vm->cpus & ~(1U << cpu.vcpu->phys_id);
        } else {
            /**
             * TODO: we are assuming the vm has a single cluster. Change this
             * when adding virtual cluster support.
             */
            trgtlist = vm_translate_to_pcpu_mask(
                cpu.vcpu->vm, ICC_SGIR_TRGLSTFLT(sgir), cpu.vcpu->vm->cpu_num);
        }
        vgic_send_sgi_msg(cpu.vcpu, trgtlist, int_id);
    }

    return true;
}

bool vgic_icc_sre_handler(emul_access_t *acc)
{
    if (!acc->write) {
        vcpu_writereg(cpu.vcpu, acc->reg, 0x1);
    }
    return true;
}

void vgic_init(vm_t *vm, const struct gic_dscrp *gic_dscrp)
{
    vm->arch.vgicr_addr = gic_dscrp->gicr_addr;
    vm->arch.vgicd.CTLR = 0;
    uint64_t vtyper_itln = vgic_get_itln(gic_dscrp);
    vm->arch.vgicd.int_num = 32 * (vtyper_itln + 1);
    vm->arch.vgicd.TYPER =
        ((vtyper_itln << GICD_TYPER_ITLN_OFF) & GICD_TYPER_ITLN_MSK) |
        (((vm->cpu_num - 1) << GICD_TYPER_CPUNUM_OFF) & GICD_TYPER_CPUNUM_MSK) |
        (((10 - 1) << GICD_TYPER_IDBITS_OFF) & GICD_TYPER_IDBITS_MSK);
    vm->arch.vgicd.IIDR = gicd.IIDR;

    size_t vgic_int_size = vm->arch.vgicd.int_num * sizeof(vgic_int_t);
    vm->arch.vgicd.interrupts =
        mem_alloc_page(NUM_PAGES(vgic_int_size), SEC_HYP_VM, false);
    if (vm->arch.vgicd.interrupts == NULL) {
        ERROR("failed to alloc vgic");
    }

    for (int i = 0; i < vm->arch.vgicd.int_num; i++) {
        vm->arch.vgicd.interrupts[i].owner = NULL;
        vm->arch.vgicd.interrupts[i].lock = SPINLOCK_INITVAL;
        vm->arch.vgicd.interrupts[i].id = i + GIC_CPU_PRIV;
        vm->arch.vgicd.interrupts[i].state = INV;
        vm->arch.vgicd.interrupts[i].prio = GIC_LOWEST_PRIO;
        vm->arch.vgicd.interrupts[i].cfg = 0;
        vm->arch.vgicd.interrupts[i].route = GICD_IROUTER_INV;
        vm->arch.vgicd.interrupts[i].phys.route = GICD_IROUTER_INV;
        vm->arch.vgicd.interrupts[i].hw = false;
        vm->arch.vgicd.interrupts[i].in_lr = false;
        vm->arch.vgicd.interrupts[i].enabled = false;
    }

    emul_mem_t gicd_emu = {.va_base = gic_dscrp->gicd_addr,
                           .pa_base = (uint64_t)&gicd,
                           .size = ALIGN(sizeof(gicd_t), PAGE_SIZE),
                           .handler = vgicd_emul_handler};
    vm_emul_add_mem(vm, &gicd_emu);

    list_foreach(vm->vcpu_list, vcpu_t, vcpu)
    {
        uint64_t phy_cpuid = vcpu->phys_id;
        emul_mem_t gicr_emu = {
            .va_base = gic_dscrp->gicr_addr + sizeof(gicr_t) * vcpu->id,
            .pa_base = (uint64_t) & (gicr[phy_cpuid]),
            .size = ALIGN(sizeof(gicr_t), PAGE_SIZE),
            .handler = vgicr_emul_handler};
        vm_emul_add_mem(vm, &gicr_emu);

        vcpu->arch.vgic_priv.vgicr.CTLR = 0;

        uint64_t typer = vcpu->id << GICR_TYPER_PRCNUM_OFF;
        typer |= (vcpu->arch.vmpidr & MPIDR_AFF_MSK) << GICR_TYPER_AFFVAL_OFF;
        typer |= !!(vcpu->id == vcpu->vm->cpu_num - 1) << GICR_TYPER_LAST_OFF;
        vcpu->arch.vgic_priv.vgicr.TYPER = typer;

        vcpu->arch.vgic_priv.vgicr.IIDR = gicr[cpu.id].IIDR;
    }

    emul_reg_t icc_sgir_emu = {.addr = SYSREG_ENC_ADDR(3, 0, 12, 11, 5),
                               .handler = vgic_icc_sgir_handler};
    vm_emul_add_reg(vm, &icc_sgir_emu);

    emul_reg_t icc_sre_emu = {.addr = SYSREG_ENC_ADDR(3, 0, 12, 12, 5),
                              .handler = vgic_icc_sre_handler};
    vm_emul_add_reg(vm, &icc_sre_emu);
}

void vgic_cpu_init(vcpu_t *vcpu)
{
    for (int i = 0; i < GIC_CPU_PRIV; i++) {
        vcpu->arch.vgic_priv.interrupts[i].owner = NULL;
        vcpu->arch.vgic_priv.interrupts[i].lock = SPINLOCK_INITVAL;
        vcpu->arch.vgic_priv.interrupts[i].id = i;
        vcpu->arch.vgic_priv.interrupts[i].state = INV;
        vcpu->arch.vgic_priv.interrupts[i].prio = GIC_LOWEST_PRIO;
        vcpu->arch.vgic_priv.interrupts[i].cfg = 0;
        vcpu->arch.vgic_priv.interrupts[i].route = GICD_IROUTER_INV;
        vcpu->arch.vgic_priv.interrupts[i].phys.redist = vcpu->phys_id;                              
        vcpu->arch.vgic_priv.interrupts[i].hw = false;
        vcpu->arch.vgic_priv.interrupts[i].in_lr = false;
        vcpu->arch.vgic_priv.interrupts[i].enabled = false;
    }

    for (int i = 0; i < GIC_MAX_SGIS; i++) {
        vcpu->arch.vgic_priv.interrupts[i].cfg = 0b10;
    }
}
