
#include <string.h>
#include "piece.h"

void lire_piece(const char* nom_fichier, Piece* piece) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
    return;
    }

piece->nom = fgetc(fichier);
fgetc(fichier); // saut de ligne

for (int i = 0; i < TAILLE_PIECE; i++) {
    fgets(piece->forme[i], TAILLE_PIECE * 4 + 1, fichier);
    size_t len = strlen(piece->forme[i]);
    if (len > 0 && piece->forme[i][len - 1] == '\n') {
        piece->forme[i][len - 1] = '\0';
    }                                                                                                     fclose(fichier);
}

void tourner_piece(Piece* piece){
 char nouvelle_forme[TAILLE_PIECE][TAILLE_PIECE * 4 + 1];
 for (int i = 0; i < TAILLE_PIECE; i++) {
  nouvelle_forme[i][0] = '\0';
  for (int j = TAILLE_PIECE - 1; j >= 0; j--){
     char bloc[5];
     strncpy(bloc, &piece->forme[j][i * 4], 4);
     bloc[4] = '\0';
     strncat(nouvelle_forme[i], bloc, 4);
  }
}

for (int i = 0; i < TAILLE_PIECE; i++) {
 strcpy(piece->forme[i], nouvelle_forme[i]);
}
}
