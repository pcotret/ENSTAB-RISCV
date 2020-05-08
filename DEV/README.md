# RISCV

Ce dossier contient tous les fichiers/dossiers nécéssaires  à l'implémentation du processeur sur le FPGA.

| Nom                                      | Description                                                  |
| ---------------------------------------- | ------------------------------------------------------------ |
| [README.md](./README.md)                 | Les étapes d'installation                                    |
| [setup.py](./setup.py)                   | Télécharger et installer les modules nécéssaires             |
| [nexys4ddr.py](./nexys4ddr.py)           | Décrire sa plateforme                                        |
| [buildNexys4ddr.py](./buildNexys4ddr.py) | Réaliser le build                                            |
| [load.py](./load.py)                     | Charger le bitstream                                         |
| [launch.sh](./launch.sh)                 | Lancer le load et implémenter le firmware compilé            |
| [firmware](./firmware)                   | Dossier incluant les fichiers en langage C nécéssaires au firmware |
| [module](./module)                       | Dossier incluant nos modules                                 |

## Installation

### Prérequis

- Python 3.5+
- Outils de développement Vivado de Xilinx : https://www.xilinx.com/support/download.html
- Outils en ligne de commande Digilentinc : https://reference.digilentinc.com/reference/software/adept/start
  - Récupérer les **Utilities - Latest Downloads**

### Préparation et lancement de la démo

```bash
# Installation de LiteX et de ses dépendances
chmod +x *.py
./setup.py init install --user
# Chemin du cross-compilateur
export PATH=$PATH:./riscv64/bin/
# Synthèse de l'architecture pour la Nexys4-DDR
./buildNexys4ddr.py
# Lancement du noyau
./launch.sh
```

