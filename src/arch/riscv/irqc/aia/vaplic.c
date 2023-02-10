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
#include <arch/csrs.h>

#define APLIC_MIN_PRIO 0xFF

/**
 * @brief Get the bit from reg object
 * 
 * @param reg 
 * @param bit 
 * @return unsigned 
 */
static inline unsigned get_bit_from_reg(uint32_t reg, size_t bit){
    return (reg & (1 << bit)) ? 1U : 0U;
}

/**
 * @brief Set the bit from reg object
 * 
 * @param reg 
 * @param bit 
 */
static inline void set_bit_from_reg(uint32_t* reg, size_t bit){
    *reg |=  (1 << bit);
}

/**
 * @brief Clear the bit from reg object
 * 
 * @param reg 
 * @param bit 
 */
static inline void clr_bit_from_reg(uint32_t* reg, size_t bit){
    *reg &=  ~(1 << bit);
}

/**
 * @brief Converts a virtual cpu id into the physical one
 * 
 * @param vcpu Virtual cpu to convert
 * @return int The physical cpu id; or INVALID_CPUID in case of error.
 */
static inline int vaplic_vcpuid_to_pcpuid(struct vcpu *vcpu){
    return vm_translate_to_pcpuid(vcpu->vm, vcpu->id);
}

static uint32_t vaplic_get_domaincfg(struct vcpu *vcpu);
static uint32_t vaplic_get_target(struct vcpu *vcpu, irqid_t intp_id); 
static uint32_t vaplic_get_idelivery(struct vcpu *vcpu, uint16_t idc_id);
static uint32_t vaplic_get_iforce(struct vcpu *vcpu, uint16_t idc_id);
static uint32_t vaplic_get_ithreshold(struct vcpu *vcpu, uint16_t idc_id);

void vaplic_set_hw(struct vm *vm, irqid_t intp_id)
{
    if (intp_id < APLIC_MAX_INTERRUPTS) {
        bitmap_set(vm->arch.vxplic.hw,intp_id);
    }
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
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (intp_id <= APLIC_MAX_INTERRUPTS) ret = bitmap_get(vxplic->hw, intp_id);
    return ret;
}

static bool vaplic_get_pend(struct vcpu *vcpu, irqid_t intp_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (intp_id < APLIC_MAX_INTERRUPTS){
        ret = get_bit_from_reg(vxplic->setip[intp_id/32], intp_id);
    }
    return ret;
}

static bool vaplic_get_enbl(struct vcpu *vcpu, irqid_t intp_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (intp_id < APLIC_MAX_INTERRUPTS){
        ret = get_bit_from_reg(vxplic->setie[intp_id/32], intp_id);
    }
    return ret;
}

/**
 * @brief Emulates the notifier aplic module.
 *        (02/11/2022): computes the next pending bit.
 *        Only direct mode is supported. 
 * 
 * @param vcpu 
 * @return irqid_t 
 */
static irqid_t vaplic_emul_notifier(struct vcpu* vcpu){
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;

    /** Find highest pending and enabled interrupt */
    uint32_t max_prio = APLIC_MIN_PRIO;
    irqid_t int_id = 0;
    uint32_t hart_index = 0;
    uint32_t prio = 0;

    for (size_t i = 1; i < APLIC_MAX_INTERRUPTS; i++) {
        if (vaplic_get_pend(vcpu, i) && vaplic_get_enbl(vcpu, i)) {
            uint32_t target = vaplic_get_target(vcpu, i); 
            prio = target & 0xFF; 
            
            if (prio < max_prio) {
                max_prio = prio;
                int_id = i;
                hart_index = (target >> 18) & 0x3FFF;
            }
        }
    }

    /** Can interrupt be delivery? */
    uint32_t domaincgfIE = (vaplic_get_domaincfg(vcpu) >> 8) & 0x1;
    uint32_t threshold = vaplic_get_ithreshold(vcpu, hart_index);
    uint32_t delivery = vaplic_get_idelivery(vcpu, hart_index);
    uint32_t force =  vaplic_get_iforce(vcpu, hart_index);
    if ((max_prio < threshold || threshold == 0 || force == 1) && 
         delivery == 1 && domaincgfIE == 1){
        vxplic->topi_claimi[hart_index] = (int_id << 16) | prio;
        return int_id;
    }
    else{
        return 0;
    }
}

enum {UPDATE_HART_LINE};
static void vaplic_ipi_handler(uint32_t event, uint64_t data);
CPU_MSG_HANDLER(vaplic_ipi_handler, VPLIC_IPI_ID);

/**
 * @brief Update the CPU interrupt line.
 * 
 * @param vcpu 
 */
static void vaplic_update_hart_line(struct vcpu* vcpu) 
{
    int pcpu_id = vaplic_vcpuid_to_pcpuid(vcpu);
    /** If the current cpu is the targeting cpu, signal the intp to the hart*/
    /** Else, send a mensage to the targeting cpu */
    if(pcpu_id == cpu()->id) {
        int id = vaplic_emul_notifier(vcpu);
        if(id != 0){
            CSRS(CSR_HVIP, HIP_VSEIP);
        } else  {
            CSRC(CSR_HVIP, HIP_VSEIP);
        }
    } else {
        struct cpu_msg msg = {VPLIC_IPI_ID, UPDATE_HART_LINE};
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
    switch(event) {
        case UPDATE_HART_LINE:
            vaplic_update_hart_line(cpu()->vcpu);
            break;
    }
}

// ============================================================================
/** APLIC Functions emulation */

/**
 * @brief Write to domaincfg register a new value.
 * 
 * @param vcpu 
 * @param new_val The new value to write to domaincfg
 */
static void vaplic_set_domaincfg(struct vcpu *vcpu, uint32_t new_val){
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    /** Update only the virtual domaincfg */
    /** Only Interrupt Enable is configurable. */
    new_val &= APLIC_DOMAINCFG_IE;
    vxplic->domaincfg = new_val | APLIC_DOMAINCFG_RO80;
    spin_unlock(&vxplic->lock);

    vaplic_update_hart_line(vcpu);
}

/**
 * @brief Read from domaincfg
 * 
 * @param vcpu 
 * @return uint32_t domaincfg value 
 */
static uint32_t vaplic_get_domaincfg(struct vcpu *vcpu){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    ret = vxplic->domaincfg;
    return ret;
}

/**
 * @brief Read from a given interrupt sourcecfg register
 * 
 * @param vcpu 
 * @param intp_id Interrupt id to read
 * @return uint32_t 
 */
static uint32_t vaplic_get_sourcecfg(struct vcpu *vcpu, irqid_t intp_id){
    uint32_t real_int_id = intp_id - 1;
    uint32_t ret = 0;

    if(intp_id == 0)
        return ret;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (real_int_id < APLIC_MAX_INTERRUPTS) ret = vxplic->srccfg[real_int_id];
    return ret;
}

/**
 * @brief Write to sourcecfg register of a given interrupt
 * 
 * @param vcpu 
 * @param intp_id interrupt id to write to
 * @param new_val value to write to sourcecfg
 */
static void vaplic_set_sourcecfg(struct vcpu *vcpu, irqid_t intp_id, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    /** If intp is valid and new source config is different from prev. one.*/
    if (intp_id > 0 && intp_id < APLIC_MAX_INTERRUPTS && 
        vaplic_get_sourcecfg(vcpu, intp_id) != new_val) {
        /** If intp is being delegated make whole reg 0.
         *  This happens because this domain is always a leaf. */        
        new_val &= (new_val & APLIC_SRCCFG_D) ? 0 : APLIC_SRCCFG_SM;

        /** If SM is reserved make intp inactive */
        if(new_val == 2 || new_val == 3)
            new_val = APLIC_SOURCECFG_SM_INACTIVE;
        
        /** Only edge sense can be virtualized for know */
        if(new_val  == APLIC_SOURCECFG_SM_LEVEL_HIGH){
            new_val = APLIC_SOURCECFG_SM_EDGE_RISE;
        } else if (new_val  == APLIC_SOURCECFG_SM_LEVEL_LOW){
            new_val = APLIC_SOURCECFG_SM_EDGE_FALL;
        }

        /** Is this intp a phys. intp? */
        if(vaplic_get_hw(vcpu, intp_id)){
            /** Update in phys. aplic */
            aplic_set_sourcecfg(intp_id, new_val);
            /** If phys aplic was succe. written, then update virtual*/
            if(aplic_get_sourcecfg(intp_id) == new_val){
                vxplic->srccfg[intp_id-1] = new_val;
            }
        } else {
            /** If intp is not phys. update virtual only */
            vxplic->srccfg[intp_id-1] = new_val;
        }
        vaplic_update_hart_line(vcpu);
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Get the pending bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @return uint32_t value with pending bit mapped per bit
 */
static uint32_t vaplic_get_setip(struct vcpu *vcpu, uint8_t reg){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (reg < APLIC_NUM_SETIx_REGS) ret = vxplic->setip[reg];
    return ret;
}

/**
 * @brief Set the pending bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @param new_val value with pending bit mapped per bit
 */
static void vaplic_set_setip(struct vcpu *vcpu, uint8_t reg, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (reg == 0) new_val &= 0xFFFFFFFE;
    if (reg < APLIC_NUM_SETIx_REGS && 
        vaplic_get_setip(vcpu, reg) != new_val) {
        vxplic->setip[reg] = 0;
        for(int i = 0; i < APLIC_MAX_INTERRUPTS/APLIC_NUM_SETIx_REGS; i++){
            /** Is this intp a phys. intp? */
            if(vaplic_get_hw(vcpu,i)){
                /** Update in phys. aplic */
                if(get_bit_from_reg(vxplic->setip[reg], i) && ((new_val >> i) & 1)){
                    aplic_set_pend(i);
                    if(aplic_get_pend(i)){
                        vxplic->setip[reg] |= new_val & (1 << i);
                    }
                }
            } else {
                /** If intp is not phys. emul aplic behaviour */
                vxplic->setip[reg] |= new_val & (1 << i);
                vaplic_update_hart_line(vcpu);
            }
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Set the pending bits for a given interrupt
 * 
 * @param vcpu virtual cpu
 * @param new_val value w/ the interrupt source number
 */
static void vaplic_set_setipnum(struct vcpu *vcpu, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (new_val != 0 && new_val < APLIC_MAX_INTERRUPTS && 
        !get_bit_from_reg(vxplic->setip[new_val/32], new_val)) {
        set_bit_from_reg(&vxplic->setip[new_val/32], new_val%32);
        if(vaplic_get_hw(vcpu,new_val)){
            aplic_set_pend(new_val);
        } else {
            vaplic_update_hart_line(vcpu);
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Clear the pending bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu 
 * @param reg  regiter index
 * @param new_val value with intp to be cleared per bit
 */
static void vaplic_set_in_clrip(struct vcpu *vcpu, uint8_t reg, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (reg < APLIC_NUM_CLRIx_REGS && 
        vaplic_get_setip(vcpu, reg) != new_val) {
        if (reg == 0) new_val &= 0xFFFFFFFE;
        vxplic->setip[reg] &= ~new_val;
        for(int i = 0; i < APLIC_MAX_INTERRUPTS/APLIC_NUM_CLRIx_REGS; i++){
            if(vaplic_get_hw(vcpu,i)){
                if(!get_bit_from_reg(vxplic->setip[reg], i) && ((new_val >> i) & 1)){
                    aplic_set_clripnum(i);
                }
            } else {
                vaplic_update_hart_line(vcpu);
            }
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Get the rectified input values per source
 *        NOTE: Not implemented as stated! 
 *        TODO: return the pending bits?
 * 
 * @param vcpu virtual cpu 
 * @param reg regiter index
 * @return uint32_t value with rectified intp per bit
 */
static uint32_t vaplic_get_in_clrip(struct vcpu *vcpu, uint8_t reg){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (reg < APLIC_NUM_CLRIx_REGS) ret = vxplic->in_clrip[reg];
    return ret;
}

/**
 * @brief Clear the pending bits for a given interrupt
 * 
 * @param vcpu virtual cpu
 * @param new_val value w/ the interrupt source number
 */
static void vaplic_set_clripnum(struct vcpu *vcpu, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (new_val != 0 && new_val < APLIC_MAX_INTERRUPTS && 
        get_bit_from_reg(vxplic->setip[new_val/32], new_val)) {
        clr_bit_from_reg(&vxplic->setip[new_val/32], new_val%32);
        if(vaplic_get_hw(vcpu,new_val)){
            aplic_set_clripnum(new_val);
        } else {
            vaplic_update_hart_line(vcpu);
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Get the enabled bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @return uint32_t value with enabled bit mapped per bit
 */
static uint32_t vaplic_get_setie(struct vcpu *vcpu, uint32_t reg){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (reg < APLIC_NUM_SETIx_REGS) ret = vxplic->setie[reg];
    return ret;
}

/**
 * @brief Set the enabled bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu
 * @param reg regiter index
 * @param new_val value with enbaled bit mapped per bit
 */
static void vaplic_set_setie(struct vcpu *vcpu, uint8_t reg, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (reg < APLIC_NUM_SETIx_REGS && 
        vaplic_get_setie(vcpu, reg) != new_val) {
        /** Update virt setip array */
        if (reg == 0) new_val &= 0xFFFFFFFE;
        vxplic->setie[reg] = new_val;
        for(int i = 0; i < APLIC_MAX_INTERRUPTS/APLIC_NUM_SETIx_REGS; i++){
            /** Is this intp a phys. intp? */
            if(vaplic_get_hw(vcpu,i)){
                /** Update in phys. aplic */
                if(get_bit_from_reg(vxplic->setie[reg], i) && ((new_val >> i) & 1)){
                    aplic_set_ienum(i);
                }
            } else {
                /** If intp is not phys. emul aplic behaviour */
                vaplic_update_hart_line(vcpu);
            }
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Set the enabled bits for a given interrupt
 * 
 * @param vcpu virtual cpu
 * @param new_val value w/ the interrupt source number
 */
static void vaplic_set_setienum(struct vcpu *vcpu, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (new_val != 0 && new_val < APLIC_MAX_INTERRUPTS && 
        !get_bit_from_reg(vxplic->setie[new_val/32], new_val)) {
        set_bit_from_reg(&vxplic->setie[new_val/32], new_val%32);
        if(vaplic_get_hw(vcpu,new_val)){
            aplic_set_ienum(new_val);
        } else {
            vaplic_update_hart_line(vcpu);
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Clear the enabled bits for interrupts [32*reg:(32*reg)+31]
 * 
 * @param vcpu virtual cpu 
 * @param reg  regiter index
 * @param new_val value with intp to be cleared per bit
 */
static void vaplic_set_clrie(struct vcpu *vcpu, uint8_t reg, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (reg < APLIC_NUM_CLRIx_REGS && 
        vaplic_get_setie(vcpu, reg) != new_val) {
        if (reg == 0) new_val &= 0xFFFFFFFE;
        vxplic->setie[reg] &= ~new_val;
        for(int i = 0; i < APLIC_MAX_INTERRUPTS/APLIC_NUM_CLRIx_REGS; i++){
            if(vaplic_get_hw(vcpu,i)){
                if(!get_bit_from_reg(vxplic->setie[reg], i) && ((new_val >> i) & 1)){
                    aplic_set_clrienum(i);
                }
            } else {
                vaplic_update_hart_line(vcpu);
            }
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Clear the enabled bits for a given interrupt
 * 
 * @param vcpu virtual cpu
 * @param new_val value w/ the interrupt source number
 */
static void vaplic_set_clrienum(struct vcpu *vcpu, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (new_val != 0 && new_val < APLIC_MAX_INTERRUPTS && 
        get_bit_from_reg(vxplic->setie[new_val/32], new_val)) {
        clr_bit_from_reg(&vxplic->setie[new_val/32], new_val%32);
        if(vaplic_get_hw(vcpu,new_val)){
            aplic_set_clrienum(new_val);
        } else {
            vaplic_update_hart_line(vcpu);
        }
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Write to target register of a given interrupt
 * 
 * @param vcpu 
 * @param intp_id interrupt id to write to
 * @param new_val value to write to target
 */
static void vaplic_set_target(struct vcpu *vcpu, irqid_t intp_id, uint32_t new_val){
    struct virqc *vxplic = &vcpu->vm->arch.vxplic;
    uint32_t hart_index = (new_val >> APLIC_TARGET_HART_IDX_SHIFT) & APLIC_TARGET_HART_IDX_MASK;
    cpuid_t pcpu_id = vm_translate_to_pcpuid(vcpu->vm, hart_index);

    spin_lock(&vxplic->lock);
    if(pcpu_id == INVALID_CPUID){
        /** If the hart index is invalid, make it vcpu = 0 
         *  and read the new pcpu.
         *  Software should not write anything other than legal 
         *  values to such a field */
        pcpu_id = vm_translate_to_pcpuid(vcpu->vm, 0);
    }
    /** Write the physical CPU in hart index */
    new_val &= APLIC_TARGET_IPRIO_MASK;
    new_val |= (pcpu_id << APLIC_TARGET_HART_IDX_SHIFT);

    if (intp_id > 0  && intp_id < APLIC_MAX_INTERRUPTS && 
        vaplic_get_target(vcpu, intp_id) != new_val) {

        new_val &= APLIC_TARGET_MASK;
        /** If prio is 0, set to 1 (max)*/
        if ((new_val & APLIC_TARGET_IPRIO_MASK) == 0){
            new_val |= APLIC_TARGET_PRIO_DEFAULT;
        }
        
        if(vaplic_get_hw(vcpu, intp_id)){
            aplic_set_target(intp_id, new_val);
            if(impl_src[intp_id] == IMPLEMENTED && 
               aplic_get_target(intp_id) == new_val){
                vxplic->target[intp_id-1] = new_val;
            }
        } else {
            vxplic->target[intp_id-1] = new_val;
        }
        vaplic_update_hart_line(vcpu);
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Read from a given interrupt target register
 * 
 * @param vcpu 
 * @param intp_id Interrupt id to read
 * @return uint32_t value with target from intp_id
 */
static uint32_t vaplic_get_target(struct vcpu *vcpu, irqid_t intp_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    cpuid_t pcpu_id = 0;
    cpuid_t vcpu_id = 0;
    
    if(intp_id == 0){
        return ret;
    }
    
    if (intp_id > 0 && intp_id < APLIC_MAX_INTERRUPTS){
        /** Translate the physical cpu into the its virtual pair */
        pcpu_id = vxplic->target[intp_id -1] >> APLIC_TARGET_HART_IDX_SHIFT;
        vcpu_id = vm_translate_to_vcpuid(vcpu->vm, pcpu_id);
        ret = vxplic->target[intp_id -1] & APLIC_TARGET_IPRIO_MASK;
        ret |= (vcpu_id << APLIC_TARGET_HART_IDX_SHIFT);
    }
    return ret;
}

/** IDC Functions emulation */

/**
 * @brief Set idelivery register for a given idc. Only 0 and 1 are allowed.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in iforce
 */
static void vaplic_set_idelivery(struct vcpu *vcpu, uint16_t idc_id, uint32_t new_val){
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    new_val = (new_val & 0x1);
    if (idc_id < vxplic->idc_num){
        if (new_val) 
            bitmap_set(vxplic->idelivery, idc_id);
        else
            bitmap_clear(vxplic->idelivery, idc_id);
    }
    spin_unlock(&vxplic->lock);

    vaplic_update_hart_line(vcpu);
}

/**
 * @brief Read idelivery register from a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from idelivery
 */
static uint32_t vaplic_get_idelivery(struct vcpu *vcpu, uint16_t idc_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (idc_id < vxplic->idc_num) ret = bitmap_get( vxplic->idelivery, idc_id);
    return ret;
}

/**
 * @brief Set iforce register for a given idc. Only 0 and 1 are allowed.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in iforce
 */
static void vaplic_set_iforce(struct vcpu *vcpu, uint16_t idc_id, uint32_t new_val){
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    new_val = (new_val & 0x1);
    if (idc_id < vxplic->idc_num){
        if (new_val) 
            bitmap_set(vxplic->iforce, idc_id);
        else
            bitmap_clear(vxplic->iforce, idc_id);
    }
    spin_unlock(&vxplic->lock);

    vaplic_update_hart_line(vcpu);
}

/**
 * @brief Read idelivery register from a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from iforce
 */
static uint32_t vaplic_get_iforce(struct vcpu *vcpu, uint16_t idc_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (idc_id < vxplic->idc_num) ret = bitmap_get(vxplic->iforce, idc_id);
    return ret;
}

/**
 * @brief Set ithreshold register for a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @param new_val new value to write in ithreshold
 */
static void vaplic_set_ithreshold(struct vcpu *vcpu, uint16_t idc_id, uint32_t new_val){
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    if (idc_id < vxplic->idc_num){
        vxplic->ithreshold[idc_id] = new_val;
    }
    spin_unlock(&vxplic->lock);

    vaplic_update_hart_line(vcpu);
}

/**
 * @brief Read ithreshold register from a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from ithreshold
 */
static uint32_t vaplic_get_ithreshold(struct vcpu *vcpu, uint16_t idc_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (idc_id < vxplic->idc_num) ret = vxplic->ithreshold[idc_id];
    return ret;
}

/**
 * @brief Read topi register from a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from topi
 */
static uint32_t vaplic_get_topi(struct vcpu *vcpu, uint16_t idc_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (idc_id < vxplic->idc_num) ret = vxplic->topi_claimi[idc_id];
    return ret;
}

/**
 * @brief Read claimi register from a given idc.
 * 
 * @param vcpu virtual CPU
 * @param idc_id idc identifier
 * @return uint32_t value read from claimi
 */
static uint32_t vaplic_get_claimi(struct vcpu *vcpu, uint16_t idc_id){
    uint32_t ret = 0;
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    if (idc_id < vxplic->idc_num){
        ret = vxplic->topi_claimi[idc_id];
        /** Sepurious intp*/
        if (ret == 0){
            // Clear the virt iforce bit
            vxplic->iforce[idc_id] = 0;
            if(vaplic_get_hw(vcpu,(ret >> 16))){
                // Clear the physical iforce bit
                aplic_idc_set_iforce(idc_id, 0);
            }
        }
        // Clear the virt pending bit for te read intp
        clr_bit_from_reg(&vxplic->setip[(ret >> 16)/32], (ret >> 16)%32);
        if(vaplic_get_hw(vcpu,(ret >> 16))){
            // Clear the physical pending bit for te read intp
            aplic_idc_get_claimi(idc_id);
        }
        vaplic_update_hart_line(vcpu);
    }
    return ret;
}
// ============================================================================

// ============================================================================
/**
 * @brief register access emulation functions
 * 
 * @param acc access information
 * 
 * It determines whether it needs to call the write or read funcion
 * for the choosen register.
 */

static void vaplic_emul_domaincfg_access(struct emul_access *acc){
    if (acc->write) {
        vaplic_set_domaincfg(cpu()->vcpu, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_domaincfg(cpu()->vcpu));
    }
}

static void vaplic_emul_srccfg_access(struct emul_access *acc){
    int intp = (acc->addr & 0xFFF)/4;
    if (acc->write) {
        vaplic_set_sourcecfg(cpu()->vcpu, intp, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_sourcecfg(cpu()->vcpu, intp));
    }
}

static void vaplic_emul_setip_access(struct emul_access *acc){
    int reg = (acc->addr & 0xFF)/32;
    if (acc->write) {
        vaplic_set_setip(cpu()->vcpu, reg, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_setip(cpu()->vcpu, reg));
    }
}

static void vaplic_emul_setipnum_access(struct emul_access *acc){
    if (acc->write) {
        vaplic_set_setipnum(cpu()->vcpu, vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

static void vaplic_emul_in_clrip_access(struct emul_access *acc){
    int reg = (acc->addr & 0xFF)/32;
    if (acc->write) {
        vaplic_set_in_clrip(cpu()->vcpu, reg, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_in_clrip(cpu()->vcpu, reg));
    }
}

static void vaplic_emul_clripnum_access(struct emul_access *acc){
    if (acc->write) {
        vaplic_set_clripnum(cpu()->vcpu, vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

static void vaplic_emul_setie_access(struct emul_access *acc){
    int reg = (acc->addr & 0xFF)/32;
    if (acc->write) {
        vaplic_set_setie(cpu()->vcpu, reg, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_setie(cpu()->vcpu, reg));
    }
}

static void vaplic_emul_setienum_access(struct emul_access *acc){
    if (acc->write) {
        vaplic_set_setienum(cpu()->vcpu, vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

static void vaplic_emul_clrie_access(struct emul_access *acc){
    int reg = (acc->addr & 0xFF)/32;
    if (acc->write) {
        vaplic_set_clrie(cpu()->vcpu, reg, vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

static void vaplic_emul_clrienum_access(struct emul_access *acc){
    if (acc->write) {
        vaplic_set_clrienum(cpu()->vcpu, vcpu_readreg(cpu()->vcpu, acc->reg));
    }
}

static void vaplic_emul_target_access(struct emul_access *acc){
    int intp = (acc->addr & 0xFFF)/4;
    if (acc->write) {
        vaplic_set_target(cpu()->vcpu, intp, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_target(cpu()->vcpu, intp));
    }
}

static void vaplic_emul_idelivery_access(struct emul_access *acc){
    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;
    if (acc->write) {
        vaplic_set_idelivery(cpu()->vcpu, idc_id, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_idelivery(cpu()->vcpu, idc_id));
    }
}

static void vaplic_emul_iforce_access(struct emul_access *acc){
    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;
    if (acc->write) {
        vaplic_set_iforce(cpu()->vcpu, idc_id, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_iforce(cpu()->vcpu, idc_id));
    }
}

static void vaplic_emul_ithreshold_access(struct emul_access *acc){
    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;
    if (acc->write) {
        vaplic_set_ithreshold(cpu()->vcpu, idc_id, vcpu_readreg(cpu()->vcpu, acc->reg));
    } else {
        vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_ithreshold(cpu()->vcpu, idc_id));
    }
}

static void vaplic_emul_topi_access(struct emul_access *acc){
    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;

    if (acc->write) return;
    vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_topi(cpu()->vcpu, idc_id));
}

static void vaplic_emul_claimi_access(struct emul_access *acc){
    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;

    if (acc->write) return;
    vcpu_writereg(cpu()->vcpu, acc->reg, vaplic_get_claimi(cpu()->vcpu, idc_id));
}

// ============================================================================
void vaplic_inject(struct vcpu *vcpu, irqid_t intp_id)
{
    struct virqc * vxplic = &vcpu->vm->arch.vxplic;
    spin_lock(&vxplic->lock);
    
    /** Intp has a valid ID and the virtual interrupt is not pending*/
    if (intp_id > 0 && intp_id < APLIC_MAX_INTERRUPTS && !vaplic_get_pend(vcpu, intp_id)){
        if(vxplic->srccfg[intp_id-1] != APLIC_SOURCECFG_SM_INACTIVE &&
           vxplic->srccfg[intp_id-1] != APLIC_SOURCECFG_SM_DETACH){
            set_bit_from_reg(&vxplic->setip[intp_id/32], intp_id);
        }
        vaplic_update_hart_line(vcpu);
    }
    spin_unlock(&vxplic->lock);
}

/**
 * @brief Function to handle writes (or reads) to (from) domain structure.
 * 
 * @param acc emulated access
 * @return true if conclude without errors.
 * @return false if the access is not aligned.
 */
static bool vaplic_domain_emul_handler(struct emul_access *acc)
{
    // only allow aligned word accesses
    if (acc->width != 4 || acc->addr & 0x3) return false;

    switch (acc->addr & 0xffff) {
        case APLIC_DOMAIN_OFF:
            vaplic_emul_domaincfg_access(acc);
            break;
        case APLIC_SOURCECFG_OFF ... APLIC_SOURCECFG_OFF+((APLIC_MAX_INTERRUPTS-2)*4):
            vaplic_emul_srccfg_access(acc);
            break;
        // case APLIC_MMSIADDRCFG_OFF:
        //     vaplic_emul_mmsiaddrcfg_access(acc);
        //     break;
        // case APLIC_MMSIADDRCFGH_OFF:
        //     vaplic_emul_mmsiaddrcfgh_access(acc);
        //     break;
        // case APLIC_SMSIADDRCFG_OFF:
        //     vaplic_emul_smsiaddrcfg_access(acc);
        //     break;
        // case APLIC_SMSIADDRCFGH_OFF:
        //     vaplic_emul_smsiaddrcfgh_access(acc);
        //     break;
        case APLIC_SETIP_OFF ... APLIC_SETIP_OFF+((APLIC_NUM_SETIx_REGS-1)*4):
            vaplic_emul_setip_access(acc);
            break;
        case APLIC_SETIPNUM_OFF:
            vaplic_emul_setipnum_access(acc);
            break;
        case APLIC_IN_CLRIP_OFF ... APLIC_IN_CLRIP_OFF+((APLIC_NUM_CLRIx_REGS-1)*4):
            vaplic_emul_in_clrip_access(acc);
            break;
        case APLIC_CLRIPNUM_OFF:
            vaplic_emul_clripnum_access(acc);
            break;
        case APLIC_SETIE_OFF ... APLIC_SETIE_OFF+((APLIC_NUM_SETIx_REGS-1)*4):
            vaplic_emul_setie_access(acc);
            break;
        case APLIC_SETIENUM_OFF:
            vaplic_emul_setienum_access(acc);
            break;
        case APLIC_CLRIE_OFF ... APLIC_CLRIE_OFF+((APLIC_NUM_CLRIx_REGS-1)*4):
            vaplic_emul_clrie_access(acc);
            break;
        case APLIC_CLRIENUM_OFF:
            vaplic_emul_clrienum_access(acc);
            break;
        // case APLIC_SETIPNUM_LE_OFF:
        //     vaplic_emul_setipnum_le_access(acc);
        //     break;
        // case APLIC_SETIPNUM_BE_OFF:
        //     vaplic_emul_setipnum_be_access(acc);
        //     break;
        // case APLIC_GENMSI_OFF:
        //     vaplic_emul_genmsi_access(acc);
        //     break;
        case APLIC_TARGET_OFF ...APLIC_TARGET_OFF+((APLIC_MAX_INTERRUPTS-2)*4):
            vaplic_emul_target_access(acc);
            break;
        default:
            if(!acc->write) {
                vcpu_writereg(cpu()->vcpu, acc->reg, 0);
            }
            break;
    }

    return true;
}

/**
 * @brief Function to handle writes (or reads) to (from) IDC structure.
 * 
 * @param acc emulated access
 * @return true  if conclude without errors.
 * @return false if the access is not aligned.
 */
static bool vaplic_idc_emul_handler(struct emul_access *acc)
{
    // only allow aligned word accesses
    if (acc->width > 4 || acc->addr & 0x3) return false;

    int idc_id = ((acc->addr - APLIC_IDC_OFF) >> 5) & 0x3ff;
    if(!(idc_id < cpu()->vcpu->vm->arch.vxplic.idc_num)){
        if(!acc->write) {
            vcpu_writereg(cpu()->vcpu, acc->reg, 0);
        }
        return true;
    }
    uint32_t addr = acc->addr - platform.arch.plic_base + APLIC_IDC_OFF;
    addr = addr - (sizeof(idc[0]) * idc_id);
    switch (addr & 0x1F) {
        case APLIC_IDC_IDELIVERY_OFF:
            vaplic_emul_idelivery_access(acc);
            break;
        case APLIC_IDC_IFORCE_OFF:
            vaplic_emul_iforce_access(acc);
            break;
        case APLIC_IDC_ITHRESHOLD_OFF:
            vaplic_emul_ithreshold_access(acc);
            break;
        case APLIC_IDC_TOPI_OFF:
            vaplic_emul_topi_access(acc);
            break;
        case APLIC_IDC_CLAIMI_OFF:
            vaplic_emul_claimi_access(acc);
            break;
        default:
            if(!acc->write) {
                vcpu_writereg(cpu()->vcpu, acc->reg, 0);
            }
            break;
    }

    return true;
}

void vaplic_init(struct vm *vm, vaddr_t vaplic_base)
{
    if (cpu()->id == vm->master) {
        vm->arch.vxplic.aplic_domain_emul = (struct emul_mem) {
            .va_base = vaplic_base,
            .size = sizeof(struct aplic_global),
            .handler = vaplic_domain_emul_handler
        };

        vm_emul_add_mem(vm, &vm->arch.vxplic.aplic_domain_emul);

        vm->arch.vxplic.aplic_idc_emul = (struct emul_mem) {
            .va_base = vaplic_base + APLIC_IDC_OFF,
            .size = sizeof(struct aplic_idc)*APLIC_PLAT_IDC_NUM,
            .handler = vaplic_idc_emul_handler
        };

        vm_emul_add_mem(vm, &vm->arch.vxplic.aplic_idc_emul);

        /* 1 IDC per hart */
        vm->arch.vxplic.idc_num = vm->cpu_num;
    }
}