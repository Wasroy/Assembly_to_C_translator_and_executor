#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executeur.h"



void executeligne(int tab_mem[], int *pSP, int *pPC, instruction **tab_ins) {
    switch (tab_ins[*pPC]->opcode) {
        case 0: 
            (*pPC)++;
            pop(tab_ins[*pPC - 1]->donnee, pSP, tab_mem);
        case 1: 
            (*pPC)++;
            ipop(pSP, tab_mem);
        case 2:
            (*pPC)++;
            push(tab_ins[*pPC - 1]->donnee, tab_mem, pSP);
        case 3:
            (*pPC)++;
            ipush(pSP, tab_mem);
        case 4: 
            (*pPC)++;
            push_i(tab_ins[*pPC - 1]->donnee, pSP, tab_mem);
        case 5: 
            (*pPC)++;
            jmp(tab_ins[*pPC - 1]->donnee, pPC);
        case 6: 
            (*pPC)++;
            jnz(tab_ins[*pPC - 1]->donnee, pPC, pSP, tab_mem);
        case 7: 
            (*pPC)++;
            call(tab_mem, tab_ins[*pPC - 1]->donnee, pSP, pPC);
        case 8: 
            (*pPC)++;
            ret(tab_mem, pSP, pPC);
        case 9: 
            (*pPC)++;
            read(tab_mem, tab_ins[*pPC - 1]->donnee);
        case 10: 
            (*pPC)++;
            write(tab_mem, tab_ins[*pPC - 1]->donnee);
        case 11:
            (*pPC)++;
            op(tab_mem, pSP, tab_ins[*pPC - 1]->donnee);
        case 12: 
            (*pPC)++;
            rnd(tab_mem, pSP, tab_ins[*pPC - 1]->donnee);
        case 13: 
            (*pPC)++;
            dup(tab_mem, pSP);
        case 14: 
            halt();
    }
}


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
 
void call(int tab_mem[], int adr, int* pSP, int* pPC) {
     if (*pSP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);}
    tab_mem[*pSP] = *pPC;
    *pPC += adr;
}

void ret (int tab_mem[], int *pSP, int* pPC) {
    *pPC = tab_mem[*pSP]; 
    (*pSP)--;
}

void read(int tab_mem[], int adr) {
    if (adr < 0 || adr > 4999) {
        printf("Erreur : Adresse invalide.\n");
        exit(EXIT_FAILURE);
    }
    int x;
    printf("Entrez une valeur : ");
    scanf("%d", &x);
    tab_mem[adr] = x;
}


void write(int tab_mem[], int adr) {
    if (adr < 0 || adr > 4999) {
        printf("Erreur : Adresse invalide.\n");
        exit(EXIT_FAILURE);
    }
    printf("La valeur contenue à l'adresse %d est %d\n",adr, tab_mem[adr]);
}

void op(int tab_mem[], int *pSP, int i) {
    switch (i) {    
        case 0: 
            (*pSP)--;
            if (tab_mem[*pSP] == tab_mem[*pSP-1]) 
                tab_mem[*pSP] = 1;
            else 
                tab_mem[*pSP] = 0;     
        case 1: 
            (*pSP)--;
            if (tab_mem[*pSP] == tab_mem[*pSP-1]) 
                tab_mem[*pSP] = 0;
            else 
                tab_mem[*pSP] = 1;   
        case 2: 
            (*pSP)--;
            if (tab_mem[*pSP - 1] >= tab_mem[*pSP])
                tab_mem[*pSP] = 1;
            else 
                tab_mem[*pSP] = 0;
        case 3: 
            (*pSP)--;
            if (tab_mem[*pSP - 1] <= tab_mem[*pSP])
                tab_mem[*pSP] = 1;
            else 
                tab_mem[*pSP] = 0;
        case 4: 
            (*pSP)--;
            if (tab_mem[*pSP - 1] > tab_mem[*pSP])
                tab_mem[*pSP] = 1;
            else 
                tab_mem[*pSP] = 0;
        case 5: 
            (*pSP)--;
            if (tab_mem[*pSP - 1] < tab_mem[*pSP])
                tab_mem[*pSP] = 1;
            else 
                tab_mem[*pSP] = 0;
        case 6: 
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) | (tab_mem[*pSP]);
        case 7: 
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) ^ (tab_mem[*pSP]); 
        case 8: 
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) & (tab_mem[*pSP]);
        case 9: 
            (tab_mem[*pSP-1]) = ~(tab_mem[*pSP-1]);
        case 10: 
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) + (tab_mem[*pSP]);
        case 11: 
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) - (tab_mem[*pSP]);
        case 12:
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) * (tab_mem[*pSP]);
        case 13:
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) / (tab_mem[*pSP]);
        case 14:
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) % (tab_mem[*pSP]);
        case 15: 
            (tab_mem[*pSP-1]) = -(tab_mem[*pSP-1]);
    }
}

void rnd(int tab_mem[], int *pSP, int x) {
    tab_mem[*pSP] = rand() % x; //rand() % x (bibliothèque stdlib) renvoie un nombre aléatoire entre 0 et x-1
    (*pSP)++;
}

void dup(int tab_mem[], int *pSP) {
    if (*pSP == 4999) {
        printf("Erreur : Débordement de la pile (pile pleine).\n");
        exit(EXIT_FAILURE);
    }
    tab_mem[*pSP] = tab_mem[*pSP-1];
    (*pSP)++;
}

void halt() {
    exit(EXIT_SUCCESS);
}
