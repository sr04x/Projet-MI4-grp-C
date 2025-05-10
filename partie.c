#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // sleep()
#include "partie.h"
#include "grille.h"
#include "piece.h"
#include "score.h"


/// Vérifie si la pièce `p` entre en collision avec la grille à la position `(x, y)`
static int collision(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (p->forme[i][j][0] != VIDE) {
                int gx = x + j, gy = y + i;
                if (gx < 0 || gx >= NB_COLONNES || gy >= NB_LIGNES || (gy >= 0 && grille[gy][gx] != VIDE))
                    return 1;
            }
        }
    }
    return 0;
}

/// Place la pièce `p` dans la grille à la position `(x, y)`
static void placer(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (p->forme[i][j][0] != VIDE && y + i >= 0) {
                grille[y + i][x + j] = p->forme[i][j][0];
            }
        }
    }
}

/// Boucle principale du jeu
static void boucleDeJeu(void) {
    int grilleJeu[NB_LIGNES][NB_COLONNES];
    initialiserGrille(grilleJeu);
    int score = 0;
    const char *lettres = "IJLOSTZ";

    srand(time(NULL));  // Initialisation du générateur aléatoire

    while (1) {
        // Génération d'une nouvelle pièce
        Piece p;
        char chemin[64];
        snprintf(chemin, sizeof chemin, "style_piece/%c_piece.txt", lettres[rand() % 7]);
        lire_piece(chemin, &p);
        tourner_n_fois(&p, rand() % 4);

        // Position initiale
        int x = (NB_COLONNES - taille_piece) / 2, y = -TAILLE_PIECE;

        // Vérification du game-over
        if (collision(grilleJeu, &p, x, y)) break;

        // Descente de la pièce
        while (!collision(grilleJeu, &p, x, y + 1)) {
            afficherGrille(grilleJeu);
            sleep(1);
            y++;
        }

        // Verrouillage et mise à jour du score
        placer(grilleJeu, &p, x, y);
        score += supprimerLignesCompletes(grilleJeu) * 100;
    }

    // Fin de partie
    printf("\nGame Over ! Score final : %d\n", score);
    char nom[NOM_MAX];
    printf("Entrez votre nom : ");
    if (fgets(nom, NOM_MAX, stdin)) {
        nom[strcspn(nom, "\n")] = '\0';
        sauvegarderScore(nom, score);
    }
    afficherScores();
}

/// Affiche le menu principal et gère les choix
void afficherMenuPrincipal(void) {
    int choix;
    do {
        printf("\n=== TETRIS ===\n");
        printf("1. Nouvelle partie\n2. Voir scores\n3. Quitter\nVotre choix : ");

        if (scanf("%d", &choix) != 1) choix = 3;
        while (getchar() != '\n');  // Nettoyage du buffer

        switch (choix) {
            case 1: nouvellePartie(); break;
            case 2: afficherScores(); break;
            case 3: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 3);
}

/// Lance une nouvelle partie
void nouvellePartie(void) {
    boucleDeJeu();
}
