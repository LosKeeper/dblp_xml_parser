#include <string.h>

#include "graphe.h"
#include "parsage.h"
#include "struct.h"
#include "xmlp.h"

char lecture = 0;              // equal 1 if we have to read info between 2 tags
char tag_author = 0;           // equal 1 if the current tag is a AUTHOR tag
char tag_title = 0;            // equal 1 if the current tag is a TITLE tag
unsigned short pourc_prev = 0; // store the previous rate
unsigned short pourc_new = 0;  // store the next rate

void handleText(char *txt, void *data, data_t *xmlData) {
    parser_context_t *context = data;
    if (lecture) {
        context->text_count++;
        if (tag_title) {
            strcat(xmlData->titre, txt);
        } else if (tag_author) {
            decode_html(txt);
            strcat(xmlData->auteurs, txt);
            strcat(xmlData->auteurs, ";");
        }
    }
}

void handleOpenTag(char *tag, void *data, data_t *xmlData) {
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
    if (pnt == NULL) {
        return;
    }
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