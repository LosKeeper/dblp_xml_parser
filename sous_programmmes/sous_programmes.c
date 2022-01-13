#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef struct graphe_type {
    char **liste_auteurs;
    int nb_auteurs;
    char **liste_titres;
    int nb_titres;
    size_t **liste_sucesseurs;
    size_t *liste_nb_liens;
} graphe_type;


void nmbre_separateur_a_sauter(int R, graphe_type* graphe){
    int k=0;
    int somme=0;
    while(somme!=R){
        if(graphe->liste_sucesseurs[k]==';'){
            somme++;
            k++;
        }
        else{
            graphe->liste_sucesseurs[k]==graphe->liste_sucesseurs[k+1];
            k++;
        }
    }

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



void arriver(char* auteur1, char* auteur2, graphe_type* graphe, char* numero_auteur_precedent, char* numero_auteur_deux){
    if(graphe->liste_sucesseurs[]==1){
        printf("On a atteint l'auteur voulu\n");
        return 1;
    }
    else{
        return 0;
    }
}


int dijkstra(char* auteur1, char* auteur2, graphe_type* graphe){
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
        return 1;
    }
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
        if(graphe->matrice_adj[numero_auteur_un][q]==1){
            somme_un++;
        }
        else if(graphe->matrice_adj[numero_auteur_deux][q]==1){
            somme_deux++;
        }
    if(somme_un==0 || somme_deux==0){
        printf("L'un des deux auteurs n'a co-écrit aucun récit\n");
        printf("Le chemin le plus court est de 0 (chemin impossible entre les auteurs)");
        return 0;
    }
    }
    if(graphe->matrice_adj[numero_auteur_deux][numero_auteur_un]==1){
    printf("le chemin le plus court est de 1 (chemin direct d'un auteur à l'autre)");
    return arriver;
    }
    int** tableau_dijkstra=malloc(graphe->nb_auteurs);
    } 