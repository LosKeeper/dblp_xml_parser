#include "xmlp.h"
#include <stdio.h>
#include <string.h>


typedef struct parser_context_t {
    int text_count;
    int open_count;
    int close_count;
} parser_context_t;

int lecture=0;

void handleText(char *txt, void *data) {
  parser_context_t *context = data;
  if(lecture){
    context->text_count++;
    printf("TEXT %s\n", txt);
  }
}

void handleOpenTag(char *tag, void *data) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||!strcmp(tag,"title")){
    context->open_count++;
    printf("OPEN TAG %s\n", tag);
    lecture=1;
  }
}

void handleCloseTag(char *tag, void *data) {
  parser_context_t *context = data;
  if(!strcmp(tag,"author")||!strcmp(tag,"title")){
    context->close_count++;
    printf("CLOSE TAG %s\n", tag);
    lecture=0;
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
    return err;
  }

  printf(
    "open: %i\nclose: %i\ntext: %i\n", 
    context.open_count, 
    context.close_count, 
    context.text_count);

  return 0;
}
