#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille_piece 5
#define taille_nom 50


typedef struct {
    char nom;
    char forme[taille_piece][taille_piece * 4 + 1]; // 4 octets max par caractère (emoji)
} Piece;

void lire_piece(char* nom_fichier, Piece* piece);
void tourner_piece(Piece* piece);

