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

int** bufferiserchemin(int** tableau_dijkstra, int* chemin,int k){

}


size_t** nmbre_separateur_a_sauter(int nb_auteur, graphe_type* graphe){
    int k=0;
    int somme=0;
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    while(somme!=nb_auteur){
        if(liste_sucesseurs_buffer[k]==';'){
            somme++;
            k++;
        }
        else{
            liste_sucesseurs_buffer[k]==liste_sucesseurs_buffer[k+1];
            k++;
        }
        return liste_sucesseurs_buffer;
    }
}
void verifier_si_successeurs(int nb_auteur, graphe_type* graphe){
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    liste_sucesseurs_buffer=nmbre_separateur_a_sauter(nb_auteur, graphe);
    if(liste_sucesseurs_buffer[0]=='|'){
        goto fin_boucle;
    }
    fin_boucle;
}

int arriver(int nb_auteur_precedent, int nb_puit, graphe_type* graphe){
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    liste_sucesseurs_buffer=nmbre_separateur_a_sauter(nb_auteur_precedent, graphe);
    int k=0;
    while(liste_sucesseurs_buffer[k]!=';'){
        if(liste_sucesseurs_buffer[k]==nb_puit){
            printf("On est arrivé\n");
            return 1;
            k++;
        }
        else{
            k++;
        }
    }
}








/** https://github.com/samsonmolou/dijsktra-algorithm/blob/master/main.c */


int dijkstra(char* auteur1, char* auteur2, graphe_type* graphe){
    int etape_chemin=0;
    size_t **liste_sucesseurs_buffer_un=malloc(sizeof(graphe->liste_sucesseurs));
    size_t **liste_sucesseurs_buffer_deux=malloc(sizeof(graphe->liste_sucesseurs));
    int numero_auteur_un=-1;
    int numero_auteur_deux=-1;
    int k=0;
    if(!strcmp(auteur1,auteur2)){
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0");
        goto fin_boucle;
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
    if(numero_auteur_un==-1 || numero_auteur_deux==-1){
        printf("L'un des deux auteurs n'existe pas");
        return 0;
        goto fin_boucle;
    }
    liste_sucesseurs_buffer_un=nmbre_separateur_a_sauter(numero_auteur_un,graphe);
    liste_sucesseurs_buffer_deux=nmbre_separateur_a_sauter(numero_auteur_deux, graphe);
    if(liste_sucesseurs_buffer_un[0]=='|' || liste_sucesseurs_buffer_deux[0]=='|'){
        printf("L'un des deux auteurs n'a co-écrit aucun récit\n");
        printf("Le chemin le plus court est de 0 (chemin impossible entre les auteurs)");
        return 0;
        goto fin_boucle;
    }
    }
    k=0;
    while(liste_sucesseurs_buffer_un[k]!=';'){
        if(liste_sucesseurs_buffer_un[k]==numero_auteur_deux){
            printf("le chemin le plus court est de 1 (chemin direct d'un auteur à l'autre)");
            goto fin_boucle;
        }
        else{
            k++;
        }
    }
    k=0;
    int** tableau_dijkstra=malloc(graphe->nb_auteurs);
    tableau_dijkstra[numero_auteur_un][1]=0;

    while(liste_sucesseurs_buffer_un[k]!=';'){
        tableau_dijkstra[][]=liste_sucesseurs_buffer_un[k];
    }
    fin_boucle:;
    } 

    