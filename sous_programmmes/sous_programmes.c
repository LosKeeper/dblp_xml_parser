#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int nmbre_separateur(char* string){
    int k=0;
    int somme=0;
    FILE* fichier=NULL;
    fichier=fopen(fichierthomas, "r+");
    char buffer[1000];
    fgets(buffer,1000,fichier);
    while(string[k]!='\0'){
        if(string[k]==';'){
            somme++;
            k++;
        }
        else{
            k++;
        }
    }

}

int nombres_comparaisons_a_realiser(){
    int k;
    int somme=nmbre_separateur(fichierthomas);
    int nombre_comparaisons=0;
    for(k=1; k<somme-1;k++){
        nombre_comparaisons+=k;
    }
    return nombre_comparaisons;
}

/**
int inverser_chaine(char* auteurs){
        char str[100], rev[100];
    int t, i, j;
 
    
    j = 0;
    t = strlen(auteurs);
 
    rev[t] = '\0'; //le dernier caractère doit toujours être égale à '\0'.
    for (i = t - 1; i >= 0; i--)
    {
      rev[j++] = str[i];
    }
    rev[i] = '\0';
    printf("%s\n", rev);
    return 0;
}
*/


int co_auteurs(char * auteur1, char *auteur2){
    int k=0;
    FILE* fichier=NULL; 
    fichier=fopen(fichierthomas, "r+");
    if(!strcmp(auteur1,auteur2)){
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0");
        return 0;
    }
    else{
        char buffer[1000];
        fgets(buffer,1000, fichier);
        char chaine1[100];
        char chaine2[100];
        strcpy(buffer-1,strstr(buffer, ";"));
        strcpy(chaine1,buffer);
        strcpy(chaine2,buffer);
        do{
            strstr(chaine1,";")[k]='\0';
            strstr(chaine2,";")[k+1]='\0';
            k+=1;
        }while(buffer!=\0);                 
    }
    fclose(fichier);
}



/** https://github.com/samsonmolou/dijsktra-algorithm/blob/master/main.c */