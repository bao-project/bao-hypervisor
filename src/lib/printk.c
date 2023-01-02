/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <printk.h>

#include <string.h>
#include <stdarg.h>
#include <console.h>

#define PRINT_TEXT_LEN 0x100

size_t vsprintk(char *buf, const char *fmt, va_list args)
{
    char *str;
    str = buf;
    size_t len = strnlen(fmt, PRINT_TEXT_LEN);
    for (; *fmt; ++fmt) {
        if ((*fmt != '%') && (*fmt != '\n') && (*fmt != '\t')) {
            *str++ = *fmt;
            continue;
        }

        if (*fmt == '%') {
            ++fmt;
            bool is_unsigned = false;
            bool zero_padding = false;
            bool is_long = false;

            if (*fmt == '0') {
                ++fmt;
                zero_padding = true;
            }

           if (*fmt == 'l') {
                ++fmt;
                is_long = true;
           }

            switch (*fmt) {
                case 'x': {
                    unsigned long number = is_long ? va_arg(args, unsigned long) : va_arg(args, unsigned);
                    size_t length = is_long ? 16 : 8;
                    size_t length_in_bits = is_long ? 64 : 32;
                    uint8_t byte = 0;
                    size_t i = 0;
                    bool keep_zeros = false;

                    for (i = 0; i < length; i++) {
                        byte = number >> (length_in_bits - ((i + 1) * 4));
                        byte = byte & 0xF;
                        if (byte != 0 || i == length-1) {
                            keep_zeros = true;
                        }
                        if (keep_zeros || zero_padding) {
                            if ((byte >= 0) && (byte <= 9)) {
                                byte += 0x30;
                            } else {
                                byte += (0x61-0xa);
                            }
                            *str++ = byte;
                        }
                    }
                    break;
                }
                case 'u':
                    is_unsigned = true;
                case 'i':
                case 'd': {
                    size_t i, j, max_num_zeros, num_of_digits_uint64_t,
                        number, divisor_value_uint64_t,
                        new_div_val = 1, sw_quotient_value = 0;
                    bool keep_zeros = false;

                    if (!is_unsigned) {
                        long number_signed = is_long ? va_arg(args, long) : va_arg(args, int);
                        if (number_signed < 0) {
                            *str++ = 0x2d;
                            number_signed = -(number_signed);
                        }
                        number = number_signed;
                    } else {
                        number = is_long ? va_arg(args, unsigned long) : va_arg(args, unsigned);
                    }

                    divisor_value_uint64_t = 1000000000;
                    num_of_digits_uint64_t = 10;
                    max_num_zeros = num_of_digits_uint64_t - 1;

                    for (i = 0; i < max_num_zeros; i++) {
                        while (number >= divisor_value_uint64_t) {
                            number -= divisor_value_uint64_t;
                            ++sw_quotient_value;
                        }
                        if (sw_quotient_value != 0) keep_zeros = true;
                        if (keep_zeros || zero_padding) {
                            sw_quotient_value += 0x30;
                            *str++ = sw_quotient_value;
                        }
                        j = i;
                        while (j < (max_num_zeros - 1)) {
                            new_div_val *= 10;
                            j++;
                        }
                        sw_quotient_value = 0;
                        divisor_value_uint64_t = new_div_val;
                        new_div_val = 1;
                    }
                    *str++ = (number + 0x30);
                    break;
                }
                case 's': {
                    char *arg_string = va_arg(args, char *);
                    while (((*str = *arg_string++) && (len < PRINT_TEXT_LEN))) {
                        ++str;
                        len++;
                    }
                    break;
                }
                case 'c': {
                    char character = va_arg(args, int);
                    *str++ = character;
                    break;
                }
                case '%': {
                    *str++ = *fmt;
                    break;
                }
                case '\t': {
                    *str++ = '%';
                    *str++ = *fmt;
                    break;
                }
                case '\n': {
                    *str++ = '%';
                    *str++ = '\r';
                    *str++ = '\n';
                    break;
                }
                default: {
                }
            }
        }

        if (*fmt == '\n') {
            *str++ = '\r';
            *str++ = '\n';
        }
        if (*fmt == '\t') *str++ = *fmt;
    }
    *str = '\0';
    return strnlen(fmt, PRINT_TEXT_LEN);
}

size_t printk(const char *fmt, ...)
{
    va_list args;
    size_t i;

    char print_buffer[PRINT_TEXT_LEN];

    va_start(args, fmt);

    i = vsprintk(print_buffer, fmt, args);
    va_end(args);

    console_write(print_buffer);
    return i;
}
