#include <stdio.h>
#include "simulateur.h"


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
