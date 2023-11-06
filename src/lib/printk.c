/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <printk.h>

#define F_LONG     (1U << 0U)
#define F_UNSIGNED (1U << 1U)
#define F_BASE16   (1U << 2U)

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
        printc(buf, digit_to_char(digit, base));
        char_count++;
    }

    return char_count;
}

/**
 * This is a limited printf implementation. The format string only supports integer, string and
 * char arguments. That is, 'd', 'u' or 'x', 's' and 'c' specifiers, respectively. For integers, it
 * only supports the none and 'l' lengths. It does not support any flags, width or precision
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
                } // ignore long long
            }

            do {
                ignore_char = false;
                switch (*fmt_it) {
                    case 'x':
                    case 'X':
                        flags = flags | F_BASE16;
                    /* fallthrough */
                    case 'u':
                        flags = flags | F_UNSIGNED;
                    /* fallthrough */
                    case 'd':
                    case 'i':
                        va_copy(args_tmp, *args);
                        arg_char_count = vprintd(NULL, flags, &args_tmp);
                        if (arg_char_count <= buf_left) {
                            (void)vprintd(&buf_it, flags, args);
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
