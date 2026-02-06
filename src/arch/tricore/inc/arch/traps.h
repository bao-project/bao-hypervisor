/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __TRAPS_H__
#define __TRAPS_H__

/* Trap Identifcation numbers */
/* Class 0 - MMU */
#define TIN_MMU_VAF       1 /* Virtual Address Fill */
#define TIN_MMU_VAP       2 /* Virtual Address Protection */
/* Class 1 - Internal Protection Traps */
#define TIN_IP_PRIV       1 /* Privileged Instruction */
#define TIN_IP_MPR        2 /* Memory Protection Read */
#define TIN_IP_MPW        3 /* Memory Protection Write */
#define TIN_IP_MPX        4 /* Memory Protection Execute */
#define TIN_IP_MPP        5 /* Memory Protection Peripheral Access */
#define TIN_IP_MPN        6 /* Memory Protection Null Address */
#define TIN_IP_GRWP       7 /* Global Register Write Protection */
/* Class 2 - Instructon Errors */
#define TIN_IE_IOPC       1 /* Illegal Opcode */
#define TIN_IE_UOPC       2 /* Unimplemented Opcode */
#define TIN_IE_OPD        3 /* Invalid Operand Specification */
#define TIN_IE_ALN        4 /* Data Address Alignment */
#define TIN_IE_MEM        5 /* Invalid Local Memory Address */
#define TIN_IE_CSE        6 /* Coprocessor Trap Synchronous Error */
/* Class 3 - Context Management */
#define TIN_CTXM_FCD      1 /* Free Context List Depletion (FCX=LCX) */
#define TIN_CTXM_CDO      2 /* Call Depth Overflow */
#define TIN_CTXM_CDU      3 /* Call Depth Underflow */
#define TIN_CTXM_FCU      4 /* Free Context List Underflow (FCX=0) */
#define TIN_CTXM_CSU      5 /* Call Stack Underflow (PCX=0) */
#define TIN_CTXM_CTYP     6 /* Context Type (PCXI.UL wrong) */
#define TIN_CTXM_NEST     7 /* Nesting Error RFE with non-zero call depth */
/* Class 4 - System Bus and Peripheral Errors*/
#define TIN_BPE_PSE       1 /* Program Fetch Error */
#define TIN_BPE_DSE       2 /* Data Access Synchronous Error */
#define TIN_BPE_DAE       3 /* Data Access Asynchronous Error */
#define TIN_BPE_CAE       4 /* Coprocessor Trap Asynchronous Error */
#define TIN_BPE_PIE       5 /* Program Memory Integrity Error */
#define TIN_BPE_DIE       6 /* Data Memory Integrity Error */
#define TIN_BPE_TAE       7 /* Temporal Asynchronous Error */
/* Class 5 - Assertion Traps */
#define TIN_ASSERT_OVF    1 /* Arithmetic Overflow */
#define TIN_ASSERT_SOVF   2 /* Sticky Arithmetic Overflow*/
/* Class 6 - System Call */
#define TIN_SYS_SYS       1 /* System Call */
/* Class 7 - Non-Maskable Interrupt */
#define TIN_NMI_NMI       0 /* Non-Maskable Interrupt */

/* Hypervisor Trap Identifcation numbers */
/* Class 0 - Hypervisor Call */
/* Class 1 - Hypervisor Interrupt Trap */
/* Class 3 - Level 2 code memory protection trap */
/* Class 4 - HV CSFR Access Support*/
/* The previous trap classes only have a single trap source */

/* Class 2 - Level 2 data memory protection trap */
#define TIN_HYP_L2MPR     0 /* Level 2 Memory Protection Read */
#define TIN_HYP_L2MPW     1 /* Level 2 Memory Protection Write*/

/* CPUx HR specific data asynchronous trap register */
#define DATR_SBE_BIT      (1 << 3)
#define DATR_CWE_BIT      (1 << 9)
#define DATR_CFE_BIT      (1 << 10)
#define DATR_SOE_BIT      (1 << 14)
#define DATR_E_PRS_EN_BIT (1 << 19)
#define DATR_E_VMN_EN_BIT (1 << 23)
#define DATR_BUS_S_BIT    (1 << 24)

void sys_bus_errors_handler(void);
void l2_dmem_prot_trap_handler(unsigned long* addr, unsigned long access);
void hyp_csfr_access_handler(unsigned long* addr, unsigned long hvtin);
void hvcall_handler(unsigned long function_id, unsigned long dev_id, unsigned long event_id);

#endif //__TRAPS_H__
