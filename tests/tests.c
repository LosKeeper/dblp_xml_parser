/* NOTES

|Ne pas oublier de retirer les "Home Page"
|Ajouter for dans for pour addGraphe pour plusieurs auteurs
|Finir table de hachege en ajoutant les nouveaux index au tableau
|Fichier Binaire
Tester tous les malloc et realloc
    https://coderedirect.com/questions/523992/valgrind-address-is-0-bytes-after-a-block-of-size-8-allocd
Seg Fault decode_html

*/
#include "graphe.h"
#include "hachage.h"
#include "parsage.h"
#include "struct.h"
#include "xmlp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short hache(char *chaine) {
    unsigned int a = 9887;
    unsigned int b = 49919;
    unsigned int h = 0;
    for (int k = 0; k < strlen(chaine); k++) {
        h += (unsigned int)(a * chaine[k] + b);
    }
    return (unsigned int)h % 100000;
}

void printAvancement(FILE *entree, long int taille_fichier) {
    long int pos = ftell(entree);
    double ratio = (double)pos * 100 / (double)taille_fichier;
    pourc_new = (unsigned short)ratio;
    if (pourc_new > pourc_prev) {
        printf("%d%%\n", pourc_new);
    }
    pourc_prev = pourc_new;
}

void indexation_auteur(char **liste_auteurs, size_t nb_auteurs,
                       graphe_t *graphe, int *liste_index_auteurs) {
    for (size_t k = 0; k < nb_auteurs; k++) {
        unsigned int h = hache(liste_auteurs[k]);
        if (graphe->nb_auteurs_hache[h] > 0) {
            for (size_t i = 0; i < graphe->nb_auteurs_hache[h] - 1; i++) {
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

        } else {
            graphe->hachage_auteurs[h] =
                realloc(graphe->hachage_auteurs[h],
                        (graphe->nb_auteurs_hache[h] + 1) * sizeof(size_t));
            graphe->hachage_auteurs[h][0] = graphe->nb_auteurs + k;
            graphe->nb_auteurs_hache[h]++;
            liste_index_auteurs[k] = -1;
        }
    pas_ajout:;
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

void printDataStrcut(FILE *file, data_t *data) {
    fprintf(file, "%d;%s%s\n", data->nbAuteurs, data->auteurs, data->titre);
}

void printGraphe(graphe_t *graphe, FILE *sortie) {
    fprintf(sortie, "%ld\n", graphe->nb_auteurs);
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        fprintf(sortie, "%ld;", graphe->liste_nb_liens[i]);
    }
    fprintf(sortie, "\n");
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        for (size_t j = 0; j < graphe->liste_nb_liens[i]; j++) {
            fprintf(sortie, "%ld|", graphe->liste_sucesseurs[i][j]);
        }
        fprintf(sortie, ";");
    }
    fprintf(sortie, "\n");
    for (int i = 0; i < graphe->nb_auteurs; i++) {
        fprintf(sortie, "%s;", graphe->liste_auteurs[i]);
    }
    fprintf(sortie, "\n");
    fprintf(sortie, "%ld\n", graphe->nb_titres);
    for (int i = 0; i < graphe->nb_titres; i++) {
        fprintf(sortie, "%s;", graphe->liste_titres[i]);
    }
    fprintf(sortie, "\n");
}

void importGraphe(graphe_t *graphe, FILE *entree) {

    char *buffer = malloc(STR_LEN_DEF);
    char carac_buffer = fgetc(entree);
    uint it = 0;

    // graphe->nb_auteurs
    while (carac_buffer != '\n') {
        buffer[it] = carac_buffer;
        carac_buffer = fgetc(entree);
        it++;
    }
    graphe->nb_auteurs = atoi(buffer);
    free(buffer);

    // graphe->liste_nb_liens
    graphe->liste_nb_liens =
        realloc(graphe->liste_nb_liens, sizeof(size_t) * graphe->nb_auteurs);
    graphe->liste_sucesseurs = realloc(graphe->liste_sucesseurs,
                                       sizeof(size_t *) * graphe->nb_auteurs);
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        char *buffer2 = malloc(STR_LEN_DEF);
        carac_buffer = fgetc(entree);
        it = 0;
        while (carac_buffer != ';') {
            buffer2[it] = carac_buffer;
            carac_buffer = fgetc(entree);
            it++;
        }
        it = 0;
        graphe->liste_nb_liens[i] = atoi(buffer2);
        graphe->liste_sucesseurs[i] =
            realloc(graphe->liste_sucesseurs[i],
                    sizeof(size_t) * graphe->liste_nb_liens[i]);
        free(buffer2);
    }

    // graphe->liste_successeurs
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        for (size_t j = 0; j < graphe->liste_nb_liens[i]; j++) {
            char *buffer3 = malloc(STR_LEN_DEF);
            carac_buffer = fgetc(entree);
            it = 0;
            while (carac_buffer != '|') {
                buffer3[it] = carac_buffer;
                carac_buffer = fgetc(entree);
                it++;
            }
            it = 0;
            graphe->liste_sucesseurs[i][j] = atoi(buffer3);
            free(buffer3);
        }
        carac_buffer = fgetc(entree);
    }
    carac_buffer = fgetc(entree);

    // graphe->liste_auteurs
    graphe->liste_auteurs =
        realloc(graphe->liste_auteurs, sizeof(char *) * graphe->nb_auteurs);
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        char *buffer6 = malloc(STR_LEN_DEF);
        carac_buffer = fgetc(entree);
        uint it = 0;
        while (carac_buffer != ';') {
            buffer6[it] = carac_buffer;
            carac_buffer = fgetc(entree);
            it++;
        }
        buffer6[it] = '\0';
        it = 0;
        graphe->liste_auteurs[i] = malloc(strlen(buffer6) + 1);
        strcpy(graphe->liste_auteurs[i], buffer6);
        free(buffer6);
    }
    carac_buffer = fgetc(entree);

    // graphe->nb_titres
    char *buffer4 = malloc(STR_LEN_DEF);
    carac_buffer = fgetc(entree);
    it = 0;
    while (carac_buffer != '\n') {
        buffer4[it] = carac_buffer;
        carac_buffer = fgetc(entree);
        it++;
    }
    graphe->nb_titres = atoi(buffer4);
    free(buffer4);

    // graphe->liste_titres
    graphe->liste_titres =
        realloc(graphe->liste_titres, sizeof(char *) * graphe->nb_titres);
    for (size_t i = 0; i < graphe->nb_titres; i++) {
        char *buffer5 = malloc(STR_LEN_DEF);
        carac_buffer = fgetc(entree);
        uint it = 0;
        while (carac_buffer != ';') {
            buffer5[it] = carac_buffer;
            carac_buffer = fgetc(entree);
            it++;
        }
        buffer5[it] = '\0';
        it = 0;
        graphe->liste_titres[i] = malloc(strlen(buffer5) + 1);
        strcpy(graphe->liste_titres[i], buffer5);
        free(buffer5);
    }
}

void addGraphe(graphe_t *graphe, data_t *data) {

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
        size_t index_auteur1 = index_auteurs[i];
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
            size_t index_auteur2 = index_auteurs[j];
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

void resetDataStruct(data_t *xmlData) {
    free(xmlData->auteurs);
    free(xmlData->titre);
    xmlData->nbAuteurs = 0;
    xmlData->auteurs = malloc(STR_LEN_DEF);
    xmlData->auteurs[0] = '\0';
    xmlData->titre = malloc(STR_LEN_DEF);
    xmlData->titre[0] = '\0';
}

void handleText(char *txt, void *data, data_t *xmlData, graphe_t *graphe) {
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

void handleOpenTag(char *tag, void *data, data_t *xmlData, graphe_t *graphe) {
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

void handleCloseTag(char *tag, void *data, data_t *xmlData, graphe_t *graphe,
                    FILE *entree, long int taille_fichier) {
    parser_context_t *context = data;
    if (!strcmp(tag, "author") || (!strcmp(tag, "title"))) {
        context->close_count++;
        lecture = 0;
        if (!strcmp(tag, "title")) {
            tag_author = 0;
            tag_title = 0;
            if (xmlData->nbAuteurs && strcmp(xmlData->titre, "Home Page")) {
                addGraphe(graphe, xmlData);
                printAvancement(entree, taille_fichier);
            }
            resetDataStruct(xmlData);
        }
    }
}

void initData(data_t *xmlData) {
    xmlData->auteurs = malloc(STR_LEN_DEF);
    xmlData->titre = malloc(STR_LEN_DEF);
    xmlData->auteurs[0] = '\0';
    xmlData->titre[0] = '\0';
    xmlData->nbAuteurs = 0;
}

void initInfo(parser_info_t *info, parser_context_t *context) {
    info->handleOpenTag = handleOpenTag;
    info->handleCloseTag = handleCloseTag;
    info->handleText = handleText;
    info->data = &context;
}

void initGraphe(graphe_t *graphe) {
    graphe->liste_auteurs = malloc(sizeof(char *) * STR_LEN_DEF);
    graphe->liste_titres = malloc(sizeof(char *) * STR_LEN_DEF);
    graphe->nb_auteurs = 0;
    graphe->nb_titres = 0;
    graphe->liste_sucesseurs = malloc(sizeof(int *) * STR_LEN_DEF);
    graphe->liste_nb_liens = malloc(sizeof(int) * STR_LEN_DEF);
    memset(graphe->nb_auteurs_hache, 0, sizeof(graphe->nb_auteurs_hache));
    for (int i = 0; i < 100000; i++) {
        graphe->hachage_auteurs[i] = malloc(sizeof(size_t));
    }
}

int main(int argc, char **argv) {
    if (argc != 3)
        return 2;

    graphe_t graphe;
    initGraphe(&graphe);

    data_t xmlData;
    initData(&xmlData);

    parser_context_t context = {};
    parser_info_t info;
    initInfo(&info, &context);

    FILE *sortie = fopen(argv[2], "w");

    parse(argv[1], &info, &xmlData, &graphe);
    // FILE *entree = fopen(argv[1], "r");
    // importGraphe(&graphe, entree);
    printGraphe(&graphe, sortie);
    return 0;
}
