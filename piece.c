//piece.c
#include <string.h>
#include "piece.h"

void lire_piece(char* nom_fichier, Piece* piece) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    piece->nom = fgetc(fichier);
    fgetc(fichier); // Lire le saut de ligne

    for (int i = 0; i < taille_piece; i++) {
        fgets(piece->forme[i], 32 , fichier);

        // Supprimer le '\n' final
        int len = strlen(piece->forme[i]);
        if (len > 0 && piece->forme[i][len - 1] == '\n') {
            piece->forme[i][len - 1] = '\0';
        }
    }

    fclose(fichier);
}

void tourner_piece(Piece* piece) {
 char tmp[taille_piece][taille_piece * max_octets_par_case];

    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            // Copie 4 octets (emoji) ou 1 octet (.)
            char* src = &piece->forme[taille_piece - 1 - j][i * 4];
            strncpy(&tmp[i][j * 4], src, 4);
            tmp[i][j * 4 + 4] = '\0';  // null-terminate
        }
    }

    for (int i = 0; i < taille_piece; i++) {
        strncpy(piece->forme[i], tmp[i], sizeof(piece->forme[i]));
    }
}

void tourner_n_fois(Piece* piece, int n) {
    int rotations = n % 4;
    for (int i = 0; i < rotations; i++) {
        tourner_piece(piece);
    }
}