#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <ctype.h> // Pour vérifier des types des variables
#include "assembleur_to_machine.h" 
#include "executeur.h"

//On utilise dans cette traduction 2 passages, le premier pour sauvegarder les étiquettes et le second pour pouvoir les comparer et calculer les sauts avec

//Un tableau contenant les variables assembleur et sa traduction hexa donné dans la consigne
instruction_assembleur_et_hexa table_opcodes[] = {
    {"pop", 0x00}, {"ipop", 0x01}, {"push", 0x02}, {"ipush", 0x03}, 
    {"push#", 0x04}, {"jmp", 0x05}, {"jnz", 0x06}, {"call", 0x07}, 
    {"ret", 0x08}, {"read", 0x09}, {"write", 0x0a}, {"op", 0x0b},  // on code aussi en hexa les valeurs supérieur à 9 tels que 10=A ...
    {"rnd", 0x0c}, {"dup", 0x0d}, {"halt", 0x63} 
};

int taille_opcodes = sizeof(table_opcodes) / sizeof(instruction_assembleur_et_hexa); //ou juste faire un #DEFINE TAILLEOPCODE 14 mais c plus stylé comme ça. C'est mieux pour par exemple si on veut rajouter une nouvelle instruction assembleur 

// Fonction pour obtenir l'équivalent de l'instruction assembleur en hexadécimal. On parcout le tableau et on pioche dans l'équivalent opcode avec .opcode
int obtenir_opcode(const char* instruction) {
    for (int i = 0; i < taille_opcodes; i++) {
        if (strcmp(table_opcodes[i].instruction, instruction) == 0) { //strcmp sert à comparer deux chaines de  : strcmp(a,b) donne 0 si a et b sont les mêmes
            return table_opcodes[i].opcode;
        }
    }
    return -1; 
}

//fonction qui va verifier si une etiquette est conforme aux consignes 0 si problème 1 si elle est conforme
int valider_etiq(const char* etiq) {

    if (strlen(etiq) > 30) {
        printf("erreur dans l'étiquette : elle dépasse 30 caractères\n");
        return 0;
    }

    //grace a la librairie ctype
    if (!isalpha(etiq[0])) {
        printf("il y a une erreur dans l'étiquette : le premier caractère de l'étiquette n'est pas une lettre\n");
        return 0;
    }

    //on verifie pour toutes les lettres qui composent l'étiquette
    for (int i = 0; i < strlen(etiq); i++) {

        if (!isalnum(etiq[i]) && etiq[i] != '_') {

            printf("ERREUR a cause de %c invalide à l'indice %d", etiq[i], i);

            return 0;
        }

    }

    return 1; // si il n'y a pas de problème la fonction renvoie 1 si l'étiquette est valide

}


// Fonction pour vérifier si une chaîne de caractère est un entier (nous servira pour les paramètres)
int est_un_entier(const char* str) {

    if (str == NULL || str[0] == '\0') { // si le premier caractère est null ou vide
        printf("Le paramètre n'est pas un entier : il commence par un element vide");
        return 0; 
    }

    if (str[0] != '-' && str[0] != '+' && !isdigit(str[0])) { 
        printf("La paramètre n'est pas un entier et ne commence pas par un chiffre ou un signe + / - ");
        return 0; 
    }

    //on va parcourir tous les caractères du string qui compose le "nombre"
    for (int i = 1; str[i] != '\0'; i++) { //tant qu'on rencontre pas \0 soit la fin du string
        if (!isdigit(str[i])) { //si un element est différent d'une valeure numérique par exemple '12a3' 
            printf("La paramètre n'est pas un entier, %c à la pos %d n'est pas un chiffre ", str[i], i);
            return 0; 
        }
    }

    return 1; // renvoie 1 si c'est un entier valide
}


int collecter_etiq(const char* fichier_assembleur, Tableau_detiqs* tbl_etq) { //fait un premier passage et va récuperer toutes les etiquettes du fichier qu'on va traduire et les stocker dans tbl_etq

    FILE* entree = fopen(fichier_assembleur, "r"); //on l'ouvre en mode read car on ne veut rien modifier

    if (!entree) {
        printf("CODE ROUGE : il y a un problème pour ouvrir le fichier assembleur\n");
        return -1;
    }

    char ligne[100]; //longueu max d'une ligne est de 100

    int adresse_courante = 0; //une sorte de pointeur vers l'adresse qui servira a calculer l'adresse ciblé si il y a un JUMP par exemple

    while (fgets(ligne, sizeof(ligne), entree)) { //on parcourt tout le fichier

        //supposition naturelle pour les longueurs vu qu'une ligne peut pas faire +100 caractères
        char etiq[30] = ""; 
        char instruction[20];
        char parametre[50] = "";


        //verifie si la ligne est bien composé : peut y avoir une etiquette au debut
        if (sscanf(ligne, "%49[^:]: %19s %49s", etiq, instruction, parametre) == 3 || sscanf(ligne, "%49[^:]: %19s", etiq, instruction) == 2) { //%x[^:] prends les x premiers caractères max jusqua'au " : " ce qui separe le nom de l'étiquette du reste
            
            if (!valider_etiq(etiq)) {
                printf("PROBLEME : l'étiquette %s est invalide\n", etiq);
                fclose(entree); //on ferme le fichier pour que ce soit propre et ne pas avoir de conflit avec une futur ouverture potentiel
                return -1;
            }

            //on va parcourir toutes les etiquettes deja enrengistrées
            for (int i = 0; i < tbl_etq->nombre; i++) {
                if (strcmp(tbl_etq->etiqs[i].nom, etiq) == 0) { //utilisation de strcmp pour comparer car si deux mots sont les memes cette fonction renvoie 0, vient du module string
                    printf("\n ATTENTION l'étiquette %s existe deja !\n", etiq);
                    fclose(entree);
                    return -1;
                }
            }

            //si une nouvelle etiquette est rencontré :  elle est valide et n'existe pas déja 
            strcpy(tbl_etq->etiqs[tbl_etq->nombre].nom, etiq); //on ajoute la nouvelle etiquette au tableau grace a la fonction strcpy qui permet de copier une chaine de caractère
            tbl_etq->etiqs[tbl_etq->nombre].adresse = adresse_courante; //et on y met la bonne l'adresse correspondante 
            tbl_etq->nombre++; //on incrémente le nombre d'étiquettes du tableau etq pour toujours garder un oeil sur ce qui ce passe.
        }

        adresse_courante++; //on ajoute pour dire qu'on a fini de lire la ligne
    }

    fclose(entree); //on oublie pas de fermer le fichier c'est plus propre
    return 0;
}

int traduire_instruction(const char* ligne, char* code_hexa, int adresse_courante, Tableau_detiqs* tbl_etq) {

    char etiq[30] = "";
    char instruction[20];
    char parametre[50] = "";


    //on vérifie si l'instruction est une étiquette mal placé ex : jmp: 5
    if (instruction[strlen(instruction) - 1] == ':') {
        printf("\nERREUR l'instruction %s semble être une étiquette que l'on aurait mal placée\n", instruction);
        return -1;
    }

    //idem que precedemment
    if ( (sscanf(ligne, "%49[^:]: %19s %49s", etiq, instruction, parametre) == 3 ) || ( sscanf(ligne, "%49[^:]: %19s", etiq, instruction) == 2) ) {
        if (strlen(etiq) > 0 && !valider_etiq(etiq)) {
            printf("\nERREUR ! l'étiquette %s est invalide", etiq);
            return -1;
        }
    } 
    
    else if (sscanf(ligne, "%19s %49s", instruction, parametre) == 2 || sscanf(ligne, "%19s", instruction) == 1) {
        // Pas d'étiquette sur cette ligne, ce qui est acceptable
    } 

    else {
        printf("\nATTENNNTIONE !!! erreur de syntaxe a la ligne : %s \n", ligne);
        return -1;
    }

    int code_op = obtenir_opcode(instruction);

    if (code_op == -1) {
        printf("\nERREUR !! : l'instruction %s n'est pas connue\n", instruction);
        return -1;
    }



 
    int valeur_parametre = 0;

    if (strlen(parametre) > 0) { //si y'a un paramètre

        int etiq_trouvee = 0;

        for (int i = 0; i < tbl_etq->nombre; i++) { //on parcourt tt le tableau pour verifier d'abord si c une etiquette
            if ( strcmp(tbl_etq->etiqs[i].nom, parametre) == 0 ) {

                valeur_parametre = tbl_etq->etiqs[i].adresse - adresse_courante - 1;

                etiq_trouvee = 1;
                break; //si on trouve on sort de la boucle

            }
        }

        if (!etiq_trouvee && !est_un_entier(parametre)) { //si c'est ni un entier ni une etiquette
            printf("\nprobleme : le paramètre %s est invalide\n", parametre);
            return -1;
        }

        if (!etiq_trouvee) {
            valeur_parametre = atoi(parametre); //ou strtol c pareil : transforme une chaine représentant un nb en un entier de type int.
        }

    }

    sprintf(code_hexa, "%02x %04x", code_op, (unsigned short)valeur_parametre); //on utilise sprintf pour formater le codeopérateur à deux chiffre et le paramètre à 4 en complétant si besoin par des 0 pour qu'il soit sous la forme hexadecimal attendu
    //EXEMPLE DE SPRINTF  : code_op = 9 et valeur_parametre = 1000, la chaîne écrite dans le fichier hexa sera 09 03e8 : le bon format attendu

    return 0;
}


int traducteur(const char* fichier_assembleur, const char* fichier_hexa) {

    //printf("\n Le traducteur a été utilisé depuis le fichier assembleur_to_machine.c ! bv gros bg \n");

    Tableau_detiqs tbl_etq = {.nombre = 0};

    if (collecter_etiq(fichier_assembleur, &tbl_etq) != 0) {
        return -1;
    }

    FILE* entree = fopen(fichier_assembleur, "r");


    int nb_de_ligne_fichier_assembleur = nombreDeLigne(fichier_assembleur);
    
    //printf("nb de entree : %d",nb_de_ligne_fichier_assembleur);

    FILE* sortie = fopen(fichier_hexa, "w");
    //printf("%s",fichier_hexa);

    if (!entree) { //si il y a un soucis pour  lire ou ecrire un fichier c a d le chemin d'entree ou de sortie de hexa.txt est invalide
        printf("\nProblème d'ouverture du fichier, verifie le repertoire\n");
        fclose(entree);
        return -1;
    }

    if(!sortie){
        printf("\n probleme pour ecrire le fichier, verifie le repertoire de sortie");
        fclose(sortie);
        return -1;
    }


    //supposition naturelle pour les longueurs
    char ligne[100];
    char code_hexa[100];
    int adresse_courante = 0;


    while (fgets(ligne, sizeof(ligne), entree)) {
        if (traduire_instruction(ligne, code_hexa, adresse_courante, &tbl_etq) != 0) {
            printf("\n Erreur à la ligne : %s \n ", ligne);
            fclose(entree);
            fclose(sortie);
            return -1;
        }

        adresse_courante++;

        //printf("%d\n",adresse_courante);
        //permet de pas ecrire une ligne vide à la fin
        if (adresse_courante<nb_de_ligne_fichier_assembleur){
            fprintf(sortie, "%s\n", code_hexa);
        }
        else {
            fprintf(sortie, "%s", code_hexa);

        }
        
    }

    fclose(entree);
    fclose(sortie);
    return 0;
}
