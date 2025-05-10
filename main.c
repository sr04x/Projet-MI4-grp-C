#include <stdio.h>
#include <string.h>
#include <time.h>
#include "score.h"
#include "partie.h"
#include "grille.h"
#include "piece.h"

int main(void) {
    srand(time(NULL));
    afficherMenuPrincipal();
    return 0;
}

/*int main() {
    char nom[NOM_MAX];
    int score = 0;  // Score initialisé à 0

    //Saisie sécurisée du nom 
    printf("Entrez votre nom : ");
    if (fgets(nom, NOM_MAX, stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture du nom.\n");
        return 1;
    }
    //Nettoie le '\n' à la fin de la ligne si présent
    nom[strcspn(nom, "\n")] = '\0';

    printf("\nBienvenue %s! Prépare-toi à jouer à Tech-tris!\n\n", nom);
    
    //Initialisation et affichage de la grille
    char grille[NB_LIGNES][NB_COLONNES][5];
    initialiserGrille(grille);
    afficherGrille(grille);

    //Simulation de suppression de lignes et score(exemple)
    int nblignesuppr = 2; //Supposons que 2 lignes ont été supprimées
    score += nblignesuppr * 100;
    
    // ------------code mit de cote pour exemple ----------------
    //int nbLigneSuppr = supprimerLignesCompletes(grille);
    //if (nbLigneSuppr > 0) {
       // printf("%d ligne(s) supprimée(s) !\n", nbLigneSuppr);
    //}
    //score += nbLigneSuppr * 100; //100 points par ligne supprime

    //ici plus tard la boucle principale du jeu avec les pièces etc

    //Affichage et sauvegarde du score
    printf("\nPartie terminée ! Score final : %d\n", score);
    sauvegarderScore(nom, score);  //Enregistre le score dans scores.txt
    afficherScores();               //Affiche les scores du fichier
    return 0;
}*/
