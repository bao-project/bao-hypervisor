/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_PBG_H__
#define __PLAT_PBG_H__

#include <platform.h>

#define PLAT_NUM_PBG_CHANNELS (16)

#define PLAT_PBG_BASE         (0xFF0A1300UL)

#define PBGKCPROT_ENABLE_WR   (0xA5A5A501UL)
#define PBGKCPROT_DISABLE_WR  (0xA5A5A500UL)

struct pbg_channel {
    uint32_t PBGPROT0;
    uint32_t PBGPROT1;
};

struct pbgn {
    struct pbg_channel ch[PLAT_NUM_PBG_CHANNELS];
};

struct pbgerrslvn {
    uint32_t PBGOVFCLR;
    uint32_t PBGOVFSTAT;
    uint32_t PBGRRADDR;
    uint32_t PBGRRTYPE;
    uint32_t PBGSPIDERRCLR;
    uint32_t PBGSPIDERRSTAT;
    uint32_t PBGKCPROT;
};

struct pbg_hw {
    struct pbgn PBG90;
    uint8_t pad0[0xFF0A1400 - 0xFF0A1380];
    struct pbgerrslvn PBGERRSLV90;
    uint8_t pad1[0xFF751000 - 0xFF0A141C];
    struct pbgn PBG6H0;
    uint8_t pad2[0xFF752000 - 0xFF751080];
    struct pbgerrslvn PBGERRSLV6H0;
    uint8_t pad3[0xFFC63000 - 0xFF75201C];
    struct pbgn PBG10;
    uint8_t pad4[0xFFC63100 - 0xFFC63080];
    struct pbgerrslvn PBGERRSLV10;
    uint8_t pad5[0xFFC6B000 - 0xFFC6311C];
    struct pbgerrslvn PBGERRSLV00;
    uint8_t pad6[0xFFC6B080 - 0xFFC6B01C];
    struct pbgn PBG00;
    struct pbgn PBG01;
    uint8_t pad7[0xFFC72B00 - 0xFFC6B180];
    struct pbgn PBG30;
    uint8_t pad8[0xFFC72C00 - 0xFFC72B80];
    struct pbgn PBG31;
    uint8_t pad9[0xFFC72D00 - 0xFFC72C80];
    struct pbgn PBG32;
    uint8_t pad10[0xFFC72E00 - 0xFFC72D80];
    struct pbgn PBG33;
    uint8_t pad11[0xFFC73200 - 0xFFC72E80];
    struct pbgerrslvn PBGERRSLV30;
    uint8_t pad12[0xFFC75300 - 0xFFC7321C];
    struct pbgn PBG40;
    uint8_t pad13[0xFFC75400 - 0xFFC75380];
    struct pbgerrslvn PBGERRSLV40;
    uint8_t pad14[0xFFC7A300 - 0xFFC7541C];
    struct pbgn PBG50;
    uint8_t pad15[0xFFC7A400 - 0xFFC7A380];
    struct pbgn PBG51;
    uint8_t pad16[0xFFC7A500 - 0xFFC7A480];
    struct pbgn PBG52;
    uint8_t pad17[0xFFC7A600 - 0xFFC7A580];
    struct pbgn PBG53;
    uint8_t pad18[0xFFC7B000 - 0xFFC7A680];
    struct pbgerrslvn PBGERRSLV50;
    uint8_t pad19[0xFFC81000 - 0xFFC7B01C];
    struct pbgn PBG6L0;
    uint8_t pad20[0xFFC81200 - 0xFFC81080];
    struct pbgn PBG6L1;
    uint8_t pad21[0xFFC83000 - 0xFFC81280];
    struct pbgerrslvn PBGERRSLV6L0;
    uint8_t pad22[0xFFC83040 - 0xFFC8301C];
    struct pbgerrslvn PBGERRSLV6L1;
    uint8_t pad23[0xFFDE0B00 - 0xFFC8305C];
    struct pbgn PBG20;
    uint8_t pad24[0xFFDE0C00 - 0xFFDE0B80];
    struct pbgn PBG21;
    uint8_t pad25[0xFFDE0D00 - 0xFFDE0C80];
    struct pbgn PBG22;
    uint8_t pad26[0xFFDE1000 - 0xFFDE0D80];
    struct pbgerrslvn PBGERRSLV20;
    uint8_t pad27[0xFFF29300 - 0xFFDE101C];
    struct pbgn PBG80;
    uint8_t pad28[0xFFF2A000 - 0xFFF29380];
    struct pbgerrslvn PBGERRSLV80;
    uint8_t pad29[0xFFF49400 - 0xFFF2A01C];
    struct pbgn PBG70;
    uint8_t pad30[0xFFF4A000 - 0xFFF49480];
    struct pbgerrslvn PBGERRSLV70;
};

void pbg_init(void);

#endif /* __PLAT_PBG_H__ */
