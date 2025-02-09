#include <stdio.h>
#include "assembleur_to_machine.h"
#include "assembleur_to_machine.c"

void menu_trad() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║       Assembleur vers Machine - Projet Archi          ║\n");
    printf("║     William Miserolle & Nicolas De Pellegars Malhortie║\n");
    printf("╠═══════════════════════════════════════════════════════╣\n");
    printf("║  Indique le chemin du fichier à traduire :            ║\n");
    printf("║                                                       ║\n");
    printf("║  ➜ ");
}


int main() {


    char fichier_assembleur[256];
    char fichier_hexa[] = "C:\\Users\\willi\\Desktop\\Programmation_C\\Projet_Archi\\Source\\hexa.txt" ; //changer en chemin relatif en Source/hexa.txt

    // Demande du chemin du fichier à traduire
    menu_trad();
    scanf("%255s", fichier_assembleur);
    printf("║                                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");

    //printf("\033[1;31m       \n");
    printf("\n📝 \033[1;32m Le fichier que tu as choisis est : %s \033[0m \n", fichier_assembleur);



    printf(" _____ _      _     _                _____              _       _ _        _ \n");
    printf("|  ___(_) ___| |__ (_) ___ _ __     |_   _| __ __ _  __| |_   _(_) |_     | |\n");
    printf("| |_  | |/ __| '_ \\| |/ _ \\ '__|      | || '__/ _` |/ _` | | | | | __|    | |\n");
    printf("|  _| | | (__| | | | |  __/ |         | || | | (_| | (_| | |_| | | |_     |_|\n");
    printf("|_|   |_|\\___|_| |_|_|\\___|_|         |_||_|  \\__,_|\\__,_|\\__,_|_|\\__|    (_)\n");

    printf("\n \n");

    printf("\n ✅ \033[1;36m Tu peux retrouver le fichier traduit nommé hexa.txt au chemin : %s \033[0m \n \n", fichier_hexa);


    return traducteur(fichier_assembleur, fichier_hexa);


}
