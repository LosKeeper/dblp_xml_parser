#ifndef GRAPHE_H
#define GRAPHE_H
#include "struct.h"

/**
 * @brief Add the current arcticle info stored in data into graphe
 *
 * @param graphe the struct to store the graphe informations
 * @param data the struct to store the current article informations
 */
void addGraphe(graphe_t *graphe, data_t *data);

/**
 * @brief Save the graphe in the sortie file
 *
 * @param graphe the struct to store the graphe informations
 * @param sortie the file to save the graphe
 */
void printGraphe(graphe_t *graphe, FILE *sortie);

/**
 * @brief Import graphe from a file
 *
 * @param graphe the struct to store the graphe informations
 * @param entree the file to import the graphe
 */
void importGraphe(graphe_t *graphe, FILE *entree);
/**
 * @brief Print on stdout the name of the articles written by the author
 *
 * @param graphe the struct to store the graphe informations
 * @param author_name the name of the author
 */
void findTitleFromAutor(graphe_t *graphe, char *author_name);

#endif