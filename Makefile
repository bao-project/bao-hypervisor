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
builtin_build_dir:=$(build_dir)/builtin-configs
bin_dir:=$(cur_dir)/bin/$(PLATFORM)
ifeq ($(CONFIG_BUILTIN), y)
bin_dir:=$(bin_dir)/builtin-configs/$(CONFIG)
endif
directories:=$(build_dir) $(bin_dir) $(builtin_build_dir) 

src_dirs:= $(cpu_arch_dir) $(cpu_impl_dir) $(lib_dir) $(core_dir)\
	$(platform_dir) $(addprefix $(drivers_dir)/, $(drivers))
inc_dirs:=$(addsuffix /inc, $(src_dirs))

# Setup list of objects for compilation
-include $(addsuffix /objects.mk, $(src_dirs))

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

build_dirs:=$(patsubst $(src_dir)%, $(build_dir)%, $(src_dirs) $(inc_dirs))
directories+=$(build_dirs)


# Setup list of targets for compilation
targets-y+=$(bin_dir)/$(PROJECT_NAME).elf
targets-y+=$(bin_dir)/$(PROJECT_NAME).bin

# Generated files variables

ld_script:= $(src_dir)/linker.ld
ld_script_temp:= $(build_dir)/linker_temp.ld
deps+=$(ld_script_temp).d

asm_defs_src:=$(cpu_arch_dir)/asm_defs.c
asm_defs_hdr:=$(patsubst $(src_dir)%, $(build_dir)%, \
	$(cpu_arch_dir))/inc/asm_defs.h
inc_dirs+=$(patsubst $(src_dir)%, $(build_dir)%, $(cpu_arch_dir))/inc
deps+=$(asm_defs_hdr).d

gens:=
gens+=$(asm_defs_hdr)

# Toolchain flags
override CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) $(platform-cppflags)
vpath:.=CPPFLAGS
override CFLAGS+=-O$(OPTIMIZATIONS) -Wall -Werror -ffreestanding -std=gnu11\
	$(arch-cflags) $(platform-cflags) $(CPPFLAGS)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif
override ASFLAGS+=$(CFLAGS) $(arch-asflags) $(platform-asflags)
override LDFLAGS+=-build-id=none -nostdlib $(arch-ldflags) $(plattform-ldflags)

.PHONY: all
all: $(targets-y)
	
$(bin_dir)/$(PROJECT_NAME).elf: $(gens) $(objs-y) $(ld_script_temp)
	@echo "Linking			$(patsubst $(cur_dir)/%, %, $@)"
	@$(ld) $(LDFLAGS) -T$(ld_script_temp) $(objs-y) -o $@
	@$(objdump) -S --wide $@ > $(basename $@).asm
	@$(readelf) -a --wide $@ > $@.txt

ifneq ($(DEBUG), y)
	@echo "Striping	$@"
	@$(sstrip) -s $@
endif

$(ld_script_temp):
	@echo "Pre-processing		$(patsubst $(cur_dir)/%, %, $(ld_script))"
	@$(cc) -E $(addprefix -I, $(inc_dirs)) -x assembler-with-cpp $(ld_script) \
		| grep -v '^\#' > $(ld_script_temp)

ifeq (, $(findstring $(MAKECMDGOALS), clean $(submakes)))
-include $(deps)
endif

$(ld_script_temp).d: $(ld_script) 
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -x assembler-with-cpp  -MM -MT "$(ld_script_temp) $@" \
		$(addprefix -I, $(inc_dirs))  $< > $@

$(build_dir)/%.d : $(src_dir)/%.[c,S]
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@	

$(objs-y): | $(gens)
	@echo "Compiling source	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) $(CFLAGS) -c $< -o $@

%.bin: %.elf
	@echo "Generating binary	$(patsubst $(cur_dir)/%, %, $@)"
	@$(objcopy) -S -O binary $< $@

#Generate assembly macro definitions from arch/$(ARCH)/$(asm_defs_src) if such
#	file exists

ifneq ($(wildcard $(asm_defs_src)),)
$(asm_defs_hdr): $(asm_defs_src)
	@echo "Generating header	$(patsubst $(cur_dir)/%, %, $@)"
	@$(cc) -S $(CFLAGS) $< -o - \
		| awk '($$1 == "->") { print "#define " $$2 " " $$3 }' > $@

$(asm_defs_hdr).d: $(asm_defs_src)
	@echo "Creating dependecy	$(patsubst $(cur_dir)/%, %,\
		 $(patsubst %.d,%, $@))"
	@$(cc) -MM -MT "$(patsubst %.d,%, $@)" $(addprefix -I, $(inc_dirs)) $< > $@	
endif

ifdef CONFIG
include $(configs_dir)/configs.mk
all: config
endif

ifeq ($(CONFIG_BUILTIN), y)
override CPPFLAGS+=-DCONFIG_BIN=$(CONFIG_BIN)
builtin-config-src:=$(core_dir)/builtin-config.S
$(builtin-config-obj): $(builtin-config-src) $(CONFIG_BIN)
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
