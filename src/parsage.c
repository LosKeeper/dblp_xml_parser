#include "parsage.h"
#include "xmlp.h"

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

void printAvancement(FILE *entree, long int taille_fichier) {
    long int pos = ftell(entree);
    double ratio = (double)pos * 100 / (double)taille_fichier;
    pourc_new = (unsigned short)ratio;
    if (pourc_new > pourc_prev) {
        printf("%d%%\n", pourc_new);
    }
    pourc_prev = pourc_new;
}