#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

typedef struct options_t {
    char *input_database;
    char *input_binary;
    char *output_binary;
    char *auteur1;
    char *auteur2;
} options_t;

void print_usage(void) {
    printf(
        "usage: ./fichier OPTIONS\n"
        "options:\n"
        "\t-h                      affiche l'aide\n"
        "\t-d  ARGUMENT            indique la base de donnée a ouvrir"
        "\t-i  ARGUMENT            indique le fichier binaire a ouvrir\n"
        "\t-o  ARGUMENT            indique le fichier binaire a sauvegarder\n"
        "\t-a  ARGUMENT            indique le premier auteur pour la recherche "
        "de chemin"
        "\t-b ARGUMENT            indique le second auteur pour la recherche "
        "de chemin"
        "Exemples:\n"
        "./fichier -d dblb.xml -o binaire \n"
        "./fichier -i binaire -a Dumond -b Metzger \n");
}

void cleanOptions(options_t *options) {
    if (options->input_database)
        fclose(options->input_database);
    if (options->input_binary)
        fclose(options->input_binary);
    if (options->output_binary)
        fclose(options->output_binary);
    free(options);
}

void initOptions(options_t *options) {
    options->input_database = NULL;
    options->input_binary = NULL;
    options->output_binary = NULL;
    options->auteur1 = NULL;
    options->auteur2 = NULL;
}

void checkOptionsValidity(options_t *options) {}

void parseArgs(int argc, char **argv, options_t *options) {

    initOptions(options);

    int c;
    while ((c = getopt(argc, argv, "hd:i:o:a:b:")) != -1) {
        switch (c) {
        case 'h':
            print_usage();
            abort();
            break;
        case 'd':
            options->input_database = optarg;
            break;
        case 'i':
            options->input_binary = optarg;
            break;
        case 'o':
            options->output_binary = optarg;
            break;
        case 'a':
            options->auteur1 = optarg;
            break;
        case 'b':
            options->auteur2 = optarg;
            break;
        case '?':
            if (optopt == 'd' || optopt == 'i' || optopt == 'o' ||
                optopt == 'a' || optopt == 'b') {
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                print_usage();
            } else if (isprint(optopt)) {
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                print_usage();
            } else {
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                print_usage();
            }
            abort();
        default:
            abort();
        }
    }

    checkOptionsValidity(options);
}