#include "xmlp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

int lecture=0;
int tag_author=0;
int nbTitre=0;
int nbAuteur=0;

typedef struct donnees {
  int nbAuteurs;
  size_t longueurTitre;
  size_t longueurTot;
  char* auteurs;
  char* titre;
}donnees;

void strAdd(char* chaine, char* mot){
  size_t longueurChaine=strlen(chaine);
  size_t longueurMot=strlen(mot);
  size_t longueurTot=longueurChaine+longueurMot;
  chaine=realloc(chaine,longueurTot+1);
  chaine[longueurChaine]=';';
  for(size_t i=longueurChaine+1; i<longueurChaine+longueurMot; i++){
    chaine[i]=mot[i-longueurChaine];
  }
  chaine[longueurTot]='\0';
}

void handleText(char *txt, void *data) {
  parser_context_t *context = data;
  if(lecture){
    context->text_count++;
    printf("%s %ld\n", txt,strlen(txt));
  }
}

void handleOpenTag(char *tag, void *data) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||(!strcmp(tag,"title")&&tag_author)){
    context->open_count++;
    printf("%s : ", tag);
    lecture=1;
    if(!strcmp(tag,"author")){
      tag_author=1;
      nbAuteur++;
    }
    if(!strcmp(tag,"title")){
      nbTitre++;
    }
  }
}

void handleCloseTag(char *tag, void *data) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||(!strcmp(tag,"title")&&tag_author)){
    context->close_count++;
    //printf("CLOSE TAG %s\n", tag);
    lecture=0;
    if(!strcmp(tag,"title")){
      tag_author=0;
    }
  }
}


int main(int argc, char **argv)
{
  if(argc != 2) return 2;

  parser_context_t context = {};

  parser_info_t info;
  info.handleOpenTag = handleOpenTag;
  info.handleCloseTag = handleCloseTag;
  info.handleText = handleText;
  info.data = &context;

  int err;
  if(PARSER_OK != (err = parse(argv[1], &info)))
  {
    printf("NB TITRES : %d\nNB AUTEURS : %d\n",nbTitre,nbAuteur);
    return err;
  }
  return 0;
}
