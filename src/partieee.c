#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "score.h"
#include "piece.h"
#include "grille.h"
#include "timer.h"
#include "partieee.h"


void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void afficherJeu(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece) {
    afficherGrille(grille); // Affichage fidèle

    printf("\n🧩 Pièce générée : %c\n", piece->nom);
    afficher_piece(piece); // Afficher la pièce avant la sélection

    printf("\n🌀 Orientations possibles :\n");
    afficherToutesLesOrientations(piece);
}


void genererPieceAleatoire(Piece *piece, int nb_pieces) {
    // 1️⃣ Sélection aléatoire d'une pièce parmi les 7 disponibles
    const char* nomsPieces[] = {"I", "J", "L", "O", "S", "T", "Z"};
    int index = rand() % nb_pieces;
    piece->nom = nomsPieces[index][0];  // Définir le nom

    // 2️⃣ Construire le chemin du fichier
    char cheminFichier[64];
    snprintf(cheminFichier, sizeof(cheminFichier), "style_piece/%s_piece.txt", nomsPieces[index]);

    lire_piece(cheminFichier, piece);

    printf("✅ Pièce générée : %c\n", piece->nom);
}

/// Vérifie si la pièce `p` entre en collision avec la grille à la position `(x, y)` detecter à partir du moment ou ya piece 
int collision(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (strcmp(p->forme[i][j], FOND) != 0) { //si la case est différente du fond
                int gx = x + j -2;
                int gy = y + i -2;
                if (gx < 0 || gx >= NB_COLONNES || gy >= NB_LIGNES)// on arrive en haut de la grille??
                    return 1;
                if (gy<0)
                    continue;
                if (strcmp(grille[gy][gx], FOND ) != 0) //si case grille != fond, collision
                    return 2;
            }
        }
    }
    return 0;
}


int choisirColonne() { 
    int colonne = choisir_colonne_avec_timer(30); // Sélection avec timer
    do{
        // Validation stricte
        if (colonne==-1 || colonne < 0 || colonne >= NB_COLONNES) {
            printf("❌ Choix invalide ! Colonne aléatoire sélectionnée.\n");
            return colonne_aleatoire();
        }
    }while(colonne==-1 || colonne < 0 || colonne >= NB_COLONNES);

    printf("✅ Colonne sélectionnée : %c\n", 'A' + colonne);
    return colonne;
}

int choisirOrientation() {
    int input;
    printf("🌀 Choisissez l’orientation (0–3) : ");
    
    demarrer_timer();
    scanf(" %d", &input);
    viderBuffer();

    if (temps_depasse(10)) {
        printf("⏱️ Temps dépassé ! Orientation aléatoire.\n");
        return rand() % 4;
    }

    // Vérification
    if (input < 0 || input > 3) {
        printf("❌ Orientation invalide. Choix aléatoire.\n");
        return rand() % 4;
    }

    return input;
}

void placer_bloquant(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int y, int x) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (strcmp(p->forme[i][j], FOND) != 0) {
                int gx = x + j-2;
                int gy = y + i-2;

                if (gy >= 0 && gy < NB_LIGNES && gx >= 0 && gx < NB_COLONNES) {
                    strcpy(grille[gy][gx], p->forme[i][j]);
                }
            }
        }
    }
}


int ligneDeChute(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x) {
    int y = 0;
    while (y < NB_LIGNES && collision(grille, p, x, y) == 0) {
        y++;
    }
    return y - 1;  // on retourne la dernière position valide
}

int placer(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece, int colonne, int orientation) {
  

    // Étape 1 : descente automatique
    int ligne = 0;
    while (ligne + 1 < NB_LIGNES && collision(grille, piece, colonne, ligne + 1)!=1) {
        ligne++; // ligne=9                   //erreur avec collision
    }

    // Étape 2 : vérifier si on a atteint le haut de la grille
    if (ligne==0 && collision(grille, piece, colonne, ligne) && verifierGameOver(grille)) {
        printf("Erreur: La piece est bloqué en haut. Arret immediat de la partie. ");
        return 0;
    }
    ligne = ligneDeChute(grille, piece, colonne);

    // Étape 3 : placement réel de la pièce
    placer_bloquant(grille, piece, ligne, colonne);
    printf("✅ Pièce placée en colonne %c !\n", colonne + 'A');

    // 5️⃣ Vérifier les lignes complètes après placement
    int lignesSupprimees = supprimerLignesCompletes(grille);
    if (lignesSupprimees > 0) {
        printf("🔥 %d ligne(s) supprimée(s) !\n", lignesSupprimees);
    }
    return lignesSupprimees;
}

int verifierGameOver(char grille[NB_LIGNES][NB_COLONNES][5]) {
    for (int j = 0; j < NB_COLONNES; j++) {
        if (strcmp(grille[0][j], FOND) != 0) { // Si une pièce atteint le haut
            printf("\n💀 GAME OVER ! Une pièce bloque la grille.\n");
            return 1;
        }
    }
    return 0;
}


void jouerTetris(int nb_pieces) {
    char grille[NB_LIGNES][NB_COLONNES][5];
    initialiserGrille(grille);
    
    int score = 0;
    int gameOver = 0;

    while (!gameOver) {
        // 1️⃣ Générer une nouvelle pièce
        Piece piece;
        genererPieceAleatoire(&piece, nb_pieces);
        

        // 2️⃣ Afficher la grille, la pièce et ses orientations
        afficherJeu(grille, &piece);

        // 3️⃣ Sélection du joueur
        int colonne = choisirColonne();
        int orientation = choisirOrientation();

          // Appliquer la rotation
        if (orientation > 0) {
            piece = rotation_piece_multiple(&piece, orientation);
    }
        
        // Vérification de débordement horizontal
        int depasse = 0;
        for (int i = 0; i < TAILLE_PIECE && !depasse; i++) {
            for (int j = 0; j < TAILLE_PIECE; j++) {
                if (strcmp(piece.forme[i][j], FOND) != 0) {
                    int gx = colonne + j - TAILLE_PIECE/2; 
                    if (gx < 0 || gx >= NB_COLONNES) {
                        depasse = 1;
                        break;
                    }
                }
            }
        }

        if (depasse) {
            printf("❌ Erreur : la pièce déborde horizontalement. Veuillez choisir une autre colonne.\n");
            continue; 
        }

        

        // 4️⃣ Placement sécurisé de la pièce
        int lignesSupprimees = placer(grille, &piece, colonne, orientation);
        score += lignesSupprimees * 100;
        printf("DEBUG : %d ligne(s) supprimée(s), score = %d\n", lignesSupprimees, score);

        // 5️⃣ Vérification du Game Over
        if (verifierGameOver(grille)){
            gameOver = 1;
            continue;
        }

    }

    // 🎮 Fin de partie : saisie du nom et sauvegarde du score
    Score s;
    printf("Entrez votre nom : ");
    fgets(s.nom, NOM_MAX, stdin);
    s.nom[strcspn(s.nom, "\n")] = '\0';  // Enlève le \n final
    s.score = score;
    printf("SCORE FINAL : %d", s.score);
    sauvegarderScore(s);

    // 🔄 Proposition de rejouer
    char choix;
    printf("\nVoulez-vous rejouer ? (O/N) : ");
    scanf(" %c", &choix);
    viderBuffer(); // permet entre autre de reinitialiser le timer
    if (choix == 'O' || choix == 'o') {
        jouerTetris(); // Redémarrer une nouvelle partie
    }
    else if (choix == 'N' || choix == 'n') {
        afficherMenuPrincipal(); // 
    }
}

/// Affiche le menu principal et gère les choix
void afficherMenuPrincipal(int nb_pieces) {
    int choix;
    int resultat;
    do {
        printf("\n=== TETRIS ===\n");
        printf("1. Nouvelle partie\n2. Voir scores\n3. Quitter\nVotre choix : ");
        
        resultat = scanf("%d", &choix);
        viderBuffer();
    
        if (resultat != 1) {
            printf("Choix invalide. Veuillez entrer un chiffre entre 1 et 3.\n");
            choix = 0; // valeur par défaut
        }
    
        switch (choix) {
            case 1: jouerTetris(nb_pieces); break;
            case 2: afficherMeilleursScores(5); break;
            case 3: 
                FILE*f = fopen(FICHIERS_SCORES, "w");
                if (f != NULL) fclose(f);
                printf("Au revoir !\n"); 
                break;
            default: printf("Choix invalide.\n");
        }
    
    } while (choix != 3);
    return;
}

