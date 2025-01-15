#include <stdio.h>
#include <string.h>
#include "assembleur_to_machine.h"

int traducteur(const char *fichier_a_traduire, const char *fichier_traduit) {
    FILE *input = fopen(fichier_a_traduire, "r");
    FILE *output = fopen(fichier_traduit, "w");

    if (!input) {
        printf("Erreur : Impossible d'ouvrir le fichier d'entrée %s.\n", fichier_a_traduire);
        return 1;
    }

    if (!output) {
        printf("Erreur : Impossible de créer le fichier de sortie %s.\n", fichier_traduit);
        fclose(input);
        return 1;
    }

    // Exemple de traitement
    char line[256];
    while (fgets(line, sizeof(line), input)) {
        // TODO : Traduire chaque ligne en langage machine
        fprintf(output, "TEST FINAL: %s", line); // Remplace par la logique de traduction
    }

    fclose(input);
    fclose(output);

    return 0; // Succès
}
