#!/usr/bin/env bash
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved.
#
# Resolves the addresses of a Bao panic backtrace to symbols.
#
# Usage: scripts/symbolize.sh bin/<platform>/<config>/bao.elf [log]
#
# Reads the log (stdin if omitted), finds the "[<addr>]" backtrace entries and the ELR/sepc lines
# of the internal abort dumps, and prints each with its symbol. An unstripped ELF (DEBUG=y) gives
# function, file and line through addr2line; for a stripped release ELF the symbol table that the
# build writes to bao.elf.txt before stripping gives symbol+offset.
set -eu

if [ $# -lt 1 ]; then
    echo "usage: $0 <bao.elf> [log]" >&2
    exit 1
fi
elf=$1
log=${2:-/dev/stdin}
addr2line=${ADDR2LINE:-${CROSS_COMPILE:-}addr2line}

hex16() { # $1: hexadecimal string; prints it as 16 lowercase digits so strings compare like unsigned values
    printf '%016s' "$(printf '%s' "$1" | tr 'A-F' 'a-f')" | tr ' ' '0'
}

resolve() { # $1: address as a hexadecimal string without the 0x prefix
    local out addr best name value type sym
    if out=$("$addr2line" -e "$elf" -f -p -i "0x$1" 2>/dev/null) && [ "${out#\?\?}" = "$out" ]; then
        printf '%s\n' "$out"
        return
    fi
    if [ -r "$elf.txt" ]; then
        addr=$(hex16 "$1"); best=''; name='??'
        while read -r _ value _ type _ _ _ sym _; do
            [ "$type" = FUNC ] || continue
            value=$(hex16 "$value")
            if [[ "$value" < "$addr" || "$value" == "$addr" ]] && [[ -z "$best" || "$value" > "$best" ]]; then
                best=$value; name=$sym
            fi
        done < <(grep ' FUNC ' "$elf.txt")
        if [ -n "$best" ]; then
            printf '%s+0x%x\n' "$name" $((16#$addr - 16#$best))
        else
            echo '??'
        fi
        return
    fi
    echo '??'
}

grep -aoE '\[<[0-9a-fA-F]+>\]|(ELR|sepc):[[:space:]]*0x[0-9a-fA-F]+' "$log" | while read -r entry; do
    case $entry in
    \[\<*) # a return address: point at the call instruction
        a=${entry#\[<}; a=${a%>\]}; a=$(printf '%x' $((16#$a - 1))) ;;
    *) # the faulting pc
        a=${entry##*0x} ;;
    esac
    printf '%-24s %s\n' "$entry" "$(resolve "$a")"
done
