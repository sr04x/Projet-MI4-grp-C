#include <stdio.h>
#include "grille.h"
#include "piece.h"

int main() {
    char grille[NB_LIGNES][NB_COLONNES];
    
    initialiserGrille(grille);
    afficherGrille(grille);
    int nblignesuppr = supprimerLignesCompletes(grille);
    if (nblignesuppr > 0) {
        printf("%d ligne(s) supprimée(s) !\n", nblignesuppr);
    }
    return 0;
}
