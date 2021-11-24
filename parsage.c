#include <stdio.h>
#include <string.h>

typedef struct parse {
    char * title;
    char * author;
}parse;

int main(int argc, char ** argv){
    FILE * entree=fopen(argv[1],"r");
    if(!argc){
        return 0;
    }
    do{
        char buffer[1000];
        fgets(buffer,1000,entree);
        if(strstr(buffer, "<article")){
            printf("ARTICLE\n------------------------------------------------\n");
            while(!strstr(buffer,"</article>")){
                fgets(buffer,1000,entree);
                char * author = strstr(buffer,"<author>");
                if(author){
                    printf("%s",author);
                }
            }
            printf("------------------------------------------------\n\n");
        }
    }while(!feof(entree));
}