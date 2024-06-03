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
