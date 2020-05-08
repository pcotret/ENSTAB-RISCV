# 1ère étape : choix d'une implémentation RISC-V

De nombreuses implémentations du processeur RISC-V sont disponibles sur la toile et notamment sur GitHub. La première étape de ce projet consiste donc à en sélectionner une. Mais avant de débuter, petit rappel sur les différentes spécifications proposées par la fondation RISC-V.

## Spécifications

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
- Le projet a-t-il été testé sur FPGA ?

Voici une synthèse des projets ayant retenu notre attention :

| Nom                                                   | Langage matériel | Jeu d'instruction | Dernière MAJ                                                 | Licence | Commentaires                                                 |
| ----------------------------------------------------- | ---------------- | ----------------- | ------------------------------------------------------------ | ------- | ------------------------------------------------------------ |
| [PicoRV32](https://github.com/cliffordwolf/picorv32)  | Verilog          | RV32I/E[MC]       | [27/04/2020](https://github.com/cliffordwolf/picorv32/commits/master) | ISC     | - Bien référencé, et testé sur différentes puces, le projet est open source et très régulièrement mis à jour. Il est possible de trouver plusieurs exemples sur la toile d'utilisation de ce processeur (ex: https://github.com/Jesus89/picorv32-c-examples)<br/>- La documentation y est complète, la chaine de compilation y est décrite ainsi que différents testbenches |
| [Potato Processor](https://github.com/skordal/potato) | VHDL             | RV32I             | [17/12/2019](https://github.com/skordal/potato/commits/master) | BSD     | Evoqué lors de notre première réunion, la page gitHub de ce projet est bien documentée mais semble inactive depuis quelques mois. Nous ne la retrouvons pas non plus dans la liste des projets référencés sur la page officielle. |
| [DarkRISCV](https://github.com/darklife/darkriscv)    | Verilog          | RV32I             | [05/01/2020](https://github.com/darklife/darkriscv/commits/master) | BSD     | Le projet est récent et référencé sur la liste officielle. La documentation y est présente, mais le projet ne semble pas terminé. L'auteur précise que certaine fonctionnalités sont toujours en attente de tests. A suivre... |
| [SCR1](https://github.com/syntacore/scr1)             | SystemVerilog    | RV32I/E[MC]       | [28/01/2020](https://github.com/syntacore/scr1/commits/master) | SHL     | Le projet est récent et référencé sur la liste officielle. mais une gamme plus étendue est disponible sur le site de l'entreprise (https://syntacore.com) disponible sous licence commerciale, seul le SCR1 semble avoir un SDK libre. Le GitHub est bien fourni, et l'entreprise [communique sur ses produits](https://open-src-soc.org/media/slides/2nd-RISC-V-Meeting-2019-10-02-11h30-Ekaterina-Berezina.pdf). A voir donc.... |
| [CV32E40P](https://github.com/openhwgroup/cv32e40p)   | SystemVerilog    | RV32IMFC          | [26/04/2020](https://github.com/openhwgroup/cv32e40p/commits/master) | SHL     | Dans la liste des projets évoqués par Pascal, le RI5CY est spécifiquement développé pour les plateformes PULP et semble optimisé pour le calcul parallèle. A ce stade, il est difficile de dire si ce projet sera transposable sur une autre plateforme. |
| [Ibex](https://github.com/lowRISC/ibex)               | SystemVerilog    | RV32IM            | [07/05/2020](https://github.com/lowRISC/ibex/commits/master) | Apache  | Egalement dans la liste de Pascal. A l'origine ce projet était nommé zero-riscy pour les plateformes PULP (voir ci-dessus). |
| [ORCA](https://github.com/riscveval/orca-1)           | VHDL             | RV32I/RV32IM      | [19/07/2017](https://github.com/riscveval/orca-1/commits/master) | BSD     | Projet forké, l'original ayant été supprimé.                 |
| [River CPU](https://github.com/sergeykhbr/riscv_vhdl) | VHDL             | RV64G             | [12/03/2020](https://github.com/sergeykhbr/riscv_vhdl/commits/master) | Apache  | -                                                            |
| [SweRV](https://github.com/chipsalliance/Cores-SweRV) | SystemVerilog    | RV64IMC           | [13/04/2020](https://github.com/chipsalliance/Cores-SweRV/commits/master) | Apache  | -                                                            |

Il y a également une procédure pour générer un SoC autour de ce CPU pour la Nexys4 DDR https://github.com/westerndigitalcorporation/swerv_eh1_fpga

.
