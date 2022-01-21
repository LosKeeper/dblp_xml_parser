#include "signal.h"

void initSignal(struct sigaction action, struct sigaction oldAction) {
    action.sa_handler = signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, &oldAction);
}

void signalHandler(int signal) {
    if (signal == SIGINT) {
        static unsigned short nbSignal = 0;
        nbSignal++;
        printf("Signal Ctrl^c n°%i reçu\n", nbSignal);
    }
}