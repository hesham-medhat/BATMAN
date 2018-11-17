#ifndef BATMAN_BATMONITOR_H
#define BATMAN_BATMONITOR_H


#include <zconf.h>
#include "BAT.h"

class BatMonitor {
private:
    static BatMonitor* instance;

    /* Number of BATs currently waiting */
    int waiting;

    pthread_mutex_t mutex;

    /* Condition variables for passing BATs from initial directions */
    pthread_cond_t nPass;
    pthread_cond_t ePass;
    pthread_cond_t wPass;
    pthread_cond_t sPass;

    /* Private constructor only accessible by getInstance applying singleton design pattern */
    BatMonitor();

    /* Deadlock checker and resolver. Allows north to pass resolving deadlock if present */
    void check();

public:
    /* Ensures there is only one instance of this type and returns it */
    static BatMonitor* getInstance();

    /* Monitor operations called by BATs */
    void arrive(BAT &bat);
    void cross(BAT &bat);
    void leave(BAT &bat);

    ~BatMonitor();

};


#endif //BATMAN_BATMONITOR_H
