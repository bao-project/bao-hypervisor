/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_CLOCK_H__
#define __PLAT_CLOCK_H__

#include <platform.h>

#define PLAT_CLK_ISO_BASE     (0xFF980000UL)
#define PLAT_CLK_AWO_BASE     (0xFF988000UL)

#define CLKKCPROT1_ENABLE_WR  (0xA5A5A501UL)
#define CLKKCPROT1_DISABLE_WR (0xA5A5A500UL)

#define MOSCE_MOSCENTRG_BIT   (0x1UL << 0)

#define MOSCS_MOSCEN_BIT      (0x1UL << 0)
#define MOSCS_MOSCSTAB_BIT    (0x1UL << 1)

#define PLLE_PLLENTRG_BIT     (0x1UL << 0)

#define PLLS_PLLCLKEN_BIT     (0x1UL << 0)
#define PLLS_PLLCLKSTAB_BIT   (0x1UL << 1)

/* Clock Controller Registers for ISO area */
struct clk_ctl_iso_hw {
    uint32_t PLLE;       // 0x0000 PLL Enable Register
    uint32_t PLLS;       // 0x0004 PLL Status Register
    uint8_t pad0[0xC - 0x8];
    uint32_t PLLSTPM;    // 0x000C PLL Stop Mask Register
    uint8_t pad1[0x100 - 0x10];
    uint32_t CKSC_CPUC;  // 0x0100 CLK_CPU Selector Control Register
    uint8_t pad2[0x108 - 0x104];
    uint32_t CKSC_CPUS;  // 0x0108 CLK_CPU Selector Status Register
    uint8_t pad3[0x120 - 0x10C];
    uint32_t CLKD_PLLC;  // 0x0120 CLK_PLLO Divider Control Register
    uint8_t pad4[0x128 - 0x124];
    uint32_t CLKD_PLLS;  // 0x0128 CLK_PLLO Divider Status Register
    uint8_t pad5[0x140 - 0x12C];
    uint32_t CKSC_RLINC; // 0x0140 CLK_RLIN Selector Control Register
    uint8_t pad6[0x148 - 0x144];
    uint32_t CKSC_RLINS; // 0x0148 CLK_RLIN Selector Status Register
    uint8_t pad7[0x150 - 0x14C];
    uint32_t CKSC_RCANC; // 0x0150 CLK_RCANO Selector Control Register
    uint8_t pad8[0x158 - 0x154];
    uint32_t CKSC_RCANS; // 0x0158 CLK_RCANO Selector Status Register
    uint8_t pad9[0x160 - 0x15C];
    uint32_t CKSC_ADCC;  // 0x0160 CLK_ADC Selector Control Register
    uint8_t pad10[0x168 - 0x164];
    uint32_t CKSC_ADCS;  // 0x0168 CLK_ADC Selector Status Register
    uint8_t pad11[0x170 - 0x16C];
    uint32_t CKSC_MSPIC; // 0x0170 CLK_MSPI Selector Control Register
    uint8_t pad12[0x178 - 0x174];
    uint32_t CKSC_MSPIS; // 0x0178 CLK_MSPI Selector Status Register
    uint8_t pad13[0x700 - 0x17C];
    uint32_t CLKKCPROT1; // 0x0700 Clock Controller Register Key Code Protection 1
};

/* Clock Controller Registers for AWO area */
struct clk_ctl_awo_hw {
    uint32_t MOSCE;       // 0x0000 Main OSC Enable Register
    uint32_t MOSCS;       // 0x0004 Main OSC Status Register
    uint8_t pad0[0xC - 0x8];
    uint32_t MOSCSTPM;    // 0x000C Main OSC Stop Mask Register
    uint8_t pad1[0x100 - 0x10];
    uint32_t HSOSCS;      // 0x0100 HS IntOSC Status Register
    uint32_t HSOSCSTPM;   // 0x0104 HS IntOSC Stop Mask Register
    uint8_t pad2[0x200 - 0x108];
    uint32_t CKSC_AWDTC;  // 0x0200 CLKA_WDT Selector Control Register
    uint8_t pad3[0x208 - 0x204];
    uint32_t CKSC_AWDTS;  // 0x0208 CLKA_WDT Selector Status Register
    uint8_t pad4[0x210 - 0x20C];
    uint32_t CKSC_ATAUJC; // 0x0210 CLKA_TAUJ Selector Control Register
    uint8_t pad5[0x218 - 0x214];
    uint32_t CKSC_ATAUJS; // 0x0218 CLKA_TAUJ Selector Status Register
    uint8_t pad6[0x220 - 0x21C];
    uint32_t CKSC_ARTCAC; // 0x0220 CLKA_RTCA Selector Control Register
    uint8_t pad7[0x228 - 0x224];
    uint32_t CKSC_ARTCAS; // 0x0228 CLKA_RTCA Selector Status Register
    uint8_t pad8[0x230 - 0x22C];
    uint32_t CKSC_AADCC;  // 0x0230 CLKA_ADC Selector Control Register
    uint8_t pad9[0x238 - 0x234];
    uint32_t CKSC_AADCS;  // 0x0238 CLKA_ADC Selector Status Register
    uint8_t pad10[0x240 - 0x23C];
    uint32_t CLKD_AADCC;  // 0x0240 CLKA_ADC Divider Control Register
    uint8_t pad11[0x248 - 0x244];
    uint32_t CLKD_AADCS;  // 0x0248 CLKA_ADC Divider Status Register
    uint8_t pad12[0x250 - 0x24C];
    uint32_t CKSC_FOUT0C; // 0x0250 FOUT0 Clock Selector Control Register
    uint8_t pad13[0x258 - 0x254];
    uint32_t CKSC_FOUT0S; // 0x0258 FOUT0 Clock Selector Status Register
    uint8_t pad14[0x260 - 0x25C];
    uint32_t CLKD_FOUT0C; // 0x0260 FOUT0 Clock Divider Control Register
    uint8_t pad15[0x268 - 0x264];
    uint32_t CLKD_FOUT0S; // 0x0268 FOUT0 Clock Divider Status Register
    uint8_t pad16[0x270 - 0x26C];
    uint32_t CKSC_FOUT1C; // 0x0270 FOUT1 Clock Selector Control Register
    uint8_t pad17[0x278 - 0x274];
    uint32_t CKSC_FOUT1S; // 0x0278 FOUT1 Clock Selector Status Register
    uint8_t pad18[0x280 - 0x27C];
    uint32_t CLKD_FOUT1C; // 0x0280 FOUT1 Clock Divider Control Register
    uint8_t pad19[0x288 - 0x284];
    uint32_t CLKD_FOUT1S; // 0x0288 FOUT1 Clock Divider Status Register
    uint8_t pad20[0x300 - 0x28C];
    uint32_t CKSC_WDTC;   // 0x0300 CLK_WDT Selector Control Register
    uint8_t pad21[0x308 - 0x304];
    uint32_t CKSC_WDTS;   // 0x0308 CLK_WDT Selector Status Register
};

void clock_init(void);

#endif /* __PLAT_CLOCK_H__ */
