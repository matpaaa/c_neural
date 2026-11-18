#ifndef RESEAU_H
#define RESEAU_H

#define N_IN 5
#define N_H1 8
#define N_H2 4
#define N_OUT 1

/* Fonction d'activation des couches cachees */
typedef enum { ACT_RELU, ACT_SIGMOIDE } Activation;

typedef struct {
    /* Matrices d'adjacence (poids) et biais */
    double W1[N_IN][N_H1];
    double b1[N_H1];
    
    double W2[N_H1][N_H2];
    double b2[N_H2];
    
    double W3[N_H2][N_OUT];
    double b3[N_OUT];
    
    /* Mémorisation des activations pour la rétropropagation */
    double h1[N_H1];
    double h2[N_H2];
    double out[N_OUT];

    Activation act; /* activation choisie pour les couches cachees */
} Reseau;

void initialiser_reseau(Reseau *r, Activation act);
double activer(Activation act, double x);
double derivee(Activation act, double a); /* a = valeur deja activee */

#endif