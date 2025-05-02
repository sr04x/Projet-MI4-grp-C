#ifndef GRILLE_H
#define GRILLE_H

#define NB_LIGNES 10
#define NB_COLONNES 10

#define VIDE ' '
//#define BLOC '@'  // Utilisé pour les blocs affichés dans la grille à changer avec les nouvelles pièces

void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES]);
void afficherGrille(char grille[NB_LIGNES][NB_COLONNES]);
int supprimerLignesCompletes(char grille[NB_LIGNES][NB_COLONNES]);


#endif
