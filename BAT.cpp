#include "BAT.h"
#include "BatMonitor.h"

std::unordered_map<char, char> BAT::right;

int BAT::getId() { return id; }
char BAT::getDirection() { return direction; }
char BAT::getRight() { return right[direction]; }

void BAT::execute() {
    BatMonitor* monitor = BatMonitor::getInstance();
    monitor->arrive(*this);
    monitor->cross(*this);
    monitor->leave(*this);
}