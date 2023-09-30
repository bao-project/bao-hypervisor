/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/* THIS CONFIG IS DEFINED FOR TESTING PURPOSES ONLY */

#include <config.h>

struct config config = {

        /**
         * This configuration has no VMs. It is used to test build the 
         * hypervisor with an empty configuration. We have to set
         * `vmlist_size` to 1, because the build scripts will generate
         * a macro to define an array size from it which automatically
         * triggers a set of `array subscript i is outside array bounds`
         * errors and the build which we are testing in the first place
         *  will fail.
         */
        .vmlist_size = 1,

};
