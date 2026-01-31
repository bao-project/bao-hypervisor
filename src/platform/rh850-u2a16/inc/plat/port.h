/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PORT_H__
#define __PLAT_PORT_H__

#include <platform.h>

#define PLAT_MAX_NUM_PORT_GROUPS  (25)
#define PLAT_MAX_NUM_APORT_GROUPS (6)

#define PLAT_NUM_PORT_GROUPS      (11)
#define PLAT_NUM_APORT_GROUPS     (5)

#define PLAT_NUM_PORT_CFG_REGS    (21)
#define PLAT_NUM_APORT_CFG_REGS   (11)

#define PLAT_PORT_GROUP_MASK                                                                      \
    ((1UL << 2) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (1UL << 10) | (1UL << 17) | \
        (1UL << 20) | (1UL << 21) | (1UL << 22) | (1UL << 24))

#define PLAT_APORT_GROUP_MASK    ((1UL << 0) | (1UL << 1) | (1UL << 2) | (1UL << 3) | (1UL << 4))

#define PORT_PKCPROT_ENABLE_WR   (0xA5A5A501UL)
#define PORT_PKCPROT_DISABLE_WR  (0xA5A5A500UL)
#define PORT_PWE_ENABLE_ALL_MASK (0x0BF724F8UL)

#define PLAT_PORT_BASE           (0xFFD90000UL)

enum port_reg_idx {
    Pn,
    PMn,
    PMCn,
    PFCn,
    PFCEn,
    PFCAEn,
    PINVn,
    PIBCn,
    PBDCn,
    PIPCn,
    PUn,
    PDn,
    PODCn,
    PDSCn,
    PISn,
    PISAn,
    PUCCn,
    PODCEn,
    PSFCn,
    PSFTSn,
    PSFTSEn
};

enum aport_reg_idx {
    APn,
    APMn,
    APINVn,
    APIBCn,
    APBDCn,
    APODCn,
    APDSCn,
    APODCEn,
    APSFCn,
    APSFTSn,
    APSFTSEn
};

/* Port Group Register Sets */
struct port_group_regset1 {
    uint16_t P;       /* 0x0000 + 0x40*n */
    uint8_t pad0[2];  /* 0x0002 + 0x40*n */
    uint32_t PSR;     /* 0x0004 + 0x40*n */
    uint16_t PNOT;    /* 0x0008 + 0x40*n */
    uint8_t pad1[2];  /* 0x000A + 0x40*n */
    uint16_t PPR;     /* 0x000C + 0x40*n */
    uint8_t pad2[2];  /* 0x000E + 0x40*n */
    uint16_t PM;      /* 0x0010 + 0x40*n */
    uint8_t pad3[2];  /* 0x0012 + 0x40*n */
    uint16_t PMC;     /* 0x0014 + 0x40*n */
    uint8_t pad4[2];  /* 0x0016 + 0x40*n */
    uint16_t PFC;     /* 0x0018 + 0x40*n */
    uint8_t pad5[2];  /* 0x001A + 0x40*n */
    uint16_t PFCE;    /* 0x001C + 0x40*n */
    uint8_t pad6[2];  /* 0x001E + 0x40*n */
    uint32_t PMSR;    /* 0x0020 + 0x40*n */
    uint32_t PMCSR;   /* 0x0024 + 0x40*n */
    uint16_t PFCAE;   /* 0x0028 + 0x40*n */
    uint8_t pad7[6];  /* 0x002A + 0x40*n */
    uint16_t PINV;    /* 0x0030 + 0x40*n */
    uint8_t pad8[14]; /* 0x0032 + 0x40*n */
};

struct port_group_regset2 {
    uint32_t PCR_m[16]; /* 0x2000 + 0x40*n */
};

struct port_group_regset3 {
    uint16_t PIBC;    /* 0x4000 + 0x40*n */
    uint8_t pad0[2];  /* 0x4002 + 0x40*n */
    uint16_t PBDC;    /* 0x4004 + 0x40*n */
    uint8_t pad1[2];  /* 0x4006 + 0x40*n */
    uint16_t PIPC;    /* 0x4008 + 0x40*n */
    uint8_t pad2[2];  /* 0x400A + 0x40*n */
    uint16_t PU;      /* 0x400C + 0x40*n */
    uint8_t pad3[2];  /* 0x400E + 0x40*n */
    uint16_t PD;      /* 0x4010 + 0x40*n */
    uint8_t pad4[2];  /* 0x4012 + 0x40*n */
    uint16_t PODC;    /* 0x4014 + 0x40*n */
    uint8_t pad5[2];  /* 0x4016 + 0x40*n */
    uint16_t PDSC;    /* 0x4018 + 0x40*n */
    uint8_t pad6[2];  /* 0x401A + 0x40*n */
    uint16_t PIS;     /* 0x401C + 0x40*n */
    uint8_t pad7[6];  /* 0x401E + 0x40*n */
    uint16_t PISA;    /* 0x4024 + 0x40*n */
    uint8_t pad8[2];  /* 0x4026 + 0x40*n */
    uint16_t PUCC;    /* 0x4028 + 0x40*n */
    uint8_t pad9[14]; /* 0x402A + 0x40*n */
    uint16_t PODCE;   /* 0x4038 + 0x40*n */
    uint8_t pad10[6]; /* 0x403A + 0x40*n */
};

struct port_group_regset4 {
    uint16_t PSFC;    /* 0x6000 + 0x40*n */
    uint8_t pad0[14]; /* 0x6002 + 0x40*n */
    uint16_t PSFTS;   /* 0x6010 + 0x40*n */
    uint8_t pad1[2];  /* 0x6012 + 0x40*n */
    uint16_t PSFTSE;  /* 0x6014 + 0x40*n */
    uint8_t pad2[42]; /* 0x6016 + 0x40*n */
};

/* Analog Port Group Register Sets */
struct analog_port_group_regset1 {
    uint16_t AP;      /* 0x0C80 + 0x40*n */
    uint8_t pad0[2];  /* 0x0C82 + 0x40*n */
    uint32_t APSR;    /* 0x0C84 + 0x40*n */
    uint16_t APNOT;   /* 0x0C88 + 0x40*n */
    uint8_t pad1[2];  /* 0x0C8A + 0x40*n */
    uint16_t APPR;    /* 0x0C8C + 0x40*n */
    uint8_t pad2[2];  /* 0x0C8E + 0x40*n */
    uint16_t APM;     /* 0x0C90 + 0x40*n */
    uint8_t pad3[14]; /* 0x0C92 + 0x40*n */
    uint32_t APMSR;   /* 0x0CA0 + 0x40*n */
    uint8_t pad4[12]; /* 0x0CAA + 0x40*n */
    uint16_t APINV;   /* 0x0CB0 + 0x40*n */
    uint8_t pad5[14]; /* 0x0CB2 + 0x40*n */
};

struct analog_port_group_regset2 {
    uint32_t APCR_m[16]; /* 0x2C80 + 0x40*n */
};

struct analog_port_group_regset3 {
    uint16_t APIBC;   /* 0x4C80 + 0x40*n */
    uint8_t pad0[2];  /* 0x4C82 + 0x40*n */
    uint16_t APBDC;   /* 0x4C84 + 0x40*n */
    uint8_t pad1[14]; /* 0x4C86 + 0x40*n */
    uint16_t APODC;   /* 0x4C94 + 0x40*n */
    uint8_t pad2[2];  /* 0x4C96 + 0x40*n */
    uint16_t APDSC;   /* 0x4C98 + 0x40*n */
    uint8_t pad3[30]; /* 0x4C9A + 0x40*n */
    uint16_t APODCE;  /* 0x4CB8 + 0x40*n */
    uint8_t pad4[6];  /* 0x4CBA + 0x40*n */
};

struct analog_port_group_regset4 {
    uint16_t APSFC;   /* 0x6C80 + 0x40*n */
    uint8_t pad0[14]; /* 0x6C82 + 0x40*n */
    uint16_t APSFTS;  /* 0x6C90 + 0x40*n */
    uint8_t pad1[2];  /* 0x6C92 + 0x40*n */
    uint16_t APSFTSE; /* 0x6C94 + 0x40*n */
    uint8_t pad2[42]; /* 0x6C96 + 0x40*n */
};

/* PORT Register Map Struct */
struct port_hw {
    struct port_group_regset1 p_regset1[PLAT_MAX_NUM_PORT_GROUPS];          /* 0x0000 - 0x063F */
    uint8_t pad0[0xC80 - 0x640];                                            /* 0x0640 - 0x0C7F */
    struct analog_port_group_regset1 ap_regset1[PLAT_MAX_NUM_APORT_GROUPS]; /* 0x0C80 - 0x0DFF */
    uint8_t pad1[0x2000 - 0xE00];                                           /* 0x0E00 - 0x1FFF */
    struct port_group_regset2 p_regset2[PLAT_MAX_NUM_PORT_GROUPS];          /* 0x2000 - 0x263F */
    uint8_t pad2[0x2C80 - 0x2640];                                          /* 0x2640 - 0x2C7F */
    struct analog_port_group_regset2 ap_regset2[PLAT_MAX_NUM_APORT_GROUPS]; /* 0x2C80 - 0x2DFF */
    uint8_t pad3[0x2F40 - 0x2E00];                                          /* 0x2E00 - 0x2F3F */
    uint32_t PKCPROT;                                                       /* 0x2F40 - 0x2F43 */
    uint32_t PWE;                                                           /* 0x2F44 - 0x2F47 */
    uint8_t pad4[0x2F50 - 0x2F48];                                          /* 0x2F48 - 0x2F4F */
    uint32_t LVDSCTRLA;                                                     /* 0x2F50 - 0x2F43 */
    uint32_t LVDSCTRLB;                                                     /* 0x2F54 - 0x2F57 */
    uint8_t pad5[0x4000 - 0x2F58];                                          /* 0x2F58 - 0x3FFF */
    struct port_group_regset3 p_regset3[PLAT_MAX_NUM_PORT_GROUPS];          /* 0x4000 - 0x463F */
    uint8_t pad6[0x4C80 - 0x4640];                                          /* 0x4640 - 0x4C7F */
    struct analog_port_group_regset3 ap_regset3[PLAT_MAX_NUM_APORT_GROUPS]; /* 0x4C80 - 0x4DFF */
    uint8_t pad7[0x6000 - 0x4E00];                                          /* 0x4E00 - 0x5FFF */
    struct port_group_regset4 p_regset4[PLAT_MAX_NUM_PORT_GROUPS];          /* 0x6000 - 0x663F */
    uint8_t pad8[0x6C80 - 0x6640];                                          /* 0x6640 - 0x6C7F */
    struct analog_port_group_regset4 ap_regset4[PLAT_MAX_NUM_APORT_GROUPS]; /* 0x6C80 - 0x6DFF */
};

void port_init(void);

#endif /* __PLAT_PORT_H__ */
