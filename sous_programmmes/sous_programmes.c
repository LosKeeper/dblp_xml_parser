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


size_t** nmbre_separateur_a_sauter(int nb_auteur, graphe_type* graphe){
    int k=0;
    int somme=0;
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    while(somme!=nb_auteur){
        liste_sucesseurs_buffer[k]==liste_sucesseurs_buffer[k+1];
        k++;
        somme++;
    }
    return liste_sucesseurs_buffer;
}

int arriver(int nb_auteur_precedent, int nb_puit, graphe_type* graphe){
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    liste_sucesseurs_buffer=nmbre_separateur_a_sauter(nb_auteur_precedent, graphe);
    int k=0;
    while(k!=graphe->liste_nb_liens){
        if(liste_sucesseurs_buffer[k]==nb_puit){
            printf("On est arrivé\n");
            return 1;
            k++;
        }
        else{
            k++;
        }
    }
    return 0;
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
    if(graphe->liste_sucesseurs[numero_auteur_un]==0 || graphe->liste_sucesseurs[numero_auteur_deux]==0){
        printf("L'un des deux auteurs n'a co-écrit aucun récit\n");
        printf("Le chemin le plus court est de 0 (chemin impossible entre les auteurs)");
        return 0;
        goto fin_boucle;
    }
    }
    k=0;
    int somme=0;
    while(graphe->liste_sucesseurs[numero_auteur_un]!=somme){
        if(liste_sucesseurs_buffer_un[k]==numero_auteur_deux){
            printf("le chemin le plus court est de 1 (chemin direct d'un auteur à l'autre)");
            goto fin_boucle;
        }
        else{
            k++;
        }
    }
    int etape=0;
    somme=0;
    k=0;
    int auteur_buffer;
    int** tableau_dijkstra=malloc(graphe->nb_auteurs);
    size_t** liste_sucesseurs_buffer=malloc(1000);
    tableau_dijkstra[0][numero_auteur_un]=0-0;
    while(graphe->liste_nb_liens[k]!=somme){
        somme++;
        etape++;
        auteur_buffer=liste_sucesseurs_buffer_un[0+2*k];
        liste_sucesseurs_buffer=nmbre_separateur_a_sauter(auteur_buffer, graphe);
        while(liste_sucesseurs_buffer[k]!=';'){
            if(liste_sucesseurs_buffer_un[0+2*k]==){

            }
        }
    }
    fin_boucle:;
    } 

    