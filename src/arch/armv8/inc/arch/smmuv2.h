/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      David Cerdeira <davidmcerdeira@gmail.com>
 *      Jose Martins <jose.martins@bao-project.org>
 *      Angelo Ruocco <angeloruocco90@gmail.com>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __ARCH_SMMUV2_H__
#define __ARCH_SMMUV2_H__

#include <bao.h>
#include <arch/platform.h>
#include <vm.h>
#include <mem.h>

#define SMMUV2_CR0_GFRE     (0x1 << 1)
#define SMMUV2_CR0_GFIE     (0x1 << 2)
#define SMMUV2_CR0_GCFGFRE  (0x1 << 4)
#define SMMUV2_CR0_GCFGFIE  (0x1 << 5)
#define SMMUV2_CR0_USFCFG   (0x1 << 10)
#define SMMUV2_CR0_SMCFCFG  (0x1 << 21)
#define SMMUV2_CR0_CLIENTPD (0x1 << 0)

#define SMMUV2_CR0_CLEAR(cr0)     (cr0 & (0x3 << 30 | 0x1 << 11))

#define SMMUV2_IDR0_MASK         (0xFF)
#define SMMUV2_IDR0_S2TS_BIT     (0x1 << 30)
#define SMMUV2_IDR0_SMS_BIT      (0x1 << 27)
#define SMMUV2_IDR0_CTTW_BIT     (0x1 << 14)
#define SMMUV2_IDR0_BTM_BIT      (0x1 << 13)

#define SMMUV2_IDR1_PAGESIZE_BIT    (0x1 << 31)
#define SMMUV2_IDR1_NUMCB_OFF       (0)
#define SMMUV2_IDR1_NUMCB_LEN       (8)
#define SMMUV2_IDR1_NUMPAGEDXB_OFF  (28)
#define SMMUV2_IDR1_NUMPAGEDXB_LEN  (3)

#define SMMUV2_IDR2_PTFSv8_4kB_BIT (0x1 << 12)
#define SMMUV2_IDR2_OAS_OFF         (4)
#define SMMUV2_IDR2_OAS_LEN         (4)
#define SMMUV2_IDR2_IAS_OFF         (0)
#define SMMUV2_IDR2_IAS_LEN         (4)

#define SMMUV2_IDR7_MAJOR_OFF       (4)
#define SMMUV2_IDR7_MAJOR_LEN       (4)

#define SMMU_SMR_ID_OFF 0
#define SMMU_SMR_ID_LEN 15
#define SMMU_SMR_ID(smr) bit_extract(smr, SMMU_SMR_ID_OFF, SMMU_SMR_ID_LEN)

#define SMMU_ID_MSK BIT_MASK(0, SMMU_SMR_ID_LEN)

#define SMMU_SMR_MASK_OFF 16
#define SMMU_SMR_MASK_LEN 15
#define SMMU_SMR_MASK(smr) bit_extract(smr, SMMU_SMR_MASK_OFF, SMMU_SMR_MASK_LEN)

#define SMMUV2_SMR_VALID (0x1 << 31)

#define S2CR_IMPL_OFF         (30)
#define S2CR_IMPL_LEN         (2)
#define S2CR_IMPL_MASK        BIT_MASK(S2CR_IMPL_OFF, S2CR_IMPL_LEN)

#define S2CR_TRANSIENTCFG_OFF         (28)
#define S2CR_TRANSIENTCFG_LEN         (2)
#define S2CR_TRANSIENTCFG_MASK        BIT_MASK(S2CR_TRANSIENTCFG_OFF, S2CR_TRANSIENTCFG_LEN)
#define S2CR_TRANSIENTCFG_NON_TRANSIENT (0x2 << S2CR_TRANSIENTCFG_OFF)

#define S2CR_INSTCFG_OFF         (26)
#define S2CR_INSTCFG_LEN         (2)
#define S2CR_INSTCFG_MASK        BIT_MASK(S2CR_INSTCFG_OFF, S2CR_INSTCFG_LEN)
#define S2CR_INSTCFG_DATA_ONLY   (0x2 << S2CR_INSTCFG_OFF)

#define S2CR_PRIVCFG_OFF         (24)
#define S2CR_PRIVCFG_LEN         (2)
#define S2CR_PRIVCFG_MASK        BIT_MASK(S2CR_PRIVCFG_OFF, S2CR_PRIVCFG_LEN)

#define S2CR_WACFG_OFF         (22)
#define S2CR_WACFG_LEN         (2)
#define S2CR_WACFG_MASK        BIT_MASK(S2CR_WACFG_OFF, S2CR_WACFG_LEN)

#define S2CR_RACFG_OFF         (20)
#define S2CR_RACFG_LEN         (2)
#define S2CR_RACFG_MASK        BIT_MASK(S2CR_RACFG_OFF, S2CR_RACFG_LEN)

#define S2CR_NSCFG_OFF         (18)
#define S2CR_NSCFG_LEN         (2)
#define S2CR_NSCFG_MASK        BIT_MASK(S2CR_NSCFG_OFF, S2CR_NSCFG_LEN)

#define S2CR_TYPE_OFF         (16)
#define S2CR_TYPE_LEN         (2)
#define S2CR_TYPE_MASK        BIT_MASK(S2CR_TYPE_OFF, S2CR_TYPE_LEN)

#define S2CR_MemAttr_OFF         (12)
#define S2CR_MemAttr_LEN         (4)
#define S2CR_MemAttr_MASK        BIT_MASK(S2CR_MemAttr_OFF, S2CR_MemAttr_LEN)

#define S2CR_MTCFG_OFF         (11)
#define S2CR_MTCFG_LEN         (1)
#define S2CR_MTCFG_MASK        BIT_MASK(S2CR_MTCFG_OFF, S2CR_MTCFG_LEN)

#define S2CR_EXIDVALID_OFF         (10)
#define S2CR_EXIDVALID_LEN         (1)
#define S2CR_EXIDVALID_MASK        BIT_MASK(S2CR_EXIDVALID_OFF, S2CR_EXIDVALID_LEN)

#define S2CR_SHCFG_OFF          (8)
#define S2CR_SHCFG_LEN          (2)
#define S2CR_SHCFG_MASK         BIT_MASK(S2CR_SHCFG_OFF, S2CR_SHCFG_LEN)
#define S2CR_SHCFG_IN_SHR       (0x2 << S2CR_SHCFG_OFF)

#define S2CR_CBNDX_OFF          (0)
#define S2CR_CBNDX_LEN          (8)
#define S2CR_CBNDX_MASK         BIT_MASK(S2CR_CBNDX_OFF, S2CR_CBNDX_LEN)
#define S2CR_CBNDX(s2cr)        bit_extract(s2cr, S2CR_CBNDX_OFF, S2CR_CBNDX_LEN)

/* Don't clear implementation defined bits, clear everything else. */
#define S2CR_CLEAR(s2cr)    (s2cr & S2CR_IMPL_MASK)
#define S2CR_DFLT    (0)

typedef struct {
    uint32_t CR0;
    uint32_t SCR1;
    uint32_t CR2;
    uint8_t pad1[0x10 - 0x0c];
    uint32_t ACR;
    uint8_t pad2[0x20 - 0x14];
    uint32_t IDR0;
    uint32_t IDR1;
    uint32_t IDR2;
    uint32_t IDR3;
    uint32_t IDR4;
    uint32_t IDR5;
    uint32_t IDR6;
    uint32_t IDR7;
    uint64_t GFAR;
    uint32_t GFSR;
    uint32_t GFSRRESTORE;
    uint32_t GFSYNR0;
    uint32_t GFSYNR1;
    uint32_t GFSYNR2;
    uint8_t pad3[0x60 - 0x5c];
    uint32_t STLBIALL;
    uint32_t TLBIVMID;
    uint32_t TLBIALLNSNH;
    uint32_t TLBIALLH;
    uint32_t TLBGSYNC;
    uint32_t TLBGSTATUS;
    uint32_t TLBIVAH;
    uint32_t pad4;
    uint8_t impl1[0xa0 - 0x80];
    uint64_t STLBIVALM;
    uint64_t STLBIVAM;
    uint64_t TLBIVALH64;
    uint32_t TLBIVMIDS1;
    uint32_t STLBIALLM;
    uint64_t TLBIVAH64;
    uint8_t pad5[0x100 - 0xc8];
    uint64_t GATS1UR;
    uint64_t GATS1UW;
    uint64_t GATS1PR;
    uint64_t GATS1PW;
    uint64_t GATS12UR;
    uint64_t GATS12UW;
    uint64_t GATS12PR;
    uint64_t GATS12PW;
    uint8_t pad6[0x180 - 0x140];
    uint64_t GPAR;
    uint32_t GATSR;
    uint8_t pad20[0x400 - 0x18c];
    uint32_t NSCR0;
    uint32_t pad7;
    uint32_t NSCR2;
    uint32_t pad8;
    uint32_t NSACR;
    uint8_t pad9[0x420 - 0x414];
    uint8_t pad10[0x440 - 0x420];
    uint64_t NSGFAR;
    uint32_t NSGFSR;
    uint32_t NSGFSRRESTORE;
    uint32_t NSGFSYNR0;
    uint32_t NSGFSYNR1;
    uint32_t NSGFSYNR2;
    uint8_t pad11[0x470 - 0x45C];
    uint32_t NSTLBGSYNC;
    uint32_t NSTLBGSTATUS;
    uint8_t pad12[0x480 - 0x478];
    uint8_t impl2[0x4A0 - 0x480];
    uint8_t pad13[0x500 - 0x4A0];
    uint64_t NSGATS1UR;
    uint64_t NSGATS1UW;
    uint64_t NSGATS1PR;
    uint64_t NSGATS1PW;
    uint64_t NSGATS12UR;
    uint64_t NSGATS12UW;
    uint64_t NSGATS12PR;
    uint64_t NSGATS12PW;
    uint8_t pad14[0x580 - 0x540];
    uint64_t NSGPAR;
    uint32_t NSGATSR;
    uint8_t pad15[0x800 - 0x58C];
    uint32_t SMR[128];
    uint8_t pad16[0xC00 - 0xA00];
    uint32_t S2CR[128];
    uint8_t pad17[0xFD0 - 0xE00];
    uint8_t impl3[0x1000 - 0xFD0];

} __attribute__((__packed__, __aligned__(PAGE_SIZE))) smmu_glbl_rs0_t;
#define SMMUV2_CBAR_TYPE_S2             (0)
#define SMMUV2_CBAR_TYPE_S1_S2FAULT     (0x2 << 16)
#define SMMUV2_CBAR_VMID_MASK           (0xFF)
#define SMMUV2_CBAR_VMID(ID)            ((ID) & SMMUV2_CBAR_VMID_MASK)
#define SMMUV2_CBAR_VA64                (0x1 << 0)

#define SMMUV2_CB_TTBA_END     (48)
#define SMMUV2_CB_TTBA(x)      BIT_MASK(x, (SMMUV2_CB_TTBA_END - x))

#define S2CR_IMPL_OFF         (30)
#define S2CR_IMPL_LEN         (2)
#define S2CR_IMPL_MASK        BIT_MASK(S2CR_IMPL_OFF, S2CR_IMPL_LEN)

#define S2CR_INSTCFG_OFF         (26)
#define S2CR_INSTCFG_LEN         (2)
#define S2CR_INSTCFG_MASK        BIT_MASK(S2CR_INSTCFG_OFF, S2CR_INSTCFG_LEN)
#define S2CR_INSTCFG_DATA_ONLY   (0x2 << S2CR_INSTCFG_OFF)

#define S2CR_PRIVCFG_OFF         (24)
#define S2CR_PRIVCFG_LEN         (2)
#define S2CR_PRIVCFG_MASK        BIT_MASK(S2CR_PRIVCFG_OFF, S2CR_PRIVCFG_LEN)

#define S2CR_WACFG_OFF         (22)
#define S2CR_WACFG_LEN         (2)
#define S2CR_WACFG_MASK        BIT_MASK(S2CR_WACFG_OFF, S2CR_WACFG_LEN)

#define S2CR_RACFG_OFF         (20)
#define S2CR_RACFG_LEN         (2)
#define S2CR_RACFG_MASK        BIT_MASK(S2CR_RACFG_OFF, S2CR_RACFG_LEN)

#define S2CR_NSCFG_OFF         (18)
#define S2CR_NSCFG_LEN         (2)
#define S2CR_NSCFG_MASK        BIT_MASK(S2CR_NSCFG_OFF, S2CR_NSCFG_LEN)

#define S2CR_TYPE_OFF         (16)
#define S2CR_TYPE_LEN         (2)
#define S2CR_TYPE_MASK        BIT_MASK(S2CR_TYPE_OFF, S2CR_TYPE_LEN)

#define S2CR_MemAttr_OFF         (12)
#define S2CR_MemAttr_LEN         (4)
#define S2CR_MemAttr_MASK        BIT_MASK(S2CR_MemAttr_OFF, S2CR_MemAttr_LEN)

#define S2CR_MTCFG_OFF         (11)
#define S2CR_MTCFG_LEN         (1)
#define S2CR_MTCFG_MASK        BIT_MASK(S2CR_MTCFG_OFF, S2CR_MTCFG_LEN)

#define S2CR_EXIDVALID_OFF         (10)
#define S2CR_EXIDVALID_LEN         (1)
#define S2CR_EXIDVALID_MASK        BIT_MASK(S2CR_EXIDVALID_OFF, S2CR_EXIDVALID_LEN)

#define S2CR_SHCFG_OFF         (8)
#define S2CR_SHCFG_LEN         (2)
#define S2CR_SHCFG_MASK        BIT_MASK(S2CR_SHCFG_OFF, S2CR_SHCFG_LEN)
#define S2CR_SHCFG_IN_SHR      (0x2 << S2CR_SHCFG_OFF)

#define S2CR_CBNDX_OFF         (0)
#define S2CR_CBNDX_LEN         (8)
#define S2CR_CBNDX_MASK        BIT_MASK(S2CR_CBNDX_OFF, S2CR_CBNDX_LEN)


typedef struct {
    uint32_t CBAR[128];
    uint8_t res1[0x400 - 0x200];
    uint32_t CBFRSYNRA[128];
    uint8_t res2[0x800 - 0x600];
    uint32_t CBA2R[128];
    uint8_t res3[0x1000-0xa00];
} __attribute__((__packed__,__aligned__(PAGE_SIZE))) smmu_glbl_rs1_t;

#define SMMUV2_SCTLR_M          (0x1 << 0)
#define SMMUV2_SCTLR_TRE        (0x1 << 1)
#define SMMUV2_SCTLR_AFE        (0x1 << 2)
#define SMMUV2_SCTLR_AFFD       (0x1 << 3)
#define SMMUV2_SCTLR_E          (0x1 << 4)
#define SMMUV2_SCTLR_CFRE       (0x1 << 5)
#define SMMUV2_SCTLR_CFIE       (0x1 << 6)
#define SMMUV2_SCTLR_CFCFG      (0x1 << 7)
#define SMMUV2_SCTLR_HUPCF      (0x1 << 8)
#define SMMUV2_SCTLR_PTW        (0x1 << 13)
#define SMMUV2_SCTLR_BSU_NO     (0x0 << 14)
#define SMMUV2_SCTLR_BSU_ISH    (0x1 << 14)
#define SMMUV2_SCTLR_BSU_OSH    (0x2 << 14)
#define SMMUV2_SCTLR_BSU_SYS    (0x3 << 14)

#define SMMUV2_SCTLR_CLEAR(sctlr) \
    (sctlr & (0xF << 28 | 0x1 << 20 | 0xF << 9 | 0x1 << 11))

#define SMMUV2_SCTLR_DEFAULT (SMMUV2_SCTLR_CFCFG | SMMUV2_SCTLR_M)

#define SMMUV2_TCR_T0SZ_MSK         (0x1F)
#define SMMUV2_TCR_T0SZ(SZ)         ((SZ) & SMMUV2_TCR_T0SZ_MSK)
#define SMMUV2_TCR_SL0_OFF          (6)
#define SMMUV2_TCR_SL0_MSK          (0x3 << SMMUV2_TCR_SL0_OFF)
#define SMMUV2_TCR_SL0_0            ((0x2 << SMMUV2_TCR_SL0_OFF) & SMMUV2_TCR_SL0_MSK)
#define SMMUV2_TCR_SL0_1            ((0x1 << SMMUV2_TCR_SL0_OFF) & SMMUV2_TCR_SL0_MSK)
#define SMMUV2_TCR_SL0_2            (0)
#define SMMUV2_TCR_IRGN0_OFF        (8)
#define SMMUV2_TCR_IRGN0_MSK        (0x3 << SMMUV2_TCR_IRGN0_OFF)
#define SMMUV2_TCR_IRGN0_NC         (0x0 << SMMUV2_TCR_IRGN0_OFF)
#define SMMUV2_TCR_IRGN0_WB_RA_WA   (0x1 << SMMUV2_TCR_IRGN0_OFF)
#define SMMUV2_TCR_IRGN0_WT_RA_NWA  (0x2 << SMMUV2_TCR_IRGN0_OFF)
#define SMMUV2_TCR_IRGN0_WB_RA_NWA  (0x3 << SMMUV2_TCR_IRGN0_OFF)
#define SMMUV2_TCR_ORGN0_OFF        (10)
#define SMMUV2_TCR_ORGN0_MSK        (0x3 << SMMUV2_TCR_ORGN0_OFF)
#define SMMUV2_TCR_ORGN0_NC         (0x0 << SMMUV2_TCR_ORGN0_OFF)
#define SMMUV2_TCR_ORGN0_WB_RA_WA   (0x1 << SMMUV2_TCR_ORGN0_OFF)
#define SMMUV2_TCR_ORGN0_WT_RA_NWA  (0x2 << SMMUV2_TCR_ORGN0_OFF)
#define SMMUV2_TCR_ORGN0_WB_RA_NWA  (0x3 << SMMUV2_TCR_ORGN0_OFF)
#define SMMUV2_TCR_SH0_OFF          (12)
#define SMMUV2_TCR_SH0_MSK          (0x3 << SMMUV2_TCR_SH0_OFF)
#define SMMUV2_TCR_SH0_NS           (0x0 << SMMUV2_TCR_SH0_OFF)
#define SMMUV2_TCR_SH0_OS           (0x2 << SMMUV2_TCR_SH0_OFF)
#define SMMUV2_TCR_SH0_IS           (0x3 << SMMUV2_TCR_SH0_OFF)
#define SMMUV2_TCR_TG0_OFF          (14)
#define SMMUV2_TCR_TG0_MSK          (0x3 << SMMUV2_TCR_TG0_OFF)
#define SMMUV2_TCR_TG0_4K           (0x0 << SMMUV2_TCR_TG0_OFF)
#define SMMUV2_TCR_TG0_16K          (0x2 << SMMUV2_TCR_TG0_OFF)
#define SMMUV2_TCR_TG0_64K          (0x1 << SMMUV2_TCR_TG0_OFF)
#define SMMUV2_TCR_PS_OFF           (16)
#define SMMUV2_TCR_PS_MSK           (0x7 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_32B           (0x0 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_36B           (0x1 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_40B           (0x2 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_42B           (0x3 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_44B           (0x4 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_48B           (0x5 << SMMUV2_TCR_PS_OFF)
#define SMMUV2_TCR_PS_52B           (0x6 << SMMUV2_TCR_PS_OFF)

typedef struct {
    uint32_t SCTLR;
    uint32_t ACTLR;
    uint32_t RESUME;
    uint8_t res1[0x20 - 0xc];
    uint64_t TTBR0;
    uint8_t res2[0x30 - 0x28];
    uint32_t TCR;
    uint8_t res3[0x58 - 0x34];
    uint32_t FSR;
    uint32_t FSRRESTORE;
    uint64_t FAR;
    uint32_t FSYNR0;
    uint32_t FSYNR1;
    uint64_t IPAFAR;
    uint8_t res4[0x630 - 0x78];
    uint64_t TLBIIPAS2;
    uint64_t TLBIIPAS2L;
    uint8_t res5[0x7f0 - 0x640];
    uint32_t TLBSYNC;
    uint32_t TLBSTATUS;
    uint8_t res6[0xe00 - 0x7f8];
    uint32_t PMEVCNTRm;
    uint8_t res7[0xe80 - 0xe3c];
    uint32_t PMEVTYPERm;
    uint8_t res8[0xf00 - 0xebc];
    uint32_t PMCFGR;
    uint32_t PMCR;
    uint8_t res9[0xf20 - 0xf08];
    uint32_t PMCEID0;
    uint32_t PMCEID1;
    uint8_t res10[0xf40 - 0xf28];
    uint32_t PMCNTENSET;
    uint32_t PMCNTENCLR;
    uint32_t PMINTENSET;
    uint32_t PMINTENCLR;
    uint32_t PMOVSCLR;
    uint8_t res11[0xf58 - 0xf54];
    uint32_t PMOVSSET;
    uint8_t res12[0xfb8 - 0xf5c];
    uint32_t PMAUTHSTATUS;
    uint8_t res13[];
} __attribute__((__packed__, __aligned__(PAGE_SIZE))) smmu_cntxt_t;

void smmu_init();

int smmu_alloc_ctxbnk();
int smmu_alloc_sme();
void smmu_write_ctxbnk(int32_t ctx_id, void *root_pt, uint32_t vm_id);
void smmu_write_sme(uint32_t sme, uint16_t mask, uint16_t id, bool group);
void smmu_write_s2c(uint32_t sme, int32_t ctx_id);
uint32_t smmu_sme_get_ctx(uint32_t sme);
uint16_t smmu_sme_get_id(uint32_t sme);
uint16_t smmu_sme_get_mask(uint32_t sme);
bool smmu_sme_is_group(uint32_t sme);
bool smmu_compatible_sme_exists(uint16_t mask, uint16_t id, uint32_t ctx,
                                bool group);

#endif
