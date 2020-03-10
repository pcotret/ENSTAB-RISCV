# RISCV

Ce dossier contient tous les fichiers/dossiers nécéssaires  à l'implémentation du processeur sur le FPGA.

| Nom               | Description                                                  |
| ----------------- | ------------------------------------------------------------ |
| README.md         | Les étapes d'installation                                    |
| setup.py          | Télécharger et installer les modules nécéssaires             |
| nexys4ddr.py      | Décrire sa plateforme                                        |
| buildNexys4ddr.py | Réaliser le build                                            |
| load.py           | Charger le Bitstream                                         |
| launch.sh         | Lancer le load et implémenter le firmware compilé            |
| firmware          | Dossier incluant les fichiers en langage C nécéssaire au firmware |
| module            | Dossier incluant nos modules.                                |





#### Voici les étapes à suivre pour réaliser l'installation:

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

