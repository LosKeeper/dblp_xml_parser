#ifndef PARSAGE_H
#define PARSAGE_H
#include "struct.h"

/**
 * @brief Take info between 2 tags
 *
 * @param txt the string betwenn the 2 tags
 * @param data the struct that contains info about parsing and numbers of open
 * and close tags
 * @param xmlData the struct to store the current article informations
 */
void handleText(char *txt, void *data, data_t *xmlData);

/**
 * @brief Detect an open tag
 *
 * @param tag the string that contain the tag name
 * @param data the struct that contains info about parsing and numbers of open
 * and close tags
 * @param xmlData the struct to store the current article informations
 */
void handleOpenTag(char *tag, void *data, data_t *xmlData);

/**
 * @brief Detect a close tag
 *
 * @param tag the string that contain the tag name
 * @param data the struct that contains info about parsing and numbers of open
 * and close tags
 * @param xmlData the struct to store the current article informations
 * @param graphe the struct to store the graphe informations
 * @param entree the file to parse
 * @param taille_fichier the number of bytes of the file to parse
 */
void handleCloseTag(char *tag, void *data, data_t *xmlData, graphe_t *graphe,
                    FILE *entree, long int taille_fichier);

/**
 * @brief Decode html caracteres like &ouml; into o
 *
 * @param encoded_str the string to decode
 */
void decode_html(char *encoded_str);

/**
 * @brief Print the progress of the parsing of the file
 *
 * @param entree the file to parse
 * @param taille_fichier the number of bytes of the file to parse
 */
void printAvancement(FILE *entree, long int taille_fichier);

#endif