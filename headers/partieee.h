#ifndef PARTIE_H
#define PARTIE_H

void viderBuffer();

void afficherJeu(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece);

void genererPieceAleatoire(Piece *piece, int nb_pieces);

int choisirColonne();

int collision(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y);

int choisirOrientation();

int placer(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece, int colonne, int orientation);

int verifierGameOver(char grille[NB_LIGNES][NB_COLONNES][5]);

void jouerTetris(int nb_pieces);

void afficherMenuPrincipal(int nb_pieces);

#endif // PARTIE_H