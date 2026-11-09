## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=pl011_uart/pl011_uart.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += pl011_uart
endif
