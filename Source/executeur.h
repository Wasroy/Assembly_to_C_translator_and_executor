#ifndef SIMULATEUR_H
#define SIMULATEUR_H

typedef struct {
    int opcode; 
    int donnee;
} instruction; 

void executeligne(int tab_mem[], int *pSP, int *pPC, instruction **tab_ins);
int nombreDeLigne(const char* nomfichier);
void savecode(instruction* tab[], int nligne, const char*nomfichier);
void pop(int x, int *SP, int *PC, int tab_mem[]);
void ipop(int *SP, int tab_mem[]);
void push(int x,int tab_mem[], int *SP);
void ipush(int *SP, int tab_mem[]);
void push_i(int i, int *SP,int tab_mem[]);
void jmp(int adr, int *PC, int tab_mem[]);
void jnz(int adr, int *PC, int *SP, int tab_mem[]);
void call(int tab_mem[], int adr, int* pSP, int* pPC);
void ret(int tab_mem[], int *pSP, int* pPC);
void read(int tab_mem[], int adr);
void write(int tab_mem[], int adr);
void op(int tab_mem[], int *pSP, int i);
void rnd(int tab_mem[], int *pSP, int x);
void dup(int tab_mem[], int *pSP);
void halt(instruction ** tab_ins);

#endif
