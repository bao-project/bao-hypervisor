/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>
#include <platform_defs.h>
#include <config_defs.h>

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

    . = ALIGN(PAGE_SIZE); /* start RO sections in separate page */

	.rodata :  {
		*(.rdata .rodata .rodata.*)
	}

	. = ALIGN(PAGE_SIZE); /* start RW sections in separate page */
	_data_lma_start = .;

#ifdef MEM_NON_UNIFIED
	. = CONFIG_HYP_DATA_ADDR;	/* Changed location counter to VMA address */
#endif

	_data_vma_start = .;

	.data : AT (_data_lma_start) {
		*(.data .data.*)
        PROVIDE(__global_pointer$ = . + 0x800);
		*(.sdata .sdata.* .sdata2.*)
	}

	.ipi_cpumsg_handlers : {
		ipi_cpumsg_handlers = .;
		*(.ipi_cpumsg_handlers)
	}

	.ipi_cpumsg_handlers_id : {
		_ipi_cpumsg_handlers_id_start = .;
		*(.ipi_cpumsg_handlers_id)
        _ipi_cpumsg_handlers_id_end = .;
	}

	.pad_load : {
		/**
		 * This section ensures the loadable portion of the image (_image_load_end) is page-aligned
		 * by adding padding if necessary. The BYTE(0x00) forces this section to be PROGBITS rather
		 * than NOBITS, ensuring any padding bytes are actually written to the file up to the align
		 */
		BYTE(0x00)
		. = ALIGN(PAGE_SIZE);
	}

    _image_load_end = .;

#ifdef MEM_NON_UNIFIED
	/* Save the current location counter (VMA) and switch to LMA for .vm_images */
	_vma_before_vm_images = .;
    _image_load_end = _data_lma_start + (_image_load_end - _data_vma_start);
	. = _image_load_end;
#endif

	/* Sections to be allocated only in physical memory, not in VA space */

    .vm_images : AT(_image_load_end) SUBALIGN(PAGE_SIZE) {
        _vm_image_start = .;
        KEEP(*(.vm_image*))
    }

#ifdef MEM_NON_UNIFIED
    /* Restore the location counter (VMA) */
    . = _vma_before_vm_images;
#endif

	. = ALIGN(PAGE_SIZE);
	_vm_image_end = ALIGN(_vm_image_start + SIZEOF(.vm_images), PAGE_SIZE);
    _image_noload_start = .;
    extra_allocated_phys_mem = _image_noload_start - _image_load_end;

#ifdef MEM_PROT_MMU
	/**
	 * Rewind LC to reuse VMA addresses occupied by config and make VA
	 * start immediately after image.
	 * Also, force start address of next section to enforce this.
	 */
    . = _image_load_end;
#endif

	/* Only no load regions below */

	.bss (NOLOAD) : {
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

#ifdef MEM_PROT_MMU
	/* Global dynamic memory virtual address space here */

	. = BAO_CPU_BASE;
	_cpu_private_beg = ABSOLUTE(.);

	. = BAO_VM_BASE;
	_cpu_private_end = ABSOLUTE(.);
	_vm_beg = ABSOLUTE(.);

	. = BAO_VAS_TOP;
	_vm_end = ABSOLUTE(.);
#endif
 }
