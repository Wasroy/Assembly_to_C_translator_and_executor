#include <stdio.h>
#include <string.h>
#include "assembleur_to_machine.h"
#include <ctype.h>

//constantes pour respecter les consignes

#define MAX_LINE_LENGTH 100  // Longueur maximale d'une ligne
#define MAX_LABEL_LENGTH 30  // Longueur maximale d'une étiquette
#define MAX_INSTRUCTIONS 500 // Nombre maximal d'instructions

// Structure pour représenter une étiquette
typedef struct {
    char nom[MAX_LABEL_LENGTH + 1]; // Nom de l'étiquette (30 caractères max + null terminator)
    int adresse;                   // Adresse associée à l'étiquette
} Etiquette;

// Tableau pour stocker les étiquettes
Etiquette table_etiq[MAX_INSTRUCTIONS];
int nb_etiq = 0; // Nombre d'étiquettes trouvées

int est_une_etiquette_valide(const char *nom) {
    if (!isalpha(nom[0]) && nom[0] != '_') { 
        return 0; // Doit commencer par une lettre ou un underscore
    }
    for (int i = 1; nom[i] != '\0'; i++) {
        if (!isalnum(nom[i]) && nom[i] != '_') {
            return 0; // Doit contenir uniquement des lettres, chiffres ou underscores
        }
    }
    return 1;
}

// Fonction pour ajouter une étiquette à la table des symboles
void ajouter_etiquette(const char *nom, int adresse) {
    if (nb_etiq >= MAX_INSTRUCTIONS) {
        printf("Erreur : Trop d'étiquettes (limite de %d atteinte).\n", MAX_INSTRUCTIONS);
        return;
    }
    strcpy(table_etiq[nb_etiq].nom, nom);
    table_etiq[nb_etiq].adresse = adresse;
    nb_etiq++;
}

// Fonction principale pour lire et analyser un fichier assembleur
void analyser_fichier(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }

    char ligne[MAX_LINE_LENGTH]; // Pour stocker chaque ligne
    int adresse_courante = 0;    // Adresse courante dans le programme

    // Lecture ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Supprimer les espaces ou retours à la ligne en fin de ligne
        ligne[strcspn(ligne, "\n")] = '\0';

        // Vérifier si la ligne contient une étiquette
        char etiq[MAX_LABEL_LENGTH + 1];
        if (sscanf(ligne, "%30[^:]:", etiq) == 1) { //lit 30 caractères et s'arete si rencontre un " : " donc fin de l'étiquette si l'étiquette verif les conditions alors on la stock dans la table d'étiquette
            if (est_une_etiquette_valide(etiq)) {
                printf("Étiquette détectée : %s à l'adresse %d\n", etiq, adresse_courante);
                ajouter_etiquette(etiq, adresse_courante);
            } else {
                printf("Erreur : Étiquette invalide \"%s\".\n", etiq);
                fclose(fichier); //on termine la traduction
                return ;
            }
        }

        // Extraire le code opération et les paramètres éventuels

        char opcode[20];
        int param;

        if (sscanf(ligne, "%*[^:]: %19s %d", opcode, &param) == 2 || sscanf(ligne, "%19s %d", opcode, &param) == 2) { //si il y a une étiquette et un paramètre
            printf("Instruction : %s avec paramètre %d\n", opcode, param);
            
        } else if (sscanf(ligne, "%*[^:]: %19s", opcode) == 1 || sscanf(ligne, "%19s", opcode) == 1) { // si il y a une étiquette mais pas de paramètre
            printf("Instruction : %s sans paramètre\n", opcode);

        } else {
            printf("Erreur : Ligne invalide \"%s\".\n", ligne);
            fclose(fichier);
            return;
        }

        // Incrémenter l'adresse courante pour chaque instruction
        adresse_courante++;
    }

    fclose(fichier);

    // Afficher les étiquettes détectées
    printf("\nTable des étiquettes :\n");
    for (int i = 0; i < nb_etiq; i++) {
        printf(" - %s : %d\n", table_etiq[i].nom, table_etiq[i].adresse);
    }
}

int main() {
    // Appeler la fonction pour analyser un fichier assembleur
    analyser_fichier("Exemple_de_programme_assembleur.txt");
    return 0;
}
