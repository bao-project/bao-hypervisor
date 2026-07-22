/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef __PLAT_CNT_H__
#define __PLAT_CNT_H__

#define CNTCR_EN    (1UL << 0)
#define CNTCR_HDBG  (1UL << 1)

void rzt2m_cnt_init(void);

#endif /* __PLAT_CNT_H__ */