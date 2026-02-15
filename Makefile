## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

SHELL:=bash

PROJECT_NAME:=bao

# Helper functions

define current_directory
$(realpath $(dir $(lastword $(MAKEFILE_LIST))))
endef

# Check cross compiler
ifneq ($(findstring clang,$(CROSS_COMPILE)),)
CC_IS_CLANG =	y
else
CC_IS_GCC =	y
endif

# Setup toolchain macros

ifdef CC_IS_CLANG
clang_version:=$(strip $(patsubst clang%, %, $(notdir $(CROSS_COMPILE))))
clang_path:=$(dir $(wildcard $(abspath $(CROSS_COMPILE))))
cpp=		$(clang_path)clang-cpp$(clang_version)
sstrip= 	$(clang_path)llvm-strip$(clang_version)
cc=			$(clang_path)clang$(clang_version)
ld = 		$(clang_path)ld.lld$(clang_version)
as=			$(clang_path)llvm-as$(clang_version)
objcopy=	$(clang_path)llvm-objcopy$(clang_version)
objdump=	$(clang_path)llvm-objdump$(clang_version)
readelf=	$(clang_path)llvm-readelf$(clang_version)
size=		$(clang_path)llvm-size$(clang_version)
else
cpp=		$(CROSS_COMPILE)cpp
sstrip= 	$(CROSS_COMPILE)strip
cc=			$(CROSS_COMPILE)gcc
ld = 		$(CROSS_COMPILE)ld
as=			$(CROSS_COMPILE)as
objcopy=	$(CROSS_COMPILE)objcopy
objdump=	$(CROSS_COMPILE)objdump
readelf=	$(CROSS_COMPILE)readelf
size=		$(CROSS_COMPILE)size
endif

HOST_CC:=gcc

#Makefile arguments and default values
DEBUG:=n
OPTIMIZATIONS:=2
CONFIG=
PLATFORM=

# Setup version

version:= baoversion_$(subst -,_,$(shell  git describe --always --dirty --tag --match "v*\.*\.*"))

# Directories
cur_dir:=$(current_directory)
src_dir:=$(cur_dir)/src
cpu_arch_dir=$(src_dir)/arch
lib_dir=$(src_dir)/lib
core_dir=$(src_dir)/core
platforms_dir=$(src_dir)/platform
configs_dir=$(cur_dir)/configs
CONFIG_REPO?=$(configs_dir)
scripts_dir:=$(cur_dir)/scripts
ci_dir:=$(cur_dir)/ci
src_dirs:=

-include $(ci_dir)/ci.mk

targets:=$(MAKECMDGOALS)
ifeq ($(targets),)
targets:=all
endif
non_build_targets+=ci clean
build_targets:=$(strip $(foreach target, $(targets), \
	$(if $(findstring $(target),$(non_build_targets)),,$(target))))

# Check platform target and set platform, driver and arch dirs based on it
ifeq ($(PLATFORM),)
ifneq ($(build_targets),)
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

# Check configuration exists and set configurtion sources based on it
config_dir:=$(CONFIG_REPO)
config_src:=$(wildcard $(config_dir)/$(CONFIG).c)
ifeq ($(config_src),)
  undefine config_src
  config_dir:=$(CONFIG_REPO)/$(CONFIG)
  -include $(config_dir)/config.mk
  ifeq ($(config_src),)
    config_src:=$(wildcard $(config_dir)/config.c)
  endif
endif

ifneq ($(build_targets),)
ifeq ($(CONFIG),)
$(error Configuration (CONFIG) not defined.)
endif
ifeq ($(config_src),)
$(error Cant find file for $(CONFIG) config!)
endif
endif


build_dir:=$(cur_dir)/build/$(PLATFORM)/$(CONFIG)
bin_dir:=$(cur_dir)/bin/$(PLATFORM)/$(CONFIG)
directories:=$(build_dir) $(bin_dir)

src_dirs+=$(cpu_arch_dir) $(lib_dir) $(core_dir) $(core_mem_prot_dir) \
	$(platform_dir) $(addprefix $(drivers_dir)/, $(drivers)) $(config_dir)
inc_dirs:=$(addsuffix /inc, $(src_dirs))

build_dirs:=$(patsubst $(cur_dir)%, $(build_dir)%, $(src_dirs) $(inc_dirs))
directories+=$(build_dirs)


# Setup list of targets for compilation
targets-y+=$(bin_dir)/$(PROJECT_NAME).elf
targets-y+=$(bin_dir)/$(PROJECT_NAME).bin

# Generated files variables

ld_script:= $(src_dir)/linker.ld
ld_script_temp:= $(build_dir)/linker_temp.ld
deps+=$(ld_script_temp).d

asm_defs_src:=$(cpu_arch_dir)/asm_defs.c
asm_defs_hdr:=$(patsubst $(cur_dir)%, $(build_dir)%, \
	$(cpu_arch_dir))/inc/asm_defs.h
inc_dirs+=$(patsubst $(cur_dir)%, $(build_dir)%, $(cpu_arch_dir))/inc
deps+=$(asm_defs_hdr).d

gens:=
gens+=$(asm_defs_hdr)

config_build_dir:=$(build_dir)/config
platform_build_dir:=$(build_dir)/platform
scripts_build_dir:=$(build_dir)/scripts
directories+=$(config_build_dir) $(platform_build_dir) $(scripts_build_dir)

config_def_generator_src:=$(scripts_dir)/config_defs_gen.c
config_def_generator:=$(scripts_build_dir)/config_defs_gen
config_defs:=$(config_build_dir)/config_defs_gen.h
gens+=$(config_def_generator) $(config_defs)
inc_dirs+=$(config_build_dir)

platform_def_generator_src:=$(scripts_dir)/platform_defs_gen.c
platform_arch_def_generator_src:=$(wildcard $(scripts_dir)/arch/$(ARCH)/platform_defs_gen.c)
platform_def_generator_src+=$(platform_arch_def_generator_src)
platform_def_generator:=$(scripts_build_dir)/platform_defs_gen
platform_defs:=$(platform_build_dir)/platform_defs_gen.h
platform_description:=$(platform_dir)/$(platform_description)
gens+=$(platform_defs) $(platform_def_generator)
inc_dirs+=$(platform_build_dir)

# Setup list of objects for compilation
-include $(addsuffix /objects.mk, $(src_dirs))

## Force adding config source file to to config objects (later we remove duplicate if it is already there)
config-objs-y+=$(patsubst $(config_dir)/%.c, %.o, $(config_src))

objs-y:=
objs-y+=$(addprefix $(cpu_arch_dir)/, $(cpu-objs-y))
objs-y+=$(addprefix $(lib_dir)/, $(lib-objs-y))
objs-y+=$(addprefix $(core_dir)/, $(core-objs-y))
objs-y+=$(addprefix $(platform_dir)/, $(boards-objs-y))
objs-y+=$(addprefix $(drivers_dir)/, $(drivers-objs-y))
objs-y+=$(addprefix $(config_dir)/, $(config-objs-y))

c_src_files:=$(wildcard $(patsubst %.o,%.c, $(objs-y)))
asm_src_files:=$(wildcard $(patsubst %.o,%.S, $(objs-y)))
c_hdr_files=$(shell cat $(deps) | grep -o "$(src_dir)/\S*\.h" | sort | uniq)

deps+=$(patsubst %.o,%.d,$(objs-y))
objs-y:=$(patsubst $(cur_dir)%, $(build_dir)%, $(objs-y))

# As config_dir might be an out-of-tree directory (if CONFIG_REPO is defined as such),
# we need to account for that also for the config defined objs
objs-y:=$(patsubst $(config_dir)%, $(config_build_dir)%, $(objs-y))


# Make sure that are no duplicates in directories, deps and objs-y.
# These variables should not be modified beyong this point.
directories:=$(sort $(directories))
deps:=$(sort $(deps))
objs-y:=$(sort $(objs-y))

# Toolchain flags

build_macros:=
ifeq ($(arch_mem_prot),mmu)
	build_macros+=-DMEM_PROT_MMU
endif
ifeq ($(arch_mem_prot),mpu)
	build_macros+=-DMEM_PROT_MPU
endif
ifeq ($(plat_mem),non_unified)
	build_macros+=-DMEM_NON_UNIFIED
endif
ifeq ($(phys_irqs_only),y)
	build_macros+=-DPHYS_IRQS_ONLY
endif
ifeq ($(mmio_slave_side_prot),y)
	build_macros+=-DMMIO_SLAVE_SIDE_PROT

	ifneq ($(arch_mem_prot),mpu)
		$(error mmio_slave_side_prot=y requires arch_mem_prot=mpu)
	endif
endif

ifeq ($(CC_IS_GCC),y)
	build_macros+=-DCC_IS_GCC
else ifeq ($(CC_IS_CLANG),y)
	build_macros+=-DCC_IS_CLANG
endif

override CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) \
	$(platform-cppflags) $(build_macros)
vpath:.=CPPFLAGS

HOST_CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) \
	$(platform-cppflags) $(build_macros)

ifeq ($(DEBUG), y)
	debug_flags:=-g
	OPTIMIZATIONS:=g
endif


ifeq ($(CC_IS_GCC),y)
	cflags_warns:= \
		-Warith-conversion -Wbuiltin-declaration-mismatch \
		-Wcomments  -Wdiscarded-qualifiers \
		-Wimplicit-fallthrough \
		-Wswitch-unreachable -Wreturn-local-addr  \
		-Wshift-count-negative  -Wuninitialized \
		-Wunused -Wunused-local-typedefs  -Wunused-parameter \
		-Wunused-result -Wvla \
		-Wconversion -Wsign-conversion \
		-Wmissing-prototypes -Wmissing-declarations  \
		-Wswitch-default -Wshadow -Wshadow=global \
		-Wcast-qual -Wunused-macros \
		-Wstrict-prototypes -Wunused-but-set-variable

	override CFLAGS+=-Wno-unused-command-line-argument \
		-pedantic -pedantic-errors
	override LDFLAGS+=--no-check-sections
else ifeq ($(CC_IS_CLANG), y)
	override CFLAGS+=-Wno-unused-command-line-argument --target=$(clang_arch_target)
	override CPPFLAGS+=--target=$(clang_arch_target) -ffreestanding
	override LDFLAGS+=--no-check-sections
endif

override CFLAGS+=-O$(OPTIMIZATIONS) -Wall -Werror -Wextra $(cflags_warns) \
	-ffreestanding -std=c11 -fno-pic -fno-pie \
	$(arch-cflags) $(platform-cflags) $(CPPFLAGS) $(debug_flags)

override ASFLAGS+=$(CFLAGS) $(arch-asflags) $(platform-asflags)

override LDFLAGS+=-build-id=none -nostdlib --fatal-warnings \
	--defsym=$(version)=0 \
	-z common-page-size=$(PAGE_SIZE) -z max-page-size=$(PAGE_SIZE) \
	-no-pie \
	$(arch-ldflags) $(platform-ldflags)

ifneq ($(build_targets),)

.PHONY: all
all: $(targets-y)

$(bin_dir)/$(PROJECT_NAME).elf: $(gens) $(objs-y) $(ld_script_temp)
	@echo "Linking			$(patsubst $(cur_dir)/%,%, $@)"
	@$(ld) $(LDFLAGS) -T$(ld_script_temp) $(objs-y) -o $@
	@$(objdump) -S --wide $@ > $(basename $@).asm
	@$(readelf) -a --wide $@ > $@.txt

ifneq ($(DEBUG), y)
	@echo "Striping		$(patsubst $(cur_dir)/%,%, $@)"
	@$(sstrip) -s $@
endif

$(ld_script_temp):
	@echo "Pre-processing		$(patsubst $(cur_dir)/%,%, $(ld_script))"
	@$(cc) $(CFLAGS) -E $(addprefix -I, $(inc_dirs)) -x assembler-with-cpp  $(CPPFLAGS) \
		$(ld_script) | grep -v '^\#' > $(ld_script_temp)

ifneq ($(build_targets),)
-include $(deps)
endif

$(ld_script_temp).d: $(ld_script)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) -x assembler-with-cpp  -MM -MT "$(ld_script_temp) $@" \
		$(addprefix -I, $(inc_dirs))  $< > $@

$(build_dir)/%.d : $(cur_dir)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

# We need a specific rule for the config deps which has the exact same recipe as the generic
# dep rule because the `config_dir` might be out-of-tree if CONFIG_REPO points to a foreign directory
# and the pattern match must allow for it, given it might not match $(cur_dir)
$(config_build_dir)/%.d : $(config_dir)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

$(objs-y):
	@echo "Compiling source	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -c $< -o $@

%.bin: %.elf
	@echo "Generating binary	$(patsubst $(cur_dir)/%,%, $@)"
	@$(objcopy) -S -O binary $< $@

$(deps): | $(gens)

#Generate assembly macro definitions from arch/$(ARCH)/$(asm_defs_src) if such
#	file exists

ifneq ($(wildcard $(asm_defs_src)),)
$(asm_defs_hdr): $(asm_defs_src)
	@echo "Generating header	$(patsubst $(cur_dir)/%,%, $@)"
	@$(cc) -S $(CFLAGS) -DGENERATING_DEFS $< -o - \
		| awk '($$1 == "//#" || $$1 == "##" || $$1 == "@#")   \
			{ gsub("#", "", $$3); print "#define " $$2 " " $$3 }' > $@

$(asm_defs_hdr).d: $(asm_defs_src)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%,\
		 $(patsubst %.d,%, $@))"
	@$(cc) -MM -MT $(CFLAGS) "$(patsubst %.d,%, $@)" $(addprefix -I, $(inc_dirs)) $< > $@
endif

config_obj:=$(config_src:$(config_dir)/%.c=$(config_build_dir)/%.o)
config_dep:=$(config_src:$(config_dir)/%.c=$(config_build_dir)/%.d)
$(config_dep): $(config_src)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%,\
		 $(patsubst %.d,%, $@))"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(config_obj) $@" $(CPPFLAGS) $(filter %.c, $^) > $@
	@$(cc) $(CFLAGS) $(CPPFLAGS) -S $(config_src) -o - | grep ".incbin" | \
		awk '{ gsub("\"", "", $$2); print "$(config_obj): " $$2 }' >> $@

$(config_def_generator): $(config_def_generator_src) $(config_src)
	@echo "Compiling generator	$(patsubst $(cur_dir)/%,%, $@)"
	@$(HOST_CC) $^ $(build_macros) $(HOST_CPPFLAGS) -DGENERATING_DEFS \
		$(addprefix -I, $(inc_dirs)) -o $@

$(config_defs): $(config_def_generator)
	@echo "Generating header	$(patsubst $(cur_dir)/%,%, $@)"
	@$(config_def_generator) > $(config_defs)

$(platform_def_generator): $(platform_def_generator_src) $(platform_description)
	@echo "Compiling generator	$(patsubst $(cur_dir)/%,%, $@)"
	@$(HOST_CC) $^ $(build_macros) $(HOST_CPPFLAGS) -DGENERATING_DEFS -D$(ARCH) \
		$(addprefix -I, $(inc_dirs)) -o $@

$(platform_defs): $(platform_def_generator)
	@echo "Generating header	$(patsubst $(cur_dir)/%,%, $@)"
	@$(platform_def_generator) > $(platform_defs)


#Generate directories for object, dependency and generated files

.SECONDEXPANSION:

$(objs-y) $(deps) $(targets-y) $(gens): | $$(@D)

$(directories):
	@echo "Creating directory	$(patsubst $(cur_dir)/%,%, $@)"
	@mkdir -p $@

endif

# Count lines of code for the exact target platform and configuration

.PHONY: cloc
cloc: | $(deps)
	@cloc --by-file-by-lang  $(c_src_files) $(asm_src_files) $(c_hdr_files)

#Clean all object, dependency and generated files

.PHONY: clean
clean:
	@echo "Erasing directories..."
	-rm -rf $(build_dir)
	-rm -rf $(bin_dir)

# Instantiate CI rules

ifneq ($(wildcard $(ci_dir)/ci.mk),)

all_files= $(realpath \
	$(cur_dir)/Makefile \
	$(call list_dir_files_recursive, $(src_dir), *) \
	$(call list_dir_files_recursive, $(scripts_dir), *) \
	$(call list_dir_files_recursive, $(config_dir)/example, *) \
)
all_c_src_files=$(realpath $(call list_dir_files_recursive, src, *.c))
all_c_hdr_files=$(realpath $(call list_dir_files_recursive, src, *.h))
all_c_files=$(all_c_src_files) $(all_c_hdr_files)

$(call ci, license, "Apache-2.0", $(all_files))
$(call ci, format, $(all_c_files))

.PHONY: ci
ci: license-check format-check

endif
