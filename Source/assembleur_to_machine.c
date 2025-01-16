
#include <stdio.h>    // Gestion des fichiers
#include <stdlib.h>   // Fonctions générales comme malloc, exit
#include <string.h>   // Gestion des chaînes de caractères
#include <ctype.h>

#include "assembleur_to_machine.h" // Prototypes de fonctions et constantes


CodeOperation table_opcodes[] = {
    {"pop", 0x00}, {"ipop", 0x01}, {"push", 0x02}, {"ipush", 0x03}, 
    {"push#", 0x04}, {"jmp", 0x05}, {"jnz", 0x06}, {"call", 0x07}, 
    {"ret", 0x08}, {"read", 0x09}, {"write", 0x0A}, {"op", 0x0B}, 
    {"rnd", 0x0C}, {"dup", 0x0D}, {"halt", 0x63}
};

int taille_opcodes = sizeof(table_opcodes) / sizeof(CodeOperation);

// Fonction pour obtenir le code opération en hexadécimal
int obtenir_opcode(const char* instruction) {
    for (int i = 0; i < taille_opcodes; i++) {
        if (strcmp(table_opcodes[i].instruction, instruction) == 0) {
            return table_opcodes[i].opcode;
        }
    }
    return -1; // Instruction non trouvée
}

// Fonction pour vérifier si une chaîne est un entier valide
int est_un_entier(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && !(i == 0 && str[i] == '-')) {
            return 0;
        }
    }
    return 1;
}

int valider_etiq(const char* etiq) {
    if (!isalpha(etiq[0])) { // Doit commencer par une lettre
        return 0;
    }
    int longueur = strlen(etiq);
    if (longueur > 30) { // Longueur maximale
        return 0;
    }
    for (int i = 0; i < longueur; i++) {
        if (!isalnum(etiq[i]) && etiq[i] != '_') { // Caractères autorisés
            return 0;
        }
    }
    return 1;
}



int traduire_instruction(const char* ligne, char* convertit, int adresse_courante, TableEtiquettes* table_etiq) {
    char etiq[30] = ""; // Étiquette (optionnelle)
    char instruction[20]; // Instruction
    char parametre[50] = ""; // Paramètre (optionnel)

    // Analyse de la ligne
    if (sscanf(ligne, "%49[^:]: %19s %49s", etiq, instruction, parametre) == 3) {
        // Vérifie si l'étiquette est valide
        if (!valider_etiq(etiq)) {
            fprintf(stderr, "Erreur : étiquette invalide '%s'.\n", etiq);
            return -1; // Erreur d'étiquette invalide
        }

        // Vérifie si l'étiquette est déjà utilisée
        for (int i = 0; i < table_etiq->nombre; i++) {
            if (strcmp(table_etiq->etiqs[i].nom, etiq) == 0) {
                fprintf(stderr, "Erreur : étiquette en double '%s'.\n", etiq);
                return -1; // Erreur d'étiquette en double
            }
        }

        // Ajoute l'étiquette à la table
        strcpy(table_etiq->etiqs[table_etiq->nombre].nom, etiq);
        table_etiq->etiqs[table_etiq->nombre].adresse = adresse_courante;
        table_etiq->nombre++;
    } 
    else if (sscanf(ligne, "%19s %49s", instruction, parametre) != 2 &&
             sscanf(ligne, "%19s", instruction) != 1) {
        fprintf(stderr, "Erreur de syntaxe dans la ligne : %s\n", ligne);
        return -1; // Erreur de syntaxe
    }

    // Suite de la fonction...


    int code_op = obtenir_opcode(instruction);
    if (code_op == -1) {
        fprintf(stderr, "Erreur : instruction inconnue '%s'.\n", instruction);
        return -1;
    }

    int valeur_parametre = 0;
    if (strlen(parametre) > 0) {
        int etiq_trouvee = 0;
        for (int i = 0; i < table_etiq->nombre; i++) {
            if (strcmp(table_etiq->etiqs[i].nom, parametre) == 0) {
                valeur_parametre = table_etiq->etiqs[i].adresse - adresse_courante - 1;
                etiq_trouvee = 1;
                break;
            }
        }
        if (!etiq_trouvee && !est_un_entier(parametre)) {
            fprintf(stderr, "Erreur : paramètre invalide '%s'.\n", parametre);
            return -1;
        }
        if (!etiq_trouvee) {
            valeur_parametre = atoi(parametre);
        }
    }

    sprintf(convertit, "%02x %04x", code_op, (unsigned short)valeur_parametre);
    return 0;
}



int traducteur(const char* fichier_source, const char* fichier_sortie){

    printf("Le traducteur a ete utilisé depuis le fichier !");

    FILE* entree = fopen(fichier_source, "r");
    FILE* sortie = fopen(fichier_sortie, "w");

    // GESTION DES ERREURS D'OUVERTURE ///////////////////////////
    if (!entree) {
        printf("Erreur d'ouverture du fichier Assembleur");
        return -1; // Erreur d'ouverture de fichier
    }
    if (!sortie){
        printf("Erreur d'ouverture du fichier qui va contenir la traduction en langage machine");
    }
    ////////////////////////////////////////////////////////////

    char ligne[100] ;// car une ligne ne peut pas dépasser 100 caractères.
    char convertit[100] ; // la ligne traduite
    TableEtiquettes table_etiq = {.nombre = 0};
    int adresse_courante = 0;

    while (fgets(ligne, sizeof(ligne), entree)) { //on parcout tout le fichier assembleur

        if (strlen(ligne) >= 100) {
            fprintf(stderr, "Erreur : ligne trop longue.\n");
            fclose(entree);
            fclose(sortie);
        return -1;
        }

        if (traduire_instruction(ligne, convertit,adresse_courante,&table_etiq) != 0) { // on arrete toute la traduction et on ferme les fichiers
            fprintf(stderr,"Erreur de syntaxe dans la ligne : %s", ligne); 
            fclose(entree);
            fclose(sortie);
            return -1;
        }

        if (adresse_courante >= 500) {
            fprintf(stderr, "Erreur : dépassement du nombre maximal d'instructions (500).\n");
            fclose(entree);
            fclose(sortie);
            return -1;
        }

        adresse_courante++;
        fprintf(sortie, "%s\n", convertit);// changer ligne par convertit
    }


    
    // on oublie pas de fermer les fichiers utilisés pour ne pas faire d'erreurs.
    fclose(entree);
    fclose(sortie);
    

    return 0;
}