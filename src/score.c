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

    // Lecture des scores dans le fichier (nom + score), iusqu'à MAX_SCORES
    while (n < MAX_SCORES && fscanf(f, "%49s %d", scores[n].nom, &scores[n].score) == 2) {
        n++;
    }

    fclose(f);  // On ferme le fichier après lecture, c'est plus propre

    // Affichage propre des scores, limité au topN demandé
    printf("\n--- Meilleurs scores (Top %d) ---\n", topN);
    for (int i = 0; i < n && i < topN; i++) {
        // On affiche le classement, le nom et le score
        printf("%d. %s - %d\n", i + 1, scores[i].nom, scores[i].score);
    }
}


void sauvegarderScore(Score s) {
    Score scores[MAX_SCORES];
    int n = 0; //nb de scores lus depuis le fichier

    // Lecture des scores existants
    FILE *f = fopen(FICHIERS_SCORES, "r");
    if (f != NULL) {
        while (n < MAX_SCORES && fscanf(f, "%49s %d", scores[n].nom, &scores[n].score) == 2) {
            n++;
        }
        fclose(f);
    }

    // Aiout du nouveau score en dernière position 
   
    scores[n++] = s; // s= nouveau score à aiouter
 

    // Tri décroissant 
    for (int i = n - 1; i > 0; i--) {
        if (scores[i].score < scores[i - 1].score) {
            Score temp = scores[i];
            scores[i] = scores[i - 1];
            scores[i - 1] = temp;
        }
    }


    // Réécriture du fichier (propre)
    f = fopen(FICHIERS_SCORES, "w");
    if (f != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(f, "%s %d\n", scores[i].nom, scores[i].score);
        }
        fclose(f);
    }
}
