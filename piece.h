// piece.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille_piece 5
/*#define max_octets_par_case 5
#define max_taille 100*/

typedef struct {
    char nom;
    char forme[taille_piece][taille_piece][5];
}Piece;

// Lecture d'une pièce depuis un fichier
void lire_piece(char* nom_fichier, Piece* piece);

// Affiche une pièce dans le terminal
void afficher_piece(Piece* piece);

// Fait une rotation à 90° dans le sens antihoraire
void rotation_90_anti_horaire(Piece* original, Piece* resultat);


/*void tourner_piece(Piece* piece);
void tourner_n_fois(Piece* piece, int n);*/
