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

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a72

GIC_VERSION:=GICV2
RPI4_MEM_GB:=4

drivers = 8250_uart

platform-cppflags =
platform-cflags = -mcpu=$(CPU) -DRPI4_MEM_GB=$(RPI4_MEM_GB)
platform-asflags =
platform-ldflags =
