#include <stdio.h>
#include "grille.h"
#include "piece.h"

int main() {
    char grille[NB_LIGNES][NB_COLONNES];
    
    initialiserGrille(grille);
    afficherGrille(grille);
    int nbLigneSuppr = supprimerLignesCompletes(grille);
    if (nbLigneSuppr > 0) {
        printf("%d ligne(s) supprimée(s) !\n", nbLigneSuppr);
    }
    return 0;
}
