#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int stop = 0;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        static unsigned short nbSignal = 0;
        nbSignal++;
        printf("Signal Ctrl^c n°%i reçu\n", nbSignal);
        if (nbSignal == 5)
            stop = 1;
    }
}

int main(void) {
    struct sigaction action, oldAction;

    action.sa_handler = signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, &oldAction);
    while (!stop)
        ;
    return 1;
}