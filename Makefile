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

SHELL:=bash

PROJECT_NAME:=bao

# Setup toolchain macros
cpp=		$(CROSS_COMPILE)cpp
sstrip= 	$(CROSS_COMPILE)strip
cc=			$(CROSS_COMPILE)gcc
ld = 		$(CROSS_COMPILE)ld
as=			$(CROSS_COMPILE)as
objcopy=	$(CROSS_COMPILE)objcopy
objdump=	$(CROSS_COMPILE)objdump
readelf=	$(CROSS_COMPILE)readelf
size=		$(CROSS_COMPILE)size

#Makefile arguments and default values
DEBUG:=y
OPTIMIZATIONS:=2
CONFIG_BUILTIN=n
CONFIG=
PLATFORM=

# List existing submakes
submakes:=config

# Directories
cur_dir:=$(abspath .)
src_dir:=$(cur_dir)/src
cpu_arch_dir=$(src_dir)/arch
lib_dir=$(src_dir)/lib
core_dir=$(src_dir)/core
platforms_dir=$(src_dir)/platform
configs_dir=$(cur_dir)/configs
CONFIG_REPO?=$(configs_dir)
config:=$(CONFIG_REPO)/$(CONFIG)/$(CONFIG).bin

ifeq ($(CONFIG_BUILTIN), y)
ifeq ($(CONFIG),)
 $(error Buil-in configuration enabled but no configuration (CONFIG) specified)
endif
endif

#Plataform must be defined excpet for clean target
ifeq ($(PLATFORM),) 
ifneq ($(MAKECMDGOALS), clean)
 $(error Target platform argument (PLATFORM) not specified)
endif
endif

platform_dir=$(platforms_dir)/$(PLATFORM)
drivers_dir=$(platforms_dir)/drivers

ifeq ($(wildcard $(platform_dir)),)
 $(error Target platform $(PLATFORM) is not supported)
endif

-include $(platform_dir)/platform.mk	# must define ARCH and CPU variables
cpu_arch_dir=$(src_dir)/arch/$(ARCH)
cpu_impl_dir=$(cpu_arch_dir)/impl/$(CPU)
-include $(cpu_arch_dir)/arch.mk


build_dir:=$(cur_dir)/build/$(PLATFORM)
builtin_build_dir:=$(cur_dir)/build/builtin-configs
bin_dir:=$(cur_dir)/bin/$(PLATFORM)
ifeq ($(CONFIG_BUILTIN), y)
bin_dir:=$(bin_dir)/builtin-configs/$(CONFIG)
endif
directories:=$(build_dir) $(bin_dir) $(builtin_build_dir) 

SRC_DIRS:= $(cpu_arch_dir) $(cpu_impl_dir) $(lib_dir) $(core_dir)\
	$(platform_dir) $(addprefix $(drivers_dir)/, $(drivers))
INC_DIRS:=$(addsuffix /inc, $(SRC_DIRS))

# Setup list of objects for compilation
-include $(addsuffix /objects.mk, $(SRC_DIRS))

objs-y:=
objs-y+=$(addprefix $(cpu_arch_dir)/, $(cpu-objs-y))
objs-y+=$(addprefix $(lib_dir)/, $(lib-objs-y))
objs-y+=$(addprefix $(core_dir)/, $(core-objs-y))
objs-y+=$(addprefix $(platform_dir)/, $(boards-objs-y))
objs-y+=$(addprefix $(drivers_dir)/, $(drivers-objs-y))
ifeq ($(CONFIG_BUILTIN), y)
builtin-config-obj:=$(builtin_build_dir)/$(CONFIG).o
objs-y+=$(builtin-config-obj)
endif

deps+=$(patsubst %.o,%.d,$(objs-y))
objs-y:=$(patsubst $(src_dir)%, $(build_dir)%, $(objs-y))

BUILD_DIRS:=$(patsubst $(src_dir)%, $(build_dir)%, $(SRC_DIRS) $(INC_DIRS))
directories+=$(BUILD_DIRS)


# Setup list of targets for compilation
targets-y+=$(bin_dir)/$(PROJECT_NAME).elf
targets-y+=$(bin_dir)/$(PROJECT_NAME).bin

# Generated files variables

LD_SCRIPT:= $(cur_dir)/linker.ld
LD_SCRIPT_TEMP:= $(build_dir)/linker_temp.ld
deps+=$(LD_SCRIPT_TEMP).d

ASM_DEFS_SRC:=$(cpu_arch_dir)/asm_defs.c
ASM_DEFS_HDR:=$(patsubst $(src_dir)%, $(build_dir)%, \
	$(cpu_arch_dir))/inc/asm_defs.h
INC_DIRS+=$(patsubst $(src_dir)%, $(build_dir)%, $(cpu_arch_dir))/inc
deps+=$(ASM_DEFS_HDR).d

gens:=
gens+=$(ASM_DEFS_HDR)

# Toolchain flags
cppflags+=$(addprefix -I, $(INC_DIRS)) $(arch-cppflags) $(platform-cppflags)
vpath:.=cppflags
cflags= -O$(OPTIMIZATIONS) -Wall -ffreestanding -std=gnu11 $(arch-cflags)\
	$(platform-cflags) $(cppflags)
ifeq ($(DEBUG), y)
	cflags += -g
endif
asflags:= $(cflags) $(arch-asflags) $(platform-asflags)
ldflags:= -build-id=none -nostdlib $(arch-ldflags) $(platform-ldflags)

# Default rule "make"
.PHONY: all
all: $(targets-y)
	
$(bin_dir)/$(PROJECT_NAME).elf: $(gens) $(objs-y) $(LD_SCRIPT_TEMP)
	@echo "Linking			$(patsubst $(cur_dir)/%, %, $@)"
	@$(ld) $(ldflags) -T$(LD_SCRIPT_TEMP) $(objs-y) -o $@
#	@$(size) $@
	@$(objdump) -S --wide $@ > $(basename $@).asm
	@$(readelf) -a --wide $@ > $@.txt

ifneq ($(DEBUG), y)
	@echo "Striping	$@"
	@$(sstrip) -s $@
endif

$(LD_SCRIPT_TEMP):
	@echo "Pre-processing		$(patsubst $(cur_dir)/%, %, $(LD_SCRIPT))"
	@$(cc) -E $(addprefix -I, $(INC_DIRS)) -x assembler-with-cpp $(LD_SCRIPT) \
		| grep -v '^\#' > $(LD_SCRIPT_TEMP)

ifeq (, $(findstring $(MAKECMDGOALS), clean $(submakes)))
-include $(deps)
endif

$(LD_SCRIPT_TEMP).d: $(LD_SCRIPT) 
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -x assembler-with-cpp  -MM -MT "$(LD_SCRIPT_TEMP) $@" \
		$(addprefix -I, $(INC_DIRS))  $< > $@

$(build_dir)/%.d : $(src_dir)/%.[c,S]
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(cppflags) $< > $@	

$(objs-y):
	@echo "Compiling source	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) $(cflags) -c $< -o $@

%.bin: %.elf
	@echo "Generating binary	$(patsubst $(cur_dir)/%, %, $@)"
	@$(objcopy) -S -O binary $< $@

#generate assembly macro definitions from arch/$(ARCH)/$(ASM_DEFS_SRC) if such
#	file exists

ifneq ($(wildcard $(ASM_DEFS_SRC)),)
$(ASM_DEFS_HDR): $(ASM_DEFS_SRC)
	@echo "Generating header	$(patsubst $(cur_dir)/%, %, $@)"
	@$(cc) -S $(cflags) $< -o - \
		| awk '($$1 == "->") { print "#define " $$2 " " $$3 }' > $@

$(ASM_DEFS_HDR).d: $(ASM_DEFS_SRC)
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %,\
		 $(patsubst %.d,%, $@))"
	@$(cc) -MM -MT "$(patsubst %.d,%, $@)" $(addprefix -I, $(INC_DIRS)) $< > $@	
endif

ifeq ($(CONFIG_BUILTIN), y)
cppflags+=-DCONFIG_BIN=$(config)
builtin-config-src:=$(core_dir)/builtin-config.S
$(builtin-config-obj): $(builtin-config-src) $(config)
endif

ifdef CONFIG
all: $(config)
include $(configs_dir)/configs.mk
endif

#Generate directories for object, dependency and generated files

.SECONDEXPANSION:

$(objs-y) $(deps) $(targets-y) $(gens): | $$(@D)

$(directories):
	@echo "Creating directory	$(patsubst $(cur_dir)/%, %, $@)"
	@mkdir -p $@

#Clean all object, dependency and generated files

.PHONY: clean
clean:
	@echo "Erasing directories..."
	-rm -rf $(build_dir)
	-rm -rf $(bin_dir)
