/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef _APLIC_H_
#define _APLIC_H_

#include <bao.h>
#include <platform.h>

#define APLIC_PLAT_IDC_NUM (PLAT_CPU_NUM)

/**==== APLIC Specific types ====*/
typedef unsigned idcid_t;
typedef unsigned irqid_t;

/**==== APLIC Addresses defines ====*/
#define APLIC_IDC_OFF                   (0x4000)
#define APLIC_IDC_SIZE                  (32)

#define APLIC_MAX_INTERRUPTS            (1024)
#define APLIC_NUM_SRCCFG_REGS           (APLIC_MAX_INTERRUPTS - 1)
#define APLIC_NUM_TARGET_REGS           (APLIC_MAX_INTERRUPTS - 1)
/** where x = E or P*/
#define APLIC_NUM_CLRIx_REGS            (APLIC_MAX_INTERRUPTS / 32)
#define APLIC_NUM_SETIx_REGS            (APLIC_MAX_INTERRUPTS / 32)

/**==== Source Mode defines ====*/
#define APLIC_SOURCECFG_SM_MASK         0x00000007
#define APLIC_SOURCECFG_SM_INACTIVE     0x0
#define APLIC_SOURCECFG_SM_DETACH       0x1
#define APLIC_SOURCECFG_SM_EDGE_RISE    0x4
#define APLIC_SOURCECFG_SM_EDGE_FALL    0x5
#define APLIC_SOURCECFG_SM_LEVEL_HIGH   0x6
#define APLIC_SOURCECFG_SM_LEVEL_LOW    0x7
#define APLIC_SOURCECFG_SM_DEFAULT      APLIC_SOURCECFG_SM_DETACH

/** Sources State*/
#define IMPLEMENTED                     (1)
#define NOT_IMPLEMENTED                 (0)

/**==== APLIC Offsets ====*/
#define APLIC_DOMAIN_OFF                (0x0000)
#define APLIC_SOURCECFG_OFF             (0x0004)
#define APLIC_MMSIADDRCFG_OFF           (0x1BC0)
#define APLIC_MMSIADDRCFGH_OFF          (0x1BC4)
#define APLIC_SMSIADDRCFG_OFF           (0x1BC8)
#define APLIC_SMSIADDRCFGH_OFF          (0x1BCC)
#define APLIC_SETIP_OFF                 (0x1C00)
#define APLIC_SETIPNUM_OFF              (0x1CDC)
#define APLIC_IN_CLRIP_OFF              (0x1D00)
#define APLIC_CLRIPNUM_OFF              (0x1DDC)
#define APLIC_SETIE_OFF                 (0x1E00)
#define APLIC_SETIENUM_OFF              (0x1EDC)
#define APLIC_CLRIE_OFF                 (0x1F00)
#define APLIC_CLRIENUM_OFF              (0x1FDC)
#define APLIC_SETIPNUM_LE_OFF           (0x2000)
#define APLIC_SETIPNUM_BE_OFF           (0x2004)
#define APLIC_GENMSI_OFF                (0x3000)
#define APLIC_TARGET_OFF                (0x3004)

/**==== IDC Offsets ====*/
#define APLIC_IDC_IDELIVERY_OFF         (0x00)
#define APLIC_IDC_IFORCE_OFF            (0x04)
#define APLIC_IDC_ITHRESHOLD_OFF        (0x08)
#define APLIC_IDC_TOPI_OFF              (0x18)
#define APLIC_IDC_CLAIMI_OFF            (0x1C)

/**==== APLIC fields and masks defines ====*/
#define APLIC_DOMAINCFG_DM              (1U << 2)
#define APLIC_DOMAINCFG_IE              (1U << 8)
#define APLIC_DOMAINCFG_RO80            (0x80 << 24)

#define APLIC_SRCCFG_D                  (1U << 10)
#define APLIC_SRCCFG_SM                 ((1U << 0) | (1U << 1) | (1U << 2))

#define APLIC_TARGET_HART_IDX_SHIFT     (18)
#define APLIC_TARGET_HART_IDX_MASK      (0x3FFF)
#define APLIC_TARGET_IPRIO_MASK         (0xFF)
#define APLIC_TARGET_PRIO_DEFAULT       (1)
#define APLIC_TARGET_MASK               (0xFFFC00FF)
/**==== Data structures for APLIC devices ====*/
struct aplic_global {
    uint32_t domaincfg;
    uint32_t sourcecfg[APLIC_NUM_SRCCFG_REGS];
    uint8_t  reserved1[0x1C00 - 0x1000];
    uint32_t setip[APLIC_NUM_SETIx_REGS];
    uint8_t  reserved2[0x1CDC - 0x1C80];
    uint32_t setipnum;
    uint8_t  reserved3[0x1D00 - 0x1CE0];
    uint32_t in_clrip[APLIC_NUM_CLRIx_REGS];
    uint8_t  reserved4[0x1DDC - 0x1D80];
    uint32_t clripnum;
    uint8_t  reserved5[0x1E00 - 0x1DE0];
    uint32_t setie[APLIC_NUM_SETIx_REGS];
    uint8_t  reserved6[0x1EDC - 0x1E80];
    uint32_t setienum;
    uint8_t  reserved7[0x1F00 - 0x1EE0];
    uint32_t clrie[APLIC_NUM_CLRIx_REGS];
    uint8_t  reserved8[0x1FDC - 0x1F80];
    uint32_t clrienum;
    uint8_t  reserved9[0x2000 - 0x1FE0];
    uint32_t setipnum_le;
    uint32_t setipnum_be;
    uint8_t reserved10[0x3000 - 0x2008];
    uint32_t genmsi;
    uint32_t target[APLIC_NUM_TARGET_REGS];
} __attribute__((__packed__, aligned(PAGE_SIZE)));

struct aplic_idc {
    uint32_t idelivery;
    uint32_t iforce;
    uint32_t ithreshold;
    uint8_t  reserved[0x18-0x0C];
    uint32_t topi;
    uint32_t claimi;
}__attribute__((__packed__, aligned(APLIC_IDC_SIZE))); // IDC structure CANNOT be page aligned.

extern uint32_t impl_src[APLIC_MAX_INTERRUPTS];

extern volatile struct aplic_global *aplic_domain;
extern volatile struct aplic_idc *idc;

/**==== Initialization Functions ====*/
/**
 * @brief Initialize the aplic domain.
 * 
 */
void aplic_init(void);

/**
 * @brief Initialize the aplic IDCs. 
 * The IDC component is the closest to the cpu.
 * 
 */
void aplic_idc_init(void);

/**==== Domain functions ====*/
/**
 * @brief Write to aplic's sourcecfg register
 * 
 * @param int_id interruption ID identifies the interrupt to be configured/read.
 * @param val Value to be written into sourcecfg
 */
void aplic_set_sourcecfg(irqid_t int_id, uint32_t val);

/**
 * @brief Read from aplic's sourcecfg register
 * 
 * @param int_id interruption ID identifies the interrupt to be configured/read.
 * @return uint32_t 32 bit value containing interrupt int_id's configuration.
 */
uint32_t aplic_get_sourcecfg(irqid_t int_id);

/**
 * @brief Set a given interrupt as pending, using setipnum register.
 * This should be faster than aplic_set_pend.
 * 
 * @param int_id Interrupt to be set as pending
 */
void aplic_set_pend(irqid_t int_id);

/**
 * @brief Read the pending value of a given interrut
 * 
 * @param int_id interrupt to read from
 * @return true if interrupt is pended
 * @return false if interrupt is NOT pended
 */
bool aplic_get_pend(irqid_t int_id);

/**
 * @brief Clear a pending bit from a inetrrupt writting to in_clripnum.
 * Should be faster than aplic_set_inclrip.
 *  
 * @param int_id interrupt to clear the pending bit from
 */
void aplic_set_clripnum(irqid_t intp_id);

/**
 * @brief Read the current rectified value for a given interrupt
 * 
 * @param int_id interrupt to read from
 * @return true 
 * @return false 
 */
bool aplic_get_inclrip(irqid_t int_id);

/**
 * @brief Enable a given interrupt writting to setienum register
 * Should be faster than aplic_set_ie 
 * 
 * @param int_id Interrupt to be enabled
 */
void aplic_set_ienum(irqid_t int_id);

/**
 * @brief Clear enable bit be writting to clrie register of a given interrupt. 
 * It should be faster than aplic_set_clrie 
 * 
 * @param int_id Interrupt to clear the enable bit
 */
void aplic_set_clrienum(irqid_t int_id);

/**
 * @brief Write to register target (see AIA spec 0.3.2 section 4.5.16)
 * 
 * @param int_id Interrupt to configure the target options
 * @param val Value to be written in target register
 * 
 * If domaincfg.DM = 0, target have the format:
 * 
 * +-----------+------------+----------------------------------------+
 * | Bit-Field |    Name    |              Description               |
 * +-----------+------------+----------------------------------------+
 * | 31:28     | Hart Index | Hart to which interrupts will delivery |
 * | 7:0       | IPRIO      | Interrupt priority.                    |
 * +-----------+------------+----------------------------------------+
 * 
 * 
 * If domaincfg.DM = 1, target have the format:
 * 
 * +-----------+-------------+------------------------------------------------+
 * | Bit-Field |    Name     |                  Description                   |
 * +-----------+-------------+------------------------------------------------+
 * | 31:28     | Hart Index  | Hart to which interrupts will delivery         |
 * | 17:12     | Guest Index | Only if hypervisor extension were implemented. |
 * | 10:0      | EIID        | External Interrupt Identity. Specifies the data|
 * |           |             | value for MSIs                                 |
 * +-----------+-------------+------------------------------------------------+
 */
void aplic_set_target(irqid_t int_id, uint32_t val);

/**
 * @brief Read the target configurations for a given interrupt
 * 
 * @param int_id Interrupt to read from
 * @return uint32_t value with the requested data
 */
uint32_t aplic_get_target(irqid_t int_id);

/**==== IDC functions ====*/
/**
 * @brief Useful for testing. Seting this register forces an interrupt to
 * be asserted to the corresponding hart
 * 
 * @param idc_id IDC to force an interruption
 * @param en value to be written
 */
void aplic_idc_set_iforce(idcid_t idc_id, bool en);

/**
 * @brief As the same value as topi. However, reading claimi has the side effect
 * of clearing the pending bit for the reported inetrrupt identity.
 * 
 * @param idc_id IDC to read and clear the pending-bit the highest-priority
 * @return uint32_t returns the interrupt identity and interrupt priority.
 */
uint32_t aplic_idc_get_claimi(idcid_t idc_id);

/**==== APLIC Interrupt handler ====*/
/**
 * @brief Handles an incomming interrupt in irq controller.
 * 
 */
void aplic_handle(void);

#endif //_APLIC_H_