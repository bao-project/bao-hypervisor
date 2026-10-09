/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_CPU_EXT_H__
#define __PLAT_CPU_EXT_H__

/*
 * EIC7700X: 4x SiFive P550, riscv,isa =
 * "rv64imafdch_zicsr_zifencei_zba_zbb_sscofpmf" (vendor DT). Define only the
 * tracked extensions the P550 has. The critical absentee is Sstc: no stimecmp,
 * and the envcfg CSRs are pre-1.12 so they trap (see RISCV_PRIV_VERSION).
 * Svpbmt/Zicbom/Zicboz/V/Smstateen/AIA/Sdtrig are also absent and left
 * undefined (CPU_HAS_EXTENSION -> 0).
 */
#define CPU_EXT_SSTC 0

#define CPU_EXT_F    1 /* f+d: guests use the FPU; Bao enables FS in (v)sstatus */

#endif
