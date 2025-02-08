#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "assembleur_to_machine.h"
//#include "assembleur_to_machine.c"
#include "executeur.h"


#define MEM_SIZE  5000

int tab_mem[MEM_SIZE] = {0};
int PC = 0; 
int SP = 0;
int *pPC = &PC;
int *pSP = &SP;   


int main() {
    /*printf("Le fichier a été créé ! oeoeoeoe\n");

    // faudra demander a l'utilisateur le chemin du fichier que l'on veut traduire.

    char fichier_assembleur[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/exemples/Exemple_de_programme_assembleur.txt";
    char fichier_traduit_en_hexa[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/hexa.txt" ;

    return traducteur(fichier_assembleur, fichier_traduit_en_hexa);

    // DEBUT DE LA MASTERCLASS ICI MEME // */
    const char *nomfichier = "hexasomme.txt";

    //FILE * sortie = fopen(sortie, 'r'); // PAS NECESSAIRE
    //Chaque ligne seront assignée à un élément de la structure instruction. On veut un tableau d'instruction de meme nombre déléments qu'il n'y a de ligne

    int nb_ligne = nombreDeLigne(nomfichier) + 1;
    
    instruction** tab_ins = (instruction **)malloc(sizeof(instruction*) * (nb_ligne)); 
    savecode(tab_ins, nomfichier);    

    //Detection d'une possible erreur : si il existe un call sans ret ou un ret sans call
    int nb_call = 0;
    int nb_ret = 0;
    for (int i = 0; i < nb_ligne; i++) {
        if (tab_ins[i]->opcode == 7) {
            nb_call++;
        }
        if (tab_ins[i]->opcode == 8) {
            nb_ret++;
        }
    }
    if (nb_call != nb_ret) {
        printf("\033[38;5;214m Warning : Nombre de call et de ret inegaux\033[0m\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        if (*pPC < 0) {
            printf("\033[1;31m Erreur : tentative d'accéder à une ligne inexistante (négative) du code\033[0m\n");
            exit(EXIT_FAILURE);}
        if (*pPC >= nb_ligne) {
            printf("\033[1;31m Erreur : tentative d'accéder à une ligne inexistante (superieure au nombre de ligne) du code\033[0m\n");
            exit(EXIT_FAILURE);
        }
        (*pPC)++;
        executeligne(tab_mem, pSP, pPC, tab_ins, nb_ligne);
    }
    

    return 0; 
}
