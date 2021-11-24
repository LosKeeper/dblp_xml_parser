#include <stdio.h>
#include <string.h>

typedef struct parse {
    char * title;
    char * author;
}parse;

int main(int argc, char ** argv){
    FILE * entree=fopen(argv[1],"r");
    if(argc < 1 || argc > 2){
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
                char * title = strstr(buffer,"<title>");
                if(author){
                    strstr(buffer,"</author>")[0]='\0';
                    printf("Auteur : %s\n",author+8);
                }
                if(title){
                    strstr(buffer,"</title>")[0]='\0';
                    printf("Titre : %s\n",title+7);
                }
            }
            printf("------------------------------------------------\n\n");
        }
    }while(!feof(entree));
}