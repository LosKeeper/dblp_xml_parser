#include <stdio.h>
#include <string.h>

typedef struct parse {
    char *title;
    int nbAuthor;
    char *author;
} parse;

int main(int argc, char **argv) {
    FILE *entree = fopen(argv[1], "r");
    if (argc < 1 || argc > 2) {
        return 0;
    }
    char buffer[200];
    fgets(buffer, 200, entree);
    do {
        if (strstr(buffer, "<article")) {
            printf(
                "ARTICLE\n------------------------------------------------\n");
            do {
                char *author = strstr(buffer, "<author>");
                char *title = strstr(buffer, "<title>");
                if (author) {
                    strstr(buffer, "</author>")[0] = '\0';
                    printf("Auteur : %s\n", author + 8);
                }
                if (title) {
                    strstr(buffer, "</title>")[0] = '\0';
                    printf("Titre : %s\n", title + 7);
                }
                fgets(buffer, 1000, entree);
            } while (!strstr(buffer, "</article>"));
            printf("------------------------------------------------\n\n");
        } else {
            fgets(buffer, 200, entree);
        }
    } while (!feof(entree));
}