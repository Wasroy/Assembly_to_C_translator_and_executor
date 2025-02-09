#ifndef SIMULATEUR_H
#define SIMULATEUR_H

typedef struct {
    int opcode; 
    int donnee;
} instruction; 

void executeligne(int tab_mem[], int *pSP, int *pPC, instruction **tab_ins, int nb_ligne);
int nombreDeLigne(const char* nomfichier);
void sauvegardercode(instruction* tab[], const char*nomfichier);
void pop(int x, int *SP, int *PC, int tab_mem[]);
void ipop(int *SP, int tab_mem[], int *pPC);
void push(int x,int tab_mem[], int *SP, int*pPc);
void ipush(int *SP, int tab_mem[], int*pPC);
void push_i(int i, int *SP,int tab_mem[], int *pPC);
void jmp(int adr, int *PC, int tab_mem[], int n_ligne);
void jnz(int adr, int *PC, int *SP, int tab_mem[], int n_ligne);
void call(int tab_mem[], int adr, int* pSP, int* pPC, int n_ligne);
void ret(int tab_mem[], int *pSP, int* pPC);
void read(int tab_mem[], int adr, int *pPC);
void write(int tab_mem[], int adr, int *pPC);
void op(int tab_mem[], int *pSP, int i, int *pPC);
void rnd(int tab_mem[], int *pSP, int x, int *pPC);
void dup(int tab_mem[], int *pSP, int *pPC);
void halt(instruction ** tab_ins);

#endif
