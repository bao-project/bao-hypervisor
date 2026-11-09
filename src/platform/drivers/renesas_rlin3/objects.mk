## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

drivers-objs-y+=renesas_rlin3/renesas_rlin3.o

ifeq ($(earlycon_uart),y)
earlycon_uart_driver += renesas_rlin3
endif
