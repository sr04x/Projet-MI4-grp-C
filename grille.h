#ifndef GRILLE_H
#define GRILLE_H

#define NB_LIGNES 10
#define NB_COLONNES 10

#define VIDE ' '
#define BLOC '@'  // Utilisé pour les blocs affichés dans la grille

void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES]);
void afficherGrille(char grille[NB_LIGNES][NB_COLONNES]);

#endif
