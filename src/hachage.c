#include <stdlib.h>
#include <string.h>

#include "hachage.h"

unsigned int hache(char *chaine) {
    unsigned int a = 9887;
    unsigned int b = 49919;
    unsigned int h = 0;
    for (size_t k = 0; k < strlen(chaine); k++) {
        h += (unsigned int)(a * chaine[k] + b);
    }
    return (unsigned int)h % 100000;
}

void indexation_auteur(char **liste_auteurs, size_t nb_auteurs,
                       graphe_t *graphe, int *liste_index_auteurs) {
    int auteurs_nouveaux = 0;
    for (size_t k = 0; k < nb_auteurs; k++) {
        unsigned int h = hache(liste_auteurs[k]);
        if (graphe->nb_auteurs_hache[h] > 0) {
            for (size_t i = 0; i < graphe->nb_auteurs_hache[h]; i++) {
                size_t index = graphe->hachage_auteurs[h][i];
                if (graphe->liste_auteurs[index]) {
                    if (!strcmp(liste_auteurs[k],
                                graphe->liste_auteurs[index])) {
                        liste_index_auteurs[k] = index;
                        goto pas_ajout;
                    }
                }
            }
            liste_index_auteurs[k] = -1;
            graphe->hachage_auteurs[h] =
                realloc(graphe->hachage_auteurs[h],
                        (graphe->nb_auteurs_hache[h] + 1) * sizeof(size_t));
            testAlloc(graphe->hachage_auteurs[h]);
            auteurs_nouveaux++;
            graphe->hachage_auteurs[h][graphe->nb_auteurs_hache[h]] =
                graphe->nb_auteurs + auteurs_nouveaux;
            graphe->nb_auteurs_hache[h]++;

        } else {
            graphe->hachage_auteurs[h] =
                realloc(graphe->hachage_auteurs[h],
                        (graphe->nb_auteurs_hache[h] + 1) * sizeof(size_t));
            testAlloc(graphe->hachage_auteurs[h]);
            graphe->hachage_auteurs[h][0] = graphe->nb_auteurs + k;
            graphe->nb_auteurs_hache[h]++;
            liste_index_auteurs[k] = -1;
        }
    pas_ajout:;
    }
}