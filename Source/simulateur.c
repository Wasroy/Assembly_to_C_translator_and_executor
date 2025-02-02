#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulateur.h"

int nombreDeLigne(const char* nomfichier) {  
	FILE* file = fopen(nomfichier,"r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

	int NbDeLigne = 0;
	char c;
	while((c = fgetc(file)) != EOF){
		if(c == '\n') NbDeLigne +=1; /* Le \n est le caractère de fin de ligne, il figure donc même sur la dernière */
		}
	fclose(file);
	if (NbDeLigne == 0) {
		printf("Fichier vide\n");
        exit(1);
		}
	return NbDeLigne;
}
    
void savecode(instruction* tab[], int nlignes, const char* nomfichier) {
    FILE *file = fopen(nomfichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }    
    // Lecture du fichier et remplissage du tableau
    char s_opcode[3] = {0};
    char s_donnee[5] = {0};
    char ligne[10];
    int i = 0; 
    while (fgets(ligne, 10, file) != NULL){
        
        strncpy(s_opcode, ligne, 2);
        s_opcode[2] = '\0'; 
        strncpy(s_donnee, ligne + 3, 4); 
        s_donnee[4] = '\0'; 
        
        tab[i] = (instruction *)malloc(sizeof(instruction));
        if (tab[i] == NULL){
			printf("Une allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}

        tab[i]->opcode = (int)strtol(s_opcode, NULL, 16);  
        tab[i]->donnee = (int)strtol(s_donnee, NULL, 16);

        i++;
    }

    fclose(file);
}  

void pop(int x, int *SP, int tab_mem[]) {
    if (*SP == 0) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);
    }
    tab_mem[x] = tab_mem[*SP];
    (*SP)--;
}   

void ipop(int *SP, int tab_mem[]) {
     if (*SP < 2) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);}
    tab_mem[tab_mem[*SP-1]] = tab_mem[*SP-2];
    *SP = (*SP)-2;
}

void push(int x,int tab_mem[], int *SP) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*SP] = tab_mem[x];
    (*SP)++; 
}

void ipush(int *SP, int tab_mem[]) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*SP-1] = tab_mem[tab_mem[*SP-1]];
}

void push_i (int i, int *SP, int tab_mem[]) {
    if (*SP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*SP] = i;
    (*SP)++;
}

void jmp(int adr, int *PC){
    *PC = (*PC) + adr; 
}   

void jnz(int adr, int *PC, int *pSP, int tab_mem[]) {
    if (*pSP == 0) {
        printf("Erreur : Débordement négatif de la pile (pile vide).\n");
        exit(EXIT_FAILURE);}
    if (tab_mem[*pSP-1] == 0) 
        *PC += adr;
    (*pSP)-- ; 
}
 
/*void call(int adr, int*pSP) {
     if (*pSP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*pSP];
}
*/