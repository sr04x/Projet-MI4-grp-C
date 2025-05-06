#include <stdio.h>   // ajouter commentaires
#include "grille.h"

void initialiserGrille(int grille[NB_LIGNES][NB_COLONNES]) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            grille[i][j] = VIDE;
        }
    }
}

void afficherGrille(int grille[NB_LIGNES][NB_COLONNES]) {
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


int supprimerLignesCompletes(int grille[NB_LIGNES][NB_COLONNES]) {
    int lignesSupprimees = 0;
    for (int i = NB_LIGNES - 1; i >= 0; i--) {
        int lignePleine = 1;
        for (int j = 0; j < NB_COLONNES; j++) { // Vérifie si la ligne est pleine
            if (grille[i][j] == VIDE) {
                lignePleine = 0;
                break;
            }
        }
        // Si la ligne est pleine, on la supprime
        if (lignePleine) {
            lignesSupprimees++;
            for (int k = i; k > 0; k--) {// Décale toutes les lignes au-dessus vers le bas
                for (int j = 0; j < NB_COLONNES; j++) {
                    grille[k][j] = grille[k - 1][j];
                }
            }
            for (int j = 0; j < NB_COLONNES; j++) { // Vide la première ligne
                grille[0][j] = VIDE;
            }
            i++;// Important : revérifier la même ligne (car elle a changé)
        }
    }
    return lignesSupprimees;
}
