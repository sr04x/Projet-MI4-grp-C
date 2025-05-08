//main_test_piece.c

#include <stdio.h>
#include "piece.h"

void afficher_piece(Piece* piece) {
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            printf("%s", piece->forme[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotation_90_anti_horaire(Piece* piece, Piece* resultat) {
    resultat->nom = piece->nom;
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            strcpy(resultat->forme[taille_piece - 1 - j][i], piece->forme[i][j]);
        }
    }
}

int main() {
    Piece p, r;
    lire_piece("style_piece/I_piece.txt", &p);

    printf("=== Pièce d'origine ===\n");
    afficher_piece(&p);

    for (int i = 1; i <= 3; i++) {
        Piece rot = rotation_piece_multiple(&p, i);
        printf("=== Rotation %d * 90° antihoraire ===\n", i);
        afficher_piece(&rot);
    }

    return 0;
}

/*int main() {
    Piece p,r ;
    lire_piece("style_piece/L_piece.txt", &p);

    printf("=== Pièce d'origine ===\n");
    afficher_piece(&p);

    Piece p_rot;
    rotation_90_anti_horaire(&p, &p_rot);

    printf("=== Pièce après rotation antihoraire ===\n");
    afficher_piece(&p_rot);

return 0;
}*/

/*for (int i = 1; i <= 3; i++) {
    printf("\nRotation %d° :\n", i * 90);
    tourner_n_fois(&p, 1);
    afficher_piece(&p);
}*/

/*#include <stdio.h>
#include "piece.h"

void afficher_piece(Piece* p){
    printf("Nom de la pièce : %c\n", p->nom);
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            printf("%s", p->forme[i][j]);
        }
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
}*/