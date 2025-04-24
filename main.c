#include <stdio.h>
#include "grille.h"

int main() {
    char grille[NB_LIGNES][NB_COLONNES];
    
    initialiserGrille(grille);
    afficherGrille(grille);

    return 0;
}
