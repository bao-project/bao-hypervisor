## 
 # Bao, a Lightweight Static Partitioning Hypervisor 
 #
 # Copyright (c) Bao Project (www.bao-project.org), 2019-
 #
 # Authors:
 #      Jose Martins <jose.martins@bao-project.org>
 #
 # Bao is free software; you can redistribute it and/or modify it under the
 # terms of the GNU General Public License version 2 as published by the Free
 # Software Foundation, with a special exception exempting guest code from such
 # license. See the COPYING file in the top-level directory for details. 
 #
##

core-objs-y+=init.o
core-objs-y+=mem.o
core-objs-y+=objcache.o
core-objs-y+=cache.o
core-objs-y+=interrupts.o
core-objs-y+=cpu.o
core-objs-y+=vmm.o
core-objs-y+=vm.o
core-objs-y+=config.o
core-objs-y+=console.o
core-objs-y+=iommu.o
core-objs-y+=ipc.o
