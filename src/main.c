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
    char saisie[100];  // Buffer pour lire la saisie de l'utilisateur sous forme de chaîne

    do {
        // Affiche une question claire et explicite à l'utilisateur
        printf("Avec combien de pièces voulez-vous jouer ? (entre 3 et 7) : ");
    
        // Lit une ligne entière au clavier (sécurisé contre les débordements de buffer)
        if (!fgets(saisie, sizeof(saisie), stdin)) {
            // Si fgets échoue (ex. fin de fichier), on arrête le programme proprement
            fprintf(stderr, "Erreur de lecture.\n");
            exit(1);
        }
    
        // Analyse la chaîne : sscanf extrait un entier dans nb_pieces si possible
        // Si la saisie n’est pas un nombre, ou si elle est hors intervalle, on affiche une erreur
        if (sscanf(saisie, "%d", &nb_pieces) != 1 || nb_pieces < 3 || nb_pieces > 7) {
            printf("Entrée invalide. Veuillez saisir un nombre entre 3 et 7.\n");
        }
    }while(nb_pieces<3 || nb_pieces>7);  // On recommence tant que l’entrée n’est pas valide
    afficherMenuPrincipal(nb_pieces);
    return 0;
}

