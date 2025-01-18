#include <stdio.h>
#include "assembleur_to_machine.h"
#include "assembleur_to_machine.c"
#include "simulateur.h"
#include "simulateur.c"

#define MEM_SIZE = 5000

int tab_mem[MEM_SIZE] = {0};
int PC = 0; 
int SP = 0;
int *pPC = &PC;
int *pSP = &SP;   

int main() {
    printf("Le fichier a été créé ! oeoeoeoe\n");

    // faudra demander a l'utilisateur le chemin du fichier que l'on veut traduire.

    char fichier_assembleur[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/exemples/Exemple_de_programme_assembleur.txt";
    char fichier_traduit_en_hexa[] = "C:/Users/willi/Desktop/Programmation_C/Projet_Archi/hexa.txt" ;

    return traducteur(fichier_assembleur, fichier_traduit_en_hexa);

    // DEBUT DE LA MASTERCLASS ICI MEME // 
    char nomfichier[] = hexa.txt;
    FILE * sortie = fopen(sortie, 'r'); // PAS NECESSAIRE
    //Chaque ligne seront assignée à un élément de la structure instruction. On veut un tableau d'instruction de meme nombre déléments qu'il n'y a de ligne

    int nb_ligne = nombreDeLigne(hexa.txt);
    instruction** tab_ins[] = malloc(sizeof(instruction)*nb_ligne); 
    savecode(tab_ins, hexa.txt, nb_ligne);
    
    
    

    return 0;
}

