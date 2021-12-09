#ifndef XMLP_HEADER
#define XMLP_HEADER

#define STR_LEN_DEF 10001

typedef enum parser_error_type_t {
    PARSER_OK,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG
} parser_error_type_t;

typedef struct donnees {
  int nbAuteurs;
  char* auteurs;
  char* titre;
}donnees;

typedef struct parser_info_t {
    void (*handleOpenTag)(char*, void*, donnees*);
    void (*handleCloseTag)(char*, void*, donnees*);
    void (*handleText)(char*, void*, donnees*);
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
parser_error_type_t parse(const char *filename, parser_info_t *info, donnees *xmlData);

#endif