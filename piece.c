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
        fgets(piece->forme[i], max_taille, fichier);

        // Supprimer le '\n' final
        int len = strlen(piece->forme[i]);
        if (len > 0 && piece->forme[i][len - 1] == '\n') {
            piece->forme[i][len - 1] = '\0';
        }
    }

    fclose(fichier);
}

void tourner_piece(Piece* piece){
 char nouvelle_forme[taille_piece][taille_piece * 4 + 1];
 for (int i = 0; i < taille_piece; i++) {
  nouvelle_forme[i][0] = '\0';
  for (int j = taille_piece - 1; j >= 0; j--){
    char bloc[5] = {0}; // 4 + '\0'
if ((i * 4 + 3) < strlen(piece->forme[j])) {
    strncpy(bloc, &piece->forme[j][i * 4], 4);
}
strncat(nouvelle_forme[i], bloc, 4);
  }
}
}
