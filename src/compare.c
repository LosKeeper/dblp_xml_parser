#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compare.h"

int compareFile(char *file1, char *file2) {
    char command[50];
    strcpy(command, "cmp ");
    strcat(command, file1);
    strcat(command, " ");
    strcat(command, file2);
    if (!system(command)) {
        fprintf(stderr, "OK !\n");
        return 0;
    } else {
        fprintf(stderr, "Not OK !\n");
        return 1;
    }
}