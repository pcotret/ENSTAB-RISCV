

```
                    ______ _   _  _____ _______                         
                   |  ____| \ | |/ ____|__   __|/\                      
                   | |__  |  \| | (___    | |  /  \                     
                   |  __| | . ` |\___ \   | | / /\ \                    
              ____ | |____| |\  |____) |  | |/ ____ \                   
             |  _ \|______|_| \_|_____/   |_/_/    \_\                  
             | |_) |_ __ ___| |_ __ _  __ _ _ __   ___                  
             |  _ <| '__/ _ | __/ _` |/ _` | '_ \ / _ \                 
             | |_) | | |  __| || (_| | (_| | | | |  __/                 
             |____/|_|  \___|\__\__,_|\__, |_| |_|\___|                 
                                       __/ |                            
  _____  _____  _____  _______      __|___/__           _           _   
 |  __ \|_   _|/ ____|/ ____\ \    / / |  __ \         (_)         | |  
 | |__) | | | | (___ | |     \ \  / /  | |__) _ __ ___  _  ___  ___| |_ 
 |  _  /  | |  \___ \| |      \ \/ /   |  ___| '__/ _ \| |/ _ \/ __| __|
 | | \ \ _| |_ ____) | |____   \  /    | |   | | | (_) | |  __| (__| |_ 
 |_|  \_|_____|_____/ \_____|   \/     |_|   |_|  \___/| |\___|\___|\__|
                                                      _/ |              
                                                     |__/               
```

# 
#### Projet éducatif visant à évaluer l'implémentation d'un processeur d'architecture RISC-V sur un FPGA en utilisant les outils de conception Migen et Litex.

RISC-V (http://riscv.org) est une architecture de processeur basée sur un jeu d'instruction moderne, totalement ouvert et libre de droits. La première étape de ce projet sera d'analyser les différents modèles de processeur disponibles et proposés à la communauté et ayant fait l'objet d'une implémentation sur silicium réussie.

Nous nous intéresserons ensuite aux outils de conception Migen et Litex qui proposent une alternative au langage VHDL et Verilog en offrant un flot de conception entièrement réalisable en python.

Nous tâcherons enfin de réaliser une implémentation via ces outils de conception et de réaliser l'execution d'un programme en langage C sur un FPGA.



Vous trouverez sur ce GitHub les dossiers suivants:

### DEV:

Ce dossier contient tous les fichiers/dossiers nécéssaires  à l'implémentation du processeur sur le FPGA.

| Nom               | Description                                                  |
| ----------------- | ------------------------------------------------------------ |
| README.md         | Les étapes d'installation.                                    |
| setup.py          | Télécharger et installer les modules nécéssaires.             |
| nexys4ddr.py      | Décrire sa plateforme.                                        |
| buildNexys4ddr.py | Réaliser le build.                                            |
| load.py           | Charger le Bitstream.                                         |
| launch.sh         | Lancer le load et implémenter le firmware compilé.            |
| firmware          | Dossier incluant les fichiers en langage C nécéssaires au firmware. |
| module            | Dossier incluant nos modules.                                |



### Rapport:

Ce dossier contient tous les fichiers résultant de notre analyse et décrivant étape par étape le processus d'implémentation du processeur sur le FPGA.

| Nom                 | Description                                                  |
| ------------------- | ------------------------------------------------------------ |
| 01_Analyse.md       | Analyse préliminaire sur l'architecture RISC-V et les projets open source |
| 02_Migen.md         | Migen, c'est quoi, c'est où?                                 |
| 03_Litex.md         | Litex, c'est quoi, c'est où?                                 |
| 04_Environnement.md | Choix du processeur et du FPGA.                              |
| 05_Plateforme.md    | Décrire sa plateforme avec Migen/Litex.                      |
| 06_Modules.md       | Décrire ses modules avec Migen/Litex.                        |
| 07_Architecture.md  | Builder son architecture avec Litex.                         |
| 08_Firmware.md      | Comment interagir avec le processeur.                        |
| 09_Liens_utiles.md  | La liste des liens et des sources utiles à ce projet.        |

