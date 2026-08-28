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
O?=

# Setup version

version_str:= $(shell git describe --always --dirty --tag --match "v*\.*\.*")
version:= baoversion_$(subst -,_,$(version_str))

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

all:

-include $(ci_dir)/ci.mk

targets:=$(MAKECMDGOALS)
ifeq ($(targets),)
targets:=all
endif
# Targets that are not build targets but still operate on a specific
# platform/configuration pair
config_targets:=menuconfig listconfig defconfig
plat_defconfig_targets:=$(addsuffix _defconfig, \
	$(notdir $(patsubst %/,%,$(dir $(wildcard $(platforms_dir)/*/Kconfig.plat)))))
non_build_targets+=ci clean distclean $(config_targets) $(plat_defconfig_targets)
build_targets:=$(strip $(foreach target, $(targets), \
	$(if $(filter $(target),$(non_build_targets)),,$(target))))
plat_cfg_targets:=$(strip $(build_targets) \
	$(filter $(config_targets), $(targets)))

# Two workflows: PLATFORM=/CONFIG= on the command line select the classic
# per-target build (both must be given, as before kconfig); everything else
# operates on an output directory, explicit O= or the default build/ (with
# binaries in bin/), seeded by the <platform>_defconfig targets
ifneq ($(strip $(PLATFORM)$(CONFIG)),)
ifneq ($(filter $(plat_defconfig_targets),$(targets)),)
$(error PLATFORM=/CONFIG= cannot be combined with a defconfig target; the \
	VM configuration of an output directory is set via menuconfig)
endif
ifneq ($(O),)
$(error PLATFORM=/CONFIG= select the classic per-target build and cannot \
	be combined with O=; seed the output directory with make O=$(O) \
	<platform>_defconfig instead)
endif
else ifeq ($(O),)
override O:=$(cur_dir)/build
default_o:=y
endif

# Check platform target and set platform, driver and arch dirs based on it.
# With O= the platform may instead come from the output directory's .config
ifeq ($(O),)
ifeq ($(PLATFORM),)
ifneq ($(plat_cfg_targets),)
 $(error Target platform argument (PLATFORM) not specified)
endif
endif
endif

platform_dir=$(platforms_dir)/$(PLATFORM)
drivers_dir=$(platforms_dir)/drivers

ifneq ($(PLATFORM),)
ifeq ($(wildcard $(platform_dir)),)
 $(error Target platform $(PLATFORM) is not supported)
endif
endif

# Check configuration exists and set configurtion sources based on it
override CONFIG_REPO:=$(realpath $(CONFIG_REPO))
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

ifneq ($(plat_cfg_targets),)
ifeq ($(O),)
ifeq ($(CONFIG),)
$(error Configuration (CONFIG) not defined.)
endif
endif
endif
ifneq ($(CONFIG),)
ifeq ($(config_src),)
$(error Cant find file for $(CONFIG) config!)
endif
endif


ifeq ($(O),)
build_dir:=$(cur_dir)/build/$(PLATFORM)/$(CONFIG)
bin_dir:=$(cur_dir)/bin/$(PLATFORM)/$(CONFIG)
config_build_dir:=$(build_dir)/config
else
build_dir:=$(abspath $(O))
bin_dir:=$(if $(default_o),$(cur_dir)/bin,$(build_dir))
$(shell mkdir -p $(build_dir))
# The output directory is shared between configurations, so each keeps its
# own object tree; config_name is only known once the .config is read
config_build_dir=$(kconfig_out_dir)/$(config_name)
endif
kconfig_out_dir:=$(build_dir)/config
platform_build_dir:=$(build_dir)/platform
scripts_build_dir:=$(build_dir)/scripts
directories:=$(build_dir) $(bin_dir) $(kconfig_out_dir) \
	$(platform_build_dir) $(scripts_build_dir)

# Defconfig infrastructure: each build instance carries its own .config,
# seeded from the defconfig lookup below, and synced by scripts/kconfig.py
# into a make fragment (auto.conf) and a C header (autoconf.h) force-included
# in every compilation unit
kconfig_file:=$(build_dir)/.config
kconfig_auto_conf:=$(kconfig_out_dir)/auto.conf
kconfig_auto_hdr:=$(kconfig_out_dir)/autoconf.h
kconfig_srcs:=$(shell find $(src_dir) -name Kconfig)
kconfig_tool:=$(scripts_dir)/kconfig.py
kconfig_env=srctree=$(cur_dir) KCONFIG_ROOT=$(src_dir)/Kconfig \
	KCONFIG_CONFIG=$(kconfig_file) $(if $(PLATFORM),BAO_PLATFORM=$(PLATFORM))
# Seeding layers, applied in order: the platform's base defconfig, then the
# VM config folder's defconfig (folder configurations only) overriding it,
# then pure Kconfig defaults for whatever neither mentions
seed_plat_defconfig=$(wildcard $(platform_dir)/defconfig)
seed_config_defconfig=$(strip $(if $(filter-out $(CONFIG_REPO),$(config_dir)), \
	$(wildcard $(config_dir)/defconfig)))
seed_defconfigs=$(seed_plat_defconfig) $(seed_config_defconfig)
seed_config_src_arg=$(if $(config_src),--config-src $(abspath $(config_src)))
seed_defconfig_args=\
	$(if $(seed_plat_defconfig),--platform-defconfig $(seed_plat_defconfig)) \
	$(if $(seed_config_defconfig),--config-defconfig $(seed_config_defconfig)) \
	$(seed_config_src_arg)

$(kconfig_file):
	$(if $(PLATFORM),,$(error No configuration in $(build_dir): pass \
		PLATFORM= and CONFIG=, or run make \
		$(if $(default_o),,O=$(O) )<platform>_defconfig first))
	@echo "Seeding config		$(patsubst $(cur_dir)/%,%, $@)"
	@mkdir -p $(dir $@)
	@$(kconfig_env) python3 $(kconfig_tool) seed $(seed_defconfig_args)

# Kernel-style seeding of an O= output directory: the target stem names the
# platform, and CONFIG= additionally records the VM configuration source
.PHONY: $(plat_defconfig_targets)
$(plat_defconfig_targets): %_defconfig:
	$(if $(O),,$(error $@ requires an output directory (O=<dir>)))
	@echo "Seeding config		$(kconfig_file)"
	@mkdir -p $(build_dir)
	@srctree=$(cur_dir) KCONFIG_ROOT=$(src_dir)/Kconfig \
		KCONFIG_CONFIG=$(kconfig_file) BAO_PLATFORM=$* \
		python3 $(kconfig_tool) seed \
		$(if $(wildcard $(platforms_dir)/$*/defconfig), \
			--platform-defconfig $(platforms_dir)/$*/defconfig) \
		$(if $(seed_config_defconfig),--config-defconfig $(seed_config_defconfig)) \
		$(seed_config_src_arg)

$(kconfig_auto_conf): $(kconfig_file) $(kconfig_srcs) $(kconfig_tool)
	@echo "Generating config	$(patsubst $(cur_dir)/%,%, $@)"
	@mkdir -p $(kconfig_out_dir)
	@$(kconfig_env) python3 $(kconfig_tool) sync --auto-conf $@ \
		--auto-header $(kconfig_auto_hdr)

# The sync recipe above writes both files; a two-target rule would run it
# once per target (racing under -j) and grouped targets (&:) need make 4.3+,
# so the header instead tracks auto.conf through a recipe-less rule
$(kconfig_auto_hdr): $(kconfig_auto_conf)

# Configuration options are owned by Kconfig, which resolves their
# dependencies; setting them out-of-band would bypass that resolution
config_cli_overrides:=$(strip $(foreach v, \
	$(filter-out CONFIG_REPO, $(filter CONFIG_%, $(.VARIABLES))), \
	$(if $(filter command% override, $(origin $(v))), $(v))))
ifneq ($(config_cli_overrides),)
$(error Configuration options cannot be set on the command line \
	($(config_cli_overrides)); change them via menuconfig or the defconfig)
endif

ifneq ($(strip $(build_targets) $(filter listconfig,$(targets))),)
-include $(kconfig_auto_conf)

ifneq ($(O),)
# In the O= workflow the .config owns the platform and the VM configuration.
# PLATFORM= must then agree with it and CONFIG= overrides the configuration
# source for this invocation only. The checks are skipped while auto.conf is
# still being (re)generated; make restarts with the resolved values
PLATFORM:=$(CONFIG_PLATFORM)
ifneq ($(wildcard $(kconfig_auto_conf)),)
ifneq ($(PLATFORM),)
ifeq ($(wildcard $(platform_dir)),)
 $(error Target platform $(PLATFORM) is not supported)
endif
endif
ifeq ($(config_src),)
config_src:=$(CONFIG_CONFIG_SRC)
config_dir:=$(patsubst %/,%,$(dir $(config_src)))
ifeq ($(notdir $(config_src)),config.c)
-include $(config_dir)/config.mk
endif
endif
ifneq ($(build_targets),)
ifeq ($(config_src),)
$(error No VM configuration: pass CONFIG= or set CONFIG_SRC in menuconfig)
endif
endif
endif
config_name:=$(strip $(if $(filter config.c,$(notdir $(config_src))), \
	$(notdir $(patsubst %/,%,$(dir $(config_src)))), \
	$(basename $(notdir $(config_src)))))
endif

# Platform facts are resolved by the platform choice in Kconfig; the
# makefiles below only consume them
ARCH:=$(CONFIG_ARCH)
ARCH_SUB:=$(CONFIG_ARCH_SUB)
ARCH_PROFILE:=$(CONFIG_ARCH_PROFILE)
CPU:=$(CONFIG_CPU)
GIC_VERSION:=$(CONFIG_GIC_VERSION)
IRQC:=$(CONFIG_IRQC)
IPIC:=$(CONFIG_IPIC)
arch_mem_prot:=$(if $(filter y,$(CONFIG_MEM_PROT_MPU)),mpu,mmu)

# Warn when a seed defconfig changed after this build was configured;
# the working copy is authoritative and is never silently reseeded
ifneq ($(wildcard $(kconfig_file)),)
$(foreach d, $(seed_defconfigs), \
	$(if $(shell test $(d) -nt $(kconfig_file) && echo y), \
		$(warning $(d) is newer than this build's .config; remove \
			$(kconfig_file) to adopt it)))
endif
endif

-include $(platform_dir)/platform.mk	# platform build mechanics
cpu_arch_dir=$(src_dir)/arch/$(ARCH)
-include $(cpu_arch_dir)/arch.mk
ifneq ($(arch_mem_prot),)
 core_mem_prot_dir:=$(core_dir)/$(arch_mem_prot)
endif

src_dirs+=$(cpu_arch_dir) $(lib_dir) $(core_dir) $(core_mem_prot_dir) \
	$(platform_dir) $(addprefix $(drivers_dir)/, $(drivers)) $(config_dir)
inc_dirs:=$(addsuffix /inc, $(src_dirs))

build_dirs:=$(patsubst $(cur_dir)%, $(build_dir)%, $(src_dirs) $(inc_dirs))
directories+=$(build_dirs) $(config_build_dir) $(config_build_dir)/inc


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
gens+=$(kconfig_auto_hdr)
gens+=$(asm_defs_hdr)

config_def_generator_src:=$(scripts_dir)/config_defs_gen.c
config_def_generator:=$(if $(O),$(config_build_dir),$(scripts_build_dir))/config_defs_gen
config_defs:=$(config_build_dir)/inc/config_defs_gen.h
gens+=$(config_def_generator) $(config_defs)
inc_dirs+=$(config_build_dir)/inc

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

c_src_files:=$(wildcard $(patsubst %.o,%.c, $(objs-y)))
asm_src_files:=$(wildcard $(patsubst %.o,%.S, $(objs-y)))
c_hdr_files=$(shell cat $(deps) | grep -o "$(src_dir)/\S*\.h" | sort | uniq)

deps+=$(patsubst %.o,%.d,$(objs-y))
objs-y:=$(patsubst $(cur_dir)%, $(build_dir)%, $(objs-y))

# Config objects already reside in config_build_dir so they must be added after
# the cur_dir→build_dir remapping to avoid double-expanding the build path.
# Absolute-path entries go under config_build_dir/external/ preserving the full path.
config_rel_objs-y:=$(filter-out /%, $(config-objs-y))
config_abs_objs-y:=$(filter /%, $(config-objs-y))
deps+=$(patsubst %.o,%.d,$(addprefix $(config_build_dir)/, $(config_rel_objs-y)))
deps+=$(patsubst %.o,%.d,$(addprefix $(config_build_dir)/external, $(config_abs_objs-y)))
objs-y+=$(addprefix $(config_build_dir)/, $(config_rel_objs-y))
objs-y+=$(addprefix $(config_build_dir)/external, $(config_abs_objs-y))

# Now we add all object files directories to the directories list so they can be
# created later
directories+=$(abspath $(dir $(objs-y)))


# Make sure that are no duplicates in directories, deps and objs-y.
# These variables should not be modified beyong this point.
directories:=$(sort $(abspath $(directories)))
deps:=$(abspath $(sort $(deps)))
objs-y:=$(abspath $(sort $(objs-y)))

# Toolchain flags

# Bridge kconfig-owned symbols to the unprefixed macro names the code uses
kconfig_macros:=MEM_PROT_MMU MEM_PROT_MPU MEM_NON_UNIFIED PHYS_IRQS_ONLY \
	MMIO_SLAVE_SIDE_PROT
build_macros:=$(strip $(foreach m, $(kconfig_macros), \
	$(if $(filter y, $(CONFIG_$(m))), -D$(m))))

ifeq ($(CC_IS_GCC),y)
	build_macros+=-DCC_IS_GCC
else ifeq ($(CC_IS_CLANG),y)
	build_macros+=-DCC_IS_CLANG
endif

override CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) \
	$(platform-cppflags) $(build_macros) -include $(kconfig_auto_hdr) \
	-DBAO_VERSION=\"$(version_str)\"
vpath:.=CPPFLAGS

HOST_CPPFLAGS+=$(addprefix -I, $(inc_dirs)) $(arch-cppflags) \
	$(platform-cppflags) $(build_macros) -include $(kconfig_auto_hdr)

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

$(bin_dir)/$(PROJECT_NAME).elf: $(gens) $(objs-y) $(extra-objs-y) $(ld_script_temp)
	@echo "Linking			$(patsubst $(cur_dir)/%,%, $@)"
	@$(ld) $(LDFLAGS) -T$(ld_script_temp) $(objs-y) $(extra-objs-y) -o $@
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
$(build_dir)/%.d : $(config_dir)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

# Dep rule for config-objs-y routed directly into config_build_dir.
# The stem maps directly to config_dir so out-of-tree sources are found correctly.
$(config_build_dir)/%.d : $(config_dir)/%.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

# Dep rule for absolute-path config-objs-y, placed under config_build_dir/external/.
# No slash after 'external' so the stem captures the full absolute source path.
$(config_build_dir)/external%.d : %.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

# We need to repeat the rule again to support fully out-of-tree sources (both from the root directory
# and the CONFIG_REPO)
$(build_dir)%.d : %.[c,S]
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $< > $@

$(objs-y):
	@echo "Compiling source	$(patsubst $(cur_dir)/%,%, $<)"
	@$(cc) $(CFLAGS) -c $< -o $@

%.bin: %.elf
	@echo "Generating binary	$(patsubst $(cur_dir)/%,%, $@)"
	@$(objcopy) -S -O binary $< $@

# Every generator compiles with the force-included kconfig header, so none
# may run before it exists
$(filter-out $(kconfig_auto_hdr), $(gens)) $(ld_script_temp): $(kconfig_auto_hdr)

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

config_dep:=$(config_build_dir)/$(patsubst %.c,%.d,$(notdir $(config_src)))
$(config_dep): $(config_src)
	@echo "Creating dependency	$(patsubst $(cur_dir)/%,%,\
		 $(patsubst %.d,%, $@))"
	@$(cc) $(CFLAGS) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@" $(CPPFLAGS) $(filter %.c, $^) > $@
	@$(cc) $(CFLAGS) $(CPPFLAGS) -S $(config_src) -o - | grep ".incbin" | \
		awk '{ gsub("\"", "", $$2); print "$(patsubst %.d, %.o, $@): " $$2 }' >> $@

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

# Configuration frontends operating on this build's .config

.PHONY: menuconfig
menuconfig: $(if $(O),$(if $(PLATFORM),$(kconfig_file)),$(kconfig_file))
	@$(kconfig_env) python3 $(kconfig_tool) menuconfig

.PHONY: listconfig
listconfig: $(kconfig_file)
	@$(kconfig_env) python3 $(kconfig_tool) list $(seed_defconfig_args)

# Seed the build's .config without building
.PHONY: defconfig
defconfig: $(kconfig_file)

# Count lines of code for the exact target platform and configuration

.PHONY: cloc
cloc: | $(deps)
	@cloc --by-file-by-lang  $(c_src_files) $(asm_src_files) $(c_hdr_files)

#Clean all object, dependency and generated files

# clean keeps the build's .config (a dotfile, unmatched by the wildcard);
# distclean erases the configuration as well

.PHONY: clean
clean:
	@echo "Erasing directories..."
ifneq ($(default_o),)
	-rm -rf $(build_dir) $(bin_dir)
else ifneq ($(O),)
	-rm -rf $(wildcard $(build_dir)/*) $(wildcard $(bin_dir)/*)
else
	-rm -rf $(wildcard $(build_dir)/*)
	-rm -rf $(bin_dir)
endif

.PHONY: distclean
distclean:
	@echo "Erasing directories and configuration..."
ifneq ($(default_o),)
	-rm -rf $(build_dir) $(bin_dir)
else ifneq ($(O),)
	-rm -rf $(wildcard $(build_dir)/*) $(wildcard $(bin_dir)/*) \
		$(wildcard $(build_dir)/.config)
else
	-rm -rf $(build_dir)
	-rm -rf $(bin_dir)
endif

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
