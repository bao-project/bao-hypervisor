/** 
 * Bao, a Lightweight Static Partitioning Hypervisor 
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details. 
 *
 */

#ifndef __ARCH_BAO_H__
#define __ARCH_BAO_H__

#define BAO_VAS_BASE    (0xfd8000000000)
#define BAO_CPU_BASE    (0xfe0000000000)
#define BAO_VM_BASE     (0xfe8000000000)
#define BAO_VAS_TOP     (0xff0000000000)
#define PAGE_SIZE       (0x1000)

#ifndef __ASSEMBLER__


#endif /* !__ASSEMBLER__ */


#endif /* __ARCH_BAO_H__ */