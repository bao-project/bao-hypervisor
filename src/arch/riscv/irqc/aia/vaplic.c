/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <vaplic.h>
#include <vm.h>
#include <cpu.h>
#include <emul.h>
#include <mem.h>
#include <interrupts.h>
#include <fences.h>
#include <arch/csrs.h>
#if (IRQC == AIA)
#include <imsic.h>
#endif

#define UPDATE_ALL_HARTS           (~0U)

#define SET_INTP_REG(reg, intp_id) (reg[intp_id / 32] = bit32_set(reg[intp_id / 32], intp_id % 32))
#define GET_INTP_REG(reg, intp_id) ((bit32_get(reg[intp_id / 32], intp_id % 32) != 0) ? 1U : 0U)
#define CLR_INTP_REG(reg, intp_id) \
    (reg[intp_id / 32] = bit32_clear(reg[intp_id / 32], intp_id % 32))

/**
 * @brief Returns if a given interrupt is valid
 *
 * @param intp_id interrupt ID
 * @return true if the interrupt is valid
 * @return false if the interrupt is NOT valid
 */
static inline bool vaplic_intp_valid(irqid_t intp_id)
{
    return intp_id != 0 && intp_id < APLIC_MAX_INTERRUPTS;
}

static uint32_t vaplic_get_domaincfg(struct vcpu* vcpu);
static uint32_t vaplic_get_target(struct vcpu* vcpu, irqid_t intp_id);

#if (IRQC == APLIC)
static inline bool vaplic_mode_is_level(uint32_t mode)
{
    mode &= APLIC_SRCCFG_SM;
    return mode == APLIC_SOURCECFG_SM_LEVEL_HIGH || mode == APLIC_SOURCECFG_SM_LEVEL_LOW;
}

static inline bool vaplic_source_is_level(struct vcpu* vcpu, irqid_t intp_id)
{
    return vaplic_intp_valid(intp_id) &&
        vaplic_mode_is_level(vcpu->vm->arch.vaplic.srccfg[intp_id]);
}
#endif

void vaplic_set_hw(struct vm* vm, irqid_t intp_id)
{
    if (intp_id < APLIC_MAX_INTERRUPTS) {
        bitmap_set(vm->arch.vaplic.hw, intp_id);
    }
}

/**
 * @brief Returns the target hart index of a given interrupt
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @return vcpuid_t target hart index of the given interrupt
 */
static inline vcpuid_t vaplic_get_hart_index(struct vcpu* vcpu, irqid_t intp_id)
{
    return (vaplic_get_target(vcpu, intp_id) >> APLIC_TARGET_HART_IDX_SHIFT) &
        APLIC_TARGET_HART_IDX_MASK;
}

/**
 * @brief Returns if a given interrupt is associated to the physical source
 *
 * @param vcpu virtual cpu running
 * @param intp_id interrupt to evaluate
 * @return true if is a physical intp
 * @return false if is NOT a physical intp
 */
static bool vaplic_get_hw(struct vcpu* vcpu, irqid_t intp_id)
{
    bool ret = false;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (vaplic_intp_valid(intp_id)) {
        ret = bitmap_get(vaplic->hw, intp_id);
    }
    return ret;
}

/**
 * @brief Returns if a given interrupt is pending
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @return true if the interrupt is pending
 * @return false if the interrupt is NOT pending
 */
static bool vaplic_get_pend(struct vcpu* vcpu, irqid_t intp_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (vaplic_intp_valid(intp_id)) {
        ret = !!GET_INTP_REG(vaplic->ip, intp_id);
    }
    return ret;
}

/**
 * @brief Returns if a given interrupt is enbaled
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @return true if the interrupt is enabled
 * @return false if the interrupt is NOT enabled
 */
static bool vaplic_get_enbl(struct vcpu* vcpu, irqid_t intp_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (vaplic_intp_valid(intp_id)) {
        ret = !!GET_INTP_REG(vaplic->ie, intp_id);
    }
    return ret;
}

/**
 * @brief Returns if a given interrupt is active for this domain.
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt id
 * @return true if the interrupt is active
 * @return false if the interrupt is NOT active
 */
static bool vaplic_get_active(struct vcpu* vcpu, irqid_t intp_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    bool ret = false;
    if (vaplic_intp_valid(intp_id)) {
        ret = !!GET_INTP_REG(vaplic->active, intp_id);
    }
    return ret;
}

/**
 * @brief Set a given interrupt as pending
 *
 * @pre This function should only be called by a function that has taken the lock.
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt id
 * @return true if interrupt was set pending
 * @return false if interrupt was NOT set pending
 */
static bool vaplic_set_pend(struct vcpu* vcpu, irqid_t intp_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    bool ret = false;

    if (vaplic_intp_valid(intp_id) && !vaplic_get_pend(vcpu, intp_id) &&
        vaplic_get_active(vcpu, intp_id)) {
        SET_INTP_REG(vaplic->ip, intp_id);
        ret = true;
    }
    return ret;
}

#if (IRQC == APLIC)

static uint32_t vaplic_get_idelivery(struct vcpu* vcpu, idcid_t idc_id);
static uint32_t vaplic_get_iforce(struct vcpu* vcpu, idcid_t idc_id);
static uint32_t vaplic_get_ithreshold(struct vcpu* vcpu, idcid_t idc_id);
static void vaplic_update_hart(struct vcpu* vcpu, size_t vhart_index, irqid_t irq_id);

#if (IRQC == APLIC)
static uint32_t vaplic_level_edge_mode(uint32_t level_mode, bool asserted)
{
    bool level_high = (level_mode & APLIC_SRCCFG_SM) == APLIC_SOURCECFG_SM_LEVEL_HIGH;
    if (asserted) {
        return level_high ? APLIC_SOURCECFG_SM_EDGE_FALL : APLIC_SOURCECFG_SM_EDGE_RISE;
    }
    return level_high ? APLIC_SOURCECFG_SM_EDGE_RISE : APLIC_SOURCECFG_SM_EDGE_FALL;
}

static bool vaplic_level_read_asserted(
    irqid_t intp_id, uint32_t level_mode, uint32_t physical_mode)
{
    size_t reg = intp_id / APLIC_NUM_INTP_PER_REG;
    uint32_t mask = 1U << (intp_id % APLIC_NUM_INTP_PER_REG);
    bool rectified = (aplic_get_inclrip_reg(reg) & mask) != 0U;
    bool raw_high = rectified ^ ((physical_mode & 1U) != 0U);

    return raw_high ^ ((level_mode & 1U) != 0U);
}

/* Caller holds vaplic->lock. */
static bool vaplic_level_resample(struct vcpu* vcpu, irqid_t intp_id, uint32_t level_mode)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t physical_mode = aplic_get_sourcecfg(intp_id) & APLIC_SRCCFG_SM;

    if (physical_mode != APLIC_SOURCECFG_SM_EDGE_RISE &&
        physical_mode != APLIC_SOURCECFG_SM_EDGE_FALL) {
        physical_mode = vaplic_level_edge_mode(level_mode, false);
        aplic_set_sourcecfg(intp_id, physical_mode);
        fence_sync_write();
    }

    bool asserted = vaplic_level_read_asserted(intp_id, level_mode, physical_mode);
    uint32_t required_mode = vaplic_level_edge_mode(level_mode, asserted);

    if (physical_mode != required_mode) {
        aplic_set_sourcecfg(intp_id, required_mode);
        fence_sync_write();

        bool observed = vaplic_level_read_asserted(intp_id, level_mode, required_mode);
        if (observed != asserted) {
            asserted = observed;
            aplic_set_sourcecfg(intp_id, vaplic_level_edge_mode(level_mode, asserted));
            fence_sync_write();
        }
    }

    if (asserted) {
        SET_INTP_REG(vaplic->level_asserted, intp_id);
        SET_INTP_REG(vaplic->ip, intp_id);
    } else {
        CLR_INTP_REG(vaplic->level_asserted, intp_id);
        CLR_INTP_REG(vaplic->ip, intp_id);
    }
    return asserted;
}
#endif

/**
 * @brief Converts a virtual cpu id into the physical one
 *
 * @param vcpu Virtual cpu to convert
 * @return int The physical cpu id; or INVALID_CPUID in case of error.
 */
static inline cpuid_t vaplic_vcpuid_to_pcpuid(struct vcpu* vcpu, vcpuid_t vhart)
{
    return vm_translate_to_pcpuid(vcpu->vm, vhart);
}

/* Caller holds vaplic->lock, including when refreshing another vCPU's tree. */
static void vaplic_refresh_group(struct vcpu* vcpu, size_t group)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t candidates = vaplic->active[group] & vaplic->ip[group] & vaplic->ie[group];
    uint32_t target_hart = (uint32_t)vcpu->id;
    vaplic_selector_update(&vcpu->arch.aplic_selector, vaplic->target, group, candidates,
        target_hart);
}

static void vaplic_update_topi(struct vcpu* vcpu)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    vaplic->topi_claimi[vcpu->id] = vaplic_selector_topi(&vcpu->arch.aplic_selector, vaplic->target,
        vaplic_get_ithreshold(vcpu, vcpu->id));
}

static void vaplic_refresh_idc(struct vcpu* vcpu, irqid_t irq)
{
    if (vaplic_intp_valid(irq)) {
        vaplic_refresh_group(vcpu, irq / VAPLIC_SELECTOR_GROUP_SIZE);
    }
    vaplic_update_topi(vcpu);
}

enum { UPDATE_HART_LINE };

union vaplic_msg_data {
    struct {
        uint32_t vhart_index;
        uint32_t irq_id;
    };
    uint64_t raw;
};

static void vaplic_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vaplic_ipi_handler, VPLIC_IPI_ID)

/**
 * @brief Updates the interrupt line for a single hart
 *
 * @param vcpu virtual cpu
 * @param vhart_index hart id to update
 */
static void vaplic_update_hart_line(struct vcpu* vcpu, vcpuid_t vhart_index, irqid_t irq_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    cpuid_t pcpu_id = vaplic_vcpuid_to_pcpuid(vcpu, vhart_index);

    /**
     *  If the current cpu is the targeting cpu, signal the intp to the hart. Else, send a mensage
     *  to the targeting cpu
     */
    if (pcpu_id == cpu()->id) {
        struct vcpu* target = vm_get_vcpu(vcpu->vm, vhart_index);
        vaplic_refresh_idc(target, irq_id);

        bool asserted = (vaplic_get_domaincfg(vcpu) & APLIC_DOMAINCFG_IE) != 0U &&
            vaplic_get_idelivery(vcpu, vhart_index) != 0U &&
            (vaplic->topi_claimi[vhart_index] != 0U || vaplic_get_iforce(vcpu, vhart_index) != 0U);
        if (asserted) {
            csrs_hvip_set(HIP_VSEIP);
        } else {
            csrs_hvip_clear(HIP_VSEIP);
        }
    } else {
        union vaplic_msg_data data = {
            .vhart_index = (uint32_t)vhart_index,
            .irq_id = (uint32_t)irq_id,
        };
        struct cpu_msg msg = { (uint32_t)VPLIC_IPI_ID, UPDATE_HART_LINE, data.raw };
        cpu_send_msg(pcpu_id, &msg);
    }
}

/**
 * @brief Processes an incoming event.
 *
 * @param event the event id
 * @param data
 */
static void vaplic_ipi_handler(uint32_t event, uint64_t data)
{
    switch (event) {
        case UPDATE_HART_LINE: {
            union vaplic_msg_data msg_data = { .raw = data };
            struct vcpu* vcpu = cpu()->vcpu;
            spin_lock(&vcpu->vm->arch.vaplic.lock);
            vaplic_update_hart_line(vcpu, (vcpuid_t)msg_data.vhart_index, (irqid_t)msg_data.irq_id);
            spin_unlock(&vcpu->vm->arch.vaplic.lock);
            break;
        }
        default:
            WARNING("Unknown VAPLIC IPI event\n");
            break;
    }
}

/**
 * @brief Set idelivery register for a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in idelivery. Only 0 and 1 are allowed.
 */
static void vaplic_set_idelivery(struct vcpu* vcpu, idcid_t idc_id, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    if (idc_id < vaplic->idc_num) {
        if ((new_val & 0x1) != 0) {
            bitmap_set(vaplic->idelivery, idc_id);
        } else {
            bitmap_clear(vaplic->idelivery, idc_id);
        }
    }
    vaplic_update_hart(vcpu, idc_id, INVALID_IRQID);
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Read idelivery register from a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from idelivery
 */
static uint32_t vaplic_get_idelivery(struct vcpu* vcpu, idcid_t idc_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (idc_id < vaplic->idc_num) {
        ret = bitmap_get(vaplic->idelivery, idc_id);
    }
    return ret;
}

/**
 * @brief Set iforce register for a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in iforce. Only 0 and 1 are allowed.
 */
static void vaplic_set_iforce(struct vcpu* vcpu, idcid_t idc_id, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    if (idc_id < vaplic->idc_num) {
        if ((new_val & 0x1) != 0) {
            bitmap_set(vaplic->iforce, idc_id);
        } else {
            bitmap_clear(vaplic->iforce, idc_id);
        }
    }
    vaplic_update_hart(vcpu, idc_id, INVALID_IRQID);
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Read iforce register from a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from iforce
 */
static uint32_t vaplic_get_iforce(struct vcpu* vcpu, idcid_t idc_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (idc_id < vaplic->idc_num) {
        ret = bitmap_get(vaplic->iforce, idc_id);
    }
    return ret;
}

/**
 * @brief Set ithreshold register for a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in ithreshold
 */
static void vaplic_set_ithreshold(struct vcpu* vcpu, idcid_t idc_id, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    if (idc_id < vaplic->idc_num) {
        vaplic->ithreshold[idc_id] = new_val & APLIC_IPRIO_MASK;
    }
    vaplic_update_hart(vcpu, idc_id, INVALID_IRQID);
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Read ithreshold register from a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from ithreshold
 */
static uint32_t vaplic_get_ithreshold(struct vcpu* vcpu, idcid_t idc_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (idc_id < vaplic->idc_num) {
        ret = vaplic->ithreshold[idc_id];
    }
    return ret;
}

/**
 * @brief Read topi register from a given idc.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from topi
 */
static uint32_t vaplic_get_topi(struct vcpu* vcpu, idcid_t idc_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    if (idc_id < vaplic->idc_num) {
        ret = vaplic->topi_claimi[idc_id];
    }
    return ret;
}

/**
 * @brief Returns the highest pending and enabled interrupt.
 *
 * Claimi has the same value as topi. However, reading claimi has the side effect of clearing the
 * pending bit for the reported interrupt identity.
 *
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return 32 bit value read from virt claimi
 */
static uint32_t vaplic_get_claimi(struct vcpu* vcpu, idcid_t idc_id)
{
    uint32_t ret = 0;
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    if (idc_id < vaplic->idc_num) {
        ret = vaplic->topi_claimi[idc_id];
        irqid_t claimed_id = (ret >> IDC_CLAIMI_INTP_ID_SHIFT);
#if (IRQC == APLIC)
        if (vaplic_intp_valid(claimed_id) &&
            (!vaplic_source_is_level(vcpu, claimed_id) ||
                !GET_INTP_REG(vaplic->level_asserted, claimed_id))) {
            CLR_INTP_REG(vaplic->ip, claimed_id);
        }
#else
        CLR_INTP_REG(vaplic->ip, claimed_id);
#endif
        /** Spurious intp*/
        if (ret == 0) {
            bitmap_clear(vaplic->iforce, idc_id);
        }
        vaplic_update_hart(vcpu, idc_id, claimed_id);
    }
    spin_unlock(&vaplic->lock);
    return ret;
}

/**
 * @brief idelivery register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_idelivery_access(struct emul_access* acc, idcid_t idc_id)
{
    if (acc->write) {
        vaplic_set_idelivery(cpu()->vcpu, idc_id, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_idelivery(cpu()->vcpu, idc_id));
    }
}

/**
 * @brief iforce register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_iforce_access(struct emul_access* acc, idcid_t idc_id)
{
    if (acc->write) {
        vaplic_set_iforce(cpu()->vcpu, idc_id, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_iforce(cpu()->vcpu, idc_id));
    }
}

/**
 * @brief ithreshold register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_ithreshold_access(struct emul_access* acc, idcid_t idc_id)
{
    if (acc->write) {
        vaplic_set_ithreshold(cpu()->vcpu, idc_id, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_ithreshold(cpu()->vcpu, idc_id));
    }
}

/**
 * @brief topi register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_topi_access(struct emul_access* acc, idcid_t idc_id)
{
    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_topi(cpu()->vcpu, idc_id));
    }
}

/**
 * @brief claimi register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_claimi_access(struct emul_access* acc, idcid_t idc_id)
{
    if (!acc->write) {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_claimi(cpu()->vcpu, idc_id));
    }
}

/**
 * @brief Function to handle writes (or reads) to (from) IDC structure.
 *
 * @param acc emulated access
 * @return true  if conclude without errors.
 * @return false if the access is not aligned.
 */
static bool vaplic_idc_emul_handler(struct emul_access* acc)
{
    // only allow aligned word accesses
    if (acc->width != 4 || acc->addr & 0x3) {
        return false;
    }

    uint32_t addr = (uint32_t)(acc->addr);
    idcid_t idc_id = ((acc->addr - cpu()->vcpu->vm->arch.vaplic.aplic_idc_emul.va_base) >> 5) &
        APLIC_MAX_NUM_HARTS_MAKS;

    switch (addr & 0x1F) {
        case offsetof(struct aplic_idc_hw, idelivery):
            vaplic_emul_idelivery_access(acc, idc_id);
            break;
        case offsetof(struct aplic_idc_hw, iforce):
            vaplic_emul_iforce_access(acc, idc_id);
            break;
        case offsetof(struct aplic_idc_hw, ithreshold):
            vaplic_emul_ithreshold_access(acc, idc_id);
            break;
        case offsetof(struct aplic_idc_hw, topi):
            vaplic_emul_topi_access(acc, idc_id);
            break;
        case offsetof(struct aplic_idc_hw, claimi):
            vaplic_emul_claimi_access(acc, idc_id);
            break;
        default:
            if (!acc->write) {
                vcpu_writereg(cpu()->vcpu, acc->reg, 0);
            }
            break;
    }
    return true;
}

/**
 * @brief Triggers the hart/harts interrupt line update.
 *
 * @param vcpu virtual cpu
 * @param vhart_index virtual hart to update the interrupt line. If UPDATE_ALL_HARTS were passed,
 *        this function will trigger the interrupt line update to all virtual harts running in this
 *        vm.
 */
static void vaplic_update_hart(struct vcpu* vcpu, size_t vhart_index, irqid_t irq_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    if (vhart_index == UPDATE_ALL_HARTS && irq_id == INVALID_IRQID) {
        for (size_t i = 0; i < vaplic->idc_num; i++) {
            vaplic_update_hart_line(vcpu, (vcpuid_t)i, INVALID_IRQID);
        }
    } else if (vhart_index < vaplic->idc_num) {
        vaplic_update_hart_line(vcpu, (vcpuid_t)vhart_index, irq_id);
    }
}

#elif (IRQC == AIA)

/**
 * @brief Returns the target eeid of a given interrupt
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @return uint32_t eeid of the given interrupt
 */
static inline uint32_t vaplic_get_eeid(struct vcpu* vcpu, irqid_t intp_id)
{
    return vaplic_get_target(vcpu, intp_id) & APLIC_TARGET_EEID_MASK;
}

static void vaplic_forward_by_msi(struct vcpu* vcpu, irqid_t irq_id)
{
    // This function assumes domain is enabled

    bool irq_pend = vaplic_get_pend(vcpu, irq_id);
    bool irq_enbl = vaplic_get_enbl(vcpu, irq_id);

    if (irq_enbl && irq_pend) {
        vcpuid_t hart_index = vaplic_get_hart_index(vcpu, irq_id);
        uint32_t eeid = vaplic_get_eeid(vcpu, irq_id);
        struct vcpu* target_vcpu = vcpu;
        if (vcpu->id != hart_index) {
            target_vcpu = vm_get_vcpu(vcpu->vm, hart_index);
        }

        imsic_send_guest_msi(target_vcpu->phys_id, eeid);

        CLR_INTP_REG(vcpu->vm->arch.vaplic.ip, irq_id);
    }
}

/**
 * @brief Triggers the hart/harts interrupt line update.
 *
 * @param vcpu virtual cpu
 * @param vhart_index ignored - this parameter is only used in the implementation
 * for when imsics are not present to identify the IDC to which access triggered the call
 */
static void vaplic_update_hart(struct vcpu* vcpu, size_t vhart_index, irqid_t irq_id)
{
    UNUSED_ARG(vhart_index);

    bool domain_enbl = (vaplic_get_domaincfg(vcpu) & APLIC_DOMAINCFG_IE) != 0;

    if (domain_enbl) {
        if (irq_id == INVALID_IRQID) {
            for (irqid_t i = 1; i < APLIC_MAX_INTERRUPTS; i++) {
                vaplic_forward_by_msi(vcpu, i);
            }
        } else {
            vaplic_forward_by_msi(vcpu, irq_id);
        }
    }
}
#endif /* (IRQC == AIA) */

/*
 * A bitmap-register write can change 32 sources in one selector group. All
 * source/hardware writes are finished before entering here. Refresh each
 * affected IDC once; MSI forwarding still needs one operation per source.
 */
static void vaplic_update_word(struct vcpu* vcpu, size_t word, uint32_t changed)
{
#if (IRQC == APLIC)
    BITMAP_ALLOC(updated, APLIC_DOMAIN_NUM_HARTS) = { 0 };
#endif
    for (size_t bit = 0; bit < APLIC_NUM_INTP_PER_REG; bit++) {
        if ((changed & (1U << bit)) != 0U) {
            irqid_t irq = (irqid_t)(word * APLIC_NUM_INTP_PER_REG + bit);
            vcpuid_t hart = vaplic_get_hart_index(vcpu, irq);
#if (IRQC == APLIC)
            if (hart >= vcpu->vm->arch.vaplic.idc_num || bitmap_get(updated, hart)) {
                continue;
            }
            bitmap_set(updated, hart);
#endif
            vaplic_update_hart(vcpu, hart, irq);
        }
    }
}

/**
 * @brief Write to domaincfg register a new value.
 *
 * @param vcpu
 * @param new_val The new value to write to domaincfg
 */
static void vaplic_set_domaincfg(struct vcpu* vcpu, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    /** Update only the virtual domaincfg */
    /** Only Interrupt Enable is configurable */
    new_val &= APLIC_DOMAINCFG_IE;
    if (IRQC == AIA) {
        new_val |= APLIC_DOMAINCFG_DM;
    } else {
        new_val &= ~APLIC_DOMAINCFG_DM;
    }
    vaplic->domaincfg = new_val | APLIC_DOMAINCFG_RO80;
    vaplic_update_hart(vcpu, UPDATE_ALL_HARTS, INVALID_IRQID);
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Read from domaincfg
 *
 * @param vcpu virtual hart
 * @return uint32_t domaincfg value
 */
static uint32_t vaplic_get_domaincfg(struct vcpu* vcpu)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    return vaplic->domaincfg;
}

/**
 * @brief Read the sourcecfg register of a given interrupt
 *
 * @param vcpu virtual hart
 * @param intp_id interrupt ID
 * @return uint32_t value with the interrupt sourcecfg value
 */
static uint32_t vaplic_get_sourcecfg(struct vcpu* vcpu, irqid_t intp_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t ret = 0;

    if (vaplic_intp_valid(intp_id)) {
        ret = vaplic->srccfg[intp_id];
    }
    return ret;
}

/**
 * @brief Write the sourcecfg register of a given interrupt
 *
 * @param vcpu virtual hart
 * @param intp_id interrupt ID
 * @param new_val value to write to sourcecfg
 */
static void vaplic_set_sourcecfg(struct vcpu* vcpu, irqid_t intp_id, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    /** A virtual S-mode APLIC domain is a leaf, so delegation is not supported. */
    new_val &= (new_val & APLIC_SRCCFG_D) ? 0U : APLIC_SRCCFG_SM;

    /** Reserved source modes are WARL-mapped to inactive. */
    if (new_val == 2U || new_val == 3U) {
        new_val = APLIC_SOURCECFG_SM_INACTIVE;
    }

    spin_lock(&vaplic->lock);
    if (vaplic_intp_valid(intp_id) && vaplic_get_sourcecfg(vcpu, intp_id) != new_val) {
        vcpuid_t previous_hart = vaplic_get_hart_index(vcpu, intp_id);

        if (vaplic_get_hw(vcpu, intp_id)) {
            /* The virtual and physical enable state are kept in sync for hardware sources. */
            bool enabled = vaplic_get_enbl(vcpu, intp_id);

            if (enabled) {
                aplic_clr_enbl(intp_id);
            }
#if (IRQC == APLIC)
            if (vaplic_mode_is_level(new_val)) {
                aplic_clr_pend(intp_id);
                vaplic_level_resample(vcpu, intp_id, new_val);
            } else {
                CLR_INTP_REG(vaplic->level_asserted, intp_id);
                aplic_set_sourcecfg(intp_id, new_val);
                new_val = aplic_get_sourcecfg(intp_id);
            }
#else
            aplic_set_sourcecfg(intp_id, new_val);
            new_val = aplic_get_sourcecfg(intp_id);
#endif
            if (enabled && new_val != APLIC_SOURCECFG_SM_INACTIVE) {
                aplic_set_enbl(intp_id);
            }
        }
        vaplic->srccfg[intp_id] = new_val;

        if (new_val == APLIC_SOURCECFG_SM_INACTIVE) {
            CLR_INTP_REG(vaplic->active, intp_id);
            /** Zero pend, en and target registers if intp is now inactive */
            CLR_INTP_REG(vaplic->ip, intp_id);
            CLR_INTP_REG(vaplic->ie, intp_id);
            vaplic->target[intp_id] = 0;
        } else {
            SET_INTP_REG(vaplic->active, intp_id);
        }
        vaplic_update_hart(vcpu, previous_hart, intp_id);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Get the pending bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @return uint32_t value with pending values bit-mapped
 */
static uint32_t vaplic_get_setip(struct vcpu* vcpu, size_t reg)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t ret = 0;

    if (reg < APLIC_NUM_SETIx_REGS) {
        ret = vaplic->ip[reg];
        ret |= (aplic_get_pend_reg(reg) & vaplic->hw[reg]);
    }
    return ret;
}

/**
 * @brief Set the pending bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @param new_val value with pending interrupts bit-mapped
 */
static void vaplic_set_setip(struct vcpu* vcpu, size_t reg, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t update_intps = 0;

    spin_lock(&vaplic->lock);
    if (reg < APLIC_NUM_SETIx_REGS) {
        new_val &= vaplic->active[reg];
        update_intps = (~vaplic->ip[reg]) & new_val;
        vaplic->ip[reg] |= new_val;
        vaplic_update_word(vcpu, reg, update_intps);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Set the pending bit for a given interrupt
 *
 * @param vcpu virtual cpu
 * @param new_val interrupt to set the pending bit
 */
static void vaplic_set_setipnum(struct vcpu* vcpu, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    spin_lock(&vaplic->lock);
    if (vaplic_set_pend(vcpu, new_val)) {
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, new_val), new_val);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Clear the pending bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg  regiter index
 * @param new_val value with interrupts to be cleared per bit
 */
static void vaplic_set_in_clrip(struct vcpu* vcpu, size_t reg, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t update_intps = 0;

    spin_lock(&vaplic->lock);
    if (reg < APLIC_NUM_CLRIx_REGS) {
        new_val &= vaplic->active[reg];
#if (IRQC == APLIC)
        new_val &= ~vaplic->level_asserted[reg];
#endif
        update_intps = vaplic->ip[reg];
        vaplic->ip[reg] &= ~(new_val);
        new_val &= vaplic->hw[reg];
        aplic_clr_pend_reg(reg, new_val);
        vaplic->ip[reg] |= aplic_get_pend_reg(reg) & vaplic->hw[reg] & vaplic->active[reg];
        /* Hardware resampling can add pending bits as well as remove them. */
        update_intps ^= vaplic->ip[reg];
        vaplic_update_word(vcpu, reg, update_intps);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Get the rectified input values per source
 *
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @return uint32_t value with rectified intp per bit
 */
static uint32_t vaplic_get_in_clrip(struct vcpu* vcpu, size_t reg)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t ret = 0;
    if (reg < APLIC_NUM_CLRIx_REGS) {
        ret = (aplic_get_inclrip_reg(reg) & vaplic->hw[reg]);
#if (IRQC == APLIC)
        for (size_t bit = 0; bit < APLIC_NUM_INTP_PER_REG; bit++) {
            irqid_t intp_id = (irqid_t)(reg * APLIC_NUM_INTP_PER_REG + bit);
            if (vaplic_source_is_level(vcpu, intp_id)) {
                ret &= ~(1U << bit);
                ret |= vaplic->level_asserted[reg] & (1U << bit);
            }
        }
#endif
    }
    return ret;
}

/**
 * @brief Clear the pending bit for a given interrupt
 *
 * @param vcpu virtual cpu
 * @param new_val interrupt to clear the pending bit
 */
static void vaplic_set_clripnum(struct vcpu* vcpu, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    spin_lock(&vaplic->lock);
    if (vaplic_get_active(vcpu, new_val) && vaplic_get_pend(vcpu, new_val)) {
        bool clear = true;
#if (IRQC == APLIC)
        clear = !vaplic_source_is_level(vcpu, new_val) ||
            !GET_INTP_REG(vaplic->level_asserted, new_val);
#endif
        if (clear) {
            if (vaplic_get_hw(vcpu, new_val)) {
                aplic_clr_pend(new_val);
                if (!aplic_get_pend(new_val)) {
                    CLR_INTP_REG(vaplic->ip, new_val);
                }
            } else {
                CLR_INTP_REG(vaplic->ip, new_val);
            }
            vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, new_val), new_val);
        }
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Get the enabled bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @return uint32_t value with enabled value bit-mapped
 */
static uint32_t vaplic_get_setie(struct vcpu* vcpu, size_t reg)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t ret = 0;

    if (reg < APLIC_NUM_SETIx_REGS) {
        ret = vaplic->ie[reg];
    }
    return ret;
}

/**
 * @brief Set the enabled bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @param new_val value with interrupts to be enabled per bit
 */
static void vaplic_set_setie(struct vcpu* vcpu, size_t reg, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t update_intps = 0;
    uint32_t new_hw_intps = 0;

    spin_lock(&vaplic->lock);
    if (reg < APLIC_NUM_SETIx_REGS && vaplic_get_setie(vcpu, reg) != new_val) {
        new_val &= vaplic->active[reg];
        update_intps = ~(vaplic->ie[reg]) & new_val;
        vaplic->ie[reg] |= new_val;
        new_hw_intps = update_intps & vaplic->hw[reg];
#if (IRQC == APLIC)
        for (size_t bit = 0; bit < APLIC_NUM_INTP_PER_REG; bit++) {
            irqid_t intp_id = (irqid_t)(reg * APLIC_NUM_INTP_PER_REG + bit);
            if ((new_hw_intps & (1U << bit)) != 0U &&
                vaplic_source_is_level(vcpu, intp_id)) {
                aplic_clr_pend(intp_id);
                vaplic_level_resample(vcpu, intp_id, vaplic->srccfg[intp_id]);
            }
        }
#endif
        aplic_set_enbl_reg(reg, new_hw_intps);
        vaplic_update_word(vcpu, reg, update_intps);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Set the enabled bit for a given interrupt
 *
 * @param vcpu virtual cpu
 * @param new_val interrupt to set the enable bit
 */
static void vaplic_set_setienum(struct vcpu* vcpu, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    spin_lock(&vaplic->lock);
    if (vaplic_get_active(vcpu, new_val) && !vaplic_get_enbl(vcpu, new_val)) {
        if (vaplic_get_hw(vcpu, new_val)) {
#if (IRQC == APLIC)
            if (vaplic_source_is_level(vcpu, new_val)) {
                aplic_clr_pend(new_val);
                vaplic_level_resample(vcpu, new_val, vaplic->srccfg[new_val]);
            }
#endif
            aplic_set_enbl(new_val);
        }
        SET_INTP_REG(vaplic->ie, new_val);
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, new_val), new_val);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Clear the enabled bits for interrupts [32*reg:(32*reg)+31]
 *
 * @param vcpu virtual cpu
 * @param reg  regiter index
 * @param new_val value with interrupts to be cleared per bit
 */
static void vaplic_set_clrie(struct vcpu* vcpu, size_t reg, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t update_intps = 0;

    spin_lock(&vaplic->lock);
    if (reg < APLIC_NUM_SETIx_REGS) {
        new_val &= vaplic->active[reg];
        update_intps = vaplic->ie[reg] & new_val;
        vaplic->ie[reg] &= ~(new_val);
        new_val &= vaplic->hw[reg];
        aplic_clr_enbl_reg(reg, new_val);
        vaplic_update_word(vcpu, reg, update_intps);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Clear the enabled bit for a given interrupt
 *
 * @param vcpu virtual cpu
 * @param new_val interrupt to clear the enable bit
 */
static void vaplic_set_clrienum(struct vcpu* vcpu, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    spin_lock(&vaplic->lock);
    if (vaplic_get_active(vcpu, new_val) && vaplic_get_enbl(vcpu, new_val)) {
        if (vaplic_get_hw(vcpu, new_val)) {
            aplic_clr_enbl(new_val);
        }
        CLR_INTP_REG(vaplic->ie, new_val);
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, new_val), new_val);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Write to target register of a given interrupt
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @param new_val value to write to target
 */
static void vaplic_set_target(struct vcpu* vcpu, irqid_t intp_id, uint32_t new_val)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    vcpuid_t hart_index = (new_val >> APLIC_TARGET_HART_IDX_SHIFT) & APLIC_TARGET_HART_IDX_MASK;
    uint8_t priority = (uint8_t)(new_val & APLIC_IPRIO_MASK);
    irqid_t eiid = new_val & APLIC_TARGET_EEID_MASK;
    cpuid_t pcpu_id = vm_translate_to_pcpuid(vcpu->vm, hart_index);
    vcpuid_t prev_hart_index = 0;

    spin_lock(&vaplic->lock);
    if (pcpu_id == INVALID_CPUID) {
        /** If the hart index is invalid, make it vcpu = 0 and read the new pcpu. Software should
         *  not write anything other than legal values to such a field */
        hart_index = 0;
        pcpu_id = vm_translate_to_pcpuid(vcpu->vm, hart_index);
    }

    if (IRQC == AIA) {
        new_val &= APLIC_TARGET_MSI_MASK;
    } else {
        new_val &= APLIC_TARGET_DIRECT_MASK;
        if (priority == 0) {
            new_val |= APLIC_TARGET_MAX_PRIO;
            priority = APLIC_TARGET_MAX_PRIO;
        }
    }

    if (vaplic_get_active(vcpu, intp_id) && vaplic_get_target(vcpu, intp_id) != new_val) {
        prev_hart_index = vaplic_get_hart_index(vcpu, intp_id);
        if (vaplic_get_hw(vcpu, intp_id)) {
            aplic_set_target_hart(intp_id, pcpu_id);
            if (IRQC == AIA) {
                aplic_set_target_guest(intp_id, 1);
                aplic_set_target_eiid(intp_id, eiid);
                eiid = aplic_get_target_eiid(intp_id);
            } else {
                aplic_set_target_prio(intp_id, priority);
                priority = aplic_get_target_prio(intp_id);
            }
        }

        if (IRQC == AIA) {
            uint8_t guest_index =
                (new_val >> APLIC_TARGET_GUEST_IDX_SHIFT) & APLIC_TARGET_GUEST_INDEX_MASK;
            vaplic->target[intp_id] = (uint32_t)(hart_index << APLIC_TARGET_HART_IDX_SHIFT) |
                (uint32_t)(guest_index << APLIC_TARGET_GUEST_IDX_SHIFT) | eiid;
        } else {
            vaplic->target[intp_id] =
                (uint32_t)(hart_index << APLIC_TARGET_HART_IDX_SHIFT) | priority;
        }

        if (prev_hart_index != hart_index) {
            vaplic_update_hart(vcpu, prev_hart_index, intp_id);
        }
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, intp_id), intp_id);
    }
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Read target register from a given interrupt
 *
 * @param vcpu virtual cpu
 * @param intp_id interrupt ID
 * @return uint32_t value with target value
 */
static uint32_t vaplic_get_target(struct vcpu* vcpu, irqid_t intp_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;
    uint32_t ret = 0;

    if (vaplic_intp_valid(intp_id)) {
        ret = vaplic->target[intp_id];
    }
    return ret;
}

/**
 * @brief domaincfg register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_domaincfg_access(struct emul_access* acc)
{
    if (acc->write) {
        vaplic_set_domaincfg(cpu()->vcpu, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_domaincfg(cpu()->vcpu));
    }
}

/**
 * @brief sourcecfg register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_srccfg_access(struct emul_access* acc)
{
    size_t intp = (acc->addr & 0xFFF) / 4;
    if (acc->write) {
        vaplic_set_sourcecfg(cpu()->vcpu, (irqid_t)intp,
            (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_sourcecfg(cpu()->vcpu, (irqid_t)intp));
    }
}

/**
 * @brief setip register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_setip_access(struct emul_access* acc)
{
    size_t reg = (acc->addr & 0x7F) / 4;
    if (acc->write) {
        vaplic_set_setip(cpu()->vcpu, reg, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_setip(cpu()->vcpu, reg));
    }
}

/**
 * @brief setipnum register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_setipnum_access(struct emul_access* acc)
{
    if (acc->write) {
        vaplic_set_setipnum(cpu()->vcpu, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

/**
 * @brief clrip register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_in_clrip_access(struct emul_access* acc)
{
    size_t reg = (acc->addr & 0x7F) / 4;
    if (acc->write) {
        vaplic_set_in_clrip(cpu()->vcpu, reg, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_in_clrip(cpu()->vcpu, reg));
    }
}

/**
 * @brief clripnum register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_clripnum_access(struct emul_access* acc)
{
    if (acc->write) {
        vaplic_set_clripnum(cpu()->vcpu, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

/**
 * @brief setie register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_setie_access(struct emul_access* acc)
{
    size_t reg = (acc->addr & 0x7F) / 4;
    if (acc->write) {
        vaplic_set_setie(cpu()->vcpu, reg, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_setie(cpu()->vcpu, reg));
    }
}

/**
 * @brief setienum register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_setienum_access(struct emul_access* acc)
{
    if (acc->write) {
        vaplic_set_setienum(cpu()->vcpu, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

/**
 * @brief clrie register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_clrie_access(struct emul_access* acc)
{
    size_t reg = (acc->addr & 0x7F) / 4;
    if (acc->write) {
        vaplic_set_clrie(cpu()->vcpu, reg, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

/**
 * @brief clrienum register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_clrienum_access(struct emul_access* acc)
{
    if (acc->write) {
        vaplic_set_clrienum(cpu()->vcpu, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

/**
 * @brief target register access emulation function
 *
 * @param acc access information
 *
 * It determines whether it needs to call the write or read funcion for the choosen register.
 */
static void vaplic_emul_target_access(struct emul_access* acc)
{
    size_t intp = (acc->addr & 0xFFF) / 4;
    if (acc->write) {
        vaplic_set_target(cpu()->vcpu, (irqid_t)intp, (uint32_t)vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_target(cpu()->vcpu, (irqid_t)intp));
    }
}

/**
 * @brief Injects a given interrupt into a given vcpu
 *
 * @param vcpu vcpu to inject the interrupt
 * @param intp_id interrupt unique id
 */
void vaplic_inject(struct vcpu* vcpu, irqid_t intp_id)
{
    struct vaplic* vaplic = &vcpu->vm->arch.vaplic;

    spin_lock(&vaplic->lock);
#if (IRQC == APLIC)
    if (vaplic_get_hw(vcpu, intp_id) && vaplic_source_is_level(vcpu, intp_id)) {
        vaplic_level_resample(vcpu, intp_id, vaplic->srccfg[intp_id]);
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, intp_id), intp_id);
    } else if (vaplic_set_pend(vcpu, intp_id)) {
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, intp_id), intp_id);
    }
#else
    /** If the intp was successfully injected, update the heart line. */
    if (vaplic_set_pend(vcpu, intp_id)) {
        vaplic_update_hart(vcpu, vaplic_get_hart_index(vcpu, intp_id), intp_id);
    }
#endif
    spin_unlock(&vaplic->lock);
}

/**
 * @brief Given an address, this function returns if it is reserved
 *
 * @param addr address to check
 * @return true if the address is reserved
 * @return false if the address is NOT reserved
 */
static bool vaplic_domain_emul_reserved(uint16_t addr)
{
    bool ret = false;
    if (in_range(addr, offsetof(struct aplic_control_hw, reserved1),
            sizeof(aplic_control->reserved1) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved2),
            sizeof(aplic_control->reserved2) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved3),
            sizeof(aplic_control->reserved3) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved4),
            sizeof(aplic_control->reserved4) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved5),
            sizeof(aplic_control->reserved5) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved6),
            sizeof(aplic_control->reserved6) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved7),
            sizeof(aplic_control->reserved7) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved8),
            sizeof(aplic_control->reserved8) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved9),
            sizeof(aplic_control->reserved9) - 4) ||
        in_range(addr, offsetof(struct aplic_control_hw, reserved10),
            sizeof(aplic_control->reserved10) - 4)) {
        ret = true;
    }
    return ret;
}

/**
 * @brief Function to handle writes (or reads) to (from) domain structure.
 *
 * @param acc emulated access
 * @return true if conclude without errors.
 * @return false if the access is not aligned.
 */
static bool vaplic_domain_emul_handler(struct emul_access* acc)
{
    uint16_t emul_addr = 0;
    bool read_only_zero = false;

    // only allow aligned word accesses
    if (acc->width != 4 || acc->addr & 0x3) {
        return false;
    }

    emul_addr = (acc->addr - cpu()->vcpu->vm->arch.vaplic.aplic_domain_emul.va_base) & 0x3fff;

    if (vaplic_domain_emul_reserved(emul_addr)) {
        read_only_zero = true;
    } else {
        switch (emul_addr >> 12) {
            case 0:
                if (emul_addr == offsetof(struct aplic_control_hw, domaincfg)) {
                    vaplic_emul_domaincfg_access(acc);
                } else {
                    vaplic_emul_srccfg_access(acc);
                }
                break;
            case 1:
                switch (emul_addr >> 7) {
                    case offsetof(struct aplic_control_hw, setip) >> 7:
                        vaplic_emul_setip_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, setipnum) >> 7:
                        vaplic_emul_setipnum_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, in_clrip) >> 7:
                        vaplic_emul_in_clrip_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, clripnum) >> 7:
                        vaplic_emul_clripnum_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, setie) >> 7:
                        vaplic_emul_setie_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, setienum) >> 7:
                        vaplic_emul_setienum_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, clrie) >> 7:
                        vaplic_emul_clrie_access(acc);
                        break;
                    case offsetof(struct aplic_control_hw, clrienum) >> 7:
                        vaplic_emul_clrienum_access(acc);
                        break;
                    default:
                        read_only_zero = true;
                        break;
                }
                break;
            case 3:
                if (emul_addr == offsetof(struct aplic_control_hw, genmsi)) {
                    read_only_zero = true;
                } else {
                    vaplic_emul_target_access(acc);
                }
                break;
            default:
                read_only_zero = true;
                break;
        }
    }

    if (read_only_zero) {
        if (!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
    }
    return true;
}

void vaplic_init(struct vm* vm, const union vm_irqc_dscrp* vm_irqc_dscrp)
{
    if (cpu()->id == vm->master) {
        /* 1 IDC per hart */
        vm->arch.vaplic.idc_num = vm->cpu_num;
        vm->arch.vaplic.lock = SPINLOCK_INITVAL;

        vm->arch.vaplic.aplic_domain_emul =
            (struct emul_mem){ .va_base = vm_irqc_dscrp->aia.aplic.base,
                .size = sizeof(struct aplic_control_hw),
                .handler = vaplic_domain_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vaplic.aplic_domain_emul);

#if (IRQC == APLIC)
        vm->arch.vaplic.aplic_idc_emul =
            (struct emul_mem){ .va_base = vm_irqc_dscrp->aia.aplic.base + APLIC_IDC_OFF,
                .size = sizeof(struct aplic_idc_hw) * vm->arch.vaplic.idc_num,
                .handler = vaplic_idc_emul_handler };

        vm_emul_add_mem(vm, &vm->arch.vaplic.aplic_idc_emul);
#endif
    }
}
