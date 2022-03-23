#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "struct.h"

void chemin(int **tableau_dijkstra, int numero_auteur_deux, int cout_chemin);

void comparer_auteurs(char *auteur1, char *auteur2);

void existence_auteur(int numero_auteur_un, int numero_auteur_deux);

void existence_coecriture(int numero_auteur_un, int numero_auteur_deux,
                          graphe_t graphe);

void existence_lien_direct(int numero_auteur_un, int numero_auteur_deux,
                           graphe_t graphe);

void dijkstra(char *auteur1, char *auteur2, graphe_t *graphe);

#endif