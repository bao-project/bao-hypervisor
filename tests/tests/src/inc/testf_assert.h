/*
 * Copyright (c) Bao Project and Contributors. All rights reserved
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TESTF_ASSERT_H
#define TESTF_ASSERT_H

#define EXPECTED_EQUAL(x, y)     TESTF_ASSERT_OP(x, y, ==)
#define EXPECTED_NOT_EQUAL(x, y) TESTF_ASSERT_OP(x, y, !=)
#define EXPECTED_TRUE(x)         TESTF_ASSERT_OP(x, 0, !=)
#define EXPECTED_FALSE(x)        TESTF_ASSERT_OP(x, 0, ==)
#define EXPECTED_PTR_NULL(x)     TESTF_ASSERT_OP(x, NULL, ==)
#define EXPECTED_PTR_NOT_NULL(x) TESTF_ASSERT_OP(x, NULL, !=)

#define EXPECTED_ARRAY_EQUAL(ptr1, ptr2, count, type)           \
    do {                                                        \
        unsigned int intra_fails = 0;                           \
        for (int i = 0; i < (count); i = i + 1) {               \
            if (*(type*)((ptr1) + i) != *(type*)((ptr2) + i)) { \
                (*failures)++;                                  \
                intra_fails++;                                  \
                if (intra_fails == 1)                           \
                    LOG_FAILURE();                              \
                if (TESTF_LOG_LEVEL > 1) {                      \
                    printf("    Index: %d\n", i);               \
                }                                               \
            }                                                   \
        }                                                       \
    } while (0)

#define EXPECTED_ARRAY_NOT_EQUAL(ptr1, ptr2, count, type)       \
    do {                                                        \
        unsigned int intra_fails = 0;                           \
        for (int i = 0; i < (count); i = i + 1) {               \
            if (*(type*)((ptr1) + i) != *(type*)((ptr2) + i)) { \
                intra_fails++;                                  \
            }                                                   \
        }                                                       \
        if (intra_fails == 0) {                                 \
            (*failures)++;                                      \
            LOG_FAILURE();                                      \
        }                                                       \
    } while (0)

#define TESTF_ASSERT_OP(x, y, op) \
    do {                          \
        if (!(x op y)) {          \
            (*failures)++;        \
            LOG_FAILURE();        \
        }                         \
    } while (0)

#define TESTF_PASS(message) printf("    Message: %s\n", message);

#define TESTF_FAIL(message) \
    (*failures)++;          \
    LOG_FAILURE();          \
    printf("    Message: %s\n", message);

#endif // TESTF_ASSERT_H
