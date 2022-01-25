#ifndef ARGUMENTS_H
#define ARGUMENTS_H

typedef struct options_t {
    char *input_database;
    char *input_binary;
    char *output_binary;
    char *auteur;
    char *auteur1;
    char *auteur2;
} options_t;

/**
 * @brief Print how to use the arguments of the prgm
 **/
void print_usage(void);

/**
 * @brief Reset a option_t structure
 * @param option an option_t structure used to stored arguments of the prgm
 **/
void cleanOptions(options_t *options);

/**
 * @brief Init a option_t structure
 * @param options an option_t structure used to stored arguments of the prgm
 **/
void initOptions(options_t *options);

/**
 * @brief Check the validity of the option_t structure and run the specifics
 *commands
 * @param options an option_t structure used to stored arguments of the prgm
 **/
void checkOptionsValidity(options_t *options);

/**
 * @brief This function take arguments of the prgm
 * @param argc the numbers of arguments of the prgm
 * @param argv strings of the arguments
 * @param options an option_t structure used to stored arguments of the prgm
 **/
void parseArgs(int argc, char **argv, options_t *options);

#endif