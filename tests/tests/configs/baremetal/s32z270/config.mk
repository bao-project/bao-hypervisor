this_dir:=$(dir $(lastword $(MAKEFILE_LIST)))

# Build rule for BSP objects
$(this_dir)/bsp/%.o: $(this_dir)/bsp/%.[c,S]
	@echo "Compiling BSP source	$(patsubst $(this_dir)/%,%, $<)"
	@$(cc) -I$(this_dir)/bsp/inc -c $< -o $@
