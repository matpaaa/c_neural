#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include "csv.h"
#include "reseau.h"

/*
 * Auteur : James
 * calculer_mse : erreur quadratique moyenne du reseau sur un jeu de donnees.
 * Parametres : r (reseau), data (echantillons normalises), n (nombre d'echantillons)
 * Retour : MSE moyenne sur les n echantillons (0.0 si n <= 0)
 */
double calculer_mse(Reseau *r, Echantillon *data, int n);

/* Propagation avant : remplit r->h1, r->h2 et r->out a partir de entrees[N_IN] */
void propagation_avant(Reseau *r, double *entrees);

/* Retropropagation : met a jour poids et biais pour un echantillon (cible normalisee, taux eta) */
void retropropagation(Reseau *r, double *entrees, double cible, double eta);

#endif