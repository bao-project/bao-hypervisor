# Bao - a lightweight static partitioning hypervisor


Introduction
------------

**Bao** (from Mandarin Chinese “bǎohù”, meaning “to protect”) is a lightweight, 
open-source embedded hypervisor which aims at providing strong isolation and 
real-time guarantees. Bao provides a minimal, from-scratch implementation of 
the partitioning hypervisor architecture. 

Designed mainly for targeting mixed-criticality systems, Bao strongly focuses 
on isolation for fault-containment and real-time behavior. Its implementation 
comprises only a minimal, thin-layer of privileged software leveraging ISA 
virtualization support to implement the static partitioning hypervisor architecture: 
resources are statically partitioned and assigned at VM instantiation time; 
memory is statically assigned using 2-stage translation; IO is pass-through only; 
virtual interrupts are directly mapped to physical ones; and it implements a 1-1 
mapping of virtual to physical CPUs, with no need for a scheduler. 

Bao has no external dependencies, such as on privileged VMs running untrustable, 
large monolithic general-purpose operating systems (e.g., Linux), and, as such, 
encompasses a much smaller TCB.

Bao originally targets the Armv8-A architecture, but there is experimental support
for the RISC-V architecture. The full list of supported (and work in progress) 
platforms is presented below:

- [x] Xilinx Zynq UltraScale+ MPSoC ZCU102 (Armv8-A)
- [x] Xilinx Zynq UltraScale+ MPSoC ZCU104 (Armv8-A)
- [x] Ultra96 Zynq UltraScale+ ZU3EG (Armv8-A)
- [x] 96Boards HiKey 960 (Armv8-A)
- [ ] NXP MCIMX8M-EVK (Armv8-A) - wip
- [ ] NXP MCIMX8QM-CPU (Armv8-A) - wip
- [ ] 96Boards ROCK960 (Armv8-A) - wip
- [ ] QEMU virt (Armv8-A) - wip
- [ ] QEMU virt (RISC-V rv64) - wip



**NOTE**: This is work in progress! Don't expect things to be complete. 
Use at your own risk.



Community Resources
-------------------

Project website:

 - http://www.bao-project.org/ 

Source code:

 - https://github.com/bao-project/bao-hypervisor.git
 - git@github.com:bao-project/bao-hypervisor.git

 Contributing:
 
 - Please get in touch (info@bao-project.org)



Demos
------------

As of now, there are two demos for the ZCU10X platforms.

For specific instructions on how to build, compile, and run please refer to:


1. **ZCU10X bare metal guest demo**:

- https://github.com/bao-project/zcu_baremetal_demo



2. **ZCU10X Linux/FreeRTOS demo**:

- https://github.com/bao-project/zcu_linux-freertos_demo



References
------------

1. José Martins, Adriano Tavares, Marco Solieri, Marko Bertogna, and Sandro Pinto. 
"**Bao: A Lightweight Static Partitioning Hypervisor for Modern Multi-Core Embedded 
Systems**". In Workshop on Next Generation Real-Time Embedded Systems (NG-RES 2020). 
Schloss Dagstuhl-Leibniz-Zentrum für Informatik. 2020.
https://drops.dagstuhl.de/opus/volltexte/2020/11779/


2. José Martins and Sandro Pinto. "**Bao: a modern lightweight embedded hypervisor**".
In Proceedings of the Embedded World Conference, Nuremberg, Germany, 2020. 