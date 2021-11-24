#include <stdio.h>
#include <string.h>

int main(void){
    FILE * entree=fopen("ex_parse.txt","r");
    char buffer[1000];
    fgets(buffer,1000,entree);
    char chaine[1000];
    strcpy(chaine,buffer);
    strstr(chaine,";")[0]='\0';
    printf("%s\n",buffer);
    printf("%s\n",chaine);
}