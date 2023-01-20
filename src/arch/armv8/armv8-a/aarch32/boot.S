/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <arch/bao.h>
#include <arch/sysregs.h>
#include <arch/page_table.h>
#include <asm_defs.h>

#define PT_LVLS 3

.macro get_phys_addr rd, ra, label
    ldr \rd, =\label
    ldr \ra, =BAO_VAS_BASE
    sub \rd, \rd, \ra
    add \rd, \rd, r1
.endm

.section ".boot", "ax"
.global boot_arch_profile_init
boot_arch_profile_init:

    mov r13, lr

    /*
     * Register r12 contains the size of the allocated physical memory between
     * the loadable sections of the image and the non-loadable.
     */
    ldr r10, =extra_allocated_phys_mem

    /* Disable caches and MMU */
    // TODO

    /* Skip initialy global page tables setup if not bsp (boot cpu) */
    cmp  r9, #0
    bne  wait_for_bsp

	get_phys_addr r11, r4, _page_tables_start	
	get_phys_addr r12, r4, _page_tables_end
    add r11, r11, r10
    add r12, r12, r10
	bl	boot_clear

    get_phys_addr r3, r4, root_l3_pt
    add r3, r3, r10
    ldr r4, =(PTE_INDEX(3, BAO_VAS_BASE)*8)
    add r3, r3, r4

    ldr r4, =_image_start
    ldr r5, =_image_load_end
    get_phys_addr r6, r7, _image_start
    mov r7, #(PTE_HYP_FLAGS | PTE_PAGE)
    orr r6, r6, r7
1:
    cmp r4, r5
    bge 2f
    str r6, [r3]
    add r3, r3, #8
    add r6, r6, #PAGE_SIZE
    add r4, r4, #PAGE_SIZE
    b 1b
2:
    ldr r5, =_image_end
    cmp r4, r5
    bge 3f
    get_phys_addr r6, r7, _image_noload_start
    mov r7, #(PTE_HYP_FLAGS | PTE_PAGE)
    orr r6, r6, r7
    b 1b

.pushsection .data
.balign 4
_barrier: .4byte 0
.popsection
3:
	get_phys_addr r5, r4, _barrier
    mov r4, #1
    str r4, [r5]
    sev 
    b map_cpu

wait_for_bsp:
    get_phys_addr r5, r4, _barrier
    ldr r4, [r5]
    cmp r4, #1
    wfe
    blt wait_for_bsp

map_cpu:

    /**
     * r3 -> cpu base phys
     * r4 -> current pt base phys
     * r5 -> pte index (ie offset)
     * r6 -> phys addr | pte flags
     */

    get_phys_addr r3, r4, _dmem_phys_beg
    mov r4, #(CPU_SIZE + (PT_SIZE*PT_LVLS))
    mul r4, r0, r4
    add r3, r3, r4

    mov r11, r3
    add r12, r11, #(CPU_SIZE + (PT_SIZE*PT_LVLS))
    bl boot_clear

    /* Get pointer to root (l1) page table */
	add r4, r3, #CPU_SIZE

    ldr r5, =(PTE_INDEX(1, BAO_VAS_BASE)*8)
    add r6, r4, #PT_SIZE // get address of l2 page table
    mov r7, #(PTE_HYP_FLAGS | PTE_TABLE)
    orr r6, r6, r7
    str r6, [r4, r5]

    add r4, r4, #PT_SIZE // advance to l2 page table

    ldr r5, =(PTE_INDEX(2, BAO_VAS_BASE)*8)
    get_phys_addr r6, r7, root_l3_pt // shared l3 page table (for image)
    add r6, r6, r10
    mov r7, #(PTE_HYP_FLAGS | PTE_TABLE)
    orr r6, r6, r7
    str r6, [r4, r5]

    ldr r5, =(PTE_INDEX(2, BAO_CPU_BASE)*8)
    add r6, r4, #PT_SIZE // cpuu l3 page table
    mov r7, #(PTE_HYP_FLAGS | PTE_TABLE)
    orr r6, r6, r7
    str r6, [r4, r5]

    add r4, r4, #PT_SIZE // advance to l3 page table

    ldr r5, =(PTE_INDEX(3, BAO_CPU_BASE)*8)
	mov r6, r3
    mov r7, #(PTE_HYP_FLAGS | PTE_PAGE)
	add r6, r6, r7
	ldr r7, =BAO_CPU_BASE
	add r8, r7, #(CPU_SIZE+PT_SIZE)
1:
    cmp r7, r8
    bge setup_cpu
    str r6, [r4, r5]
    add r5, r5, #8
    add r7, r7, #PAGE_SIZE
    add r6, r6, #PAGE_SIZE
    b 1b

setup_cpu:

    /* setup translation configurations */
    ldr r3, =HTCR_DFLT 
    mcr p15, 4, r3, c2, c0, 2 // htcr

	/* set hypervisor default memory attributes */
	ldr r3, =MAIR_EL2_DFLT
	mcr p15, 4, r3, c10, c2, 0 // hmair0

    /* set cpu thread pointer */
    ldr r3, =BAO_CPU_BASE
    mcr p15, 4, r3, c13, c0, 2 // write HTPIDR

    get_phys_addr r3, r4, _dmem_phys_beg
    mov r4, #(CPU_SIZE + (PT_SIZE*PT_LVLS))
    mul r4, r0, r4
    add r3, r3, r4
    add r3, r3, #CPU_SIZE
    mov r4, #0
    mcrr p15, 4, r3, r4, c2 // httbr

    ldr r3, =_enter_vas
    mcr p15, 4, r3, c12, c0, 0 // hvbar

    ldr r3, =(SCTLR_RES1 | SCTLR_M | SCTLR_C | SCTLR_I)
    mcr p15, 4, r3, c1, c0, 0 // hsctlr

    // tlbi alle2
    dsb nsh
    isb
    b .

.balign 0x20
_enter_vas:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    ldr r3, =_hyp_vector_table
    mcr p15, 4, r3, c12, c0, 0 // hvbar
    
    sub r13, r13, r1
    ldr r3, =_image_start
    add r13, r13, r3
    bx  r13

.global psci_boot_entry
psci_boot_entry:
    /* TODO */
    // restore base state
    // reenable mmu
    b .
