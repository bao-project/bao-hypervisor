/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <cpu.h>
#include <mem.h>

/************************** Master MPU Configuration **************************/

// #define RZ_BASE_MPUi          0x81281100u   // MPUi base: 0x8128_1100 + 0x0100*i  (i = 0..4,6)
// #define RZ_MPUi_STRIDE        0x00000100u   // stride entre MPUs
// #define RZ_MPU_OFF_STADD(m)   (0x00u + 0x10u*(m))
// #define RZ_MPU_OFF_ENDADD(m)  (0x04u + 0x10u*(m))
// #define RZ_MPU_OFF_ERRINF     0x80u         // ERRINF / ERRINF_R
// #define RZ_MPU_OFF_ERRINFW    0x84u         // ERRINF_W (AXI)

// #define RZ_RWP_S_PRCRS        (*(volatile uint32_t*)0x81281A00u) // PRCRS (safety) + PRKEY
// #define PRCRS_PRKEY(key)      ((uint32_t)(0xA5u << 8) | (key))
// #define PRCRS_PRC3            (1u << 3)     // habilita escrita em “system control” (inclui Master-MPU regs)

// // Masters (i) conforme o manual (Tabela 12.3): AXI: 0=DMAC0,1=DMAC1,2=GMAC,6=CoreSight; AHB: 3=USB Host, 4=USB Func
// #define MPU_I_DMAC0   0
// #define MPU_I_DMAC1   1
// #define MPU_I_GMAC    2
// #define MPU_I_USBH    3   // AHB
// #define MPU_I_USBF    4   // AHB
// #define MPU_I_DBGAXI  6

// // Máscara por conveniência
// #define MPU_MASK_DMAC0  (1u << MPU_I_DMAC0)
// #define MPU_MASK_DMAC1  (1u << MPU_I_DMAC1)
// #define MPU_MASK_GMAC   (1u << MPU_I_GMAC)
// #define MPU_MASK_USBH   (1u << MPU_I_USBH)
// #define MPU_MASK_USBF   (1u << MPU_I_USBF)
// #define MPU_MASK_DBGAXI (1u << MPU_I_DBGAXI)
// // #define MPU_MASK_ALL    (MPU_MASK_DMAC0|MPU_MASK_DMAC1|MPU_MASK_GMAC|MPU_MASK_USBH|MPU_MASK_USBF|MPU_MASK_DBGAXI)

// // util: escreve STADD/ENDADD com RDPR/WRPR=1
// static inline void mpu_write_region(uint32_t mpu_i, uint32_t region_m,
//                                     uint32_t start, uint32_t end, bool axi)
// {
//     volatile uint32_t* STADDm  = (uint32_t*)(RZ_BASE_MPUi + RZ_MPUi_STRIDE*mpu_i + RZ_MPU_OFF_STADD(region_m));
//     volatile uint32_t* ENDADDm = (uint32_t*)(RZ_BASE_MPUi + RZ_MPUi_STRIDE*mpu_i + RZ_MPU_OFF_ENDADD(region_m));

//     // Campos STADDR/ENDADDR são [31:10]; HW força [9:0] a 0 (start) e 1 (end)
//     uint32_t st = (start >> 10);
//     uint32_t en = (end   >> 10);

//     if (axi) {
//         // AXI exige STADDR[1:0]=00 e ENDADDR[1:0]=11
//         st = (st & ~0x3u) | 0x0u;
//         en = (en & ~0x3u) | 0x3u;
//     }

//     // RDPR=bit0, WRPR=bit1
//     *STADDm  = (st << 10) | (1u<<0) | (1u<<1);
//     *ENDADDm = (en << 10);
// }

// // checagens de alinhamento para AXI/AHB (AXI=4KB, AHB=1KB)
// static inline bool is_axi_aligned(uint32_t start, uint32_t end) {
//     return ((start & 0xFFFu) == 0) && ((end & 0xFFFu) == 0xFFFu);
// }
// static inline bool is_ahb_aligned(uint32_t start, uint32_t end) {
//     return ((start & 0x3FFu) == 0) && ((end & 0x3FFu) == 0x3FFu);
// }

// /**
//  * Bloqueia [start,end] para os masters selecionados em 'masters_mask',
//  * usando a região 'region_m' (0..7) de cada MPUi.
//  * Retorna 0 se OK, <0 se erro de alinhamento.
//  *
//  * Nota: region_m=1 é uma boa prática para deixar m=0 para a default.
//  */
// int master_mpu_block_region(uint32_t start, uint32_t end,
//                             uint32_t masters_mask, uint32_t region_m);
//  int master_mpu_block_region(uint32_t start, uint32_t end,
//                             uint32_t masters_mask, uint32_t region_m)
// {
//     if (start > end) return -1;

//     // Abrir proteção de escrita (PRCRS.PRC3=1 com PRKEY=0xA5)
//     RZ_RWP_S_PRCRS = PRCRS_PRKEY(PRCRS_PRC3);
//     // Programar AXI MPUs: i = 0,1,2,6 (precisam 4KB)
//     if (masters_mask & (MPU_MASK_DMAC0|MPU_MASK_DMAC1|MPU_MASK_GMAC|MPU_MASK_DBGAXI)) {
//         if (!is_axi_aligned(start, end)) {
//             RZ_RWP_S_PRCRS = PRCRS_PRKEY(0x0); // fechar
//             return -2; // desalinhado p/ AXI
//         }
//         if (masters_mask & MPU_MASK_DMAC0)  mpu_write_region(MPU_I_DMAC0,  region_m, start, end, true);
//         if (masters_mask & MPU_MASK_DMAC1)  mpu_write_region(MPU_I_DMAC1,  region_m, start, end, true);
//         if (masters_mask & MPU_MASK_GMAC)   mpu_write_region(MPU_I_GMAC,   region_m, start, end, true);
//         if (masters_mask & MPU_MASK_DBGAXI) mpu_write_region(MPU_I_DBGAXI, region_m, start, end, true);
//     }
//     // Programar AHB MPUs: i = 3,4 (1KB)
//     if (masters_mask & (MPU_MASK_USBH|MPU_MASK_USBF)) {
//         if (!is_ahb_aligned(start, end)) {
//             RZ_RWP_S_PRCRS = PRCRS_PRKEY(0x0); // fechar
//             return -3; // desalinhado p/ AHB
//         }
//         if (masters_mask & MPU_MASK_USBH) mpu_write_region(MPU_I_USBH, region_m, start, end, false);
//         if (masters_mask & MPU_MASK_USBF) mpu_write_region(MPU_I_USBF, region_m, start, end, false);
//     }

//     // Fechar proteção de escrita
//     //RZ_RWP_S_PRCRS = PRCRS_PRKEY(0x0);
//     return 0;
// }

// /* opcional: helper para limpar “VALID” nas ERRINF_x e ler último endereço */
// static inline void master_mpu_clear_err(uint32_t mpu_i, bool axi)
// {
//     volatile uint32_t* ERR = (uint32_t*)(RZ_BASE_MPUi + RZ_MPUi_STRIDE*mpu_i + RZ_MPU_OFF_ERRINF);
//     if (axi) {
//         volatile uint32_t* ERRW = (uint32_t*)(RZ_BASE_MPUi + RZ_MPUi_STRIDE*mpu_i + RZ_MPU_OFF_ERRINFW);
//         (void)*ERR;   // leitura opcional
//         (void)*ERRW;
//         // limpar VALID escrevendo 0
//         *(volatile uint32_t*)ERR  = 0;
//         *(volatile uint32_t*)ERRW = 0;
//     } else {
//         (void)*ERR;
//         *(volatile uint32_t*)ERR = 0;
//     }
// }

// static void reset_cpu1(void){

//     // Disable write protection for low-power/reset registers (PRC1)
//     R_RWP_NS->PRCRN |= (RWP_PRCR_PRKEY | RWP_PRCR_PRC1);
//     R_RWP_S->PRCRS  |= (RWP_PRCR_PRKEY | RWP_PRCR_PRC1);

//     // Trigger reset in CPU1 without auto-release
//     R_SYSC_S->SWRCPU1 = SWR_RESET_NO_RELEASE;
//     // Confirm CPU1 reset
//     if(R_SYSC_NS->RSTSR0_b.SWR1F != 1) {
//         ERROR("CPU1 reset failed\n");
//     }

//     // Re-enable write protection for low-power/reset registers (PRC1)
//     R_RWP_NS->PRCRN = ((R_RWP_NS->PRCRN | RWP_PRCR_PRKEY) & (~RWP_PRCR_PRC1 & 0x7U));
//     R_RWP_S->PRCRS  = ((R_RWP_S->PRCRS | RWP_PRCR_PRKEY) & (~RWP_PRCR_PRC1 & 0xFU));
// }

void platform_default_init(void) { 

    if (cpu_is_master()) {

        /* Enable peripheral port (LLPP) for EL2 and EL1/0 */
        __asm volatile (
        "LLPP_access_enable:                      \n"
        "    MRC   p15, #0, r1, c15, c0,#0        \n"
        "    ORR   r1, r1, #(0x1 << 1)            \n"
        "    ORR   r1, r1, #(0x1)                 \n"
        "    DSB                                  \n"
        "    MCR   p15, #0, r1, c15, c0,#0        \n"
        "    ISB                                  \n"
        ::: "memory");

        /* Map peripheral MMIO regions for platform initialization */
        vaddr_t periph_mmio = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE, INVALID_VA,
            (paddr_t)PLAT_PERIPHERAL_MEM_BASE, NUM_PAGES(PLAT_PERIPHERAL_MEM_SIZE));
        if (periph_mmio == INVALID_VA) {
            ERROR("Maping peripheral MMIO failed");
        }

        // Initialize clocks
        rzt2m_clock_init();

        // Configure IO ports
        rzt2m_ioport_open();

        mem_unmap(&cpu()->as, (vaddr_t)PLAT_PERIPHERAL_MEM_BASE, 
            NUM_PAGES(PLAT_PERIPHERAL_MEM_SIZE), true);

        /* GICD ICFGR initialization */
        rzt2m_gicd_icfgr_init();

        /* System Counter initialization */
        rzt2m_cnt_init();
    }
}
