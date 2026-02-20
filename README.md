# Bao - a lightweight static partitioning hypervisor

![code quality workflow](https://github.com/bao-project/bao-hypervisor/actions/workflows/code-quality.yaml/badge.svg)
![arm build workflow](https://github.com/bao-project/bao-hypervisor/actions/workflows/build-arm.yaml/badge.svg)
![riscv build workflow](https://github.com/bao-project/bao-hypervisor/actions/workflows/build-riscv.yaml/badge.svg)
![rh850 build workflow](https://github.com/bao-project/bao-hypervisor/actions/workflows/build-v850.yaml/badge.svg)

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
- [x] Toradex Verdin iMX8M Plus (w/ Dahlia Carrier Board)
- [ ] NXP S32G

**Armv7-A / Armv8-A AArch32**
- [x] Arm Fixed Virtual Platforms
- [ ] QEMU virt

**Armv8-R AArch64**
- [x] Arm Fixed Virtual Platforms

**Armv8-R AArch32**
- [x] Arm Fixed Virtual Platforms
- [x] Arm MPS3-AN536
- [ ] NXP S32Z/E
- [ ] Renesas RZT2M

**RISC-V RV64**
- [x] QEMU virt
- [ ] SiFive HiFive Premier P550

**RISC-V RV32**
- [x] QEMU virt

**Infineon Tricore 1.8**
- [ ] TC4x Communication Board  ([WiP branch](https://github.com/bao-project/bao-hypervisor/tree/feat/tricore))

**Renesas RH850**
- [x] RH850 U2A16


Community Resources
-------------------

Project website:

 - http://www.bao-project.org/

Source code:

 - https://github.com/bao-project/bao-hypervisor.git
 - git@github.com:bao-project/bao-hypervisor.git

 Documentation:

 - https://bao-project.readthedocs.io/

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

6. José Martins and Sandro Pinto. "**Shedding Light on Static Partitioning Hypervisors for Arm-based Mixed-Criticality Systems**".
In RTAS 2023, San Antonio, Texas, 2023. https://arxiv.org/abs/2303.11186

7. José Martins and Sandro Pinto. "**Porting of a Static Partitioning Hypervisor to Arm’s Cortex-R52**"
In Embedded Open Source Summit 2023, Prague, Czech Republic, 2023. https://www.youtube.com/watch?v=GmeOikZJRas

8. David Cerdeira and José Martins. "**"Hello 'Bao' World" Tutorial**"
In Bao Half-Day, Virtual Workshop, 2023. https://www.youtube.com/watch?v=6c8_MG-OHYo

9. João Peixoto, José Martins, David Cerdeira and Sandro Pinto. "**BiRtIO: VirtIO for Real-Time Network Interface Sharing on the Bao Hypervisor**"
In IEEE Access, 2024. https://ieeexplore.ieee.org/document/10781314

10. Hidemasa Kawasaki and Soramichi Akiyama. "**Running Bao Hypervisor on gem5**"
In gem5 blog, 2024. https://www.gem5.org/2024/11/12/bao-on-gem5.html
