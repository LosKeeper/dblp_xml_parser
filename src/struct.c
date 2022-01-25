#include <stdlib.h>
#include <string.h>

#include "parsage.h"
#include "struct.h"

void testAlloc(void *pnt) {
    if (!pnt) {
        fprintf(stderr, "Memory Allocation Error\n");
        exit(1);
    }
}

void initData(data_t *xmlData) {
    xmlData->auteurs = malloc(STR_LEN_DEF);
    testAlloc(xmlData->auteurs);
    xmlData->titre = malloc(STR_LEN_DEF);
    testAlloc(xmlData->titre);
    xmlData->auteurs[0] = '\0';
    xmlData->titre[0] = '\0';
    xmlData->nbAuteurs = 0;
}

void resetDataStruct(data_t *xmlData) {
    free(xmlData->auteurs);
    free(xmlData->titre);
    xmlData->nbAuteurs = 0;
    xmlData->auteurs = malloc(STR_LEN_DEF);
    testAlloc(xmlData->auteurs);
    xmlData->auteurs[0] = '\0';
    xmlData->titre = malloc(STR_LEN_DEF);
    testAlloc(xmlData->titre);
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
    testAlloc(graphe->liste_auteurs);
    graphe->liste_titres = malloc(sizeof(char *) * STR_LEN_DEF);
    testAlloc(graphe->liste_titres);
    graphe->nb_auteurs = 0;
    graphe->nb_titres = 0;
    graphe->liste_sucesseurs = malloc(sizeof(size_t *) * STR_LEN_DEF);
    testAlloc(graphe->liste_sucesseurs);
    graphe->liste_nb_liens = malloc(sizeof(size_t) * STR_LEN_DEF);
    testAlloc(graphe->liste_nb_liens);
    memset(graphe->nb_auteurs_hache, 0, sizeof(graphe->nb_auteurs_hache));
    for (size_t i = 0; i < 100000; i++) {
        graphe->hachage_auteurs[i] = malloc(sizeof(size_t));
        testAlloc(graphe->hachage_auteurs);
    }
}