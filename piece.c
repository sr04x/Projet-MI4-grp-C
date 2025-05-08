//piece.c
#include <string.h>
#include "piece.h"

/*void lire_piece(char* nom_fichier, Piece* piece) {
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
}*/

void lire_piece(char* nom_fichier, Piece* piece) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    piece->nom = fgetc(fichier);
    fgetc(fichier); // saut de ligne après le nom

    char ligne[64];
    for (int i = 0; i < taille_piece; i++) {
        fgets(ligne, sizeof(ligne), fichier);

        // Nettoie le saut de ligne
        int len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Maintenant on découpe ligne en blocs de 4 octets (chaque emoji)
        for (int j = 0; j < taille_piece; j++) {
            strncpy(piece->forme[i][j], &ligne[j * 4], 4);
            piece->forme[i][j][4] = '\0'; // ajoute le \0 manuellement
        }
    }

    fclose(fichier);
}

Piece rotation_piece( Piece* piece) {
    Piece result;

    // Initialiser toute la matrice de résultat à "."
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
            strcpy(result.forme[i][j], ".");
        }
    }

      // Conserver le bloc central tel quel
    strcpy(result.forme[2][2], piece->forme[2][2]);
    
    // Appliquer la rotation anti-horaire autour du centre (2,2)
    for (int i = 0; i < taille_piece; i++) {
        for (int j = 0; j < taille_piece; j++) {
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