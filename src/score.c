#include <stdio.h>
//#include <stlib.h> // pas besoin pour l'instant peut etre plus tard pour trier score (qsort)
#include <string.h> //pour manipuler chaine de caractere (strcmp() trie score par nom)
#include "score.h"


void afficherScores() {
    FILE *f = fopen("scores.txt", "r");
    if (f == NULL) {
        printf("Aucun score enregistré pour le moment.\n");
        return;
    }

    char ligne[100];
    printf("\n--- Scores enregistrés ---\n");
    while (fgets(ligne, sizeof(ligne), f)) {
        printf("%s", ligne);
    }
    fclose(f);
}


void sauvegarderScore(const char *nom, int score) {
    FILE *f = fopen("scores.txt", "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture de scores.txt");
        return;
    }
    fprintf(f, "%s %d\n", nom, score);
    fclose(f);
}
