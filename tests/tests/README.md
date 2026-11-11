<!-- SPDX-License-Identifier: Apache-2.0 -->
<!-- Copyright (c) Bao Project and Contributors. All rights reserved -->

# Bao tests

This directory holds the tests that [Bao Kao](../kao) builds into guest images
and runs on a target platform, plus the environments they run in.

```
tests
├── README.md
├── check_ids.py
├── envs                          one directory per environment
│   └── baremetal
│       ├── qemu-aarch64-virt.yaml
│       └── zcu104.yaml
└── src
    ├── 00_generic                tests for every platform
    │   ├── 0000_boot.c
    │   └── 0001_irq.c
    ├── 01_arch                   mirrors src/arch, e.g. 00_armv8/aarch64/00_el.c
    └── 02_platform               mirrors src/platform, e.g. 00_qemu-aarch64-virt/00_uart.c
```

Run them from the repository root with `make tests PLATFORM=<platform>`;
`KAO_TESTS` selects IDs, `KAO_EXCLUDE_TAGS` (default `nightly,manual`) keeps
the default run to what a pull request should execute, and `KAO_ARGS`
forwards further kao options (`--tags`, `--env`, `-l`, ...).

## Source tree

Test sources live under `src` in three categories:

1. `00_generic`: tests that apply to every platform. Files sit directly in the
   directory and are named `FFFF_name.c`.
2. `01_arch`: one subdirectory per hypervisor architecture, `SS_<ARCH>`, with
   `<ARCH>` the value of `ARCH` in `src/platform/<platform>/platform.mk`
   (`armv8`, `riscv`, ...). Inside, tests may sit at the top level or in nested
   directories named after the variables the hypervisor build selects sources
   with: `ARCH_SUB` (`aarch64`, `aarch32`, `riscv64`, `riscv32`),
   `ARCH_PROFILE` (`armv8-a`, `armv8-r`), `ARCH_PROFILE/ARCH_SUB`, and
   `arch_mem_prot` (`mmu`, `mpu`, and `spmp` when it lands). Files are named
   `FF_name.c`.
3. `02_platform`: one subdirectory per platform, `SS_<PLATFORM>`, with
   `<PLATFORM>` the name used in `src/platform`. Files are named `FF_name.c`.

For the platform given to `make tests`, `tests/tests.mk` hands kao every
generic test, the arch subtree matching the platform's `ARCH` (and only the
nested directories matching its `ARCH_SUB`, `ARCH_PROFILE` and
`arch_mem_prot`), and the platform subtree with its name, the same way
`src_dirs` is composed for the hypervisor build. kao itself knows nothing about this layout: it compiles and
runs only the sources it is given, so platform-specific code does not have to
build elsewhere.

## Writing a test

```c
#include "kao.h"

static void gen_boot_vm(void)
{
    if (cpu_is_master()) {
        KAO_PASS("System booted successfully!\n");
    }
}
KAO_TEST(00_00_00_00, gen_boot_vm, TAGS(integration, boot, smoke), ENVS(baremetal),
    "Check that baremetal guest boots successfully");
```

### Naming

Test functions are named `<scope>_<module>_<what>`:

| # | Part | Values |
|---|------|--------|
| 1 | scope | `gen`, `arch` or `plat`, matching the category directory the file is in |
| 2 | module | the file's module name without its number: `boot`, `irq`, `gic`, `mem`, ... |
| 3 | what | what the function checks, in a few words: `vm`, `all_cpus`, `timer`, `eoi` |

Examples: `gen_boot_vm`, `gen_boot_all_cpus`, `gen_irq_timer`, `arch_gic_eoi`,
`plat_uart_passthrough`. The name is what kao prints next to the ID when the
test runs, and since selected sources are compiled as one unit the prefix
also keeps names from clashing across files. This is a convention, not
checked by anything.

`KAO_TEST` registers an ordinary `static void fn(void)` function with its ID,
tags, environments and description; a non-static function or another
signature fails to compile at the registration line. Tests that are not
selected for a run are left out of the guest binary. Selected sources are
compiled as one unit, so keep static names and file-level macros unique across
test files. Every CPU runs the function; only failures recorded on the master
CPU count. Assertions
(`EXPECTED_EQUAL`, `EXPECTED_TRUE`, `KAO_FAIL`, ...) and kao commands
(`COMMAND_SET_TIMEOUT`, `COMMAND_SEND_CHAR`, ...) come with `kao.h`.

Environments name the directories under `envs`; a test runs once in every
listed environment that has a `<platform>.yaml` for the target platform.

## Tags

Tags drive selection: `make tests PLATFORM=... KAO_ARGS="--tags functional,irq"`
runs the tests carrying both, `--exclude-tags nightly` drops those carrying
that one. Matching is case-insensitive; write tags in lower case. Every test
carries a type, a suite, the scope of its file, and the run sets it belongs
to, then whatever else is useful:

| # | Kind | Values | Where |
|---|------|--------|-------|
| 1 | Type: what the test is (exactly one) | `unit`, `functional`, `integration`, `regression`, `stress`, `perf` | `TAGS(...)` of the test |
| 2 | Suite: what the test targets (exactly one) | `boot`, `irq`, `timer`, `uart`, `mem`, `cpu`, `smp`, ... | `TAGS(...)` of the test |
| 3 | Scope: where the test applies | `arch` plus the arch names (`armv8`, `aarch64`, `riscv`), or `platform` plus the platform name | `FILE_TAGS(...)` once in the file |
| 4 | Run set: exceptions to the default run (any number) | `smoke`, `nightly`, `manual` | `TAGS(...)` of the test |

### Types

Most tests here run inside a guest, so the definitions say where the code
under test is exercised from.

| # | Type | Definition |
|---|------|------------|
| 1 | `unit` | A white-box test of hypervisor code: it calls a hypervisor function directly, inside a Bao build made for testing, with no guest in between. Reserved for that; none exist yet. |
| 2 | `functional` | A black-box test of one hypervisor mechanism through the interface the guest sees, with one expected outcome. One mechanism is one thing Bao does on the guest's behalf: trapping and emulating a register, delivering one interrupt from one source, answering one PSCI or SBI call, mapping one memory region, forwarding one IPI. The test may use whatever the guest runtime and kao already provide to set the stage (boot, a timer, a character sent on the serial line); that is the harness, not the thing under test. Runs in seconds, keeps no state beyond the function. If the outcome depends on two mechanisms interacting, or on another VM, it is not a functional test. |
| 3 | `integration` | Several mechanisms, several VMs, or the whole boot path together: all CPUs coming up, a device passed through end to end, two VMs exchanging data through shared memory. |
| 4 | `regression` | Reproduces one bug that was fixed and names it in the description. Its shape may be that of a functional or an integration test; the type says why it exists. |
| 5 | `stress` | Loops, races and long runs meant to shake out timing and resource problems. Minutes; usually `nightly`. |
| 6 | `perf` | Measures and reports numbers rather than passing or failing on them. |

### Run sets

The default run, what a pull request executes, is every test that is not
excluded: `make tests` passes `--exclude-tags nightly,manual` unless
`KAO_EXCLUDE_TAGS` says otherwise. A new test is therefore in the default run
unless it opts out.

| # | Run set | Meaning |
|---|---------|---------|
| 1 | `smoke` | The handful of tests that prove a platform boots at all; run first, run everywhere. |
| 2 | `nightly` | Too slow or too noisy for a pull request; the nightly job runs `--tags nightly`. |
| 3 | `manual` | Needs a person, a specific board or an external setup; never run by CI. |

Generic tests carry no scope tag; not being `arch` or `platform` is what makes
them generic. Scope goes in `FILE_TAGS` because it holds for the whole
file, which sits under `01_arch` or `02_platform` anyway:

```c
#include "kao.h"

FILE_TAGS(arch, armv8, aarch64);

static void arch_cpu_el1(void) { ... }
KAO_TEST(01_00_00_00, arch_cpu_el1, TAGS(functional, cpu), ENVS(baremetal),
    "Check that the guest runs at EL1 under the hypervisor");
```

This is a convention, checked by review; kao matches tags and knows nothing
about their meaning. New suite names are fine when a new area appears; list
them here.

## Test IDs

IDs are eight digits written as `CC_SS_FF_TT` and follow from the location of
the file:

| # | Field | Meaning |
|---|-------|---------|
| 1 | `CC` | Category: `00` generic, `01` arch, `02` platform. |
| 2 | `SS` | Two-digit prefix of the subdirectory (`00_armv8`, `00_qemu-aarch64-virt`). Generic tests have no subdirectory: `SS` and `FF` together are the four-digit file prefix (`0001_irq.c`). |
| 3 | `FF` | Two-digit prefix of the file (`00_el.c`). It must be unique across the whole subdirectory tree, nested directories included. |
| 4 | `TT` | Number of the test inside the file, assigned by the author, starting at `00`. |

Examples: `00_00_01_01` is the second test of `00_generic/0001_irq.c`,
`01_00_00_00` would be the first test of `01_arch/00_armv8/aarch64/00_el.c`,
and `02_00_00_00` the first test of `02_platform/00_qemu-aarch64-virt/00_uart.c`.

Assigning IDs is the responsibility of whoever adds the test. The scheme is a
Bao convention, not something kao understands: `check_ids.py` in this
directory verifies that each ID matches its file location and that no two
tests share an ID. It runs before every `make tests` (`make check-test-ids`
runs it alone) and in the code-quality CI job. Pick the next free directory or
file prefix when adding a subdirectory or file, and never renumber existing
ones: IDs are meant to stay stable so results can be compared across runs.
