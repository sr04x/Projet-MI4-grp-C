#include "piece.h"

void lire_piece(char* nom_fichier,Piece* piece){
  FILE* fichier= fopen ("style_piece.txt","r"); // r = read
  if (fichier==NULL){ //test ouverture du fichier
    printf("erreur dans la lecture du fichier\n");
  return 0;
  }

//lecture du nom de la pièce
fget(piece->nom,taille_nom, fichier);

for(int i=0; i<taille_piece,i++){
  if (fget(piece->forme,taille_piece, fichier)!=NULL){
  //lecture de la ligne i du fichier texte + verif
   for(int j=0, j<taille_piece,j++){ //associe chaque          caractère du fichier à une colonne du tab de la struc
      Piece->forme[i][j]= Piece->forme[j];
   }
  }else{
    printf("erreur dans la lecture de la ligne %d\n",i);
    fclose(fichier);
    return 0;
  }
}
fclose(fichier);
return 1;
}
