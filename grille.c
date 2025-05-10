#include <string.h>
#include <stdio.h>
#include "grille.h"

void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES][5]) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            strcpy(grille[i][j], FOND);  // chaque case contient 🟦
        }
    }
}

void afficherGrille(char grille[NB_LIGNES][NB_COLONNES][5]) {
    printf("Voici votre grille :\n  ");
    printf(" ");
    for (int col = 0; col < NB_COLONNES; col++) {
        printf("%c ", 'A' + col);
    }
    printf(" :\n");

    for (int i = 0; i < NB_LIGNES; i++) {
        printf("  ");
        for (int j = 0; j < NB_COLONNES; j++) {
            printf("%s", grille[i][j]);
        }
        printf("\n");
    }
}

int supprimerLignesCompletes(char grille[NB_LIGNES][NB_COLONNES][5]) {
    int lignesSupprimees = 0;

    for (int i = NB_LIGNES - 1; i >= 0; i--) {
        int lignePleine = 1;
        for (int j = 0; j < NB_COLONNES; j++) {
            if (strcmp(grille[i][j], FOND) == 0) {
                lignePleine = 0;
                break;
            }
        }

        if (lignePleine) {
            lignesSupprimees++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < NB_COLONNES; j++) {
                    strcpy(grille[k][j], grille[k - 1][j]);
                }
            }
            for (int j = 0; j < NB_COLONNES; j++) {
                strcpy(grille[0][j], FOND);
            }
            i++;  // revérifie la ligne
        }
    }

    return lignesSupprimees;
}