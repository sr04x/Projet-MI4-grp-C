#ifndef PARTIE_H
#define PARTIE_H

void viderBuffer();

void afficherJeu(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece);

void genererPieceAleatoire(Piece *piece);

int choisirColonne();

int collision(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y);

int choisirOrientation();

void placer(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece, int colonne, int orientation);

int verifierGameOver(char grille[NB_LIGNES][NB_COLONNES][5]);

void jouerTetris();

void afficherMenuPrincipal();

#endif // PARTIE_H