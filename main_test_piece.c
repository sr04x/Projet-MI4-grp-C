#include <stdio.h>
#include "pieces.h"
#include "piece.c"

void afficher_piece(Piece* p) {
    printf("Nom de la pièce : %s\n", p->nom);
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            printf("%c", p->forme[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Piece p;
    lire_piece("style_piece/L_piece.txt", &p);
    afficher_piece(&p);
    return 0;
}
