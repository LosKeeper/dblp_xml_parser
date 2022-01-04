/* NOTES

Ne pas oublier de retirer les "Home Page"
Ajouter for dans for pour addGraphe pour plusieurs auteurs

*/
#include "xmlp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

typedef struct graphe_type {
    char **liste_auteurs;
    int nb_auteurs;
    char **liste_titres;
    int nb_titres;
    int **matrice_adj;
} graphe_type;

int lecture = 0;
int tag_author = 0;
int tag_title = 0;
int structInit = 0;

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

void decode_html(char *encoded_str) {
    char *pnt = strstr(encoded_str, "&");
    if (pnt) {
        pnt[0] = pnt[1];
        char *ptvirgule = strstr(encoded_str, ";");
        int n = strlen(pnt) - strlen(ptvirgule);
        for (size_t k = 1; k < strlen(pnt) - n; k++) {
            pnt[k] = ptvirgule[k];
        }
        pnt[strlen(pnt) - n] = '\0';
    }
}

void printBinaire(FILE *file, donnees *data) {
    fprintf(file, "%d;%s%s\n", data->nbAuteurs, data->auteurs, data->titre);
}

void addGraphe(graphe_type *graphe, donnees *data) {
    graphe->liste_titres =
        realloc(graphe->liste_titres, sizeof(char *) * graphe->nb_titres + 1);
    graphe->liste_titres[graphe->nb_titres] = data->titre;

    char *pnt = data->auteurs;
    char auteur1[100];
    strcpy(auteur1, pnt);
    strstr(auteur1, ";")[0] = '\0';
    pnt = strstr(pnt, ";");
    graphe->nb_auteurs++;

    int index_auteur1;
    int auteur_existe = 0;
    for (int k = 0; k < graphe->nb_auteurs; k++) {
        if (!strcmp(auteur1, graphe->liste_auteurs[k])) {
            auteur_existe = 1;
            index_auteur1 = k;
        }
    }
    if (!auteur_existe) {
        graphe->liste_auteurs =
            realloc(graphe->liste_auteurs, sizeof(char *) * graphe->nb_auteurs);
        graphe->liste_auteurs[graphe->nb_auteurs - 1] = auteur1;
        graphe->matrice_adj =
            realloc(graphe->matrice_adj, sizeof(int *) * (graphe->nb_auteurs));
        index_auteur1 = graphe->nb_auteurs - 1;
        graphe->matrice_adj[index_auteur1] =
            malloc(sizeof(int) * graphe->nb_auteurs);
        for (int i = 0; i < index_auteur1; i++) {
            graphe->matrice_adj[index_auteur1][i] = -1;
        }
    }

    for (int i = 1; i < data->nbAuteurs; i++) {

        // Détection des auteurs

        char auteur2[100];
        strcpy(auteur2, pnt);
        strstr(auteur2, ";")[0] = '\0';
        pnt = strstr(pnt, ";");
        graphe->nb_auteurs++;

        // Recherche si l'auteur existe deja

        int index_auteur2;
        int auteur_existe = 0;
        for (int k = 0; k < graphe->nb_auteurs; k++) {
            if (!strcmp(auteur2, graphe->liste_auteurs[k])) {
                auteur_existe = 1;
                index_auteur2 = k;
            }
        }
        if (!auteur_existe) {
            graphe->liste_auteurs = realloc(
                graphe->liste_auteurs, sizeof(char *) * graphe->nb_auteurs);
            graphe->liste_auteurs[graphe->nb_auteurs - 1] = auteur2;
            graphe->matrice_adj = realloc(graphe->matrice_adj,
                                          sizeof(int *) * (graphe->nb_auteurs));
            index_auteur2 = graphe->nb_auteurs - 1;
            graphe->matrice_adj[index_auteur2] =
                malloc(sizeof(int) * graphe->nb_auteurs);
            for (int i = 0; i < index_auteur2; i++) {
                graphe->matrice_adj[index_auteur2][i] = -1;
            }
        }
        graphe->matrice_adj[max(index_auteur1, index_auteur2)]
                           [min(index_auteur1, index_auteur1)] =
            graphe->nb_titres;
        index_auteur1 = index_auteur2;
        strcpy(auteur1, auteur2);
    }
    graphe->nb_titres++;
}

void initStruct(donnees *xmlData) {
    free(xmlData->auteurs);
    free(xmlData->titre);
    xmlData->nbAuteurs = 0;
    xmlData->auteurs = malloc(STR_LEN_DEF);
    xmlData->auteurs[0] = '\0';
    xmlData->titre = malloc(STR_LEN_DEF);
    xmlData->titre[0] = '\0';
}

void handleText(char *txt, void *data, donnees *xmlData) {
    parser_context_t *context = data;
    if (lecture) {
        context->text_count++;
        if (tag_title) {
            strcat(xmlData->titre, txt);
        } else if (tag_author) {
            decode_html(txt);
            strcat(xmlData->auteurs, strcat(txt, ";"));
        }
    }
}

void handleOpenTag(char *tag, void *data, donnees *xmlData) {
    parser_context_t *context = data;
    if (!strcmp(tag, "author") || (!strcmp(tag, "title") && tag_author)) {
        context->open_count++;
        lecture = 1;
        if (!strcmp(tag, "author")) {
            tag_author = 1;
            xmlData->nbAuteurs++;
        } else {
            tag_title = 1;
        }
    }
}

void handleCloseTag(char *tag, void *data, donnees *xmlData) {
    parser_context_t *context = data;
    if (!strcmp(tag, "author") || (!strcmp(tag, "title"))) {
        context->close_count++;
        lecture = 0;
        if (!strcmp(tag, "title")) {
            tag_author = 0;
            tag_title = 0;
            if (xmlData->nbAuteurs) {
                printBinaire(stdout, xmlData);
            }
            initStruct(xmlData);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 2;

    parser_context_t context = {};

    donnees xmlData;
    xmlData.auteurs = malloc(STR_LEN_DEF);
    xmlData.titre = malloc(STR_LEN_DEF);
    xmlData.auteurs[0] = '\0';
    xmlData.titre[0] = '\0';
    xmlData.nbAuteurs = 0;

    parser_info_t info;
    info.handleOpenTag = handleOpenTag;
    info.handleCloseTag = handleCloseTag;
    info.handleText = handleText;
    info.data = &context;

    int err;
    if (PARSER_OK != (err = parse(argv[1], &info, &xmlData))) {
        return err;
    }
    return 0;
}
