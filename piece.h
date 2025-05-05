// piece.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille_piece 5
#define max_taille 32

typedef struct {
    char nom;
    char forme[taille_piece][max_taille];
}Piece;

void lire_piece(char* nom_fichier, Piece* piece);
void tourner_piece(Piece* piece);

