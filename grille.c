#include <stdio.h>
#include "grille.h"

void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES]) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            grille[i][j] = VIDE;
        }
    }
}

void afficherGrille(char grille[NB_LIGNES][NB_COLONNES]) {
    // En-tête
    printf("Voici votre grille :\n  ");
    for (int col = 0; col < NB_COLONNES; col++) {
        printf(" %c", 'A' + col);
    }
    printf(" :\n");

    // Grille
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("  ");
        for (int j = 0; j < NB_COLONNES; j++) {
            printf("|%c", grille[i][j]);
        }
        printf("|\n");
    }
}
