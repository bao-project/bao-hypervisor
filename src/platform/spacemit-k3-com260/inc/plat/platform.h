/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

/* K3 UART0: 16550-compatible, 32-bit registers (reg-shift=2, reg-io-width=4),
 * registers start at the page base (no page offset). */
#define UART8250_REG_WIDTH (4)

#include <drivers/8250_uart.h>

/*
 * CPU extensions the X100 (cpu@0-7) harts implement, from the vendor DT
 * riscv,isa = "rv64imafdcvh" + isa-extensions (smaia, ssaia, smstateen, sstc,
 * sdtrig, ...). Bao only acts on the ones it tracks; defining them makes the
 * hypervisor handle guest state correctly. CRITICAL: the whole hstateen
 * state-enable block in vmm.c (which grants VS-mode guests access to the
 * AIA/IMSIC indirect CSRs they need) is gated on CPU_EXT_SSSTATEEN, and its AIA
 * path requires CPU_EXT_SSCSRIND.
 */
#define CPU_EXT_F         1 /* f + d: guest uses the FPU (sstatus.FS), so Bao must ctx-switch it */
#define CPU_EXT_V         1 /* v: vector unit (sstatus.VS), so Bao must ctx-switch it */
#define CPU_EXT_ZICBOM    1 /* cbo.clean/flush/inval - Linux uses these for DMA cache mgmt */
#define CPU_EXT_ZICBOZ    1 /* cbo.zero */
#define CPU_EXT_SSTC      1 /* per-hart supervisor timer (sstc) */
#define CPU_EXT_SSSTATEEN 1 /* smstateen + H => hstateen CSRs (enables the vmm.c block) */
#define CPU_EXT_SSCSRIND  1 /* indirect CSRs (siselect/sireg) - required by Ssaia/AIA */
#define CPU_EXT_SDTRIG    1 /* sdtrig (debug triggers / scontext) */

#define IPIC_SBI     (1)
#define IPIC_ACLINT  (2)

#endif
