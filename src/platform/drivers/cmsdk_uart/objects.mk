## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=cmsdk_uart/cmsdk_uart.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += cmsdk_uart
endif
