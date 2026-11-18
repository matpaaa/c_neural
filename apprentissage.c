/* Auteur : James - Role : propagation avant, retropropagation, calcul de la MSE */
#include "apprentissage.h"

double calculer_mse(Reseau *r, Echantillon *data, int n) {
    int k;
    double somme = 0.0, erreur;

    if (n <= 0) return 0.0;
    for (k = 0; k < n; k++) {
        propagation_avant(r, data[k].x);
        erreur = r->out[0] - data[k].y;
        somme += erreur * erreur;
    }
    return somme / n;
}

/* Propagation avant : calcule h1, h2 et out a partir des entrees (tableau de 5 valeurs normalisees) */
void propagation_avant(Reseau *r, double *entrees) {
    int i, j;

    /* Entrée (5) -> Cachée 1 (8) */
    for (j = 0; j < N_H1; j++) {
        r->h1[j] = r->b1[j];
        for (i = 0; i < N_IN; i++) {
            r->h1[j] += entrees[i] * r->W1[i][j];
        }
        r->h1[j] = activer(r->act, r->h1[j]);
    }

    /* Cachée 1 (8) -> Cachée 2 (4) */
    for (j = 0; j < N_H2; j++) {
        r->h2[j] = r->b2[j];
        for (i = 0; i < N_H1; i++) {
            r->h2[j] += r->h1[i] * r->W2[i][j];
        }
        r->h2[j] = activer(r->act, r->h2[j]);
    }

    /* Cachée 2 (4) -> Sortie (1) avec activation linéaire */
    for (j = 0; j < N_OUT; j++) {
        r->out[j] = r->b3[j];
        for (i = 0; i < N_H2; i++) {
            r->out[j] += r->h2[i] * r->W3[i][j];
        }
    }
}

/* Retropropagation : tous les deltas sont calcules avant de modifier les poids */
void retropropagation(Reseau *r, double *entrees, double cible, double eta) {
    int i, j;
    double d3[N_OUT];
    double d2[N_H2];
    double d1[N_H1];

    /* 1. Calcul de l'erreur sur la couche de sortie (activation linéaire) */
    for (j = 0; j < N_OUT; j++) {
        d3[j] = r->out[j] - cible;
    }

    /* 2. Calcul de l'erreur sur la couche cachée 2 (4 neurones) */
    for (j = 0; j < N_H2; j++) {
        double somme = 0.0;
        for (i = 0; i < N_OUT; i++) {
            somme += d3[i] * r->W3[j][i];
        }
        d2[j] = somme * derivee(r->act, r->h2[j]);
    }

    /* 3. Calcul de l'erreur sur la couche cachée 1 (8 neurones) */
    for (j = 0; j < N_H1; j++) {
        double somme = 0.0;
        for (i = 0; i < N_H2; i++) {
            somme += d2[i] * r->W2[j][i];
        }
        d1[j] = somme * derivee(r->act, r->h1[j]);
    }

    /* 4. Mise à jour des poids et biais (Cachée 2 -> Sortie) */
    for (i = 0; i < N_H2; i++) {
        for (j = 0; j < N_OUT; j++) {
            r->W3[i][j] -= eta * r->h2[i] * d3[j];
        }
    }
    for (j = 0; j < N_OUT; j++) r->b3[j] -= eta * d3[j];

    /* 5. Mise à jour des poids et biais (Cachée 1 -> Cachée 2) */
    for (i = 0; i < N_H1; i++) {
        for (j = 0; j < N_H2; j++) {
            r->W2[i][j] -= eta * r->h1[i] * d2[j];
        }
    }
    for (j = 0; j < N_H2; j++) r->b2[j] -= eta * d2[j];

    /* 6. Mise à jour des poids et biais (Entrée -> Cachée 1) */
    for (i = 0; i < N_IN; i++) {
        for (j = 0; j < N_H1; j++) {
            r->W1[i][j] -= eta * entrees[i] * d1[j];
        }
    }
    for (j = 0; j < N_H1; j++) r->b1[j] -= eta * d1[j];
}