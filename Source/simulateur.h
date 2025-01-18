#ifndef SIMULATEUR_H
#define SIMULATEUR_H

typedef struct {
    int opcode; 
    int donnee;
} instruction; 

int nombreDeLigne(const char* nomfichier);
void savecode(instruction* tab[], int nligne, const char*nomfichier);
void pop(int x, int *SP, int tab_mem[]);
void ipop(int *SP, int tab_mem[]);
void push(int x,int tab_mem[], int *SP);
void ipush(int *SP, int tab_mem[]);
void push_i(int i, int *SP,int tab_mem[]);
void jmp(int adr, int *PC);
void jnz(int adr, int *PC, int *SP, int tab_mem[]);
void call(int adr, int *pSP);

#endif
