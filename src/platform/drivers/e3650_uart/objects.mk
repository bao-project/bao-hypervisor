## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=e3650_uart/e3650_uart.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += e3650_uart
endif
