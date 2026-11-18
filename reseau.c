#include <stdlib.h>
#include <math.h>
#include "reseau.h"

/* Génère un nombre aléatoire entre min et max */
double rand_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void initialiser_reseau(Reseau *r, Activation act) {
    int i, j;
    double limite;

    r->act = act;

    /* Poids et biais : Entrée (5) -> Cachée 1 (8) */
    limite = sqrt(6.0 / N_IN);
    for (i = 0; i < N_IN; i++) {
        for (j = 0; j < N_H1; j++) {
            r->W1[i][j] = rand_double(-limite, limite);
        }
    }
    for (j = 0; j < N_H1; j++) r->b1[j] = 0.1;

    /* Poids et biais : Cachée 1 (8) -> Cachée 2 (4) */
    limite = sqrt(6.0 / N_H1);
    for (i = 0; i < N_H1; i++) {
        for (j = 0; j < N_H2; j++) {
            r->W2[i][j] = rand_double(-limite, limite);
        }
    }
    for (j = 0; j < N_H2; j++) r->b2[j] = 0.1;

    /* Poids et biais : Cachée 2 (4) -> Sortie (1) */
    limite = sqrt(6.0 / N_H2);
    for (i = 0; i < N_H2; i++) {
        for (j = 0; j < N_OUT; j++) {
            r->W3[i][j] = rand_double(-limite, limite);
        }
    }
    for (j = 0; j < N_OUT; j++) r->b3[j] = 0.0;
}

/* Fonction d'activation selon l'enum (ReLU ou sigmoide) */
double activer(Activation act, double x) {
    if (act == ACT_SIGMOIDE) return 1.0 / (1.0 + exp(-x));
    return x > 0 ? x : 0.0;
}

/* Derivee de l'activation, calculee a partir de la valeur deja activee a */
double derivee(Activation act, double a) {
    if (act == ACT_SIGMOIDE) return a * (1.0 - a);
    return a > 0 ? 1.0 : 0.0;
}