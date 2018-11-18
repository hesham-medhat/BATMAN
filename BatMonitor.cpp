#include <pthread.h>
#include <iostream>
#include "BatMonitor.h"

BatMonitor* BatMonitor::instance;

BatMonitor::BatMonitor() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_mutex_init(&passing, nullptr);

    pthread_cond_init(&nPass, nullptr);
    pthread_cond_init(&ePass, nullptr);
    pthread_cond_init(&wPass, nullptr);
    pthread_cond_init(&sPass, nullptr);
    pthread_cond_init(&nQ, nullptr);
    pthread_cond_init(&eQ, nullptr);
    pthread_cond_init(&wQ, nullptr);
    pthread_cond_init(&sQ, nullptr);

    passCondMap['n'] = &nPass;
    passCondMap['e'] = &ePass;
    passCondMap['w'] = &wPass;
    passCondMap['s'] = &sPass;
    qCondMap['n'] = &nQ;
    qCondMap['e'] = &eQ;
    qCondMap['w'] = &wQ;
    qCondMap['s'] = &sQ;

    BAT::right['n'] = 'w';
    BAT::right['w'] = 's';
    BAT::right['s'] = 'e';
    BAT::right['e'] = 'n';

    queueSize['n'] = 0;
    queueSize['w'] = 0;
    queueSize['s'] = 0;
    queueSize['e'] = 0;

    waiting = 0;
}

void BatMonitor::check(BAT &bat) {
    if (waiting == 4) { // All are waiting
        pthread_cond_signal(passCondMap[bat.getDirection()]);
        std::cout << "DEADLOCK: BAT jam detected, resolving dynamically" << std::endl;
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

    queueSize[bat.getDirection()]++;
    if (queueSize[bat.getDirection()] > 1) pthread_cond_wait(qCondMap[bat.getDirection()], &mutex);
    printf("BAT %d from %c arrives at crossing\n", bat.getId(), bat.getDirection());

    waiting++;

    pthread_mutex_unlock(&mutex);
}

void BatMonitor::cross(BAT &bat) {
    pthread_mutex_lock(&mutex);

    if (queueSize[bat.getRight()] > 0) pthread_cond_wait(passCondMap[bat.getRight()], &mutex);

    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&passing);

    pthread_mutex_lock(&mutex);

    waiting--;
    printf("BAT %d from %c crossing\n", bat.getId(), bat.getDirection());
    queueSize[bat.getDirection()]--;
    pthread_cond_signal(qCondMap[bat.getDirection()]);

    pthread_mutex_unlock(&mutex);

    sleep(1);

    pthread_mutex_unlock(&passing);
}


void BatMonitor::leave(BAT &bat) {
    pthread_mutex_lock(&mutex);

    printf("BAT %d from %c leaving crossing\n", bat.getId(), bat.getDirection());
    pthread_cond_signal(passCondMap[bat.getDirection()]);

    pthread_mutex_unlock(&mutex);
}

BatMonitor::~BatMonitor() {
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&passing);

    pthread_cond_destroy(&nPass);
    pthread_cond_destroy(&ePass);
    pthread_cond_destroy(&wPass);
    pthread_cond_destroy(&sPass);
    pthread_cond_destroy(&nQ);
    pthread_cond_destroy(&eQ);
    pthread_cond_destroy(&wQ);
    pthread_cond_destroy(&sQ);

}