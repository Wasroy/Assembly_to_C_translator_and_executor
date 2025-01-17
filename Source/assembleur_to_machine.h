#ifndef ASSEMBLEUR_TO_MACHINE_H
#define ASSEMBLEUR_TO_MACHINE_H


//Structure d'une étiquette
typedef struct {
    char nom[30];   // de longueur 30 caractères max donné par Monsieur Emmanuel Lazard sur Teams
    int adresse;    // variable pour stocké l'adresse liée à l'étiquette
} Etiquette;

//Structure pour la table qui va contenir les étiquettes du prgramme
typedef struct {
    Etiquette etiqs[500]; //nb max de ligne d'un fichier, possible si chaque ligne possède une étiquette
    int nombre;     //nb total d'étiquettes enregistrées
} Tableau_detiqs;

//Structure pour traduire une instruction en hexa en stockant son opération et son code opératoire (sa forme en héxa) équivalentes qu'on appellera opcode
typedef struct {
    char* instruction; // Le nom de l'instruction en assembleur
    int opcode;        // sa traduction en hexadécimal associé
} Instruction_assembleur_et_hexa;

//Les fonctions utilisées dans le fichier c: 
int traduire_instruction(const char* ligne, char* convertit, int adresse_courante, Tableau_detiqs* table_etiq);
int traducteur(const char* fichier_source, const char* fichier_sortie);
int obtenir_opcode(const char* instruction);
int est_un_entier(const char* str);
int valider_etiq(const char* etiq);

#endif
