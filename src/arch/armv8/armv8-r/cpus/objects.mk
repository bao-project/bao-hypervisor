## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_PROFILE)/cpus/core_impl.o

# CPU-specific implementations based on platform configuration
cpu-objs-y+=$(foreach cpu, $(PLAT_CPUS), $(ARCH_PROFILE)/cpus/$(cpu).o)
