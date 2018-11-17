#include <pthread.h>
#include "BatMonitor.h"

BatMonitor::BatMonitor() {
    pthread_mutex_init(&mutex, nullptr);

    pthread_cond_init(&nPass, nullptr);
    pthread_cond_init(&ePass, nullptr);
    pthread_cond_init(&wPass, nullptr);
    pthread_cond_init(&sPass, nullptr);

    pthread_cond_signal(&nPass);
    pthread_cond_signal(&ePass);
    pthread_cond_signal(&wPass);
    pthread_cond_signal(&sPass);

    waiting = 0;
}

void BatMonitor::check() {
    if (waiting == 4) { // All are waiting
        pthread_cond_signal(&wPass); // As if west has just passed to let North pass resolving deadlock
    }
}

BatMonitor* BatMonitor::getInstance() {
    if (instance == nullptr) {
        instance = new BatMonitor();
    }
    return instance;
}

void BatMonitor::arrive(BAT &bat) {
    pthread_mutex_lock(&mutex);
    // TODO: Implement arrival

    check();
    pthread_mutex_unlock(&mutex);
}

void BatMonitor::cross(BAT &bat) {
    pthread_mutex_lock(&mutex);
    // TODO: Implement cross

    check();
    pthread_mutex_unlock(&mutex);
}

void BatMonitor::leave(BAT &bat) {
    pthread_mutex_lock(&mutex);
    // TODO: Implement leave

    check();
    pthread_mutex_unlock(&mutex);
}
