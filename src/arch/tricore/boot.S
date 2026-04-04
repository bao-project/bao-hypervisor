/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/csfrs.h>
#include <asm_defs.h>
#include <config_defs.h>
#include <platform_defs.h>
#include <arch/csa.h>

.macro load_32bit_val_a ra, label
    movh.a \ra, hi:\label
    lea    \ra, [\ra]lo:\label
.endm

.macro load_32bit_val_d rd, label
    movh   \rd, hi:\label
    addi   \rd, \rd, lo:\label
.endm

/**
 * barrier is used to minimal synchronization in boot - other cores wait for bsp to set it.
 */
.pushsection .datanocopy
.balign 4
_barrier: .4byte 0

/**
 * _master_set is used to ensure correct master cpu initialization
 */
 .pushsection .datanocopy
 .balign 4
_master_set: .4byte 0
/**
 *  The following code MUST be at the base of the image, as this is bao's entry point. Therefore
 * .boot section must also be the first in the linker script. DO NOT implement any code before the
 * _reset_handler in this section.
 */
 .section ".boot", "ax"
.globl _reset_handler
_reset_handler:

    /**
     * The following registers are however reserved to be passed to main
     * as arguments, these are calculated at the end:
     *     d0 -> contains cpu id
     *     d1 -> contains image base load address
     * Internal logic:
     * Register d14 is reserved to indicate if the current CPU is master (negated)
     * a14 -> pointer to cpu struct
     * Intended ABI:
     *      a12-a13 -> sub-routine use
     *      d10-d13 -> sub-routine use
     *      d2-d7 -> main flow
     *      a2-a7 -> main flow
     */

    /* Read core ID */
    mfcr    %d0,$core_id
    and     %d0,%d0,COREID_CORE_MASK


    /*
     * Install vector table physical address early, in case exception occurs during this
     * initialization.
     */

    load_32bit_val_d %d3, _trap_vector_table
    mtcr    $btv,%d3

    load_32bit_val_d %d3, _hyp_vector_table
    mtcr    CSFR_BHV,%d3

    load_32bit_val_d %d3, _irq_vector
    mtcr    $biv,%d3
    isync

    /* Force MPU disable */
    mov %d3, 0
    mtcr CSFR_CORECON, %d3

    jl platform_init_mem

#if defined(CPU_MASTER_FIXED)
    load_32bit_val_a %a4, CPU_MASTER
    load_32bit_val_d %d3, CPU_MASTER_FIXED
    st.w     [%a4], %d3
#else
    load_32bit_val_a %a5, _master_set
    ld.w %d3, [%a5]
    jnz %d3, 1f
    load_32bit_val_a %a4, CPU_MASTER
    st.w     [%a4], %d0
    mov      %d3, 1
    st.w     [%a5], %d3
1:
#endif

    jl disable_watchdogs

    /* Invalidate Caches */
    mov     %d3, 1 /* invalidate data cache */
    mtcr    CSFR_DCON1, %d3

    mov     %d3, 3 /* invalidate program cache and program buffer */
    mtcr    CSFR_PCON1, %d3
    isync

    mov %d3, 2
    /* Data cache bypass. */
    /* Data cache is disable because there is no coherency between cores */
    mtcr CSFR_DCON0, %d3

    mov %d3, 0
    /* Program cache enable */
    mtcr CSFR_PCON0, %d3

    isync


    /* Clear stack pointer to avoid unaligned SP exceptions during boot */
    mov     %d3, 0
    mov.a   %sp, %d3

    /* CPU physical based address */
    load_32bit_val_d    %d3, _dmem_beg

    /* CPU_X physical base address */
    mov     %d4, CPU_SIZE
    madd    %d3, %d3, %d0, %d4

    mov.a %a8, %d3

    /* Clear the CPU struct */
    mov.a   %a12, %d3   //start of CPU struct
    add     %d3, %d4   //end of CPU struct
    mov.a   %a13, %d3

    mov.aa     %a14, %a8 /* a14 will contain pointer to CPU struct */

#ifdef MEM_NON_UNIFIED
    load_32bit_val_a %a4, CPU_MASTER
    ld.w %d4, [%a4]
    jne     %d4, %d0, 1f
        /* Copy data from RX to RWX */
    load_32bit_val_a    %a12, _data_lma_start // LMA start
    load_32bit_val_a    %a13, _data_vma_start // VMA start
    load_32bit_val_d    %d5, _data_vma_end // LMA end
    jl copy_data
1:
#endif
    /**
     * Get base image load address.
     */
    load_32bit_val_d %d1, _reset_handler
    load_32bit_val_a %a4, img_addr
    st.w [%a4], %d1

    load_32bit_val_d %d1, _data_vma_start
    load_32bit_val_a %a4, data_addr
    st.w [%a4], %d1

1:
    isync

    mov %d3, 0
    /* make sure no region can be accessed, executed */
    mtcr    CSFR_DPRE_0, %d3
    mtcr    CSFR_DPRE_1, %d3
    mtcr    CSFR_DPRE_2, %d3
    mtcr    CSFR_DPRE_3, %d3
    mtcr    CSFR_DPRE_4, %d3
    mtcr    CSFR_DPRE_5, %d3
    mtcr    CSFR_DPRE_6, %d3
    mtcr    CSFR_DPRE_7, %d3

    mtcr    CSFR_DPWE_0, %d3
    mtcr    CSFR_DPWE_1, %d3
    mtcr    CSFR_DPWE_2, %d3
    mtcr    CSFR_DPWE_3, %d3
    mtcr    CSFR_DPWE_4, %d3
    mtcr    CSFR_DPWE_5, %d3
    mtcr    CSFR_DPWE_6, %d3
    mtcr    CSFR_DPWE_7, %d3

    mtcr    CSFR_CPXE_0, %d3
    mtcr    CSFR_CPXE_1, %d3
    mtcr    CSFR_CPXE_2, %d3
    mtcr    CSFR_CPXE_3, %d3
    mtcr    CSFR_CPXE_4, %d3
    mtcr    CSFR_CPXE_5, %d3
    mtcr    CSFR_CPXE_6, %d3
    mtcr    CSFR_CPXE_7, %d3

    isync

    /* If this is the cpu master, clear bss */
    load_32bit_val_a %a4, CPU_MASTER
    ld.w %d4, [%a4]
    jne     %d4, %d0, 1f
    load_32bit_val_a %a12, _bss_start
    load_32bit_val_a %a13, _bss_end

    jl      boot_clear

    load_32bit_val_a %a5, _barrier
    mov     %d7, 1
    st.w    [%a5],%d7

1:
    /* wait for bsp to finish clearing bss */
    load_32bit_val_a %a5, _barrier
2:
    ld.w    %d8, [%a5]
    jlt     %d8, 1, 2b

    dsync

    /* initialize context save areas */
    jl    _init_csa

    /* reset access to system global registers */
    mfcr    %d3,$psw
    or      %d3,%d3,0x100               // clear GW bit
    mtcr    $psw,%d3
    isync

    /* Initialize stack pointer */
    mov.d   %d4, %a14

    load_32bit_val_d %d5, (CPU_STACK_OFF + CPU_STACK_SIZE)
    add     %d4, %d4, %d5

    mov.a   %sp, %d4

    mov %d4, %d0
    mov %d5, %d1


    j       init

    /* This point should never be reached */
oops:
    j       oops

/*****  Helper functions for boot code. ******/

.global boot_clear
/* A12 contains the start position and A13 the end position.
   this functions clears the memory between A12 and A13 */
boot_clear:
    mov     %d10, 0 //zero
    mov.d   %d11, %a13 //d11 = end of loop
    mov     %d12, 4  //d12 = increment value
    mov.d   %d13, %a12 // d13 = current position
2:
    st.w    [%a12],%d10
    jge     %d13, %d11, 1f
    add     %d13, %d13, %d12
    mov.a   %a12,  %d13
    j       2b
1:
    ji      %a11


/* Copies data from a12 to a13 up to the d5 limit */
.global copy_data
copy_data:
1:
    ld.w %d3, [%a12]
    st.w [%a13], %d3
    mov.d %d3, %a13
    jge  %d3, %d5, 2f
    add.a %a12, 4
    add.a %a13, 4
    j 1b
2:
    ji      %a11

.global    _init_csa
_init_csa:
    movh    %d10,0
    mtcr    CSFR_PCXI,%d10               // previous context info is null
    isync

    // %d10 = begin of CSA
    load_32bit_val_d %d10, csa_array

    mov     %d11, CSA_ENTRIES
    mul     %d12, %d11, 64
    madd    %d10, %d10, %d0, %d12

    /* Initialize first CSA */
    mov.a   %a12,%d10                 // %a12 = address of first CSA
    extr.u  %d10,%d10,28,4            // %d10 = segment (4 msb)
    sh      %d10,%d10,16              // %d10 = segment << 16

    mov.aa  %a13,%a12                 // %a13 = current CSA
    lea     %a12,[%a12]64             // %a12 = %a12->nextCSA

    mov.d   %d12,%a12
    extr.u  %d12,%d12,6,16            // get CSA index
    or      %d12,%d12,%d10             // add segment number
    mtcr    $fcx,%d12                // initialize FCX

    add     %d11,%d11,-2              // CSAs to initialize -= 2
    mov.a   %a7,%d11                 // %a7 = loop counter

csa_loop:
    add     %d12, %d12, 1
    st.w    [%a12],%d12               // store "nextCSA" pointer
    mov.aa  %a13,%a12                 // %a13 = current CSA address
    lea     %a12,[%a12]64             // %a12 = %a3->nextCSA
    loop    %a7,csa_loop            // repeat until done

    mov %d10, 0
    st.w [%a12], %d10
    add     %d12, %d12, -1
    mtcr    $lcx,%d12                // initialize LCX

    isync
    ji      %a11

#define WDTSYS_CRTLA    0xF00001A8
#define WDTSYS_CRTLB    0xF00001AC
#define WDTCPUy_CTRLA   0xF000003C
#define WDTCPUy_CTRLB   0xF0000040
#define WDT_PASSWORD_UNLOCK 0xF8
#define WDT_PASSWORD_LOCK 0xF9

.global disable_watchdogs
disable_watchdogs:
    jne     %d14, 0, 1f
    load_32bit_val_a %a13, WDTSYS_CRTLA

    mov %d11, WDT_PASSWORD_UNLOCK
    st.w [%a13], %d11

    load_32bit_val_a %a12, WDTSYS_CRTLB
    ld.w %d12, [%a12]
    or %d12, %d12, 1
    st.w [%a12], %d12

    mov %d11, WDT_PASSWORD_LOCK
    st.w [%a13], %d11

1:
    load_32bit_val_d %d10, WDTCPUy_CTRLA
    madd %d10,%d10, %d0, 0x30
    mov.a %a13, %d10

    mov %d11, WDT_PASSWORD_UNLOCK
    st.w [%a13], %d11

    load_32bit_val_d %d12, WDTCPUy_CTRLB
    madd %d12,%d12, %d0, 0x30
    mov.a %a12, %d12
    ld.w %d12, [%a12]
    or %d12, %d12, 1
    st.w [%a12], %d12

    mov %d11, WDT_PASSWORD_LOCK
    st.w [%a13], %d11

    dsync
    ji %a11


#define LMU0_SFR_BASE 0xFB000000
#define LMUx_OFFSET 0x10000
#define ALL_CPUS_MASK 0x10000FFF
#define LMU_RGN0_WRA_OFFSET 0x300
#define ACCENDLMU0_CFG_WRA 0xF880E060
#define ACCENDLMUx_OFFSET 0x40000
#define ACCENDLMU0_RNG0_WRA 0xF880E400

.global platform_init_mem
platform_init_mem:
init_lmus:
    /* Enable access to LMUs to all CPUs */
    load_32bit_val_d %d10, LMU0_SFR_BASE
    load_32bit_val_d %d11, ALL_CPUS_MASK
    load_32bit_val_d %d12, LMU_RGN0_WRA_OFFSET
    add %d10, %d10, %d12
    mov.a %a12, %d10
    load_32bit_val_d %d12, LMUx_OFFSET
    mov.a %a13, %d12
    mov %d12, 9
1:
    st.w [%a12], %d11
    isync
    add.a %a12, %a12, %a13
    add %d12, %d12, -1
    jnz %d12, 1b

init_dlmus:
    /* currently, each cpu enables access to all other cpus to its DLMU */
    load_32bit_val_d %d10, ACCENDLMU0_CFG_WRA
    load_32bit_val_d %d11, ACCENDLMU0_RNG0_WRA
    load_32bit_val_d %d12, ALL_CPUS_MASK
    load_32bit_val_d %d8, ACCENDLMUx_OFFSET

1:
    madd %d10, %d10, %d0, %d8
    madd %d11, %d11, %d0, %d8
    mov.a %a13, %d10
    st.w [%a13], %d12
    mov.a %a13, %d11
    st.w [%a13], %d12

    dsync
    ji %a11
