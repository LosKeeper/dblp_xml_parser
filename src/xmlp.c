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
    char *buffer = malloc(STR_LEN_DEF);
    testAlloc(buffer);
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
                            fprintf(stderr,
                                    "Unexpected end of tag (missing '>')1\n");
                            // free(buffer);
                            fclose(entree);
                            return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        fclose(entree);
                        // free(buffer);
                        return PARSER_OK;
                    }
                    buffer[it] = carac_buffer;
                    previous_carac = carac_buffer;
                    carac_buffer = (char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                buffer[it] = '\0';
                info->handleCloseTag(buffer, info->data, xmlData, graphe,
                                     entree, taille_fichier);
            } else {
                while (carac_buffer != '>') {
                    if (carac_buffer == EOF) {
                        if (CptOuvrant != CptFermant) {
                            fprintf(stderr,
                                    "Unexpected end of tag (missing '>')2\n");
                            fclose(entree);
                            // free(buffer);
                            return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        // free(buffer);
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
                    buffer[it] = carac_buffer;
                    previous_carac = carac_buffer;
                    carac_buffer = (char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                buffer[it] = '\0';
                info->handleOpenTag(buffer, info->data, xmlData);
            }
        } else {
            int it = 0;
            while (carac_buffer != '<') {
                if (carac_buffer == EOF) {
                    if (CptOuvrant != CptFermant) {
                        fprintf(stderr,
                                "Unexpected end of tag (missing'>')3\n");
                        // free(buffer);
                        fclose(entree);
                        return ERROR_UNEXPECTED_END_OF_TAG;
                    }
                    // free(buffer);
                    fclose(entree);
                    return PARSER_OK;
                }
                buffer[it] = carac_buffer;
                previous_carac = carac_buffer;
                carac_buffer = (char)fgetc(entree);
                it++;
            }
            buffer[it] = '\0';
            info->handleText(buffer, info->data, xmlData);
            goto passe_fgetc;
        }
        previous_carac = carac_buffer;
        carac_buffer = (char)fgetc(entree);
    passe_fgetc:;
    }
    // free(buffer);
    fclose(entree);
    return PARSER_OK;
}