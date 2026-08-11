# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved

kao_dir:=$(tests_dir)/kao/src
kao_script:=$(kao_dir)/kao.py

KAO_TESTS?=all
KAO_ARGS?=

non_build_targets+=tests benchs check-kao

.PHONY: check-kao
check-kao:
	@if [ ! -f $(kao_script) ]; then \
		echo "Bao Kao is not initialized; run 'git submodule update --init --recursive tests/kao'."; \
		exit 1; \
	fi

.PHONY: tests
tests: check-kao
	@echo "Running bao-kao tests for $(PLATFORM)..."
	@python3 $(kao_script) -t $(KAO_TESTS) -p $(PLATFORM) \
		--hyp-srcs $(cur_dir) $(KAO_ARGS)

.PHONY: benchs
benchs: check-kao
	@echo "Running bao-kao benchmarks for $(PLATFORM)..."
	@python3 $(kao_script) -b -p $(PLATFORM)
