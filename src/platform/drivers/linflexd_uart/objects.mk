## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=linflexd_uart/linflexd_uart.o 

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += linflexd_uart
endif
