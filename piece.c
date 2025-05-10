//piece.c
#include <string.h>
#include "piece.h"

void lire_piece(char* nom_fichier, Piece* piece) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    char ligne[64];
    for (int i = 0; i < TAILLE_PIECE; i++) {
        fgets(ligne, sizeof(ligne), fichier);

        // Nettoie le saut de ligne
        int len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Maintenant on découpe ligne en blocs de 4 octets (chaque emoji)
        for (int j = 0; j < TAILLE_PIECE; j++) {
            strncpy(piece->forme[i][j], &ligne[j * 4], 4);
            piece->forme[i][j][4] = '\0'; // ajoute le \0 manuellement
        }
    }

    fclose(fichier);
}

Piece rotation_piece( Piece* piece) {
    Piece result;

    // Initialiser toute la matrice de résultat à "."
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            strcpy(result.forme[i][j], ".");
        }
    }

      // Conserver le bloc central tel quel
    strcpy(result.forme[2][2], piece->forme[2][2]);
    
    // Appliquer la rotation anti-horaire autour du centre (2,2)
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if ((i != 2 || j != 2) && strcmp(piece->forme[i][j], ".") != 0) {
                int di = i - 2;
                int dj = j - 2;

                int ni = 2 + dj;
                int nj = 2 - di;

                strcpy(result.forme[ni][nj], piece->forme[i][j]);
            }
        }
    }


    return result;
}

Piece rotation_piece_multiple(Piece* piece, int nb_rotations) {
    Piece temp1 = *piece;
    Piece temp2;

    nb_rotations = (nb_rotations % 4 + 4) % 4; // normalise entre 0 et 3

    for (int i = 0; i < nb_rotations; i++) {
        temp2 = rotation_piece(&temp1);  // ta fonction existante de rotation 90° antihoraire
        temp1 = temp2;
    }

    return temp1;
}
void afficher_piece(Piece* piece) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            printf("%s", piece->forme[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*void tourner_n_fois(Piece* piece, int n) {
    int rotations = n % 4;
    for (int i = 0; i < rotations; i++) {
        rotation_piece(piece);
    }
}*/

/* void tourner_piece(Piece* piece) {
    char tmp[taille_piece][taille_piece][5];
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            strcpy(tmp[i][j], piece->forme[taille_piece - j - 1][i]);
        }
    }
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            strcpy(piece->forme[i][j], tmp[i][j]);
        }
    }
 }


void tourner_n_fois(Piece* piece, int n) {
    int rotations = n % 4;
    for (int i = 0; i < rotations; i++) {
        tourner_piece(piece);
    }
}*/