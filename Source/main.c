#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembleur_to_machine.h"
#include "executeur.h"


#define MEM_SIZE  5000

int tab_mem[MEM_SIZE] = {0};
int PC = 0; 
int SP = 0;
int *pPC = &PC;
int *pSP = &SP;   


void menu_trad() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║       Assembleur vers Machine - Projet Archi          ║\n");
    printf("║     William Miserolle & Nicolas De Pellegars Malhortie║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
}


int main(int argc, char *argv[]) {

    //On verifie qu'un fichier est correctement passé en argument
    if (argc != 2) {
        printf("\033[1;31m Erreur : veuillez passer un fichier en argument\033[0m\n");
        exit(EXIT_FAILURE);
    }

    

    char *fichier_assembleur = argv[1];
    char fichier_hexa[] = "hexa.txt" ; //changer en chemin relatif en Source/hexa.txt

    menu_trad();
    
    printf("\n📝 \033[1;32m Le fichier que tu as choisis est : %s \033[0m \n", fichier_assembleur);



    printf(" _____ _      _     _                _____              _       _ _        _ \n");
    printf("|  ___(_) ___| |__ (_) ___ _ __     |_   _| __ __ _  __| |_   _(_) |_     | |\n");
    printf("| |_  | |/ __| '_ \\| |/ _ \\ '__|      | || '__/ _` |/ _` | | | | | __|    | |\n");
    printf("|  _| | | (__| | | | |  __/ |         | || | | (_| | (_| | |_| | | |_     |_|\n");
    printf("|_|   |_|\\___|_| |_|_|\\___|_|         |_||_|  \\__,_|\\__,_|\\__,_|_|\\__|    (_)\n");

    printf("\n \n");

    printf("\n ✅ \033[1;36m Tu peux retrouver le fichier traduit nommé hexa.txt au chemin : %s \033[0m \n \n", fichier_hexa);


    int traduction_reussi = traducteur(fichier_assembleur, fichier_hexa); //0 si ça ce passe bien et -1 si un prolbème
    traduction_reussi = -1;

    if (traduction_reussi ==-1){
        printf("\033[1;31m Attention erreur dans la traduction. Fin du programme ! \033[0m\n");
        exit (EXIT_FAILURE);
    }

    

    const char *nomfichier = "hexa.txt";

    int nb_ligne = nombreDeLigne(nomfichier);
    
    instruction** tab_ins = (instruction **)malloc(sizeof(instruction*) * (nb_ligne)); 
    savecode(tab_ins, nomfichier);    

    //Detection d'un possible warning : si il existe un call sans ret ou un ret sans call
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
    }

    //Début de la boucle qui parcourt le tableau d'instruction jusqu'à ce qu'ont halt() soit appelé
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
