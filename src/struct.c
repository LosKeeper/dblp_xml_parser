#include "struct.h"
#include "parsage.h"
#include <stdlib.h>
#include <string.h>

void initData(data_t *xmlData) {
    xmlData->auteurs = malloc(STR_LEN_DEF);
    xmlData->titre = malloc(STR_LEN_DEF);
    xmlData->auteurs[0] = '\0';
    xmlData->titre[0] = '\0';
    xmlData->nbAuteurs = 0;
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