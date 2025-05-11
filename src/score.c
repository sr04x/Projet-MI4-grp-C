#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour manipuler chaine de caractere (strcmp() trie score par nom)
#include "score.h"


// Affiche les top N meilleurs scores enregistrés dans le fichier FICHIERS_SCORES
void afficherMeilleursScores(int topN) {
    FILE *f = fopen(FICHIERS_SCORES, "r");
    if (f == NULL) {
        printf("Aucun score enregistré pour le moment.\n");
        return;
    }

    Score scores[MAX_SCORES];
    int n = 0;

    // Lecture des scores depuis le fichier
    while (n < MAX_SCORES && fscanf(f, "%49s %d", scores[n].nom, &scores[n].score) == 2) {
        n++;
    }

    fclose(f);

    if (n == 0) {
        printf("Aucun score enregistré pour le moment.\n");
        return;
    }

    // Affichage des scores
    printf("\n--- Meilleurs scores (Top %d) ---\n", topN);
    for (int i = 0; i < n && i < topN; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].nom, scores[i].score);
    }
}



void sauvegarderScore(Score s) {
    Score scores[MAX_SCORES + 1]; // un de plus pour le score en trop temporaire
    int n = 0;

    // Lecture des scores existants
    FILE *f = fopen(FICHIERS_SCORES, "r");
    if (f != NULL) {
        while (n < MAX_SCORES && fscanf(f, "%49s %d", scores[n].nom, &scores[n].score) == 2) {
            n++;
        }
        fclose(f);
    }

    // Ajout du nouveau score
    scores[n++] = s;

    // Tri décroissant par score (priorité à celui qui est ajouté en dernier en cas d'égalité)
    for (int i = n - 1; i > 0; i--) {
        if (scores[i].score > scores[i - 1].score) {
            Score tmp = scores[i];
            scores[i] = scores[i - 1];
            scores[i - 1] = tmp;
        }
    }

    // Limite à MAX_SCORES
    if (n > MAX_SCORES) {
        n = MAX_SCORES;
    }

    // Réécriture propre du fichier
    f = fopen(FICHIERS_SCORES, "w");
    if (f != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(f, "%s %d\n", scores[i].nom, scores[i].score);
        }
        fclose(f);
    }
}