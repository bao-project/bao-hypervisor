/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/registers.h>
#include <asm_defs.h>
#include <config_defs.h>
#include <platform_defs.h>

.macro get_phys_addr rd, ra, label
    movh \rd, hi:\label
    mov  \rd, lo:\label

    movh \ra, hi:BAO_VAS_BASE
    mov \ra, lo:BAO_VAS_BASE

    sub \rd, \rd, \ra
    add \rd, \rd, %d11
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
.globl _el2_entry
_el2_entry:
_reset_handler:

    /**
     * Not following any ABI for registers in this boot code.
     * The following registers are however reserved to be passed to main
     * as arguments:
     *     d0 -> contains cpu id
     *     d1 -> contains image base load address
     *     d2 -> contains config binary load address (passed in r0)
     * Register r9 is reserved to indicate if the current CPU is master (negated)
     */

    /* Read core ID */
    mfcr    %d0,$core_id
    and     %d0,%d0,7

    /**
     * Get base image load address.
     */
    movh    %d1,hi:_el2_entry
    mov     %d1,lo:_el2_entry

    /*
     * Install vector table physical address early, in case exception occurs during this
     * initialization.
     */
    get_phys_addr %d3, %d4, _trap_vector_table

    movh    %d3,hi:_trap_vector_table
    addi    %d3,%d3,lo:_trap_vector_table
    mtcr    $btv,%d3

    get_phys_addr %d3, %d4, _hyp_vector_table
    movh    %d3,hi:_hyp_vector_table
    addi    %d3,%d3,lo:_hyp_vector_table
    mtcr    $bhv,%d3

    movh    %d3,hi:_irq_vector
    addi    %d3,%d3,lo:_irq_vector
    mtcr    $biv,%d3
    isync

    /* Setting r9 should if set !is_cpu_master */
    mov     %d3, CPU_MASTER_FIXED
    ne      %d9, %d0, %d3
    jeq     %d9, 1, 1f

    get_phys_addr %d3, %d4, CPU_MASTER
    mov.a     %a4, %d3
    st.w     [%a4], %d0
1:

    /**
     * TODO: bring the system to a well known state. This includes disabling the MPU, all caches,
     * BP and others, and invalidating them.
     */

    /* Clear stack pointer to avoid unaligned SP exceptions during boot */
    /* TODO needed? */
    mov     %d3, 0
    mov.a   %sp, %d3


    /* Invalidate Caches */
    /* TODO do we need to? */
    mov     %d10, 1 // invalidate data cache
    mtcr    $hrv_dcon1, %d0

    mov     %d10, 3 // TODO invalidate program cache and program buffer */
    mtcr    $hrv_pcon1, %d3
    isync

    /** subarch specific **/
    /* CPU physical based address */
    movh    %d3,hi:_dmem_phys_beg
    addi    %d3,%d3,lo:_dmem_phys_beg

    /* CPU_X physical base address */
    mov     %d4, CPU_SIZE
    madd    %d3, %d3, %d0, %d4

    /* Clear the CPU struct */
    mov.a     %a0, %d3
    add     %d3, %d7
    mov.a     %a1, %d3

    /* no need to save a11 if not in subarch subroutine */
    mov.aa   %a12, %a11
    jl      boot_clear
    mov.aa   %a11, %a12

    mov.a     %a14, %d3 /* a14 will contain pointer to CPU struct */

    mov     %d3, 2
    /* Program cache bypass */
    mtcr    $hrv_pcon0, %d3
    /* Data cache bypass */
    mtcr    $hrv_dcon0, %d3

    /* disable memory protection and other properties... */
    mov %d3, 0
    mtcr    CORECON, %d3

    isync


    mov %d3, 0
    /* make sure no region can be accessed, executed */
    mtcr    $hrv_dpre_0, %d3
    mtcr    $hrv_dpre_1, %d3
    mtcr    $hrv_dpre_2, %d3
    mtcr    $hrv_dpre_3, %d3
    mtcr    $hrv_dpre_4, %d3
    mtcr    $hrv_dpre_5, %d3
    mtcr    $hrv_dpre_6, %d3
    mtcr    $hrv_dpre_7, %d3

    mtcr    $hrv_dpwe_0, %d3
    mtcr    $hrv_dpwe_1, %d3
    mtcr    $hrv_dpwe_2, %d3
    mtcr    $hrv_dpwe_3, %d3
    mtcr    $hrv_dpwe_4, %d3
    mtcr    $hrv_dpwe_5, %d3
    mtcr    $hrv_dpwe_6, %d3
    mtcr    $hrv_dpwe_7, %d3

    mtcr    $hrv_cpxe_0, %d3
    mtcr    $hrv_cpxe_1, %d3
    mtcr    $hrv_cpxe_2, %d3
    mtcr    $hrv_cpxe_3, %d3
    mtcr    $hrv_cpxe_4, %d3
    mtcr    $hrv_cpxe_5, %d3
    mtcr    $hrv_cpxe_6, %d3
    mtcr    $hrv_cpxe_7, %d3

    /**
     * Map loadable image (and possibly unloadable)
     * If the vm image section is used and has built-in vm images, we need to map the loadble and
     * non-loadble region of the image separately. Otherwise we can map it as a single region.
     */
    movh    %d3,hi:_image_start
    addi    %d3,%d3,lo:_image_start
    mtcr    $hrv_dpr0_l, %d3

    movh    %d3,hi:_image_load_end
    addi    %d3,%d3,lo:_image_load_end
    movh    %d4,hi:_image_noload_start
    addi    %d4,%d4,lo:_image_noload_start
    jne    %d3, %d4, 1f

    movh    %d3,hi:_image_end
    addi    %d3,%d3,lo:_image_end
    j       2f
1:
    movh    %d3,hi:_image_load_end
    addi    %d3,%d3,lo:_image_load_end
2:
    mov     %d4, 1
    sub     %d3, %d4
    mtcr    $hrv_dpr0_0, %d3

    /* TODO x-only, RO, and RW according to section permissions */
    /* TODO set permissions all at once to avoid muiltiple rw to sys regs */
    mfcr    %d3, $hrv_cpxe_0
    or      %d3, %d3, (1 << 0)
    mtcr    $hrv_cpxe_0, %d3

    mfcr    %d3, $hrv_dpre_0
    or      %d3, %d3, (1 << 0)
    mtcr    $hrv_dpre_0, %d3

    mfcr    %d3, $hrv_dpwe_0
    or      %d3, %d3, (1 << 0)
    mtcr    $hrv_dpwe_0, %d3


    /* Map Image Non-loadable if needed */
    movh    %d3,hi:_image_load_end
    addi    %d3,%d3,lo:_image_load_end
    movh    %d4,hi:_image_noload_start
    addi    %d4,%d4,lo:_image_noload_start
    jeq     %d3, %d4, skip_non_loadable

    movh    %d3,hi:_image_noload_start
    addi    %d3,%d3,lo:_image_noload_start
    mtcr    $hrv_dpr1_l, %d3

    movh    %d3,hi:_image_end
    addi    %d3,%d3,lo:_image_end
    mov     %d4, 1
    sub     %d3, %d4
    mtcr    $hrv_dpr1_l, %d3

    mfcr    %d3, $hrv_cpxe_0
    or      %d3, %d3, (1 << 1)
    mtcr    $hrv_cpxe_0, %d3

    mfcr    %d3, $hrv_dpre_0
    or      %d3, %d3, (1 << 1)
    mtcr    $hrv_dpre_0, %d3

    mfcr    %d3, $hrv_dpwe_0
    or      %d3, %d3, (1 << 1)
    mtcr    $hrv_dpwe_0, %d3


skip_non_loadable:

    /* Region 2 - CPU */
    mov.d   %d3, %a14
    mtcr    $hrv_dpr2_l, %d3

    mov     %d4, CPU_SIZE
    add     %d3, %d3, %d4
    mov     %d4, 1
    sub     %d3, %d3, %d4
    mtcr    $hrv_dpr2_u, %d3

    mfcr    %d3, $hrv_cpxe_0
    or      %d3, %d3, (1 << 2)
    mtcr    $hrv_cpxe_0, %d3

    mfcr    %d3, $hrv_dpre_0
    or      %d3, %d3, (1 << 2)
    mtcr    $hrv_dpre_0, %d3

    mfcr    %d3, $hrv_dpwe_0
    or      %d3, %d3, (1 << 2)
    mtcr    $hrv_dpwe_0, %d3

    isync

    mov %d3, 2
    /* Program cache bypass */
    mtcr $hrv_pcon0, %d3
    /* Data cache bypass */
    mtcr $hrv_dcon0, %d3

    /* disable memory protection and other properties... */
    mov %d3, 0
    mtcr $hrv_corecon, %d3

    isync

    /* END OF SUBARCH */


    /* reset access to system global registers */
    mfcr    %d0,$hrv_psw
    andn    %d0,%d0,0x100               // clear GW bit
    mtcr    $hrv_psw,%d0
    isync

    movh    %d3,hi:_dmem_phys_beg
    addi    %d3,%d3,lo:_dmem_phys_beg

    /* CPU_X physical base address */
    mov     %d4, CPU_SIZE
    madd    %d3, %d3, %d0, %d4

    /* initialize context save areas */
    mov     %d4, %d0
    mov     %d5, %d1
    mov     %d6, %d2

    // %d0 = begin of CSA
    movh    %d0,hi:_csa_begin
    addi    %d0,%d0,lo:_csa_begin
    /* CPU_X CSA base address TODO */
    mov     %d7, 0x200
    madd    %d0, %d0, %d4, %d7

    // %d1 = size of CSA TODO
    mov    %d1, 0x200

    jl    _init_csa

    mov     %d0, %d4
    mov     %d1, %d5
    mov     %d2, %d6

    /* If this is the cpu master, clear bss */
    jne     %d9, 0, 1f
    movh.a  %a0,hi:_bss_start
    lea     %a0,[%a0]lo:_bss_start

    movh.a  %a1,hi:_bss_end
    lea     %a1,[%a1]lo:_bss_end

    mov.aa  %a12, %a11
    jl      boot_clear
    mov.aa  %a11, %a12

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

    /* Initialize stack pointer */
    mov.d   %d4, %a14

    movh    %d4,hi:(CPU_STACK_OFF + CPU_STACK_SIZE)
    mov     %d4,lo:(CPU_STACK_OFF + CPU_STACK_SIZE)

    mov.a   %sp, %d4

    j       init

    /* This point should never be reached */
oops:
    j       oops

/*****  Helper functions for boot code. ******/

.global boot_clear
.func boot_clear
boot_clear:
    mov     %d8, 0
    mov.d   %d4, %a1
2:
    mov.d   %d3, %a0
    jge     %d3, %d4, 1f
    st.w    [%a0],%d8
    mov     %d5, 4
    add     %d3, %d3, %d5
    j       2b
1:
    ji      %a11
.endfunc


.global boot_cache_invalidate
.func boot_cache_invalidate
boot_cache_invalidate:
    /* TODO */
    /* cachei.i [a3]4 */
    /* TODO: how about l2? "If the cache line at the index/way specified
     * by the address register A[b] is present in the L1 data cache, then
     * invalidate the line. Note that there is no writeback of any dirty data
     * in the cache line prior to invalidation." */
.endfunc


.global    _init_csa
.func _init_csa
_init_csa:
    movh    %d0,0
    mtcr    $hrv_pcxi,%d0               // previous context info is null
    isync

    addi    %d0,%d0,0x3f            // force alignment (2^6)
    andn    %d0,%d0,0x3f

    andn    %d1,%d1,63              // force alignment (2^6)
    sub     %d1,%d1,%d0             // %d1 size of CSA

    sh      %d1,%d1,-6              // %d1/size of each Ctx = number of CSAs

    /* Initialize first CSA */
    mov.a   %a3,%d0                 // %a3 = address of first CSA
    extr.u  %d0,%d0,28,4            // %d0 = segment (4 msb)
    sh      %d0,%d0,16              // %d0 = segment << 16
    lea     %a4,0                   // %a4 = previous CSA = 0
    st.a    [%a3],%a4               // store it in 1st CSA
    mov.aa  %a4,%a3                 // %a4 = current CSA

    lea     %a3,[%a3]64             // %a3 = %a3->nextCSA

    mov.d   %d2,%a3
    extr.u  %d2,%d2,6,16            // get CSA index
    or      %d2,%d2,%d0             // add segment number
    mtcr    $hrv_lcx,%d1                // initialize lcx

    add     %d1,%d1,-2              // CSAs to initialize -= 2
    mov.a   %a5,%d1                 // %a5 = loop counter

csa_loop:
    mov.d   %d2,%a4                 // %d1 = current CSA address
    extr.u  %d2,%d2,6,16            // get CSA index
    or      %d2,%d2,%d0             // add segment number
    st.w    [%a3],%d1               // store "nextCSA" pointer
    mov.aa  %a4,%a3                 // %a4 = current CSA address
    lea     %a3,[%a3]64             // %a3 = %a3->nextCSA
    loop    %a5,csa_loop            // repeat until done

    mov.d   %d2,%a4                 // %d1 = current CSA address
    extr.u  %d2,%d2,6,16            // get CSA index
    or      %d2,%d2,%d0             // add segment number
    mtcr    $hrv_fcx,%d1            // initialize fcx
    isync
    ji      %a11
.endfunc

.data
.balign 0x1000
/**
 * Context Save Area
 */
_csa_begin: .fill 0x1000
