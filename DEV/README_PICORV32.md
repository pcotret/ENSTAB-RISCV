# RISCV


init install --user


2. Install a RISC-V toolchain:
  wget https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.1.0-2019.01.0-x86_64-linux-ubuntu14.tar.gz
  tar -xvf riscv64-unknown-elf-gcc-8.1.0-2019.01.0-x86_64-linux-ubuntu14.tar.gz
  export PATH=$PATH:$PWD/riscv64-unknown-elf-gcc-8.1.0-2019.01.0-x86_64-linux-ubuntu14/bin/

Attention renommer le dossier RISCV64 et à installer dans le dossier ~/ sinon, il faut changer le export PATH


~/.local/lib/python3.7/site-packages/litex-0.2.dev0-py3.7.egg/litex/soc/software/common.mac:

modifier la variable "PYTHON?=python3" en  "PYTHON?=python3.7"
