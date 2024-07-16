/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/*
    ? Questions:
    -   Target platform to determine microarchitectural-dependent details
    -   Ask whether Bao supports MSI interrupts. The SMMUv3 generates MSIs in a standardized manner.
        Wired interrupts are generated in an implementation-defined way.
*/

#ifndef __ARCH_SMMUV3_H__
#define __ARCH_SMMUV3_H__

#include <bao.h>
#include <arch/platform.h>
#include <vm.h>
#include <mem.h>

// #-------------
// # Register Map
// #-------------

// # Page 0

/* IDR0 */
#define SMMUV3_IDR0_S2P_BIT (0x1UL << 0) // Stage-2 translation support
#define SMMUV3_IDR0_TTF_OFF \
    (2) // Translation tables format support //? Check target platform requirements
#define SMMUV3_IDR0_TTF_LEN           (2)
#define SMMUV3_IDR0_COHACC_BIT        (0x1UL << 4) // Coherent access support
#define SMMUV3_IDR0_BTM_BIT           (0x1UL << 5) // Broadcast TLB Maintenance Support
// A and D bits update support ignored
// Dormhint support ignored (to check if the SMMU has any cached data)
// Hyp Stage-1 context support ignored
// ATS ignored
// ASID ignored
// MSI generation support ignored
// ATOS support ignored (Register-based address translation, like debug reg IF in RISC-V)
// PRI ignored
#define SMMUV3_IDR0_VMW_BIT           (0x1UL << 17) // VMID matching for invalidation
#define SMMUV3_IDR0_VMID16_BIT        (0x1UL << 18) // 16-bit VMID support
// 2-lvl CDT ignored
// VATOS ignored
// endianness ignored
// stall model support ignored
// terminate model behavior is ignored since stage-2 faulting transactions always abort
#define SMMUV3_IDR0_ST_LEVEL_OFF      (27) // Multi-lvl ST support
#define SMMUV3_IDR0_ST_LEVEL_LEN      (2)

/* IDR1 */
#define SMMUV3_IDR1_SIDSIZE_OFF       (0) // Supported max width of the StreamID (max 32)
#define SMMUV3_IDR1_SIDSIZE_LEN       (6)
// SubstreamID ignored
// PRI queue supported
#define SMMUV3_IDR1_EVENTQS_OFF       (16) // Max number of EVTQ entries as log2(N)
#define SMMUV3_IDR1_EVENTQS_LEN       (5)
#define SMMUV3_IDR1_CMDQS_OFF         (21) // Max number of CMDQ entries as log2(N)
#define SMMUV3_IDR1_CMDQS_LEN         (5)
// Memory attributes override ignored
#define SMMUV3_IDR1_REL_BIT           (1UL << 28)
#define SMMUV3_IDR1_QUEUES_PRESET_BIT (1UL << 29)
#define SMMUV3_IDR1_TABLES_PRESET_BIT (1UL << 30)
// Enhanced CQ Interface support ignored

/* IDR2 */
// VATOS support ignored

/* IDR3 */
// All ignored

/* IDR4 */
// Implementation defined. Ignored

/* IDR5 */
#define SMMUV3_IDR5_OAS_OFF           (0)          // Output Address Size
#define SMMUV3_IDR5_OAS_LEN           (3)
#define SMMUV3_IDR5_GRAN4K_BIT        (0x1UL << 4) // 4KiB translation granule support
// 16k and 64k translation granularities support ignored (//? check whether bao uses this)
// VAX and STALL_MAX ignored

/* IIDR */
// All ignored

/* AIDR */
// Minor arch version ignored
#define SMMUV3_AIDR_MAJOR_OFF         (4) // Major SMMU arch version (must be 0 => SMMUv3)
#define SMMUV3_AIDR_MAJOR_LEN         (4)

/* CR0 */
#define SMMUV3_CR0_SMMUEN_BIT         (0x1UL << 0)
// PRIQ ignored
#define SMMUV3_CR0_EVENTQEN_BIT       (0x1UL << 2)
#define SMMUV3_CR0_CMDQEN_BIT         (0x1UL << 3)
// ATS check ignored
// VMID grouping for invalidations ignored

/* CR0 ACK */
#define SMMUV3_CR0ACK_SMMUEN_BIT      (0x1UL << 0)
// PRIQ ignored
#define SMMUV3_CR0ACK_EVENTQEN_BIT    (0x1UL << 2)
#define SMMUV3_CR0ACK_CMDQEN_BIT      (0x1UL << 3)

/* CR1 */
// Queue and Table Cacheability and shareability ignored

/* CR2 */
// EL2-E2H translation regime enable
#define SMMUV3_CR2_RECINVSID_BIT      (0x1UL << 1) // generate fault records for invalid streamIDs
#define SMMUV3_CR2_PTM_BIT            (0x1UL << 2) // Private TLB maintenance (ignore broadcast TLB operations)
// ATS records fault records ignored

/* STATUSR */
// Dormant ignored

/* GBPA */
#define SMMUV3_GBPA_MEMATTR_OFF       (0)          // Memory type
#define SMMUV3_GBPA_MEMATTR_LEN       (4)
#define SMMUV3_GBPA_MTCFG_BIT         (0x1UL << 4) // Memory type override (select input or override)
#define SMMUV3_GBPA_ALLOCCFG_OFF      (8)          // Alloc config
#define SMMUV3_GBPA_ALLOCCFG_LEN      (4)
#define SMMUV3_GBPA_SHCFG_OFF         (12)         // Shareability config
#define SMMUV3_GBPA_SHCFG_LEN         (2)
#define SMMUV3_GBPA_PRIVCFG_OFF       (16)         // Privileged config
#define SMMUV3_GBPA_PRIVCFG_LEN       (2)
#define SMMUV3_GBPA_INSTCFG_OFF       (18)         // Instruction/Data config
#define SMMUV3_GBPA_INSTCFG_LEN       (2)
#define SMMUV3_GBPA_ABORT_BIT         (0x1UL << 20) // Do not bypass transactions in the SMMU
#define SMMUV3_GBPA_MTCFG_BIT         (0x1UL << 31) // Set to 1 when updating the register

/* AGBPA */
// Ignored

/* IRQ_CTRL */
#define SMMUV3_IRQCTRL_GERROR_BIT     (0x1UL << 0) // Global errors interrupts enable
// PRI IRQ control ignored
#define SMMUV3_IRQCTRL_EVENTQ_BIT     (0x1UL << 2) // Event queue interrupts enable

/* IRQ_CTRL_ACK */
#define SMMUV3_IRQCTRLACK_GERROR_BIT  (0x1UL << 0) // Global errors interrupts enable ACK
#define SMMUV3_IRQCTRLACK_EVENTQ_BIT  (0x1UL << 2) // Event queue interrupts enable ACK

/* GERROR */
// unknown CMD errors ignored since we are not issuing commands
#define SMMUV3_GERROR_EVENTQ_ABT_BIT  (0x1UL << 2) // An access to the EQ was terminated with abort
// PRI ignored
// CMD sync MSI write error ignored
// EVENTQ MSI write error ignored   (we will use WSI)
// PRI MSI write ignored
// GERROR MSI write notification error ignored
#define SMMUV3_GERROR_SFM_ERR_BIT \
    (0x1UL << 8) // The SMMU entered Service Failure Mode. Traffic stopped
// Extended command queue errors ignored

/* GERROR_N (to acknowledge global errors toggling bits) */
#define SMMUV3_GERROR_N_EVENTQ_ABT_BIT (0x1UL << 2) // An access to the EQ was terminated with abort
#define SMMUV3_GERROR_N_SFM_ERR_BIT \
    (0x1UL << 8) // The SMMU entered Service Failure Mode. Traffic stopped

/* GERROR_IRQ_CFG0 (MSI Addr) */
// Ignored since we are not using MSIs to notify global errors

/* GERROR_IRQ_CFG1 (MSI Data) */
// Ignored since we are not using MSIs to notify global errors

/* GERROR_IRQ_CFG2 (MSI Shareability and Mem type) */
// Ignored since we are not using MSIs to notify global errors

/* STRTAB_BASE (64-bit) */
#define SMMUV3_STRTAB_BASE_ADDR_OFF (6) // Base address of the ST
#define SMMUV3_STRTAB_BASE_ADDR_LEN (46)
#define SMMUV3_STRTAB_BASE_ADDR_MASK \
    BIT64_MASK(SMMUV3_STRTAB_BASE_ADDR_OFF, SMMUV3_STRTAB_BASE_ADDR_LEN)
#define SMMUV3_STRTAB_BASE_RA_BIT         (1ULL << 62) // Read-allocate hint

/* STRTAB_BASE_CFG */
#define SMMUV3_STRTAB_BASE_CFG_LOG2SZ_OFF (0) // Size of the ST as log2(N)
#define SMMUV3_STRTAB_BASE_CFG_LOG2SZ_LEN (6)
#define SMMUV3_STRTAB_BASE_CFG_LOG2SZ_MASK \
    BIT32_MASK(SMMUV3_STRTAB_BASE_CFG_LOG2SZ_OFF, SMMUV3_STRTAB_BASE_CFG_LOG2SZ_LEN)
#define SMMUV3_STRTAB_BASE_CFG_SPLIT_OFF (6) // StreamID split point for 2-lvl STs
#define SMMUV3_STRTAB_BASE_CFG_SPLIT_LEN (5)
#define SMMUV3_STRTAB_BASE_CFG_SPLIT_MASK \
    BIT32_MASK(SMMUV3_STRTAB_BASE_CFG_SPLIT_OFF, SMMUV3_STRTAB_BASE_CFG_SPLIT_LEN)
#define SMMUV3_STRTAB_BASE_CFG_FMT_OFF (16) // ST format
#define SMMUV3_STRTAB_BASE_CFG_FMT_LEN (2)
#define SMMUV3_STRTAB_BASE_CFG_FMT_MASK \
    BIT32_MASK(SMMUV3_STRTAB_BASE_CFG_FMT_OFF, SMMUV3_STRTAB_BASE_CFG_FMT_LEN)
#define SMMUV3_STRTAB_BASE_CFG_FMT_LINEAR (0x0UL << SMMUV3_STRTAB_BASE_CFG_FMT_OFF)
#define SMMUV3_STRTAB_BASE_CFG_FMT_2LVL   (0x1UL << SMMUV3_STRTAB_BASE_CFG_FMT_OFF)

/* CMDQ BASE, PROD AND CONS */
// We are not using the CMDQ

/* EVENTQ_BASE */
#define SMMUV3_EVENTQ_BASE_LOG2SZ_OFF     (0) // Size of the EVENTQ as log2(N)
#define SMMUV3_EVENTQ_BASE_LOG2SZ_LEN     (5)
#define SMMUV3_EVENTQ_BASE_LOG2SZ_MASK \
    BIT64_MASK(SMMUV3_EVENTQ_BASE_LOG2SZ_OFF, SMMUV3_EVENTQ_BASE_LOG2SZ_LEN)
#define SMMUV3_EVENTQ_BASE_ADDR_OFF (5) // Base address of the EVENTQ
#define SMMUV3_EVENTQ_BASE_ADDR_LEN (47)
#define SMMUV3_EVENTQ_BASE_ADDR_MASK \
    BIT64_MASK(SMMUV3_EVENTQ_BASE_ADDR_OFF, SMMUV3_EVENTQ_BASE_ADDR_LEN)
#define SMMUV3_EVENTQ_BASE_WA_BIT    (1ULL << 62) // Write-allocate hint

/* alias for EVENTQ_PROD */
// not implemented

/* alias for EVENTQ_CONS */
// not implemented

/* EVENTQ_IRQ_CFG0 (MSI Addr) */
// Ignored since we are not using MSIs to notify EVENTQ interrupts

/* EVENTQ_IRQ_CFG1 (MSI Data) */
// Ignored since we are not using MSIs to notify EVENTQ interrupts

/* EVENTQ_IRQ_CFG2 (MSI Shareability and Mem type) */
// Ignored since we are not using MSIs to notify EVENTQ interrupts

/* PRIQ BASE, PROD AND CONS */
// Ignored. We are not using the PRIQ

/* GATOS registers */
// Ignored. We are not using the ATOS interface

/* MPAMIDR and VATOS regs */
// We are not using MPAM support

// All registers associated to the Enhanced CMDQ IF are ignored

// # Page 1

/* EVENTQ_PROD */
#define SMMUV3_EVENTQ_PROD_WR_OFF    (0)         // Write index of the EVENTQ
#define SMMUV3_EVENTQ_PROD_WR_LEN    (20)
#define SMMUV3_EVENTQ_PROD_OVFLG_BIT (1UL << 31) // Overflow flag (to be compared with CONS flag)

/* EVENTQ_CONS */
#define SMMUV3_EVENTQ_CONS_RD_OFF    (0)         // Read index of the EVENTQ
#define SMMUV3_EVENTQ_CONS_RD_LEN    (20)
#define SMMUV3_EVENTQ_CONS_OVACK_BIT (1UL << 31) // Overflow ACK flag

// # Register Map: Page 0 (4-kiB) (Offset 0x0)
struct smmuv3_regmap_p0_hw {
    uint32_t IDR0;
    uint32_t IDR1;
    uint32_t IDR2;
    uint32_t IDR3;
    uint32_t IDR4;
    uint32_t IDR5;
    uint32_t IIDR;
    uint32_t AIDR;
    uint32_t CR0;
    uint32_t CR0_ACK;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t STATUSR;
    uint32_t GBPA;
    uint32_t AGBPA;
    uint32_t IRQ_CTRL;
    uint32_t IRQ_CTRLACK;
    uint32_t GERROR;
    uint32_t GERROR_N;
    uint64_t GERROR_IRQ_CFG0;
    uint32_t GERROR_IRQ_CFG1;
    uint32_t GERROR_IRQ_CFG2;
    uint64_t STRTAB_BASE;
    uint32_t STRTAB_BASE_CFG;
    uint64_t CMDQ_BASE;
    uint32_t CMDQ_PROD;
    uint32_t CMDQ_CONS;
    uint64_t EVENTQ_BASE;
    uint32_t __EVENTQ_PROD;
    uint32_t __EVENTQ_CONS;
    uint64_t EVENTQ_IRQ_CFG0;
    uint32_t EVENTQ_IRQ_CFG1;
    uint32_t EVENTQ_IRQ_CFG2;
    uint64_t PRIQ_BASE;
    uint32_t __PRIQ_PROD;
    uint32_t __PRIQ_CONS;
    uint64_t PRIQ_IRQ_CFG0;
    uint32_t PRIQ_IRQ_CFG1;
    uint32_t PRIQ_IRQ_CFG2;
    uint32_t GATOS_CTRL;
    uint64_t GATOS_SID;
    uint64_t GATOS_ADDR;
    uint64_t GATOS_PAR;
    uint32_t MPAMIDR;
    uint32_t GMPAM;
    uint32_t GBPMPAM;
    uint32_t VATOS_SEL;
    uint32_t IDR6;
    uint8_t __impl1[0xF00 - 0xE00];
    uint8_t ID_REGS[0x1000 - 0xFD0];
} __attribute__((__packed__, __aligned__(0x10000))); // Aligned to 64 kiB

// Enhanced CMDQ not used

// Secure Register Interface not used

// # Register Map: Page 1 (4-kiB) (Offset 0x10000)
struct smmuv3_regmap_p1_hw {
    uint8_t __pad1[0xA8 - 0x00];
    uint32_t EVENTQ_PROD;
    uint32_t EVENTQ_CONS;
    uint8_t __pad2[0xC8 - 0xB0];
    uint32_t PRIQ_PROD;
    uint32_t PRIQ_CONS;
    uint8_t __pad3[0x1000 - 0x00D0];
} __attribute__((__packed__, __aligned__(0x10000))); // Aligned to 64 kiB

// #-------------
// # Stream Table
// #-------------

/* DW 1 */
#define SMMUV3_STE_VALID_BIT       (1ULL << 0)
#define SMMUV3_STE_CONFIG_OFF      (1)
#define SMMUV3_STE_CONFIG_LEN      (3)
#define SMMUV3_STE_CONFIG_MASK     BIT64_MASK(SMMUV3_STE_CONFIG_OFF, SMMUV3_STE_CONFIG_LEN)
#define SMMUV3_STE_CONFIG_ABORT    ((0b0ULL << SMMUV3_STE_CONFIG_OFF) & SMMUV3_STE_CONFIG_MASK)
#define SMMUV3_STE_CONFIG_BYPASS   ((0b0100ULL << SMMUV3_STE_CONFIG_OFF) & SMMUV3_STE_CONFIG_MASK)
#define SMMUV3_STE_CONFIG_S1ONLY   ((0b0101ULL << SMMUV3_STE_CONFIG_OFF) & SMMUV3_STE_CONFIG_MASK)
#define SMMUV3_STE_CONFIG_S2ONLY   ((0b0110ULL << SMMUV3_STE_CONFIG_OFF) & SMMUV3_STE_CONFIG_MASK)
#define SMMUV3_STE_CONFIG_2STAGE   ((0b0111ULL << SMMUV3_STE_CONFIG_OFF) & SMMUV3_STE_CONFIG_MASK)
// Stage 1 format and contexts ignored

/* DW 2 */
// Default SubstreamID ignored
// S1 ctx ptr attributes ignored (inner and outer cacheablility/allocation, shareability)
// Page-based HW attributes ignored (bits 59, 60, 61 and 62)
// Destructive Reads ignored
#define SMMUV3_STE_CONT_OFF        (77 - 64) // May be used to group equal STEs for different devices
#define SMMUV3_STE_CONT_LEN        (4)
#define SMMUV3_STE_CONT_MASK       BIT64_MASK(SMMUV3_STE_CONT_OFF, SMMUV3_STE_CONT_LEN)
// DCP ignored
// PPAR ignored
// Fault records merging ignored
// Stage 2 control of attributes ignored
// Stage 1 MPAM ignored
// Stage 1 stalls disable ignored
// We do not give support for ATS

#define SMMUV3_STE_MEMATTR_OFF     (96 - 96) // Memory type to be overriden
#define SMMUV3_STE_MEMATTR_LEN     (4)
#define SMMUV3_STE_MEMATTR_MASK    BIT64_MASK(SMMUV3_STE_MEMATTR_OFF, SMMUV3_STE_MEMATTR_LEN)
#define SMMUV3_STE_MEMATTR_IWB_OWB ((0b1111 << SMMUV3_STE_MEMATTR_OFF) & SMMUV3_STE_MEMATTR_MASK)
#define SMMUV3_STE_MTCFG_BIT       (1ULL << (100 - 96)) // Memory type override enable
#define SMMUV3_STE_ALLOCCFG_OFF    (101 - 96)           // Allocation hints override
#define SMMUV3_STE_ALLOCCFG_LEN    (4)
#define SMMUV3_STE_ALLOCCFG_MASK   BIT64_MASK(SMMUV3_STE_ALLOCCFG_OFF, SMMUV3_STE_ALLOCCFG_LEN)
#define SMMUV3_STE_ALLOCCFG_RA_WA  ((0b1110UL << SMMUV3_STE_ALLOCCFG_OFF) & SMMUV3_STE_ALLOCCFG_MASK)
#define SMMUV3_STE_SHCFG_OFF       (108 - 96) // Shareability config override
#define SMMUV3_STE_SHCFG_LEN       (2)
#define SMMUV3_STE_SHCFG_MASK      BIT64_MASK(SMMUV3_STE_SHCFG_OFF, SMMUV3_STE_SHCFG_LEN)
#define SMMUV3_STE_SHCFG_NONSH     ((0b00UL << SMMUV3_STE_SHCFG_OFF) & SMMUV3_STE_SHCFG_MASK)
#define SMMUV3_STE_SHCFG_USEIN     ((0b01UL << SMMUV3_STE_SHCFG_OFF) & SMMUV3_STE_SHCFG_MASK)
#define SMMUV3_STE_SHCFG_OUTSH     ((0b10UL << SMMUV3_STE_SHCFG_OFF) & SMMUV3_STE_SHCFG_MASK)
#define SMMUV3_STE_SHCFG_INNSH     ((0b11UL << SMMUV3_STE_SHCFG_OFF) & SMMUV3_STE_SHCFG_MASK)
// NS attribute ignored since we do not use Secure ST
#define SMMUV3_STE_PRIVCFG_OFF     (112 - 96) // Privilege config override
#define SMMUV3_STE_PRIVCFG_LEN     (2)
#define SMMUV3_STE_PRIVCFG_MASK    BIT64_MASK(SMMUV3_STE_PRIVCFG_OFF, SMMUV3_STE_PRIVCFG_LEN)
#define SMMUV3_STE_INSTCFG_OFF     (114 - 96) // Inst/Data override
#define SMMUV3_STE_INSTCFG_LEN     (2)
#define SMMUV3_STE_INSTCFG_MASK    BIT64_MASK(SMMUV3_STE_INSTCFG_OFF, SMMUV3_STE_INSTCFG_LEN)

/* DW 3 */
#define SMMUV3_STE_S2VMID_OFF      (128 - 128) // Stage 2 VMID
#define SMMUV3_STE_S2VMID_LEN      (16)
#define SMMUV3_STE_S2VMID_MASK     BIT64_MASK(SMMUV3_STE_S2VMID_OFF, SMMUV3_STE_S2VMID_LEN)

#define SMMUV3_STE_S2T0SZ_OFF      (160 - 160) // Size of the IPA input region
#define SMMUV3_STE_S2T0SZ_LEN      (6)
#define SMMUV3_STE_S2T0SZ_MASK     BIT64_MASK(SMMUV3_STE_S2T0SZ_OFF, SMMUV3_STE_S2T0SZ_LEN)
#define SMMUV3_STE_S2SL0_OFF       (166 - 160) // Starting level of stage 2 translation table walk
#define SMMUV3_STE_S2SL0_LEN       (2)
#define SMMUV3_STE_S2SL0_MASK      BIT64_MASK(SMMUV3_STE_S2SL0_OFF, SMMUV3_STE_S2SL0_LEN)
#define SMMUV3_STE_S2SL0_LVL0      ((0b10UL << SMMUV3_STE_S2SL0_OFF) & SMMUV3_STE_S2SL0_LEN)
#define SMMUV3_STE_S2SL0_LVL1      ((0b01UL << SMMUV3_STE_S2SL0_OFF) & SMMUV3_STE_S2SL0_LEN)
#define SMMUV3_STE_S2SL0_LVL2      ((0b00UL << SMMUV3_STE_S2SL0_OFF) & SMMUV3_STE_S2SL0_LEN)
#define SMMUV3_STE_S2IR0_OFF       (168 - 160) // Inner region cacheability for stage 2 table walks
#define SMMUV3_STE_S2IR0_LEN       (2)
#define SMMUV3_STE_S2IR0_MASK      BIT64_MASK(SMMUV3_STE_S2IR0_OFF, SMMUV3_STE_S2IR0_LEN)
#define SMMUV3_STE_S2IR0_NC        ((0b00UL << SMMUV3_STE_S2IR0_OFF) & SMMUV3_STE_S2IR0_MASK)
#define SMMUV3_STE_S2IR0_WB_RA_WA  ((0b01UL << SMMUV3_STE_S2IR0_OFF) & SMMUV3_STE_S2IR0_MASK)
#define SMMUV3_STE_S2IR0_WT_RA     ((0b10UL << SMMUV3_STE_S2IR0_OFF) & SMMUV3_STE_S2IR0_MASK)
#define SMMUV3_STE_S2IR0_WB_RA_NWA ((0b11UL << SMMUV3_STE_S2IR0_OFF) & SMMUV3_STE_S2IR0_MASK)
#define SMMUV3_STE_S2OR0_OFF       (170 - 160) // Outer region cacheability for stage 2 table walks
#define SMMUV3_STE_S2OR0_LEN       (2)
#define SMMUV3_STE_S2OR0_MASK      BIT64_MASK(SMMUV3_STE_S2OR0_OFF, SMMUV3_STE_S2OR0_LEN)
#define SMMUV3_STE_S2OR0_NC        ((0b00UL << SMMUV3_STE_S2OR0_OFF) & SMMUV3_STE_S2OR0_MASK)
#define SMMUV3_STE_S2OR0_WB_RA_WA  ((0b01UL << SMMUV3_STE_S2OR0_OFF) & SMMUV3_STE_S2OR0_MASK)
#define SMMUV3_STE_S2OR0_WT_RA     ((0b10UL << SMMUV3_STE_S2OR0_OFF) & SMMUV3_STE_S2OR0_MASK)
#define SMMUV3_STE_S2OR0_WB_RA_NWA ((0b11UL << SMMUV3_STE_S2OR0_OFF) & SMMUV3_STE_S2OR0_MASK)
#define SMMUV3_STE_S2SH0_OFF       (172 - 160) // Shareability for stage 2 table walks
#define SMMUV3_STE_S2SH0_LEN       (2)
#define SMMUV3_STE_S2SH0_MASK      BIT64_MASK(SMMUV3_STE_S2SH0_OFF, SMMUV3_STE_S2SH0_LEN)
#define SMMUV3_STE_S2SH0_NONSH     ((0b00UL << SMMUV3_STE_S2SH0_OFF) & SMMUV3_STE_S2SH0_MASK)
#define SMMUV3_STE_S2SH0_OUTSH     ((0b10UL << SMMUV3_STE_S2SH0_OFF) & SMMUV3_STE_S2SH0_MASK)
#define SMMUV3_STE_S2SH0_INNSH     ((0b11UL << SMMUV3_STE_S2SH0_OFF) & SMMUV3_STE_S2SH0_MASK)
#define SMMUV3_STE_S2TG_OFF        (174 - 160) // Stage 2 translation granule size
#define SMMUV3_STE_S2TG_LEN        (2)
#define SMMUV3_STE_S2TG_MASK       BIT64_MASK(SMMUV3_STE_S2TG_OFF, SMMUV3_STE_S2TG_LEN)
#define SMMUV3_STE_S2PS_OFF        (176 - 160) // Physical address size (for fault checking)
#define SMMUV3_STE_S2PS_LEN        (2)
#define SMMUV3_STE_S2PS_MASK       BIT64_MASK(SMMUV3_STE_S2PS_OFF, SMMUV3_STE_S2PS_LEN)
#define SMMUV3_STE_S2AA64_BIT \
    (1ULL << (179 - 160)) // Stage 2 translation table format (AArch64 /AArch32)
#define SMMUV3_STE_S2ENDI_BIT (1ULL << (180 - 160)) // Stage 2 translation table endianness
#define SMMUV3_STE_S2AFFD_BIT (1ULL << (181 - 160)) // Stage 2 AF fault disable
// Protected Table Walks not used
#define SMMUV3_STE_S2HD_BIT   (1ULL << (183 - 160)) // Stage 2 DF HW update
#define SMMUV3_STE_S2HA_BIT   (1ULL << (184 - 160)) // Stage 2 AF HW updates
#define SMMUV3_STE_S2S_BIT    (1ULL << (185 - 160)) // Stage 2 fault behavior - Stall
#define SMMUV3_STE_S2R_BIT    (1ULL << (186 - 160)) // Stage 2 fault behavior - Record

/* DW 4 */
#define SMMUV3_STE_S2TTB_OFF  (196 - 196) // Address of Translation Table Base
#define SMMUV3_STE_S2TTB_LEN  (48)
#define SMMUV3_STE_S2TTB_MASK BIT64_MASK(SMMUV3_STE_S2TTB_OFF, SMMUV3_STE_S2TTB_LEN)

/* DW 5 */
// MPAM PARTID ignored
// Secure fields ignored

/* DW 6 */
// MPAM PMG and NS ignored
// VM Structure ignored (we're using stage 2 only)

/* DW 7 */
// Secure STE stuff ignored

struct smmuv3_ste {
    uint64_t s1_ctx;
    uint32_t tc;
    uint32_t attr_ovrd;
    uint32_t s2_vmid;
    uint32_t s2_cfg;
    uint64_t s2_ttb;
    uint32_t partid;
    uint32_t sec_cfg;
    uint64_t vms_ptr;
    uint64_t sec_s2ttb;
    uint64_t __res0;
} __attribute__((__packed__));

// #-------------
// # Event Queue
// #-------------

#define SMMUV3_EVENTQ_NUMBER_OFF  (0)
#define SMMUV3_EVENTQ_NUMBER_LEN  (8)
#define SMMUV3_EVENTQ_NUMBER_MASK BIT32_MASK(SMMUV3_EVENTQ_NUMBER_OFF, SMMUV3_EVENTQ_NUMBER_LEN)

struct smmuv3_eventq_entry {
    uint32_t record[8];
} __attribute__((__packed__));

void smmu_init();

ssize_t smmu_alloc_ctxbnk();
ssize_t smmu_alloc_sme();
void smmu_write_ctxbnk(size_t ctx_id, paddr_t root_pt, asid_t vm_id);
void smmu_write_sme(size_t sme, streamid_t mask, streamid_t id, bool group);
void smmu_write_s2c(size_t sme, size_t ctx_id);
size_t smmu_sme_get_ctx(size_t sme);
streamid_t smmu_sme_get_id(size_t sme);
streamid_t smmu_sme_get_mask(size_t sme);
bool smmu_sme_is_group(size_t sme);
bool smmu_compatible_sme_exists(streamid_t mask, streamid_t id, size_t ctx, bool group);

#endif
