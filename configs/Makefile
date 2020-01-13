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


#Note: all toolchain and flag variables are supposed to be passed  
#	main makefile

ifeq ($(CONFIG),)
$(error Target configuration (TARGET) not defined.)
endif

TARGET_DIR:=$(realpath $(CONFIG))
TARGET:=$(TARGET_DIR)/config.c
CONFIG_OBJ:=$(patsubst %.c, %.o, $(TARGET))
CONFIG_DEP:=$(patsubst %.c, %.d, $(TARGET))
CONFIG_BLOB:=$(TARGET_DIR)/$(CONFIG)

.PHONY: all clean

config: $(CONFIG_BLOB).bin

-include $(CONFIG_DEP)

%.d: %.c 
	@$(cc) $(cppflags) -S $(patsubst %.d, %.c, $@) -o temp.S
	@grep ".incbin" temp.S > $(patsubst %.d, %.S, $@) 
	@$(as) -MD $@ $(patsubst %.d, %.S, $@)  -o $(patsubst %.d, %.o, $@)
	@rm temp.S $(patsubst %.d, %.S, $@)
	@$(cc) -MM -MG -MT "$(patsubst %.d, %.o, $@) $@"  $(cppflags) $(filter %.c, $^) >> $@

%.o: %.[c,S]
	@echo Compiling source $<
	@$(cc) $(cflags) -c $< -o $@

%.S: %.c
	@$(cc) $(cppflags) -S $< -o $@

$(CONFIG_BLOB).elf: linker.ld $(CONFIG_OBJ)
	@echo Linking $@
	@$(ld) $(ldflags) -Tlinker.ld $(CONFIG_OBJ) -o $@

%.bin: %.elf
	@echo Generating $@
	@$(objcopy) -S -O binary $< $@

clean:
	-rm -rf $(TARGET_DIR)/*.d
	-rm -rf $(TARGET_DIR)/*.S
	-rm -rf $(TARGET_DIR)/*.o
	-rm -rf $(TARGET_DIR)/*.elf
	-rm -rf $(TARGET_DIR)/*.bin