#ifndef BATMAN_BAT_H
#define BATMAN_BAT_H

#include <unordered_map>

class BAT {
private:

    int id;
    char direction;

public:
    static std::unordered_map<char, char> right;
    BAT(const int id, const char &direction) : id(id), direction(direction) { }

    void execute();

    int getId();
    char getDirection();
    char getRight();
};


#endif //BATMAN_BAT_H
