

# Installation:

*Etape 0*: s'assurer d'avoir Python 3.5+ et les outils de développement FPGA du vendeur (Vivado). Ainsi que les drivers de la carte Nexys4-DDR.

*Etape 1*: installation de LiteX et de ses dépendances

```bash
./setup.py init install --user
```

Nota: définir les fichiers.py comme executables :

```bash
chmod +x *.py
```

Etape 2*: chemin vers le cross-compilateur RISC-V

```bash
export PATH=$PATH:./riscv64/bin/
```

Nota: dans certain cas, il est nécessaire de préciser le chemin complet vers le cross-compilateur.

*Etape 3*: Synthèse de l'architecture pour la Nexys4-DDR

```bash
./buildNexys4ddr.py
```

*Etape 4*: Lancement du noyau

```bash
./launch.sh
```

