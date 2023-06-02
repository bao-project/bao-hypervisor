/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __RISCV_IOMMU_H__
#define __RISCV_IOMMU_H__

#include <bao.h>
#include <arch/platform.h>
#include <vm.h>
#include <mem.h>

// We initially use a 1-LVL DDT with DC in extended format
// N entries = 4kiB / 64 B p/ entry = 64 Entries
#define DDT_N_ENTRIES (64)

#define FQ_N_ENTRIES  (64)
#define FQ_LOG2SZ_1   (5ULL)
#define FQ_INDEX_MASK BIT32_MASK(0, FQ_LOG2SZ_1 + 1)

//# Memory-mapped Register Interface
// Capabilities register fields
#define RV_IOMMU_CAPS_VERSION_OFF    (0)
#define RV_IOMMU_CAPS_VERSION_LEN    (8)

#define RV_IOMMU_CAPS_SV39X4_BIT     (0x1ULL << 17)
#define RV_IOMMU_CAPS_MSI_FLAT_BIT   (0x1ULL << 22)
#define RV_IOMMU_CAPS_IGS_OFF        (28)
#define RV_IOMMU_CAPS_IGS_LEN        (2)

// Features control register fields
#define RV_IOMMU_FCTL_WSI_BIT        (0x1UL << 1)
#define RV_IOMMU_FCTL_DEFAULT        (RV_IOMMU_FCTL_WSI_BIT)

// Device Directory Table Pointer register
#define RV_IOMMU_DDTP_MODE_OFF       (0ULL)
#define RV_IOMMU_DDTP_MODE_BARE      (1ULL)
#define RV_IOMMU_DDTP_MODE_1LVL      (2ULL)
#define RV_IOMMU_DDTP_MODE_2LVL      (3ULL)
#define RV_IOMMU_DDTP_MODE_3LVL      (4ULL)

#define RV_IOMMU_DDTP_BUSY_BIT       (0x1ULL << 4)

#define RV_IOMMU_DDTP_PPN_OFF        (10)
#define RV_IOMMU_DDTP_PPN_LEN        (44)
#define RV_IOMMU_DDTP_PPN_MASK       BIT64_MASK(RV_IOMMU_DDTP_PPN_OFF, RV_IOMMU_DDTP_PPN_LEN)

// Queue management
#define RV_IOMMU_XQB_PPN_OFF         (10)
#define RV_IOMMU_XQB_PPN_LEN         (44)
#define RV_IOMMU_XQB_PPN_MASK        BIT64_MASK(RV_IOMMU_XQB_PPN_OFF, RV_IOMMU_XQB_PPN_LEN)

#define RV_IOMMU_XQCSR_EN_BIT        (1ULL << 0)
#define RV_IOMMU_XQCSR_IE_BIT        (1ULL << 1)
#define RV_IOMMU_XQCSR_MF_BIT        (1ULL << 8)
#define RV_IOMMU_XQCSR_ON_BIT        (1ULL << 16)
#define RV_IOMMU_XQCSR_BUSY_BIT      (1ULL << 17)

// FQ CSR
#define RV_IOMMU_FQCSR_OF_BIT        (1ULL << 9)
#define RV_IOMMU_FQCSR_DEFAULT       (RV_IOMMU_XQCSR_EN_BIT | \
                                         RV_IOMMU_XQCSR_IE_BIT | \
                                         RV_IOMMU_XQCSR_MF_BIT | \
                                         RV_IOMMU_FQCSR_OF_BIT)
#define RV_IOMMU_FQCSR_CLEAR_ERR     (RV_IOMMU_XQCSR_MF_BIT | RV_IOMMU_FQCSR_OF_BIT)

// Interrupt pending register
#define RV_IOMMU_IPSR_FIP_BIT        (1UL << 1)
#define RV_IOMMU_IPSR_CLEAR          (0x0FUL)

// Interrupt Vectors
#define RV_IOMMU_ICVEC_CIV_NUM       (0ULL)
#define RV_IOMMU_ICVEC_FIV_NUM       (1ULL)

#define RV_IOMMU_ICVEC_CIV_OFF       (0)
#define RV_IOMMU_ICVEC_FIV_OFF       (4)

#define RV_IOMMU_ICVEC_CIV           (RV_IOMMU_ICVEC_CIV_NUM << RV_IOMMU_ICVEC_CIV_OFF)
#define RV_IOMMU_ICVEC_FIV           (RV_IOMMU_ICVEC_FIV_NUM << RV_IOMMU_ICVEC_FIV_OFF)
#define RV_IOMMU_ICVEC_DEFAULT       (RV_IOMMU_ICVEC_CIV | RV_IOMMU_ICVEC_FIV)

// MSI Configuration Table entry
struct msi_cfg_tbl_entry {
    uint64_t addr;
    uint32_t data;
    uint32_t vctl;
} __attribute__((__packed__));

//# RISC-V IOMMU Memory-Mapped Register Interface
struct riscv_iommu_regmap {
    uint64_t caps;
    uint32_t fctl;
    uint8_t  __custom1[4];
    uint64_t ddtp;
    uint64_t cqb;
    uint32_t cqh;
    uint32_t cqt;
    uint64_t fqb;
    uint32_t fqh;
    uint32_t fqt;
    uint64_t pqb;
    uint32_t pqh;
    uint32_t pqt;
    uint32_t cqcsr;
    uint32_t fqcsr;
    uint32_t pqcsr;
    uint32_t ipsr;
    uint32_t iocntovf;
    uint32_t iocntinh;
    uint64_t iohpmcycles;
    uint64_t iohpmctr[31];
    uint64_t iohpmevt[31];
    uint64_t tr_req_iova;
    uint64_t tr_req_ctl;
    uint64_t tr_response;
    uint8_t  __rsv1[64];
    uint8_t  __custom2[72];
    uint64_t icvec;
    struct msi_cfg_tbl_entry msi_tbl[16];
    uint8_t  __rsv2[3072];

} __attribute__((__packed__, __aligned__(PAGE_SIZE)));

//# RISC-V IOMMU Device Directory Table
#define RV_IOMMU_DC_VALID_BIT   (1ULL << 0)
#define RV_IOMMU_DC_DTF_BIT     (1ULL << 4)

#define RV_IOMMU_DC_IOHGATP_PPN_OFF     (0)
#define RV_IOMMU_DC_IOHGATP_PPN_LEN     (44)
#define RV_IOMMU_DC_IOHGATP_PPN_MASK    BIT64_MASK(RV_IOMMU_DC_IOHGATP_PPN_OFF, RV_IOMMU_DC_IOHGATP_PPN_LEN)
#define RV_IOMMU_DC_IOHGATP_GSCID_OFF   (44)
#define RV_IOMMU_DC_IOHGATP_GSCID_LEN   (16)
#define RV_IOMMU_DC_IOHGATP_GSCID_MASK  BIT64_MASK(RV_IOMMU_DC_IOHGATP_GSCID_OFF, RV_IOMMU_DC_IOHGATP_GSCID_LEN)
#define RV_IOMMU_DC_IOHGATP_MODE_OFF    (60)
#define RV_IOMMU_DC_IOHGATP_MODE_LEN    (4)
#define RV_IOMMU_DC_IOHGATP_MODE_MASK   BIT64_MASK(RV_IOMMU_DC_IOHGATP_MODE_OFF, RV_IOMMU_DC_IOHGATP_MODE_LEN)
#define RV_IOMMU_IOHGATP_SV39X4         (8ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)
#define RV_IOMMU_IOHGATP_BARE           (0ULL << RV_IOMMU_DC_IOHGATP_MODE_OFF)

#define RV_IOMMU_DC_IOHGATP_PSCID_OFF   (12)
#define RV_IOMMU_DC_IOHGATP_PSCID_LEN   (20)
#define RV_IOMMU_DC_IOHGATP_PSCID_MASK  BIT64_MASK(RV_IOMMU_DC_IOHGATP_PSCID_OFF, RV_IOMMU_DC_IOHGATP_PSCID_LEN)

#define RV_IOMMU_DC_FSC_PPN_OFF         (0)
#define RV_IOMMU_DC_FSC_PPN_LEN         (44)
#define RV_IOMMU_DC_FSC_PPN_MASK        BIT64_MASK(RV_IOMMU_DC_FSC_PPN_OFF, RV_IOMMU_DC_FSC_PPN_LEN)
#define RV_IOMMU_DC_FSC_MODE_OFF        (60)
#define RV_IOMMU_DC_FSC_MODE_LEN        (4)
#define RV_IOMMU_DC_FSC_MODE_MASK       BIT64_MASK(RV_IOMMU_DC_FSC_MODE_OFF, RV_IOMMU_DC_FSC_MODE_LEN)

#define RV_IOMMU_DC_MSIPTP_PPN_OFF      (0)
#define RV_IOMMU_DC_MSIPTP_PPN_LEN      (44)
#define RV_IOMMU_DC_MSIPTP_PPN_MASK     BIT64_MASK(RV_IOMMU_DC_MSIPTP_PPN_OFF, RV_IOMMU_DC_MSIPTP_PPN_LEN)
#define RV_IOMMU_DC_MSIPTP_MODE_OFF     (60)
#define RV_IOMMU_DC_MSIPTP_MODE_LEN     (4)
#define RV_IOMMU_DC_MSIPTP_MODE_MASK    BIT64_MASK(RV_IOMMU_DC_MSIPTP_MODE_OFF, RV_IOMMU_DC_MSIPTP_MODE_LEN)

#define RV_IOMMU_DC_MSIMASK_OFF         (0)
#define RV_IOMMU_DC_MSIMASK_LEN         (52)
#define RV_IOMMU_DC_MSIMASK_MASK        BIT64_MASK(RV_IOMMU_DC_MSIMASK_OFF, RV_IOMMU_DC_MSIMASK_LEN)

struct ddt_entry {
    uint64_t tc;
    uint64_t iohgatp;
    uint64_t ta;
    uint64_t fsc;
    uint64_t msiptp;
    uint64_t msi_addr_mask;
    uint64_t msi_addr_pattern;
    uint64_t __rsv;
} __attribute__((__packed__));


//# Fault Queue Record
#define RV_IOMMU_FQ_CAUSE_OFF    (0)
#define RV_IOMMU_FQ_CAUSE_LEN    (12)
#define RV_IOMMU_FQ_PID_OFF      (12)
#define RV_IOMMU_FQ_PID_LEN      (20)
#define RV_IOMMU_FQ_TTYP_OFF     (34)
#define RV_IOMMU_FQ_TTYP_LEN     (6)
#define RV_IOMMU_FQ_DID_OFF      (40)
#define RV_IOMMU_FQ_DID_LEN      (24)

struct fq_entry {
    uint64_t tags;
    uint64_t __rsv;
    uint64_t iotval;
    uint64_t iotval2;
} __attribute__((__packed__));

void rv_iommu_init(void);
bool rv_iommu_alloc_did(deviceid_t dev_id);
void rv_iommu_write_ddt(deviceid_t dev_id, struct vm *vm, paddr_t root_pt);

#endif /* __RISCV_IOMMU_H__ */
