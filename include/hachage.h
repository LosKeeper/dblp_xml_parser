#ifndef HACHAGE_H
#define HACHAGE_H
#include "struct.h"
#include <stdio.h>

/**
 * @brief Hache a string into a number modulo 100 000
 *
 * @param chaine a string to hache

 * @return a number modulo 100 000 that correspond to the string
 */
unsigned int hache(char *chaine);

/**
 * @brief Index all the autors from liste_auteurs into the hache table in graphe
 *
 * @param liste_auteurs all the currents autors name from the current aticle
 * @param nb_auteurs the number of autors to index
 * @param graphe the graphe structure to store graphe informations
 * @param liste_index_auteurs the list to return the index of the current autors
 */
void indexation_auteur(char **liste_auteurs, size_t nb_auteurs,
                       graphe_t *graphe, int *liste_index_auteurs);

#endif