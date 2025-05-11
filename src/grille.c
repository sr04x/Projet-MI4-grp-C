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
    int lignesSupprimees = 0;  // Compteur du nombre de lignes pleines supprimées

    // Parcours de la grille de bas en haut (i = ligne)
    for (int i = NB_LIGNES - 1; i >= 0; i--) {
        int lignePleine = 1;  // Hypothèse : la ligne est pleine

        // Vérifie chaque case de la ligne i
        for (int j = 0; j < NB_COLONNES; j++) {
            if (strcmp(grille[i][j], FOND) == 0) {
                // Si une seule case est vide (contient FOND), la ligne n'est pas pleine
                lignePleine = 0;
                break; // inutile de vérifier les autres cases
            }
        }

        // Si la ligne est pleine, on la supprime
        if (lignePleine) {
            lignesSupprimees++;  // On note qu'on a supprimé une ligne

            // Décalage vers le bas de toutes les lignes au-dessus
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < NB_COLONNES; j++) {
                    // Copie la case au-dessus (k-1) dans la ligne actuelle (k)
                    strcpy(grille[k][j], grille[k - 1][j]);
                }
            }

            // Remplit la première ligne (tout en haut) avec des cases vides
            for (int j = 0; j < NB_COLONNES; j++) {
                strcpy(grille[0][j], FOND);
            }

            i++;  // ⚠️ Re-vérifie cette ligne (nouvelle ligne descendue ici après décalage)
            // Sans ce i++, on pourrait sauter la vérif d'une ligne fusionnée
        }
    }

    return lignesSupprimees;  // Nombre total de lignes supprimées
}

