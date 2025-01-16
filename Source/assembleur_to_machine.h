#ifndef ASSEMBLEUR_TO_MACHINE_H
#define ASSEMBLEUR_TO_MACHINE_H

#include <stdio.h>

// Définition des constantes
#define MAX_ETIQUETTES 30
#define MAX_LIGNE 100
#define TAILLE_OPCODE 16

// Structure pour stocker une étiquette
typedef struct {
    char nom[50];   // Nom de l'étiquette
    int adresse;    // Adresse associée
} Etiquette;

// Structure pour la table des étiquettes
typedef struct {
    Etiquette etiqs[MAX_ETIQUETTES];
    int nombre;     // Nombre total d'étiquettes enregistrées
} TableEtiquettes;

// Structure pour stocker un opcode
typedef struct {
    char* instruction; // Nom de l'instruction
    int opcode;        // Code hexadécimal associé
} CodeOperation;

// Prototypes des fonctions
int traduire_instruction(const char* ligne, char* convertit, int adresse_courante, TableEtiquettes* table_etiq);
int traducteur(const char* fichier_source, const char* fichier_sortie);
int obtenir_opcode(const char* instruction);
int est_un_entier(const char* str);
int valider_etiq(const char* etiq)

#endif // ASSEMBLEUR_TO_MACHINE_H
