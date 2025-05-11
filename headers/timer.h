//timer.h
#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

// Démarre le chronomètre
void demarrer_timer();

// Vérifie si le temps est dépassé
bool temps_depasse(int limite_secondes);

// Renvoie le temps écoulé
int temps_ecoule();

// Renvoie une colonne choisie par l'utilisateur ou aléatoire si dépassement de temps ou entrée invalide
int choisir_colonne_avec_timer(int temps_max);

// Génère une colonne aléatoire (indice 0–9)
int colonne_aleatoire();

#endif
