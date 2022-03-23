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
        fprintf(stderr, "\x1B[32mOK !\x1B[0m\n");
        return 0;
    } else {
        fprintf(stderr, "\x1B[31mNot OK !\x1B[0m\n");
        return 1;
    }
}