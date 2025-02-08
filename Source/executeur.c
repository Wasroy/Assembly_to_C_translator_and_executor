#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "executeur.h"

void executeligne(int tab_mem[], int *pSP, int *pPC, instruction **tab_ins, int nb_ligne) {
    
    switch (tab_ins[(*pPC)-1]->opcode) {
        case 0: 
            pop(tab_ins[*pPC-1]->donnee, pSP, pPC, tab_mem);
            break;
        case 1: 
            ipop(pSP, tab_mem, pPC);
            break;
        case 2:
            push(tab_ins[*pPC-1]->donnee, tab_mem, pSP, pPC);
            break;
        case 3:
            ipush(pSP, tab_mem, pPC);
            break;
        case 4: 
            push_i(tab_ins[*pPC-1]->donnee, pSP, tab_mem, pPC);
            break;
        case 5: 
            jmp(tab_ins[*pPC-1]->donnee, pPC, tab_mem, nb_ligne);
            break;
        case 6: 
            jnz(tab_ins[*pPC-1]->donnee, pPC, pSP, tab_mem, nb_ligne);
            break;
        case 7: 
            call(tab_mem, tab_ins[*pPC-1]->donnee, pSP, pPC, nb_ligne);
            break;
        case 8: 
            ret(tab_mem, pSP, pPC);
            break;
        case 9: 
            read(tab_mem, tab_ins[*pPC-1]->donnee, pPC);
            break;
        case 10: 
            write(tab_mem, tab_ins[*pPC-1]->donnee, pPC);
            break;
        case 11:
            op(tab_mem, pSP, tab_ins[*pPC-1]->donnee, pPC);
            break;
        case 12: 
            rnd(tab_mem, pSP, tab_ins[*pPC-1]->donnee, pPC);
            break;
        case 13: 
            dup(tab_mem, pSP, pPC);
            break;
        case 99: 
            halt(tab_ins);
            break;
    }
}


int nombreDeLigne(const char* nomfichier) {  
	FILE* file = fopen(nomfichier,"r");
    if (file == NULL) {
        perror("\033[1;31mErreur lors de l'ouverture du fichier\033[0m");
        exit(EXIT_FAILURE);
    }

	int NbDeLigne = 0;
	char c;
	while((c = fgetc(file)) != EOF){
		if(c == '\n') NbDeLigne +=1; /* Le \n est le caractère de fin de ligne, il figure donc même sur la dernière */
		}
	fclose(file);
	if (NbDeLigne == 0) {
		printf("\033[1;31mFichier vide\033[0m\n");
        	exit(1);
		}
	return NbDeLigne;
}
    
void savecode(instruction* tab[], const char* nomfichier) {
    FILE *file = fopen(nomfichier, "r");
    if (file == NULL) {
        perror("\033[1;31mErreur lors de l'ouverture du fichier\033[0m");
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

        //printf("Code instruction fichier : %s, Code donnee fichier : %s\n", s_opcode, s_donnee);
        
        tab[i] = (instruction *)malloc(sizeof(instruction));
        if (tab[i] == NULL){
			printf("\033[1;31mUne allocation mémoire n'a pas pu être effectué\033[0m\n");
			exit(1);
			}
        int a = (int)strtol(s_opcode, NULL, 16);
        
        int b = (int)strtol(s_donnee, NULL, 16);

        if (a>32767) {
            tab[i]->opcode = a - 65536;}
        else {tab[i]->opcode = a;}
        
        if (b>32767) {
            tab[i]->donnee = b - 65536;}
        else {tab[i]->donnee = b;}
        i++;
    }

    fclose(file);
}  

void pop(int x, int *SP,int *PC, int tab_mem[]) {
    if (*SP == 0) {
        printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction pop (SP vaut 0).\033[0m\n", *PC); //On affiche la ligne *PC car PC représente l'instruction suivante. Or le tableau d'instruction commence à 0, et pour afficher la ligne correspondante, on afficher donc *PC-1+1=*PC 
        exit(EXIT_FAILURE);
    }
    tab_mem[x] = tab_mem[*SP-1];
    (*SP)--;
}   

void ipop(int *SP, int tab_mem[], int* pPC) {
     if (*SP < 2) {
        printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction ipop (SP vaut 0).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    tab_mem[tab_mem[*SP-1]] = tab_mem[*SP-2];
    *SP = (*SP)-2;
    //printf("On a pop la valeur %d\n", tab_mem[tab_mem[*SP-1]]);
}

void push(int x,int tab_mem[], int *SP, int* pPC) {
    if (*SP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction push - Mémoire saturée (SP > 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    if (x < 0 || x > 4999) {
        printf("\033[1;31mErreur ligne %d : Adresse invalide lors de l'appel à la fonction push - x < 0 ou x > 4999\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    if (tab_mem[*SP] != 0)
    printf("\033[38;5;214m Warning ligne %d : la pile a peut être écrasé des données à l'adresse %d \033[0m\n",*pPC, *SP);

    tab_mem[*SP] = tab_mem[x];
    (*SP)++; 
    //printf("On a mis en haut de la pile la valeur %d\n", tab_mem[x]);
}

void ipush(int *SP, int tab_mem[], int* pPC) {
    if (*SP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction ipush - Mémoire saturée (SP > 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    if (tab_mem[*SP-1] != 0)
        printf("\033[38;5;214m Warning ligne %d : la pile a peut être écrasé des données à l'adresse %d \033[0m\n",*pPC, *SP);
    tab_mem[*SP-1] = tab_mem[tab_mem[*SP-1]];
    //printf("On a mis en haut de la pile la valeur %d\n", tab_mem[tab_mem[*SP-1]]);
}

void push_i (int i, int *SP, int tab_mem[], int *pPC) {
    if (*SP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction push# i - Mémoire saturée (SP > 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    if (tab_mem[*SP] != 0)
        printf("\033[38;5;214m Warning ligne %d : la pile a peut être écrasé des données à l'adresse %d \033[0m\n",*pPC, *SP);

    tab_mem[*SP] = i;
    (*SP)++;
}

void jmp(int adr, int *PC, int tab_mem[], int n_ligne) {
    if (adr == -1) {
        printf("\033[1;31mErreur ligne %d : boucle infine détectée (JMP -1).\033[0m\n", *PC);
    }
    int a = *PC; //On stocke l'adresse de l'instruction dans un variable temporaire pour pouvoir afficher la ligne en cas d'erreur

    *PC += adr; 

    if (*PC < 0) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à JMP (PC < 0).\033[0m\n", a);
        exit(EXIT_FAILURE);}
    if (*PC > n_ligne) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à JMP (PC >= n_ligne).\033[0m\n", a);
        exit(EXIT_FAILURE);}
}   

void jnz(int adr, int *PC, int *pSP, int tab_mem[], int n_ligne) { 

    if (adr == -1) {
        printf("\033[1;31mErreur ligne %d : boucle infine détectée (JMP -1).\033[0m\n", *PC);
    }

    if (*pSP == 0) {
        printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction JNZ (SP vaut 0).\033[0m\n", *PC);
        exit(EXIT_FAILURE);}
    (*pSP)-- ; 

    int a = *PC; //On stocke l'adresse de l'instruction dans un variable temporaire pour pouvoir afficher la ligne en cas d'erreur

    if (tab_mem[*pSP] != 0) {
        *PC += adr;}
    
    if (*PC < 0) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à JNZ (PC < 0).\033[0m\n", a);
        exit(EXIT_FAILURE);}
    if (*PC > n_ligne) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à JNZ (PC >= n_ligne).\033[0m\n", a);
        exit(EXIT_FAILURE);
        }
}
 
void call(int tab_mem[], int adr, int* pSP, int* pPC, int n_ligne) {

    if (adr == -1) {
        printf("\033[1;31mErreur ligne %d : boucle infine détectée (JMP -1).\033[0m\n", *pPC);

    }

     if (*pSP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction call - Mémoire saturée (SP vaut 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    
    if (tab_mem[*pSP] != 0)
        printf("\033[38;5;214m Warning ligne %d : la pile a peut être écrasé des données à l'adresse %d \033[0m\n",*pPC, *pSP);

    int a = *pPC; //On stocke l'adresse de l'instruction dans un variable temporaire pour pouvoir afficher la ligne en cas d'erreur

    tab_mem[*pSP] = *pPC;
    (*pSP)++;
    *pPC += adr;
    
    if (*pPC < 0) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à call (PC < 0).\033[0m\n", a);
        exit(EXIT_FAILURE);}
    if (*pPC > n_ligne) {
        printf("\033[1;31mErreur ligne %d : On tente d'acceder à une instruction inexistante après un appel à call (PC >= n_ligne).\033[0m\n", a);
        exit(EXIT_FAILURE);
    }
}

void ret (int tab_mem[], int *pSP, int* pPC) {
    if (*pSP == 0) {
        printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction JNZ (SP vaut 0).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}

    *pPC = tab_mem[*pSP]; 
    (*pSP)--;
    //printf("Rien compris à la fonction mais on l'a effectuée\n");
}

void read(int tab_mem[], int adr, int *pPC) {

    if (adr < 0 || adr > 4999) {
        printf("\033[1;31mErreur ligne %d : Adresse invalide lors de l'appel à la fonction read - ard < 0 ou adr > 4999\033[0m\n", *pPC);
        exit(EXIT_FAILURE);
    }
    int x;
    printf("Entrez une valeur : ");
    scanf("%d", &x); //On ne fait pas de test - On considère que l'utilisateur rentre une valeur correcte
    tab_mem[adr] = x;

}


void write(int tab_mem[], int adr, int *pPC) {
    if (adr < 0 || adr > 4999) {
        printf("\033[1;31mErreur ligne %d : Adresse invalide lors de l'appel à la fonction write - ard < 0 ou adr > 4999\033[0m\n", *pPC);
        exit(EXIT_FAILURE);
    }
    printf("La valeur contenue a l'adresse %d est %d.\n",adr, tab_mem[adr]);
}

void op(int tab_mem[], int *pSP, int i, int *PC) {
    switch (i) {    
        case 0: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 0 (SP vaut 1 ou 0).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP] == tab_mem[*pSP-1]) 
                tab_mem[*pSP-1] = 1;
            else 
                tab_mem[*pSP-1] = 0;     
            break;
        case 1: 
        if (*pSP < 2) {
            printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 1 (SP < 2).\033[0m\n", *PC);
            exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP] == tab_mem[*pSP-1]) 
                tab_mem[*pSP-1] = 0;
            else 
                tab_mem[*pSP-1] = 1;   
            break;
        case 2: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 2 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP - 1] >= tab_mem[*pSP])
                tab_mem[*pSP-1] = 1;
            else 
                tab_mem[*pSP-1] = 0;
            break;
        case 3: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 3 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP - 1] <= tab_mem[*pSP])
                tab_mem[*pSP-1] = 1;
            else 
                tab_mem[*pSP-1] = 0;
            break;
        case 4: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d: Débordement négatif de la pile lors de l'appel à la fonction op 4 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP - 1] > tab_mem[*pSP])
                tab_mem[*pSP-1] = 1;
            else 
                tab_mem[*pSP-1] = 0;
            break;
        case 5: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 5 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            if (tab_mem[*pSP - 1] < tab_mem[*pSP])
                tab_mem[*pSP-1] = 1;
            else 
                tab_mem[*pSP-1] = 0;
            break;
        case 6: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 6 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) | (tab_mem[*pSP]);
            break;
        case 7: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 7 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) ^ (tab_mem[*pSP]); 
            break;
        case 8: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 8 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            (tab_mem[*pSP-1]) = (tab_mem[*pSP-1]) & (tab_mem[*pSP]);
            break;
        case 9: 
            if (*pSP < 1) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 9 (SP < 1).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (tab_mem[*pSP-1]) = ~(tab_mem[*pSP-1]);
            break;
        case 10: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 10 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            int s = (tab_mem[*pSP-1]) + (tab_mem[*pSP]);

            //Verification que le nombre obtenu est codable sur 16 bits

            if (s <= 32767 && s >= -32768) {
                tab_mem[*pSP-1] = s;}
            else {
                printf("\033[1;31mErreur ligne %d : Resultat de %d + %d non codable sur 16bits.\033[0m\n", *PC, tab_mem[*pSP-1], tab_mem[*pSP]);
                exit(EXIT_FAILURE);
            }
            break;
        case 11: 
            if (*pSP < 2) {
                printf("\033[1;31mErreur %d : Débordement négatif de la pile lors de l'appel à la fonction op 11 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            s = (tab_mem[*pSP-1]) - (tab_mem[*pSP]);

            //Verification que le nombre obtenu est codable sur 16 bits

            if (s <= 32767 && s >= -32768) {
                tab_mem[*pSP-1] = s;}
            else {
                printf("\033[1;31mErreur ligne %d : Resultat de %d - %d non codable sur 16bits.\033[0m\n", *PC, tab_mem[*pSP-1], tab_mem[*pSP]);
                exit(EXIT_FAILURE);
            }
            break;
        case 12:
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 12 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            int m = (tab_mem[*pSP-1]) * (tab_mem[*pSP]);
            if (m <= 32767 && m >= -32768) {
                tab_mem[*pSP-1] = m;}
            else {
                printf("\033[1;31mErreur ligne %d : Resultat de %d * %d non codable sur 16bits.\033[0m\n", *PC, tab_mem[*pSP-1], tab_mem[*pSP]);
                exit(EXIT_FAILURE);
            }
            break;
            
        case 13:
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 13 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            tab_mem[*pSP-1] = (tab_mem[*pSP-1]) / (tab_mem[*pSP]); //Pas besoin d'ajouter un test pour la division par 0 car on ne peut pas diviser par 0 en C
            break;
        case 14:
            if (*pSP < 2) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 14 (SP < 2).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            (*pSP)--;
            tab_mem[*pSP-1] = (tab_mem[*pSP-1]) % (tab_mem[*pSP]); //Pas besoin d'ajouter un test pour la division par 0 car on ne peut pas diviser par 0 en C
            break;
        case 15: 
            if (*pSP < 1) {
                printf("\033[1;31mErreur ligne %d : Débordement négatif de la pile lors de l'appel à la fonction op 15 (SP < 1).\033[0m\n", *PC);
                exit(EXIT_FAILURE);}
            tab_mem[*pSP-1] = -(tab_mem[*pSP-1]);
            break;
    }
}

void rnd(int tab_mem[], int *pSP, int x, int *pPC) {
    if (*pSP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction rnd - Mémoire saturée (SP > 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);}
    
    if (tab_mem[*pSP] != 0)
        printf("\033[38;5;214m Warning ligne %d : la pile a peut être écrasé des données à l'adresse %d \033[0m\n", *pSP, *pPC);
    tab_mem[*pSP] = rand() % x; //rand() % x (bibliothèque stdlib) renvoie un nombre aléatoire entre 0 et x-1
    (*pSP)++;
}

void dup(int tab_mem[], int *pSP, int *pPC) {
    if (*pSP > 4999) {
        printf("\033[1;31mErreur ligne %d : Débordement de la pile lors de l'appel à la fonction rnd - Mémoire saturée (SP > 4999).\033[0m\n", *pPC);
        exit(EXIT_FAILURE);
    }

    if (tab_mem[*pSP] != 0)
        printf("\033[38;5;214m Warning ligne %d: la pile a peut être écrasé des données à l'adresse %d \033[0m\n", *pSP, *pPC);

    tab_mem[*pSP] = tab_mem[*pSP-1];
    (*pSP)++;
}

void halt(instruction** tab_ins) {
    printf("Fin du programme\n");
    free(tab_ins);
    exit(EXIT_SUCCESS);
}
