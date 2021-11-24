#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int co_auteurs(char * auteur1, char *auteur2){
    FILE* fichier=NULL; 
    fichier=fopen(fichierthomas, "r+");
    if(!strcmp(auteur1,auteur2)){
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0")
        return 0;
    }
    else{
        char* marqueur;
        while(fscanf(fichier, "%c", &marqueur)!=EOF){

        }
    }
    fclose(fichier);
}