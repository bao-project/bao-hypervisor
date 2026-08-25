## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

CROSS_COMPILE ?= tricore-elf-

clang_arch_target:=tricore-unknown-unknown-elf

arch-cppflags+=
arch-ldflags=

PAGE_SIZE:=64
