#include "BAT.h"
#include "BatMonitor.h"

int BAT::getId() { return id; }
char BAT::getDirection() { return direction; }

void BAT::execute() {
    BatMonitor* monitor = BatMonitor::getInstance();
    monitor->arrive(*this);
    monitor->cross(*this);
    monitor->leave(*this);
}