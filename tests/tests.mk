# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved

bao-tests_dir = $(tests_dir)/bao-tests
bao-nix_dir = $(tests_dir)/bao-nix
recipes_dir = $(tests_dir)/recipes

LOG_LEVEL?=2
ECHO?=tf

irq_flags:= 

ifdef GIC_VERSION
irq_flags+=-gicv
irq_flags+=$(GIC_VERSION)
endif

ifdef IRQC
irq_flags+=-irqc
irq_flags+=$(IRQC)
endif

ifdef IPIC
irq_flags+=-ipic
irq_flags+=$(IPIC)
endif


.PHONY: test-framework
framework:

ifndef RECIPE
	@echo "Error: RECIPE variable is not defined. Please specify the path to the recipe file."
	@exit 1
endif

	@echo "Running Bao Tests Framework..."
	python3 $(bao-tests_dir)/framework/test_framework.py \
        -recipe $(recipes_dir)/$(RECIPE) \
        -log_level $(LOG_LEVEL) \
        -echo $(ECHO) \
        -platform $(PLATFORM) \
		$(irq_flags)

