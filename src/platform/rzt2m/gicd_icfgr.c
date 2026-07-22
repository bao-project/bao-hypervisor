/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <cpu.h>
#include <arch/gic.h>
#include <arch/gicv3.h>

#define BSP_PRV_ICFGR_MAX            (30U)

volatile struct gicd_hw* gicd_ptr;

static const uint32_t BSP_PRV_GICD_ICFGR_INIT[BSP_PRV_ICFGR_MAX] =
{
    0x0,                /* Padding */
    0x0,                /* Padding */
    0xAAAAAAAAUL,       /* Event No. 0 to 15    */
    0xAAAAA8AAUL,       /* Event No. 16 to 31   */
    0xAAAAAAAAUL,       /* Event No. 32 to 47   */
    0xAAAAAAAAUL,       /* Event No. 48 to 63   */
    0xAAAAAAAAUL,       /* Event No. 64 to 79   */
    0xAAAAAAAAUL,       /* Event No. 80 to 85   */
    0xAAAAAAAAUL,       /* Event No. 96 to 111  */
    0xAAAAAA00UL,       /* Event No. 112 to 127 */
    0xAAAAAAAAUL,       /* Event No. 128 to 143 */
    0xAAAAAAAAUL,       /* Event No. 144 to 159 */
    0xAAAAAAAAUL,       /* Event No. 160 to 175 */
    0xAAAAAAAAUL,       /* Event No. 176 to 191 */
    0xAAAAAAAAUL,       /* Event No. 192 to 207 */
    0xAAAAAAAAUL,       /* Event No. 208 to 223 */
    0xAAAAAAAAUL,       /* Event No. 224 to 239 */
    0x0000000AUL,       /* Event No. 240 to 255 */
    0x00000000UL,       /* Event No. 256 to 271 */
    0xA02A0000UL,       /* Event No. 272 to 287 */
    0x28282828UL,       /* Event No. 288 to 303 */
    0x00282828UL,       /* Event No. 304 to 319 */
    0xA82A0A00UL,       /* Event No. 320 to 335 */
    0xA0AA8020UL,       /* Event No. 336 to 351 */
    0x00000002UL,       /* Event No. 352 to 367 */
    0x00000000UL,       /* Event No. 368 to 383 */
    0xAAAA0AAAUL,       /* Event No. 384 to 399 */
    0xAAAAAAAAUL,       /* Event No. 400 to 315 */
    0x00AAAAAAUL,       /* Event No. 416 to 431 */
    0x828A0A2AUL        /* Event No. 432 to 447 */
};

void rzt2m_gicd_icfgr_init(void)
{
    vaddr_t tmp_gicd = mem_alloc_map_dev(&cpu()->as, SEC_HYP_PRIVATE,
        INVALID_VA, platform.arch.gic.gicd_addr, NUM_PAGES(sizeof(struct gicd_hw)));
    if (tmp_gicd == INVALID_VA) {
        ERROR("Maping GICD MMIO for platform initialization failed");
    }
    gicd_ptr = (void*)tmp_gicd;

    for (size_t i = 2; i < BSP_PRV_ICFGR_MAX; i++) {
        gicd_ptr->ICFGR[i] = BSP_PRV_GICD_ICFGR_INIT[i];
    }

    mem_unmap(&cpu()->as, (vaddr_t)platform.arch.gic.gicd_addr, 
        NUM_PAGES(sizeof(struct gicd_hw)), true);
}