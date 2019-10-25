# RISCV

*Etape 0*: s'assurer d'avoir Python 3.5+ et l'outils de développement FPGA du vendeur (vivado).

*Etape 1*: installation de LiteX et de ses dépendances

```bash
./setup.py init install --user
```

*Etape 2*: chemin vers le cross-compilateur RISC-V

```bash
export PATH=$PATH:./riscv64/bin/
```

*Etape 3*: Synthèse de l'architecture pour la Nexys4-DDR

```bash
./buildNexys4ddr.py
```

*Etape 4*: Lancement du noyau

```bash
./launch.sh
```

