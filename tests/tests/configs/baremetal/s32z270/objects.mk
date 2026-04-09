## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.
this_dir:=$(dir $(lastword $(MAKEFILE_LIST)))

config-objs-y:=plat.o

extra-objs-y+=$(this_dir)/bsp/clock_control_nxp_s32.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Cfg.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Data.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Divider.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_DividerTrigger.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_ExtOsc.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_FracDiv.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Frequency.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Gate.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_IntOsc.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Monitor.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Pll.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_ProgFreqSwitch.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Selector.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip_Specific.o
extra-objs-y+=$(this_dir)/bsp/Clock_Ip.o
extra-objs-y+=$(this_dir)/bsp/OsIf_Timer.o
extra-objs-y+=$(this_dir)/bsp/SchM_Mcu.o
extra-objs-y+=$(this_dir)/bsp/__aeabi_uldivmod.o
extra-objs-y+=$(this_dir)/bsp/__aeabi_uidiv.o
