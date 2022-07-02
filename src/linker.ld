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

#include <bao.h>

ENTRY(_image_start)

SECTIONS
{

	. = BAO_VAS_BASE;

	_image_start = ABSOLUTE(.);

	.boot : {
		*(.boot)
	}

	.text :  {
		*(.text)
	}

	.rodata :  {
		*(.rdata .rodata .rodata.*)
	}
	
	.data : {
		*(.data .data.*)
        PROVIDE(__global_pointer$ = . + 0x800);
		*(.sdata .sdata.* .sdata2.*)
	}

	.ipi_cpumsg_handlers : {
		_ipi_cpumsg_handlers_start = .;
		*(.ipi_cpumsg_handlers)
	}

	.ipi_cpumsg_handlers_id : {
		_ipi_cpumsg_handlers_id_start = .;
		*(.ipi_cpumsg_handlers_id)
	}

	_ipi_cpumsg_handlers_size = SIZEOF(.ipi_cpumsg_handlers);

    . = ALIGN(PAGE_SIZE);
    _image_load_end = .;

	/* Sections to be allocated only in physical memory, not in VA space */

	.vm_images : SUBALIGN(PAGE_SIZE) {
		_vm_image_start = .;
		KEEP(*(.vm_image*))
	}
	. = ALIGN(PAGE_SIZE);
	_vm_image_end = .;
    _image_noload_start = .;
    extra_allocated_phys_mem = _image_noload_start - _image_load_end;

	/**
	 * Rewind LC to reuse VMA addresses occupied by config and make VA
	 * start immediately after image.
	 * Also, force start address of next section to enforce this.
	 */
    . = _image_load_end;

	/* Only no load regions below */
	
	.bss (NOLOAD) :  {	
		_bss_start = .;
		*(.bss* .sbss*)  
		*(COMMON)	
		_bss_end = .;
	} 

	.glb_page_tables (NOLOAD) : ALIGN(PAGE_SIZE) {
		_page_tables_start = .;
		*(.glb_page_tables)
		_page_tables_end = .;
	}
	
	. = ALIGN(PAGE_SIZE);
	_image_end = ABSOLUTE(.);
	_dmem_phys_beg = ABSOLUTE(.) + extra_allocated_phys_mem;

	. = ALIGN(PAGE_SIZE);
	_dmem_beg = ABSOLUTE(.);
	_cpu_if_base = ABSOLUTE(.);
	
	/* Global dynamic memory virtual address space here */

	. = BAO_CPU_BASE;
	_cpu_private_beg = ABSOLUTE(.);

	. = BAO_VM_BASE;
	_cpu_private_end = ABSOLUTE(.);
	_vm_beg = ABSOLUTE(.);

	. = BAO_VAS_TOP;
	_vm_end = ABSOLUTE(.);
 }
