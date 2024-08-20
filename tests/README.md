# Bao Test Framework

## Overview

The primary goal of the Bao Test Framework is to provide the infrastructure for the testing process of Bao Project components. It encompasses three core components: (i) a C library designed for real-time test handling, (ii) a Python tool for comprehensive test management, and (iii) a build system based on Nix.
The C library and Python tool are provided in the `bao-tests` repository while the Nix packages required are available in the `bao-nix` repository. Lastly, a folder `recipes` contains all the recipes and tests.



## How to use

**1. Create a folder inside `recipes` with the following structure**

```
 tests
 ├── bao-tests     
 ├── bao-nix   
 ├── recipes  
 │   ├── RECIPE-EXAMPLE   
 │   │   ├── configs 
 │   │   ├── src  
```

The name `RECIPE-EXAMPLE` will be used as an argument when using `make`. 
The folder `configs` is used to store all the bao configs (link to docs) related to the recipe in question.
Lastly, the folder `src` is used for test sources.

**2. Create a `.nix` file in the `RECIPE-EXAMPLE` folder.**

The following code is an example of a Nix recipe to build the system with a single baremetal guest.

```nix
{
  pkgs ? import (fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/refs/tags/22.11.tar.gz";
    sha256 = "sha256:11w3wn2yjhaa5pv20gbfbirvjq6i3m7pqrq2msf0g7cv44vijwgw";
  }) {},
  platform ? " ",
  bao_cfg_repo ? " ",
  bao_cfg ? " ",
  list_tests ? " ",
  list_suites ? " ",
  log_level ? " ",
  GIC_VERSION ? " ",
  IRQC ? " ",
  IPIC ? " ",
}:

with pkgs;

let
  packages = rec {

    setup-cfg  = callPackage ../../bao-nix/pkgs/setup-cfg/setup-cfg.nix{
      inherit platform;
      inherit GIC_VERSION;
      inherit IRQC;
      inherit IPIC;
      bao-tests = ../../bao-tests;
      tests_srcs = ./src;
      baremetal_patch = ./baremetal.patch;
    };

    #Build toolchain
    toolchain = callPackage ../../bao-nix/pkgs/toolchains/${setup-cfg.toolchain_name}.nix{};

    #Build guests
    guests = [
          (callPackage (../../bao-nix/pkgs/guest/tf/baremetal.nix)
                  { 
                    inherit setup-cfg;
                    inherit toolchain;
                    guest_name = "baremetal";
                    list_tests = "";
                    list_suites = "CPU_BOOT_CHECK";
                    inherit log_level;                     
                  }
          )
      ];

    bao_cfg_repo = ./configs;
   
    #Build Hypervisor
    bao = callPackage ../../bao-nix/pkgs/bao/bao.nix 
    { 
      inherit setup-cfg;
      inherit toolchain;
      inherit bao_cfg_repo;
      inherit bao_cfg;
      inherit guests; 
      #bao_srcs_path = /home/mafs/bao-hypervisor;
    };

    # Build Firmware
    firmware = callPackage ../../bao-nix/pkgs/firmware/${platform}.nix {
      inherit toolchain;
      inherit platform;
      inherit setup-cfg;
    };
    inherit pkgs;
  };
in
  packages

```

The main fields in the recipe that should be modified for other uses are:

* **guests** - This array should include all the the guest used in the bao configuration. 
* **list_tests** - For each guest that will execute tests, this field should be filled with test names.
* **list_suits** - Similar to the previous field, but should be filled with suites (groups of tests) instead.

**3. Implement the tests**

Create a `.c` file in the `src` folder and implement the tests following the example below: 

```c
#include "testf.h"

BAO_TEST(SUITE_NAME, TEST_NAME)
{
    printf("Hello World!!!\n");
}
```

Every source file that implements tests should include the `testf.h` header.
A test is defined using the macro `BAO_TEST` with `SUITE_NAME` and `TEST_NAME` as arguments to identify the test in the previous step.

**4. Run the framework**

From the **bao-hypervisor** main directory, to run the test framework you should use the following command:

```
make tests PLATFORM=platform RECIPE=RECIPE_EXAMPLE
```