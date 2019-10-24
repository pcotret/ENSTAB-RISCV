# 1ère étape : choix d'une implémentation RISC-V

De nombreuses implémentations du processeur RISC-V sont disponibles sur la toile et notamment sur GitHub. La première étape de ce projet consiste donc à en sélectionner une. Mais avant de débuter, petit rappel sur les différentes spécifications proposées par la fondation RISC-V.

## Spécifications:

Le RISC-V est modulaire et son architecture se compose d'une base de traitement des entiers, à laquelle peut être adjointe des extensions. La spécification est disponible ici:https://riscv.org/specifications/

L’architecture résultante est donnée par un code : RV XY, avec RV pour RISC-V, X la longueur en bits des instructions et Y la base et les extensions ajoutées.

Les deux bases possibles, sont "I" pour la gestion des entiers et "E " indiquant un jeu d'instructions réduit pour l'embarqué :

| Base   | Version | Status   |
| ------ | ------- | -------- |
| RVWMO  | 2.0     | Ratified |
| RV32I  | 2.1     | Ratified |
| RV64I  | 2.1     | Ratified |
| RV32E  | 1.9     | Draft    |
| RV128I | 1.7     | Draft    |

Les extensions disponibles sont listées dans le tableau ci-après, la page WIKI sur le sujet: https://fr.wikipedia.org/wiki/RISC-V est également complète.

A noter la lettre "G" qui est l'acronyme de "Général Purpose" et qui inclue les lettres IMAFD. Le plus simple processeur RISC-V pour l’embarqué serait le RV32E et le généraliste le plus commun le RV64G.

| Extensions:                                                  |
| ------------------------------------------------------------ |
| M – Standard Extension for Integer Multiplication and Division |
| A – Standard Extension for Atomic Instructions               |
| F – Standard Extension for Single-Precision Floating-Point   |
| D – Standard Extension for Double-Precision Floating-Point   |
| G – Shorthand for the base and above extensions              |
| Q – Standard Extension for Quad-Precision Floating-Point     |
| L – Standard Extension for Decimal Floating-Point            |
| C – Standard Extension for Compressed Instructions           |
| B – Standard Extension for Bit Manipulation                  |
| J – Standard Extension for Dynamically Translated Languages such as C#, Go, Haskell, Java, JavaScript, OCaml, PHP, Python, R, Ruby, Scala or WebAssembly |
| T – Standard Extension for Transactional Memory              |
| P – Standard Extension for Packed-SIMD Instructions          |
| V – Standard Extension for Vector Operations                 |
| N – Standard Extension for User-Level Interrupts             |
| H – Standard Extension for Hypervisor                        |



## Tour d'horizon des implémentations

Le site officiel de la fondation RISC-V propose une liste de projets qui s'efforcent de respecter les spécifications RISC-V: https://riscv.org/risc-v-cores/, une liste plus complète existe également sur GitHub:  https://github.com/riscv/riscv-cores-list.

Afin d'affiner notre sélection, nous nous sommes imposés quelques critères:

- La licence: de préférence libre
- Le langage: de préférence VHDL, Verilog, SystemeVerilog
- Le projet doit être disponible sous GitHub
- Le projet doit être suffisamment documenté
- Le projet doit être régulièrement mis à jour
- Le projet a t'il été testé sur FPGA?



Voici une synthèse des projets ayant retenu notre attention :

1. **PicoRV32** |Verilog|RV32I/E[MC]|Dernière màj: -10j |Licence: ISC (libre)

   https://github.com/cliffordwolf/picorv32.git |Auteur: indépendant (Clifford Wolf)

   Bien référencé, et testé sur différentes puces, le projet est open source et très régulièrement mis à jour. Il est possible de trouver plusieurs exemple sur la toile d'utilisation de ce processeur (ex: https://github.com/Jesus89/picorv32-c-examples).

   La documentation y est complète, la chaine de compilation y est décrite ainsi que différents Testbenches.

   

2. **Potato Processor** |VHDL|RV32I|Dernière màj: 1 an|Licence: BSD (libre).

   https://github.com/skordal/potato.git |Auteur: indépendant (Kristian Klomsten Skordal)

   Evoqué lors de notre première réunion, la page gitHub de ce projet est bien documentée mais semble inactive depuis un an. Nous ne la retrouvons pas non plus dans la liste des projets référencés sur la page officielle.

   

3. **DarkRISCV** |Verilog|RV32I|Dernière màj: -1mois|Licence: BSD (libre).

   https://github.com/darklife/darkriscv.git | Auteur: indépendant (NC)

   Le projet est récent et référencé sur la liste officielle. La documentation y est présente, mais le projet ne semble pas terminé. L'auteur précise que certaine fonctionnalités sont toujours en attente de tests.

   A suivre..

   

4. **SCR1** |systemVerilog|RV32I\|E[MC] ISA|Dernière màj: -1mois|Licence: SHL (commerciale).

   https://github.com/syntacore/scr1.git | Auteur: Entreprise (Syntacore, Russie)

   Le projet est récent et référencé sur la liste officielle. mais une gamme plus étendue est disponible sur le site de l'entreprise (https://syntacore.com) disponible sous licence commerciale, seul le SCR1 semble avoir un SDK libre. Le GitHub est bien fourni, et l'entreprise communique sur ses produits (cf conférence P. Cotret). A voir donc....

   

5. **Pulp** **RI5CY: RISC-V Core**|systemVerilog|RV32IMFC|Dernière màj: -1mois|Licence: SHL (commerciale).

   https://github.com/pulp-platform/riscv | Auteur: ETH Zurich, Università di Bologna

   Dans la liste des projets évoqués par Pascal, le RI5CY est spécifiquement développé pour les plateformes PULP et semble optimisé pour le calcul parallèle. A ce stade, il est difficile de dire si ce projet sera transposable sur une autre plateforme.

   

6. **LowRISC** / **Ibex (formerly Zero-riscy)** |systemVerilog|RV32IM|Dernière màj: -1mois|Licence: Apache (commerciale).

   https://github.com/lowRISC/ibex|Auteur: https://www.lowrisc.org/ 

   Egalement dans la liste de pascal. A l'origine ce projet était nommé zero-riscy pour les plateformes PULP (voir ci-dessus). 

   

7. **ORCA** |VHDL|RV32I / RV32IM |Dernière màj: 5 mois|Licence: BSD (libre).

   https://github.com/vectorblox/orca |Auteur: VectorBlox

   Projet en VHDL, le GITHub semble complet et contient également un exemple pour une installation sur une carte ALTERA DE2-115 identique à celle utilisée en cours pour l'implémentation du NIOS.



La liste ci-dessus n'est pas exhaustive et sera mise à jour au fil du projet.

.

