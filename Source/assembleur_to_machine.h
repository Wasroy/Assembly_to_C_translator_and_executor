#ifndef ASSEMBLEURTOMACHINE_H //verif si pas deja utilisé et alors on peut continuer
#define ASSEMBLEURTOMACHINE_H // si pas deja utilisé on definit

//traduire fichier assembleur au langage machine (hexa genre 0X....)
int traducteur(const char *fichier_a_traduire, const char *fichier_traduit);

#endif //termine la condition pour fermer le header et ne pas pouvoir l'inclure une autre fois
