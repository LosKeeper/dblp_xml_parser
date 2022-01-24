#include <stdlib.h>
#include <string.h>

#include "graphe.h"
#include "hachage.h"

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
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        fprintf(sortie, "%s;", graphe->liste_auteurs[i]);
    }
    fprintf(sortie, "\n");
    fprintf(sortie, "%ld\n", graphe->nb_titres);
    for (size_t i = 0; i < graphe->nb_titres; i++) {
        fprintf(sortie, "%s;", graphe->liste_titres[i]);
    }
    fprintf(sortie, "\n");
}

void importGraphe(graphe_t *graphe, FILE *entree) {

    char *buffer = malloc(STR_LEN_DEF);
    testAlloc(buffer);
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
    testAlloc(graphe->liste_nb_liens);
    graphe->liste_sucesseurs = realloc(graphe->liste_sucesseurs,
                                       sizeof(size_t *) * graphe->nb_auteurs);
    testAlloc(graphe->liste_sucesseurs);
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        char *buffer2 = malloc(STR_LEN_DEF);
        testAlloc(buffer2);
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
        testAlloc(graphe->liste_sucesseurs[i]);
        free(buffer2);
    }

    // graphe->liste_successeurs
    for (size_t i = 0; i < graphe->nb_auteurs; i++) {
        for (size_t j = 0; j < graphe->liste_nb_liens[i]; j++) {
            char *buffer3 = malloc(STR_LEN_DEF);
            testAlloc(buffer3);
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
        testAlloc(buffer6);
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
        testAlloc(graphe->liste_auteurs[i]);
        strcpy(graphe->liste_auteurs[i], buffer6);
        free(buffer6);
    }
    carac_buffer = fgetc(entree);

    // graphe->nb_titres
    char *buffer4 = malloc(STR_LEN_DEF);
    testAlloc(buffer4);
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
    testAlloc(graphe->liste_titres);
    for (size_t i = 0; i < graphe->nb_titres; i++) {
        char *buffer5 = malloc(STR_LEN_DEF);
        testAlloc(buffer5);
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
        testAlloc(graphe->liste_titres[i]);
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
    testAlloc(graphe->liste_titres);
    graphe->liste_titres[graphe->nb_titres] = malloc(strlen(data->titre) + 1);
    testAlloc(graphe->liste_titres[graphe->nb_titres]);
    strcpy(graphe->liste_titres[graphe->nb_titres], data->titre);
    // graphe->liste_titres[graphe->nb_titres] = strdup(data->titre);

    // Création d'une liste des auteurs a traiter
    char **liste_auteurs_a_traiter = malloc(sizeof(char *) * data->nbAuteurs);
    char *pointeur = data->auteurs;
    for (int i = 0; i < data->nbAuteurs; i++) {
        char *buffer = malloc(strlen(pointeur) + 1);
        strcpy(buffer, pointeur);
        strstr(buffer, ";")[0] = '\0';
        liste_auteurs_a_traiter[i] = malloc(strlen(buffer) + 1);
        testAlloc(liste_auteurs_a_traiter[i]);
        for (size_t j = 0; j < strlen(buffer) + 1; j++) {
            liste_auteurs_a_traiter[i][j] = buffer[j];
        }
        free(buffer);
        pointeur = strstr(pointeur, ";") + 1;
    }

    int nb_auteurs_a_traiter = data->nbAuteurs;
    int *index_auteurs = malloc(sizeof(int) * nb_auteurs_a_traiter);
    testAlloc(index_auteurs);
    indexation_auteur(liste_auteurs_a_traiter, nb_auteurs_a_traiter, graphe,
                      index_auteurs);

    for (int i = 0; i < nb_auteurs_a_traiter - 1; i++) {
        int index_auteur1 = index_auteurs[i];
        if (index_auteur1 == -1) {
            graphe->liste_auteurs =
                realloc(graphe->liste_auteurs,
                        (graphe->nb_auteurs + 1) * sizeof(char *));
            testAlloc(graphe->liste_auteurs);
            graphe->liste_auteurs[graphe->nb_auteurs] =
                malloc(strlen(liste_auteurs_a_traiter[i]) + 1);
            testAlloc(graphe->liste_auteurs[graphe->nb_auteurs]);
            strcpy(graphe->liste_auteurs[graphe->nb_auteurs],
                   liste_auteurs_a_traiter[i]);
            graphe->liste_sucesseurs =
                realloc(graphe->liste_sucesseurs,
                        (graphe->nb_auteurs + 1) * sizeof(size_t *));
            testAlloc(graphe->liste_sucesseurs);
            index_auteur1 = graphe->nb_auteurs;
            index_auteurs[i] = index_auteur1;
            graphe->liste_sucesseurs[index_auteur1] =
                malloc(2 * sizeof(size_t));
            testAlloc(graphe->liste_sucesseurs[index_auteur1]);
            graphe->liste_nb_liens =
                realloc(graphe->liste_nb_liens,
                        (graphe->nb_auteurs + 1) * sizeof(size_t));
            testAlloc(graphe->liste_nb_liens);
            graphe->liste_nb_liens[index_auteur1] = 0;
            graphe->nb_auteurs++;
        } else {
            graphe->liste_sucesseurs[index_auteur1] = realloc(
                graphe->liste_sucesseurs[index_auteur1],
                (graphe->liste_nb_liens[index_auteur1] + 1) * sizeof(size_t));
            testAlloc(graphe->liste_sucesseurs[index_auteur1]);
        }
        for (int j = i + 1; j < nb_auteurs_a_traiter; j++) {
            int index_auteur2 = index_auteurs[j];
            if (index_auteur2 == -1) {
                graphe->liste_auteurs =
                    realloc(graphe->liste_auteurs,
                            (graphe->nb_auteurs + 1) * sizeof(char *));
                testAlloc(graphe->liste_auteurs);
                graphe->liste_auteurs[graphe->nb_auteurs] = malloc(
                    sizeof(char) * (strlen(liste_auteurs_a_traiter[j]) + 1));
                testAlloc(graphe->liste_auteurs[graphe->nb_auteurs]);
                strcpy(graphe->liste_auteurs[graphe->nb_auteurs],
                       liste_auteurs_a_traiter[j]);
                graphe->liste_sucesseurs =
                    realloc(graphe->liste_sucesseurs,
                            (graphe->nb_auteurs + 1) * sizeof(size_t *));
                testAlloc(graphe->liste_sucesseurs);
                index_auteur2 = graphe->nb_auteurs;
                index_auteurs[j] = index_auteur2;
                graphe->liste_sucesseurs[index_auteur2] =
                    malloc(2 * sizeof(size_t));
                testAlloc(graphe->liste_sucesseurs[index_auteur2]);
                graphe->liste_nb_liens =
                    realloc(graphe->liste_nb_liens,
                            (graphe->nb_auteurs + 1) * sizeof(size_t));
                testAlloc(graphe->liste_nb_liens);
                graphe->liste_nb_liens[index_auteur2] = 0;
                graphe->nb_auteurs++;
            } else {
                graphe->liste_sucesseurs[index_auteur2] =
                    realloc(graphe->liste_sucesseurs[index_auteur2],
                            (graphe->liste_nb_liens[index_auteur2] + 1) *
                                sizeof(size_t));
                testAlloc(graphe->liste_sucesseurs[index_auteur2]);
            }
            graphe->liste_sucesseurs[index_auteur1] = realloc(
                graphe->liste_sucesseurs[index_auteur1],
                (graphe->liste_nb_liens[index_auteur1] + 1) * sizeof(size_t));
            testAlloc(graphe->liste_sucesseurs[index_auteur1]);
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