# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved

kao_dir:=$(tests_dir)/kao/src
kao_script:=$(kao_dir)/kao.py
kao_tests:=$(tests_dir)/tests
kao_check_ids:=$(kao_tests)/check_ids.py

KAO_TESTS?=all
KAO_EXCLUDE_TAGS?=nightly,manual
KAO_ARGS?=

# Test sources that apply to the target: the generic ones, the arch subtree
# matching ARCH with the nested ARCH_SUB and ARCH_PROFILE directories, and the
# platform subtree. Mirrors how src_dirs is composed for the hypervisor itself.
# Expanded lazily: ARCH and friends are only known once platform.mk is included.
# The nested names are the variables the hypervisor build itself selects
# sources with: ARCH_SUB (aarch64, aarch32, riscv64, riscv32), ARCH_PROFILE
# (armv8-a, armv8-r) and arch_mem_prot (mmu, mpu, spmp...). Each is optional:
# an empty name adds no directory, and wildcard drops directories that do not
# exist.
kao_arch_dir=$(wildcard $(kao_tests)/src/01_arch/*_$(ARCH))
kao_arch_variants=$(ARCH_SUB) $(ARCH_PROFILE) $(arch_mem_prot) \
	$(if $(and $(ARCH_PROFILE),$(ARCH_SUB)),$(ARCH_PROFILE)/$(ARCH_SUB))
kao_src_dirs=$(wildcard $(kao_tests)/src/00_generic) \
	$(kao_arch_dir) \
	$(wildcard $(addprefix $(kao_arch_dir)/,$(kao_arch_variants))) \
	$(wildcard $(kao_tests)/src/02_platform/*_$(PLATFORM))

non_build_targets+=tests check-test-ids

# Checked at parse time, like PLATFORM for build targets in the top Makefile,
# but only when tests are requested so clean and ci keep working without it.
ifneq ($(filter tests,$(MAKECMDGOALS)),)
ifeq ($(PLATFORM),)
$(error Target platform argument (PLATFORM) not specified)
endif
ifeq ($(wildcard $(kao_script)),)
$(error Bao Kao is not initialized; run 'git submodule update --init --recursive tests/kao')
endif
endif

.PHONY: check-test-ids
check-test-ids:
	@python3 $(kao_check_ids) $(kao_tests)/src

.PHONY: tests
tests: check-test-ids
	@echo "Running bao-kao tests for $(PLATFORM)..."
	@python3 $(kao_script) -t $(KAO_TESTS) -p $(PLATFORM) \
		--hyp-srcs $(cur_dir) --wrkdir $(tests_dir)/wrkdir \
		--tests-root $(kao_tests) --envs $(kao_tests)/envs \
		$(if $(KAO_EXCLUDE_TAGS),--exclude-tags $(KAO_EXCLUDE_TAGS)) \
		$(addprefix --tests-src , $(kao_src_dirs)) $(KAO_ARGS)
