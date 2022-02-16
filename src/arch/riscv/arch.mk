CROSS_COMPILE := riscv64-unknown-elf-

arch-cppflags = 
arch-cflags = -mcmodel=medany -march=rv64g -mstrict-align
arch-asflags =
arch-ldflags = -z common-page-size=0x1000

arch_mem_prot:=mmu
