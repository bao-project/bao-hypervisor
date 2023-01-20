/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef SMCC_H
#define SMCC_H

#define SMCC64_BIT   (0x40000000)

#define SMCC_E_NOT_SUPPORTED  (-1)

#define SMCC32_FID_STD_SRVC     (0x84000000)
#define SMCC64_FID_STD_SRVC     (SMCC32_FID_STD_SRVC | SMCC64_BIT)
#define SMCC32_FID_VND_HYP_SRVC (0x86000000)
#define SMCC64_FID_VND_HYP_SRVC (SMCC32_FID_VND_HYP_SRVC  | SMCC64_BIT)
#define SMCC_FID_FN_NUM_MSK     (0xFFFF)

#endif /* SMCC_H */
