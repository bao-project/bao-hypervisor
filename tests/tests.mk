# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved

kao_dir:=$(tests_dir)/kao/src

KAO_TESTS?=all
KAO_ARGS?=

non_build_targets+=tests benchs

.PHONY: tests
tests:
	@echo "Running bao-kao tests for $(PLATFORM)..."
	@python3 $(kao_dir)/kao.py -t $(KAO_TESTS) -p $(PLATFORM) \
		--hyp-srcs $(cur_dir) $(KAO_ARGS)

.PHONY: benchs
benchs:
	@echo "Running bao-kao benchmarks for $(PLATFORM)..."
	@python3 $(kao_dir)/kao.py -b -p $(PLATFORM)
