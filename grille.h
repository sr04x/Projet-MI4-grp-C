#ifndef GRILLE_H
#define GRILLE_H

#define NB_LIGNES 10
#define NB_COLONNES 10

#define VIDE "."  // chaîne pour vide
#define FOND "🟦"  // fond de la grille
#define BLOC0 "🔲"
#define BLOC1 "🟥"
#define BLOC2 "🟨"
#define BLOC3 "🟩"
#define BLOC4 "🟫"
#define BLOC5 "🟧"
#define BLOC6 "🟪"


void initialiserGrille(char grille[NB_LIGNES][NB_COLONNES][5]);
void afficherGrille(char grille[NB_LIGNES][NB_COLONNES][5]);
int supprimerLignesCompletes(char grille[NB_LIGNES][NB_COLONNES][5]);

#endif