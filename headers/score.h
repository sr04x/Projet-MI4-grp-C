#ifndef SCORE_H
#define SCORE_H
#define NOM_MAX 50
#define MAX_SCORES 100
#define FICHIERS_SCORES "scores.txt"

typedef struct {
    char nom[NOM_MAX];
    int score;
}Score; 

void afficherScores();
void sauvegarderScore(Score s);
void afficherMeilleursScores(int topN);



#endif
