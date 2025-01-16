#include <stdio.h>
#include "assembleur_to_machine.h"
#include "assembleur_to_machine.c"

int main() {
    printf("Le fichier a été créé ! oeoeoeoe\n");

    // faudra demander a l'utilisateur le chemin du fichier que l'on veut traduire.

    char fichier_assembleur[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/exemples/Exemple_de_programme_assembleur.txt";
    char fichier_traduit_en_hexa[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/hexa.txt" ;

    return traducteur(fichier_assembleur, fichier_traduit_en_hexa);


    return 0;
}

