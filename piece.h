#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille_piece 5
#define taille_nom 50

typedef struct{ //structure d'une pièce Tetris
char nom [taille_nom];
char forme  [taille_piece][taille_piece];
}Piece; 

