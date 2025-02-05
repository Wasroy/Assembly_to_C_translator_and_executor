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
    const char *nomfichier = "hexa.txt";

    //FILE * sortie = fopen(sortie, 'r'); // PAS NECESSAIRE
    //Chaque ligne seront assignée à un élément de la structure instruction. On veut un tableau d'instruction de meme nombre déléments qu'il n'y a de ligne

    int nb_ligne = nombreDeLigne(nomfichier) + 1;
    printf("%d\n", nb_ligne);
    instruction** tab_ins = (instruction **)malloc(sizeof(instruction*) * (nb_ligne)); 
    savecode(tab_ins, nb_ligne-1, nomfichier);    

    for (int i=0; i<nb_ligne; i++) {
        printf(" Code instruction : %d, Code donnee : %d\n", tab_ins[i]->opcode, tab_ins[i]->donnee);
    }
    
    while (*pPC < nb_ligne) {
        (*pPC)++;
        printf("PC = %d\n", *pPC);

        executeligne(tab_mem, pSP, pPC, tab_ins);
        printf("Executeligne fais correctement\n");
    }

    printf("tab_mem[1000] = %d\n", tab_mem[1000]);

    for (int i=0; i<1000; i++) {
            printf("tab_mem[%d] = %d\n", i, tab_mem[i]);}

    free(tab_ins);

    return 0;
}