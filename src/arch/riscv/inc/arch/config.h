/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

enum npm_mode {
    NPM_MODE_DISABLED = 0,
    NPM_MODE_PMLEN_7 = 7,
    NPM_MODE_PMLEN_16 = 16,
};

struct arch_vm_config {
    /**
     * VS-mode pointer masking policy for this VM. Defaults to disabled.
     * Nonzero modes require RV64 and CPU_EXT_SSNPM, and must be supported
     * by every hart assigned to this VM.
     */
    enum npm_mode npm_mode;
};

#endif /* __ARCH_CONFIG_H__ */
