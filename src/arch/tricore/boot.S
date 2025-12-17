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

.macro get_phys_addr rd, ra, label
    movh \rd, hi:\label
    mov  \rd, lo:\label

    movh \ra, hi:BAO_VAS_BASE
    mov \ra, lo:BAO_VAS_BASE

    sub \rd, \rd, \ra
    add \rd, \rd, %d11
.endm

.macro get_label_addr rd, label
    movh \rd, hi:\label
    addi  \rd, \rd, lo:\label
.endm

.data
.balign 4
/**
 * barrier is used to minimal synchronization in boot - other cores wait for bsp to set it.
 */
_barrier: .4byte 0

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
    and     %d0,%d0,7


    /*
     * Install vector table physical address early, in case exception occurs during this
     * initialization.
     */
    
    get_label_addr %d3, _trap_vector_table
    mtcr    $btv,%d3

    get_label_addr %d3, _hyp_vector_table
    mtcr    0xb010,%d3

    get_label_addr %d3, _irq_vector
    mtcr    $biv,%d3
    isync

    /* Force MPU disable */
    mov %d3, 0
    mtcr 0xFE14, %d3

    jl platform_init_mem
    isync
    
    /* Setting r9 should if set !is_cpu_master */
    mov     %d3, CPU_MASTER_FIXED
    ne      %d14, %d0, %d3
    jeq     %d14, 1, 1f

    get_label_addr %d3, CPU_MASTER
    mov.a     %a4, %d3
    st.w     [%a4], %d0
1:
    jl disable_watchdogs
    isync

    /* Clear stack pointer to avoid unaligned SP exceptions during boot */
    mov     %d3, 0
    mov.a   %sp, %d3

    /* Invalidate Caches */
    mov     %d3, 1 // invalidate data cache
    mtcr    csfr_dcon1, %d3

    mov     %d3, 3 // TODO invalidate program cache and program buffer */
    mtcr    csfr_pcon1, %d3
    isync

    /** subarch specific **/
    /* CPU physical based address */
    get_label_addr    %d3, _dmem_beg

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
    jne     %d14, 0, 1f
        /* Copy data from RX to RWX */
    get_label_addr    %d3, _data_lma_start // LMA start
    get_label_addr    %d4, _data_vma_start // VMA start
    get_label_addr    %d5, _image_load_end // LMA end
    jl copy_data
#endif
    /* disable memory protection and other properties... */
    mov     %d3, 0
    mtcr    csfr_corecon, %d3

    isync


    /**
     * Get base image load address.
     */
    get_label_addr %d1, _reset_handler
    get_label_addr %d2, img_addr
    mov.a %a4, %d2
    st.w [%a4], %d1

    get_label_addr %d1, _data_vma_start
    get_label_addr %d2, data_addr
    mov.a %a4, %d2
    st.w [%a4], %d1

1:
    isync

    mov %d3, 0
    /* make sure no region can be accessed, executed */
    mtcr    csfr_dpre_0, %d3
    mtcr    csfr_dpre_1, %d3
    mtcr    csfr_dpre_2, %d3
    mtcr    csfr_dpre_3, %d3
    mtcr    csfr_dpre_4, %d3
    mtcr    csfr_dpre_5, %d3
    mtcr    csfr_dpre_6, %d3
    mtcr    csfr_dpre_7, %d3

    mtcr    csfr_dpwe_0, %d3
    mtcr    csfr_dpwe_1, %d3
    mtcr    csfr_dpwe_2, %d3
    mtcr    csfr_dpwe_3, %d3
    mtcr    csfr_dpwe_4, %d3
    mtcr    csfr_dpwe_5, %d3
    mtcr    csfr_dpwe_6, %d3
    mtcr    csfr_dpwe_7, %d3

    mtcr    csfr_cpxe_0, %d3
    mtcr    csfr_cpxe_1, %d3
    mtcr    csfr_cpxe_2, %d3
    mtcr    csfr_cpxe_3, %d3
    mtcr    csfr_cpxe_4, %d3
    mtcr    csfr_cpxe_5, %d3
    mtcr    csfr_cpxe_6, %d3
    mtcr    csfr_cpxe_7, %d3

    isync

    /* END OF SUBARCH */
    
    /* If this is the cpu master, clear bss */
    jne     %d14, 0, 1f
    movh.a  %a12,hi:_bss_start
    lea     %a12,[%a12]lo:_bss_start

    movh.a  %a13,hi:_bss_end
    lea     %a13,[%a13]lo:_bss_end

    mov.aa  %a7, %a11
    jl      boot_clear
    mov.aa  %a11, %a7

    movh.a  %a5,hi:_barrier
    lea     %a5,[%a5]lo:_barrier
    mov     %d7, 2
    st.w    [%a5],%d7

1:
    /* wait for bsp to finish clearing bss */
    movh.a  %a5,hi:_barrier
    lea     %a5,[%a5]lo:_barrier
2:
    ld.w    %d8, [%a5]
    jlt     %d8, 2, 2b

    isync

    /* initialize context save areas */
    mov.aa %a6, %a7
    jl    _init_csa
    mov.aa %a7, %a6

    isync

    mov %d3, 2
    /* Program cache bypass */
    mtcr csfr_pcon0, %d3
    /* Data cache bypass */
    mtcr csfr_dcon0, %d3

    isync

    /* reset access to system global registers */
    mfcr    %d3,$psw
    or      %d3,%d3,0x100               // clear GW bit
    mtcr    $psw,%d3
    isync

    /* Initialize stack pointer */
    mov.d   %d4, %a14

    movh    %d5,hi:(CPU_STACK_OFF + CPU_STACK_SIZE)
    mov     %d5,lo:(CPU_STACK_OFF + CPU_STACK_SIZE)
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
   this functions clears the memory between A0 and A1 */
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


/* Copies data from d3 to d4 up to the d5 limit */
.global copy_data
copy_data:
    mov.a %a12, %d3
    mov.a %a13, %d4
1:
    ld.w %d3, [%a12]
    st.w [%a13], %d3
    mov.d %d3, %a12
    mov.d %d4, %a13
    jge  %d3, %d5, 2f
    add %d3, %d3, 4
    add %d4, %d4, 4
    mov.a %a12 , %d3
    mov.a %a13 , %d4
    j 1b
2:
    ji      %a11

.global boot_cache_invalidate
boot_cache_invalidate:
    /* TODO */
    /* cachei.i [a3]4 */
    /* TODO: how about l2? "If the cache line at the index/way specified
     * by the address register A[b] is present in the L1 data cache, then
     * invalidate the line. Note that there is no writeback of any dirty data
     * in the cache line prior to invalidation." */

.global    _init_csa
_init_csa:
    movh    %d10,0
    mtcr    csfr_pcxi,%d10               // previous context info is null
    isync

    // %d10 = begin of CSA
    get_label_addr %d10, csa_array

    mov     %d11, CSA_ENTRIES    
    mul     %d12, %d11, 64      
    madd    %d10, %d10, %d0, %d12

    //addi    %d10,%d10,0x3f            // force alignment (2^6)
    //andn    %d10,%d10,0x3f

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

.global disable_watchdogs
disable_watchdogs:
    jne     %d14, 0, 1f 
    get_label_addr %d10, WDTSYS_CRTLA
    mov.a %a13, %d10

    mov %d11, 0xF8 //Password is 0x7C on reset. UNLOCK
    st.w [%a13], %d11

    get_label_addr %d12, WDTSYS_CRTLB
    mov.a %a12, %d12
    ld.w %d12, [%a12]
    or %d12, %d12, 1
    st.w [%a12], %d12

    mov %d11, 0xF9 //Password is 0x7C on reset. LOCK
    st.w [%a13], %d11

1:
    get_label_addr %d10, WDTCPUy_CTRLA
    madd %d10,%d10, %d0, 0x30
    mov.a %a13, %d10

    mov %d11, 0xF8 //Password is 0x7C on reset. UNLOCK
    st.w [%a13], %d11

    get_label_addr %d12, WDTCPUy_CTRLB
    madd %d12,%d12, %d0, 0x30
    mov.a %a12, %d12
    ld.w %d12, [%a12]
    or %d12, %d12, 1
    st.w [%a12], %d12

    mov %d11, 0xF9 //Password is 0x7C on reset. LOCK
    st.w [%a13], %d11

    ji %a11


#define LMU0_SFR_BASE 0xFB000000
#define ALL_CPUS_MASK 0x10000FFF
#define LMU_RGN0_WRA_OFFSET 0x300
#define ACCENDLMU0_CFG_WRA 0xF880E060
#define ACCENDLMU0_RNG0_WRA 0xF880E400

.global platform_init_mem
platform_init_mem:
init_lmus:
    // Enable access to LMUs to all CPUs
    //maybe only master? master not fixed yet? master always fixed on TC4
    get_label_addr %d10, LMU0_SFR_BASE
    get_label_addr %d11, ALL_CPUS_MASK
    get_label_addr %d12, LMU_RGN0_WRA_OFFSET
    add %d10, %d10, %d12
    mov.a %a12, %d10   
    get_label_addr %d12, 0x10000
    mov.a %a13, %d12
    mov %d12, 9
1:    
    st.w [%a12], %d11
    isync
    add.a %a12, %a12, %a13
    add %d12, %d12, -1
    jnz %d12, 1b

init_dlmus:
    //currently, each cpus enables access to all other cpus to their DLMU
    get_label_addr %d10, ACCENDLMU0_CFG_WRA
    get_label_addr %d11, ACCENDLMU0_RNG0_WRA
    get_label_addr %d12, ALL_CPUS_MASK
    get_label_addr %d8, 0x40000

1:
    madd %d10, %d10, %d0, %d8
    madd %d11, %d11, %d0, %d8
    mov.a %a13, %d10
    st.w [%a13], %d12
    mov.a %a13, %d11
    st.w [%a13], %d12

    ji %a11
