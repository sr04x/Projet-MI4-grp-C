#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "piece.h"
#include "grille.h"
#include "score.h"
#include "timer.h"
#include "partieee.h"


int main() {
    int nb_pieces;
    srand(time(NULL));
    printf("Combien de pièces avez-vous dessinées ?\n");
    scanf("%d", &nb_pieces);
    afficherMenuPrincipal(nb_pieces);
    return 0;
}

