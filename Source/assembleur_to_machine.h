#ifndef ASSEMBLEUR_TO_MACHINE_H
#define ASSEMBLEUR_TO_MACHINE_H


//structure d'une étiquette
typedef struct etiq{
    char nom[30];   // de longueur 30 caractères max donné par Monsieur Emmanuel Lazard sur Teams
    int adresse;    // variable pour stocké l'adresse liée à l'étiquette
} Etiquette;

//structure pour la table qui va contenir les étiquettes du prgramme
typedef struct tabledetiqs{
    Etiquette etiqs[500]; //nb max de ligne d'un fichier, possible si chaque ligne possède une étiquette
    int nombre;     //nb total d'étiquettes enregistrées
} Tableau_detiqs;

//structure pour traduire une instruction en hexa en stockant son opération et son code opératoire (sa forme en héxa) équivalentes qu'on appellera opcode
typedef struct instrAetH{
    char* instruction; // Le nom de l'instruction en assembleur
    int opcode;        // sa traduction en hexadécimal associé
} instruction_assembleur_et_hexa;

//Les fonctions du fichier c: 
int traduire_instruction(const char* ligne, char* code_hexa, int adresse_courante, Tableau_detiqs* tbl_etq);
int traducteur(const char* fichier_assembleur, const char* fichier_hexa);
int obtenir_opcode(const char* instruction);
int est_un_entier(const char* str);
int valider_etiq(const char* etiq);

#endif
