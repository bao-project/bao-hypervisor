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

CONFIG_DIR:=$(CONFIG_REPO)/$(CONFIG)
CONFIG_LD:=$(configs_dir)/linker.ld
CONFIG_SRC:=$(CONFIG_DIR)/config.c
CONFIG_ASM:=$(CONFIG_SRC:%.c=%.S)
CONFIG_OBJ:=$(CONFIG_SRC:%.c=%.o)
CONFIG_DEP:=$(CONFIG_SRC:%.c=%.d)
CONFIG_BIN:=$(CONFIG_DIR)/$(CONFIG).bin
CONFIG_ELF=$(CONFIG_BIN:%.bin=%.elf)

config: $(CONFIG_BLOB).bin

-include $(CONFIG_DEP)

$(CONFIG_DEP): $(CONFIG_SRC)
	@$(cc) $(cppflags) -S $(patsubst %.d, %.c, $@) -o temp.S
	@grep ".incbin" temp.S > $(patsubst %.d, %.S, $@) 
	@$(as) -MD $@ $(patsubst %.d, %.S, $@)  -o $(patsubst %.d, %.o, $@)
	@rm temp.S $(patsubst %.d, %.S, $@)
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(cppflags) $(filter %.c, $^) >> $@

$(CONFIG_OBJ): $(CONFIG_SRC)
	@echo "Compiling source	$(patsubst $(cur_dir)/%, %, $<)"
	@$(cc) $(cflags) -c $< -o $@

$(CONFIG_ASM): $(CONFIG_SRC)
	@$(cc) $(cppflags) -S $< -o $@

$(CONFIG_ELF): $(CONFIG_LD) $(CONFIG_OBJ)
	@echo "Linking			$(patsubst $(cur_dir)/%, %, $@)"
	@$(ld) $(ldflags) -T$(CONFIG_LD) $(CONFIG_OBJ) -o $@

$(CONFIG_BIN): $(CONFIG_ELF)
	@echo "Generating		$(patsubst $(cur_dir)/%, %, $@)"
	@$(objcopy) -S -O binary $< $@

clean-config:
	@echo "Erasing config..."
	-rm -rf $(CONFIG_ASM)
	-rm -rf $(CONFIG_OBJ)
	-rm -rf $(CONFIG_DEP)
	-rm -rf $(CONFIG_BIN)
	-rm -rf $(CONFIG_ELF)

clean: clean-config

.PHONY: clean clean-config