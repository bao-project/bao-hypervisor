## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=asclin_uart/asclin_uart.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += asclin_uart
endif
