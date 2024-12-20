//ICI NOUS METTRONS NOTRE CODE





#include <stdio.h>
#include <string.h>

#define max_mot_par_ligne 100  // Nombre maximum de mots par ligne
#define max_longueur_mot 100 // Longueur maximale d'un mot

int main() {
    char line[256]; // Stocker une ligne de texte
    char *words[max_mot_par_ligne]; // Tableau de pointeurs pour les mots
    int word_count = 0; // Compteur de mots

    // Exemple de ligne (à remplacer par une lecture depuis un fichier ou l'utilisateur)
    strcpy(line, "Ceci est une phrase avec des mots séparés par des espaces.");

    // Découper la ligne en mots
    char *token = strtok(line, " "); // Premier mot
    while (token != NULL && word_count < max_mot_par_ligne) {
        words[word_count] = token; // Ajouter le mot au tableau
        word_count++;
        token = strtok(NULL, " "); // Passer au mot suivant
    }

    // Afficher les mots et leurs indices
    printf("Mots extraits de la ligne :\n");
    for (int i = 0; i < word_count; i++) {
        printf("words[%d] = %s\n", i, words[i]);
    }
    
    printf("BOnjour");

    return 0;
}
