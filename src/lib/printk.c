/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <printk.h>

#define F_LONG        (1U << 0U)
#define F_UNSIGNED    (1U << 1U)
#define F_BASE16      (1U << 2U)
#define F_LONG_LONG   (1U << 3U)

/* Number of digits of the largest 64-bit value in base 10. */
#define LL_MAX_DIGITS (20U)

static inline char digit_to_char(unsigned long i, unsigned int base)
{
    unsigned long c;
    unsigned long digit = i % base;
    if (i < 10U) {
        c = ((unsigned long)'0') + digit;
    } else {
        c = ((unsigned long)'a') + (digit - 10U);
    }
    return (char)c;
}

static inline void printc(char** buf, char c)
{
    if (buf != NULL) {
        **buf = c;
        (*buf)++;
    }
}

static size_t prints(char** buf, const char* str)
{
    const char* str_it = str;
    size_t char_count = 0;
    while (*str_it != '\0') {
        printc(buf, *str_it);
        char_count++;
        str_it++;
    }
    return char_count;
}

static size_t vprintd(char** buf, unsigned int flags, va_list* args)
{
    unsigned long u;
    size_t base = ((flags & F_BASE16) != 0U) ? (unsigned int)16U : 10U;
    bool is_long = ((flags & F_LONG) != 0U);
    bool is_unsigned = ((flags & F_UNSIGNED) != 0U) || (base != 10U);
    size_t divisor;
    unsigned long tmp;
    size_t char_count = 0;

    if (is_unsigned) {
        u = is_long ? va_arg(*args, unsigned long) : va_arg(*args, unsigned int);
    } else {
        signed long s = is_long ? va_arg(*args, signed long) : va_arg(*args, signed int);
        if (s < 0) {
            printc(buf, '-');
            char_count++;
            s = -s;
        }
        u = (unsigned long)s;
    }

    divisor = 1;
    tmp = u;
    while (tmp >= base) {
        divisor *= base;
        tmp /= base;
    }

    while (divisor > 0U) {
        unsigned long digit = u / divisor;
        u -= digit * divisor;
        divisor /= base;
        printc(buf, digit_to_char(digit, (unsigned int)base));
        char_count++;
    }

    return char_count;
}

/**
 * Divides the 64-bit value held in hi:lo by base, in place, and returns the remainder. It only
 * uses 32-bit divisions, so that printing 64-bit values does not depend on the compiler's runtime
 * library on 32-bit targets. The low word is divided in two 16-bit steps so that each partial
 * dividend fits in 32 bits, which holds as long as base is not larger than 2^16.
 */
static uint32_t div64_by_base(uint32_t* hi, uint32_t* lo, uint32_t base)
{
    uint32_t rem;
    uint32_t cur;
    uint32_t quot_lo;

    rem = *hi % base;
    *hi = *hi / base;

    cur = (rem << 16U) | (*lo >> 16U);
    quot_lo = (cur / base) << 16U;
    rem = cur % base;

    cur = (rem << 16U) | (*lo & 0xffffU);
    quot_lo |= cur / base;
    rem = cur % base;

    *lo = quot_lo;

    return rem;
}

static size_t vprintll(char** buf, unsigned int flags, va_list* args)
{
    unsigned long long u;
    unsigned int base = ((flags & F_BASE16) != 0U) ? 16U : 10U;
    bool is_unsigned = ((flags & F_UNSIGNED) != 0U) || (base != 10U);
    char digits[LL_MAX_DIGITS];
    size_t num_digits = 0;
    size_t char_count = 0;
    uint32_t hi;
    uint32_t lo;

    if (is_unsigned) {
        u = va_arg(*args, unsigned long long);
    } else {
        signed long long s = va_arg(*args, signed long long);
        u = (unsigned long long)s;
        if (s < 0) {
            printc(buf, '-');
            char_count++;
            /* Negate as unsigned so that the most negative value does not overflow. */
            u = 0ULL - u;
        }
    }

    hi = (uint32_t)(u >> 32U);
    lo = (uint32_t)(u & 0xffffffffULL);

    /* Digits come out least significant first, so store them and print them in reverse. */
    do {
        uint32_t digit = div64_by_base(&hi, &lo, base);
        digits[num_digits] = digit_to_char(digit, base);
        num_digits++;
    } while ((hi != 0U) || (lo != 0U));

    while (num_digits > 0U) {
        num_digits--;
        printc(buf, digits[num_digits]);
        char_count++;
    }

    return char_count;
}

static size_t vprintint(char** buf, unsigned int flags, va_list* args)
{
    size_t char_count;

    if ((flags & F_LONG_LONG) != 0U) {
        char_count = vprintll(buf, flags, args);
    } else {
        char_count = vprintd(buf, flags, args);
    }

    return char_count;
}

/**
 * This is a limited printf implementation. The format string only supports integer, string and
 * char arguments. That is, 'd', 'u' or 'x', 's' and 'c' specifiers, respectively. For integers, it
 * supports the none, 'l' and 'll' lengths. It does not support any flags, width or precision
 * fields. If present, this fields are ignored.
 *
 * Note this does not follow the C lib vsnprintf specification. It returns the numbers of
 * characters written to the buffer, and changes fmt to point to the first character that was not
 * printed.
 */
size_t vsnprintk(char* buf, size_t buf_size, const char** fmt, va_list* args)
{
    char* buf_it = buf;
    size_t buf_left = buf_size;
    const char* fmt_it = *fmt;
    va_list args_tmp;

    while ((*fmt_it != '\0') && (buf_left > 0U)) {
        if ((*fmt_it) != '%') {
            printc(&buf_it, *fmt_it);
            buf_left--;
        } else {
            unsigned int flags;
            bool ignore_char;
            size_t arg_char_count = 0;

            fmt_it++;
            flags = 0;
            if (*fmt_it == 'l') {
                fmt_it++;
                flags = flags | F_LONG;
                if (*fmt_it == 'l') {
                    fmt_it++;
                    flags = flags | F_LONG_LONG;
                }
            }

            do {
                ignore_char = false;
                switch (*fmt_it) {
                    case 'x':
                    case 'X':
                        flags = flags | F_BASE16;
                        __attribute__((fallthrough));
                    case 'u':
                        flags = flags | F_UNSIGNED;
                        __attribute__((fallthrough));
                    case 'd':
                    case 'i':
                        va_copy(args_tmp, *args);
                        arg_char_count = vprintint(NULL, flags, &args_tmp);
                        if (arg_char_count <= buf_left) {
                            (void)vprintint(&buf_it, flags, args);
                        }
                        break;
                    case 's':
                        va_copy(args_tmp, *args);
                        arg_char_count = prints(NULL, va_arg(args_tmp, char*));
                        if (arg_char_count <= buf_left) {
                            (void)prints(&buf_it, va_arg(*args, char*));
                        }
                        break;
                    case 'c':
                        arg_char_count = 1;
                        if (arg_char_count <= buf_left) {
                            printc(&buf_it, (char)va_arg(args_tmp, int));
                        }
                        break;
                    case '%':
                        arg_char_count = 1;
                        if (arg_char_count <= buf_left) {
                            printc(&buf_it, *fmt_it);
                        }
                        break;
                    default:
                        ignore_char = true;
                        break;
                }
            } while (ignore_char);

            if (arg_char_count <= buf_left) {
                buf_left -= arg_char_count;
            } else {
                while (*fmt_it != '%') {
                    fmt_it--;
                }
                break;
            }
        }
        fmt_it++;
    }

    *fmt = fmt_it;
    return buf_size - buf_left;
}
