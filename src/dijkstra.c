#include "struct.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
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
*/
/*
int arriver(int nb_auteur_precedent, int nb_puit, graphe_type* graphe){
    size_t **liste_sucesseurs_buffer=malloc(sizeof(graphe->liste_sucesseurs));
    liste_sucesseurs_buffer=nmbre_separateur_a_sauter(nb_auteur_precedent,
graphe); int k=0; while(k!=*graphe->liste_nb_liens){
        if(liste_sucesseurs_buffer[nb_auteur_precedent][k]==nb_puit){
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
*/

char *chemin(int **tableau_dijkstra, int numero_auteur_deux, int cout_chemin) {
    printf("Le coût de ce chemin est de : %d \n", cout_chemin);
    printf("Le chemin est le suivant : \n");
    int k = 0;
    int i = numero_auteur_deux;
    while (k != cout_chemin) {
        printf("%d - ", tableau_dijkstra[i][1]);
        i = tableau_dijkstra[i][1];
    }
}

char *dijkstra(char *auteur1, char *auteur2, graphe_type *graphe) {
    int etape_chemin = 0;
    int numero_auteur_un = -1;
    int numero_auteur_deux = -1;
    int k = 0;
    if (!strcmp(auteur1, auteur2)) {
        printf("C'est le même auteur\n");
        printf("Le chemin le plus court est de 0");
        goto fin_boucle;
    }
    while (k < ((graphe->nb_auteurs) - 1)) {
        if (graphe->liste_auteurs[k] == auteur1) {
            numero_auteur_un = k;
            k++;
        } else if (graphe->liste_auteurs[k] == auteur2) {
            numero_auteur_deux = k;
            k++;
        } else {
            k++;
        }
        if (numero_auteur_un == -1 || numero_auteur_deux == -1) {
            printf("L'un des deux auteurs n'existe pas");
            goto fin_boucle;
        }
        if (graphe->liste_nb_liens[numero_auteur_un] == 0 ||
            graphe->liste_nb_liens[numero_auteur_deux] == 0) {
            printf("L'un des deux auteurs n'a co-écrit aucun récit\n");
            printf("Le chemin le plus court est de 0 (chemin impossible entre "
                   "les auteurs)");
            goto fin_boucle;
        }
    }
    k = 0;
    size_t somme = 0;
    while (graphe->liste_nb_liens[numero_auteur_un] != somme) {
        if ((int)graphe->liste_sucesseurs[numero_auteur_un][k] ==
            numero_auteur_deux) {
            printf("le chemin le plus court est de 1 (chemin direct d'un "
                   "auteur à l'autre)");
            goto fin_boucle;
        } else {
            k++;
        }
    }
    int etape = 0;
    somme = 0;
    k = 0;
    int numero_auteur_buffer_precedent = numero_auteur_un;
    int numero_auteur_buffer;
    int **tableau_dijkstra = malloc(graphe->nb_auteurs);
    tableau_dijkstra[0][numero_auteur_un] = 0 - 0;
    while (graphe->liste_nb_liens[numero_auteur_un] != somme) {
        somme++;
        etape++;
        numero_auteur_buffer = graphe->liste_sucesseurs[numero_auteur_un][k];
        int somme_buffer = 0;
        while ((int)graphe->liste_nb_liens[numero_auteur_buffer] !=
               somme_buffer) {
            if ((int)graphe->liste_sucesseurs[numero_auteur_buffer][k] ==
                numero_auteur_deux) {
                tableau_dijkstra[0][numero_auteur_buffer] =
                    etape - numero_auteur_un;
                tableau_dijkstra[0][numero_auteur_deux] =
                    etape - numero_auteur_buffer;
                return chemin(tableau_dijkstra, numero_auteur_deux,
                              tableau_dijkstra[numero_auteur_deux][0]);
            } else {
                tableau_dijkstra[0][numero_auteur_buffer] =
                    etape - numero_auteur_buffer_precedent;
                somme_buffer++;
                numero_auteur_buffer_precedent = numero_auteur_buffer;
            }
        }
        printf("Aucun chemin n'existe entre l'auteur numéro un et l'auteur "
               "numéro deux\n");
    }
fin_boucle:;
}

int main() { return 0; }