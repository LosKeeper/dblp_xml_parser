#include <stdio.h>
#include <stdlib.h>

typedef struct parse {
    char * title;
    char * author;
}parse;

int main(int argc, char ** argv){
    FILE * entree=fopen(argv[1],"r");
    do{
        char * buffer[1000];
        fgets(buffer,1000,entree);
        if(strstr(buffer, "</article>")){

        }
    }while(!feof(entree));
}