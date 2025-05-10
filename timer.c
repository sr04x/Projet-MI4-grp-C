//timer.c

#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

static time_t debut;

void demarrer_timer() {
    debut = time(NULL);
}

bool temps_depasse(int limite_secondes) {
    return (time(NULL) - debut) > limite_secondes;
}

int temps_ecoule() {
    return (int)(time(NULL) - debut);
}

int colonne_aleatoire() {
    return rand() % 10; // 0 à 9 correspondant à A–J
}

int choisir_colonne_avec_timer(int temps_max) {
    char input[16];
    printf("Choisissez une colonne (A–J), vous avez %d secondes : ", temps_max);
    
    demarrer_timer();
    fgets(input, sizeof(input), stdin);

    if (temps_depasse(temps_max)) {
        printf("⏱️ Temps dépassé ! Choix aléatoire forcé.\n");
        return colonne_aleatoire();
    }

    // Vérification de validité
    if (strlen(input) == 0) {
        printf("❌ Entrée vide. Choix aléatoire.\n");
        return colonne_aleatoire();
    }

    char lettre = toupper(input[0]);
    if (lettre >= 'A' && lettre <= 'J') {
        return lettre - 'A'; // colonne valide
    } else {
        printf("❌ Entrée invalide. Choix aléatoire.\n");
        return colonne_aleatoire();
    }
    return -1;
}