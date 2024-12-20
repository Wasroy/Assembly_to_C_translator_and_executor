Projet d'Architecture Des Ordinateurs L2 MIDO William Miserolle & Nicolas De Pellegars

Ce projet consiste à simuler une machine virtuelle à pile capable de lire, assembler et exécuter un programme donné écrit en langage assembleur

(ATTENTION A LA VARIABLE DANS LE NOM DU FICHIER DONNE, pas le definir avant).

Assembleur :
Convertit un fichier (txt) écrit en  assembleur (lisible par un humain) en un fichier en langage machine (lisible par la machine).
Gère les erreurs de syntaxe et les signales.

Simulateur :
Exécute les instructions traduites en langage machine en simulant le fonctionnement d'une pile, (en gérant bien la mémoire et même les registres)

COMMENT CA MARCHE : 

Assembleur :

Lit un programme assembleur ligne par ligne
Identifie et traduit les instructions reconnues (pop, push, halt, etc....)
Gère les étiquettes pour les instructions de saut (jmp, jnz) car en assembleur les sauts sont gérés manuellements
Produit un fichier hexa.txt contenant le code en langage machine (avec les normes de l'héxadecimal de la consigne)

Simulateur :

Lit le fichier généré par l'assembleur le fichier "hexa.txt"
Exécute chaque instruction et simule les registres PC (Program Counter) et SP (Stack Pointer)
Le programme peut intéragire avec l'utilisateur via des instructions comme read (saisie par l'utilisateur) et write (affichage).
