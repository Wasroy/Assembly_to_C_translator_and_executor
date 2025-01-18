#include <stdio.h>
#include "simulateur.h"

int nombreDeLigne(const char* nomfichier){  /*Récupérer la longeur max des lignes*/
	FILE* file = fopen(nomfichier,"r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
	int NbDeLigne = 0;
	char c;
	while((c = fgetc(file)) != EOF){
		if(c == '\n') NbDeLigne += 1; /* Le \n est le caractère de fin de ligne, il figure donc même sur la dernière */
		}
	fclose(file);
	if (NbDeLigne == 0){
		annonceErreur();
		printf("Fichier vide\n");
		exit(1);
		}
	return NbDeLigne;
	}
    
void save_code(instruction* tab[], int nligne, const char*nomfichier) {
    FILE *file = fopen(nomfichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    char ligne[8];
    for (int i=0; i < nligne; i++) {
        fgets(ligne, 8, file); 
        char s_opcode[3];  
        char s_donnee[5];  

        strncpy(s_opcode, ligne, 2);
        s_opcode[2] = '\0'; 
        strncpy(s_donnee, ligne + 4, 4); 
        s_donnee[4] = '\0'; 

        tab[i]->opcode = (int)strtol(s_opcode, NULL, 16);  
        tab[i]->donnee = (int)strtol(s_donnee, NULL, 16);
    }

    fclose(file);
}  

void pop(int x, int *SP){
    if (*SP == 0) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);}
    tab_mem[x] = tab_mem[*SP];
    (*SP)--;
}   

void ipop(int *SP) {
     if (*SP < 2) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);}
    tab_mem[tab_mem[*SP-1]] = tab_mem[*SP-2];
    *SP = (*SP)-2;
}

void push(int x, tab[], int *SP) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[SP] = tab_mem[x];
    (*SP)++; 
}

void ipush(int *SP) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*SP-1] = tab_mem[tab_mem[*SP-1]];
}

void push_i (int i, int *SP) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*SP] = i;
    (*SP)++;
}

void jmp(int adr, int *PC){
    *PC = (*PC) + adr; 
}   

void jnz(int adr, int *PC, int *SP) {
    if (*SP == 0) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);}
    if (tab_mem[SP-1] == 0) 
        *PC += adr;
    (*SP)--   
}
 
void call(int adr) {
     if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[SP]
}
