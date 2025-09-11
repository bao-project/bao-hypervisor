/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <asm_defs.h>
#include <platform_defs.h>
#include <plat/platform.h>

.macro LOAD_ADDR    sym, reg
    movhi hi(\sym), r0, \reg
    movea lo(\sym), \reg, \reg
.endm

.extern platform

/**
 * The following code MUST be at the base of the image, as this is bao's entrypoint. Therefore
 * .boot section must also be the first in the linker script. DO NOT implement any code before the
 * _reset_handler in this section.
 */
 .section ".boot", "ax"
.global _reset_handler
_reset_handler:

    /**
     * Not following any ABI for registers in this boot code.
     * The following registers are however reserved to be passed to main
     * as arguments:
     *     r6 -> CPU ID
     *
     * Register r10 is reserved to hold the CPU ID
     * Register r11 is reserved to hold the master CPU ID
     * Register r12 is reserved to hold the CPU struct size
     * Register r13 is reserved to hold the CPU struct pointer
     * Register r31 is reserved as link pointer when calling a routine
     *
     * The remaining code must use r20-r29 as scratchpad registers in the main
     * flow and r15-r19 as arguments and return values. r10-r14 are used to hold constants.
     */

    di  /* Disable interrupts */

    stsr 0, r10, 2               /* get current CPU ID from PEID */

    mov CPU_MASTER_FIXED, r11   /* identify master cpu */

    /* set PSW.EBV and PSW.ID */
    mov 0x8020, r20
    ldsr r20, 5, 0

    /* configure EBASE with exception vector */
    LOAD_ADDR _hyp_vector_table, r20
    ori 0x2, r20, r20   /* direct vector method */
    ldsr r20, 3, 1

    /* clear MPM to disable memory protections */
    mov r0, r20
    ldsr r20, 0, 5

    /* configure protection setting check */
    ldsr r0, 8, 5   /* MCA = MCS = 0 covers all memory */
    ldsr r0, 9, 5
    ldsr r0, 12, 5  /* MCI = 0 */
    ldsr r10, 0, 1  /* set SPID = CPU ID */

    /* initialize mpu entries for bank 0 */
    /* TODO: Discover number of MPU banks */
    ldsr r0, 17, 5      /* set MPBK.BK = 0 */
    jarl _clear_mpu, lp

    /* enable interrupt virtualization support,
    recommended at CPU initialization after reset */
    mov PLAT_INTC1_ADDR, r20
    mov 0x1, r21
    st.w r21, PLAT_INTC1_IHVCFG_OFFSET[r20]    /* IHVCFG.IHVE = 0x1 */

    /* check if current CPU is CPU_MASTER */
    cmp r11, r10
    bne _clear_cpu
    /* initialize RAM defined in plat desc */
    LOAD_ADDR platform, r15
    LOAD_ADDR _data_vma_start, r16
    LOAD_ADDR _data_lma_start, r17
    jarl clear_rwx_regions, lp

    /* copy non-text sections from flash to ram */
    LOAD_ADDR _data_lma_start, r15
    LOAD_ADDR _image_load_end, r16
    mov PLAT_DATA_ADDR, r17
    jarl _copy_data, lp

    /* clear .bss in ram */
    LOAD_ADDR _image_noload_start, r15
    LOAD_ADDR _image_end, r16
    jarl _boot_clear, lp

    /* store image load address in img_addr */
    LOAD_ADDR _image_start, r20
    LOAD_ADDR img_addr, r21
    st.w r20, 0[r21]

    /* store data section address in data_addr */
    mov PLAT_DATA_ADDR, r20
    LOAD_ADDR data_addr, r21
    st.w r20, 0 [r21]

_clear_cpu:
    /* clear CPUn struct */
    LOAD_ADDR _image_end, r20
    mov CPU_SIZE, r12
    mov r10, r21
    mulh r12, r21   /* cpu struct offset */
    add r21, r20    /* end of .bss + cpu struct offset = r20 points to cpu */
    mov r20, r13    /* r13 holds the CPU pointer */
    mov r13, r15
    mov r13, r16
    add r12, r16
    jarl _boot_clear, lp

    ldsr r13, 29, 0 /* use FEWR as CPU* pointer holder */

    /* Initialize stack pointer */
    mov CPU_STACK_OFF, r20
    add r13, r20
    mov CPU_STACK_SIZE, r21
    add r21, r20
    mov r20, sp

    /* Set init arguments */
    mov r10, r6     /* copy CPU ID to r6 */

    jr init

/**
 * Clear RWX memory regions defined in platform
 * r15 = plat_vma   (pointer value as linked for VMA)
 * r16 = data_vma   (start of .data at VMA)
 * r17 = data_lma   (start of .data at LMA)
 */
clear_rwx_regions:
    /* Compute delta = data_lma - data_vma  (r20 = delta) */
    mov     r17, r20
    sub     r16, r20              /* r20 = r17 - r16 */

    /* Convert platform pointer to LMA: plat_lma = plat_vma + delta (r20) */
    mov     r15, r21
    add     r20, r21             /* r21 = r15 + delta */

    /* Load region_num (use r24 as loop counter) */
    ld.w    PLATFORM_REGION_NUM_OFF[r21], r24
    cmp     r0, r24
    be      _done                /* if (region_num == 0) return */

    /* Load regions pointer (stored as VMA pointer), convert to LMA */
    ld.w    PLATFORM_REGIONS_PTR_OFF[r21], r18   /* r18 = regions_vma */
    add     r20, r18                         /* r18 = regions_lma */

    /* r25 = sizeof(struct mem_region) */
    mov     MEM_REGION_SIZEOF, r25

_loop_region:
    /* region->perms */
    ld.w    MEM_REGION_PERMS_OFF[r18], r26
    /* Assumes RWX permission is 0x0 */
    cmp     r0, r26
    bne     _skip_clear           /* perms != MEM_RWX => skip */

    /* region->base and region->size */
    ld.w    MEM_REGION_BASE_OFF[r18], r22    /* r22 = base */
    ld.w    MEM_REGION_SIZE_OFF[r18], r23    /* r23 = size */
    cmp     r0, r23
    be      _skip_clear

    /* end = base + size */
    add     r22, r23              /* r23 = end */

    /* Clear [r12, r13) */
    br      _clear_rwx_range

_skip_clear:
    /* next region struct */
    add     r25, r18

    /* decrement count and loop */
    addi    -1, r24, r24
    cmp     r0, r24
    bne     _loop_region

_done:
    jmp     [lp]

/**
 * Clears words between [r22, r23[
 * r22 = start
 * r23 = end
 */
_clear_rwx_range:
    cmp     r22, r23
    be      _cr_done
    st.w    r0, 0[r22]
    addi    4, r22, r22
    br      _clear_rwx_range

_cr_done:
    br      _skip_clear



/**
 * Clear from [r15] to [r16]
 * r15: start of region
 * r16: end of region
 */
_boot_clear:
    cmp r16, r15
    bge _boot_clear_exit
    st.w r0, 0[r15]
    addi 4, r15, r15
    br _boot_clear
_boot_clear_exit:
    jmp [lp]


/**
 * Copy contents from [r15] until [r16] to [r17]
 * r15: start of the source region
 * r16: end of the source region
 * r17: start of the destination region
 */
_copy_data:
    ld.w 0[r15], r18
    st.w r18, 0[r17]
    addi 4, r15, r15
    addi 4, r17, r17
    cmp r15, r16
    bne _copy_data
    jmp [lp]

/**
 * Clear MPU SRs
 * Uses r15, r16
 */
_clear_mpu:
    mov r0, r15
    stsr 2, r16, 5      /* r16 = MPCFG (SR2, sel 5) */
    andi 0x1F, r16, r16 /* r16 = NMPUE (bits 4..0) */
    addi 1, r16, r16    /* r16 = NMPUE + 1 = entry count */
_clear_mpu_1:
    cmp r15, r16
    be _clear_mpu_exit

    ldsr r15, 16, 5 /* set MPIX */

    ldsr r0, 20, 5  /* clear MPLA */
    ldsr r0, 21, 5  /* clear MPUA */
    ldsr r0, 22, 5  /* clear MPAT */

    addi 1, r15, r15
    br _clear_mpu_1
_clear_mpu_exit:
    jmp [lp]
