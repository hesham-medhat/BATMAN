#ifndef BATMAN_BATMONITOR_H
#define BATMAN_BATMONITOR_H


#include <zconf.h>
#include <unordered_map>

#include "BAT.h"

class BatMonitor {
private:
    static BatMonitor* instance;

    std::unordered_map<char, pthread_cond_t*> passCondMap;
    std::unordered_map<char, pthread_cond_t*> qCondMap;
    std::unordered_map<char, size_t> queueSize;

    /* Number of BATs currently waiting */
    int waiting;

    bool crossing;

    pthread_mutex_t mutex;
    pthread_mutex_t passing;

    /* Condition variables for passing BATs from initial directions */
    pthread_cond_t nPass;
    pthread_cond_t ePass;
    pthread_cond_t wPass;
    pthread_cond_t sPass;
    pthread_cond_t nQ;
    pthread_cond_t eQ;
    pthread_cond_t wQ;
    pthread_cond_t sQ;

    /* Private constructor only accessible by getInstance applying singleton design pattern */
    BatMonitor();

    /* Deadlock checker and resolver. Allows north to pass resolving deadlock if present */
    void check(BAT &bat);

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
