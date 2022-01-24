#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "xmlp.h"

parser_error_type_t parse(const char *filename, parser_info_t *info,
                          data_t *xmlData, graphe_t *graphe) {
    FILE *entree = fopen(filename, "r");
    fseek(entree, 0, SEEK_END);
    long int taille_fichier = ftell(entree);
    fseek(entree, 0, SEEK_SET);
    if (entree == NULL) {
        return ERROR_UNABLE_TO_OPEN_FILE;
    }
    int CptOuvrant = 0;
    int CptFermant = 0;
    char carac_buffer = (char)fgetc(entree);
    char previous_carac;
    char *data = malloc(STR_LEN_DEF);
    while (carac_buffer != EOF) {
        if (carac_buffer == '<') {
            CptOuvrant++;
            previous_carac = carac_buffer;
            carac_buffer = (char)fgetc(entree);
            int it = 0;
            if (carac_buffer == '/' && previous_carac == '<') {
                previous_carac = carac_buffer;
                carac_buffer = (char)fgetc(entree);
                while (carac_buffer != '>') {
                    if (carac_buffer == EOF) {
                        if (CptOuvrant != CptFermant) {
                            // fprintf(stderr,
                            //         "Unexpected end of tag (missing '>')");
                            // free(data);
                            fclose(entree);
                            return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        fclose(entree);
                        free(data);
                        return PARSER_OK;
                    }
                    data[it] = carac_buffer;
                    previous_carac = carac_buffer;
                    carac_buffer = (char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                data[it] = '\0';
                info->handleCloseTag(data, info->data, xmlData, graphe, entree,
                                     taille_fichier);
            } else {
                while (carac_buffer != '>') {
                    if (carac_buffer == EOF) {
                        if (CptOuvrant != CptFermant) {
                            // fprintf(stderr,
                            //         "Unexpected end of tag (missing '>')");
                            fclose(entree);
                            // free(data);
                            return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        free(data);
                        fclose(entree);
                        return PARSER_OK;
                    }
                    if (carac_buffer == ' ') {
                        while (carac_buffer != '>') {
                            previous_carac = carac_buffer;
                            carac_buffer = (char)fgetc(entree);
                        }
                        previous_carac = carac_buffer;
                        carac_buffer = (char)fgetc(entree);
                        goto passe_fgetc;
                    }
                    data[it] = carac_buffer;
                    previous_carac = carac_buffer;
                    carac_buffer = (char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                data[it] = '\0';
                info->handleOpenTag(data, info->data, xmlData);
            }
        } else {
            int it = 0;
            while (carac_buffer != '<') {
                if (carac_buffer == EOF) {
                    if (CptOuvrant != CptFermant) {
                        // fprintf(stderr, "Unexpected end of tag (missing
                        // '>')"); free(data);
                        fclose(entree);
                        return ERROR_UNEXPECTED_END_OF_TAG;
                    }
                    free(data);
                    fclose(entree);
                    return PARSER_OK;
                }
                data[it] = carac_buffer;
                previous_carac = carac_buffer;
                carac_buffer = (char)fgetc(entree);
                it++;
            }
            data[it] = '\0';
            info->handleText(data, info->data, xmlData);
            goto passe_fgetc;
        }
        previous_carac = carac_buffer;
        carac_buffer = (char)fgetc(entree);
    passe_fgetc:;
    }
    free(data);
    fclose(entree);
    return PARSER_OK;
}