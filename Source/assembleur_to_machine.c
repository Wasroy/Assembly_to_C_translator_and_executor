#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h> // Pour vérifier des types des variables

#include "assembleur_to_machine.h" 

/*On utilise dans cette traduction 2 passages, le premier pour sauvegarder les étiquettes et le second pour pouvoir les comparer et calculer les sauts avec */


Instruction_assembleur_et_hexa table_opcodes[] = {
    {"pop", 0x00}, {"ipop", 0x01}, {"push", 0x02}, {"ipush", 0x03}, 
    {"push#", 0x04}, {"jmp", 0x05}, {"jnz", 0x06}, {"call", 0x07}, 
    {"ret", 0x08}, {"read", 0x09}, {"write", 0x0A}, {"op", 0x0B},  // on code aussi en hexa les valeurs supérieur à 9 tels que 10=A ...
    {"rnd", 0x0C}, {"dup", 0x0D}, {"halt", 0x63} 
};

int taille_opcodes = sizeof(table_opcodes) / sizeof(Instruction_assembleur_et_hexa); //ou juste faire un #DEFINE TAILLEOPCODE 14 mais c plus stylé comme ça. C'est mieux pour par exemple si on veut rajouter une nouvelle instruction assembleur 

// Fonction pour obtenir l'équivalent de l'instruction assembleur en hexadécimal. Globalement on parcout le tableau et on pioche dans l'équivalent opcode avec .opcode
int obtenir_opcode(const char* instruction) {
    for (int i = 0; i < taille_opcodes; i++) {
        if (strcmp(table_opcodes[i].instruction, instruction) == 0) {
            return table_opcodes[i].opcode;
        }
    }
    return -1; 
}

// Fonction pour vérifier si une chaîne est un entier valide 

int est_un_entier(const char* str) {

    if (str == NULL || str[0] == '\0') { // si le premier caractère est null ou vide
        printf("La chaine n'est pas un entier valide, elle commence par un element vide");
        return 0; 
    }

    if (str[0] != '-' && str[0] != '+' && !isdigit(str[0])) {
        printf("La chaine n'est pas un entier valide, elle commence par un chiffre ou un signe + / - ");
        return 0; 
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            printf("La chaine n'est pas un entier valide, le caractère '%c' à la pos %d n'est pas un chiffre ", str[i], i);
            return 0; 
        }
    }

    return 1; // renvoie 1 si c'est un entier valide
}

int valider_etiq(const char* etiq) {
    if (strlen(etiq) > 30) {
        printf("ERREUR ! L'étiquette dépasse 30 caractères \n ");
        return 0;
    }

    if (!isalpha(etiq[0])) {
        printf("ATTENTION ! le premier element de l'étiquette n'est pas une lettre \n");
        return 0;
    }

    for (int i = 0; i < strlen(etiq); i++) {
        if (!isalnum(etiq[i]) && etiq[i] != '_') {
            return 0;
        }
    }
    return 1; // renvoie 1 si l'étiquette est valide
}

int collecter_etiq(const char* fichier_source, Tableau_detiqs* table_etiq) {
    FILE* entree = fopen(fichier_source, "r");
    if (!entree) {
        printf("\n Erreur : impossible d'ouvrir le fichier source.\n");
        return -1;
    }

    char ligne[100];
    int adresse_courante = 0;

    while (fgets(ligne, sizeof(ligne), entree)) {
        char etiq[30] = "";
        char instruction[20];
        char parametre[50] = "";

        if (sscanf(ligne, "%49[^:]: %19s %49s", etiq, instruction, parametre) == 3 ||
            sscanf(ligne, "%49[^:]: %19s", etiq, instruction) == 2) {
            if (!valider_etiq(etiq)) {
                printf("\n Erreur : étiquette invalide '%s'.\n", etiq);
                fclose(entree);
                return -1;
            }

            for (int i = 0; i < table_etiq->nombre; i++) {
                if (strcmp(table_etiq->etiqs[i].nom, etiq) == 0) {
                    printf("\n Erreur : étiquette en double '%s'.\n", etiq);
                    fclose(entree);
                    return -1;
                }
            }

            strcpy(table_etiq->etiqs[table_etiq->nombre].nom, etiq);
            table_etiq->etiqs[table_etiq->nombre].adresse = adresse_courante;
            table_etiq->nombre++;
        }

        adresse_courante++;
    }

    fclose(entree);
    return 0;
}

int traduire_instruction(const char* ligne, char* convertit, int adresse_courante, Tableau_detiqs* table_etiq) {
    char etiq[30] = "";
    char instruction[20];
    char parametre[50] = "";

    if (sscanf(ligne, "%49[^:]: %19s %49s", etiq, instruction, parametre) == 3 ||
        sscanf(ligne, "%49[^:]: %19s", etiq, instruction) == 2) {
        if (strlen(etiq) > 0 && !valider_etiq(etiq)) {
            printf("\n Erreur : étiquette invalide '%s'\n", etiq);
            return -1;
        }
    } else if (sscanf(ligne, "%19s %49s", instruction, parametre) == 2 ||
               sscanf(ligne, "%19s", instruction) == 1) {
        // Pas d'étiquette sur cette ligne, ce qui est acceptable
    } else {
        printf("\n Erreur de syntaxe dans la ligne : %s\n", ligne);
        return -1;
    }

    // Vérifie si "instruction" est une étiquette suivie d'un deux-points
    if (instruction[strlen(instruction) - 1] == ':') {
        printf("\n Erreur : '%s' semble être une étiquette mal placée\n", instruction);
        return -1;
    }

    int code_op = obtenir_opcode(instruction);
    if (code_op == -1) {
        printf("\n Erreur : instruction inconnue '%s'\n", instruction);
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
            printf("\n Erreur : paramètre invalide '%s'\n", parametre);
            return -1;
        }
        if (!etiq_trouvee) {
            valeur_parametre = atoi(parametre);
        }
    }

    sprintf(convertit, "%02x %04x", code_op, (unsigned short)valeur_parametre);
    return 0;
}

int traducteur(const char* fichier_source, const char* fichier_sortie) {
    printf("Le traducteur a été utilisé depuis le fichier assembleur_to_machine.c ! \n");

    Tableau_detiqs table_etiq = {.nombre = 0};

    if (collecter_etiq(fichier_source, &table_etiq) != 0) {
        return -1;
    }

    FILE* entree = fopen(fichier_source, "r");
    FILE* sortie = fopen(fichier_sortie, "w");

    if (!entree || !sortie) {
        printf("\n Erreur : problème d'ouverture des fichiers\n");
        if (entree) fclose(entree);
        if (sortie) fclose(sortie);
        return -1;
    }

    char ligne[100];
    char convertit[100];
    int adresse_courante = 0;

    while (fgets(ligne, sizeof(ligne), entree)) {
        if (traduire_instruction(ligne, convertit, adresse_courante, &table_etiq) != 0) {
            printf("\n Erreur de syntaxe dans la ligne : %s \n ", ligne);
            fclose(entree);
            fclose(sortie);
            return -1;
        }

        adresse_courante++;
        fprintf(sortie, "%s\n", convertit);
    }

    fclose(entree);
    fclose(sortie);
    return 0;
}
