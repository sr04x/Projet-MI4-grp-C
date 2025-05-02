#include <stdio.h>
//#include <stlib.h> // pas besoin pour l'instant peut etre plus tard pour trier score (qsort)
#include <string.h> //pour manipuler chaine de caractere (strcmp() trie score par nom)
#include score.h


void ajouterScores(const char *nom,int score){ //ajout du nom et score dans un fichier
    FILE *f = fopen(FICHIER_SCORES,"a");
    if (f = NULL){
        perror("Erreur lors de l'ouverture du ficher score")
    }
    fprintf(f,"%s %d \n", nom, score);
    fclose(f);
}

void afficherScores(){
    FILE *f = fopen(FICHIER_SCORES,"r");
    if (f = NULL){
        perror("Erreur lors de l'ouverture du ficher score");
        printf("ou aucun score enregistré pour l'instant\n");
    }
    char nom[NOM_MAX];
    int score;
    printf("\n ----- HIGH SCORES -----\n");
    while(fscanf(f,"%s %d",nom, &score)==2){
        printf("%s : %d\n",nom, score);
    }
    fclose(f);
}
