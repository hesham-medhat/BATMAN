#include <iostream>
#include <cstring>

#include "BAT.h"
#include "BatMonitor.h"

BatMonitor* monitor;

void createBats(BAT* bat[], char* ss) {
    int i = 1;
    while (ss != nullptr) {
        bat[i] = new BAT(i, *ss);
        i++;
        ss++;
    }
}

static void* runBat(void* batPtr) {
    BAT bat = *((BAT*) batPtr);
    // TODO: Execute thread and simulate.

    return nullptr;
}

void runSimulation(pthread_t runner[], BAT* bat[], size_t bats) {
    for (int i = 1; i < bats; i++) pthread_create(&runner[i], nullptr, runBat, bat[i]);
}

void joinThreads(pthread_t runner[], size_t bats) {
    for (int i = 1; i < bats; i++) pthread_join(runner[i], nullptr);
}

void cleanupBats(BAT* bat[], const size_t bats) {
    for (int i = 1; i < bats; i++) free(bat[i]);
}

int main(int argc, char* args[]) {
    if (argc == 1) {
        std::cout << "No simulation string received." << std::endl;
        return -1;
    }
    /* Initialisation */
    char* ss = args[1];
    size_t bats = strlen(ss);
    BAT* bat[bats + 1];
    pthread_t runner[bats + 1];

    /* Prepare mutex */
    monitor = BatMonitor::getInstance();

    /* Simulation */
    createBats(bat, ss);
    runSimulation(runner, bat, bats);

    /* Clean up */
    joinThreads(runner, bats);
    cleanupBats(bat, bats);
    free(monitor);

    return 0;
}