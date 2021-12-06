#include "xmlp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN_DEF 1000

typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

int lecture=0;
int tag_author=0;
int structInit=0;

void printBinaire(FILE* file,donnees * data){
  fprintf(file,"%d;%s%s\n",data->nbAuteurs,data->auteurs,data->titre);
}

void initStruct(donnees* xmlData){
  free(xmlData->auteurs);
  free(xmlData->titre);
  xmlData->nbAuteurs=0;
  xmlData->auteurs=malloc(STR_LEN_DEF);
  xmlData->auteurs[0]='\0';
  xmlData->titre=malloc(STR_LEN_DEF);
  xmlData->titre[0]='\0';
}

void handleText(char *txt, void *data, donnees *xmlData) {
  parser_context_t *context = data;
  if(lecture){
    context->text_count++;
    if(tag_author){
      strcat(xmlData->auteurs,strcat(txt,";"));
    }
    else {
      xmlData->titre=txt;
    }
  }
}

void handleOpenTag(char *tag, void *data, donnees *xmlData) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||(!strcmp(tag,"title")&&tag_author)){
    context->open_count++;
    lecture=1;
    if(!strcmp(tag,"author")){
      tag_author=1;
      xmlData->nbAuteurs++;
    }
  }
}

void handleCloseTag(char *tag, void *data, donnees *xmlData) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||(!strcmp(tag,"title")&&tag_author)){
    context->close_count++;
    lecture=0;
    if(!strcmp(tag,"title")){
      tag_author=0;
      printBinaire(stdout,xmlData);
      initStruct(xmlData);
    }
  }
}

int main(int argc, char **argv)
{
  if(argc != 2) return 2;

  parser_context_t context = {};
  

  donnees xmlData;
  xmlData.auteurs=malloc(STR_LEN_DEF);
  xmlData.titre=malloc(STR_LEN_DEF);
  xmlData.nbAuteurs=0;

  parser_info_t info;
  info.handleOpenTag = handleOpenTag;
  info.handleCloseTag = handleCloseTag;
  info.handleText = handleText;
  info.data = &context;

  int err;
  if(PARSER_OK != (err = parse(argv[1], &info, &xmlData)))
  {
    return err;
  }
  return 0;
}
