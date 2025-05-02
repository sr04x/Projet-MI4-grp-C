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
    score += nbLigneSuppr * 100; //100 points par ligne supprime

    char nom[NOM_MAX];
    printf("Entrez votre nom :");
    scanf("%s", nom); //ajouter securiter scanf

    ajouterScore(nom,score);
    afficherScore();
    
    return 0;
}
