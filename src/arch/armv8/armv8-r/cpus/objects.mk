## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

cpu-objs-y+=$(ARCH_PROFILE)/cpus/core_impl.o

cpu-objs-$(CONFIG_CPU_CORTEX_R52)+=$(ARCH_PROFILE)/cpus/cortex_r52.o
