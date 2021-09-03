/**
 * Bao Hypervisor
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

#ifndef __ARCH_CSR_H__
#define __ARCH_CSR_H__

#include <bao.h>

#define CSR_VSSTATUS 0x200
#define CSR_VSIE 0x204
#define CSR_VSTVEC 0x205
#define CSR_VSSCRATCH 0x240
#define CSR_VSEPC 0x241
#define CSR_VSCAUSE 0x242
#define CSR_VSTVAL 0x243
#define CSR_VSIP 0x244
#define CSR_VSATP 0x280

#define CSR_HSTATUS 0x600
#define CSR_HEDELEG 0x602
#define CSR_HIDELEG 0x603
#define CSR_HIE 0x604
#define CSR_HTIMEDELTA 0x605
#define CSR_HTIMEDELTAH 0x615
#define CSR_HCOUNTEREN 0x606
#define CSR_HGEIE 0x607
#define CSR_HTVAL 0x643
#define CSR_HIP 0x644
#define CSR_HVIP 0x645
#define CSR_HTINST 0x64A
#define CSR_HGATP 0x680
#define CSR_HGEIP 0xE07

#define STVEC_MODE_OFF (0)
#define STVEC_MODE_LEN (2)
#define STVEC_MODE_MSK BIT_MASK(STVEC_MODE_OFF, STVEC_MODE_LEN)
#define STVEC_MODE_DIRECT (0)
#define STVEC_MODE_VECTRD (1)

#if (RV64)
#define SATP_MODE_OFF (60)
#define SATP_MODE_DFLT SATP_MODE_39
#define SATP_ASID_OFF (44)
#define SATP_ASID_LEN (16)
#define HGATP_VMID_OFF (44)
#define HGATP_VMID_LEN (14)
#elif (RV32)
#define SATP_MODE_OFF (31)
#define SATP_MODE_DFLT SATP_MODE_32
#define SATP_ASID_OFF (22)
#define SATP_ASID_LEN (9)
#define HGATP_VMID_OFF (22)
#define HGATP_VMID_LEN (7)
#endif

#define SATP_MODE_BARE (0ULL << SATP_MODE_OFF)
#define SATP_MODE_32 (1ULL << SATP_MODE_OFF)
#define SATP_MODE_39 (8ULL << SATP_MODE_OFF)
#define SATP_MODE_48 (9ULL << SATP_MODE_OFF)
#define SATP_ASID_MSK BIT_MASK(SATP_ASID_OFF, SATP_ASID_LEN)

#define HGATP_MODE_OFF SATP_MODE_OFF
#define HGATP_MODE_DFLT SATP_MODE_DFLT
#define HGATP_VMID_MSK BIT_MASK(HGATP_VMID_OFF, HGATP_VMID_LEN)

#define SSTATUS_UIE_BIT (1ULL << 0)
#define SSTATUS_SIE_BIT (1ULL << 1)
#define SSTATUS_UPIE_BIT (1ULL << 4)
#define SSTATUS_SPIE_BIT (1ULL << 5)
#define SSTATUS_SPP_BIT (1ULL << 8)
#define SSTATUS_FS_OFF (13)
#define SSTATUS_FS_LEN (2)
#define SSTATUS_FS_MSK BIT_MASK(SSTATUS_FS_OFF, SSTATUS_FS_LEN)
#define SSTATUS_FS_AOFF (0)
#define SSTATUS_FS_INITIAL (1ULL << SSTATUS_FS_OFF)
#define SSTATUS_FS_CLEAN (2ULL << SSTATUS_FS_OFF)
#define SSTATUS_FS_DIRTY (3ULL << SSTATUS_FS_OFF)
#define SSTATUS_XS_OFF (15)
#define SSTATUS_XS_LEN (2)
#define SSTATUS_XS_MSK BIT_MASK(SSTATUS_XS_OFF, SSTATUS_XS_LEN)
#define SSTATUS_XS_AOFF (0)
#define SSTATUS_XS_INITIAL (1ULL << SSTATUS_XS_OFF)
#define SSTATUS_XS_CLEAN (2ULL << SSTATUS_XS_OFF)
#define SSTATUS_XS_DIRTY (3ULL << SSTATUS_XS_OFF)
#define SSTATUS_SUM (1ULL << 18)
#define SSTATUS_MXR (1ULL << 19)
#define SSTATUS_SD (1ULL << 63)

#define SIE_USIE (1ULL << 0)
#define SIE_SSIE (1ULL << 1)
#define SIE_UTIE (1ULL << 4)
#define SIE_STIE (1ULL << 5)
#define SIE_UEIE (1ULL << 8)
#define SIE_SEIE (1ULL << 9)

#define SIP_USIP SIE_USIE
#define SIP_SSIP SIE_SSIE
#define SIP_UTIP SIE_UTIE
#define SIP_STIP SIE_STIE
#define SIP_UEIP SIE_UEIE
#define SIP_SEIP SIE_SEIE

#define HIE_VSSIE (1ULL << 2)
#define HIE_VSTIE (1ULL << 6)
#define HIE_VSEIE (1ULL << 10)
#define HIE_SGEIE (1ULL << 12)

#define HIP_VSSIP HIE_VSSIE
#define HIP_VSTIP HIE_VSTIE
#define HIP_VSEIP HIE_VSEIE
#define HIP_SGEIP HIE_SGEIE

#define SCAUSE_INT_BIT (1ULL << ((REGLEN * 8) - 1))
#define SCAUSE_CODE_MSK (SCAUSE_INT_BIT - 1)
#define SCAUSE_CODE_USI (0 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_SSI (1 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_VSSI (2 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_UTI (4 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_STI (5 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_VSTI (6 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_UEI (8 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_SEI (9 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_VSEI (10 | SCAUSE_INT_BIT)
#define SCAUSE_CODE_IAM (0)
#define SCAUSE_CODE_IAF (1)
#define SCAUSE_CODE_ILI (2)
#define SCAUSE_CODE_BKP (3)
#define SCAUSE_CODE_LAM (4)
#define SCAUSE_CODE_LAF (5)
#define SCAUSE_CODE_SAM (6)
#define SCAUSE_CODE_SAF (7)
#define SCAUSE_CODE_ECU (8)
#define SCAUSE_CODE_ECS (9)
#define SCAUSE_CODE_ECV (10)
#define SCAUSE_CODE_IPF (12)
#define SCAUSE_CODE_LPF (13)
#define SCAUSE_CODE_SPF (15)
#define SCAUSE_CODE_IGPF (20)
#define SCAUSE_CODE_LGPF (21)
#define SCAUSE_CODE_VRTI (22)
#define SCAUSE_CODE_SGPF (23)

#define HIDELEG_USI SIP_USIP
#define HIDELEG_SSI SIP_SSIP
#define HIDELEG_UTI SIP_UTIP
#define HIDELEG_STI SIP_STIP
#define HIDELEG_UEI SIP_UEIP
#define HIDELEG_SEI SIP_SEIP
#define HIDELEG_VSSI HIP_VSSIP
#define HIDELEG_VSTI HIP_VSTIP
#define HIDELEG_VSEI HIP_VSEIP
#define HIDELEG_SGEI HIP_SGEIP

#define HEDELEG_IAM (1ULL << 0)
#define HEDELEG_IAF (1ULL << 1)
#define HEDELEG_ILI (1ULL << 2)
#define HEDELEG_BKP (1ULL << 3)
#define HEDELEG_LAM (1ULL << 4)
#define HEDELEG_LAF (1ULL << 5)
#define HEDELEG_SAM (1ULL << 6)
#define HEDELEG_SAF (1ULL << 7)
#define HEDELEG_ECU (1ULL << 8)
#define HEDELEG_ECS (1ULL << 9)
#define HEDELEG_ECV (1ULL << 10)
#define HEDELEG_IPF (1ULL << 12)
#define HEDELEG_LPF (1ULL << 13)
#define HEDELEG_SPF (1ULL << 15)

#define MISA_H (1ULL << 7)

#define HSTATUS_VSBE (1ULL << 5)
#define HSTATUS_GVA (1ULL << 6)
#define HSTATUS_SPV (1ULL << 7)
#define HSTATUS_SPVP (1ULL << 8)
#define HSTATUS_HU (1ULL << 9)
#define HSTATUS_VGEIN_OFF (12)
#define HSTATUS_VGEIN_LEN (12)
#define HSTATUS_VGEIN_MSK (BIT_MASK(HSTATUS_VGEIN_OFF, HSTATUS_VGEIN_LEN))
#define HSTATUS_VTVM (1ULL << 20)
#define HSTATUS_VTW (1ULL << 21)
#define HSTATUS_VTSR (1ULL << 22)
#define HSTATUS_VSXL_OFF (32)
#define HSTATUS_VSXL_LEN (2)
#define HSTATUS_VSXL_MSK (BIT_MASK(HSTATUS_VSXL_OFF, HSTATUS_VSXL_LEN))
#define HSTATUS_VSXL_32 (1ULL << HSTATUS_VSXL_OFF)
#define HSTATUS_VSXL_64 (2ULL << HSTATUS_VSXL_OFF)

#define HCOUNTEREN_CY (1ULL << 0)
#define HCOUNTEREN_TM (1ULL << 1)
#define HCOUNTEREN_IR (1ULL << 2)

#define TINST_PSEUDO_STORE  (0x3020)
#define TINST_PSEUDO_LOAD   (0x3000)
#define TINST_INS_COMPRESSED(tinst) (!((tinst) & 0x2))
#define TINST_INS_SIZE(tinst) (TINST_INS_COMPRESSED((tinst)) ? 2 : 4)

#ifndef __ASSEMBLER__

#define CSRR(csr)                                     \
    ({                                                \
        uint64_t _temp;                               \
        asm volatile("csrr  %0, " XSTR(csr) "\n\r" \
                     : "=r"(_temp)::"memory");        \
        _temp;                                        \
    })

#define CSRW(csr, rs) \
    asm volatile("csrw  " XSTR(csr) ", %0\n\r" ::"rK"(rs) : "memory")
#define CSRS(csr, rs) \
    asm volatile("csrs  " XSTR(csr) ", %0\n\r" ::"rK"(rs) : "memory")
#define CSRC(csr, rs) \
    asm volatile("csrc  " XSTR(csr) ", %0\n\r" ::"rK"(rs) : "memory")

#endif /* __ASSEMBLER__ */

#endif /* __ARCH_CSRS_H__ */
