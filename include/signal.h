#ifndef SIGNAL_H
#define SIGNAL_H
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Init signal interruption
 *
 * @param action the action is stored here
 * @param oldAction the old action is stored here
 **/
void initSignal(struct sigaction action, struct sigaction oldAction);

/**
 * @brief The function executed after the interruption detected
 *
 * @param signal correspond to the signal received
 **/
void signalHandler(int signal);

#endif