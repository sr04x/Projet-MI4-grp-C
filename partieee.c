#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>  // sleep()
#include "piece.h"
#include "grille.h"
#include "score.h"
#include "timer.h"
#include "partieee.h"

void afficherJeu(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece) {
    afficherGrille(grille); // Affichage fidèle

    printf("\n🧩 Pièce générée : %c\n", piece->nom);
    afficher_piece(piece); // Afficher la pièce avant la sélection

    printf("\n🌀 Orientations possibles :\n");
    printf("0️⃣ : Aucun changement\n");
    printf("1️⃣ : Rotation 90° antihoraire\n");
    printf("2️⃣ : Rotation 180°\n");
    printf("3️⃣ : Rotation 270° antihoraire\n");// il faut qu'il affiche les pieces
}


void genererPieceAleatoire(Piece *piece) {
    // 1️⃣ Sélection aléatoire d'une pièce parmi les 7 disponibles
    const char* nomsPieces[] = {"I", "J", "L", "O", "S", "T", "Z"};
    int index = rand() % 7;
    piece->nom = nomsPieces[index][0];  // Définir le nom

    // 2️⃣ Construire le chemin du fichier
    char cheminFichier[64];
    snprintf(cheminFichier, sizeof(cheminFichier), "style_piece/%s_piece.txt", nomsPieces[index]);

    // 3️⃣ Lire le fichier correspondant
    FILE *fichier = fopen(cheminFichier, "r");
    if (!fichier) {
        printf("❌ Erreur : Impossible de lire le fichier %s\n", cheminFichier);
        return;
    }

    // 4️⃣ Stocker la forme dans la structure
    char ligne[64];
    for (int i = 0; i < TAILLE_PIECE; i++) {
        fgets(ligne, sizeof(ligne), fichier);

        // Nettoie le saut de ligne
        int len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Maintenant on découpe ligne en blocs de 4 octets (chaque emoji)
        for (int j = 0; j < TAILLE_PIECE; j++) {
            strncpy(piece->forme[i][j], &ligne[j * 4], 4);
            piece->forme[i][j][4] = '\0'; // ajoute le \0 manuellement
        }
    }

    fclose(fichier);

    printf("✅ Pièce générée : %c\n", piece->nom);
}

/// Vérifie si la pièce `p` entre en collision avec la grille à la position `(x, y)`
int collision(char grille[NB_LIGNES][NB_COLONNES][5], Piece *p, int x, int y) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (strcmp(p->forme[i][j], FOND) != 0) {
                int gx = x + j;
                int gy = y + i;
                if (gx < 0 || gx >= NB_COLONNES || gy >= NB_LIGNES)
                    return 1;
                if (gy<0)
                    continue;
                if (strcmp(grille[gy][gx], FOND) != 0)
                    return 1;
            }
        }
    }
    return 0;
}


int choisirColonne() {
    int colonne = choisir_colonne_avec_timer(10); // Sélection avec timer
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
                int gx = x + j;
                int gy = y + i;

                if (gy >= 0 && gy < NB_LIGNES && gx >= 0 && gx < NB_COLONNES) {
                    strcpy(grille[gy][gx], p->forme[i][j]);
                }
            }
        }
    }
}

void placer(char grille[NB_LIGNES][NB_COLONNES][5], Piece *piece, int colonne, int orientation) {
    // 1️⃣ Appliquer la rotation choisie
    if (orientation > 0) {
        *piece = rotation_piece_multiple(piece, orientation);
    }

    // 2️⃣ Trouver la ligne la plus basse disponible dans la colonne
    int ligne = NB_LIGNES - 1;
    while (ligne >= 0 && strcmp(grille[ligne][colonne], FOND) != 0) {
        ligne--; // On cherche la première ligne libre
    }

    if (ligne < 0) {
        printf("❌ Impossible de placer la pièce ici ! Game Over imminent...\n");
        return; // La colonne est pleine, la pièce ne peut pas être placée
    }

    // 3️⃣ Vérifier la collision avant de placer
    if (collision(grille, piece, ligne, colonne)) {
        printf("❌ Collision détectée ! Placement annulé.\n");
        return;
    }

    // 4️⃣ Insérer la pièce
    placer_bloquant(grille, piece, ligne, colonne);
    printf("✅ Pièce placée en colonne %c !\n", 'A' + colonne);

    // 5️⃣ Vérifier les lignes complètes après placement
    int lignesSupprimees = supprimerLignesCompletes(grille);
    if (lignesSupprimees > 0) {
        printf("🔥 %d lignes supprimées !\n", lignesSupprimees);
    }
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
void boucleDeJeu() {
    char grille[NB_LIGNES][NB_COLONNES][5];
    initialiserGrille(grille);
    int gameOver = 0;

    while (!gameOver) {
        // 1️⃣ Affichage de la grille et de la pièce
        Piece piece;
        genererPieceAleatoire(&piece);
        afficherJeu(grille, &piece);

        // 2️⃣ Sélection de la colonne et de l’orientation
        int colonne = choisirColonne();
        int orientation = choisirOrientation();

        // 3️⃣ Placement de la pièce
        placer(grille, &piece, colonne, orientation);

        // 4️⃣ Vérification du Game Over
        gameOver = verifierGameOver(grille);
    }

    printf("\n💀 Fin de la partie ! Merci d'avoir joué.\n");
}

void jouerTetris() {
    char grille[NB_LIGNES][NB_COLONNES][5];
    initialiserGrille(grille);
    
    int score = 0;
    int gameOver = 0;

    while (!gameOver) {
        // 1️⃣ Générer une nouvelle pièce
        Piece piece;
        genererPieceAleatoire(&piece);

        // 2️⃣ Afficher la grille et la pièce
        afficherJeu(grille, &piece);

        // 3️⃣ Sélection du joueur
        int colonne = choisirColonne();
        int orientation = choisirOrientation();

        // 4️⃣ Placement sécurisé de la pièce
        placer(grille, &piece, colonne, orientation);
        
        // 5️⃣ Vérification du Game Over
        if (verifierGameOver(grille)){
            gameOver = 1;
            continue;
        }

        // 6️⃣ Gestion des lignes complètes
        score += supprimerLignesCompletes(grille) * 100;

    }

    // 🎮 Fin de partie : affichage du score
    printf("\n💀 GAME OVER ! Score final : %d\n", score);
    sauvegarderScore("Joueur", score);

    // 🔄 Proposition de rejouer
    char choix;
    printf("\nVoulez-vous rejouer ? (O/N) : ");
    scanf(" %c", &choix);
    while (getchar() != '\n'); // permet entre autre de reinitialiser le timer
    if (choix == 'O' || choix == 'o') {
        jouerTetris(); // Redémarrer une nouvelle partie
    }
}

/// Affiche le menu principal et gère les choix
void afficherMenuPrincipal(void) {
    int choix;
    do {
        printf("\n=== TETRIS ===\n");
        printf("1. Nouvelle partie\n2. Voir scores\n3. Quitter\nVotre choix : ");

        if (scanf("%d", &choix) != 1) choix = 3;
        while (getchar() != '\n');  // Nettoyage du buffer

        switch (choix) {
            case 1: jouerTetris(); break;
            case 2: afficherScores(); break;
            case 3: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 3);
}

/// Lance une nouvelle partie
void nouvellePartie() {
    boucleDeJeu();
}