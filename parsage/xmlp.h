#ifndef XMLP_HEADER
#define XMLP_HEADER

typedef enum parser_error_type_t {
    PARSER_OK,
    ERROR_UNABLE_TO_OPEN_FILE,
    ERROR_UNEXPECTED_END_OF_TAG
} parser_error_type_t;

typedef struct parser_info_t {
    void (*handleOpenTag)(char*, void*);
    void (*handleCloseTag)(char*, void*);
    void (*handleText)(char*, void*);
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
parser_error_type_t parse(const char *filename, parser_info_t *info);

#endif