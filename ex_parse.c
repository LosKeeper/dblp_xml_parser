#include <stdio.h>
#include <string.h>


int main(void){
    FILE * entree=fopen("ex_parse.txt","r");
    char buffer[1000];
    fgets(buffer,1000,entree);
    char titre[100];
    strcpy(buffer-1,strstr(buffer, ";"));
    strcpy(titre,buffer);
    strstr(titre,";")[0]='\0';
    strstr(buffer,";")[8]='\0';
    printf("%s\n",buffer);
    printf("%s\n",titre);  
}
