{
  description = "Bao dev environment with pinned toolchains, Python deps, and QEMU";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };


  in {
    devShells.${system}.default = pkgs.mkShell {
      name = "bao-dev";

      buildInputs = with pkgs; [
        git curl wget tree vim nano sudo gnumake

        nettools socat xterm

        python3 python3Packages.pip python3Packages.psutil
        python3Packages.pyserial

        nodejs nodePackages.cspell
        bison flex gawk dtc ninja pkg-config
        enchant 

      ];
    };
  };
}
