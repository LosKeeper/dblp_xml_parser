#include "xmlp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

parser_error_type_t parse(const char *filename, parser_info_t *info){
    FILE * entree=fopen(filename,"r");
    if(entree==NULL){
        return ERROR_UNABLE_TO_OPEN_FILE;
    }
    int CptOuvrant=0;
    int CptFermant=0;
    char carac_buffer=(char)fgetc(entree);
    char * data=malloc(1001);
    while(carac_buffer!=EOF){
        if(carac_buffer=='<'){
            CptOuvrant++;
            carac_buffer=(char)fgetc(entree);
            int it=0;
            if(carac_buffer=='/'){
                carac_buffer=(char)fgetc(entree);
                while(carac_buffer!='>'){
                    if(carac_buffer==EOF){
                                if(CptOuvrant != CptFermant){
                                    fprintf(stderr,"Unexpected end of tag (missing '>')");
                                free(data);
                                return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        free(data);
                        return PARSER_OK;
                    }
                    data[it]=carac_buffer;
                    carac_buffer=(char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                data[it]='\0';
                info->handleCloseTag(data,info->data);
            }
            else{
                while(carac_buffer!='>'){
                    if(carac_buffer==EOF){
                                if(CptOuvrant != CptFermant){
                                    fprintf(stderr,"Unexpected end of tag (missing '>')");
                                free(data);
                                return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        free(data);
                        return PARSER_OK;
                    }
                    if(carac_buffer==' '){
                        while(carac_buffer!='>'){
                            carac_buffer=(char)fgetc(entree);
                        }
                        carac_buffer=(char)fgetc(entree);
                        goto passe_fgetc;
                    }
                    data[it]=carac_buffer;
                    carac_buffer=(char)fgetc(entree);
                    it++;
                }
                CptFermant++;
                data[it]='\0';
                info->handleOpenTag(data,info->data);
            }
        }
        else {
            int it=0;
            while(carac_buffer!='<'){
                if(carac_buffer==EOF){
                                if(CptOuvrant != CptFermant){
                                    fprintf(stderr,"Unexpected end of tag (missing '>')");
                                    free(data);
                                return ERROR_UNEXPECTED_END_OF_TAG;
                        }
                        free(data);
                        return PARSER_OK;
                    }
                data[it]=carac_buffer;
                carac_buffer=(char)fgetc(entree);
                it++;
            }
            data[it]='\0';
            info->handleText(data,info->data);
            goto passe_fgetc;
        }
        carac_buffer=(char)fgetc(entree);
        passe_fgetc:;
    }
    free(data);
    return PARSER_OK;
}