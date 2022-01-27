#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

#include "arguments.h"
#include "dijkstra.h"
#include "graphe.h"
#include "struct.h"
#include "xmlp.h"

void print_usage(void) {
    printf(
        "usage: ./dblp-parsing OPTIONS\n"
        "options:\n"
        "\t-h                      affiche l'aide\n"
        "\t-d  ARGUMENT            indique la base de donnée a ouvrir\n"
        "\t-i  ARGUMENT            indique le fichier binaire a ouvrir (si pas "
        "de bases de données renseignée)\n"
        "\t-o  ARGUMENT            indique le fichier binaire a sauvegarder "
        "(uniquement si une base de donnée a été renseignée)\n"
        "\t-t  ARGUMENT            indique l'auteur pour lequel on veut "
        "connaitre le titre de ses ouvrages\n"
        "\t-a  ARGUMENT            indique le premier auteur pour la recherche "
        "de chemin\n"
        "\t-b ARGUMENT             indique le second auteur pour la recherche "
        "de chemin"
        "Exemples:\n"
        "./dblp-parsing -d dblb.xml -o binaire \n"
        "./dblp-parsing -i binaire -a \"Dumond Thomas\" -b \"Metzger "
        "Benjamin\" \n");
}

void cleanOptions(options_t *options) {
    if (options->input_database)
        free(options->input_database);
    if (options->input_binary)
        free(options->input_binary);
    if (options->output_binary)
        free(options->output_binary);
    if (options->auteur)
        free(options->auteur);
    if (options->auteur2)
        free(options->auteur2);
    if (options->auteur1)
        free(options->auteur1);
    free(options);
}

void initOptions(options_t *options) {
    options->input_database = NULL;
    options->input_binary = NULL;
    options->output_binary = NULL;
    options->auteur = NULL;
    options->auteur1 = NULL;
    options->auteur2 = NULL;
}

void checkOptionsValidity(options_t *options) {
    if (options->input_database) {
        if (options->input_binary) {
            fprintf(stderr, "Too many options.\n");
            print_usage();
            abort();
        }
        if (options->output_binary) {
            graphe_t *graphe = malloc(sizeof(graphe_t));
            initGraphe(graphe);
            data_t *data = malloc(sizeof(data_t));
            initData(data);
            parser_info_t *info = malloc(sizeof(parser_info_t));
            parser_context_t context = {};
            initInfo(info, &context);
            parse(options->input_database, info, data, graphe);
            FILE *sortie = fopen(options->output_binary, "w");
            printGraphe(graphe, sortie);
        }
    }
    if (options->input_binary) {
        if (options->auteur) {
            graphe_t *graphe = malloc(sizeof(graphe_t));
            initGraphe(graphe);
            data_t *data = malloc(sizeof(data_t));
            initData(data);
            parser_info_t *info = malloc(sizeof(parser_info_t));
            parser_context_t context = {};
            initInfo(info, &context);
            FILE *entree = fopen(options->input_binary, "r");
            importGraphe(graphe, entree);
            findTitleFromAuthor(graphe, options->auteur);
        } else if (options->auteur1) {
            if (options->auteur2) {
                graphe_t *graphe = malloc(sizeof(graphe_t));
                initGraphe(graphe);
                data_t *data = malloc(sizeof(data_t));
                initData(data);
                parser_info_t *info = malloc(sizeof(parser_info_t));
                parser_context_t context = {};
                initInfo(info, &context);
                FILE *entree = fopen(options->input_binary, "r");
                importGraphe(graphe, entree);
                dijkstra(options->auteur1, options->auteur2, graphe);
            }
        }
    }
}

void parseArgs(int argc, char **argv, options_t *options) {

    initOptions(options);

    int c;
    while ((c = getopt(argc, argv, "hd:i:o:t:a:b:")) != -1) {
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
        case 't':
            options->auteur = optarg;
            break;
        case 'a':
            options->auteur1 = optarg;
            break;
        case 'b':
            options->auteur2 = optarg;
            break;
        case '?':
            if (optopt == 'd' || optopt == 'i' || optopt == 'o' ||
                optopt == 't' || optopt == 'a' || optopt == 'b') {
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