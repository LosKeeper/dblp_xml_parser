// utilser memcpy

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments.h"
#include "graphe.h"
#include "hachage.h"
#include "parsage.h"
#include "struct.h"
#include "xmlp.h"

void signalHandler(int signal) {
    if (signal == SIGINT) {
        static unsigned short nbSignal = 0;
        nbSignal++;
        printf("Signal Ctrl^c n°%i reçu\n", nbSignal);
    }
}

int main(int argc, char **argv) {
    if (argc != 3)
        return 2;

    struct sigaction action;
    struct sigaction oldAction;
    action.sa_handler = &signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, &oldAction);

    graphe_t graphe;
    initGraphe(&graphe);

    data_t xmlData;
    initData(&xmlData);

    parser_context_t context = {};
    parser_info_t info;
    initInfo(&info, &context);

    FILE *sortie = fopen(argv[2], "w");

    parse(argv[1], &info, &xmlData, &graphe);
    printGraphe(&graphe, sortie);
    return 0;
}