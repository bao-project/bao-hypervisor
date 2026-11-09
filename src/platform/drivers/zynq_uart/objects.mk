## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=zynq_uart/zynq_uart.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += zynq_uart
endif
