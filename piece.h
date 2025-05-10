// piece.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_PIECE 5
/*#define max_octets_par_case 5
#define max_taille 100*/

typedef struct {
    char nom;
    char forme[TAILLE_PIECE][TAILLE_PIECE][5];
}Piece;

// Lecture d'une pièce depuis un fichier
void lire_piece(char* nom_fichier, Piece* piece);

// Affiche une pièce dans le terminal
void afficher_piece(Piece* piece);

// Fait une rotation à 90° dans le sens antihoraire
Piece rotation_90_antihoraire(Piece* original, Piece* resultat);

// Fait nb_rotations rotations antihoraires (0 à 3)
Piece rotation_piece_multiple(Piece* piece, int nb_rotations);

/*void tourner_piece(Piece* piece);
void tourner_n_fois(Piece* piece, int n);*/
