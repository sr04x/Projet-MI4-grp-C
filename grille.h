#ifndef GRILLE_H
#define GRILLE_H

#define NB_LIGNES 10
#define NB_COLONNES 10

#define VIDE "."  // chaîne pour vide
#define FOND "🟦"  // fond de la grille

void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES][5]);
void afficherGrille(char grille[NB_LIGNES][NB_COLONNES][5]);
int supprimerLignesCompletes(char grille[NB_LIGNES][NB_COLONNES][5]);

#endif