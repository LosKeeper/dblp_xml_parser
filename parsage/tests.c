/* NOTES

|Ne pas oublier de retirer les "Home Page"
|Ajouter for dans for pour addGraphe pour plusieurs auteurs
~Finir table de hachege en ajoutant les nouveaux index au tableau
Fichier Binaire
Tester tous les malloc et realloc
    https://coderedirect.com/questions/523992/valgrind-address-is-0-bytes-after-a-block-of-size-8-allocd
Seg Fault decode_html

*/
#include "xmlp.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

char lecture = 0;
char tag_author = 0;
char tag_title = 0;
char structInit = 0;

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

unsigned short hache(char *chaine) {
    unsigned int a = 5;
    unsigned int b = 151;
    unsigned int h = 0;
    for (int k = 0; k < strlen(chaine); k++) {
        h += (unsigned short)(a * chaine[k] + b);
    }
    return (unsigned short)h % 1000;
}

void printAvancement(FILE *entree, long int taille_fichier) {
    long int pos = ftell(entree);
    double ratio = (double)pos * 100 / (double)taille_fichier;
    printf("%.2f%%\n", ratio);
}

void indexation_auteur(char **liste_auteurs, size_t nb_auteurs,
                       graphe_type *graphe, int *liste_index_auteurs) {
    for (size_t k = 0; k < nb_auteurs; k++) {
        unsigned short h = hache(liste_auteurs[k]);
        if (graphe->nb_auteurs_hache[h] > 0) {
            for (size_t i = 0; i < graphe->nb_auteurs_hache[h]; i++) {
                size_t index = graphe->hachage_auteurs[h][i];
                if (graphe->liste_auteurs[index]) {
                    if (!strcmp(liste_auteurs[k],
                                graphe->liste_auteurs[index])) {
                        liste_index_auteurs[k] = index;
                        goto pas_ajout;
                    }
                }
            }
            liste_index_auteurs[k] = -1;
            graphe->hachage_auteurs[h] =
                realloc(graphe->hachage_auteurs[h],
                        (graphe->nb_auteurs_hache[h] + 1) * sizeof(size_t));
            graphe->hachage_auteurs[h][graphe->nb_auteurs_hache[h]] =
                graphe->nb_auteurs + k;
            graphe->nb_auteurs_hache[h]++;

        pas_ajout:;
        } else {
            graphe->hachage_auteurs[h] =
                realloc(graphe->hachage_auteurs[h],
                        (graphe->nb_auteurs_hache[h] + 1) * sizeof(size_t));
            graphe->hachage_auteurs[h][0] = graphe->nb_auteurs + k;
            graphe->nb_auteurs_hache[h]++;
            liste_index_auteurs[k] = -1;
        }
    }
}

void decode_html(char *encoded_str) {
    char *pnt = strstr(encoded_str, "&");
    while (strstr(encoded_str, ";")) {
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
    printf("LISTE SUCC : \n");
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        for (size_t j = 0; j < graphe->liste_nb_liens[i]; j++) {
            printf("%ld|", graphe->liste_sucesseurs[i][j]);
        }
        printf(";");
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

    if (!data->auteurs) {
        goto no_add_graphe;
    }

    // decode_html(data->titre);
    graphe->liste_titres =
        realloc(graphe->liste_titres, sizeof(char *) * (graphe->nb_titres + 1));
    graphe->liste_titres[graphe->nb_titres] = malloc(strlen(data->titre) + 1);
    strcpy(graphe->liste_titres[graphe->nb_titres], data->titre);

    // Création d'une liste des auteurs a traiter
    char **liste_auteurs_a_traiter = malloc(sizeof(char *) * data->nbAuteurs);
    char *pointeur = data->auteurs;
    for (int i = 0; i < data->nbAuteurs; i++) {
        char *buffer = malloc(strlen(pointeur) + 1);
        strcpy(buffer, pointeur);
        strstr(buffer, ";")[0] = '\0';
        liste_auteurs_a_traiter[i] = malloc(strlen(buffer) + 1);
        for (int j = 0; j < strlen(buffer) + 1; j++) {
            liste_auteurs_a_traiter[i][j] = buffer[j];
        }
        free(buffer);
        pointeur = strstr(pointeur, ";") + 1;
    }

    int nb_auteurs_a_traiter = data->nbAuteurs;
    int *index_auteurs = malloc(sizeof(int) * nb_auteurs_a_traiter);
    indexation_auteur(liste_auteurs_a_traiter, nb_auteurs_a_traiter, graphe,
                      index_auteurs);

    for (int i = 0; i < nb_auteurs_a_traiter; i++) {
        int index_auteur1 = index_auteurs[i];
        if (index_auteur1 == -1) {
            graphe->liste_auteurs =
                realloc(graphe->liste_auteurs,
                        (graphe->nb_auteurs + 1) * sizeof(char *));
            graphe->liste_auteurs[graphe->nb_auteurs] =
                malloc(strlen(liste_auteurs_a_traiter[i]) + 1);
            strcpy(graphe->liste_auteurs[graphe->nb_auteurs],
                   liste_auteurs_a_traiter[i]);
            graphe->liste_sucesseurs =
                realloc(graphe->liste_sucesseurs,
                        (graphe->nb_auteurs + 1) * sizeof(size_t *));
            index_auteur1 = graphe->nb_auteurs;
            index_auteurs[i] = index_auteur1;
            graphe->liste_sucesseurs[index_auteur1] =
                malloc(2 * sizeof(size_t));
            graphe->liste_nb_liens =
                realloc(graphe->liste_nb_liens,
                        (graphe->nb_auteurs + 1) * sizeof(size_t));
            graphe->liste_nb_liens[index_auteur1] = 0;
            graphe->nb_auteurs++;
        } else {
            graphe->liste_sucesseurs[index_auteur1] = realloc(
                graphe->liste_sucesseurs[index_auteur1],
                (graphe->liste_nb_liens[index_auteur1] + 1) * sizeof(size_t));
        }
        for (int j = i + 1; j < nb_auteurs_a_traiter; j++) {
            int index_auteur2 = index_auteurs[j];
            if (index_auteur2 == -1) {
                graphe->liste_auteurs =
                    realloc(graphe->liste_auteurs,
                            (graphe->nb_auteurs + 1) * sizeof(char *));
                graphe->liste_auteurs[graphe->nb_auteurs] = malloc(
                    sizeof(char) * (strlen(liste_auteurs_a_traiter[j]) + 1));
                strcpy(graphe->liste_auteurs[graphe->nb_auteurs],
                       liste_auteurs_a_traiter[j]);
                graphe->liste_sucesseurs =
                    realloc(graphe->liste_sucesseurs,
                            (graphe->nb_auteurs + 1) * sizeof(size_t *));
                index_auteur2 = graphe->nb_auteurs;
                index_auteurs[j] = index_auteur2;
                graphe->liste_sucesseurs[index_auteur2] =
                    malloc(2 * sizeof(size_t));
                graphe->liste_nb_liens =
                    realloc(graphe->liste_nb_liens,
                            (graphe->nb_auteurs + 1) * sizeof(size_t));
                graphe->liste_nb_liens[index_auteur2] = 0;
                graphe->nb_auteurs++;
            } else {
                graphe->liste_sucesseurs[index_auteur2] =
                    realloc(graphe->liste_sucesseurs[index_auteur2],
                            (graphe->liste_nb_liens[index_auteur2] + 1) *
                                sizeof(size_t));
            }
            graphe->liste_sucesseurs[index_auteur1] = realloc(
                graphe->liste_sucesseurs[index_auteur1],
                (graphe->liste_nb_liens[index_auteur1] + 1) * sizeof(size_t));
            graphe->liste_sucesseurs[index_auteur1]
                                    [graphe->liste_nb_liens[index_auteur1]] =
                index_auteur2;
            graphe->liste_sucesseurs[index_auteur2]
                                    [graphe->liste_nb_liens[index_auteur2]] =
                index_auteur1;
            graphe->liste_nb_liens[index_auteur1]++;
            graphe->liste_nb_liens[index_auteur2]++;
        }
    }
    graphe->nb_titres++;
    free(liste_auteurs_a_traiter);
    free(index_auteurs);
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
                    graphe_type *graphe, FILE *entree,
                    long int taille_fichier) {
    parser_context_t *context = data;
    if (!strcmp(tag, "author") || (!strcmp(tag, "title"))) {
        context->close_count++;
        lecture = 0;
        if (!strcmp(tag, "title")) {
            tag_author = 0;
            tag_title = 0;
            if (xmlData->nbAuteurs && strcmp(xmlData->titre, "Home Page")) {
                addGraphe(graphe, xmlData);
                // printAvancement(entree, taille_fichier);
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
    graphe.liste_sucesseurs = malloc(sizeof(int *) * STR_LEN_DEF);
    graphe.liste_nb_liens = malloc(sizeof(int) * STR_LEN_DEF);
    memset(graphe.nb_auteurs_hache, 0, sizeof(graphe.nb_auteurs_hache));
    for (int i = 0; i < 1000; i++) {
        graphe.hachage_auteurs[i] = malloc(sizeof(size_t));
    }

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
