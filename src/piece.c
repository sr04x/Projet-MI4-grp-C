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

void afficherToutesLesOrientations(Piece *piece) {
    printf("\nVoici les orientations possibles :\n\n");

    // Pour chaque ligne (0 à 4) à afficher
    for (int ligne = 0; ligne < TAILLE_PIECE; ligne++) {

        // Pour chaque orientation de 0 à 3
        for (int ori = 0; ori < 4; ori++) {

            // On génère la pièce temporaire dans l'orientation courante
            Piece temp = rotation_piece_multiple(piece, ori);

            printf("  "); // Petite marge avant chaque bloc de pièce

            // On affiche la ligne `ligne` de cette orientation
            for (int col = 0; col < TAILLE_PIECE; col++) {
                printf("%s", temp.forme[ligne][col]);
            }

            printf("   "); // Espace entre chaque orientation
        }

        // Une fois les 4 orientations affichées côte à côte sur la ligne, on passe à la suivante
        printf("\n");
    }

    // Saut de ligne pour séparer visuellement
    printf("\n");

    // Affichage des indices 0 à 3 en-dessous, bien alignés
    for (int ori = 0; ori < 4; ori++) {
        printf("    %d         ", ori); // alignement visuel
    }

    printf("\n\n"); // Finition propre
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