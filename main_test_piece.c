//main_test_piece.c
#include <stdio.h>
#include "piece.h"

void afficher_piece(Piece* p){
    printf("Nom de la pièce : %c\n", p->nom);
    for (int i = 0; i < taille_piece; i++) {
        printf("%s\n", p->forme[i]);
    }
}

int main() {
    Piece p;
    char* nom_fichier= "style_piece/L_piece.txt";
    lire_piece(nom_fichier, &p);
    afficher_piece(&p);

    for (int i = 1; i <= 3; i++) {
        printf("\nRotation %d° :\n", i * 90);
        tourner_n_fois(&p, 1);
        afficher_piece(&p);
    }

    return 0;
}