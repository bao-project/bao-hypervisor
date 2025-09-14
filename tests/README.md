# Bao Test Framework

### Prerequesites 
If you prefer not to use Docker or Nix, you can install the required dependencies manually:
```sh
sudo apt-get update && sudo apt-get install -y \
  git curl wget tree vim nano sudo make net-tools socat xterm \
  python3 python3-pip nodejs npm bison flex gawk device-tree-compiler \
  ninja-build pkg-config enchant

pip install psutil pyserial
```


### Clone docker
To pull the Docker image, run the following command:

```sh
docker pull baoproject/bao-tests:latest
```

### Run the Test framework inside Docker

First, start Docker with the following command in the repo's root directory:
```sh
docker run --rm -it \
  -v "$(pwd):$(pwd)" \
  -w "$(pwd)" \
  -u $(id -u):$(id -g) \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  baoproject/bao-tests:latest
```

Then, initialize the Nix environment:
```sh
nix develop ./tests/
```

Finally, run the test framework with:
```sh
make tests PLATFORM=<platform_name> RECIPE=<target_recipe>
```

Currently, the following platforms are available:
- QEMU RV64 virt (qemu-aarch64-virt)
- QEMU Aarch64 virt (qemu-aarch64-virt)
- FVP-A AArch64 (fvp-a)
- FVP-R AArch64 (fvp-r)
