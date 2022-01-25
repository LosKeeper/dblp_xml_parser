#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>

#define STR_LEN_DEF 100000

typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

typedef struct data_t {
    int nbAuteurs;
    char *auteurs;
    char *titre;
} data_t;

typedef struct graphe_t {
    char **liste_auteurs;
    size_t nb_auteurs;
    char **liste_titres;
    size_t **liste_titres_auteurs;
    size_t *nb_titres_auteurs;
    size_t nb_titres;
    size_t **liste_sucesseurs;
    size_t *liste_nb_liens;
    size_t *hachage_auteurs[100000];
    size_t nb_auteurs_hache[100000];
} graphe_t;

typedef struct parser_info_t {
    void (*handleOpenTag)(char *, void *, data_t *);
    void (*handleCloseTag)(char *, void *, data_t *, graphe_t *, FILE *,
                           long int);
    void (*handleText)(char *, void *, data_t *);
    void *data;
} parser_info_t;

/**
 * @brief test if memory allocation for a pointer is good
 * @param pnt a pointer
 */
void testAlloc(void *pnt);

/**
 * @brief save a data_t struct into the file named file
 *
 * @param file the file to save the struct informations
 * @param data the struct to store the current article informations
 */
void printDataStrcut(FILE *file, data_t *data);

/**
 * @brief initialise a structure data_t type
 *
 * @param xmlData the struct to store the current article informations
 */
void initData(data_t *xmlData);

/**
 * @brief reset a structure data_t type
 *
 * @param xmlData the struct to store the current article informations
 */
void resetDataStruct(data_t *xmlData);

/**
 * @brief initialise a structure parser_info_t type and parser_context_t
 *
 * @param info the struct to store functions about parsing
 *
 * @param context the struct to store counters about parsing
 */
void initInfo(parser_info_t *info, parser_context_t *context);

/**
 * @brief initialise a structure graphe_t type
 *
 * @param graphe the struct to store the graphe informations
 */
void initGraphe(graphe_t *graphe);

#endif