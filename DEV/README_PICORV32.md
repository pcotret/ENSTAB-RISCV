# Installation d'un processeur RISCV PicoRV32 sur FPGA NEXYS 4 DDR

**Step1**: Créer un dossier pour le projet.

**Step2**: télécharger l'ensemble du contenu du dossier DEV: https://github.com/SylvainEnsta/RISCV/tree/master/DEV

**Step3**: lancer la commande:
./setup.py init install --user
Nota: l'installation du GCC RICV est longue, patienter...

**step4**: 
dans ~/.local/lib/python3.7/site-packages/litex-0.2.dev0-py3.7.egg/litex/soc/software/common.mak

  modifier la variable "PYTHON?=python3" en "PYTHON?=python3.7"
  
**step5**: lancer la commande
export PATH=$PATH:./riscv64/bin/

**step6**: lancer la commande
./buildNexys4ddr.py

**step7**: lancer la commande
./launch.sh
