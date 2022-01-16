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
int arriver(int nb_auteur_precedent, int nb_puit, graphe_type* graphe){
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    liste_sucesseurs_buffer=nmbre_separateur_a_sauter(nb_auteur_precedent, graphe);
    int k=0;
    while(liste_sucesseurs_buffer[k]!=';'){
        if(liste_sucesseurs_buffer[k]==nb_puit){
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
    size_t **liste_sucesseurs_buffer_un=malloc(sizeof(graphe->liste_sucesseurs));
    size_t **liste_sucesseurs_buffer_deux=malloc(sizeof(graphe->liste_sucesseurs));
    int numero_auteur_un=0;
    int numero_auteur_deux=0;
    int k=0;
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
    liste_sucesseurs_buffer_un=nmbre_separateur_a_sauter(numero_auteur_un,graphe);
    liste_sucesseurs_buffer_deux=(numero_auteur_deux, graphe);
    if(liste_sucesseurs_buffer_un[0]=='|' || liste_sucesseurs_buffer_deux[0]=='|'){
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