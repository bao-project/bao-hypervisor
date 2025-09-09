/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <asm_defs.h>
#include <platform_defs.h>

.macro LOAD_ADDR    sym, reg
    movhi hi(\sym), r0, \reg
    movea lo(\sym), \reg, \reg
.endm

.data 
.balign 4
.global img_addr
img_addr: .4byte 0

.balign 4
.global data_addr
data_addr: .4byte PLAT_DATA_MEM

/**
 * 	The following code MUST be at the base of the image, as this is bao's entrypoint. Therefore
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

    /* store image load address in img_addr */
    LOAD_ADDR _image_start, r20
    LOAD_ADDR img_addr, r21
    st.w r20, 0[r21]

    stsr 0, r10, 2               /* get current CPU ID from PEID */

    mov CPU_MASTER_FIXED, r11   /* identify master cpu */
    /* TODO: Support for non-fixed master cpu*/

/*  TODO: Remove.
    This loop serves as a workaround for the fact that, when using e2studio to debug execution,
    all cores start executing simultaneously, instead of following the BOOTCTRL mechanism */
sync_loop:
    /* mov 3, r20
    cmp r10, r20
    be sync_loop
    mov 2, r20
    cmp r10, r20
    be sync_loop
    mov 1, r20
    cmp r10, r20
    be sync_loop */

    /* set PSW.EBV and PSW.ID */
    mov 0x8020, r20
    ldsr r20, 5, 0

    /* configure EBASE with exception vector */
    LOAD_ADDR _hyp_vector_table, r20
    ori 0x2, r20, r20   /* direct vector method */
    ldsr r20, 3, 1

    /* configure INTBP with interrupt vector */
    LOAD_ADDR _hyp_interrupt_table, r20
    ldsr r20, 4, 1

    /* clear MPM to disable memory protections */
    mov r0, r20
    ldsr r20, 0, 5

    /* configure protection setting check */
    ldsr r0, 8, 5   /* MCA = MCS = 0 covers all memory */
    ldsr r0, 9, 5
    ldsr r0, 12, 5  /* MCI = 0 */
    ldsr r0, 0, 1   /* CPU SPID = 0 */

    /* initialize mpu entries for bank 0 */
    /* TODO: Discover number of MPU banks */
    ldsr r0, 17, 5      /* set MPBK.BK = 0 */
    jarl _clear_mpu, lp

    /* initialize local RAM */
    /* TODO: use macros for platform addresses */
    mov 0xFDE00000, r20
    mov 0xFDE0FFFF, r21
    jarl _boot_clear, lp

    /* check if current CPU is CPU_MASTER */
    cmp r11, r10
    bne _clear_cpu
    /* bne _check_barrier */

    /* enable interrupt virtualization support,
    recommended at CPU initialization after reset */
    mov 0xFFFC402F0, r20
    mov 0x1, r21
    st.w r21, 0[r20]    /* IHVCFG.IHVE = 0x1 */

    /* initialize cluster RAM */
    /* TODO: use macros for platform addresses */
    mov 0xFE000000, r15
    mov 0xFE07FFFF, r16
    jarl _boot_clear, lp

    mov 0xFE100000, r15
    mov 0xFE17FFFF, r16
    jarl _boot_clear, lp

    mov 0xFE400000, r15
    mov 0xFE5FFFFF, r16
    jarl _boot_clear, lp

    mov 0xFE800000, r15
    mov 0xFE83FFFF, r16
    jarl _boot_clear, lp
   
    /* copy non-text sections from flash to ram */
    LOAD_ADDR _data_lma_start, r15
    LOAD_ADDR _image_load_end, r16
    mov PLAT_DATA_MEM, r17
    jarl _copy_data, lp 

    /* clear .bss in ram */
    LOAD_ADDR _image_noload_start, r15
    LOAD_ADDR _image_end, r16
    jarl _boot_clear, lp

    /* store CPU_MASTER */
    LOAD_ADDR CPU_MASTER, r20
    st.w r11, 0[r20]

/*
_check_barrier:
    # Initialize CPU barrier
    ## Write 0x3 to BR0EN
    mov 0xFFFB8004, r20
    mov 0x3, r21 # TODO: create macro for BR0EN macro
    st.b r21, 0[r20]
    # ## Write 0x1 to BR0INIT
    # mov 0xFFFB8000, r20
    # mov 0x1, r21
    # st.b r21, 0[r20]
    ## Write 0x1 to BR0CHKS
    mov 0xFFFB8100, r20
    mov 0x1, r21
    st.b r21, 0[r20]

_poll_barrier:
    # Poll BR0SYNCS
    mov 0xFFFB8104, r20
    ld.bu 0[r20], r21
    cmp r0, r21
    be _poll_barrier
*/

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
    LOAD_ADDR init, r5

    br init


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
 * uses r18
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
_clear_mpu_1:
    mov 32, r16     /* TODO: discover number of MPU entries */
    cmp r15, r16
    be _clear_mpu_exit

    ldsr r15, 16, 5 /* set MPIX */

    ldsr r0, 20, 5  /* clear MPLA */
    ldsr r0, 21, 5  /* clear MPUA */
    ldsr r0, 22, 5  /* clear MPAT */

    addi 1, r15, r15
    bne _clear_mpu_1
_clear_mpu_exit:
    jmp [lp]
