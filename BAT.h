#ifndef BATMAN_BAT_H
#define BATMAN_BAT_H


class BAT {
private:
    int id;
    char direction;

public:
    BAT(const int id, const char &direction) : id(id), direction(direction) { }

    void execute();

    int getId();
    char getDirection();
};


#endif //BATMAN_BAT_H
