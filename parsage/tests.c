/* NOTES

|Ne pas oublier de retirer les "Home Page"
|Ajouter for dans for pour addGraphe pour plusieurs auteurs
~Regler codage html SUR LES TITRES !!!
~addGraphe matrice_adj avec valeurs bizarres qui fonctionne mais regarder
uniquement trig inférieur
Fichier Binaire Tester tous les malloc et realloc

QUESTIONS
Pourquoi valgrind OK et pas en mode normal ?
Possibilité de stocker au choix des shorts ou bien des int (les deux en m tps)
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
    if (strstr(encoded_str, ";")) {
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

void printGraphe(graphe_type *graphe) {
    printf("MATRICE : \n");
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        for (size_t j = 0; j <= i; j++) {
            printf("%d  |", graphe->matrice_adj[i][j]);
        }
        printf("\n");
    }
    printf("\nLISTE AUTEURS : ");
    for (int i = 0; i < graphe->nb_auteurs; i++) {
        printf("%s;", graphe->liste_auteurs[i]);
    }
    printf("\nLISTE TITRES : ");
    for (int i = 0; i < graphe->nb_titres; i++) {
        printf("%s;", graphe->liste_titres[i]);
    }
    printf("\n");
}

void addGraphe(graphe_type *graphe, donnees *data) {
    if (data->nbAuteurs <= 1) {
        goto no_add_graphe;
    }
    graphe->liste_titres =
        realloc(graphe->liste_titres, sizeof(char *) * (graphe->nb_titres + 1));
    graphe->liste_titres[graphe->nb_titres] = malloc(strlen(data->titre));
    strcpy(graphe->liste_titres[graphe->nb_titres], data->titre);

    // Création d'une liste des auteurs a traiter (verifier si pas d'auteur
    // alors erreur)
    char **liste_auteurs_a_traiter =
        malloc(sizeof(char *) * graphe->nb_auteurs);
    char *pointeur = data->auteurs;
    for (int i = 0; i < data->nbAuteurs; i++) {
        char *buffer = malloc(strlen(pointeur) + 1);
        strcpy(buffer, pointeur);
        strstr(buffer, ";")[0] = '\0';
        liste_auteurs_a_traiter[i] = malloc(strlen(buffer) + 1);
        for (int j = 0; j < strlen(buffer); j++) {
            liste_auteurs_a_traiter[i][j] = buffer[j];
        }
        liste_auteurs_a_traiter[i][strlen(buffer)] = '\0';
        free(buffer);
        pointeur = strstr(pointeur, ";") + 1;
    }
    int nb_auteurs_a_traiter = data->nbAuteurs;
    size_t index_auteur1;
    short auteur1_existe = 0;
    size_t index_auteur2;
    short auteur2_existe = 0;
    for (int i = 0; i < nb_auteurs_a_traiter; i++) {

        // Recherche si auteur 1 existe deja
        for (int k = 0; k < graphe->nb_auteurs; k++) {
            if (!strcmp(liste_auteurs_a_traiter[i], graphe->liste_auteurs[k])) {
                auteur1_existe = 1;
                index_auteur1 = k;
            }
        }
        if (!auteur1_existe) {
            graphe->liste_auteurs =
                realloc(graphe->liste_auteurs,
                        sizeof(char *) * (graphe->nb_auteurs + 1));
            graphe->liste_auteurs[graphe->nb_auteurs] =
                malloc(strlen(liste_auteurs_a_traiter[i]) + 1);
            graphe->liste_auteurs[graphe->nb_auteurs] =
                liste_auteurs_a_traiter[i];
            graphe->matrice_adj = realloc(
                graphe->matrice_adj, sizeof(int *) * (graphe->nb_auteurs + 1));
            index_auteur1 = graphe->nb_auteurs;
            graphe->matrice_adj[index_auteur1] =
                malloc(sizeof(int) * (graphe->nb_auteurs + 1));
            graphe->nb_auteurs++;
            for (int l = 0; l < graphe->nb_auteurs; l++) {
                graphe->matrice_adj[index_auteur1][l] = -1;
            }
        }
        for (int j = i + 1; j < nb_auteurs_a_traiter; j++) {

            // Recherche si auteur 2 existe deja
            for (int k = 0; k < graphe->nb_auteurs; k++) {
                if (!strcmp(liste_auteurs_a_traiter[j],
                            graphe->liste_auteurs[k])) {
                    auteur2_existe = 1;
                    index_auteur2 = k;
                }
            }
            if (!auteur2_existe) {
                graphe->liste_auteurs =
                    realloc(graphe->liste_auteurs,
                            sizeof(char *) * (graphe->nb_auteurs + 1));
                graphe->liste_auteurs[graphe->nb_auteurs] =
                    malloc(strlen(liste_auteurs_a_traiter[j]) + 1);
                graphe->liste_auteurs[graphe->nb_auteurs] =
                    liste_auteurs_a_traiter[j];
                graphe->matrice_adj =
                    realloc(graphe->matrice_adj,
                            sizeof(int *) * (graphe->nb_auteurs + 1));
                index_auteur2 = graphe->nb_auteurs;
                graphe->matrice_adj[index_auteur2] =
                    malloc(sizeof(int) * (graphe->nb_auteurs + 1));
                graphe->nb_auteurs++;
                for (int l = 0; l < graphe->nb_auteurs; l++) {
                    graphe->matrice_adj[index_auteur2][l] = -1;
                }
            }
            auteur2_existe = 0;
            graphe->matrice_adj[max(index_auteur1, index_auteur2)]
                               [min(index_auteur1, index_auteur2)] =
                graphe->nb_titres;
        }
        auteur1_existe = 0;
    }
    graphe->nb_titres++;
no_add_graphe:;
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

void handleText(char *txt, void *data, donnees *xmlData, graphe_type *graphe) {
    parser_context_t *context = data;
    if (lecture) {
        context->text_count++;
        if (tag_title) {
            // decode_html(txt);
            strcat(xmlData->titre, txt);
        } else if (tag_author) {
            decode_html(txt);
            strcat(xmlData->auteurs, strcat(txt, ";"));
        }
    }
}

void handleOpenTag(char *tag, void *data, donnees *xmlData,
                   graphe_type *graphe) {
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

void handleCloseTag(char *tag, void *data, donnees *xmlData,
                    graphe_type *graphe) {
    parser_context_t *context = data;
    if (!strcmp(tag, "author") || (!strcmp(tag, "title"))) {
        context->close_count++;
        lecture = 0;
        if (!strcmp(tag, "title")) {
            tag_author = 0;
            tag_title = 0;
            if (xmlData->nbAuteurs && strcmp(xmlData->titre, "Home Page")) {
                // printBinaire(stdout, xmlData);
                addGraphe(graphe, xmlData);
                printGraphe(graphe);
            }
            initStruct(xmlData);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 2;

    parser_context_t context = {};

    graphe_type graphe;
    graphe.liste_auteurs = malloc(sizeof(char *) * STR_LEN_DEF);
    graphe.liste_titres = malloc(sizeof(char *) * STR_LEN_DEF);
    graphe.nb_auteurs = 0;
    graphe.nb_titres = 0;
    graphe.matrice_adj = malloc(sizeof(int *) * STR_LEN_DEF);

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
    if (PARSER_OK != (err = parse(argv[1], &info, &xmlData, &graphe))) {
        printGraphe(&graphe);
        return err;
    }
    return 0;
}
