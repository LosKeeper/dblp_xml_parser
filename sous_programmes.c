#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int co_auteurs(char * auteur1, char *auteur2){
    int k=0;
    FILE* fichier=NULL; 
    fichier=fopen(fichierthomas, "r+");
    if(!strcmp(auteur1,auteur2)){
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0")
        return 0;
    }
    else{
        char buffer[1000];
        fgets(buffer,1000, fichier)
        char chaine1[1000];
        char chaine2[1000];
        strstr(buffer,";")+1;
        strcpy(chaine1,buffer);
        strcpy(chaine2,buffer);
        do{
            strstr(chaine1,";")[k]='\0';
            strstr(chaine2,";")[k+1]='\0';
            k+=1;
        }while(buffer!=\0);
       // char *chaine1=strstr(buffer, ";")+1;
        //char *chaine2=strstr(buffer, ";")+1;
    }
    fclose(fichier);
}