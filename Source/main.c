#include <stdio.h>
#include "assembleur_to_machine.h"

int main() {
    const char *fichier_a_traduire = "exemples/Exemple_de_programme_assembleur.txt";
    const char *fichier_traduit = "hexa.txt";

    // appelle la fct traducteur
    if (traducteur(fichier_a_traduire, fichier_traduit) != 0) {
        printf("ERREUR \n");
        return 1;
    }

    printf("Le fichier %s a été créé ! \n", fichier_traduit);
    return 0;
}
