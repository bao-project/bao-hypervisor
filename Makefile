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

HOST_CC:=gcc

#Makefile arguments and default values
DEBUG:=y
OPTIMIZATIONS:=2
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
scripts_dir:=$(cur_dir)/scripts
src_dirs:=

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
-include $(cpu_arch_dir)/arch.mk
ifneq ($(MAKECMDGOALS), clean)
 core_mem_prot_dir:=$(core_dir)/$(arch_mem_prot)
endif


build_dir:=$(cur_dir)/build/$(PLATFORM)/$(CONFIG)
bin_dir:=$(cur_dir)/bin/$(PLATFORM)/$(CONFIG)
directories:=$(build_dir) $(bin_dir)

src_dirs+=$(cpu_arch_dir) $(lib_dir) $(core_dir) $(core_mem_prot_dir) \
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


config_dir:=$(CONFIG_REPO)
config_src:=$(wildcard $(config_dir)/$(CONFIG).c)
ifeq ($(config_src),)
config_dir:=$(CONFIG_REPO)/$(CONFIG)
config_src:=$(wildcard $(config_dir)/config.c)
endif

config_build_dir:=$(build_dir)/config
platform_build_dir:=$(build_dir)/platform
scripts_build_dir:=$(build_dir)/scripts
directories+=$(config_build_dir) $(platform_build_dir) $(scripts_build_dir)

config_def_generator_src:=$(scripts_dir)/config_defs_gen.c
config_def_generator:=$(scripts_build_dir)/config_defs_gen
config_defs:=$(config_build_dir)/config_defs.h
gens+=$(config_def_generator) $(config_defs)
inc_dirs+=$(config_build_dir)

platform_def_generator_src:=$(scripts_dir)/platform_defs_gen.c
platform_def_generator:=$(scripts_build_dir)/platform_defs_gen
platform_defs:=$(platform_build_dir)/platform_defs.h
platform_description:=$(platform_dir)/$(platform_description)
gens+=$(platform_defs) $(platform_def_generator)
inc_dirs+=$(platform_build_dir)


ifneq ($(MAKECMDGOALS), clean)
ifeq ($(CONFIG),)
$(error Configuration (CONFIG) not defined.)
endif
ifeq ($(config_src),)
$(error Cant find file for $(CONFIG) config!)
endif
endif

config_obj:=$(config_src:$(config_dir)/%.c=$(config_build_dir)/%.o)
config_dep:=$(config_src:$(config_dir)/%.c=$(config_build_dir)/%.d)

deps+=$(config_dep)
objs-y+=$(config_obj)

# Toolchain flags
override CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) $(platform-cppflags)
vpath:.=CPPFLAGS

ifeq ($(DEBUG), y)
	debug_flags:=-g
endif

override CFLAGS+=-O$(OPTIMIZATIONS) -Wall -Werror -ffreestanding -std=gnu11 \
	-fno-pic $(arch-cflags) $(platform-cflags) $(CPPFLAGS) $(debug_flags)

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
	@echo "Creating dependency	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -x assembler-with-cpp  -MM -MT "$(ld_script_temp) $@" \
		$(addprefix -I, $(inc_dirs))  $< > $@

$(build_dir)/%.d : $(src_dir)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@	

$(objs-y):
	@echo "Compiling source	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) $(CFLAGS) -c $< -o $@

%.bin: %.elf
	@echo "Generating binary	$(patsubst $(cur_dir)/%, %, $@)"
	@$(objcopy) -S -O binary $< $@

$(deps): | $(gens)

#Generate assembly macro definitions from arch/$(ARCH)/$(asm_defs_src) if such
#	file exists

ifneq ($(wildcard $(asm_defs_src)),)
$(asm_defs_hdr): $(asm_defs_src)
	@echo "Generating header	$(patsubst $(cur_dir)/%, %, $@)"
	@$(cc) -S $(CFLAGS) -DGENERATING_DEFS $< -o - \
		| awk '($$1 == "->") \
			{ gsub("#", "", $$3); print "#define " $$2 " " $$3 }' > $@

$(asm_defs_hdr).d: $(asm_defs_src)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%, %,\
		 $(patsubst %.d,%, $@))"
	@$(cc) -MM -MT "$(patsubst %.d,%, $@)" $(addprefix -I, $(inc_dirs)) $< > $@	
endif

$(config_dep): $(config_src)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%, %,\
		 $(patsubst %.d,%, $@))"
	@$(cc) $(CPPFLAGS) -S $< -o - | grep ".incbin" | $(as) -MD $@ -o $@
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $(filter %.c, $^) > $@

$(config_def_generator): $(config_def_generator_src) $(config_src)
	@echo "Compiling generator	$(patsubst $(cur_dir)/%, %, $@)"
	@$(HOST_CC) $^ -DGENERATING_DEFS $(addprefix -I, $(inc_dirs)) -o $@

$(config_defs): $(config_def_generator)
	@echo "Generating header	$(patsubst $(cur_dir)/%, %, $@)"
	@$(config_def_generator) > $(config_defs)

$(platform_def_generator): $(platform_def_generator_src) $(platform_description)
	@echo "Compiling generator	$(patsubst $(cur_dir)/%, %, $@)"
	@$(HOST_CC) $^ -DGENERATING_DEFS -D$(ARCH) \
		$(addprefix -I, $(inc_dirs)) -o $@

$(platform_defs): $(platform_def_generator)
	@echo "Generating header	$(patsubst $(cur_dir)/%, %, $@)"
	@$(platform_def_generator) > $(platform_defs)


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
