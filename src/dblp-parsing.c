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

unsigned short nbSignal = 0;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        nbSignal++;
        printf("Signal Ctrl^c n°%i reçu, processus tué au bout de 5 signaux "
               "reçus\n",
               nbSignal);
        if (nbSignal == 5) {
            exit(2);
        }
    }
}

int main(int argc, char **argv) {

    struct sigaction action;
    struct sigaction oldAction;
    action.sa_handler = &signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, &oldAction);

    options_t options;
    parseArgs(argc, argv, &options);
    // cleanOptions(&options);

    return 0;

    /* AVANT
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
        findTitleFromAuthor(&graphe, "Frank Manola");
        return 0;
        */
}