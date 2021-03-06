#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments.h"
#include "compare.h"
#include "graphe.h"
#include "hachage.h"
#include "parsage.h"
#include "struct.h"
#include "xmlp.h"

int main(void) {
    // test write binary file from an another file
    graphe_t graphe;
    initGraphe(&graphe);
    data_t data;
    initData(&data);
    parser_info_t info;
    parser_context_t context = {};
    initInfo(&info, &context);
    parse("test_export_binary/test_balise_a_la_ligne.xml", &info, &data,
          &graphe);
    FILE *sortie = fopen("test_export_binary/my_export.txt", "w");
    printGraphe(&graphe, sortie);
    fclose(sortie);
    fprintf(stderr, "Test write binary file : ");
    compareFile("test_export_binary/my_export.txt",
                "test_export_binary/file_exported.txt");

    // test decode_html
    char encoded[] = "M. Tamer &Ouml;zsu";
    char decoded[] = "M. Tamer Ozsu";
    decode_html(encoded);
    fprintf(stderr, "Test decode html : ");
    if (!strcmp(encoded, decoded)) {
        fprintf(stderr, "\x1B[32mOK !\x1B[0m\n");
    } else {
        fprintf(stderr, "\x1B[31mNot OK !\x1B[0m\n");
    }

    // test import binary file
    graphe_t graphe2;
    initGraphe(&graphe2);
    FILE *entree2 = fopen("test_import_binary/file_to_import.txt", "r");
    FILE *sortie2 = fopen("test_import_binary/my_export.txt", "w");
    importGraphe(&graphe2, entree2);
    printGraphe(&graphe2, sortie2);
    fprintf(stderr, "Test import binary file : ");
    compareFile("test_import_binary/file_to_import.txt",
                "test_import_binary/my_export.txt");
    fclose(entree2);
    fclose(sortie2);
}