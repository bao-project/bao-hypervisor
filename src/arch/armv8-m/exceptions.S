/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <asm_defs.h>
#include <arch/csfrs.h>
#include <arch/csa.h>

/*
 * TODO:ARMV8M
 * In Armv8-M the vector table is naturally aligned to a power of two, with an alignment value that
 * is, e.g., 128 bytes for CM33, 256 bytes for CM23. As such, this needs to be cpu-specific.
 *
 * The number of interrupts is also cpu-specific, e.g., 480 for CM33, 240 for CM23.
 */
#define VECTTBL_ALIGN   (0x80)
#define MAX_INTERRUPTS  (480)

.macro define_handler name
    .thumb
    .thumb_func
    .global \name
    \name:
.endm

.syntax unified
.text

.macro SAVE_HYP_GPRS
    @ st.w [%a10]0x0, %d0
    @ st.w [%a10]0x4, %d1
    @ st.w [%a10]0x8, %d2
    @ st.w [%a10]0xc, %d3
    @ st.w [%a10]0x10, %d4
    @ st.w [%a10]0x14, %d5
    @ st.w [%a10]0x18, %d6
    @ st.w [%a10]0x1c, %d7
    @ st.w [%a10]0x20, %d8
    @ st.w [%a10]0x24, %d9
    @ st.w [%a10]0x28, %d10
    @ st.w [%a10]0x2c, %d11
    @ st.w [%a10]0x30, %d12
    @ st.w [%a10]0x34, %d13
    @ st.w [%a10]0x38, %d14
    @ st.w [%a10]0x3c, %d15

    @ st.a [%a10]0x40, %a0
    @ st.a [%a10]0x44, %a1
    @ st.a [%a10]0x48, %a2
    @ st.a [%a10]0x4c, %a3
    @ st.a [%a10]0x50, %a4
    @ st.a [%a10]0x54, %a5
    @ st.a [%a10]0x58, %a6
    @ st.a [%a10]0x5c, %a7
    @ st.a [%a10]0x60, %a8
    @ st.a [%a10]0x64, %a9
    @ mov.d %d0, %a10
    @ mov.a %a9, %d0
    @ st.a [%a10]0x68, %a9
    @ st.a [%a10]0x6c, %a11
    @ st.a [%a10]0x70, %a12
    @ st.a [%a10]0x74, %a13
    @ st.a [%a10]0x78, %a14
    @ st.a [%a10]0x7c, %a15
.endm

.macro GET_CPU_PTR
    @ movh    %d9,hi:_dmem_phys_beg
    @ addi    %d9,%d9,lo:_dmem_phys_beg

    @ mfcr    %d8,$core_id
    @ and     %d8,%d8,7
    @ /* CPU_X physical base address */
    @ mov     %d10, CPU_SIZE
    @ madd    %d8, %d9, %d8, %d10
    @ mov.a   %a10, %d0
.endm

.macro GET_VCPU_REGS_PTR
    @ mov.d   %d8, %a8    
    @ mov     %d10, CPU_VCPU_OFF
    @ add     %d8, %d8, %d10
    @ mov.a   %a11, %d8
    @ ld.w    %d8, [%a11]
    @ mov     %d11, VCPU_REGS_OFF
    @ add     %d8, %d8, %d11
    @ mov.a   %a10, %d8
.endm

.macro GET_VCPU_LOWER_CTX_PTR
    @ mov.d   %d8, %a8    
    @ mov     %d10, CPU_VCPU_OFF
    @ add     %d8, %d8, %d10
    @ mov.a   %a11, %d8
    @ ld.w    %d8, [%a11]
    @ mov     %d11, VCPU_REGS_LOWER_CTX_OFF
    @ add     %d8, %d8, %d11
    @ mov.a   %a10, %d8
.endm

.macro VM_EXIT
    @ /*Upper context was saved by hardware*/

    @ /*Save lower context*/
    @ svlcx 

    @ /* Save a0, a1, a8, a9 */
    @ GET_VCPU_REGS_PTR

    @ mfcr %d0, 0xFF81
    @ st.w [%a10] REGS_A0_OFF, %d0    

    @ mfcr %d0, 0xFF85
    @ st.w [%a10] REGS_A1_OFF, %d0 

    @ mfcr %d0, 0xFFA1
    @ st.w [%a10] REGS_A8_OFF, %d0 

    @ mfcr %d0, 0xFFA5
    @ st.w [%a10] REGS_A8_OFF, %d0 

    
.endm

.macro VM_ENTRY
    @     /* d8 and A10 contains the pointer to vcpu->regs (same as lower_ctx) */
    @     GET_VCPU_REGS_PTR
    @     /*
    @         CPU_HVHRA_A0 0x0FF81
    @         CPU_HVHRA_A1 0x0FF85
    @         CPU_HVHRA_A8 0x0FFA1
    @         CPU_HVHRA_A9 0x0FFA5
    @     */
    @     /*restore a0, a1, a8, a9*/
    @     ld.w %d0, [%a10] REGS_A0_OFF
    @     mtcr 0xFF81, %d0

    @     ld.w %d0, [%a10] REGS_A1_OFF
    @     mtcr 0xFF85, %d0

    @     ld.w %d0, [%a10] REGS_A8_OFF
    @     mtcr 0xFFA1, %d0

    @     ld.w %d0, [%a10] REGS_A9_OFF
    @     mtcr 0xFFA5, %d0

    @     //movh %d0, hi:0x90000200
    @     //addi %d0, %d0, lo:0x90000200
    @     //mtcr 0xFE25, %d0

    @     isync
    @     /* Restore lower context */
    @     rslcx

    @     /* Return from hypervisor (Restore upper context) */ 
    @     rfh

    @ 1:
    @     j   1b
.endm


.balign VECTTBL_ALIGN
.global _sec_vector_table
_sec_vector_table:
    /* Exceptions */
    /*
     * In Armv8-M, the processor fetches the first two words of the vector table at each power-on/
     * reset sequence. The first is initial value of the MSP (stack pointer) and the second is the
     * reset vector. The reset vector is the address of the reset handler.
     */
    .word 0                     //TODO:ARMV8M should this be initialized with the real MSP value?
    .word _reset_handler
    .word _nmi_handler
    .word _hard_fault_handler
    .word _mem_manage_handler
    .word _bus_fault_handler
    .word _usage_fault_handler
    .word _secure_fault_handler
    .word 0
    .word 0
    .word 0
    .word _svc_handler
    .word _debug_mon_handler
    .word 0
    .word _pendsv_handler
    .word _systick_handler
    /* Interrupts */
    .rept MAX_INTERRUPTS
    .word _irq_handler
    .endr


/* Handlers */
define_handler _nmi_handler
_nmi_handler:
    b   .

define_handler _hard_fault_handler
_hard_fault_handler:
    b   .

define_handler _mem_manage_handler
_mem_manage_handler:
    b   .

define_handler _bus_fault_handler
_bus_fault_handler:
    b   .

define_handler _usage_fault_handler
_usage_fault_handler:
    b   .

define_handler _secure_fault_handler
_secure_fault_handler:
    b   .

define_handler _svc_handler
_svc_handler:
    b   .

define_handler _debug_mon_handler
_debug_mon_handler:
    b   .

define_handler _pendsv_handler
_pendsv_handler:
    b   .

define_handler _systick_handler
_systick_handler:
    b   .

define_handler _irq_handler
_irq_handler:
    b   .

.global vcpu_arch_entry
vcpu_arch_entry:
/*
    TODO: 
    Setup PCX for the guest.
*/
/*
    The last in the CSA array is the 1st context used. 
    We are sure of this, because this code only executes in the boot sequence.
    We need to re-establish the CSA list. To do it, we have to point the FCX
    to the current PCXI, and point the 1st context to the current FCX.
*/
    @ mfcr %d0, $pcxi
    @ mfcr %d1, $fcx 
    @ mtcr $fcx, %d0
    @ movh %d0, hi:csa_array
    @ addi %d0, %d0, lo:csa_array
    @ mov %d2, CSA_ARRAY_SIZE-(16*4)  
    @ add %d0, %d0, %d2
    @ mov.a %a2, %d0
    @ st.w [%a2], %d1

    @ /* Invalidate the PCXI register */
    @ GET_VCPU_REGS_PTR
    @ /* convert the vcpu->regs to pcx format */    
    @ extr.u %d1, %d8, 28, 4
    @ extr.u %d2, %d8, 6, 16
    @ sh %d1, %d1, 16
    @ or %d2, %d2, %d1
    @ /* point pcxi to the vcpu->regs->lower_ctx*/
    @ mtcr $pcxi, %d2


    @ /* Clear CDC before jumping to guest */
    @ mfcr %d0, $psw
    @ movh %d1, hi:0xFFFFF80
    @ addi %d1, %d1, lo:0xFFFFF80
    @ and %d0, %d0, %d1
    @ mtcr $psw, %d0

    @ /* Enable VCON2 l2_prs */
    @ mfcr %d0, 0xB008
    @ or %d0, %d0, 0x000000100
    @ mtcr 0xB008, %d0

    @ /* Enable VCON0 NMI handled by HV */
    @ mfcr %d0, 0xB000
    @ or %d0, %d0, 0x02
    @ mtcr 0xB000, %d0


    /*
    Init VCPU lower -> upper
    PCXi -> vcpu.lower
    restore lower context inst
    rfh
    */
    VM_ENTRY
