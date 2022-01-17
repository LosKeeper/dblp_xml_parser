#ifndef XMLP_HEADER
#define XMLP_HEADER

#define STR_LEN_DEF 10000
#include <stdio.h>
typedef enum parser_error_type_t {
    PARSER_OK,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG
} parser_error_type_t;

typedef struct donnees {
    int nbAuteurs;
    char *auteurs;
    char *titre;
} donnees;

typedef struct graphe_type {
    char **liste_auteurs;
    int nb_auteurs;
    char **liste_titres;
    int nb_titres;
    size_t **liste_sucesseurs;
    size_t *liste_nb_liens;
    size_t *hachage_auteurs[500];
    size_t nb_auteurs_hache[500];
} graphe_type;

typedef struct parser_info_t {
    void (*handleOpenTag)(char *, void *, donnees *, graphe_type *);
    void (*handleCloseTag)(char *, void *, donnees *, graphe_type *, FILE *,
                           long int);
    void (*handleText)(char *, void *, donnees *, graphe_type *);
    void *data;
} parser_info_t;

/**
 * @brief Open and parse the file pointed by filename
 *
 * @param filename the name of the file to parse
 * @param info the info containing the handler functions
 *
 * @return PARSER_OK if everything went fine, an error otherwise
 */
parser_error_type_t parse(const char *filename, parser_info_t *info,
                          donnees *xmlData, graphe_type *graphe);

#endif