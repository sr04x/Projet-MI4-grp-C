// piece.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille_piece 5
#define max_octets_par_case 5

typedef struct {
    char nom;
    char forme[taille_piece][taille_piece* max_octets_par_case];
}Piece;

void lire_piece(char* nom_fichier, Piece* piece);
void tourner_piece(Piece* piece);
void tourner_n_fois(Piece* piece, int n);
