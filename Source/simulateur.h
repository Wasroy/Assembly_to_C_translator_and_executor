#ifndef SIMULATEUR_H
#define SIMULATEUR_H

typedef struct {
    int opcode; 
    int donnee;
} instruction; 

int nombreDeLigne(const char* nomfichier);
void save_code(int tab[], int nligne, instruction* ptr);
void pop(int x, int *SP);
void ipop(int *SP);
void push(int x, tab[], int *SP);
void ipush(int *SP);
void push_i (int i, int *SP);
void jmp(int adr, int *PC);
void jnz(int adr, int *PC, int *SP);
void call(int adr);

#endif
