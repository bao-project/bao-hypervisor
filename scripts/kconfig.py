#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) Bao Project and Contributors. All rights reserved.

"""Bao Kconfig helper.

seed: create the build's .config (KCONFIG_CONFIG) by layering the platform
      defconfig, then the VM config folder defconfig on top, then Kconfig
      defaults for the rest, always pinning the platform given in
      BAO_PLATFORM.
sync: re-resolve .config against the Kconfig tree and generate the make
      fragment (auto.conf) and C header (autoconf.h) consumed by the build.
list: print every visible option with its value and which layer decided it
      (default/platform/config/modified), plus the fixed platform facts.
menuconfig: run the interactive frontend on the build's .config.
"""

import argparse
import os
import re
import sys

import kconfiglib


def platform_symbol(kconf, platform):
    name = 'PLAT_' + platform.upper().replace('-', '_')
    sym = kconf.syms.get(name)
    if sym is None:
        sys.exit(f'kconfig: platform {platform} has no {name} symbol')
    return sym


def check_platform(kconf, platform):
    configured = kconf.syms['PLATFORM'].str_value
    if configured != platform:
        sys.exit(f'kconfig: .config is for platform {configured} but the '
                 f'build targets {platform}; remove the build directory to '
                 'reconfigure')


def emitted_syms(kconf):
    # Artifacts expose facts and values, not choice selector symbols; the
    # platform identity symbol is the exception as code gates on it
    for sym in kconf.unique_defined_syms:
        if sym.choice and not sym.name.startswith('PLAT_'):
            continue
        yield sym


def write_auto_conf(kconf, path):
    with open(path, 'w') as f:
        for sym in emitted_syms(kconf):
            if sym.orig_type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                if sym.tri_value > 0:
                    f.write(f'CONFIG_{sym.name}=y\n')
            elif sym.str_value:
                f.write(f'CONFIG_{sym.name}={sym.str_value}\n')


def write_auto_conf_header(kconf, path):
    with open(path, 'w') as f:
        for sym in emitted_syms(kconf):
            # CONFIG_SRC is a build input consumed by make, not by code
            if sym.name == 'CONFIG_SRC':
                continue
            if sym.orig_type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
                if sym.tri_value > 0:
                    f.write(f'#define CONFIG_{sym.name} 1\n')
            elif sym.orig_type is kconfiglib.STRING:
                if sym.str_value:
                    f.write(f'#define CONFIG_{sym.name} "{sym.str_value}"\n')
            elif sym.str_value:
                f.write(f'#define CONFIG_{sym.name} {sym.str_value}\n')


def check_warnings(kconf):
    if kconf.warnings:
        for warning in kconf.warnings:
            print(warning, file=sys.stderr)
        sys.exit('kconfig: invalid configuration input')
    for sym in kconf.unique_defined_syms:
        if sym.user_value is None or sym.visibility:
            continue
        if sym.orig_type in (kconfiglib.BOOL, kconfiglib.TRISTATE):
            mismatch = sym.user_value != sym.tri_value
        else:
            mismatch = sym.user_value != sym.str_value
        if mismatch:
            sys.exit(f'kconfig: CONFIG_{sym.name} is fixed by the platform '
                     'selection and cannot be set in a defconfig')


def defconfig_keys(path):
    keys = set()
    for line in open(path):
        m = re.match(r'# CONFIG_([A-Za-z0-9_]+) is not set$|'
                     r'CONFIG_([A-Za-z0-9_]+)=', line)
        if m:
            keys.add(m.group(1) or m.group(2))
    return keys


def load_defconfigs(kconf, paths):
    # A later layer overriding an earlier one is the point of layering,
    # not a suspect double assignment
    kconf.warn_assign_override = False
    kconf.warn_assign_redun = False
    for i, path in enumerate(paths):
        kconf.load_config(path, replace=(i == 0))


def list_options(kconf, platform, plat_file, cfg_file, config_src):
    plat_keys = defconfig_keys(plat_file) if plat_file else set()
    cfg_keys = defconfig_keys(cfg_file) if cfg_file else set()
    load_defconfigs(kconf, [f for f in (plat_file, cfg_file) if f])
    platform_symbol(kconf, platform).set_value(2)
    if config_src:
        kconf.syms['CONFIG_SRC'].set_value(config_src)
        cfg_keys.add('CONFIG_SRC')
    expected = {sym.name: sym.str_value for sym in kconf.unique_defined_syms}
    if os.path.exists(os.environ.get('KCONFIG_CONFIG', '.config')):
        kconf.load_config()
    for sym in kconf.unique_defined_syms:
        node = sym.nodes[0]
        if sym.choice or not node.prompt or not sym.visibility:
            continue
        if sym.str_value != expected.get(sym.name):
            source = 'modified'
        elif sym.name in cfg_keys:
            source = 'config'
        elif sym.name in plat_keys:
            source = 'platform'
        else:
            source = 'default'
        default = (kconfiglib.expr_str(sym.defaults[0][0]) if sym.defaults
                   else '-')
        help_text = (node.help or '').strip().split('\n')[0]
        print(f'CONFIG_{sym.name:<21} {kconfiglib.TYPE_TO_STR[sym.orig_type]:<5} '
              f'{sym.str_value:<8} (default {default}) [{source}] {help_text}')
    for sym in kconf.unique_defined_syms:
        if sym.orig_type is kconfiglib.STRING and sym.str_value and \
                not any(node.prompt for node in sym.nodes):
            print(f'CONFIG_{sym.name:<21} fixed {sym.str_value}')


def peek_platform():
    # O= builds carry the platform in the .config rather than the environment
    if not os.path.exists(os.environ.get('KCONFIG_CONFIG', '.config')):
        sys.exit('kconfig: no .config yet; seed one with a '
                 '<platform>_defconfig target first')
    peek = kconfiglib.Kconfig(os.environ.get('KCONFIG_ROOT', 'Kconfig'),
                              suppress_traceback=True)
    peek.load_config()
    return peek.syms['PLATFORM'].str_value


def run_menuconfig():
    import menuconfig

    node_str = menuconfig._node_str

    def blank_aware_node_str(node):
        # Empty comments separate option and fact blocks in the menu view
        if node.item is kconfiglib.COMMENT and not node.prompt[0]:
            return ''
        # @SYM@ placeholders in comments display the resolved symbol value
        return re.sub(r'@([A-Z0-9_]+)@',
                      lambda m: menuconfig._kconf.syms[m.group(1)].str_value,
                      node_str(node))

    menuconfig._node_str = blank_aware_node_str
    sys.argv = [sys.argv[0], os.environ.get('KCONFIG_ROOT', 'Kconfig')]
    menuconfig._main()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('command', choices=['seed', 'sync', 'list', 'menuconfig'])
    parser.add_argument('--platform-defconfig')
    parser.add_argument('--config-defconfig')
    parser.add_argument('--config-src')
    parser.add_argument('--auto-conf')
    parser.add_argument('--auto-header')
    args = parser.parse_args()

    platform = os.environ.get('BAO_PLATFORM')
    if not platform and args.command == 'seed':
        sys.exit('kconfig: BAO_PLATFORM not set')

    if args.command == 'menuconfig':
        run_menuconfig()
        return

    kconf = kconfiglib.Kconfig(os.environ.get('KCONFIG_ROOT', 'Kconfig'),
                               suppress_traceback=True)

    defconfigs = [f for f in (args.platform_defconfig,
                              args.config_defconfig) if f]
    if args.command == 'seed':
        load_defconfigs(kconf, defconfigs)
        platform_symbol(kconf, platform).set_value(2)
        if args.config_src:
            kconf.syms['CONFIG_SRC'].set_value(args.config_src)
        check_warnings(kconf)
        check_platform(kconf, platform)
        kconf.write_config()
    elif args.command == 'sync':
        kconf.load_config()
        check_warnings(kconf)
        if platform:
            check_platform(kconf, platform)
        kconf.write_config()
        write_auto_conf_header(kconf, args.auto_header)
        write_auto_conf(kconf, args.auto_conf)
    else:
        if not platform:
            platform = peek_platform()
        list_options(kconf, platform, args.platform_defconfig,
                     args.config_defconfig, args.config_src)


if __name__ == '__main__':
    main()
