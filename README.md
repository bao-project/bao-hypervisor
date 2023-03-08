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

**NOTE**: This is work in progress! Don't expect things to be complete. 
Use at your own risk.


Supported Platforms
-------------------

The full list of supported (and work in progress) 
platforms is presented below:

**Armv8-A AArch64**
- [x] Xilinx Zynq UltraScale+ MPSoC ZCU102/4
- [x] Ultra96 Zynq UltraScale+ ZU3EG
- [x] NXP MCIMX8QM-CPU
- [x] NVIDIA Jetson TX2
- [x] 96Boards HiKey 960
- [x] Raspberry Pi 4
- [x] QEMU virt
- [x] Arm Fixed Virtual Platforms
- [ ] BeagleBone AI-64
- [ ] NXP MCIMX8M-EVK
- [ ] 96Boards ROCK960

**Armv7-A / Armv8-A AArch32**
- [x] Arm Fixed Virtual Platforms
- [ ] QEMU virt
- [ ] STM32MP157-DK2

**Armv8-R AArch64**
- [x] Arm Fixed Virtual Platforms

**Armv8-R AArch32**
- [x] Arm Fixed Virtual Platforms
- [ ] NXP S32Z/E
- [ ] Renesas RZT2M

**RISC-V RV64**
- [x] QEMU virt 
- [ ] Rocket w/ H-extension 
- [ ] CVA6 w/ H-extension 

**RISC-V RV32**
- [ ] QEMU virt

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

For a step-by-step guide on how to run different demo configurations 
of the Bao hypervisor featuring multiple guest operating systems and 
targeting several platforms please refer to:
[**Bao Hypervisor Demo Guide**](https://github.com/bao-project/bao-demos)



References
------------

1. José Martins, Adriano Tavares, Marco Solieri, Marko Bertogna, and Sandro Pinto. 
"**Bao: A Lightweight Static Partitioning Hypervisor for Modern Multi-Core Embedded 
Systems**". In Workshop on Next Generation Real-Time Embedded Systems (NG-RES 2020). 
Schloss Dagstuhl-Leibniz-Zentrum für Informatik. 2020.
https://drops.dagstuhl.de/opus/volltexte/2020/11779/

2. José Martins and Sandro Pinto. "**Bao: a modern lightweight embedded hypervisor**".
In Proceedings of the Embedded World Conference, Nuremberg, Germany, 2020. 

3. José Martins and Sandro Pinto. "**Static Partitioning Virtualization on RISC-V**".
In RISC-V Summit, virtual, 2020. https://www.youtube.com/watch?v=yuxMn4ZApEM

4. Bruno Sá, José Martins and Sandro Pinto. "**A First Look at RISC-V Virtualization from an Embedded Systems Perspective**".
In IEEE Transactions on Computers, doi: 10.1109/TC.2021.3124320.

5. Samuel Pereira, João Sousa, Sandro Pinto, José Martins, David Cerdeira "**Bao-Enclave: Virtualization-based Enclaves for Arm**.
In https://arxiv.org/abs/2209.05572

