#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour manipuler chaine de caractere (strcmp() trie score par nom)
#include "score.h"


// Affiche les top N meilleurs scores enregistrés dans le fichier FICHIERS_SCORES
void afficherMeilleursScores(int topN) {
    // Ouvre le fichier des scores en lecture
    FILE *f = fopen(FICHIERS_SCORES, "r");
    if (f == NULL) {
        // Si le fichier n'existe pas encore, on informe simplement l'utilisateur
        printf("Aucun score enregistré pour le moment.\n");
        return;
    }

    Score scores[MAX_SCORES];  // Tableau pour stocker les scores chargés depuis le fichier
    int n = 0; // Compteur du nombre de scores réellement lus

    // Lecture des scores dans le fichier (nom + score), jusqu'à MAX_SCORES
    while (n < MAX_SCORES && fscanf(f, "%49s %d", scores[n].nom, &scores[n].score) == 2) {
        n++;
    }

    fclose(f);  // On ferme le fichier après lecture, c'est plus propre

    // Tri des scores en ordre décroissant (plus grand score en premier)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (scores[j].score > scores[i].score) {
                // Échange des deux structures Score si l’ordre n’est pas bon
                Score tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
        }
    }

    // Affichage propre des scores, limité au topN demandé
    printf("\n--- Meilleurs scores (Top %d) ---\n", topN);
    for (int i = 0; i < n && i < topN; i++) {
        // On affiche le classement, le nom et le score
        printf("%d. %s - %d\n", i + 1, scores[i].nom, scores[i].score);
    }
}


void sauvegarderScore(Score s) {
    FILE *f = fopen(FICHIERS_SCORES, "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture de scores.txt");
        return;
    }
    fprintf(f, "%s %d\n", s.nom, s.score);
    fclose(f);
}
