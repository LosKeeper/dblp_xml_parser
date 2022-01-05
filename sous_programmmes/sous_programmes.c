#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct graphe_type {
    char **liste_auteurs;
    int nb_auteurs;
    char **liste_titres;
    int nb_titres;
    int **matrice_adj;
} graphe_type;

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


/**int co_auteurs(char * auteur1, char *auteur2){
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
*/



/** https://github.com/samsonmolou/dijsktra-algorithm/blob/master/main.c */


void dijkstra(char* auteur1, char* auteur2, graphe_type* graphe){
    FILE* fichier=NULL;
    fichier=fopen(fichierthomas);
    int numero_auteur_un=0;
    int numero_auteur_deux=0;
    int k=0;
    int q;
    int somme_un=0;
    int somme_deux;
    if(!strcmp(auteur1,auteur2)){
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0");
    while(k<((graphe->nb_auteurs)-1)){
        if(graphe->liste_auteurs[k]==auteur1){
            numero_auteur_un=k;
            k++;
        }
        else if(graphe->liste_auteurs[k]==auteur2){
            numero_auteur_deux=k;
            k++;
        }
        else{
            k++;
        }
    for(q=0; q<((graphe->nb_auteurs)-1); q++){
        if(graphe->matrice_adj[q][numero_auteur_un]==1){
            somme_un++;
            break;
        }
        if(graphe->matrice_adj[q][numero_auteur_deux]==1){
            somme_deux++;
            break;
        }
        else{
            continue;
        }
    if(somme_un==0 || somme_deux==0){
        printf("L'un des deux auteurs n'a co-écrit aucun récit\n");
        printf("Le chemin le plus court est de 0 (chemin impossible entre les auteurs)");
    }
    }
    if(graphe->matrice_adj[numero_auteur_un][numero_auteur_deux]==1){
    printf("le chemin le plus court est de 1 (chemin direct d'un auteur à l'autre)");
    }
    int** tableau_dijkstra[graphe->nb_auteurs]= {0};
 