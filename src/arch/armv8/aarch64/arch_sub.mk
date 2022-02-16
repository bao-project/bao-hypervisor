CROSS_COMPILE ?= aarch64-none-elf-

arch-cppflags+= 
arch-cflags+= -mcmodel=large -mstrict-align
arch-asflags+=
arch-ldflags+=
