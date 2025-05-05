//main_test_piece.c
#include <stdio.h>
#include "piece.h"

int main() {
    Piece p;
    char* nom_fichier= "style_piece/L_piece.txt";
    lire_piece(nom_fichier, &p);

    printf("Nom de la pièce : %c\n", p.nom);
    for (int i = 0; i < taille_piece; i++) {
        printf("%s\n", p.forme[i]);
    }
    return 0;
}
