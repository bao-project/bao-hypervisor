/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

/**
 * Halts the calling core forever. Called by panic() (see core/inc/bao.h) on a
 * fatal error. Implemented in assembly, not C, so the halt loop is invisible
 * to AST-based static analysis of its C call sites. Shared by both aarch32
 * and aarch64 (wfi/b are valid mnemonics in either mode).
 */
.global panic
panic:
	wfi
	b	panic
