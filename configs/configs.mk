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


#Note: all directory, toolchain and flag variables are supposed to be 
# defined/passed by the main makefile

ifeq ($(CONFIG),)
$(error Configuration (CONFIG) not defined.)
endif

config_dir:=$(CONFIG_REPO)
config_src:=$(wildcard $(config_dir)/$(CONFIG).c)
ifeq ($(config_src),)
config_dir:=$(CONFIG_REPO)/$(CONFIG)
config_src:=$(wildcard $(config_dir)/config.c)
endif
ifeq ($(config_src),)
$(error Cant find file for $(CONFIG) config!)
endif

config_ld:=$(configs_dir)/linker.ld
config_asm:=$(config_src:%.c=%.S)
config_obj:=$(config_src:%.c=%.o)
config_dep:=$(config_src:%.c=%.d)
CONFIG_BIN:=$(config_dir)/$(CONFIG).bin
config_elf=$(CONFIG_BIN:%.bin=%.elf)

config: $(CONFIG_BIN)

-include $(config_dep)

$(config_dep): $(config_src)
	@$(cc) $(CPPFLAGS) -S $< -o temp.S
	-@grep ".incbin" temp.S > $(patsubst %.d, %.S, $@) 
	@$(as) -MD $@ $(patsubst %.d, %.S, $@)  -o $(patsubst %.d, %.o, $@)
	@rm temp.S $(patsubst %.d, %.S, $@)
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(CPPFLAGS) $(filter %.c, $^) >> $@

$(config_obj): $(config_src)
	@echo "Compiling source	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) $(CFLAGS) -c $< -o $@

$(config_asm): $(config_src)
	@$(cc) $(CPPFLAGS) -S $< -o $@

$(config_elf): $(config_ld) $(config_obj)
	@echo "Linking			$(patsubst $(cur_dir)/%, %, $@)"
	@$(ld) $(LDFLAGS) -T$(config_ld) $(config_obj) -o $@

$(CONFIG_BIN): $(config_elf)
	@echo "Generating		$(patsubst $(cur_dir)/%, %, $@)"
	@$(objcopy) -S -O binary $< $@

clean-config:
	@echo "Erasing config..."
	-rm -rf $(config_asm)
	-rm -rf $(config_obj)
	-rm -rf $(config_dep)
	-rm -rf $(CONFIG_BIN)
	-rm -rf $(config_elf)

clean: clean-config

.PHONY: clean clean-config
