#ifndef BATMAN_BATMONITOR_H
#define BATMAN_BATMONITOR_H


#include <zconf.h>
#include "BAT.h"

class BatMonitor {
private:
    BatMonitor* instance;

    pthread_mutex_t mutex;

    pthread_cond_t nPass;
    pthread_cond_t ePass;
    pthread_cond_t wPass;
    pthread_cond_t sPass;

    BatMonitor();

    void check();

public:
    static BatMonitor getInstance();

    void arrive(BAT &bat);
    void cross(BAT &bat);
    void leave(BAT &bat);

};


#endif //BATMAN_BATMONITOR_H
