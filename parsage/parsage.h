#ifndef PARSAGE_H
#define PARSAGE_H
#include "struct.h"

char lecture = 0;    // equal 1 if we have to read info between 2 tags
char tag_author = 0; // equal 1 if the current tag is a AUTHOR tag
char tag_title = 0;  // equal 1 if the current tag is a TITLE tag
/**
 * @brief Take info between 2 tags
 *
 * @param txt the string betwenn the 2 tags
 * @param data the struct that contains info about parsing and numbers of open
 * and close tags
 * @param xmlData the struct to store the current article informations
 * @param graphe the struct to store the graphe informations
 */
void handleText(char *txt, void *data, data_t *xmlData, graphe_t *graphe);

/**
 * @brief Detect an open tag
 *
 * @param tag the string that contain the tag name
 * @param data the struct that contains info about parsing and numbers of open
 * and close tags
 * @param xmlData the struct to store the current article informations
 * @param graphe the struct to store the graphe informations
 */
void handleOpenTag(char *tag, void *data, data_t *xmlData, graphe_t *graphe);

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

unsigned short pourc_prev = 0; // store the previous rate
unsigned short pourc_new = 0;  // store the next rate
/**
 * @brief Print the progress of the parsing of the file
 *
 * @param entree the file to parse
 * @param taille_fichier the number of bytes of the file to parse
 */
void printAvancement(FILE *entree, long int taille_fichier);

#endif