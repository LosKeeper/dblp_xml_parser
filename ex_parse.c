#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    int k=0;
    FILE * entree=fopen("ex_parse.txt","r");
    char buffer[1000];
    char buffercpy[1000];
    strcpy(buffercpy,buffer);
    fgets(buffer,1000,entree);
    char titre[100];
    strcpy(buffer-1,strstr(buffer, ";"));
    strcpy(titre,buffer);
    strstr(titre,";")[0]='\0';
    strstr(buffer,";")[8]='\0';
    while(k<strlen(titre)){
        buffercpy[k]= buffercpy[k+1];
        buffercpy[strlen(buffercpy)-1]='\0';
        k+=1;   
}
    printf("%s\n",buffer);
    printf("%s\n",titre);
    printf("%ld\n",strlen(titre));
    printf("%s\n",buffercpy);
}